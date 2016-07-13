#include "Board_Interface.h"

Board_Interface::Board_Interface()
{
	bmp = new Adafruit_BMP085;
	sdPin = 10;
	sampling = 2;
	error = false;

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
	if (BI == nullptr)
	{
		BI = new Board_Interface;
	}

	return BI;
}

bool Board_Interface::is_Error()
{
	return error;
}

Board_Interface::~Board_Interface()
{
	if (BI != nullptr)
	{
		delete bmp;
	}
}