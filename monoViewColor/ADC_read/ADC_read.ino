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
  lcd.setTextSize(1);
}

int adc=0;
char numberBuffer[30];

void loop() {

adc = analogRead(2);
sprintf(numberBuffer,"ADC A2:%.4d",adc);
lcd.setCursor(5,5);
lcd.print(numberBuffer);
delay(10);

adc = analogRead(3);
sprintf(numberBuffer,"ADC A3:%.4d",adc);
lcd.setCursor(5,15);
lcd.print(numberBuffer);
delay(10);

adc = analogRead(4);
sprintf(numberBuffer,"SCA A4:%.4d",adc);
lcd.setCursor(5,25);
lcd.print(numberBuffer);
delay(10);

adc = analogRead(5);
sprintf(numberBuffer,"SCL A5:%.4d",adc);
lcd.setCursor(5,35);
lcd.print(numberBuffer);
delay(10);

adc = analogRead(6);
sprintf(numberBuffer,"ADC A6:%.4d",adc);
lcd.setCursor(5,45);
lcd.print(numberBuffer);
delay(10);

adc = analogRead(7);

sprintf(numberBuffer,"ADC A7:%.4d",adc);
lcd.setCursor(5,55);
lcd.print(numberBuffer);
delay(10);

}
