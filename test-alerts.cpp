#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
//#include "catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
	Maintenance_and_Support check_breach;
	REQUIRE(check_breach.inferBreach(12, 20, 30) == TOO_LOW);
	Maintenance_and_Support check_alert1;
	BatteryCharacter batteryChar1;
	batteryChar1.coolingType = PASSIVE_COOLING;
	check_alert1.checkAndAlert(TO_EMAIL, batteryChar1, 2);

	Maintenance_and_Support check_alert2;
	BatteryCharacter batteryChar2;
	batteryChar2.coolingType = PASSIVE_COOLING_AIR_PRESSURE;
	check_alert2.checkAndAlert(TO_EMAIL, batteryChar2, 90);
	//system("pause");
	
}

	
