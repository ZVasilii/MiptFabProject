#include "recipies.h"

enum State {VODKA, JUICE, SCREW};
String strState[NUM_STATES] = {"VODKA",  "JUICE ", "SCREW "};
enum PUMP_STATE {ON, OFF};


int currentState = 0;
int pumpState = OFF;

const uint32_t millisThreshold = 500;
uint32_t lastMillis = 0;

long weightRaw = 0;
long weight = 0;

void setup() {
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_DIODE, OUTPUT);
  stp.setSpeed(10);
  Serial.begin(9600);
  srv.attach(PIN_SERVO);
  srv.write(SERVO_DEFAULT);

  calibrateWeight();
  lcd.init();
  lcd.backlight();// Включаем подсветку дисплея
  lcd.print("BAR MACHINE V1");
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
    if (btnClicked)
    {
      switch (currentState)
      {
        case State::VODKA:
          createVodka();
          break;
        case State::JUICE:
          createJuice();
          break;
        case State::SCREW:
          createScrewdriver();
          break;
      }
    }
    updateLCD(btnClicked, strState[currentState], weight);
    lastMillis = millis();
  }
}
