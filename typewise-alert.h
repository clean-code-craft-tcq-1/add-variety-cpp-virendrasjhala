#pragma once
#pragma once
#include"iostream"
#include <map>
typedef enum {
	PASSIVE_COOLING,
	HI_ACTIVE_COOLING,
	MED_ACTIVE_COOLING
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
	std::string s;
} BatteryCharacter;

class NotificationTo
{
public:
	virtual void sendToController(BreachType breachType) = 0;
	virtual void sendToEmail(BreachType breachType) = 0;
};

class InterfaceFor :public NotificationTo {
public:
	void sendToController(BreachType breachType);
	void sendToEmail(BreachType breachType);
};

class Maintenance_and_Support {
public:
	std::map<CoolingType, std::pair<double, double>> m;
	BreachType inferBreach(double value, double lowerLimit, double upperLimit);
	BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
	void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

};
