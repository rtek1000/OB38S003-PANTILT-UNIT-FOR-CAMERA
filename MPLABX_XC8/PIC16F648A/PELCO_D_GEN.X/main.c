/*
 * File:   main.c
 * Author: RTEK1000
 *
 * Created on 29 de Janeiro de 2025, 23:30
 */

#include "main.h"
#include "usart.h"

#define send_stop 0
#define send_up 1
#define send_down 2
#define send_left 3
#define send_right 4

//uint8_t stop_array[7] = {0x01, 0x00, 0x00, 0x00, 0x00};
//uint8_t up_array[7] = {0x01, 0x00, 0x08, 0x00, 0x06};
//uint8_t down_array[7] = {0x01, 0x00, 0x10, 0x00, 0x06};
//uint8_t left_array[7] = {0x01, 0x00, 0x04, 0x06, 0x00};
//uint8_t right_array[7] = {0x01, 0x00, 0x02, 0x06, 0x00};

uint8_t stop_array[7] = {0x01, 0x00, 0x00, 0x00, 0x00};
uint8_t up_array[7] = {0x01, 0x00, 0x08, 0x00, 0xFF};
uint8_t down_array[7] = {0x01, 0x00, 0x10, 0x00, 0x01};
uint8_t left_array[7] = {0x01, 0x00, 0x04, 0x06, 0x00};
uint8_t right_array[7] = {0x01, 0x00, 0x02, 0x32, 0x00};

//uint8_t checksum_calc(uint8_t *dat);
void send_pelco_d(uint8_t cmd);
void send_data(uint8_t *dat);

void main(void) {
    PORTA = 0;
    PORTB = 0;

    CMCON = 7; //comparador off

    OPTION_REG = 0b11001111;
    //bit 7 RBPU: PORTB Pull-up Enable bit: disabled
    //bit 3 PSA: Prescaler is assigned to the WDT
    //bit 2-0 PS2:PS0: Prescaler Rate Select bits (1:128)

    INTCON = 0b00000000;
    //bit 7 Global Interrupt Enable bit
    //bit 6 Peripheral Interrupt Enable bit

    TRISA = 0b00001111;
    //0 - BUTTON_D
    //1 - BUTTON_L
    //2 - BUTTON_R
    //3 - BUTTON_U
    //4 - NC
    //5 - NC
    //6 - NC
    //7 - NC

    TRISB = 0b00000010;
    //0 - NC
    //1 - RXD
    //2 - TXD
    //3 - NC
    //4 - NC
    //5 - NC
    //6 - PGC
    //7 - PGD

    UART_Init(9600);

    //UART_Write_Text("\r\n\r\nStart\r\n");

    UC_LED = 1;

    while (1) {
        if (BUTTON_U == 0) {
            if (SWITCH1 == 0) {
                send_pelco_d(send_left);

                __delay_ms(18);

                send_pelco_d(send_up);
            } else {
                send_pelco_d(send_up);
            }
            
            __delay_ms(18);

            while (BUTTON_U == 0) {
                UC_LED = 0;
            }

            send_pelco_d(send_stop);

            UC_LED = 1;
        } else if (BUTTON_D == 0) {
            if (SWITCH1 == 0) {
                send_pelco_d(send_left);

                __delay_ms(18);

                send_pelco_d(send_down);
            } else {
                send_pelco_d(send_down);
            }
            
            __delay_ms(18);

            while (BUTTON_D == 0) {
                UC_LED = 0;
            }

            send_pelco_d(send_stop);

            UC_LED = 1;
        } else if (BUTTON_L == 0) {
            send_pelco_d(send_left);

            while (BUTTON_L == 0) {
                UC_LED = 0;
            }
            
            __delay_ms(18);

            send_pelco_d(send_stop);

            UC_LED = 1;
        } else if (BUTTON_R == 0) {
            send_pelco_d(send_right);

            while (BUTTON_R == 0) {
                UC_LED = 0;
            }
            
            __delay_ms(18);

            send_pelco_d(send_stop);

            UC_LED = 1;
        }
    }

    return;
}

// cksm: This is the arithmetic sum of all bytes except for the sync byte and itself.

//uint8_t checksum_calc(uint8_t *dat) {
//    uint8_t res = 0;
//
//    for (uint8_t i = 1; i <= 4; i++) {
//        res += dat[i];
//    }
//    
//    return res;
//}

void send_pelco_d(uint8_t cmd) {   
    switch (cmd) {
        case send_stop:
        {
            send_data(stop_array);
            break;
        }
        case send_up:
        {
            send_data(up_array);
            break;
        }
        case send_down:
        {
            send_data(down_array);
            break;
        }
        case send_left:
        {
            send_data(left_array);
            break;
        }
        case send_right:
        {
            send_data(right_array);
            break;
        }
        default:
            return;
    }
}

void send_data(uint8_t *in_dat) {
    uint8_t i = 0;
    uint8_t _dat[7] = {0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01};
    uint8_t checksum_calc = 0;
    
//    for (i = 0; i <= 4; i++) {
//        UART_Write(_dat[i]); // Start, Addr, Cmd1, Cmd2, Data1, (Data2, Checksum) // Test: send corrupted frame
//
//        __delay_ms(1);
//    }
//    
//    __delay_ms(18);

    _dat[0] = 0xFF;

    for (i = 0; i <= 4; i++) {
        _dat[i + 1] = in_dat[i]; // Addr, Cmd1, Cmd2, Data1, Data2 
    }

    for (uint8_t i = 1; i <= 5; i++) {
        checksum_calc += _dat[i];
    }

    _dat[6] = checksum_calc;

    for (i = 0; i <= 6; i++) {
        UART_Write(_dat[i]); // Start, Addr, Cmd1, Cmd2, Data1, Data2, Checksum

        __delay_ms(1);
    }
}