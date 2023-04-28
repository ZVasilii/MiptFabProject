#include "common.h"
#include "functions.h"

String strState[NUM_STATES] = {"FIRST      ", "SECOND      ", "THIRD       ",
                               "FOURTH     ", "FIFTH       "};
int currentState = 0;
uint16_t lastMillis = 0;
const uint16_t millisThreshHold = 500;

void setup() {
  lcd.init();
  lcd.backlight();// Включаем подсветку дисплея
  lcd.print("BAR MACHINE");
  Serial.begin(9600);
  delay(500);
  lcd.clear();
}

void loop() {
  enc.tick();

  if (enc.turn()) {
    //Serial.println("TURN");
    currentState = changeState(enc.dir(), currentState);
    //Serial.println(currentState);
  }

  if (millis() - lastMillis > millisThreshHold)
  {
    updateLCD(enc.click(), strState[currentState]);
    lastMillis = millis();
  }
}
