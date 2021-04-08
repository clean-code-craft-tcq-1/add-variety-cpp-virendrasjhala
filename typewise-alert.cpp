#include "typewise-alert.h"
#include <stdio.h>


BreachType Maintenance::inferBreach(double value, double lowerLimit, double upperLimit) {
	if (value < lowerLimit) {
		return TOO_LOW;
	}
	if (value > upperLimit) {
		return TOO_HIGH;
	}
	return NORMAL;
}

BreachType Maintenance::classifyTemperaturePressureBreach(CoolingType coolingtype, double valuetocheck) {

	return inferBreach(valuetocheck, check_cooling[coolingtype].first, check_cooling[coolingtype].second);
}

BreachType Maintenance::checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double valuetocheck) {

	BreachType breachType = Maintenance::classifyTemperaturePressureBreach( batteryChar.coolingType, valuetocheck);
	InterfaceFor controller_notifier, email_notifier;
	switch (alertTarget) {
	case TO_CONTROLLER:
		return controller_notifier.sendToController(breachType);
		break;
	case TO_EMAIL:
		return email_notifier.sendToEmail(breachType, batteryChar.coolingType);
		break;
	default: std::cout<<"UNWANTED_ERROR: "<< UNWANTED_ERROR<<"\n";
	}

	return UNWANTED_ERROR;
}

BreachType InterfaceFor::sendToController(BreachType breachType) {
	const unsigned short header = 0xfeed;
	printf("%x : %x\n", header, breachType);

	return breachType;
}

BreachType InterfaceFor::sendToEmail(BreachType breachType, CoolingType coolingType) {
	const char* recepient = "a.b@c.com";
	printf("To: %s\n", recepient);
	std::cout<<"Hi"<<"\n";
	std::cout << m[coolingType].data()<<":"<<email_contain[breachType].data() << "\n\n";

	return breachType;
}
