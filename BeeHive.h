#include "Arduino.h"

class BeeHive
{
	int internalHumidity;			//inside BeeHive humidity
	int externalHumidity;			//outside BeeHive humidity
	double internalTemp;			//inside BeeHive temperature
	double externalTemp;			//outside BeeHive temperature
	double weight;					//BeeHive weight
	String openscale;				//String von OpenScale Chip
	unsigned long beeReturned;		//returned bee-count
	unsigned long beeOutside;		//outside bee-count
	bool lidState;					//state of BeeHive lid (open/closed)

public:
	//set or get Openscale-String
	void setOpenscale(String openscale);
	String getOpenscale();

	//set or get internal temperature
	void setIntTemp(double intTemp);
	double getIntTemp();

	//set or get external temperature
	void setExtTemp(double extTemp);
	double getExtTemp();

	//set or get internal humidity
	void setIntHum(int intHum);
	int getIntHum();

	//set or get external humidity
	void setExtHum(int extHum);
	int getExtHum();

	//set or get beehive weight
	void setWeight(double weight);
	double getWeight();

	//set or get count of bees returned
	void setBeeReturned(unsigned long beeReturned);
	unsigned long getBeeReturned();

	//set or get count of bees outside
	void setBeeOutside(unsigned long beeOutside);
	unsigned long getBeeOutside();

	//set or get lid state
	void setLidState(bool lidState);
	bool getLidState();
};

