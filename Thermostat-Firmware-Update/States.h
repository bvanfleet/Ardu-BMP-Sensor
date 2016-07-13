#pragma once

#if (ARDUINO >= 100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

/* Important Global Definitions */
#define LOCAL_TIMER_CUTOFF 0x493E0 // 5 minute timer cutoff
#define MINUTE_TIMER_CUTOFF 0xEA60 // 1 minute timer cutoff

#include "Board_Interface.h"

class States
{
public:
	States();
	virtual int handleState()=0;
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
	BoardWrite(String);
	int handleState();
	~BoardWrite();
};