# JAMNIK - DACHSHUND
![jamnik1](https://user-images.githubusercontent.com/15147818/30785475-6be08bc2-a167-11e7-89fb-f1d0cfbbc1aa.jpg) ![jamnik2](https://user-images.githubusercontent.com/15147818/30785454-2b70f39c-a167-11e7-9060-58dd86775a70.jpg) ![screenshot_2017-09-24-20-21-18-291_com example ania jamnik](https://user-images.githubusercontent.com/15147818/30786390-0a9ba582-a175-11e7-8181-006393cfc8f3.png)

## Overwiev
Can't you have a dog? Do you have allergies to fur? Parents don't want a small furry family member?
Calm down! You can create your own dachshund and... it will not mess up! :)

## Description
Project include a program in C language for microcontroller STM32F407VG DISCOVERY and an Android application in Java.
Whole dachshund is powered by a Power Bank. It's controlled by application and it can move forward, backward, left and right.

## IDE
- CoIDE 1.7.8
- Android Studio 2.3.3

## Tools
- Microcontroller STM32F407VG DISCOVERY
- Bluetooth module HC-06 FC-114
- HG7881 module (L9110) for engines
- Chassis 2WD Robot Car
- Power Bank 
- Smartphone with Android system

## Connection
- **Bluetooth module**<br>
RX - PC10 <br>
TX - PC11 <br>
GND - GND <br>
VCC - 5V <br>
STATE and EX - not connected <br>

- **HG7881 module for engines** <br>
A-1A - PC8 <br>
A-1B - PC9 <br>
B-1A - PC7 <br>
B-2A - PC6 <br>
VCC - 5V <br>
GND - GND <br>

## How to run
 - **Microcontroller part:** <br>
 Connect STM32 microcontroller to your computer via USB. Then open project in CoIDE and click *Download Code To Flash*.
 - **Android application part:** <br>
 Connect smartphone to your computer via USB (you must have enabled developer mode in it!). Then open project in Android Studio and click *Run* (Android Studio automatically find your ADB in phone). Press *Install* on your phone.

## Authors
- [Anna Zdrojewska](https://github.com/SideCut13)
- [Marek Wojciechowski](https://github.com/marek27)

## Supervisor
- [PhD Marek Kraft](http://www.marekkraft.info/)

## Credits
The project was made during the Microprocessor Lab course held by the Institute of Control and Information Engineering, Poznan University of Technology. 
