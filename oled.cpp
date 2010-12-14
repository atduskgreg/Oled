#include "oled.h"

Oled::Oled(NewSoftSerial *serial, int resetPin){
    _serial = serial;
    _resetPin = resetPin;
}


// Initialise OLED display. You must first activate a _serial comunication!

void Oled::init()

{

  // First reset display
  resetDisplay();  

  delay(OLED_INITDELAYMS);                       // Wait for init

  // Autodetect baudrate

  _serial->print(OLED_DETECT_BAUDRATE, BYTE); 

  getResponse(); 



}


void Oled::resetDisplay()

{

  digitalWrite(_resetPin, LOW);

  delay(20);                  

  digitalWrite(_resetPin, HIGH);

  delay(20);  



}



char Oled::getResponse()

{

  byte incomingByte = OLED_ACK;



  // Wait for data avaliable

  while (!_serial->available()) { 
    delay(1); 
  }



  // Read incoming byte

  incomingByte = _serial->read();



  return incomingByte;

}






// Get 16bits value from RGB (0 to 63, 565 format)

int Oled::getRGB(int red, int green, int blue)

{



  char text[255];



  int outR = ((red * 31) / 255);

  int outG = ((green * 63) / 255);

  int outB = ((blue * 31) / 255);



  return (outR << 11) | (outG << 5) | outB;

}



void Oled::clear()

{



  _serial->print(OLED_CLEAR, BYTE); // Pixel write

  delay(20);

  getResponse();



}



void Oled::putPixel(char x, char y, int color)

{



  // Putpixel

  _serial->print(OLED_PUTPIXEL, BYTE); // Pixel write

  _serial->print(x, BYTE);	// x

  _serial->print(y, BYTE);



  // Color

  _serial->print(color >> 8, BYTE);		// MSB			

  _serial->print(color & 0xFF, BYTE);		// LSB



  getResponse();



}



void Oled::drawLine(char x1, char y1, char x2, char y2, int color)

{



  // Line drawing

  _serial->print(OLED_LINE, BYTE); // Line



  _serial->print(x1, BYTE);	// x1

  _serial->print(y1, BYTE);		// y1

  _serial->print(x2, BYTE);	// x2

  _serial->print(y2, BYTE);		// y2



  // Color

  _serial->print(color >> 8, BYTE);		// MSB			

  _serial->print(color & 0xFF, BYTE);		// LSB



  getResponse();



}



void Oled::drawRectangle(char x, char y, char width, char height, char filled, int color)

{



  //int color = 0xFFFF;



  // Rectangle drawing

  _serial->print(OLED_RECTANGLE, BYTE); 



  _serial->print(x, BYTE);			// x1

  _serial->print(y, BYTE);		// y1



  _serial->print(x+width, BYTE);		// x2

  _serial->print(y+height, BYTE);		// y1



  // Color

  _serial->print(color >> 8, BYTE);		// MSB			

  _serial->print(color & 0xFF, BYTE);		// LSB

  /*

   	if (filled == 1) { _serial->print(0x01); }	// Filled
   
   	else { _serial->print(0x00); }				// Outline
   
   	*/

  getResponse();

}



void Oled::drawCircle(char x, char y, char radius, char filled, int color)

{

  _serial->print(OLED_CIRCLE, BYTE); 



  _serial->print(x, BYTE);	// x

  _serial->print(y, BYTE);	// y

  _serial->print(radius, BYTE);	// radius



  // Color

  _serial->print(color >> 8, BYTE);		// MSB			

  _serial->print(color & 0xFF, BYTE);		// LSB



  getResponse();



}



/*

 Change font format:
 
 FontType can be:
 
 OLED_FONT5X7
 
 OLED_FONT8X8
 
 OLED_FONT8X12
 
 */

void Oled::setFontSize(char FontType)

{

  _serial->print(OLED_SETFONTSIZE, BYTE);

  _serial->print(FontType, BYTE);



  getResponse();

}



void Oled::drawText(char column, char row, char font_size, char *mytext, int color)

{

  //char mytext[] = "Arkanoid by pK";



  _serial->print(0x73, BYTE); // s (Formated text)



  //_serial->print(column); // column



  // Adjust to center of the screen (26 Columns at font size 0)

  int newCol = 13 - (strlen(mytext)/2);

  //_serial->print(newCol); // column

  _serial->print(column, BYTE); // column



  _serial->print(row, BYTE); // row

  _serial->print(font_size, BYTE); // font size (0 = 5x7 font, 1 = 8x8 font, 2 = 8x12 font)



  // Color

  _serial->print(color >> 8, BYTE);		// MSB			

  _serial->print(color & 0xFF, BYTE);		// LSB



  for (int i=0 ; i<strlen(mytext) ; i++)

  {

    _serial->print(mytext[i], BYTE); // character to write

  }

  _serial->print(0x00, BYTE); // string terminator (always 0x00)



  getResponse();



}



void Oled::drawSingleChar(char column, char row, char font_size, char MyChar, int color)

{



  _serial->print(OLED_TEXTFORMATED, BYTE); // T (Formated)



  _serial->print(MyChar, BYTE);

  _serial->print(column, BYTE);

  _serial->print(row, BYTE);



  // Color

  _serial->print(color >> 8, BYTE);		// MSB			

  _serial->print(color & 0xFF, BYTE);	// LSB



  getResponse();



}



