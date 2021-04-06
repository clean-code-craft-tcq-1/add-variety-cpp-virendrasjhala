#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
	Maintenance_and_Support check_breach;
	REQUIRE(check_breach.inferBreach(15, 20, 30) == TOO_LOW);

	Maintenance_and_Support PC_Breach;
	BatteryCharacter passive_cooling;
	passive_cooling.coolingType = PASSIVE_COOLING;
	REQUIRE(PC_Breach.checkAndAlert(TO_EMAIL, passive_cooling, 10) == NORMAL);

	Maintenance_and_Support HI_AC_Breach;
	BatteryCharacter active_cooling;
	active_cooling.coolingType = HI_ACTIVE_COOLING_AIR_PRESSURE;
	REQUIRE(HI_AC_Breach.checkAndAlert(TO_EMAIL, active_cooling, 50) == TOO_HIGH);
	
	Maintenance_and_Support MID_AC_Breach1;
	BatteryCharacter mid_cooling1;
	mid_cooling1.coolingType = MED_ACTIVE_COOLING_AIR_PRESSURE;
	REQUIRE(MID_AC_Breach1.checkAndAlert(TO_CONTROLLER, mid_cooling1, 40) == NORMAL);

	Maintenance_and_Support MID_AC_Breach2;
	BatteryCharacter mid_cooling2;
	mid_cooling2.coolingType = MED_ACTIVE_COOLING_AIR_PRESSURE;
	REQUIRE(MID_AC_Breach2.checkAndAlert(NO_Target, mid_cooling2, 40) == UNWANTED_ERROR);
}

	
