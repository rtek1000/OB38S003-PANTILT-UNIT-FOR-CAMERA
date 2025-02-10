/*
 * uart.h
 *
 *  Ported on: 02.17.2023
 *      Author: Jonathan Armstrong
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdbool.h>
#include <stdint.h>

// FIXME: explain choice of size
// portisch allocated TX=64 and RX=32
#define UART_RX_BUFFER_SIZE 48
#define UART_TX_BUFFER_SIZE	32


// high byte error return code of uart_getc()
// Framing Error by UART
#define UART_FRAME_ERROR      0x1000
// Overrun condition by UART
#define UART_OVERRUN_ERROR    0x0800
// Parity Error by UART
#define UART_PARITY_ERROR     0x0400
// receive ringbuffer overflow
#define UART_BUFFER_OVERFLOW  0x0200
// no receive data available
#define UART_NO_DATA          0x0100


//-----------------------------------------------------------------------------
// public variables
//-----------------------------------------------------------------------------

// public prototypes
void uart_init_tx_polling(void);
bool is_uart_tx_finished(void);
bool is_uart_tx_buffer_empty(void);
unsigned int uart_getc(void);
void uart_putc(const uint8_t txdata);
void uart_write(const uint8_t value);
void uart_write_Text(char *text);
//extern void uart_put_command(const uint8_t command);


#endif // INC_UART_H_
