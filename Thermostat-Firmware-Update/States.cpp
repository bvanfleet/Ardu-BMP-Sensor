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

	// Check if Board_Interface is null or has an error
	if (_BI == nullptr) _BI->getInstance();
	if (_BI->is_Error()) exit(1);

	// Compare to the timer to see if it exceeds the minute_timer_cutoff
	while (count <= MINUTE_TIMER_CUTOFF)
	{
		count = millis() - timer;
	}

	return sID;
}

BoardWait::~BoardWait()
{
	if (_BI != nullptr)
	{
		delete _BI;
	}
}

/*****************************************/
/* BoardRead Child Class Implementations */
/*****************************************/

BoardRead::BoardRead()
	:States()
{	}

int BoardRead::handleState()
{
	int sID = 2;

	// Check if Board_Interface is null, and get instance
	if (_BI == nullptr) _BI->getInstance();
	if (_BI->is_Error()) exit(1);

	// Call readBMP function to gather data
	_BI->readBMP();

	return sID;
}

BoardRead::~BoardRead()
{
	if (_BI != nullptr)
	{
		delete _BI;
	}
}

/******************************************/
/* BoardWrite Child Class Implementations */
/******************************************/

BoardWrite::BoardWrite()
	:States()
{	}

int BoardWrite::handleState()
{
	// Set sID to 0 to start the state loop over
	int sID = 0;

	// Check if Board_Interface is null, and get instance
	if (_BI == nullptr) _BI->getInstance();
	if (_BI->is_Error()) exit(1);

	_BI->writeSD();

	return sID;
}

BoardWrite::~BoardWrite()
{
	if (_BI != nullptr)
	{
		delete _BI;
	}
}