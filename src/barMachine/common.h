#ifndef _COMMON_HEADER_H
#define _COMMON_HEADER_H

#include <Stepper.h>
#include <LiquidCrystal_I2C.h>
#include <EncButton2.h>
#include <GyverHX711.h>
#include <Servo.h>


//const char PIN_STP[4] = {8, 10, 9, 11};
//const char PIN_BTTN = 2;
const char PIN_WEIGHT_DATA = 6;
const char PIN_WEIGHT_SCK = 5;
const int PIN_RELAY = 12;
const int PIN_SERVO = 7;
const int PIN_DIODE = 13;
const char PIN_STP[4] = {8, 10, 9, 11};
const char PIN_ENC[3] = {2, 3, 4};
const int TMP_DELAY = 4000;
const int NUM_STATES = 3;
const int SERVICE_DELAY = 200;
const int FULL_REVOLUTION = 2048;
const int ONE_STEP = 980;
const int SERVO_DEFAULT = 0;
const int SERVO_ATTACHED = 75;
const int WEIGHT_FACTOR = 375;
#endif
