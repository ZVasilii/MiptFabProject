#include "common.h"
#include "functions.h"

String strState[NUM_STATES] = {"FIRST ", "SECOND", "THIRD ",
                               "FOURTH", "FIFTH "};
enum PUMP_STATE {ON, OFF};


int currentState = 0;
int pumpState = OFF;

uint32_t pumpMillis = 0;
uint32_t lastMillis = 0;
const uint32_t millisThreshold = 500;
const uint32_t pumpThreshold = 2000;

long weightRaw = 0;
long weight = 0;
long weightThreshold = 600;

void setup() {
  calibrateWeight();
  lcd.init();
  lcd.backlight();// Включаем подсветку дисплея
  lcd.print("BAR MACHINE V1");
  Serial.begin(9600);
  delay(500);
  lcd.clear();
  lcd.print("Calibrated");
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

  if (millis() - lastMillis > millisThreshold)
  {
    weightRaw = getWeightValue();
    //CHANGE TO CALIBRATE
    weight = weightRaw/345;
    //~~~~~~~~~~~~~~~~~~~
    Serial.println( weightRaw);
    Serial.println(weight);
    bool btnClicked = enc.click();
    updateLCD(btnClicked, strState[currentState], weight);
    lastMillis = millis();

    if (btnClicked && pumpState == OFF)
    {
      changeValve(true, 200);
      pumpON();
      pumpState = ON;
      pumpMillis = millis();
    }
  }


  if (pumpState == ON)
  {
    if (weight > weightThreshold)
    {
      pumpOFF();
      pumpState = OFF;
    }
  }

}
