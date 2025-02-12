/*
 * File:   main.c
 * Author: RTEK1000
 *
 * Created on 29 de Janeiro de 2025, 19:13
 * 
 * Pelco D 9600 receiver
 * 
 * Stop: {FF}{01}{00}{00}{00}{00}{01}
 * 
 * Max PRESET: 50
 * 
 */

#include "main.h"
#include "usart.h"

#define MOT_PAN_1A PORTAbits.RA0
#define MOT_PAN_1B PORTAbits.RA7
#define MOT_PAN_2A PORTAbits.RA6
#define MOT_PAN_2B PORTAbits.RA1

#define UC_LED PORTBbits.RB3

#define MOT_TILT_1A PORTBbits.RB4
#define MOT_TILT_1B PORTBbits.RB5
#define MOT_TILT_2A PORTBbits.RB6
#define MOT_TILT_2B PORTBbits.RB7

#define DEVICE_ADDR 0x01

#define EEPROM_BAUD_ADDR 0xFF // EEPROM BAUD addr: 255; PIC16F648 EEPROM: 256B;
#define PRESET_MAX 50 // PIC16F648 EEPROM: 256B; Preset size: 4 Bytes; 256 / 4 = 64;

#define PRESET_SET 0x03
#define PRESET_CLEAR 0x05
#define PRESET_GOTO 0x07

#define MOVE_RIGHT 0x02
#define MOVE_LEFT 0x04
#define MOVE_UP 0x08
#define MOVE_DOWN 0x10

#define RESP_NONE 0x00
#define RESP_GENERAL 0x01

#define MOVE_CC false
#define MOVE_CCW true

#define MOTOR_ENABLED true
#define MOTOR_DISABLED false

#define BUFFER_ARRAY 5
#define BUFFER_SIZE 7
#define P_SYNC 0xFF
#define NO_HEADER 0xFE

#define SPEED_MAX_REF 0x32
#define SPEED_MIN_REF 0x06

#define SPEED_MAX_TMR 1  // 0-1  (2)
#define SPEED_MIN_TMR 19 // 0-19 (20)

#define PAN_STROKE_LIMIT_STEPS 11700 // Mechanical stroke limit
#define TILT_STROKE_LIMIT_STEPS 2300 // Mechanical stroke limit

volatile uint8_t data_receiv = 0;
volatile uint8_t buffer_index1 = 0;
volatile uint8_t buffer_index2 = 0;
volatile uint8_t buffer_data0[BUFFER_SIZE] = {0};
volatile uint8_t buffer_data1[BUFFER_SIZE] = {0};
volatile uint8_t buffer_data2[BUFFER_SIZE] = {0};
volatile uint8_t buffer_data3[BUFFER_SIZE] = {0};
volatile uint8_t buffer_data4[BUFFER_SIZE] = {0};
volatile _Bool buffer_ready[BUFFER_ARRAY] = {0};
volatile uint8_t header_cnt = 0;

volatile uint8_t timeout_receiv = 0;
volatile uint8_t timeout_uart1 = 0;
volatile uint8_t timeout_uart2 = 0;
volatile uint8_t timeout_uart3 = 0;

volatile _Bool preset_pan_enabled = MOTOR_DISABLED;
volatile _Bool preset_pan_enabled_old = MOTOR_DISABLED;

volatile _Bool preset_tilt_enabled = MOTOR_DISABLED;
volatile _Bool preset_tilt_enabled_old = MOTOR_DISABLED;

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

volatile uint16_t pan_goto = 0;
volatile uint16_t tilt_goto = 0;

uint8_t frame_index = 0;
uint8_t frame_data[7] = {0};

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

uint8_t alarms_data = 0;

_Bool is_reboot = 0;

_Bool is_init = 0;

const _Bool steps_1A[8] = {1, 1, 0, 0, 0, 0, 0, 1};
const _Bool steps_1B[8] = {0, 1, 1, 1, 0, 0, 0, 0};
const _Bool steps_2A[8] = {0, 0, 0, 1, 1, 1, 0, 0};
const _Bool steps_2B[8] = {0, 0, 0, 0, 0, 1, 1, 1};

const uint8_t speed_ref[8] = {0x06, 0x0C, 0x12, 0x19, 0x1F, 0x25, 0x2C, 0x32};

