#include "OB38S003.h"
#include "motor.h"
#include "delay.h"
#include "uart.h"
#include "pan_tilt_cam_pins.h"

volatile uint8_t is_motor_init = 0;

uint8_t mot1_step = 0;
uint8_t mot2_step = 0;

uint8_t mot1_enabled = 0;
uint8_t mot2_enabled = 0;

uint8_t mot1_direction = MOTOR_CC;
uint8_t mot2_direction = MOTOR_CC;

uint8_t mot1_speed = 0; // relative to timer0
uint8_t mot2_speed = 0; // relative to timer0

uint8_t mot1_speed_old = 0; // relative to timer0
uint8_t mot2_speed_old = 0; // relative to timer0

uint8_t mot1_speed_tmr = 200; // relative to timer0
uint8_t mot2_speed_tmr = 200; // relative to timer0

uint16_t mot1_cnt1 = 0; // required for preset
uint16_t mot2_cnt1 = 0; // required for preset

const uint8_t speed_ref[8] = { 0x06, 0x0C, 0x12, 0x19, 0x1F, 0x25, 0x2C, 0x32 };

const _Bool steps_phase_1[4] = {1, 0, 0, 1};
const _Bool steps_phase_2[4] = {1, 1, 0, 0};

extern volatile uint8_t is_preset;

static void motor1_output(void);
static void motor2_output(void);

void motor_init(void) {
	is_motor_init = 1;

	motor1_set_speed(SPEED_MAX_REF);

	//mot1_enabled = MOTOR_ENABLED;
	motor1_enable();

	//mot1_direction = MOVE_CCW;
	motor1_set_dir(MOVE_CCW);

	uart_write_Text("Motor 1: go to home, wait...\r\n");

	delay1ms(5000);

	//mot1_enabled = MOTOR_DISABLED;
	motor1_disable();

	mot1_cnt1 = 0;

	motor2_set_speed(SPEED_MAX_REF);

	// mot2_enabled = MOTOR_ENABLED;
	motor2_enable();

	// mot2_direction = MOVE_CCW;
	motor2_set_dir(MOVE_CCW);

	uart_write_Text("Motor 2: go to home, wait...\r\n");

	delay1ms(5000);

	//mot2_enabled = MOTOR_DISABLED;
	motor2_disable();

	mot2_cnt1 = 0;

	is_motor_init = 0;
}

void motor1_enable(void) {
	mot1_enabled = true;

	MOT1EN = mot1_enabled;
}

void motor1_disable(void) {
	mot1_enabled = false;

	MOT1EN = mot1_enabled;
}

void motor2_enable(void) {
	mot2_enabled = true;

	MOT2EN = mot2_enabled;
}

void motor2_disable(void) {
	mot2_enabled = false;

	MOT2EN = mot2_enabled;
}

void motor1_set_speed(uint8_t speed) {
	mot1_speed = speed;

	mot1_speed_tmr = motor_speed_calc(mot1_speed);
}

void motor2_set_speed(uint8_t speed) {
	mot2_speed = speed;

	mot2_speed_tmr = motor_speed_calc(mot2_speed);
}

uint8_t motor_speed_calc(uint8_t speed) {
	uint8_t sp_calc = 0;

	if (speed > SPEED_MAX_REF) {
		speed = SPEED_MAX_REF;
	}

	if (speed < SPEED_MIN_REF) {
		speed = SPEED_MIN_REF;
	}

	sp_calc = SPEED_MAX_TMR + ((SPEED_MAX_REF - speed) / 2);

	if (sp_calc < SPEED_MAX_TMR) {
		sp_calc = SPEED_MAX_TMR;
	}

	if (sp_calc > SPEED_MIN_TMR) {
		sp_calc = SPEED_MIN_TMR;
	}

	return sp_calc;
}

void motor1_set_dir(uint8_t dir) {
	mot1_direction = dir;
}

void motor2_set_dir(uint8_t dir) {
	mot2_direction = dir;
}

void motor1_step_cc(void) {
	if (mot1_cnt1 < 65535) {
		mot1_cnt1++;

		if (mot1_step < 3) {
			mot1_step++;
		} else {
			mot1_step = 0;
		}

		motor1_output();
	}
}

void motor1_step_ccw(void) {
	if (mot1_cnt1 > 0) {
		mot1_cnt1--;

		if (mot1_step > 0) {
			mot1_step--;
		} else {
			mot1_step = 3;
		}

		motor1_output();
	}
}

static void motor1_output(void) {
	MOT1PA = steps_phase_1[mot1_step];
	MOT1PB = steps_phase_2[mot1_step];
}

void motor2_step_cc(void) {
	if (mot2_step < 3) {
		mot2_step++;
	} else {
		mot2_step = 0;
	}

	motor2_output();
}

void motor2_step_ccw(void) {
	if (mot2_step > 0) {
		mot2_step--;
	} else {
		mot2_step = 0;
	}

	motor2_output();
}

static void motor2_output(void) {
	MOT2PA = steps_phase_1[mot1_step];
	MOT2PB = steps_phase_2[mot1_step];
}
