#include "LM335.h"
#include <math.h>
#define VitesseSerie           115200
#include <VirtualWire.h>
#define pinRadio  2
#define bal     1
#define temp    2
#define move    3
#define lum     4
#define bell    5
#define smoke   6
#define open    7
#define OUI     1
#define NON     0
#define Type    0
#define Numero    1
#define ValeurEnt 2
#define ValeurDec 3
LM335 mTemp(4.46, 0);//supply volts, analog pin
char message[4];
char sensorNum  = 1;

void setup()
{
  Serial.begin(VitesseSerie);
  vw_setup(2000);                // Bits par seconde. (La doc VirtualWire dit que si on l’augmente, la portée diminue. A 9000 ça devient très chaotique, à partir de 10000 le signal n’est plus perçu).
    vw_set_tx_pin(pinRadio);       // La pin 6 sera utilisée pour transmettre
}

void loop()
{
  //Serial.print(mTemp.measureV());
  float temperature = mTemp.measureC();
  int tempPart1 = abs(temperature);
  tempPart1 = (char)tempPart1;
  Serial.println(temperature);
  int tempPart2 = (int)roundf((temperature-(float)tempPart1)*10);
  tempPart2 = (char)tempPart2;
  Serial.print(tempPart1);Serial.print(",");Serial.println(tempPart2);
  
  char message[]={temp,sensorNum,tempPart1,tempPart2};
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx();
  delay(2000);
}






