# OB38S003-PANTILT-UNIT-FOR-CAMERA

This PAN TILT positioner model may have a printed circuit board with the OB38S003W20 microcontroller (On-Bright). Apparently the chassis was created for a larger board, perhaps to use another type of microcontroller.

- It may be important to check the speed of the device before purchasing, the standard is 9600, but some sellers sell 2400 baud devices without warning.

![img](https://raw.githubusercontent.com/rtek1000/OB38S003-PANTILT-UNIT-FOR-CAMERA/refs/heads/main/Img/Ad3.jpg)

-----

I didn't find much information on the On-Bright manufacturer's website, I tried to contact them but I don't know if they will answer me.

On the other hand, I found two projects that allow you to develop a program and burn the chip.

- Example program:
- - [RF-Bridge_OB38S003 ](https://github.com/rtek1000/RF-Bridge_OB38S003)

- Chip Burner using NodeMCU:
- - [OnbrightFlasher_OB38S003 ](https://github.com/rtek1000/OnbrightFlasher_OB38S003)
 
-----

When I purchased this model of PAN TILT unit, it was not specified in the advertisement that the communication speed was only 2400 baud.

After the device arrived, I went to research more details, and found other ads, some with 9600 baud models, others with 2400 baud models.

And the camera that will be mounted with this unit can only send PELCO D data at 9600 baud speed.

-----

![img](https://raw.githubusercontent.com/rtek1000/OB38S003-PANTILT-UNIT-FOR-CAMERA/refs/heads/main/SDCC/Schematic1.png)

I started to write a program for PIC16F648A, and tried to port it to OB38S003. But I had difficulties to activate the P1.5 pin (shared with RESET).

Unfortunately, the oscilloscope probe slipped between pin 1 (VCC 12V) and pin 2 (ENABLE) of IC U9, which caused pin P0.4 (pin 19) of the OB38S003 microcontroller to burn out. Despite this, other parts of the IC continue to function, but I am no longer confident in continuing the program with this board, and will return to work on the board with the uC PIC.

The program is still unfinished and is missing the PRESET, EEPROM, MOTOR parts. What works is the TIMER, UART (to receive Pelco D commands).

- sdcc --version
SDCC : mcs51/z80/z180/r2k/r2ka/r3ka/sm83/tlcs90/ez80_z80/z80n/r800/ds390/pic16/pic14/TININative/ds400/hc08/s08/stm8/pdk13/pdk14/pdk15/mos6502/mos65c02/f8 TD- 4.5.0 #15242 (Linux)
published under GNU General Public License (GPL)

- Eclipse IDE Version: 2024-12 (4.34.0) Build id: 20241128-0757

### Note 
This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

- Please note that this code was adapted from an original code with predefined license.

Reference: https://github.com/mightymos/RF-Bridge-OB38S003/issues/29

-----

### PIC code (MPLAX XC8):

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA



