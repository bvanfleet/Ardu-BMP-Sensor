/*
 Name:		Thermostat_Firmware.ino
 Created:	7/12/2016 10:53:14 AM
 Author:	Bradley
*/

#include "States.h"
#include <SD.h>
#include <SPI.h>

/* Pin Definitions */
#define BTN 7  // Button pin
#define RED 6  // Red LED pin
#define BLUE 5 // Blue LED pin

/* Global Variable Declarations */
States* boardStates[3];
int sID; // ID for which state to run next

// Code to perform upon power-up or reset.
void setup() {
	/* Initialize the LED and button hardware */
	pinMode(BTN, INPUT);
	pinMode(RED, OUTPUT);
	pinMode(BLUE, OUTPUT);

	/* Initialize the state machine */
	boardStates[0] = new BoardWait;
	boardStates[1] = new BoardRead;
	boardStates[2] = new BoardWrite;

	/* Wait 2 seconds to ensure that everything's ready to go */
	delay(2000);
}

void loop() {
	sID = boardStates[sID]->handleState();
	delay(60);
}