void __interrupt() myISR();
void main(void);
void UC_Init(void);
void TIMER1_Init(void);
void TIMER2_Init(void);
unsigned char CKSM_calc(uint8_t *in_dat);
void SEND_resp_general(uint8_t cmd_cksm);
void delay_wdt(uint16_t _ms);
void MOTOR_Init(void);
uint8_t SPEED_calc(uint8_t speed);
void eeprom_update(uint8_t addr, uint8_t value);
void PRESET_save(uint8_t id, uint16_t pan, uint16_t tilt);
void PRESET_load(uint8_t id, uint16_t *pan, uint16_t *tilt);
void BAUDS_set(uint8_t index);
uint8_t BAUDS_get(void);
void print_cnt(uint16_t _pan, uint16_t _tilt);
void print_val(uint16_t value);
void print_preset(uint8_t id, uint16_t pan, uint16_t tilt, char *text);
void print_cmd_mov(char *text, uint16_t pan, uint16_t tilt);

void __interrupt() myISR() {
    if (PIR1bits.RCIF == 1) {
        data_receiv = RCREG; //UART1_Read();

        timeout_uart1 = 0;
        timeout_uart2 = 0;

        UC_LED = !UC_LED;

        if (is_init == true) {
            return;
        }

        if (data_receiv == P_SYNC) {
            timeout_receiv = 0;
        }

        if ((buffer_index2 <= 6) || ((buffer_index2 == 0) && (data_receiv == P_SYNC))) {
            switch (buffer_index1) {
                case 0:
                    buffer_data0[buffer_index2++] = data_receiv;
                    break;
                case 1:
                    buffer_data1[buffer_index2++] = data_receiv;
                    break;
                case 2:
                    buffer_data2[buffer_index2++] = data_receiv;
                    break;
                case 3:
                    buffer_data3[buffer_index2++] = data_receiv;
                    break;
                case 4:
                    buffer_data4[buffer_index2++] = data_receiv;
                    break;
                default:
                    // statements
                    break;
            }
        }

        if (buffer_index2 == 7) {
            buffer_index2 = 0;

            buffer_ready[buffer_index1] = 1;

            if (buffer_index1 < 4) { // if (buffer_index1 < 4) {
                buffer_index1++;
            } else {
                buffer_index1 = 0;
            }
        }

        PIR1bits.RCIF = 0;
    } else if (PIR1bits.TMR1IF == 1) { // 2Hz @ 4MHz
        // Timer1 Interrupt - Freq = 2.00 Hz - Period = 0.499408 seconds
        PIR1bits.TMR1IF = 0; // interrupt must be cleared by software
        PIE1bits.TMR1IE = 1; // reenable the interrupt
        TMR1H = 12; // preset for timer1 MSB register
        TMR1L = 38; // preset for timer1 LSB register


        PIR1bits.TMR1IF = 0;

        // UC_LED = !UC_LED;

        if (timeout_uart1 < 120) { // 60s: 2Hz * 120; 1 minute
            timeout_uart1++;
        } else {
            timeout_uart1 = 0;

            if (timeout_uart2 < 2) { // UART Timeout 3 minutes: 180s
                timeout_uart2++;
            } else {
                timeout_uart2 = 0;
                
                // (Cannot restart uC without losing home position)
                // Try resetting the UART only:

                RCSTAbits.FERR = 0;
                RCSTAbits.OERR = 0;

                (void) RCREG; // UART_Read();
                (void) RCREG; // UART_Read();

                RCSTAbits.CREN = 0;
                RCSTAbits.SPEN = 0;

                RCSTAbits.CREN = 1;
                RCSTAbits.SPEN = 1;
            }
        }
    } else if (PIR1bits.TMR2IF == 1) { // 1ms @ 4MHz
        PIR1bits.TMR2IF = 0; // clears TMR2IF       bit 1 TMR2IF: TMR2 to PR2 Match Interrupt Flag bit

        if (timeout_receiv < 15) {
            timeout_receiv++;
        } else if (buffer_index2 > 0) {
            buffer_index2 = 0;
        }

        if (timer1_pan < timer1_pan_ref) {
            timer1_pan++;
        } else {
            timer1_pan = 0;

            if (pan_enabled == MOTOR_ENABLED) {
                if (pan_direction == MOVE_CC) {
                    if (pan_counter < (PAN_STROKE_LIMIT_STEPS - 1)) {
                        pan_counter++;

                        if ((pan_step_phase == 0) || (pan_step_phase > 7)) {
                            pan_step_phase = 7;
                        } else {
                            pan_step_phase--;
                        }
                    }
                } else {
                    if ((pan_counter > 0) || (is_init == true)) {
                        pan_counter--;

                        if (pan_step_phase >= 7) {
                            pan_step_phase = 0;
                        } else {
                            pan_step_phase++;
                        }
                    }
                }

                if (pan_goto == pan_counter) {
                    if (preset_pan_enabled == MOTOR_ENABLED) {
                        preset_pan_enabled = MOTOR_DISABLED;

                        pan_enabled = MOTOR_DISABLED;
                    }
                }

                MOT_PAN_1A = steps_1A[pan_step_phase];
                MOT_PAN_1B = steps_1B[pan_step_phase];
                MOT_PAN_2A = steps_2A[pan_step_phase];
                MOT_PAN_2B = steps_2B[pan_step_phase];
            } else {
                MOT_PAN_1A = 0;
                MOT_PAN_1B = 0;
                MOT_PAN_2A = 0;
                MOT_PAN_2B = 0;
            }

            // UC_LED = 0;
        }

        if (timer1_tilt < timer1_tilt_ref) {
            timer1_tilt++;
        } else {
            timer1_tilt = 0;

            if (tilt_enabled == MOTOR_ENABLED) {
                if (tilt_direction == MOVE_CC) {
                    if (tilt_counter < (TILT_STROKE_LIMIT_STEPS - 1)) {
                        tilt_counter++;

                        if ((tilt_step_phase == 0) || (tilt_step_phase > 7)) {
                            tilt_step_phase = 7;
                        } else {
                            tilt_step_phase--;
                        }
                    }
                } else {
                    if ((tilt_counter > 0) || (is_init == true)) {
                        tilt_counter--;

                        if (tilt_step_phase >= 7) {
                            tilt_step_phase = 0;
                        } else {
                            tilt_step_phase++;
                        }
                    }
                }

                if (tilt_goto == tilt_counter) {
                    if (preset_tilt_enabled == MOTOR_ENABLED) {
                        preset_tilt_enabled = MOTOR_DISABLED;

                        tilt_enabled = MOTOR_DISABLED;
                    }
                }

                MOT_TILT_1A = steps_1A[tilt_step_phase];
                MOT_TILT_1B = steps_1B[tilt_step_phase];
                MOT_TILT_2A = steps_2A[tilt_step_phase];
                MOT_TILT_2B = steps_2B[tilt_step_phase];
            } else {
                MOT_TILT_1A = 0;
                MOT_TILT_1B = 0;
                MOT_TILT_2A = 0;
                MOT_TILT_2B = 0;
            }
        }
    }
}

