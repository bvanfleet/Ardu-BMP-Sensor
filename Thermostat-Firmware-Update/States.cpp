#include "States.h"

/***********************************************/
/* States Abstract Base Class Immplementations */
/***********************************************/

States::States()
{
	_BI = _BI->getInstance();
}

void States::is_Error(int pin)
{
	if (_BI->is_Error())
	{
		digitalWrite(pin, HIGH);
		exit(1);
	}
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
	Serial.println("Entering BoardWait State");
	delay(60);

	// Instance variables to be changed throughout the function
	int sID = 1; // State ID number for the next state
	long int count = 0;

	// Check if Board_Interface is null or has an error
	if (_BI == nullptr)
	{
		_BI = _BI->getInstance();
	}

	// Compare to the timer to see if it exceeds the minute_timer_cutoff
	while (count <= MINUTE_TIMER_CUTOFF)
	{
		count = millis() - timer;
		delay(1000);
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
	Serial.println("Entering BoardReach State");
	delay(60);

	int sID = 2;

	// Check if Board_Interface is null, and get instance
	if (_BI == nullptr)
	{
		_BI = _BI->getInstance();
	}

	// Call readBMP function to gather data
	_BI->readBMP();

	return sID;
}

BoardRead::~BoardRead()
{
<<<<<<< HEAD
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
=======
	sID = 0;
>>>>>>> BMP180

int BoardWrite::handleState()
{
	Serial.println("Entering BoardWrite State");
	delay(60);

	// Set sID to 0 to start the state loop over
	int sID = 0;

	// Check if Board_Interface is null, and get instance
	if (_BI == nullptr)
	{
		_BI = _BI->getInstance();
	}

	_BI->writeSD();
	delay(60);

	return sID;
}
<<<<<<< HEAD

BoardWrite::~BoardWrite()
{
	if (_BI != nullptr)
	{
		delete _BI;
	}
}
=======
>>>>>>> BMP180
