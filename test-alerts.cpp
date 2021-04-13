#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
	Maintenance check_breach;
	REQUIRE(check_breach.inferBreach(15, 20, 30) == TOO_LOW);

	Maintenance PC_Breach;
	BatteryCharacter passive_cooling;
	passive_cooling.coolingType = PASSIVE_COOLING;
	REQUIRE(PC_Breach.checkAndAlert(TO_EMAIL, passive_cooling, 10) == NORMAL);

	Maintenance HI_AC_Breach;
	BatteryCharacter active_cooling;
	active_cooling.coolingType = HI_ACTIVE_COOLING_AIR_PRESSURE;
	REQUIRE(HI_AC_Breach.checkAndAlert(TO_EMAIL, active_cooling, 50) == TOO_HIGH);
	
	Maintenance MID_AC_Breach1;
	BatteryCharacter mid_cooling1;
	mid_cooling1.coolingType = MED_ACTIVE_COOLING_AIR_PRESSURE;
	REQUIRE(MID_AC_Breach1.checkAndAlert(TO_CONTROLLER, mid_cooling1, 40) == NORMAL);

	Maintenance MID_AC_Breach2;
	BatteryCharacter mid_cooling2;
	mid_cooling2.coolingType = MED_ACTIVE_COOLING_AIR_PRESSURE;
	REQUIRE(MID_AC_Breach2.checkAndAlert(NO_Target, mid_cooling2, 40) == UNWANTED_ERROR);


	/*-------------------------------------varify-----------------------------------------*/
	//varify
	emailInterface email_I;
	assert(email_I.emailSent() != 0);

	//varify
	ControllerInterface Controller_I;
	assert(Controller_I.controllerAlertSent() != 0);

}

	
