#pragma once

#ifndef BMPSENSE_H
#define BMPSENSE_H

#include <SD.h>
#include <SPI.h>
#include <Adafruit_BMP085.h>

/****************
 BMP Sense Class
 @Last_Modified: 3/6/2016
 @Developed_By: Bradley Van Fleet
 
 @Description: BMP Sensor class, holds the data members and functions for use with
 data logger board. Includes Adafruit BMP085 sensor library and SD card library.
*****************/
class BMPSense {
  /**************************
   Private Member Data
  *=========================*/
  private:
  /**************************
   Error State Codes
  ***************************/
  const int SD_CARD = 3, SENSOR = 4, DATA = 5;
  /**************************
   Object Declarations
  ***************************/
  Adafruit_BMP085 _BMP180;
  File data_txt;
  /**************************
   Variables for total temperature and pressure
  ***************************/
  double total_Temp, total_Press;
  int tCount, pCount;

  /**************************
   Public Member Data
  *=========================*/
  public:
  /**************************
   Begin Function
   @Purpose: Initialize data members and objects for sensor and SD card
   @Param: sampling in for BMP180, select for SD
   @Return: int value for state checking
  ***************************/
  int begin(int sampling, int select) {
    // Initalize BMP180 and SD card
    if(!_BMP180.begin(sampling)) return SENSOR;
    if(!SD.begin(select)) return SD_CARD;
    
    // Initialize data members
    total_Temp = 0;
    total_Press = 0;
    tCount = 0;
    pCount = 0;

    return 0;
  };

  /**************************
   StartSD Function
   @Purpose: Initialize SD card with filepath
   @Param: String file path
   @Return: int value for state checking
  ***************************/
  int startSD(String path) {
    // Open SD card
    if(!SD.exists(path)) SD.mkdir("BMP-Data");
    data_txt = SD.open(path, FILE_WRITE);
    if(!data_txt) return DATA;
  };

  /**************************
   CloseSD Function
   @Purpose: Close File if one exists
   @Param: None
   @Return: None
  ***************************/
  void closeSD() {
    if(data_txt) data_txt.close();
  }

  /**************************
   getSD_Size Function
   @Purpose: Returns the SD card volume size in MBs
   @Param: None
   @Return: SD volume size in MBs
  ***************************/
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
  };

  /**************************
   WriteTemp Function
   @Purpose: Write BMP sensor data to data_txt File
   @Param: None
   @Return: String sensor data
  ***************************/
  String writeTemp() {
    String data;
    
    float temp = _BMP180.readTemperature();
    total_Temp += temp;
    tCount++;
    
    data = "Temperature: ";
    data += temp;
    data += " C";

    data_txt.println(data); // Write temperature to data_txt
    return data;
  };

  /**************************
   WritePress Function
   @Purpose: Write BMP sensor data to data_txt File
   @Param: None
   @Return: String sensor data
  ***************************/
  String writePress() {
    String data;
    
    float pressure = _BMP180.readPressure();
    total_Press += pressure;
    pCount++;
    
    data = "Pressure: ";
    data += pressure;
    data += " Pa";

    data_txt.println(data);
    return data;
  };

  /**************************
   WriteAcg Function
   @Purpose: Write average sensor data to data_txt File
   @Param: None
   @Return: String average data
  ***************************/
  String writeAvg() {
    String data;
    
    data = "Average Temperature: ";
    data += (total_Temp / tCount);
    data += "  |  ";
    data += "Average Pressure: ";
    data += (total_Press / pCount);
  
    data_txt.println(data);
    return data;
  };
  
}; // End BMPSense Class

#endif
