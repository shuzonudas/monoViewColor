#include "monoViewColor.h"


monoViewColor lcd;

void setup() {
  lcd.softwareReset();
  lcd.rotate(1);
  lcd.begin();
  delay(50);

  lcd.setBackColor(0xFF,0xFF,0xFF);
  lcd.fillScreen();

  lcd.setColor(0xFF,0x00,0x00);

  lcd.setCursor(5,5);
  lcd.setTextSize(2);
  lcd.print("<<< RED >>>");

  lcd.setColor(0x00,0xFF,0x00);

  lcd.setCursor(5,35);
  lcd.print("<<< BLUE >>>");

  lcd.setColor(0x00,0x00,0xFF);

  lcd.setCursor(5,65);
  lcd.print("<<< GREEN >>>");

  delay(1000);
  lcd.fillScreen();


  lcd.setColor(0xFF,0xFF,0x00);
  lcd.setCursor(5,30);
  lcd.print("Hi! Harald ");
  delay(500);
  lcd.fillScreen();

  lcd.setCursor(5,5);
  lcd.setTextSize(1);
  lcd.print("Circles");

  for (int i = 0;i<20;i++)
  {
    lcd.drawCircle(80, 64, i * 3);
    //lcd.drawDisplay();
    delay(200);
  }

  lcd.setColor(0xFF,0xFF,0x00);
  lcd.fillScreen();
  lcd.setCursor(5,5);
  lcd.setTextSize(1);
  lcd.print("Lines");

  for (int i = 0;i <= 32;i++)
  {
    lcd.drawLine(0, 0, i * 5, 128);
    delay(20);
  }

  for (int i = 0;i<32;i++)
  {
    lcd.drawLine(i * 5, 128, 160, 0);
    delay(20);
  }

  lcd.setColor(0x00,0xFF,0xFF);
  lcd.fillScreen();
  lcd.setCursor(5,5);
  lcd.setTextSize(1);
  lcd.print("Rectangles");

  for (int i = 0;i<120;i += 6)
  {
    lcd.drawRect(i,i,(160 - i) / 2, (128 - i) / 2);
    delay(20);
  }

  lcd.setColor(0x00,0x80,0xFF);
  lcd.fillScreen();
  lcd.setCursor(5,5);
  lcd.setTextSize(1);
  lcd.print("Rounded Rectangles");

  for (int i = 5;i<100;i += 6)
  {
    lcd.drawRoundRect(80 - i / 2, 64 - i / 2, i, i,5);
    delay(20);
  }

  lcd.fillScreen();

  lcd.setColor(0xFF,0x00,0x00);
  lcd.drawCircle(40,96,4);
  lcd.drawCircle(40,96,8);
  lcd.drawCircle(40,96,16);
  lcd.drawCircle(40,96,24);

  lcd.setColor(0xFF,0xFF,0x00);
  lcd.fillCircle(120,96,24);

  lcd.setColor(0x00,0xFF,0x00);
  lcd.drawRect(8,8,64,48);
  lcd.drawRect(12,12,56,40);
  lcd.drawRect(16,16,48,32);

  lcd.setColor(0x00,0xFF,0xFF);
  lcd.fillRect(96,16,48,32);

}

void loop(){
lcd.displayInverse();
delay(500);
lcd.displayNormal();
delay(500);
}

