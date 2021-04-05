#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
	Maintenance_and_Support check_breach;
	REQUIRE(check_breach.inferBreach(25, 20, 30) == NORMAL);

	Maintenance_and_Support PC_Breach;
	BatteryCharacter passive_cooling;
	passive_cooling.coolingType = PASSIVE_COOLING;
	REQUIRE(PC_Breach.checkAndAlert(TO_EMAIL, passive_cooling, 2) == NORMAL);

	Maintenance_and_Support HI_AC_Breach;
	BatteryCharacter active_cooling;
	active_cooling.coolingType = HI_ACTIVE_COOLING_AIR_PRESSURE;
	REQUIRE(HI_AC_Breach.checkAndAlert(TO_EMAIL, active_cooling, 20) == NORMAL);
	
	
	Maintenance_and_Support MID_AC_Breach;
	BatteryCharacter mid_cooling;
	mid_cooling.coolingType = MED_ACTIVE_COOLING_TEMP;
	REQUIRE(MID_AC_Breach.checkAndAlert(TO_CONTROLLER, mid_cooling, 30) == NORMAL);
	
}

	
