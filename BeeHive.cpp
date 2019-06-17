#include "Arduino.h"
#include "BeeHive.h"

//in BeeHive.cpp passiert die Action, also Berechnungen, eigentliche Zuweisungen etc.
//in BeeHive.h werden ausschließlich alle Dinge benannt (deklariert)

//Hier wird aus "was KÖNNTE" passieren eine konkrete Aktion. 

//Temporäre Notlösung da OpenScale-Board nicht wie gewollt funktioniert
void BeeHive::setOpenscale(String inpOpenscale)
{
	openscale = inpOpenscale;
}

String BeeHive::getOpenscale()
{
	return openscale;
}


//Methoden um Temperatur zuzuweisen bzw. abfragen
void BeeHive::setIntTemp(double inpTemp)
{
	internalTemp = inpTemp;		//internalTemp ist in ".h" privat. Da aber oben "BeeHive::" steht darf darauf zugegriffen werden (ein Bienenstock darf seine eigene Temperatur ändern)
}

double BeeHive::getIntTemp()
{
	return internalTemp;
}

//Methoden um externe Temperatur zuzuweisen bzw. abfragen
void BeeHive::setExtTemp(double inpTemp)
{
	externalTemp = inpTemp;		
}

double BeeHive::getExtTemp()
{
	return externalTemp;
}

//Methoden um interne Luftfeuchtigkeit zu setzen bzw. abfragen
void BeeHive::setIntHum(int inpHum)
{
	internalHumidity = inpHum;
}
int BeeHive::getIntHum()
{
	return internalHumidity;
}

//Methoden um externe Luftfeuchtigkeit zu setzen bzw. abfragen
void BeeHive::setExtHum(int inpHum)
{
	externalHumidity = inpHum;
}
int BeeHive::getExtHum()
{
	return externalHumidity;
}

//Methode zum Gewicht setzen/lesen
void BeeHive::setWeight(double inpWeight)
{
	weight = inpWeight;
}
double BeeHive::getWeight()
{
	return weight;
}

//Methoden um Anzahl zurueckgekehrter Bienen festzulegen
void BeeHive::setBeeReturned(unsigned long inpBeeReturned)
{
	beeReturned = inpBeeReturned;
}
unsigned long BeeHive::getBeeReturned()
{
	return beeReturned;
}

//Methoden um Anzahl Bienen außerhalb festzulegen
void BeeHive::setBeeOutside(unsigned long inpBeeOutside)
{
	beeOutside = inpBeeOutside;
}
unsigned long BeeHive::getBeeOutside()
{
	return beeOutside;
}

//Methode für Deckelstatus
void BeeHive::setLidState(bool inpLid)
{
	lidState = inpLid;
}
bool BeeHive::getLidState()
{
	return lidState;
}