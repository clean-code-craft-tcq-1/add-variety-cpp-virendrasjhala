#include "typewise-alert.h"
#include <stdio.h>
#include<sstream>

 int emailInterface::sentEmails=0;
 int ControllerInterface::controllerAlert =0;

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

int emailInterface::emailSent()
{
	return sentEmails++;
}
void emailInterface::EmailSender() {
	const char* recepient = "a.b@c.com";
	printf("To: %s\n", recepient);
	std::cout << "Hi" << "\n";

	emailSent();
}
int ControllerInterface::controllerAlertSent() {

	return controllerAlert++;
}
void ControllerInterface::InformController() {
	controllerAlertSent();
}

void InterfaceFor::controllerToConsole(BreachType breachType) {
	
	std::cout <<std::hex<<header <<":"<< email_contain[breachType].data()<<"\n\n";
}
void InterfaceFor::emailToConsole(BreachType breachType, CoolingType coolingType) {

	std::cout << cooling[coolingType].data() << ":" << email_contain[breachType].data() << "\n\n";
}   

BreachType InterfaceFor::sendToController(BreachType breachType) {
	ControllerInterface Controller_I;
	Controller_I.InformController();
	controllerToConsole(breachType);
	return breachType;
}

BreachType InterfaceFor::sendToEmail(BreachType breachType, CoolingType coolingType) {
	emailInterface Email_I;
	Email_I.EmailSender();
	emailToConsole(breachType, coolingType);
	return breachType;
}
