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
	States();
	virtual int handleState()=0;
	virtual void is_Error(int);
	virtual ~States();
protected:
	Board_Interface* _BI;
};

class BoardWait : public States
{
private:
	int timer;
public:
	BoardWait();
	int handleState();
	~BoardWait();
};

class BoardRead : public States
{
private:
	String data;
	int count;
public:
	BoardRead();
	int handleState();
	~BoardRead();
};

class BoardWrite : public States
{
private:
	String data;
	int average;
public:
	BoardWrite();
	int handleState();
	~BoardWrite();
};