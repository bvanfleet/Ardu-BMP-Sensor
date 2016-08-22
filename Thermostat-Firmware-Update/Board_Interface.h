#pragma once

#if (ARDUINO >= 100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

/* Required package inclusions */
#include <Adafruit_BMP085.h>
#include <SD.h>
#include <SPI.h>

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
	static Board_Interface* board;
	Adafruit_BMP085* bmp;
	int sdPin;
	int sampling;
	bool error;

	/* Temperature and Pressure variables */
	String data;
	double avg_press;
	double avg_temp;
	int count;

	/* Constructor function definitions */
	/* Standard constructor with default parameters */
	/* @Param: SD Select pin number and BMP180 sampling settings, non-negative int */
	Board_Interface(int, int);

	/* Copy constructors are removed to maintain the singleton pattern */
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
	// @Return: Const pointer reference to Board_Interface object
	Board_Interface* getInstance() const;

	// is_Error function
	//
	// Description: Return the error data member. Used for error checking.
	//
	// @Param: None
	// @Return: True or False, depending on if errors are present.
	bool is_Error() const;
	
	// readBMP Function
	//
	// Description: Takes temperature and pressure reading from the sensor and stores
	//  readings into the data string to write to SD card.
	//
	// @Param: None
	// @Return: Void
	void readBMP();

	// writeSD Function
	//
	// Description: Writes data taken during the readBMP function and writes to the SD card.
	//
	// @Param: None
	// @Return: Void
	void writeSD();

	// Board_Interface deconstructor
	~Board_Interface();
};

