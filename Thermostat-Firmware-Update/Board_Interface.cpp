#include "Board_Interface.h"

Board_Interface::Board_Interface()
{
	/* General Board datamember initializations */
	bmp = new Adafruit_BMP085;
	sdPin = 10;
	sampling = 2;
	error = false;
	
	/* Temperature and Pressure variable initializations */
	data = "Brad Van Fleet's Thermostat Log\n\n";
	double avg_press;
	double avg_temp;
	int count;

	/* Initialize and check SD and BMP180 for errors */
	if (!bmp->begin(sampling))
	{
		error = true;
		return;
	}

	if (!SD.begin(sdPin))
	{
		error = true;
		return;
	}
}

Board_Interface* Board_Interface::getInstance()
{
	// Check if there's another instance and either create or return an instance
	if (_BI == nullptr)
	{
		_BI = new Board_Interface;
	}

	return _BI;
}

bool Board_Interface::is_Error()
{
	return error;
}

void Board_Interface::readBMP()
{
	// Iterate count
	count++;

	// Read data from BMP and store results
	double temp = bmp->readTemperature();
	double press = bmp->readPressure();
	
	avg_press += press;
	avg_temp += temp;

	// Write results to string
	data += "<T>: " + String(temp, 1) + "\n";
	data += "<P>: " + String(press, 1) + "\n";

	// If the count is 5, then calc and write the average
	if (count == 5)
	{
		data += "<avg-T>: " + String((avg_temp / count), 1) + "\n";
		data += "<avg-P>: " + String((avg_press / count), 1) + "\n";

		// Clear data to start the count and average over
		count = 0;
		avg_temp = 0.0;
		avg_press = 0.0;
	}
}

void Board_Interface::writeSD()
{
	// Initialize filename string
	String filename = "press-temp-log.txt";
	
	// Checks if the file already exists, and creates it if it does not

	// Open the file stream and SD card,
	//  and writes the contents of the data string to it.
	//  If the SD card cannot be written to, then set error flag.
	File dataFile = SD.open(filename, FILE_WRITE);
	if (dataFile)
	{
		dataFile.print(data);
		dataFile.close();
	}
	else
	{
		error = true;
		return;
	}

	data = "";
}

Board_Interface::~Board_Interface()
{
	if (_BI != nullptr)
	{
		delete bmp;
	}
}