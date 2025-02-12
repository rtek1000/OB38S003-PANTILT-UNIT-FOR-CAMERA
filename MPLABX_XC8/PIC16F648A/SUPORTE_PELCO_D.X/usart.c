/*
 * File:   usart.c
 * Author: RTEK1000
 *
 * Created on 12 de Abril de 2024, 07:09
 */

#include "usart.h"

extern uint8_t BAUDS_get(void);

void UART_Init(void) {
    // See datasheet 
    // TABLE 12-5: BAUD RATES FOR ASYNCHRONOUS MODE (BRGH = 1)

    uint8_t bauds_index = BAUDS_get();

    switch (bauds_index) {
        case 0: // 2400 (2403.846)
            BRGH = 0; //Setting Low Baud Rate
            SPBRG = 25; // ERROR +0.160% (4MHz)
            break;
        case 1: // 4800 (4807.692)
            BRGH = 1; //Setting High Baud Rate
            SPBRG = 51; // ERROR +0.160% (4MHz)
            break;
//        case 2: // 9600
//            // statements
//            break;
        case 3: // 19200 (19230.77)
            BRGH = 1; //Setting High Baud Rate
            SPBRG = 12; // ERROR +0.160% (4MHz)
            break;
        case 4: // 38400 (35714.286)
            BRGH = 1; //Setting High Baud Rate
            SPBRG = 6; // ERROR -6.994% (4MHz)
            break;
        case 5: // 115200 (125000)
            BRGH = 1; //Setting High Baud Rate
            SPBRG = 1; // ERROR +8.507% (4MHz)
            break;
        default: // 9600 (9615.385)
            BRGH = 1; //Setting High Baud Rate
            SPBRG = 25; // ERROR +0.160% (4MHz)
            break;
    }

    // BRGH = 1; //Setting High Baud Rate
    // SPBRG = 25; //Writing SPBRG Register (9600)
    SYNC = 0; //Setting Asynchronous Mode, ie UART
    SPEN = 1; //Enables Serial Port
    CREN = 1; //Enables Continuous Reception
    TXEN = 1; //Enables Transmission

    PIR1bits.RCIF = 0;
    PIE1bits.RCIE = 1;
}

void UART_Write(char data) {
    unsigned long timeout = 0x1FFFF;

    while (!TRMT) {
        if (timeout > 0) {
            timeout--;
        } else {
            break;
        }
    }

    TXREG = data;
}

void UART_Write_Text(char *text) {
    int i;
    for (i = 0; text[i] != '\0'; i++)
        UART_Write(text[i]);
}

//char UART_Data_Ready(void) {
//    return RCIF;
//}

//char UART_Read(void) {
//    unsigned long timeout = 0x1FFFF;
//
//    while (!RCIF) {
//        if (timeout > 0) {
//            timeout--;
//        } else {
//            break;
//        }
//    }
//
//    return RCREG;
//}