void main(void) {
    UC_Init();

    UART_Init();

    TIMER1_Init();

    TIMER2_Init();

    delay_wdt(500);

    UART_Write_Text_CRLF("\r\n\r\nStart");

    UART_Write_Text_CRLF("Goto PAN and TILT Home");

    delay_wdt(50);

    MOTOR_Init();

    UART_Write_Text_CRLF("Waiting for commands");

    while (1) {
        CLRWDT();

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

                //  UART_Write(frame_data[i]); // loopback
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
                        if ((P_cmd1 == 0xF0) && (P_cmd2 == 0x83) && (P_dat1 == 0x00) && (P_dat2 == 0x01)) {
                            UART_Write_Text_CRLF("REBOOT");

                            while (1) {
                                // wait for Watchdog Timer (WDT)
                            }
                        } else if ((P_cmd1 == 0x00) && (P_cmd2 == 0x67) && (P_dat1 == 0x00)) {
                            // Set Remote Baud Rate (Ref.: FUJIFILM SX800)
                            if (is_reboot == 1) {
                                BAUDS_set(P_dat2);

                                UART_Write_Text("SET BAUD RATE");

                                switch (P_dat2) {
                                    case 0x00:
                                        UART_Write_Text_CRLF("2400");
                                        break;
                                    case 0x01:
                                        UART_Write_Text_CRLF("4800");
                                        break;
                                    case 0x03:
                                        UART_Write_Text_CRLF("19200");
                                        break;
                                    case 0x04:
                                        UART_Write_Text_CRLF("38400");
                                        break;
                                    case 0x05:
                                        UART_Write_Text_CRLF("115200");
                                        break;
                                    default:
                                        // 9600 (default)
                                        UART_Write_Text_CRLF("9600");
                                        break;
                                }

                                UART_Write_Text("\r\nPLEASE ");
                            } else {
                                UART_Write_Text("\r\nNEED ");
                            }

                            UART_Write_Text_CRLF("REBOOT");
                        } else if ((P_cmd1 == 0x00) && (P_cmd2 == 0x00) && (P_dat1 == 0x00) && (P_dat2 == 0x00)) {
                            pan_enabled = MOTOR_DISABLED;
                            tilt_enabled = MOTOR_DISABLED;
                            preset_pan_enabled = MOTOR_DISABLED;
                            preset_tilt_enabled = MOTOR_DISABLED;

                            response_type = RESP_GENERAL;
                            UART_Write_Text("STOP (");
                            print_cnt(pan_counter, tilt_counter);
                            UART_Write_Text_CRLF(")");

                        } else if ((P_cmd1 == 0x00) && (P_cmd2 == PRESET_SET) && (P_dat1 == 0x00)) {
                            preset_id = P_dat2;
                            PRESET_save(preset_id, pan_counter, tilt_counter);
                            response_type = RESP_GENERAL;

                            print_preset(preset_id, pan_counter, tilt_counter, "SET PRESET ");
                        } else if ((P_cmd1 == 0x00) && (P_cmd2 == PRESET_CLEAR) && (P_dat1 == 0x00)) {
                            preset_id = P_dat2;
                            PRESET_save(preset_id, 0xFFFF, 0xFFFF);

                            uint16_t pan_tmp = 0;
                            uint16_t tilt_tmp = 0;
                            PRESET_load(preset_id, &pan_tmp, &tilt_tmp);
                            pan_goto = pan_tmp;
                            tilt_goto = tilt_tmp;

                            response_type = RESP_GENERAL;

                            print_preset(preset_id, pan_goto, tilt_goto, "CLEAR PRESET ");
                        } else if ((P_cmd1 == 0x00) && (P_cmd2 == PRESET_GOTO) && (P_dat1 == 0x00)) {
                            preset_id = P_dat2;

                            uint16_t pan_tmp = 0;
                            uint16_t tilt_tmp = 0;
                            PRESET_load(preset_id, &pan_tmp, &tilt_tmp);
                            pan_goto = pan_tmp;
                            tilt_goto = tilt_tmp;

                            preset_pan_enabled = MOTOR_ENABLED;
                            preset_pan_enabled_old = MOTOR_DISABLED;

                            pan_speed = SPEED_MAX_REF;
                            timer1_pan_ref = SPEED_calc(pan_speed);
                            pan_enabled = MOTOR_ENABLED;

                            if (pan_goto < PAN_STROKE_LIMIT_STEPS) {
                                if (pan_goto > pan_counter) {
                                    pan_direction = MOVE_CC;
                                } else if (pan_goto < pan_counter) {
                                    pan_direction = MOVE_CCW;
                                } else { // if (pan_goto == pan_counter)
                                    preset_pan_enabled = MOTOR_DISABLED;
                                    pan_enabled = MOTOR_DISABLED;
                                }
                            } else {
                                preset_pan_enabled = MOTOR_DISABLED;
                                pan_enabled = MOTOR_DISABLED;
                            }

                            preset_tilt_enabled = MOTOR_ENABLED;
                            preset_tilt_enabled_old = MOTOR_DISABLED;

                            tilt_speed = SPEED_MAX_REF;
                            timer1_tilt_ref = SPEED_calc(tilt_speed);
                            tilt_enabled = MOTOR_ENABLED;

                            if (tilt_goto < TILT_STROKE_LIMIT_STEPS) {
                                if (tilt_goto > tilt_counter) {
                                    tilt_direction = MOVE_CC;
                                } else if (tilt_goto < tilt_counter) {
                                    tilt_direction = MOVE_CCW;
                                } else { // if (tilt_goto == tilt_counter)
                                    preset_tilt_enabled = MOTOR_DISABLED;
                                    tilt_enabled = MOTOR_DISABLED;
                                }
                            } else {
                                preset_tilt_enabled = MOTOR_DISABLED;
                                tilt_enabled = MOTOR_DISABLED;
                            }

                            response_type = RESP_GENERAL;

                            print_preset(preset_id, pan_goto, tilt_goto, "GOTO PRESET ");
                        } else {
                            if ((P_cmd2 & MOVE_LEFT) == MOVE_LEFT) {
                                pan_speed = P_dat1;
                                timer1_pan_ref = SPEED_calc(pan_speed);
                                pan_direction = MOVE_CC;
                                pan_enabled = MOTOR_ENABLED;

                                preset_pan_enabled = MOTOR_DISABLED;
                                preset_tilt_enabled = MOTOR_DISABLED;

                                response_type = RESP_GENERAL;
                                is_reboot = false;

                                print_cmd_mov("LEFT", pan_counter, tilt_counter);
                            } else if ((P_cmd2 & MOVE_RIGHT) == MOVE_RIGHT) {
                                pan_speed = P_dat1;
                                timer1_pan_ref = SPEED_calc(pan_speed);
                                pan_direction = MOVE_CCW;
                                pan_enabled = MOTOR_ENABLED;

                                preset_pan_enabled = MOTOR_DISABLED;
                                preset_tilt_enabled = MOTOR_DISABLED;

                                response_type = RESP_GENERAL;
                                is_reboot = false;

                                print_cmd_mov("RIGHT", pan_counter, tilt_counter);
                            }

                            if ((P_cmd2 & MOVE_DOWN) == MOVE_DOWN) {
                                tilt_speed = P_dat2;
                                timer1_tilt_ref = SPEED_calc(tilt_speed);
                                tilt_direction = MOVE_CC;
                                tilt_enabled = MOTOR_ENABLED;

                                preset_pan_enabled = MOTOR_DISABLED;
                                preset_tilt_enabled = MOTOR_DISABLED;

                                response_type = RESP_GENERAL;
                                is_reboot = false;

                                print_cmd_mov("DOWN", pan_counter, tilt_counter);
                            } else if ((P_cmd2 & MOVE_UP) == MOVE_UP) {
                                tilt_speed = P_dat2;
                                timer1_tilt_ref = SPEED_calc(tilt_speed);
                                tilt_direction = MOVE_CCW;
                                tilt_enabled = MOTOR_ENABLED;

                                preset_pan_enabled = MOTOR_DISABLED;
                                preset_tilt_enabled = MOTOR_DISABLED;

                                response_type = RESP_GENERAL;
                                is_reboot = false;

                                print_cmd_mov("UP", pan_counter, tilt_counter);
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

            // UC_LED = !UC_LED;
        }
    }

    return;
}

void UC_Init(void) {
    PCONbits.OSCF = 1; // INTOSC Oscillator Frequency bit: 1 = 4 MHz typical

    // MCLR / WDT
    if ((PCONbits.nPOR == 1) && (PCONbits.nBOR == 1)) {

        is_reboot = 1;
    }

    PORTA = 0;
    PORTB = 0;

    CMCON = 7; //Comparador off

    OPTION_REGbits.nRBPU = 1; // PORTB pull-ups are disabled
    OPTION_REGbits.PSA = 1; // Prescaler is assigned to the WDT
    OPTION_REGbits.PS = 0b111; // 0b111 WDT Rate 1:128
    //bit 7 RBPU: PORTB Pull-up Enable bit: disabled
    //bit 3 PSA: Prescaler is assigned to the WDT
    //bit 2-0 PS2:PS0: Prescaler Rate Select bits (1:128)
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    //bit 7 Global Interrupt Enable bit
    //bit 6 Peripheral Interrupt Enable bit

    // PIE1bits.RCIE = 1;
    // PIE1bits.TMR1IE = 1;
    //bit 5 RCIE: USART Receive Interrupt Enable bit
    //bit 0 TMR1IE: TMR1 Overflow Interrupt Enable bit

    TRISA = 0b00000000;
    //0 - MOTOR PAN 1A (HORIZONTAL)
    //1 - MOTOR PAN 2B (HORIZONTAL)
    //2 - NC
    //3 - NC
    //4 - NC
    //5 - NC
    //6 - PGC / MOTOR PAN 2A (HORIZONTAL)
    //7 - PGD / MOTOR PAN 1B (HORIZONTAL)

    TRISB = 0b11000010;
    //0 - NC
    //1 - RXD
    //2 - TXD
    //3 - UC LED
    //4 - MOTOR TILT 1A (VERT)
    //5 - MOTOR TILT 1B (VERT)
    //6 - PGC / MOTOR TILT 2A (VERT)
    //7 - PGD / MOTOR TILT 2B (VERT)
}

void TIMER1_Init(void) {
    // Timer1 Registers Prescaler= 8 - TMR1 Preset = 3110 - Freq = 2.00 Hz - Period = 0.499408 seconds (Oscillator Frequency 4MHz)
    // Ref.: http://eng-serve.com/pic/pic_timer.html

    T1CONbits.T1CKPS1 = 1; // bits 5-4  Prescaler Rate Select bits
    T1CONbits.T1CKPS0 = 1; // bit 4
    T1CONbits.T1OSCEN = 0; // bit 3 Timer1 Oscillator Enable Control bit 0 = off
    T1CONbits.nT1SYNC = 1; // bit 2 Timer1 External Clock Input Synchronization Control bit...1 = Do not synchronize external clock input
    T1CONbits.TMR1CS = 0; // bit 1 Timer1 Clock Source Select bit...0 = Internal clock (FOSC/4)
    T1CONbits.TMR1ON = 1; // bit 0 enables timer
    //    TMR1H = 255; // preset for timer1 MSB register
    //    TMR1L = 131; // preset for timer1 LSB register
    TMR1H = 12; // preset for timer1 MSB register
    TMR1L = 38; // preset for timer1 LSB register

    PIR1bits.TMR1IF = 0; // clear timer1 interupt flag TMR1IF
    PIE1bits.TMR1IE = 1; // enable Timer1 interrupts
}

void TIMER2_Init(void) {
    // Timer2 Registers Prescaler= 4 - TMR2 PostScaler = 1 - PR2 = 250 - Freq = 1000.00 Hz - Period = 0.001000 seconds (Oscillator Frequency 4MHz)
    // Ref.: http://eng-serve.com/pic/pic_timer.html

    T2CONbits.TOUTPS = 0; // bits 6-3 Post scaler 1:1 thru 1:16; 0000 = 1:1 Postscale Value
    T2CONbits.T2CKPS = 1; // bits 1-0  Prescaler Rate Select bits; 01 = 1:4 Prescaler Value
    PR2 = 250; // PR2 (Timer2 Match value)

    PIR1bits.TMR2IF = 0; // clear timer1 interupt flag TMR1IF
    PIE1bits.TMR2IE = 1; // enable Timer2 interrupts

    T2CONbits.TMR2ON = 1; // bit 2 turn timer2 on;
}

// cksm: This is the arithmetic sum of all bytes except for the sync byte and itself.

//unsigned char CKSM_calc(uint8_t *in_dat) {
//    uint8_t i = 0;
//    uint8_t res = 0;
//
//    for (i = 1; i <= 5; i++) {
//        res += in_dat[i];
//    }
//
//    return res;
//}

// General Response

//void SEND_resp_general(uint8_t cmd_cksm) {
//    // cksm: This is the arithmetic sum of the checksum of the command that
//    // caused this reply and the alarms ¯eld of this reply.
//    // (Not exactly what might be expected.)
//    uint8_t checksum = cmd_cksm + alarms_data;
//
//    UART_Write(0xFF);
//    UART_Write(DEVICE_ADDR);
//    UART_Write(alarms_data);
//    UART_Write(checksum);
//}

// Motor speed max: 500Hz
// Speed min 0x06 (06); timer 20 (050Hz)
// Speed max 0x32 (50); timer 02 (500Hz)
//
// SPEED_MAX_TMR: 2
// SPEED_MIN_TMR: 20
// SPEED_MAX_REF: 50 (0x32)
// SPEED_MIN_REF: 06 (0x06)
//
// 2 + ((50 - x) / 2)
// 2 + ((50 - 50) / 2) = 2
// 2 + ((50 - 6) / 2) = 24
//
// Timer 1ms; 1000/2 = 500Hz
// Timer 1ms; 1000/24 = 41Hz

void delay_wdt(uint16_t _ms) {
    CLRWDT();

    while (_ms--) {

        CLRWDT();
        __delay_ms(1);
    };
}

void MOTOR_Init(void) {
    is_init = true;

    //    // Go to mechanical stroke limit
    //    pan_speed = SPEED_MAX_REF;
    //    pan_direction = MOVE_CCW;
    //    pan_enabled = MOTOR_ENABLED;
    //
    //    delay_wdt(22500); // Time adjusted according to the mechanism
    //
    //    pan_enabled = MOTOR_DISABLED;
    //
    //    pan_counter = 0; // New mechanical stroke limit
    //
    //    delay_wdt(100);
    //
    //    // Relieve mechanical stress
    //    pan_speed = SPEED_MAX_REF;
    //    pan_direction = MOVE_CC;
    //    pan_enabled = MOTOR_ENABLED;
    //
    //    delay_wdt(500); // Time adjusted according to the mechanism
    //
    //    pan_enabled = MOTOR_DISABLED;
    //
    //    pan_counter = 0; // New mechanical stroke limit
    //
    //    delay_wdt(50);
    //
    //    // Go to mechanical stroke limit
    //    tilt_speed = SPEED_MAX_REF;
    //    tilt_direction = MOVE_CCW;
    //    tilt_enabled = MOTOR_ENABLED;
    //
    //    delay_wdt(6000); // Time adjusted according to the mechanism
    //
    //    tilt_enabled = MOTOR_DISABLED;
    //
    //    tilt_counter = 0; // New mechanical stroke limit
    //
    //    delay_wdt(100);
    //
    //    // Relieve mechanical stress
    //    tilt_speed = SPEED_MAX_REF;
    //    tilt_direction = MOVE_CC;
    //    tilt_enabled = MOTOR_ENABLED;
    //
    //    delay_wdt(750); // Time adjusted according to the mechanism
    //
    //    tilt_enabled = MOTOR_DISABLED;
    //
    //    tilt_counter = 0; // New mechanical stroke limit

    // Go to mechanical stroke limit
    pan_speed = SPEED_MAX_REF;
    pan_direction = MOVE_CCW;
    pan_enabled = MOTOR_ENABLED;

    // Go to mechanical stroke limit
    tilt_speed = SPEED_MAX_REF;
    tilt_direction = MOVE_CCW;
    tilt_enabled = MOTOR_ENABLED;

    // delay_wdt(22500); // Time adjusted according to the mechanism
    delay_wdt(6000); // Time adjusted according to the mechanism

    tilt_enabled = MOTOR_DISABLED;

    tilt_counter = 0; // New mechanical stroke limit

    delay_wdt(100);

    // Relieve mechanical stress
    tilt_speed = SPEED_MAX_REF;
    tilt_direction = MOVE_CC;
    tilt_enabled = MOTOR_ENABLED;

    delay_wdt(750); // Time adjusted according to the mechanism

    tilt_enabled = MOTOR_DISABLED;

    tilt_counter = 0; // New mechanical stroke limit

    // Now complete the time for the PAN movement
    // 22500ms - 6000ms - 100ms - 750ms = 15650ms
    delay_wdt(15650); // Time adjusted according to the mechanism

    pan_enabled = MOTOR_DISABLED;

    pan_counter = 0; // New mechanical stroke limit

    delay_wdt(100);

    // Relieve mechanical stress
    pan_speed = SPEED_MAX_REF;
    pan_direction = MOVE_CC;
    pan_enabled = MOTOR_ENABLED;

    delay_wdt(500); // Time adjusted according to the mechanism

    pan_enabled = MOTOR_DISABLED;

    pan_counter = 0; // New mechanical stroke limit

    //    // Go to mechanical center
    //    pan_speed = SPEED_MAX_REF;
    //    pan_direction = MOVE_CC;
    //    pan_enabled = MOTOR_ENABLED;
    //
    //    delay_wdt(4700); // Time adjusted according to the mechanism
    //
    //    pan_enabled = MOTOR_DISABLED;
    //
    //    // Go to mechanical center
    //    tilt_speed = SPEED_MAX_REF;
    //    tilt_direction = MOVE_CC;
    //    tilt_enabled = MOTOR_ENABLED;
    //
    //    delay_wdt(1000); // Time adjusted according to the mechanism
    //
    //    tilt_enabled = MOTOR_DISABLED;

    // Go to mechanical center
    pan_speed = SPEED_MAX_REF;
    pan_direction = MOVE_CC;
    pan_enabled = MOTOR_ENABLED;

    // Go to mechanical center
    tilt_speed = SPEED_MAX_REF;
    tilt_direction = MOVE_CC;
    tilt_enabled = MOTOR_ENABLED;

    // delay_wdt(4700); // Time adjusted according to the mechanism
    delay_wdt(1000); // Time adjusted according to the mechanism

    tilt_enabled = MOTOR_DISABLED;

    // Now complete the time for the PAN movement
    // 4700ms - 1000ms = 3700ms
    delay_wdt(3500); // Time adjusted according to the mechanism (best: 3500ms)

    pan_enabled = MOTOR_DISABLED;

    is_init = false;
}

uint8_t SPEED_calc(uint8_t speed) {
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

void eeprom_update(uint8_t addr, uint8_t value) {
    if (value != eeprom_read(addr)) {
        eeprom_write(addr, value);
    }
}

void PRESET_save(uint8_t id, uint16_t pan, uint16_t tilt) {
    uint8_t _addr = id * 4;

    if (id < PRESET_MAX) { // PIC16F648 EEPROM: 256B; 256 / 4 = 64

        eeprom_update(_addr, pan & 0xFF);
        eeprom_update(_addr + 1, (pan >> 8) & 0xFF);

        eeprom_update(_addr + 2, tilt & 0xFF);
        eeprom_update(_addr + 3, (tilt >> 8) & 0xFF);
    }
}

void PRESET_load(uint8_t id, uint16_t *pan, uint16_t *tilt) {
    uint8_t _addr = id * 4;

    if (id < PRESET_MAX) { // PIC16F648 EEPROM: 256B; 256 / 4 = 64

        *pan = (uint16_t) (eeprom_read(_addr));
        *pan |= (uint16_t) (eeprom_read(_addr + 1) << 8);

        *tilt = (uint16_t) (eeprom_read(_addr + 2));
        *tilt |= (uint16_t) (eeprom_read(_addr + 3) << 8);
    }
}

void BAUDS_set(uint8_t index) {

    eeprom_update(EEPROM_BAUD_ADDR, index);
}

uint8_t BAUDS_get(void) {

    return eeprom_read(EEPROM_BAUD_ADDR);
}

void print_cnt(uint16_t _pan, uint16_t _tilt) {
    print_val(_pan);

    UART_Write_Text(", ");

    print_val(_tilt);
}

void print_val(uint16_t value) {
    uint16_t val10000 = 0;
    uint16_t val1000 = 0;
    uint16_t val100 = 0;
    uint16_t val10 = 0;
    uint16_t val1 = 0;

    val10000 = value / 10000;
    value -= val10000 * 10000;

    val1000 = value / 1000;
    value -= val1000 * 1000;

    val100 = value / 100;
    value -= val100 * 100;

    val10 = value / 10;
    value -= val10 * 10;

    val1 = value;

    val10000 += 48;
    val1000 += 48;
    val100 += 48;
    val10 += 48;
    val1 += 48;

    if (val10000 > 0) {
        UART_Write((uint8_t) val10000);
    }

    if ((val10000 > 0) || (val1000 > 0)) {
        UART_Write((uint8_t) val1000);
    }

    if ((val10000 > 0) || (val1000 > 0) || (val100 > 0)) {
        UART_Write((uint8_t) val100);
    }
    if ((val10000 > 0) || (val1000 > 0) || (val100 > 0) || (val10 > 0)) {
        UART_Write((uint8_t) val10);
    }

    UART_Write((uint8_t) val1);
}

void print_preset(uint8_t id, uint16_t pan, uint16_t tilt, char *text) {
    uint8_t preset_id_10 = id / 10;
    uint8_t preset_id_1 = id - (preset_id_10 * 10);

    preset_id_10 += 48;
    preset_id_1 += 48;

    UART_Write_Text(text);
    UART_Write(preset_id_10);
    UART_Write(preset_id_1);
    UART_Write_Text(" (");
    print_cnt(pan, tilt);
    UART_Write_Text_CRLF(")");
}

void print_cmd_mov(char *text, uint16_t pan, uint16_t tilt) {
    UART_Write_Text(text);
    UART_Write_Text(" (");
    print_cnt(pan, tilt);
    UART_Write_Text_CRLF(")");
}