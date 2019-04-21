#include "monoViewColor.h"


monoViewColor lcd;

int brightness = 125;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

char buffer[50]; 
void setup() {
  lcd.softwareReset();
  lcd.rotate(1);
  lcd.begin();
  delay(50);

  lcd.setBackColor(0x00,0x00,0x00);
  lcd.fillScreen();

  lcd.setColor(0xFF,0xFF,0xFF);
  lcd.fillCircle(26,64,13);

  lcd.setColor(0xFF,0x00,0x00);
  lcd.fillCircle(62,64,13);

  lcd.setColor(0x00,0xFF,0x00);
  lcd.fillCircle(98,64,13);

  lcd.setColor(0x00,0x00,0xFF);
  lcd.fillCircle(134,64,13);

  lcd.setColor(0xFF,0xFF,0xFF);

}

void loop(){

  lcd.setCursor(5,5);
  lcd.setTextSize(2);
  sprintf(buffer,"Backlight:%.3d",brightness);
  lcd.print(buffer);

  lcd.backlight(brightness);
  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(30);
}

