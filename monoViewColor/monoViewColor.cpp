/*
  Written by Mohammed Rezwanul Islam
*/

#include "Arduino.h"
#include "monoViewColor.h"

monoViewColor::monoViewColor(void)

{

	 _SCKPin = 15;
	 _CSPin = 7;
	 _SDAPin = 14;

   //set pin directions
  pinMode(_CSPin, OUTPUT);
  pinMode(_SDAPin, OUTPUT);
  pinMode(_SCKPin, OUTPUT);

  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
 
  //disable monoViewColor to start with 
  digitalWrite(_CSPin, HIGH);
  digitalWrite(_SDAPin, LOW);
  digitalWrite(_SCKPin, LOW);

  

 }
 

void monoViewColor::backlight(byte bklt)
{
analogWrite(6, bklt);
}
 




void monoViewColor::command(byte payload)
{

  //select monoPro
  //  digitalWrite(_CSPin, LOW);
  cbi(PORTD, 0x07);

  //write data/command bit
  //0=command & 1= data
  cbi(PORTC, 0x00);

  //digitalWrite(_SCKPin, HIGH);
  sbi(PORTC, 0x01);
  //digitalWrite(_SCKPin, LOW);
  cbi(PORTC, 0x01);

  //write payload 8 bits
  for (int i = 7; i >= 0; i--)
  {
    if (((payload >> i) & 1) == 1)
    {
      sbi(PORTC, 0x00);
    }
    else
    {
      cbi(PORTC, 0x00);
    }
    //toggle clock
    sbi(PORTC, 0x01);
    cbi(PORTC, 0x01);
  }

  //  digitalWrite(_CSPin, HIGH);
  sbi(PORTD, 0x07);
}


void monoViewColor::data(byte payload)
{
  //select monoPro
  //  digitalWrite(_CSPin, LOW);
  cbi(PORTD, 0x07);

  //write data/command bit
  //0=command & 1= data
  sbi(PORTC, 0x00);

  //digitalWrite(_SCKPin, HIGH);
  sbi(PORTC, 0x01);
  //digitalWrite(_SCKPin, LOW);
  cbi(PORTC, 0x01);

  //write payload 8 bits
  for (int i = 7; i >= 0; i--)
  {
    if (((payload >> i) & 1) == 1)
    {
      sbi(PORTC, 0x00);
    }
    else
    {
      cbi(PORTC, 0x00);
    }
    //toggle clock
    sbi(PORTC, 0x01);
    cbi(PORTC, 0x01);
  }
}


void monoViewColor::begin()
{

  monoViewColor::command(0x01);
  delay(12);
  monoViewColor::command(0x11);
  delay(50);
  monoViewColor::command(0x29);
  delay(50);

  // color mode 16bit
  monoViewColor::command(0x3A);
  monoViewColor::data(0x06);

  // set column
  monoViewColor::command(0x2A);
  monoViewColor::data(0x00);
  monoViewColor::data(0x02);
  monoViewColor::data(0x00);
  monoViewColor::data(0x81);

  // set row
  monoViewColor::command(0x2B);
  monoViewColor::data(0x00);
  monoViewColor::data(0x01);
  monoViewColor::data(0x00);
  monoViewColor::data(0xA0);
}


void monoViewColor:: fillScreen(void)
{
  // set column
command(0x2A);
data(0x00);
data(0x01);
data(0x00);

if(_LCD_x==128)
{data(0x81);}
else
{data(0xA0);}

// set row
command(0x2B);
data(0x00);
data(0x01);
data(0x00);
data(0xA0);


command(0x2C);
  
int i=0;
for(i=0;i<20800;i++)
{
  data(_setBackColorRed);
  data(_setBackColorGreen);
  data(_setBackColorBlue);
}

command(0x00);

}

void monoViewColor::setBackColor( uint8_t red, uint8_t green, uint8_t blue)
{
  _setBackColorRed = red;
  _setBackColorGreen = green;
  _setBackColorBlue = blue;
}

void monoViewColor::setColor( uint8_t red, uint8_t green, uint8_t blue)
{
 _textColorRed=red;
 _textColorBlue=green;
 _textColorGreen=blue;
}

