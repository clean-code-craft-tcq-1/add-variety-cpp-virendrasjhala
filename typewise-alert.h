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
	TOO_HIGH,
	UNWANTED_ERROR
} BreachType;

typedef enum {
	TO_CONTROLLER,
	TO_EMAIL,
	NO_Target
} AlertTarget;

typedef struct {
	CoolingType coolingType;
	char brand[48];
} BatteryCharacter;

class NotificationTo{
public:
	virtual BreachType sendToController(BreachType breachType) = 0;
	virtual BreachType sendToEmail(BreachType breachType, CoolingType coolingType) = 0;
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
	BreachType sendToController(BreachType breachType);
	BreachType sendToEmail(BreachType breachType, CoolingType coolingType);
	std::map<BreachType, std::string> email_contain = { { TOO_HIGH , " TOO HIGH" },
														{ TOO_LOW  , " TOO LOW"  },
														{ NORMAL   , " NORMAL"   }
													   };
};
class Maintenance {
public:
	std::map<CoolingType, std::pair<double, double>> check_cooling = {	{ PASSIVE_COOLING              ,std::make_pair(5,35)  },
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
	BreachType classifyTemperaturePressureBreach(CoolingType coolingType, double temperatureInC);
	BreachType checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

};
