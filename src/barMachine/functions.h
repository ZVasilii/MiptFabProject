#ifndef _CUSTOM_FUNCTIONS_H
#define _CUSTOM_FUNCTIONS_H
#include "common.h"


Servo srv;
Stepper stp(FULL_REVOLUTION, PIN_STP[0], PIN_STP[1], PIN_STP[2],PIN_STP[3]);
LiquidCrystal_I2C lcd(0x27,16,2);
EncButton2<EB_ENCBTN> enc(INPUT, PIN_ENC[0], PIN_ENC[1], PIN_ENC[2]);
GyverHX711 weigthSensor(PIN_WEIGHT_DATA, PIN_WEIGHT_SCK, HX_GAIN64_A);

int currentValve = 0;

bool createVodka();
bool createScrewdriver();
bool createJuice();
void changeValve(bool clockwise, int step_); //True -> 0, False -> N
void pumpON();
void pumpOFF();
void changeValveR();
void changeValveL();
void finishedCreating();
void serviceDelay();
int changeState(int direction, int currentState);
void updateLCD(bool click, const String& state, long weight);
void calibrateWeight();
long getWeightValue();

void finishedCreating()
{
   Serial.println("FINISHED!");
}

void serviceDelay()
{
  delay(SERVICE_DELAY);
}
void changeValveR()
{
  changeValve(true, ONE_STEP);
}

void changeValveL()
{
  changeValve(false, ONE_STEP);
}

void changeValve(bool clockwise, int step_)
{
  if (clockwise)
  {
    stp.step(step_);
    currentValve--;
    #ifdef DEBUG
      Serial.println(String("CurrentValve ") + String(currentValve));
    #endif
  }
  else
  {
    stp.step(-step_);
    currentValve++;
    #ifdef DEBUG
      Serial.println(String("CurrentValve ") + String(currentValve));
    #endif
  }
}

void pumpON()
{
  srv.write(SERVO_ATTACHED);
  digitalWrite(PIN_RELAY, HIGH);
  digitalWrite(PIN_DIODE, HIGH);
}

void pumpOFF()
{
  srv.write(SERVO_DEFAULT);
  digitalWrite(PIN_RELAY, LOW);
  digitalWrite(PIN_DIODE, LOW);
  serviceDelay();
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

void updateLCD(bool click, const String& state, long weight)
{
  lcd.setCursor(0, 0);
  lcd.print(String("     "));
  lcd.setCursor(0, 0);
  lcd.print(String(weight));
  lcd.setCursor(5, 0);
  lcd.print(String(" " + state));
  lcd.setCursor(0, 1);
  if (click)
    lcd.print(String("START!        "));
  else
    lcd.print("Press button!");
}

//WARNING! DELAY INSIDE FOR CALIBRATION
void calibrateWeight()
{
  delay(500);
  weigthSensor.tare();
}

long getWeightValue()
{
  if (weigthSensor.available())
    return weigthSensor.read();
  else
    return 0l;
}

#endif
