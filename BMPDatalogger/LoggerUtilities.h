#pragma once

#ifndef LOGGERUTILITIES_H
#define LOGGERUTILITIES_H

using namespace std;

#include "ErrorState.h"

class LoggerUtilities
{
  private:
  ErrorState boardState;
  int flag;
  String eMessage;
  
  public:
  LoggerUtilities() {
    boardState = ErrorState();
    flag = 0;
    eMessage = "";
  };

  void raiseErr(int err) {
    flag = err;
    boardState.raiseFatalError();
  }

  void raiseErr(int err, String message) {
    flag = err;
    boardState.raiseError(err, message);
  };

  /****************************
   getTime Function
   @Purpose: Returns the time, subtracts clk from millis()
   @Param: Current clock time
   @Return: time, in milis
  *****************************/
  int getTimeDelay(int clk) {
    return ( millis() - clk );
  };

  /****************************
   checkState Function
   @Purpose: Check boardState for errors, quit program if any
   @Param: None
   @Return: None
  *****************************/
  void checkState(int led) {
    bool err = boardState.isError(flag, eMessage);
    if(err && flag == 1)
    {
      digitalWrite(led, HIGH);
      exit(1);
    }
    else if(err && flag > 1)
    {
      do {
      // Print error
      Serial.println(eMessage);
      delay(60); // Delay 60 ms to allow message to be displayed
      } while(Serial.available());
      
      // Activate red LED and exit
      digitalWrite(led, HIGH);
      exit(1);
    }
    else return;
  };
  
}; // End Logger Utitlies Class

#endif
