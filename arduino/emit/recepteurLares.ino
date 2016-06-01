#include <VirtualWire.h>
#define pinRadio	2
#define bal			1
#define temp 		2
#define	move 		3
#define	lum			4
#define	bell		5
#define	smoke		6
#define	open		7
#define OUI			1
#define	NON			0
#define Type		0
#define Numero		1
#define ValeurEnt	2
#define ValeurDec	3
/*
messages :  "type d'objet:numero:information"

types	: données
temp 	: xxx°
bal 	: 1
move 	: 1
lum    	: 1 / 0
bell	: 1
smoke	: 1
open	: 1 / 0

exemple:
"bal:1:1:0"
*/

void setup()
{
    Serial.begin(9600);
    Serial.println("setup");
    vw_setup(2000);
	vw_set_rx_pin(pinRadio);
    vw_rx_start();
}

char message[4];

void loop()
{
	uint8_t buf[4];
    uint8_t buflen = 4;
	// un uint_8 fait un octet
	// un float en fait 4
	
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
		int i;

        //digitalWrite(13, true); // Flash a light to show received good message
		// Message with a good checksum received, dump it.
		Serial.print("Got: ");
		
		for (i = 0; i < buflen; i++)
		{
			//Serial.print(buf[i], HEX);
			//Serial.print(" ");
			message[i]=buf[i];
			Serial.println(message[i]);
		}
		//Serial.println("");
		
		sendToPi();
		resetMessage();
    }
	
	
}

void sendToPi()
{
	//I2C
	switch(message[Type])
	{
		case temp:
			//char numero = message[Numero];
			//char valeure = message[ValeurEnt];
			//char dec = message[ValeurDec];
			printMessage("temperature!");
			break;
		case bal:
			printMessage("BAL");
			break;
		case move:
			printMessage("MOVE");
			break;
		case lum:
			printMessage("LUM");
			break;
		case bell:
			printMessage("BELL");
			break;
		case smoke:
			printMessage("SMOKE");
			break;
		case open:
			printMessage("OPEN");
			break;
	}
}
	
void resetMessage()
{
	for (int i =0; i< 4;i++)
	{
		message[i]=0;
	}
}
	
void printMessage(char type[])
{
	Serial.print(type);
	Serial.println(" :");
	Serial.print("- numero : ");
	Serial.println(message[Numero]);
	Serial.print("- valeure : ");
	Serial.print(message[ValeurEnt]);
	Serial.print(".");
	Serial.println(message[ValeurDec]);
}