#pragma once

#ifndef ERRORSTATE_H
#define ERRORSTATE_H

using namespace std;

/********************************
Error State Class

@Last_Modified: 2/16/2016
@Developed_By: Bradley Van Fleet

@Description: Provides basic error exception handling for sensor embedded system.
*********************************/

class ErrorState
{
private:
  bool error;
  String eMessage;
  int eFlag;
  /******************************
   Error Codes
    * 0 = None (initialized at construction)
    * 1 = FATAL
    * 2 = SERIAL OBJECT
    * 3 = SD CARD
    * 4 = BMP180 SENSOR
    * 5 = FILE OBJECT
    * 6 = SD VOLUME
  *******************************/
  enum error_Code { FATAL=1, SERIAL_OBJ, SD_CARD, BMP180_S, FILE_OBJ, SD_VOLUME };

public:

  // Error State constructor
  // Purpose: Initiates data members
  // Parameters: None
  // Returns: None
  ErrorState()
  {
    error = false;
    eMessage = "";
    eFlag = 0;
  };

  // Raise Error Function
  // Purpose: If no previous error are set,
  //  sets error boolean and holds a message
  // Parameters: String, message to hold about error
  // Returns: None
  void raiseError(int flag, String what)
  {
    if (!error)
    {
      error = true;
      eFlag = flag;
      eMessage = String(what);
    }
  };

  // Raise Fatal Error Function
  // Purpose: Set error to true, but doesn't take a string
  // Parameters: None
  // Returns: None
  void raiseFatalError()
  {
    error = true;
    eFlag = FATAL;
  };

  // Is Error Function
  // Purpose: Gets the class state and any messages contained
  // Parameters: Reference string, to gather any messages set
  // Returns: Boolean error state
  bool isError(int& flag, String& what) {
    if (error && (eFlag != FATAL || eFlag != SERIAL_OBJ))
    {
      what = String(eMessage);
      flag = eFlag;
      return error;
    }
    else return error;
  };

  // Is Fatal Function
  // Purpose: Returns if there has been a fatal error
  //  Doesn't return a string
  // Parameters: None
  // Returns: Boolean, if error
  bool isFatal()
  {
    if(eFlag == FATAL || SERIAL_OBJ)
    {
      return error;
    }
  };
  
}; // Class ErrorState

#endif
