<<<<<<< HEAD
# How to make a DIY Pixel Stick   

Please watch my related video     
 https://www.youtube.com/watch?v=Cxnwvp_BdA0  
and subscribe to my Youtube channel if you like this project.

## Introduction
The pixelstick is an ADRESSABLE RGB LED STRIP controlled by an Arduino that can display all sorts of animations to make awesome lightpaintings photographs.  
Each LED acts like a pixel on a screen,  displaying an image one vertical line at a time as you walk. These vertical lines, when captured by a long exposure photography, combine to recreate your image in mid air, leaving the person using it invisible.
This technique is also called [lightpaintings](https://fr.wikipedia.org/wiki/Light_painting).

![Image](./documentation/pixelstick_demo.jpg)

This repo provides a simple method to build a DIY version of the stick.
I believe it is one of the simplest method you'll find on the web (after the one which consists in directly buying the stick).

## How it works

I made a 40 LEDS long pixel stick.  
It allows me to display 40 pixels high images.

#### Step 1 :
I draw a 40 pixels **high** image on photoshop.  
The **width** is not important, it defines the length of your animation (a very large image will take a long time to display on the stick).  
The image can be anything : text, drawing, photo ... The only thing to know here is that a turned off LED is equivalent black.

For the next steps I'll use a 40x200 pixels "la fabrique diy" logo as an example.

#### Step 2 :
I run the "generate.py" script in the same folder as the previously saved png file.  
In the terminal command :
```
python generate.py
```
For every png file in the current folder, the python script generates a TXT file with the same name.

The script rotates the image and transforms it in an array of R,G,B colors than can easily be read by the Arduino.   
For our 40x200 pixels logo, the TXT file will contain 8000 comma separated RGB values.

I used this technique to simplify the Arduino sketch and avoid some UGLY .bmp extraction code (like I saw on other tutorials on the subject).

#### Step 3 :
I save all the txt files on a micro SD card.

#### Step 4 :

The Arduino program reads the  8000 values by batch of 40 every 120ms and maps them on the RGB strip.

Basically it "prints" each vertical line of our logo during 120 ms and the camera records and adds each subpart of the whole image.

The main `loop()` of the `pixelstick.ino` loops on the same animation until one presses the button input which switches to the next image on the sd card.

# Circuit and construction

In my video I used many power tools to build the stick.   
This is because I wanted to start off a raw plank of wood.
However you can grab any long object an attach an adressable LED STRIP to it to get the same result.  
"Adressable" strips can be addressed using a one-wire interface, allowing you full control over the color of each RGB LED. They run on 5V an are built with WS2812B leds.

The circuit is made of an SD Card module linked to an Arduino Nano as follow :
* MOSI -> pin 11
* MISO -> pin 12
* CLK -> pin 13
* CS -> pin 4
* VCC -> 5V
* GND -> GND

A standard pushbutton on pin 2 of the arduino (check the Arduino example to learn how to wire a button).

A 40 LEDS long adressable strip (these have 3 wires) linked to the same Arduino as follow :
* DIN -> pin 6

** Be careful ** : Adressable strips only run in one direction, the data input of the arduino should enter the strip (DI) (check the arrow on the strip)  
** Be careful 2** : if you wire the 5V and GND of the strip directly to the Arduino the amount of current required by the strip will burn your board. Instead power the arduino in parallel with the strip from a battery.

My Pixelstick is made of 40 LEDS. As each RGB LED draw 40mA, I used a 2A 5V smartphone backup battery to power the pixelstick (arduino + leds).

Once your circuit is ready, upload the `pixelstick.ino` on your board and you are good to go !


# License 

MIT License

Copyright (c) 2017 Lucas Berbesson

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
=======
The pixelstick is an ADRESSABLE RGB LED STRIP controlled by an Arduino that can display all sorts of animations to make awesome [lightpaintings](https://fr.wikipedia.org/wiki/Light_painting) photographs. 

The Arduino circuit contains an SD Card module where I can upload the images I want to display. 
>>>>>>> 80f564d46f02898cfb957344280f21e4072d2121
