/*
 * pan_tilt_cam_pins.h
 *
 *  Created on: 9 de fev. de 2025
 *      Author: RTEK1000
 */

#ifndef INC_PAN_TILT_CAM_PINS_H_
#define INC_PAN_TILT_CAM_PINS_H_

// hardware uart
#define UART_TX_PIN P1_0
#define UART_RX_PIN P1_1

#define LED P1_0

// reset pin is connected to copper pad so can use as a debug output
// need to set as gpio in SMAP AC utility when flashing (i.e., disable reset function)
// can be used with software uart
// #define RESET_PIN P1_5 // as GPIO

//

#define MOT1EN P1_5
#define MOT1PA P1_6
#define MOT1PB P1_7

#define MOT2EN P0_4
#define MOT2PA P0_5
#define MOT2PB P0_7

#endif
