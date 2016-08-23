Ardu BMP Sensor
===============

 Created By: [Bradley Van Fleet](bvanfleet)
 Date Created: 7/12/2016
 Date Last Modified: 7/13/2016

 **Purpose**: This program, written for educational purposes, is for installing an SD card and [Bosch BMP180]
  pressure/temperature sensor to an Arduino. This code is still undergoing development and should not be
  used in professional settings, unless further modification is undertaken.
  
  _Please reference my [wiki] regarding code documentation._
  
  [Bosch BMP180]: https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMP180-DS000-121.pdf
  [wiki]: https://github.com/bvanfleet/Ardu-BMP-Sensor/wiki

---

## Installation
 
 This program was written with the intended use for Arduino. Use with any other microcontroller, or application, is not recommended. This program can be uploaded using the ArduinoIDE, Visual Studio, or any other program capable of compiling and uploading Arduino sketches.
 
 For instructions on uploading a sketch using the ArduinoIDE, please reference their documentation [HERE](https://www.arduino.cc/en/Guide/Environment#toc9).
 
 Once the upload has successfully completed you may unplug the microcontroller and connect it to a power supply. Once the board setup has completed, the green LED will flash, and the board will proceed to operate as a datalogger. If an issue arrises in the hardware or software, the red LED will illuminate, and the board will cease operation until reset.

 If you experience any issues with this software, or have any questions, please send me an [email](mailto:brad@guildofshades.com).

---

## Notes Regarding Software Design

 For those interested in understanding how this program is currently set up, below you will find documentation regarding the code, patterns used, and the tasklist as it stands:

 * Design Patterns -
   * [x] State Machine - overall program structure
   * [x] Singleton - interface with board hardware
   * [ ] Observer Pattern - control with future mobile app
 * Classes -
   * States - There is an abstract parent class as well as 3 subclasses. There will be eventual subclasses added to handle new states, such as updating the information read.
   * Board_Interface - Currently in charge of the [Bosch BMP180] sensor and the SD card. This interface may eventually handle the Wi-Fi shield. However, to keep it from becoming too large, I may split the functionality of that shield to just the Arduino Wi-Fi library, or it's own class.
 * Eventual Tasks -
   * Change the file stream to write over the data after 10 writes.
   * Synchronise the singleton objects to work in possible multi-threaded environments (especially with Wi-Fi).
   * Interface to handle exchange from C++ read data to Java coded mobile app.

*Please reference the [latest release] for the source code*

 [latest release]: https://github.com/bvanfleet/Ardu-BMP-Sensor/tree/v0.3-beta

---

### IMPORTANT GNU PUBLIC LISCENCE NOTE

 _This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version._

 _This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details._

 _You should have received a copy of the GNU General Public License
along with this program.  If not, see <[http://www.gnu.org/licenses/](http://www.gnu.org/licenses/)>_
