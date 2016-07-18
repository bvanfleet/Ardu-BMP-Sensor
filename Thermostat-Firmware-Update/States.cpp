#include "States.h"

/***********************************************/
/* States Abstract Base Class Immplementations */
/***********************************************/

States::States()
{
	_BI = _BI->getInstance();
}

States::~States()
{
	if (_BI != nullptr)
	{
		delete _BI;
	}
}

/*****************************************/
/* BoardWait Child Class Implementations */
/*****************************************/

BoardWait::BoardWait()
	:States()
{
	timer = millis();
}

int BoardWait::handleState()
{
	// Instance variables to be changed throughout the function
	int sID = 1; // State ID number for the next state
	int count = 0;

	// Compare to the timer to see if it exceeds the minute_timer_cutoff
	while (count <= MINUTE_TIMER_CUTOFF)
	{
		count = millis() - timer;
		delay(1000);
	}

	return sID;
}

/*****************************************/
/* BoardRead Chile Class Implementations */
/*****************************************/

BoardRead::BoardRead()
{

}

int BoardRead::handleState()
{
	sID = 0;



	return sID;
}
