/*
 * SPDX-License-Identifier: BSD-2-Clause
 * 
 * Copyright (c) 2024 Jonathan Armstrong. All rights reserved.
 * 
 * Modified by RTEK1000: For Pelco D PAN TILT use
 * Date: 02-2025
 * Partial code from: PIC MPLABX project
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright 
 * notice, this list of conditions and the following disclaimer in the 
 * documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#if !defined(TARGET_BOARD_EFM8BB1) && !defined(TARGET_BOARD_OB38S003) && !defined(TARGET_BOARD_EFM8BB1LCB)
#error Please define TARGET_BOARD in makefile
#endif

// printf() requires a decent amount of code space and ram which we would like to avoid
// and printf is not particularly useful once packet format is used
// including will conflict with puts() in uart_software.c
//#include <stdio.h>

// borrowed from area-8051 uni-stc HAL...
#include "delay.h"

// basically just function wrappers for setting pins etc
// not really a complete hardware abstraction layer
#include "hal.h"

//// the classic library for radio packet decoding
//#include "rcswitch.h"
//
//// similar to portisch commands
//#include "state_machine.h"

// generic tick logic independent of controller
//#include "ticks.h"

// hardware specific
#include "timer_interrupts.h"

// ring buffer supported
#include "uart.h"

#include "motor.h"

//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------
volatile uint8_t data_receiv = 0;
volatile uint8_t buffer_index1 = 0;
volatile uint8_t buffer_index2 = 0;
volatile uint8_t buffer_data0[BUFFER_SIZE] = { 0 };
volatile uint8_t buffer_data1[BUFFER_SIZE] = { 0 };
volatile uint8_t buffer_data2[BUFFER_SIZE] = { 0 };
volatile uint8_t buffer_data3[BUFFER_SIZE] = { 0 };
volatile uint8_t buffer_data4[BUFFER_SIZE] = { 0 };

volatile _Bool buffer_ready[BUFFER_ARRAY] = { 0 };

volatile uint8_t header_cnt = 0;

volatile uint8_t timeout_receiv = 0;

volatile _Bool preset_enabled = MOTOR_DISABLED;

volatile _Bool pan_enabled = MOTOR_DISABLED;
volatile _Bool pan_direction = MOVE_CC;
volatile uint8_t pan_speed = 0;
volatile uint8_t pan_speed_old = 0;
volatile uint16_t pan_counter = 0;

volatile _Bool tilt_enabled = MOTOR_DISABLED;
volatile _Bool tilt_direction = MOVE_CC;
volatile uint8_t tilt_speed = 0;
volatile uint8_t tilt_speed_old = 0;
volatile uint16_t tilt_counter = 0;

volatile uint8_t pan_step_phase = 0;
volatile uint8_t tilt_step_phase = 0;

volatile uint8_t timer1_pan = 0;
volatile uint8_t timer1_tilt = 0;
volatile uint8_t timer1_pan_ref = 0;
volatile uint8_t timer1_tilt_ref = 0;

volatile uint8_t is_preset = 0;

uint8_t alarms_data = 0;

uint8_t frame_index = 0;
uint8_t frame_data[7] = { 0 };

uint8_t header_pos = 0;

//uint8_t cmd_type = CMD_STOP;
uint8_t response_type = RESP_NONE; // RESP_NONE

uint8_t P_addr = 0;
uint8_t P_cmd1 = 0;
uint8_t P_cmd2 = 0;
uint8_t P_dat1 = 0;
uint8_t P_dat2 = 0;
uint8_t P_chksum = 0;

uint8_t preset_id = 0;

extern volatile uint8_t is_motor_init;

// since the uart pins are used for communication with ESP8265
// it is helpful to have serial output on another pin (e.g., reset pin)
//#include "uart_software.h"

// a rough way of setting a blink period
// set a threshold
// about every six seconds @ 24500000 MHz
//#define HEARTBEAT_THRESHOLD 0x80000

// sdccman sec. 3.8.1 indicates isr prototype must appear or be included in the file containing main
// it is probably more proper to achieve this through include files but also easy to omit
// and then things just will not work with no clear reason why, even though compilation is succcessful
//#if defined(TARGET_BOARD_OB38S003)
// for software uart
// FIXME: if reset pin is set to reset function, instead of gpio, does this interfere with anything (e.g., software serial?)
//extern void tm0(void)        __interrupt (d_T0_Vector);
// supports timeout
extern void timer0_isr(void)
__interrupt (d_T0_Vector);
// pca like capture mode for radio decoding
//    extern void timer2_isr(void) __interrupt (d_T2_Vector);
// hardware uart
extern void uart_isr(void)
__interrupt (d_UART0_Vector);

//#elif defined(TARGET_BOARD_EFM8BB1) || defined(TARGET_BOARD_EFM8BB1LCB)
//
//    // software uart
//    //extern void tm0(void)        __interrupt (TIMER0_VECTOR);
//    // supports timeout
//    extern void timer2_isr(void) __interrupt (TIMER2_VECTOR);
//    // hardware uart (uses timer 1)
//    extern void uart_isr(void)   __interrupt (UART0_VECTOR);
//    // radio decoding
//    extern void pca0_isr(void)   __interrupt (PCA0_VECTOR);
//
//    // unique ID is stored in xram (MSB at address 0xFF)
//    //#define ID0_ADDR_RAM 0xFF
//    //#define ID1_ADDR_RAM 0xFE
//    //#define ID2_ADDR_RAM 0xFD
//    //#define ID3_ADDR_RAM 0xFC
//
//    // this will fail if we assign external ram to values which are initialized
//    // and we really do not need the feature anyway
//    //void startup_uid(void)
//    //{
//    //  puthex2(*((__xdata unsigned char*) ID0_ADDR_RAM));
//    //  puthex2(*((__xdata unsigned char*) ID1_ADDR_RAM));
//    //  puthex2(*((__xdata unsigned char*) ID2_ADDR_RAM));
//    //  puthex2(*((__xdata unsigned char*) ID3_ADDR_RAM));
//    //}
//
//#else
//    #error Please define TARGET_BOARD in makefile
//#endif

//-----------------------------------------------------------------------------
// FIXME: this is sometimes needed to initialize external ram, setup watch dog timer, etc.
//-----------------------------------------------------------------------------
void __sdcc_external_startup(void) {

}

//#if 0
//    void startup_debug(const __idata unsigned char* stackStart)
//    {
//        // just demonstrate serial uart is working basically
//        printf_fast("Startup...\r\n");
//
//        printf_fast("Start of stack: %p\r\n", stackStart);
//
//        //printf_fast("num. of protocols: %u\r\n", numProto);
//
//        // DEBUG: demonstrates that we cannot write above SP (stack pointer)
//        //*gStackStart       = 0x5a;
//        //*(gStackStart + 1) = 0x5a;
//        //printf_fast("gStackStart[%p]: 0x%02x\r\n", gStackStart,   *gStackStart);
//        //printf_fast("gStackStart[%p]: 0x%02x\r\n", gStackStart+1, *(gStackStart + 1));
//    }
//#endif

// buzzer
//void startup_beep(void)
//{
//    // FIXME: startup beep helpful or annoying?
//    buzzer_on();
//    delay1ms(20);
//    buzzer_off();
//}

// led
void startup_blink(void)
{
    // double blink
    led_off();
    delay1ms(250);

    led_on();
    delay1ms(250);

    led_off();
    delay1ms(250);

    led_on();
    delay1ms(250);
}

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main(void) {
	// just track how many loops have transpired as a rough way of tracking time
	//uint32_t ticks = HEARTBEAT_THRESHOLD;

	// upper eight bits hold error or no data flags
	unsigned int rxdataWithFlags = UART_NO_DATA;

	// allows communication between uart state machine and radio state machine
//    RF_COMMAND_T rfCommand;

	delay1ms(500);

	// hardware initialization
	set_clock_mode(); // 16MHz

//#if defined(TARGET_BOARD_OB38S003)
	init_port_pins();
//#elif defined(TARGET_BOARD_EFM8BB1) || defined(TARGET_BOARD_EFM8BB1LCB)
//    // the crossbar on this microcontroller makes initialization more complicated
//    init_port_pins_for_serial();
//#else
//    #error Please define TARGET_BOARD in makefile
//#endif

	// set default pin levels
//    led_off();
//    buzzer_off();
//    tdata_off();

	// DEBUG:
	// on some boards, "debug pin" is actually buzzer so we do not want to use it for debugging unless buzzer has been removed
	//debug_pin01_off();

	//

//	while (true) {
//	    startup_blink();
//	}

	startup_blink();

    // setup hardware serial
	// timer 1 is clock source for uart0 on efm8bb1
	// should call these after initializing port pins
	init_uart();
	uart_rx_enabled();

	// hardware serial interrupt
	init_serial_interrupt();
	enable_serial_interrupt();

	init_timer0_8bit_autoreload();
	init_first_delay_ms(0);

	enable_timer0_interrupt();

//#if 0
//    // software serial
//    // default state is reset/pin1 high if using software uart as transmit pin
//    soft_tx_pin_on();
//
//    // allows use of a gpio to output text characters for debugging hardware uart is assigned for communicating with esp8285
//    init_software_uart();
//#endif

//#if defined(TARGET_BOARD_OB38S003)
	// timer 0 provides one millisecond tick or supports software uart
	// at various times during development timer 0 has been used to support software uart
	//init_timer0(SOFT_BAUD);

	// supports microseconds and milliseconds delays respectively
	// init_timer0_8bit_autoreload();
	// init_timer0_8bit_autoreload();

	// timer 2 supports compare and capture module
	// for determining pulse lengths of received radio signals
	// init_timer2_as_capture();

	//
	// enable_timer0_interrupt();
	//enable_timer1_interrupt();
	//enable_timer2_interrupt();
//#elif defined(TARGET_BOARD_EFM8BB1) || defined(TARGET_BOARD_EFM8BB1LCB)
//    // pca used timer0 in stock portisch (why?), however rcswitch can use dedicated pca counters
//    // at various times during development timer 0 has been used to support software uart
//    //init_timer0(SOFT_BAUD);
//    // uart must use timer1 on this controller
//    init_timer1_8bit_autoreload(TIMER1_UART0);
//    timer1_run();
//
//    // timer 2 is used on demand to produce delays (i.e., time enabled at start, wait, then timer stopped at overflow)
//    // however, we initialize reload value when using delay so nothing to initialize at this step
//    //init_timer2(TIMER2_RELOAD_10MICROS);
//
//    // timer 3 is unused for now
//
//    //enable_timer0_interrupt();
//    //enable_timer1_interrupt();
//    enable_timer2_interrupt();
//
//    // there are two interrupts required enabled to perform edge capture
//    enable_pca0_interrupt();
//
//    // pca0 clock source was timer 0 on portisch
//    // however we use system clock divided by 12 as source here
//    pca0_init();
//    pca0_run();
//#endif

	// radio receiver edge detection
	// enable_capture_interrupt();

	// enable interrupts
	enable_global_interrupts();

	uart_write_Text("Start\r\n");

	motor_init();

	uart_write_Text("Initialized.\r\n");

//#if defined(TARGET_BOARD_OB38S003)
//    // FIXME: function empty on efm8bb1, because unknown if receiver has enable pin
//    radio_receiver_on();
//#endif

	//startup_beep();
	//startup_debug(stackStart);
//    startup_blink();
	//startup_reset_status();

	// just to give some startup time
//    delay1ms(500);

	// watchdog will force a reset, unless we periodically write to it, demonstrating loop is not stuck somewhere
	// enable_watchdog();

//#if 0
//    // demonstrate software uart is working
//    putstring("boot\r\n");
//#endif

//#if defined(TARGET_BOARD_EFM8BB1) || defined(TARGET_BOARD_EFM8BB1LCB)
//  putstring("uid:");
//  startup_uid();
//  putstring("\r\n");
//#endif

	while (true) {

		// if this is not periodically called, watchdog will force microcontroller reset
		// refresh_watchdog();

		if (buffer_ready[frame_index] == 1) {
			buffer_ready[frame_index] = 0;

			for (uint8_t i = 0; i < 7; i++) {
				if (frame_index == 0) {
					frame_data[i] = buffer_data0[i];
				} else if (frame_index == 1) {
					frame_data[i] = buffer_data1[i];
				} else if (frame_index == 2) {
					frame_data[i] = buffer_data2[i];
				} else if (frame_index == 3) {
					frame_data[i] = buffer_data3[i];
				} else if (frame_index == 4) {
					frame_data[i] = buffer_data4[i];
				}
			}

			if (frame_data[0] == P_SYNC) {
				uint8_t chksum_calc = 0;

				for (uint8_t m = 1; m <= 5; m++) {
					chksum_calc += frame_data[m];
				}

				if (chksum_calc == frame_data[6]) {
					// Save data frame
					P_addr = frame_data[1];
					P_cmd1 = frame_data[2];
					P_cmd2 = frame_data[3];
					P_dat1 = frame_data[4];
					P_dat2 = frame_data[5];
					P_chksum = frame_data[6];

					response_type = RESP_NONE;

					// decode command
					if (P_addr == DEVICE_ADDR) {
						if ((P_cmd1 == 0x00) && (P_cmd2 == 0x67)
								&& (P_dat1 == 0x00)) {
							// Set Remote Baud Rate (Ref.: FUJIFILM SX800)
							uart_write_Text("SET BAUD RATE ");

							if (P_dat2 == 0x00) {
								// 2400
								uart_write_Text("2400\r\n");
							} else if (P_dat2 == 0x01) {
								// 4800
								uart_write_Text("4800\r\n");
//                            } else if (P_dat2 == 0x02) {
//                                // 9600 (default)
//                                uart_write_Text("9600\r\n");
							} else if (P_dat2 == 0x03) {
								// 19200
								uart_write_Text("19200\r\n");
							} else if (P_dat2 == 0x04) {
								// 38400
								uart_write_Text("38400\r\n");
							} else if (P_dat2 == 0x05) {
								// 115200
								uart_write_Text("115200\r\n");
							} else {
								// 9600 (default)
								uart_write_Text("9600\r\n");
							}
						} else if ((P_cmd1 == 0x00) && (P_cmd2 == 0x00)
								&& (P_dat1 == 0x00) && (P_dat2 == 0x00)) {
							//pan_enabled = MOTOR_DISABLED;
							//tilt_enabled = MOTOR_DISABLED;
							motor1_disable();
							motor2_disable();
							response_type = RESP_GENERAL;
							uart_write_Text("STOP\r\n");
						} else if ((P_cmd1 == 0x00) && (P_cmd2 == PRESET_SET)
								&& (P_dat1 == 0x00)) {
							preset_id = P_dat2;
							response_type = RESP_GENERAL;
							uart_write_Text("SET PRESET\r\n");
						} else if ((P_cmd1 == 0x00) && (P_cmd2 == PRESET_CLEAR)
								&& (P_dat1 == 0x00)) {
							preset_id = P_dat2;
							response_type = RESP_GENERAL;
							uart_write_Text("CLEAR PRESET\r\n");
						} else if ((P_cmd1 == 0x00) && (P_cmd2 == PRESET_GOTO)
								&& (P_dat1 == 0x00)) {
							preset_id = P_dat2;
							preset_enabled = MOTOR_ENABLED;
							response_type = RESP_GENERAL;
							uart_write_Text("GOTO PRESET\r\n");
						} else {
							if ((P_cmd2 & MOVE_LEFT) == MOVE_LEFT) {
								//pan_speed = P_dat1;
								motor1_set_speed(P_dat1);
								//pan_direction = MOVE_CC;
								motor1_set_dir(MOVE_CC);
								//pan_enabled = MOTOR_ENABLED;
								motor1_enable();
								response_type = RESP_GENERAL;
								uart_write_Text("LEFT\r\n");
							} else if ((P_cmd2 & MOVE_RIGHT) == MOVE_RIGHT) {
								//pan_speed = P_dat1;
								motor1_set_speed(P_dat1);
								//pan_direction = MOVE_CCW;
								motor1_set_dir(MOVE_CCW);
								//pan_enabled = MOTOR_ENABLED;
								motor1_enable();
								response_type = RESP_GENERAL;
								uart_write_Text("RIGHT\r\n");
							}

							if ((P_cmd2 & MOVE_DOWN) == MOVE_DOWN) {
								// tilt_speed = P_dat2;
								motor2_set_speed(P_dat2);

								//tilt_direction = MOVE_CC;
								motor2_set_dir(MOVE_CC);

								//tilt_enabled = MOTOR_ENABLED;
								motor2_enable();
								response_type = RESP_GENERAL;
								uart_write_Text("DOWN\r\n");
							} else if ((P_cmd2 & MOVE_UP) == MOVE_UP) {
								//tilt_speed = P_dat2;
								motor2_set_speed(P_dat2);
								//tilt_direction = MOVE_CCW;
								motor2_set_dir(MOVE_CCW);
								//tilt_enabled = MOTOR_ENABLED;
								motor2_enable();
								response_type = RESP_GENERAL;
								uart_write_Text("UP\r\n");
							}
						}
					}

					if (response_type == RESP_GENERAL) {
						//SEND_resp_general(P_chksum);
					}
				}
			}
		} else {
			if (frame_index < 4) { // if (frame_index < (BUFFER_ARRAY - 1)) {
				frame_index++;
			} else {
				frame_index = 0;
			}
		}

	}

}
