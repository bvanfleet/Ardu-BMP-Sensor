COPYRIGHT NOTICE
================

 Created By: [Bradley Van Fleet](bvanfleet)
 Date Created: 7/12/2016
 Date Last Modified: 7/13/2016

 **Purpose**: This program, written for educational purposes, is for installing an SD card and [Bosch BMP180]
  pressure/temperature sensor to an Arduino. This code is still undergoing development and should not be
  used in professional settings, unless further modification is undertaken.
  
  [Bosch BMP180]: https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BMP180-DS000-121.pdf

---

##NOTES REGARDING THE CURCUIT

 To ensure proper function, please follow the below guidelines to ensure proper operation of
  the thermostat. Please be sure to also follow safety and regulatory guidelines for assembling
  or modifying the curcuit or code. Depending on the SD slot manufacturer, please adjust the CS
  pin as needed.

**SD card attached to SPI bus as follows:**
* MOSI - pin 11
* MISO - pin 12
* CLK - pin 13
* CS - pin 4 or 10

**SAMPLING SETTINGS FOR BMP180:**
* ULTRA LOW POWER    0
* STANDARD           1
* HIGH RES           2
* ULTRA HIGH RES     3

 If you experience any issues with this software, or have any questions, please send me an [email](mailto:brad@guildofshades.com).

---

###IMPORTANT GNU PUBLIC LISCENCE NOTE

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
