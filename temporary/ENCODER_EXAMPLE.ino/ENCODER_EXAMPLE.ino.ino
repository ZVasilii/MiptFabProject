#include <EncButton2.h>
#include <Stepper.h>
#include <Servo.h>

const int TMP_DELAY = 4000;
const int SERVICE_DELAY = 200;
const int FULL_REVOLUTION = 2048;
const int ONE_STEP = 980;
const int PIN_RELAY = 5;
const int PIN_SERVO = 3;
const int PIN_DIODE = 12;
const char PIN_STP[4] = {8, 10, 9, 11};
const char SERVO_DEFAULT = 0;
const char SERVO_ATTACHED = 80;

Servo srv;
Stepper stp(FULL_REVOLUTION, PIN_STP[0], PIN_STP[1], PIN_STP[2],PIN_STP[3]);
EncButton2<EB_BTN> btn1(INPUT, 0); 
EncButton2<EB_BTN> btn2(INPUT, 1); 
EncButton2<EB_BTN> btn3(INPUT, 2);
EncButton2<EB_BTN> btn4(INPUT, 4);

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

void setup() 
{
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_DIODE, OUTPUT);
  stp.setSpeed(10);
  Serial.begin(9600);
  srv.attach(PIN_SERVO);
  srv.write(SERVO_DEFAULT);
}

void loop() {
  btn1.tick();
  btn2.tick();
  btn3.tick();
  btn4.tick();
  // Rotate CW slowly at 5 RPM
  if (btn1.click())
  {
    Serial.println("Vodka");
    //changeValve(true, ONE_STEP);
    if(createVodka())
      finishedCreating();
  }
  
  else if (btn2.click())
  {
    Serial.println("Juice");
    //changeValve(false, ONE_STEP);
    if(createJuice())
      finishedCreating();
  }

  /*
  if (btn3.press())
  {
    Serial.println("3");
    //srv.write(SERVO_ATTACHED);
    //pumpON();
    
    
  }
  if (btn3.release())
  {
    //srv.write(SERVO_DEFAULT);
    pumpOFF();
  }
  */
  else if (btn3.click())
  {
    Serial.println("Screwdriver");
    if(createScrewdriver())
      finishedCreating();
  }
  

  else if (btn4.press())
  {
    #ifdef DEBUG
      Serial.println("4 pressed");
    #endif
    srv.write(80);
  }
  else if (btn4.release())
  {
    #ifdef DEBUG
      Serial.println("4 released");
    #endif
    srv.write(0);
  }
}

bool createVodka()
{
  if (currentValve != 0)
    changeValveR();
  pumpON();
  delay(TMP_DELAY);
  pumpOFF();
  return true; 
}

bool createJuice()
{
  if (currentValve != 1)
    changeValveL();
  pumpON();
  delay(TMP_DELAY);
  pumpOFF();
  return true; 
}

bool createScrewdriver()
{
  if (currentValve != 0)
    changeValveR();
  //Vodka
  pumpON();
  delay(TMP_DELAY);
  pumpOFF();
  changeValveL();
  //Juice
  pumpON();
  delay(TMP_DELAY);
  pumpOFF();
  return true; 
}
