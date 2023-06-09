#include "functions.h"

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
