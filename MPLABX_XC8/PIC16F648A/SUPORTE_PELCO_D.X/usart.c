/*
 * File:   usart.c
 * Author: RTEK1000
 *
 * Created on 12 de Abril de 2024, 07:09
 */

#include "usart.h"

char UART_Init(const uint32_t baudrate) {
    // See datasheet 
    // TABLE 12-5: BAUD RATES FOR ASYNCHRONOUS MODE (BRGH = 1)
    
    BRGH = 1; //Setting High Baud Rate
    SPBRG = 25; //Writing SPBRG Register
    SYNC = 0; //Setting Asynchronous Mode, ie UART
    SPEN = 1; //Enables Serial Port
    CREN = 1; //Enables Continuous Reception
    TXEN = 1; //Enables Transmission
    
    PIR1bits.RCIF = 0;
    PIE1bits.RCIE = 1;
    
    return 1; //Returns 1 to indicate Successful Completion
    
//    uint32_t x;
//    x = (uint32_t)((_XTAL_FREQ - (baudrate * 64)) / (baudrate * 64)); //SPBRG for Low Baud Rate
//    if (x > 255) //If High Baud Rage Required
//    {
//        x = (uint32_t)((_XTAL_FREQ - (baudrate * 16)) / (baudrate * 16)); //SPBRG for High Baud Rate
//        BRGH = 1; //Setting High Baud Rate
//    }
//    
//    if (x <= 255) {
//        SPBRG = (unsigned char) x; //Writing SPBRG Register
//        SYNC = 0; //Setting Asynchronous Mode, ie UART
//        SPEN = 1; //Enables Serial Port
//
//        CREN = 1; //Enables Continuous Reception
//        TXEN = 1; //Enables Transmission
//        return 1; //Returns 1 to indicate Successful Completion
//    }
//    return 0; //Returns 0 to indicate UART initialization failed
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