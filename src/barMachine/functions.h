#ifndef _CUSTOM_FUNCTIONS_H
#define _CUSTOM_FUNCTIONS_H
#include "common.h"


Stepper stp(stepsPerRevolution, PIN_STP[0], PIN_STP[1], PIN_STP[2],PIN_STP[3]);
LiquidCrystal_I2C lcd(0x27,16,2);

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
#endif
