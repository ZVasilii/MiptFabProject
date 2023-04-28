#ifndef _CUSTOM_FUNCTIONS_H
#define _CUSTOM_FUNCTIONS_H
#include "common.h"


Stepper stp(stepsPerRevolution, PIN_STP[0], PIN_STP[1], PIN_STP[2],PIN_STP[3]);
LiquidCrystal_I2C lcd(0x27,16,2);
EncButton2<EB_ENCBTN> enc(INPUT, PIN_ENC[0], PIN_ENC[1], PIN_ENC[2]);


void pumpON()
{
  digitalWrite(PIN_RELAY, HIGH);
}

void pumpOFF()
{
  digitalWrite(PIN_RELAY, LOW);
}

void changeValve(bool clockwise, int step)
{
  if (clockwise)
  {
    stp.step(step);
  }
  else
  {
    stp.step(-step);
  }
}

int changeState(int direction, int currentState)
{
  int newState = 0;
  if (direction == 1)
  {
    newState = (currentState == NUM_STATES - 1) ? 0 : ++currentState;
  }
  if (direction == -1)
  {
    newState = (currentState == 0) ? NUM_STATES - 1 : --currentState;
  }
  return newState;
}

void updateLCD(bool click, const String& state)
{
  lcd.setCursor(0, 0);
  lcd.print(state);
  lcd.setCursor(0, 1);
  if (click)
    lcd.print("START!        ");
  else
    lcd.print("Press button!");
}

#endif
