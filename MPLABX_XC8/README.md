This folder has two projects, one is the Pelco D protocol generator, the other is the receiver, both with PIC16F648A, but the code is written in C for XC8, and can be easily adapted to other microcontroller models.

- About the motor, there are two types, bipolar with 4 wires (which comes inside the unit mentioned here, in this repository) and the 5 wire motor type (which usually comes inside low cost cameras with PAN TILT movements). The motors in this unit are similar to the Yoosee camera motor and those sold for use with Arduino, but the shaft is different. However, the body and gear are compatible. For the circuit version with PIC, I left the driver for 5 wires. (With the OB38S003 board, despite having the 5-pin connector, only 4 pins are used). This way I changed the motor coil, so I could take advantage of the ULN2803 driver that I already had on hand.

The main idea is to store all valid frames. It must start with 0xFF and be 7 bytes long. The time limit is 10ms (15ms to have better tolerance), after which the frame is discarded. Considering the speed of 9600 bauds and it was the camera that generated this timing pattern. Other devices may generate different times.

![img](https://raw.githubusercontent.com/rtek1000/OB38S003-PANTILT-UNIT-FOR-CAMERA/refs/heads/main/Img/1.png)

In the VMS program (XMEye) the data is sent with speed from 1 to 8, but the camera I was testing could send PTZ speed data from 1 to 10.

The interval between each byte is 1ms, and the interval between each frame is at least 19ms.

![img](https://raw.githubusercontent.com/rtek1000/OB38S003-PANTILT-UNIT-FOR-CAMERA/refs/heads/main/Img/Space_1ms.png)

![img](https://raw.githubusercontent.com/rtek1000/OB38S003-PANTILT-UNIT-FOR-CAMERA/refs/heads/main/Img/Space_19ms.png)


-----

Codes noted using the[ Hercules SETUP utility ](https://www.hw-group.com/software/hercules-setup-utility)program:

- Note that only the VMS program sent combined keys (diagonal).

Website (camera)

Stop:
{FF}{01}{00}{00}{00}{00}{01}

Up:
- {FF}{01}{00}{08}{00}{06}{0F} (step 1)
- {FF}{01}{00}{08}{00}{0C}{15} (step 2)
- {FF}{01}{00}{08}{00}{12}{1B} (step 3)
- {FF}{01}{00}{08}{00}{19}{22} (step 4)
- {FF}{01}{00}{08}{00}{1F}{28} (step 5)
- {FF}{01}{00}{08}{00}{25}{2E} (step 6)
- {FF}{01}{00}{08}{00}{2C}{35} (step 7)
- {FF}{01}{00}{08}{00}{32}{3B} (step 8)
- {FF}{01}{00}{08}{00}{38}{41} (step 9)
- {FF}{01}{00}{08}{00}{3F}{48} (step 10)

Dn:
- {FF}{01}{00}{10}{00}{06}{17} (step 1)

L:
- {FF}{01}{00}{04}{06}{00}{0B} (step 1)

R:
- {FF}{01}{00}{02}{06}{00}{09} (step 1)

Zoom+:
- {FF}{01}{00}{20}{00}{00}{21}

Zoom-:
- {FF}{01}{00}{40}{00}{00}{41}

Focus+:
- {FF}{01}{01}{00}{00}{00}{02}

Focus-:
- {FF}{01}{00}{80}{00}{00}{81}

Iris+:
- {FF}{01}{02}{00}{00}{00}{03}

Iris-:
- {FF}{01}{04}{00}{00}{00}{05}

Preset1 (set):
- {FF}{01}{00}{03}{00}{01}{05}

Preset1 (goto):
- {FF}{01}{00}{07}{00}{01}{09}

Preset1 (erase):
- {FF}{01}{00}{05}{00}{01}{07}

Preset2 (set):
- {FF}{01}{00}{03}{00}{02}{06}

Preset2 (goto):
- {FF}{01}{00}{07}{00}{02}{0A}

Preset2 (erase):
- {FF}{01}{00}{05}{00}{02}{08}

-----

VMS (XMEye Windows)
Stop:
- {FF}{01}{00}{00}{00}{00}{01}

Up:
- {FF}{01}{00}{08}{00}{06}{0F} (step 1) [06: 06]
- {FF}{01}{00}{08}{00}{0C}{15} (step 2) [0C: 12]
- {FF}{01}{00}{08}{00}{12}{1B} (step 3) [12: 18]
- {FF}{01}{00}{08}{00}{19}{22} (step 4) [19: 25]
- {FF}{01}{00}{08}{00}{1F}{28} (step 5) [1F: 31]
- {FF}{01}{00}{08}{00}{25}{2E} (step 6) [25: 37]
- {FF}{01}{00}{08}{00}{2C}{35} (step 7) [2C: 44]
- {FF}{01}{00}{08}{00}{32}{3B} (step 8) [32: 50]

Dn:
- {FF}{01}{00}{10}{00}{06}{17} (step 1)

L:
- {FF}{01}{00}{04}{06}{00}{0B} (step 1)

R:
- {FF}{01}{00}{02}{06}{00}{09} (step 1)

Up-L: (step 1)
- {FF}{01}{00}{04}{06}{00}{0B}   {FF}{01}{00}{08}{00}{06}{0F}

Up-R: (step 1)
- {FF}{01}{00}{02}{06}{00}{09}   {FF}{01}{00}{08}{00}{06}{0F}

Dn-L: (step 1)
- {FF}{01}{00}{04}{06}{00}{0B}   {FF}{01}{00}{10}{00}{06}{17}

Dn-R: (step 1)
- {FF}{01}{00}{02}{06}{00}{09}   {FF}{01}{00}{10}{00}{06}{17}

Zoom+:
- {FF}{01}{00}{20}{00}{00}{21}

Zoom-:
- {FF}{01}{00}{40}{00}{00}{41}

Focus+:
- NONE (BUG)

Focus-:
- NONE (BUG)

Iris+:
- NONE (BUG)

Iris-:
- NONE (BUG)

Preset1 (set):
- {FF}{01}{00}{03}{00}{01}{05}

Preset1 (goto):
- {FF}{01}{00}{07}{00}{01}{09}

Preset1 (erase):
- NONE (BUG)

Preset2 (set):
- {FF}{01}{00}{03}{00}{02}{06}

Preset2 (goto):
- {FF}{01}{00}{07}{00}{02}{0A}

Preset2 (erase):
- NONE (BUG)
