/*
 * File:   usart.h
 * Author: RTEK1000
 *
 * Created on 12 de Abril de 2024, 07:09
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __USART_H__
#define	__USART_H__

#include "main.h"

char UART_Init(const uint32_t baudrate);
void UART_Write(char data);
void UART_Write_Text(char *text);
//char UART_Data_Ready(void);
//char UART_Read(void);

#endif	/* __USART_H__ */

