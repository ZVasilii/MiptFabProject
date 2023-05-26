#ifndef _COMMON_HEADER_H
#define _COMMON_HEADER_H

#include <Stepper.h>
#include <LiquidCrystal_I2C.h>
#include <EncButton2.h>
#include <GyverHX711.h>


const char PIN_RELAY = 13;
const int stepsPerRevolution = 2048;
const char PIN_STP[4] = {8, 9, 10, 11};
const char PIN_ENC[3] = {2, 3, 4};
const char PIN_BTTN = 2;
const char NUM_STATES = 5;
const char PIN_WEIGHT_DATA = 6;
const char PIN_WEIGHT_SCK = 5;
const char PIN_BUZZER = 12;
#endif
