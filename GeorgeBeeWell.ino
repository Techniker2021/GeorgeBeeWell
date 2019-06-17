/*
 Name:		GeorgeBeeWell.ino
 Created:	01.05.2019 16:08:58
 Author:	Burkhard, Dario

 Notes: TTN = TheThingsNetwork https://www.thethingsnetwork.org/
		
*/

#include <MKRWAN.h>
#include <BeeHive.h> 

BeeHive BurkhardsBienen = BeeHive();
LoRaModem modem(SerialLoRa);

const char* appEui = "YOUR-APP-EUI";			//ID-Number of TTN-Application
const char* appKey = "YOUR-APP-KEY";			//Burkhard MKRWAN 1300

bool modemBeginState = false;					//debug for LoRa-Modem-Start
bool OTAAState = false;							//debug state for OTAA (Over-The-Air-Authentication)
bool msgSend = false;							//debug state for Message sent
bool loopCheck = false;							//debug state for Loop

String tempString = "void";						//Temp-String to save values

int intervalle[] = { 60000 };					//Time-intervals: 1 minute      
unsigned long lastTime[1];						//variable to save last time aktivation of time-interval

void setup() {
	Serial.begin(9600);                         //starts Serial to USB communication
	SERIAL_PORT_HARDWARE.begin(9600);           //starts Serial to OpenScale communication

	while (!SERIAL_PORT_HARDWARE);				//Wait for OpenScale communication to start		

	connectToTTN();								//Connect to TTN

	Serial.println("Setup complete");
	Serial.println();
}

void loop() {
	if (loopCheck == false)
	{
		loopCheck = true;
		Serial.println("Start Loop");
		Serial.println();
	}

	if (Serial.available()) // If anything comes in Serial (USB), pass it on to OpenScale
	{
		SERIAL_PORT_HARDWARE.write(Serial.read());   // read USB-Serial and send it out to SERIAL_PORT_HARDWARE (pins 13 & 14)
	}

	if (SERIAL_PORT_HARDWARE.available()) // If anything comes in SERIAL_PORT_HARDWARE (pins 13 & 14)
	{
		BurkhardsBienen.setOpenscale(SERIAL_PORT_HARDWARE.readStringUntil('\n'));	//Read until next line and save value to String
		//BurkhardsBienen.setWeight(tempString.toDouble());			//Convert string to double and save as beehive-property
	}

	if (zeitAbfrage(0))		//if time interval is over check LoRa-State and send Data
	{
		sendData();			//send data to TTN
	}
}

void connectToTTN()		//Method to connect to TTN
{
	/*
	Start LoRa-TTN-Modem in EU868-Band (Standard-DataRate: 5)

	DataRate 	Modulation 	SF 	BW 		bit/s
	0 			LoRa 		12 	125 	250
	1 			LoRa 		11 	125 	440
	2 			LoRa 		10 	125 	980
	3 			LoRa 		9 	125 	1'760
	4 			LoRa 		8 	125 	3'125
-->	5 			LoRa 		7 	125 	5'470
	6 			LoRa 		7 	250 	11'000
	*/

	Serial.println("Start LoRa-Modem");
	modemBeginState = modem.begin(EU868);		//start LoRa modem in specified band
	Serial.print("LoRa-Modem state: ");
	Serial.println(modemBeginState);

	Serial.println("Start of OTAA-request");
	OTAAState = modem.joinOTAA(appEui, appKey);	//request Over-The-Air-Authentication from TTN-Network
	Serial.print("OTAA-Return-Value: ");
	Serial.println(OTAAState);
	return;
}

void sendData()		//Method to check LoRa state and send data to TTN
{
	if (!modemBeginState || !OTAAState)	//Check if LoRa-Modem start & OTAA was correct last time, if not, try again
	{
		connectToTTN();
	}

	if (modemBeginState && OTAAState)	//if connection to TTN was successful at least once, send message
	{
		modem.beginPacket();
		modem.println(BurkhardsBienen.getOpenscale());		//get wieght from BeeHive & println in LoRa-Modem
		//modem.println(BurkhardsBienen.getIntTemp());		//get internal temperature from BeeHive & println in LoRa-Modem
		msgSend = modem.endPacket(true);					//endPacket finishes all messages and sends it to TTN

		if (msgSend) {
			Serial.println("Message sent correctly!");
			return;
		}
		else {
			Serial.println("Error sending message :(");
		}
	}
	return;
}

bool zeitAbfrage(int interval)  //Methode-universalis um ein Zeitinterval abzufragen. Benoetigt ein globales Array mit zu erwartenden intervallen, gibt true zurueck wenn Zeit abgelaufen ist.
{
	if (lastTime[interval] + intervalle[interval] <= millis())
	{
		lastTime[interval] = millis();
		return true;
	}
	else
	{
		return false;
	}
}
