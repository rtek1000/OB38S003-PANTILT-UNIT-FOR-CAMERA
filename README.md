# PANTILT UNIT FOR CAMERA (uC OB38S003)

This PAN TILT positioner model may have a board with the OB38S003W20 microcontroller (On-Bright). Apparently the chassis was created for a larger board, perhaps to use another type of microcontroller.

- It may be important to check the speed of the device before purchasing, the standard is 9600, but some sellers sell 2400 baud devices without warning.

- The connection is RS485, no response, only receiving commands.

![img](https://raw.githubusercontent.com/rtek1000/OB38S003-PANTILT-UNIT-FOR-CAMERA/refs/heads/main/Img/Ad3.jpg)

-----

I didn't find much information on the [On-Bright manufacturer's website](https://www.on-bright.com/en/index/product/detail/cid/126/id/375.shtml), I tried to contact them but I don't know if they will answer me.

But I found this warning:
> Note: Factory default settings
>
> RST/P1.5 is set as a normal bidirectional I/O (P1.5) pin at the factory. If the user needs to switch to a reset pin, this pin can be defined as the RESET pin during programming
>
> To avoid accidentally entering the ISP programming state (refer to Unit 18.4), make sure there is no continuous pulse signal on the RXD P1.1 pin and the P1.6 pin must be set high when powering on
>
> OSI_SDA/P1.3 and OCI_SCL/P1.2 are ICP programming function pins during reset, and switch to bidirectional I/O after reset is completed.

On the other hand, I found two projects that allow you to develop a program and burn the chip.

- Example program:
- - [RF-Bridge_OB38S003 ](https://github.com/rtek1000/RF-Bridge_OB38S003)

- Chip Burner using NodeMCU:
- - [OnbrightFlasher_OB38S003 ](https://github.com/rtek1000/OnbrightFlasher_OB38S003)

If you need sample codes, you can find them in the Codzard program:

![img](https://raw.githubusercontent.com/rtek1000/OB38S003-PANTILT-UNIT-FOR-CAMERA/refs/heads/main/Img/Codzard.png)

If it is necessary to modify the fuses, it may be necessary to use the MSM9066 programmer for greater ease:

![img](https://raw.githubusercontent.com/rtek1000/OB38S003-PANTILT-UNIT-FOR-CAMERA/refs/heads/main/Img/SMAP%20AC.png)

I found this ad from the programmer:
https://www.aliexpress.com/item/1005007667412447.html

![img](https://raw.githubusercontent.com/rtek1000/OB38S003-PANTILT-UNIT-FOR-CAMERA/refs/heads/main/Img/MSM9066_ad.png)

-----

-----

When I purchased this model of PAN TILT unit, it was not specified in the advertisement that the communication speed was only 2400 baud.

After the device arrived, I went to research more details, and found other ads, some with 9600 baud models, others with 2400 baud models.

And the camera that will be mounted with this unit can only send PELCO D data at 9600 baud speed.

-----

![img](https://raw.githubusercontent.com/rtek1000/OB38S003-PANTILT-UNIT-FOR-CAMERA/refs/heads/main/Img/Schematic_PANTILT.png)

I started to write a program for PIC16F648A, and tried to port it to OB38S003. But I had difficulties to activate the P1.5 pin (shared with RESET).

Unfortunately, the oscilloscope probe slipped between pin 1 (VCC 12V) and pin 2 (ENABLE) of IC U9, which caused pin P0.4 (pin 19) of the OB38S003 microcontroller to burn out. Despite this, other parts of the IC continue to function, but I am no longer confident in continuing the program with this board, and will return to work on the board with the uC PIC.

The program is still unfinished and is missing the PRESET, EEPROM, MOTOR parts. What works is the TIMER, UART (to receive Pelco D commands).

- [SDCC 4.5.0 #15242 (Linux)](https://sourceforge.net/projects/sdcc/files/sdcc/4.5.0/)

- [Eclipse IDE Version: 2024-12 (4.34.0) Build id: 20241128-0757](https://download.eclipse.org/eclipse/downloads/)

### Note 
This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

- Please note that this code was adapted from an original code with predefined license.

Reference: https://github.com/mightymos/RF-Bridge-OB38S003/issues/29

-----

### PIC code (MPLAX XC8):

This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with this library; if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA



