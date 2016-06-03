#include "LM335.h"

LM335 mTemp(4.46, 0);//supply volts, analog pin

void setup()
{
  Serial.begin(115200);
}
void loop()
{
  Serial.print(mTemp.measureV());
  Serial.println(" volts");
  Serial.println("Temperatures: ");
  Serial.print("Celsius: ");
  Serial.println(mTemp.measureC());
  delay(1000);
}
