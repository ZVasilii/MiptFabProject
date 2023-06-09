#include "functions.h"

bool createVodka()
{
  if (currentValve != 0)
    changeValveR();
  pumpON();
  waitForGramms(20);
  pumpOFF();
  return true;
}

bool createJuice()
{
  if (currentValve != 1)
    changeValveL();
  pumpON();
  waitForGramms(50);
  pumpOFF();
  return true;
}

bool createScrewdriver()
{
  if (currentValve != 0)
    changeValveR();
  //Vodka
  pumpON();
  waitForGramms(20);
  pumpOFF();
  changeValveL();
  //Juice
  pumpON();
  waitForGramms(50);
  pumpOFF();
  return true;
}
