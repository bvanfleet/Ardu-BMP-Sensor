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

@Last_Modified: 2/15/2016
@Developed_By: Bradley Van Fleet

******************************/

/***External library referencees***/
#include <SD.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>
#include "ErrorState.h"

/***Pin definitions***/
#define CARD_SELECT 10  // SD Shield card selector pin
#define BTN 7           // Button pin
#define RED 6           // Red LED pin
#define BLUE 5          // Blue LED pin

/*****************************
 BMP180 Sensor Declaration
 SAMPLING SETTINGS FOR BMP180:
 ULTRA LOW POWER    0
 STANDARD           1
 HIGH RES           2
 ULTRA HIGH RES     3
******************************/
Adafruit_BMP085 BMP180;
#define SAMPLING 3

const long int SECOND = 1000, MINUTE = 60;    // Const for time conversions
const short KBYTE = 1024;                     // Const for SD volume comparison

/*****************************
States to check and contain error messages
eMessage string initialized to store error messages
flag integer used to store error flags from ErrorState
******************************/
ErrorState boardState = ErrorState();
String eMessage = "";
int flag = 0;

int clk;                        // Clock, with time stored in milis
bool logger_Button = true;      // Button, if set to true, activates datalogger
File data_txt;                  // File object used to log data

/****************************
 getTime Function
 @Purpose: Returns the time, subtracts from clk, and 
 @Param: None
 @Return: time, in milis
*****************************/
int getTimeDelay();

/****************************
 getSD_Size Function
 @Purpose: Returns the SD card volume size in MBs
 @Param: None
 @Return: SD volume size in MBs
*****************************/
double getSD_Size();

/****************************
 checkState Function
 @Purpose: Check boardState for errors, quit program if any
 @Param: None
 @Return: None
*****************************/
void checkState();

/****************************
 Setup Function
 @Purpose: Setup code to run once, initialization code
*****************************/
void setup() {
  /***Pin Initializations***/
  pinMode(BTN, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);

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
    flag = 2;
    boardState.raiseFatalError();
  }
  delay(500); // Half second delay to allow Serial to fully initialize
  checkState();
  Serial.println("Serial Initialized...");

  /***BMP180 initialization***/
  if(!BMP180.begin(SAMPLING)) {
    flag = 4;
    boardState.raiseError(flag, "Error: Cannot initialize BMP180 sensor");
  }
  checkState();
  Serial.println("BMP180 Sensor Initialized...");
  
  /***SD initialziation***/
  if(!SD.begin(CARD_SELECT)) {
    flag = 3;
    boardState.raiseError(flag, "Error initializing SD card!");
  }
  if(boardState.isError(flag, eMessage)) 
  checkState();
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
  int tDelay = getTimeDelay();
  String data; // String initalized to hold the sensor readings to pass to data_txt
  int while_Loop_Delay = 5 * SECOND;
  const long int CUTOFF = 5 * SECOND * MINUTE;

  /***************************
   Variables used for additional data logging purposes:
    * total_Temp
    * total_Press
    * count
   Calc average after 5 minutes of logging data and pass into data.txt file
  ****************************/
  float total_Temp = 0;
  float total_Press = 0;
  short count = 0;
  
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
 
    /***Check that there is space on the SD card to write to***/
    /***TODO: debug below to check that there is enough space on SD card***/
    /*
    if(getSD_Size() <= KBYTE) {
      // Print space available, in bytes, if not enough room
      Serial.print("Volume size: ");
      Serial.print(getSD_Size());
      Serial.println(" bytes available.");
      
      flag = 6;
      boardState.raiseError(flag, "Error: Not enough space on SD card");
    }
    checkState();
    */
    
    /***Check for pre-existing data.txt file***/
    if(!SD.exists("BMP-Data/data.txt")) SD.mkdir("BMP-Data"); // If the file doesn't exitst, create it
    data_txt = SD.open("BMP-Data/data.txt", FILE_WRITE);
    if(!data_txt) {
      flag = 5;
      boardState.raiseError(flag, "Error: Cannot open data.txt");
    }
    checkState();

    // Turn BLUE on while data is being written
    digitalWrite(BLUE, HIGH);
    delay(60);

    /***********************
     Data logging sequence:
      * Write temp and pressure
      * close file
    ************************/
    
    /***********************
     Temperature Reading
    ************************/
    float temp = BMP180.readTemperature();
    total_Temp += temp;
    
    data = "Temperature: ";
    data += temp;
    data += " C";

    data_txt.println(data); // Write temperature to data_txt
    Serial.println(data);
    
    /***********************
     Pressure Reading
    ************************/
    float pressure = BMP180.readPressure();
    total_Press += pressure;
    
    data = "Pressure: ";
    data += pressure;
    data += " Pa";

    data_txt.println(data); // Write pressure to data_txt
    Serial.println(data);
    
    data_txt.close(); // Close file after completion
    
    count++; // Increment count for averaging

    // Turn BLUE off after file is closed and time is changed
    digitalWrite(BLUE, LOW);
    delay(while_Loop_Delay); // Wait half-second before starting loop over

    /***********************
     Recalculate tDelay for the while loop
    ************************/
    tDelay = getTimeDelay();
  } // While(tDelay < CUTOFF)

  /*************************
   After while(tDelay < CUTOFF) is finished, open SD card and write average temp and pressure
  **************************/
  data_txt = SD.open("BMP-Data/data.txt", FILE_WRITE);
  if(!data_txt) {
    flag = 5;
    boardState.raiseError(flag, "Error: Cannot open data.txt");
  }
  checkState();

  data = "Average Temperature: ";
  data += (total_Temp / count);
  data += "  |  ";
  data += "Average Pressure: ";
  data += (total_Press / count);

  data_txt.println(data);
  Serial.println(data);
  data_txt.close();

  clk = millis(); // Reset the clock after logging 5 minutes of data
}

/***getTimeDelay function implementation***/
int getTimeDelay() {
  int tempTime = millis();
  int tDelay = tempTime - clk;

  return tDelay;
}

/***getSD_Size function implementation***/
double getSD_Size() {
  // Initialize temp volume object
  SdVolume volume;

  // Delcare byte and kByte constants, for conversions
  const int BYTE = 512;
  
  // Initialize volume size (vSize) integer
  // Assign blocks/cluster to vSize
  int vSize = volume.blocksPerCluster();

  // Convert blocks/cluster to clusters, then bytes
  vSize *= volume.clusterCount();
  vSize *= BYTE;

  // Return vSize
  return vSize;
}

/***checkState functions implementation***/
void checkState() {
  if(boardState.isFatal() && flag == 1)
  {
    digitalWrite(RED, HIGH);
    exit(1);
  }
  else if(boardState.isError(flag, eMessage) && flag > 1)
  {
    do {
    // Print error
    Serial.println(eMessage);
    delay(60); // Delay 60 ms to allow message to be displayed
    } while(Serial.available());
    
    // Activate red LED and exit
    digitalWrite(RED, HIGH);
    exit(1);
  }
  else return;
}

