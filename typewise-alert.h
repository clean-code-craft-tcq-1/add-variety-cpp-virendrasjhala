#pragma once
#pragma once
#include"iostream"
#include <map>
#include<vector>
typedef enum {
	PASSIVE_COOLING,
	PASSIVE_COOLING_TEMP,
	PASSIVE_COOLING_AIR_PRESSURE,
	HI_ACTIVE_COOLING,
	HI_ACTIVE_COOLING_TEMP,
	HI_ACTIVE_COOLING_AIR_PRESSURE,
	MED_ACTIVE_COOLING,
	MED_ACTIVE_COOLING_TEMP,
	MED_ACTIVE_COOLING_AIR_PRESSURE
} CoolingType;

typedef enum {
	NORMAL,
	TOO_LOW,
	TOO_HIGH
} BreachType;

typedef enum {
	TO_CONTROLLER,
	TO_EMAIL
} AlertTarget;

typedef struct {
	CoolingType coolingType;
	char brand[48];
} BatteryCharacter;

class NotificationTo{
public:
	virtual void sendToController(BreachType breachType) = 0;
	virtual void sendToEmail(BreachType breachType, CoolingType coolingType) = 0;
};

class InterfaceFor :public NotificationTo {
public:
	std::map<CoolingType, std::string> m = { { PASSIVE_COOLING             ,"PASSIVE_COOLING" },
											{ PASSIVE_COOLING_TEMP         ,"PASSIVE_COOLING_TEMP" },
											{ PASSIVE_COOLING_AIR_PRESSURE ,"PASSIVE_COOLING_AIR_PRESSURE"},
											{ HI_ACTIVE_COOLING            ,"HI_ACTIVE_COOLING" },
											{ HI_ACTIVE_COOLING_TEMP       ,"HI_ACTIVE_COOLING_TEMP" },
											{ HI_ACTIVE_COOLING_AIR_PRESSURE,"HI_ACTIVE_COOLING_AIR_PRESSURE" },
											{ MED_ACTIVE_COOLING           ,"MED_ACTIVE_COOLING" },
											{ MED_ACTIVE_COOLING_TEMP      ,"MED_ACTIVE_COOLING_TEMP" },
											{ MED_ACTIVE_COOLING_AIR_PRESSURE,"MED_ACTIVE_COOLING_AIR_PRESSURE" }
											};
	


	void sendToController(BreachType breachType);
	void sendToEmail(BreachType breachType, CoolingType coolingType);
	std::map<BreachType, std::string> email_contain = { { TOO_HIGH , "  IS TOO HIGH" },
														{ TOO_LOW  , "  IS TOO LOW"  },
														{ NORMAL   , "  IS NORMAL"   }
													   };
};
class Maintenance_and_Support {
public:
	std::map<CoolingType, std::pair<double, double>> check_cooling = {	{ PASSIVE_COOLING              ,std::make_pair(0,35)  },
																		{ PASSIVE_COOLING_TEMP         ,std::make_pair(10,25) },
																		{ PASSIVE_COOLING_AIR_PRESSURE ,std::make_pair(5,30)  },
																		{ HI_ACTIVE_COOLING            ,std::make_pair(0,45)  },
																		{ HI_ACTIVE_COOLING_TEMP       ,std::make_pair(20,30) },
																		{ HI_ACTIVE_COOLING_AIR_PRESSURE,std::make_pair(5,45) },
																	    { MED_ACTIVE_COOLING           ,std::make_pair(0,40)  },
																		{ MED_ACTIVE_COOLING_TEMP      ,std::make_pair(8,50)  },
																		{ MED_ACTIVE_COOLING_AIR_PRESSURE,std::make_pair(8,60)}
																	  };
	BreachType inferBreach(double value, double lowerLimit, double upperLimit);
	BreachType classifyTemperatureAndPressureBreach(CoolingType coolingType, double temperatureInC);
	void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

};
