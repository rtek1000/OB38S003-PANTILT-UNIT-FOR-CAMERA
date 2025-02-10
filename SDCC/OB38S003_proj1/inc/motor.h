/*
 * motor.h
 *
 *  Created on: 9 de fev. de 2025
 *      Author: RTEK1000
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include <stdint.h>
#include <stdbool.h>

#define MOTOR_CC false
#define MOTOR_CCW true

#define SPEED_MAX_REF 0x32
#define SPEED_MIN_REF 0x06

#define SPEED_MAX_TMR 1  // 0-1  (2)
#define SPEED_MIN_TMR 19 // 0-19 (20)

#define RESP_NONE 0x00
#define RESP_GENERAL 0x01

#define MOVE_CC false
#define MOVE_CCW true

#define MOTOR_ENABLED true
#define MOTOR_DISABLED false

void motor_init(void);

void motor1_enable(void);
void motor1_disable(void);
void motor2_enable(void);
void motor2_disable(void);

void motor1_set_speed(uint8_t speed);
void motor2_set_speed(uint8_t speed);
uint8_t motor_speed_calc(uint8_t speed);

void motor1_set_dir(uint8_t dir);
void motor2_set_dir(uint8_t dir);

void motor1_step_cc(void);
void motor1_step_ccw(void);
void motor2_step_cc(void);
void motor2_step_ccw(void);


#endif /* INC_MOTOR_H_ */
