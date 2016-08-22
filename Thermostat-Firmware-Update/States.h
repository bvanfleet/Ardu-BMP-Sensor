#pragma once

#if (ARDUINO >= 100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

/* Important Global Definitions */
#define LOCAL_TIMER_CUTOFF 300000 // 5 minute timer cutoff
#define MINUTE_TIMER_CUTOFF 60000 // 1 minute timer cutoff

/* Include the Board Interface class */
#include "Board_Interface.h"

// States abstract class and subclasses
//
// Developed by: Brad Van Fleet
// Date Created: 7/13/2016
// 
// Description: Abstract base class and subclasses used for controling the hardware.
//  All subclasses implement the abstract handleState function and return the
//  state ID for the next state to be called.
class States
{
public:
	/* Default constructor and destructor */
	States();
	virtual ~States();

	/* handleState function declared, pure virtual */
	virtual int handleState() = 0;

	// is_Error function
	// Purpose: Handle error conditions from the Board_Interface object.
	// @Param: int pin value, non-negative.
	// @Return: None
	virtual void is_Error(int);
protected:
	Board_Interface* _BI;
};

class BoardWait : public States
{
public:
	BoardWait();
	int handleState();
	~BoardWait();
private:
	int timer;
};

class BoardRead : public States
{
public:
	BoardRead();
	int handleState();
	~BoardRead();
private:
	String data;
	int count;
};

class BoardWrite : public States
{
public:
	BoardWrite();
	int handleState();
	~BoardWrite();
private:
	String data;
	int average;
};