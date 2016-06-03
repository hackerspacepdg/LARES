#ifndef Morse_h
#define Morse_h
#include "Arduino.h"
#endif

class LM335
{
  float cal;
  int pin;
  public:
  LM335(float mCal, int mPin);
  float measureV();
  float measureK();
  float measureC();
  float measureF();
  float measureRankine();
};

LM335::LM335(float mCal, int mPin)
{
  cal = mCal;
  pin = mPin;
}
float LM335::measureV()
{
  float retVal = (float) analogRead(pin);
  retVal = (retVal*cal)/1024.0;
  return retVal;
}
float LM335::measureK()
{
  return measureV()/0.01;//10mV/k
}
float LM335::measureC()
{
  return (measureV()/0.01)-273.15;
}
float LM335::measureF()
{
  return (((measureV()/0.01)-273.15)*1.8)+32;
}
float LM335::measureRankine()
{
  return measureF() + 458.67;
}