void monoViewColor::setAddrWindow(uint8_t x0, uint8_t y0, uint8_t x1,uint8_t y1)

{
  command(0x2A); // Column addr set
  data(0x00);
  data(x0);     // XSTART 
  data(0x00);
  data(x1);     // XEND

  command(0x2B); // Row addr set
  data(0x00);
  data(y0);     // YSTART
  data(0x00);
  data(y1);     // YEND

  command(0x2C); // write to RAM
}


void monoViewColor::drawPixel(int16_t x, int16_t y)
{
  drawPixel(x,y, _textColorRed,_textColorGreen,_textColorBlue);
}

void monoViewColor::drawPixel(int16_t x, int16_t y, uint8_t red,uint8_t green,uint8_t blue)
{

  setAddrWindow(x,y,x+1,y+1);
  data(red);
  data(green);
  data(blue);
}

// Bresenham's algorithm - thx wikpedia
void monoViewColor::drawLine(int16_t x0, int16_t y0,int16_t x1, int16_t y1)
{
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      drawPixel(y0, x0);
    } else {
      drawPixel(x0, y0);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}

void monoViewColor::drawFastVLine(int16_t x, int16_t y,int16_t h) 
{
  drawLine(x, y, x, y+h-1);
}

void monoViewColor::drawFastHLine(int16_t x, int16_t y,int16_t w) 
{
  drawLine(x, y, x+w-1, y);
}

void monoViewColor::drawRect(int16_t x, int16_t y,int16_t w, int16_t h)
{
  drawFastHLine(x, y, w);
  drawFastHLine(x, y+h-1, w);
  drawFastVLine(x, y, h);
  drawFastVLine(x+w-1, y, h);
}

void monoViewColor::fillRect(int16_t x, int16_t y, int16_t w, int16_t h) 
{
  for (int16_t i=x; i<x+w; i++) 
  {
    drawFastVLine(i, y, h);
  }
}

void  monoViewColor::drawCircle(int16_t x0, int16_t y0, int16_t r) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  drawPixel(x0  , y0+r);
  drawPixel(x0  , y0-r);
  drawPixel(x0+r, y0);
  drawPixel(x0-r, y0);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    drawPixel(x0 + x, y0 + y);
    drawPixel(x0 - x, y0 + y );
    drawPixel(x0 + x, y0 - y );
    drawPixel(x0 - x, y0 - y );
    drawPixel(x0 + y, y0 + x );
    drawPixel(x0 - y, y0 + x );
    drawPixel(x0 + y, y0 - x );
    drawPixel(x0 - y, y0 - x );
  }
}

void monoViewColor::drawCircleHelper( int16_t x0, int16_t y0,int16_t r, uint8_t cornername) {
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      drawPixel(x0 + x, y0 + y );
      drawPixel(x0 + y, y0 + x );
    } 
    if (cornername & 0x2) {
      drawPixel(x0 + x, y0 - y );
      drawPixel(x0 + y, y0 - x );
    }
    if (cornername & 0x8) {
      drawPixel(x0 - y, y0 + x );
      drawPixel(x0 - x, y0 + y );
    }
    if (cornername & 0x1) {
      drawPixel(x0 - y, y0 - x );
      drawPixel(x0 - x, y0 - y );
    }
  }
}

void monoViewColor::drawRoundRect(int16_t x, int16_t y, int16_t w,
  int16_t h, int16_t r) {
  // smarter version
  drawFastHLine(x+r  , y    , w-2*r ); // Top
  drawFastHLine(x+r  , y+h-1, w-2*r ); // Bottom
  drawFastVLine(x    , y+r  , h-2*r ); // Left
  drawFastVLine(x+w-1, y+r  , h-2*r ); // Right
  // draw four corners
  drawCircleHelper(x+r    , y+r    , r, 1 );
  drawCircleHelper(x+w-r-1, y+r    , r, 2 );
  drawCircleHelper(x+w-r-1, y+h-r-1, r, 4 );
  drawCircleHelper(x+r    , y+h-r-1, r, 8 );
}


