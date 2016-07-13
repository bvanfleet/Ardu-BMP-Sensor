#pragma once

#if (ARDUINO >= 100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

/* Required package inclusions */
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <SD.h>

// Board_Interface singleton class
// Designed by: Bradley Van Fleet
// Date Created 7/13/2016
//
// Description: Hardware API interface for use within the thermostat firmware.
//  Includes the SD card and BMP180 sensor API. Singleton design to keep instantiation
//  to a minimum.
class Board_Interface
{
private:
	/* Datamember declarations */
	static Board_Interface* BI;
	Adafruit_BMP085* bmp;
	int sdPin;
	int sampling;
	bool error;

	/* Constructor function definitions */
	Board_Interface();
	Board_Interface(Board_Interface&) = delete;
	Board_Interface(Board_Interface&&) = delete;

public:
	// getInstance function
	//
	// Description: Checks for an existing instance of the Board_Interface object.
	//  If one is found, it is returned; otherwise, an instance of the Board_Interface
	//  object is created.
	//
	// @Param: None
	// @Return: Pointer reference to Board_Interface object
	Board_Interface* getInstance();

	// is_Error function
	//
	// Description: Return the error data member. Used for error checking.
	//
	// @Param: None
	// @Return: True or False, depending on if errors are present.
	bool is_Error();

	// Board_Interface deconstructor
	~Board_Interface();
};

