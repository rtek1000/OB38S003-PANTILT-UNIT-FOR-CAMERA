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

void UART_Init(void);
void UART_Write(char data);
void UART_Write_Text(char *text);
void UART_Write_Text_CRLF(char *text); 
//char UART_Data_Ready(void);
//char UART_Read(void);

#endif	/* __USART_H__ */