void monoViewColor::fillCircleHelper(int16_t x0, int16_t y0, int16_t r,uint8_t cornername, int16_t delta)
{
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      drawFastVLine(x0+x, y0-y, 2*y+1+delta);
      drawFastVLine(x0+y, y0-x, 2*x+1+delta);
    }
    if (cornername & 0x2) {
      drawFastVLine(x0-x, y0-y, 2*y+1+delta);
      drawFastVLine(x0-y, y0-x, 2*x+1+delta);
    }
  }
}

void monoViewColor::fillRoundRect(int16_t x, int16_t y, int16_t w,
				 int16_t h, int16_t r) {
  // smarter version
  fillRect(x+r, y, w-2*r, h );

  // draw four corners
  fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1 );
  fillCircleHelper(x+r    , y+r, r, 2, h-2*r-1 );
}

void monoViewColor::fillCircle(int16_t x0, int16_t y0, int16_t r)
{
  drawFastVLine(x0, y0-r, 2*r+1);
  fillCircleHelper(x0, y0, r, 3, 0);
}

void monoViewColor::setTextSize(uint8_t x)
{
  _fontSize = x;
  if (x <1) {  _fontSize = 1;}
}

void monoViewColor::setCursor( uint8_t x,uint8_t y)
{
  _x_pos=x;
  _y_pos=y;
}

void monoViewColor::drawFontPixel(uint8_t x, uint8_t y, uint8_t red,uint8_t green,uint8_t blue,uint8_t pixelSize)
{
  setAddrWindow(x,y,x+pixelSize-1,y+pixelSize-1);
 for (uint8_t i=0;i<pixelSize*pixelSize ;i++)
 {
   data(red);
   data(green);
   data(blue);
 }
}

void monoViewColor::character(char character)
{
  if(_x_pos < _fontSize)  {_x_pos =  _fontSize;}

for (uint8_t i=0;i<5 ;i++)
{
for (uint8_t j=0;j<8 ;j++)
{  
byte myByte=0;
myByte = pgm_read_byte(&(ASCII[(byte)character - 0x20][i]));

  if(((myByte >> j)  & 0b00000001) == 0b00000001) 

  {// draw font color
  drawFontPixel(_x_pos,_y_pos,_textColorRed,_textColorGreen,_textColorBlue,_fontSize);}
  else
  {//draw back color
  drawFontPixel(_x_pos,_y_pos,_setBackColorRed,_setBackColorGreen,_setBackColorBlue,_fontSize);}

  _y_pos = _y_pos + _fontSize;
  }
  _y_pos = _y_pos - _fontSize*8;
  _x_pos = _x_pos + _fontSize;

}
_x_pos = _x_pos + _fontSize;

if(_x_pos > _LCD_x)
  {
    _x_pos=1+_fontSize;
    _y_pos = _y_pos +_fontSize*8;
  }
}


void monoViewColor::print(char *characters)
{
  while (*characters)
  {
    character(*characters++);
  }
}

void monoViewColor::println(char *characters)
{
 _x_pos=_fontSize;
// _y_pos= _fontSize;
  while (*characters)
  {
    character(*characters++);
  }
_y_pos=_y_pos + 8* _fontSize;
}


void monoViewColor::rotate( byte _rotation){
command(0x36);
switch (_rotation) {
   case 0:
      data(MADCTL_MX | MADCTL_MY | MADCTL_RGB);
      _LCD_x=128;
      break;
   case 1:
      data(MADCTL_MY | MADCTL_MV | MADCTL_RGB);
      _LCD_x=157;
      break;
  case 2:
       data(MADCTL_RGB);
       _LCD_x=128;
       break;
  case 3:
      data(MADCTL_MX | MADCTL_MV | MADCTL_RGB);
      _LCD_x=157;
      break;
     }
  command(0x2C);
}

void monoViewColor::displayOff(){
  command(0x28);
}

void monoViewColor::displayOn(){
  command(0x29);
}


void monoViewColor::displayInverse(){
  command(0x21);
}

void monoViewColor::displayNormal(){
  command(0x20);
}

void monoViewColor::softwareReset(){
  command(0x01);
  delay(12);
}

void  monoViewColor::sleep_IN(){
  command(0x10);
}
void  monoViewColor::sleep_OUT(){
  command(0x11);
}