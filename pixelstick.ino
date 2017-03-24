#include <Adafruit_NeoPixel.h>

// Neopixel data pin
#define PIN 6
// SD card CS pin
#define SDPin 4  


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)



// * SD card attached to SPI bus as follows:
// ** MOSI - pin 11
// ** MISO - pin 12
// ** CLK - pin 13
// ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

#include <SPI.h>
#include <SD.h>

// Neopixel data pin
#define PIN 6
// SD card CS pin
#define SDPin 4  



int buttonPin = 2;
bool playAnimation = true;
int buttonState = 0;
int file_position = 0;  
int m_NumberOfFiles = 0;
bool runAnimation = true;
String m_FileNames[10];
File root;
File dataFile;
String m_CurrentFilename = "";

int number_of_leds = 40;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(number_of_leds, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
 Serial.begin(115200);
 pinMode(buttonPin, INPUT);
 pinMode(13, OUTPUT);
 pinMode(5, OUTPUT);
 digitalWrite(5,HIGH);
 strip.begin();
 strip.show();
 setupSDcard();
 delay(100);
}

void loop() {
  if (digitalRead(buttonPin) == HIGH) {
     digitalWrite(13,HIGH);
     file_position++;
     Serial.println(file_position);
     delay(100);
     digitalWrite(13,LOW);
   }
  delay(500);
   Serial.print("Sending file");
   if ( file_position >= m_NumberOfFiles) {
    file_position = 0;
   }
   SendFile(m_FileNames[file_position]);
   ClearStrip();
   
}


void setupSDcard() {
 pinMode(SDPin, OUTPUT);

 while (!SD.begin(SDPin)) {
   Serial.println("SD init failed!");
   delay(500);
 }
 Serial.println("SD init done");
 delay(1000);
 root = SD.open("/");
 Serial.println("Scanning files");
 delay(500);
 GetFileNamesFromSD(root);
}

void GetFileNamesFromSD(File dir) {
 int fileCount = 0;
 String CurrentFilename = "";
 while(1) {
   File entry =  dir.openNextFile();
   if (! entry) {
     // no more files
     m_NumberOfFiles = fileCount;
     Serial.println("total files");
     Serial.println(fileCount);
   entry.close();
     break;
   }
   else {
       CurrentFilename = entry.name();
       if (CurrentFilename.endsWith(".TXT")) { //only txt files
         if(CurrentFilename.startsWith("_")){      // mac sidecar files start with _ and should not be included, may be on card if written from Mac
         }else{
           m_FileNames[fileCount] = entry.name();
           fileCount++;
         }
       }
   }
   entry.close();
 }
}
   

void SendFile(String Filename) {
 char temp[14];
 runAnimation = true;
 Filename.toCharArray(temp,14);
 Serial.println(Filename);
 dataFile = SD.open(temp);
 // if the file is available send it to the LED's
 if (dataFile) {
   int i = 0;
   int red, green, blue;
   strip.setPixelColor(1,255,255,255);
   strip.show();
   delay(500);
   strip.setPixelColor(1,0,0,0);
   strip.show();
   delay(500);
   strip.setPixelColor(1,255,255,255);
   strip.show();
   delay(500);
   strip.setPixelColor(1,0,0,0);
   strip.show();
   delay(2000);
   while(dataFile.available() && runAnimation){

     if (digitalRead(buttonPin) == HIGH) {
       runAnimation = false;
       break;
       delay(100);
     }
     
     if (i == (number_of_leds)) {
       i=0;
       strip.show();
       delay(120);
       }
     red = dataFile.parseInt();
     green = dataFile.parseInt();
     blue = dataFile.parseInt();
     strip.setPixelColor(i, red, green, blue);
     i++;  

     
   }
   Serial.print("closing file");
   dataFile.close();
 } else {
   Serial.print("  Error reading ");
   setupSDcard();
   return;
   }
 }


void ClearStrip() {
 int x;
 for(x=0;x<number_of_leds;x++) {
   strip.setPixelColor(x, 0);
 }
 strip.show();
}
