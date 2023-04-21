#include "common.h"
#include "functions.h"

void setup()
{
  stp.setSpeed(10);
  pinMode(PIN_RELAY, OUTPUT);

  lcd.init();
  lcd.backlight();// Включаем подсветку дисплея
  lcd.print("Hello, world");
  lcd.setCursor(8, 1);
  lcd.print("LCD 1602");
}

void loop()
{
  lcd.setCursor(0, 1);
  lcd.print(millis()/1000);
  /*
  changeValve(true, 500);
  pumpON();
  delay(500);
  pumpOFF();
  delay(500);
  */
}
