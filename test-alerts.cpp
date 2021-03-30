#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
//#include "catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
	Maintenance_and_Support check_breach;
	REQUIRE(check_breach.inferBreach(12, 20, 30) == TOO_LOW);
	Maintenance_and_Support check_alert;
	BatteryCharacter batteryChar1;
	batteryChar1.coolingType = PASSIVE_COOLING;
	check_alert.checkAndAlert(TO_EMAIL, batteryChar1, 90);
	//system("pause");
	
}

	
