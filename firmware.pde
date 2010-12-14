#include <NewSoftSerial.h>
#include "oled.h"

NewSoftSerial augmentSerial(2, 3);
NewSoftSerial uclaSerial(4, 5);
int augmentResetPin = 8;
int uclaResetPin = 9;

Oled augmentScreen = Oled(&augmentSerial, 8);
Oled uclaScreen = Oled(&uclaSerial, 9);

void setup() {
  
  augmentSerial.begin(9600);
  pinMode(augmentResetPin, OUTPUT); 
  augmentScreen.init();
  augmentScreen.clear();
  
  uclaSerial.begin(9600);
  pinMode(uclaResetPin, OUTPUT); 
  uclaScreen.init();
  uclaScreen.clear();
  
  
}

void loop() {
  //draw an ellipse, you can use the function in oled_lib
  augmentScreen.drawCircle(78, 68, 10, 1, 63488);
  //draw arectangle, you can use the function in oled_lib
  augmentScreen.drawRectangle(10, 30, 120, 10, 1, 99999);
  
    //draw an ellipse, you can use the function in oled_lib
  uclaScreen.drawCircle(78, 68, 10, 1, 63488);
  //draw arectangle, you can use the function in oled_lib
  uclaScreen.drawRectangle(10, 30, 120, 10, 1, 99999);
  
  
  
}



