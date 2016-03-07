/*****************************
  DATALOGGER FOR BMP180 SENSOR
******************************

@Description: Board firmware code for Arduino attached to Seeedstudio SD card shield.
Counts for 5 minutes and saves a .txt file with data readings.
Repeats until the SD card is or user ends the logger.

//============================//

* SD card shield information *
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 10
 
//============================//

@Last_Modified: 3/6/2016
@Developed_By: Bradley Van Fleet

******************************/

/***External library referencees***/
#include "BMPSense.h"
#include "LoggerUtilities.h"

/*****************************
 BMP180 Sensor Declaration
 SAMPLING SETTINGS FOR BMP180:
 ULTRA LOW POWER    0
 STANDARD           1
 HIGH RES           2
 ULTRA HIGH RES     3
******************************/
#define SAMPLING 3      // Sampling setting for BMP180 sensor

/***Pin definitions***/
#define CARD_SELECT 10  // SD Shield card selector pin
#define BTN 7           // Button pin
#define RED 6           // Red LED pin
#define BLUE 5          // Blue LED pin

const long int SECOND = 1000, MINUTE = 60;  // Const for time conversions
const short KBYTE = 1024;                   // Const for SD volume comparison

/*****************************
Declarations for File and Logger Utilites objects
Declare clock variable for future use with logger
******************************/
BMPSense BMP180;                            // BMP180 Object to handle sensor and SD card
LoggerUtilities logger = LoggerUtilities(); // LoggerUtilites class to help manage constantly used functions
int clk;                                    // Clock, with time stored in milis
int state;                                  // Integer to hold the state code of the BMP Sense object

/****************************
 Setup Function
 @Purpose: Setup code to run once, initialization code
*****************************/
void setup() {
  /***Pin Initializations***/
  pinMode(BTN, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);

  /***Error Flag Contants***
    * 0 = None (initialized at construction)
    * 1 = FATAL
    * 2 = SERIAL OBJECT
    * 3 = SD CARD
    * 4 = BMP180 SENSOR
  **************************/
  const int FATAL = 1,
    SERIAL_OBJ = 2;
  
  /*************************
  Initialization order:
   * Serial
   * BMP180 Sensor
   * SD card
  Check for errors while initializing,
  Print errors if the initialization fails.
  **************************/
  
  /***Serial initialization***/
  Serial.begin(9600);
  if(!Serial) {
    logger.raiseErr(SERIAL_OBJ);
  }
  delay(500); // Half second delay to allow Serial to fully initialize
  logger.checkState(RED);
  Serial.println("Serial Initialized...");
  
  /***BMP180 initialization***/
  state = BMP180.begin(SAMPLING, CARD_SELECT);
  if(!state) {
    logger.raiseErr(state, "Error: Cannot initialize BMP180 object");
  }
  logger.checkState(RED);
  Serial.println("BMP180 Sensor Initialized...");
  Serial.println("SD Card Initialized...");

  /***Display message and time elapsed after initializations***/
  Serial.println("\nSetup Complete...");
  Serial.print("Time Elapsed: ");
  Serial.println(millis());
  // Wait 1 second to finish initializations
  delay(1000);

  /***Initialize clk last for time when setup ends***/
  clk = millis();
}

void loop() {
  int tDelay = logger.getTimeDelay(clk);
  String data; // String initalized to hold the sensor readings to pass to data_txt
  int while_Loop_Delay = 5 * SECOND;
  const long int CUTOFF = 5 * SECOND * MINUTE;
  
  /***Check that tDelay is less than CUTOFF***/
  while (tDelay < CUTOFF)
  {
    /***********************
    While loop order:
      * Check for pre-existing "Data.txt" file
      * Check volume size to allow for data to be written
      * Open Data.txt file
      * Write BMP180 sensor information
      * "Rinse, Lather, Repeat", exit loop after 5 minutes
    Check for errors after each step
    ************************/

    // Turn BLUE on while data is being written
    digitalWrite(BLUE, HIGH);
    delay(60);

    state = BMP180.startSD("BMP-Data/data.txt");
    
    /***********************
     Temperature and Pressure Reading
    ************************/
    Serial.println(BMP180.writeTemp());
    Serial.println(BMP180.writePress());
    BMP180.closeSD(); // Close file after completion

    // Turn BLUE off after file is closed and time is changed
    digitalWrite(BLUE, LOW);
    delay(while_Loop_Delay); // Wait half-second before starting loop over

    /***********************
     Recalculate tDelay for the while loop
    ************************/
    tDelay = logger.getTimeDelay(clk);
  } // While(tDelay < CUTOFF)

  /*************************
   After while(tDelay < CUTOFF) is finished, open SD card and write average temp and pressure
  **************************/
  state = BMP180.startSD("BMP-Data/data.txt");
  if(!state) {
    logger.raiseErr(state, "Error: Cannot open data.txt");
  }
  logger.checkState(RED);

  Serial.println(BMP180.writeAvg());
  BMP180.closeSD();

  clk = millis(); // Reset the clock after logging 5 minutes of data
}

