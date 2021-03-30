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

	return inferBreach(temperatureInC, check_cooling[coolingType].first, check_cooling[coolingType].second);
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
	printf("To: %s\n", recepient);
	printf("Hi");
	std::cout << email_contain[breachType].data()<<"\n";

}
