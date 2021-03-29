#include "typewise-alert.h"
#include <stdio.h>

BreachType Maintenance_and_Support::inferBreach(double value, double lowerLimit, double upperLimit) {
	if (value < lowerLimit) {
		return TOO_LOW;
	}
	if (value > upperLimit) {
		return TOO_HIGH;
	}
	return NORMAL;
}

BreachType Maintenance_and_Support::classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
	int lowerLimit = 0;
	int upperLimit = 0;
	switch (coolingType) {
	case PASSIVE_COOLING:
		lowerLimit = 0;
		upperLimit = 35;
		break;
	case HI_ACTIVE_COOLING:
		lowerLimit = 0;
		upperLimit = 45;
		break;
	case MED_ACTIVE_COOLING:
		lowerLimit = 0;
		upperLimit = 40;
		break;
	}
	return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void Maintenance_and_Support::checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

	BreachType breachType = Maintenance_and_Support::classifyTemperatureBreach( batteryChar.coolingType, temperatureInC);
	InterfaceFor controller_notifier, email_notifier;
	switch (alertTarget) {
	case TO_CONTROLLER:
		controller_notifier.sendToController(breachType);
		break;
	case TO_EMAIL:
		email_notifier.sendToEmail(breachType);
		break;
	}
}

void InterfaceFor::sendToController(BreachType breachType) {
	const unsigned short header = 0xfeed;
	printf("%x : %x\n", header, breachType);
}

void InterfaceFor::sendToEmail(BreachType breachType) {
	const char* recepient = "a.b@c.com";
	switch (breachType) {
	case TOO_LOW:
		printf("To: %s\n", recepient);
		printf("Hi, the temperature is too low\n");
		break;
	case TOO_HIGH:
		printf("To: %s\n", recepient);
		printf("Hi, the temperature is too high\n");
		break;
	case NORMAL:
		break;
	}
}
