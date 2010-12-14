/*******************************************************
 * uOLED-160-GMD1 Driver for Arduino
 * 
 * Updated by Mustafa Bagdatli
 * http://mustafabagdatli.com
 * 12/02/2010
 * 
 * Original code by Oscar Gonzalez
 * www.bricogeek.com
 * August 2007
 * 
 * 
 * 
 * 
 *******************************************************/

#ifndef Oled_h
#define Oled_h


#define OLED_BAUDRATE                                           9600//57600

#define OLED_RESETPIN                                           8      // PIN of reset

#define OLED_INITDELAYMS                                        5000



// Initialisation routine

#define	OLED_DETECT_BAUDRATE					0x55



// Drawing routines

#define	OLED_CLEAR						0x45

#define	OLED_BKGCOLOR						0x42

#define	OLED_COPYPASTE						0x63



#define	OLED_LINE						0x4C

#define	OLED_CIRCLE						0x43

#define	OLED_CIRCLEFILL						0x69

#define	OLED_PUTPIXEL						0x50

#define	OLED_READPIXEL						0x52

#define	OLED_RECTANGLE						0x72

#define	OLED_PAINTAREA						0x70



// Text properties

#define	OLED_SETFONTSIZE					0x46

#define	OLED_FONT5X7					0x01

#define	OLED_FONT8X8					0x02

#define	OLED_FONT8X12					0x03

#define	OLED_TEXTFORMATED					0x54



// OLED Control

#define	OLED_COMMAND_CONTROL					0x59

#define	OLED_COMMAND_DISPLAY					0x01

#define	OLED_COMMAND_CONTRAST					0x02

#define	OLED_COMMAND_POWER					0x03



#define OLED_ACK  0x06  // Ok

#define OLED_NAK  0x15  // Error

#include "Print.h"
#include "WProgram.h"
#include "NewSoftSerial.h"

class Oled
{
private:
  // per object data
  NewSoftSerial *_serial;
  int _resetPin;

public:
    void resetDisplay();
    char getResponse();
    Oled(NewSoftSerial *serial, int resetPin);
    void init();
    int getRGB(int red, int green, int blue);
    void clear();
    void putPixel(char x, char y, int color);
    void drawLine(char x1, char y1, char x2, char y2, int color);
    void drawRectangle(char x, char y, char width, char height, char filled, int color);
    void drawCircle(char x, char y, char radius, char filled, int color);
    void setFontSize(char FontType);
    void drawText(char column, char row, char font_size, char *mytext, int color);
    void drawSingleChar(char column, char row, char font_size, char MyChar, int color);

};

#endif
