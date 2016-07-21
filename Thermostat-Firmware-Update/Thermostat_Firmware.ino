/*
 Name:		Thermostat_Firmware.ino
 Created:	7/12/2016 10:53:14 AM
 Author:	Brad Van Fleet
*/

#include "States.h"

/* Pin Definitions */
#define BTN 7  // Button pin
#define RED 6  // Red LED pin
#define BLUE 5 // Blue LED pin

/* Global Variable Declarations */
States* boardStates[3];
int sID; // ID for which state to run next

/* ledBlink function */
/* Purpose: Causes blue LED to blink for half second */
void ledBlink();

// Code to perform upon power-up or reset.
void setup() {
	/* Initialize the LED and button hardware */
	pinMode(BTN, INPUT);
	pinMode(RED, OUTPUT);
	pinMode(BLUE, OUTPUT);

	Serial.begin(9600);
	if (!Serial)
	{
		digitalWrite(RED, HIGH);
		delay(60);
		exit(1);
	}

	/* Initialize the state machine */
	boardStates[0] = new BoardWait;
	boardStates[1] = new BoardRead;
	boardStates[2] = new BoardWrite;

	/* Wait 2 seconds to ensure that everything's ready to go */
	Serial.println("Setup Complete");
	ledBlink();
	delay(2000);
}

void loop() {
	sID = boardStates[sID]->handleState();
	boardStates[sID]->is_Error(RED);

	if(sID == 2) ledBlink();
	delay(60);
}

void ledBlink()
{
	int tDelay = 500;

	digitalWrite(BLUE, HIGH);
	delay(tDelay);
	digitalWrite(BLUE, LOW);
}
