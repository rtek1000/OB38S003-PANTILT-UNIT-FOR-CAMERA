/*
 *
 *  Created on: 02.16.2023
 *      Author: Jonathan Armstrong
 */

#include "hal.h"

//#if defined(TARGET_BOARD_OB38S003)
#include "OB38S003.h"
//#elif defined(TARGET_BOARD_EFM8BB1) || defined(TARGET_BOARD_EFM8BB1LCB)
//    // these are just a difference in naming convention
//    #define SBUF SBUF0
//    #define SCON SCON0
//#endif

//#include "portisch_command_format.h"
#include "uart.h"

#include <stdint.h>
#include <stdbool.h>

//
// the original implementation from RF-Bridge-EFM8BB1 looks similar to this implementation
// https://github.com/hrshygoodness/EFM32-Library/blob/master/v2/an/an0820_efm32_smart_card/usart_driver.c
//-----------------------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------------------

volatile bool is_TI = 0;

extern volatile uint8_t is_motor_init;

extern volatile uint8_t data_receiv;
extern volatile uint8_t buffer_index1;
extern volatile uint8_t buffer_index2;
extern volatile uint8_t buffer_data0[BUFFER_SIZE];
extern volatile uint8_t buffer_data1[BUFFER_SIZE];
extern volatile uint8_t buffer_data2[BUFFER_SIZE];
extern volatile uint8_t buffer_data3[BUFFER_SIZE];
extern volatile uint8_t buffer_data4[BUFFER_SIZE];

extern volatile _Bool buffer_ready[BUFFER_ARRAY];

extern volatile uint8_t header_cnt;

extern volatile uint8_t timeout_receiv;

//__xdata volatile uint8_t UART_RX_Buffer[UART_RX_BUFFER_SIZE];
//__xdata volatile uint8_t UART_TX_Buffer[UART_TX_BUFFER_SIZE];
//
//__xdata static volatile uint8_t UART_RX_Buffer_Position = 0;
//__xdata static volatile uint8_t UART_TX_Buffer_Position = 0;
//__xdata static volatile uint8_t UART_Buffer_Read_Position = 0;
//__xdata static volatile uint8_t UART_Buffer_Write_Position = 0;
//__xdata static volatile uint8_t UART_Buffer_Write_Len = 0;

//__xdata static volatile uint8_t lastRxError;

// prefer to avoid storing in external ram to take advantage of bit addressable internal ram
static volatile bool gTXFinished = true;

//-----------------------------------------------------------------------------
// UART ISR Callbacks
//-----------------------------------------------------------------------------
// removed to save code space

void uart_write(const uint8_t value) {
	TI = 0; // TI: Transmit interrupt flag, set by hardware after completion of a serial transfer.
			// Must be cleared by software.

	SBUF = value;

	is_TI = 0;

	while (is_TI == 0)
		; // TI == 0; wait for completion of a serial transfer
}

void uart_write_Text(char *text) {
	int i;
	for (i = 0; text[i] != '\0'; i++)
		uart_write(text[i]);
}

// FIXME: this could probably be replaced with call to
// void init_serial_interrupt(void) which sets the same flag
void uart_init_tx_polling(void) {
	TI = 1;
}

//=========================================================
//=========================================================
//#if defined(TARGET_BOARD_OB38S003)
void uart_isr(void)
__interrupt (d_UART0_Vector)
//#elif defined(TARGET_BOARD_EFM8BB1) || defined(TARGET_BOARD_EFM8BB1LCB)
//void uart_isr(void) __interrupt (UART0_VECTOR)
//#endif
{
	uint8_t SCON_buff = SCON;

	if ((SCON_buff & 0x02) == 0x02) {
		is_TI = 1;

		TI = 0;
	}

	if ((SCON_buff & 0x01) == 0x01) { // receiving byte
		RI = 0;

		data_receiv = SBUF;//UART1_Read();

		if (is_motor_init == 1) {
			return;
		}

		//SBUF = data_receiv; // loopback

		if (data_receiv == P_SYNC) {
			timeout_receiv = 0;
		}

		if ((buffer_index2 <= 6) || ((buffer_index2 == 0) && (data_receiv == P_SYNC))) {
			if (buffer_index1 == 0) {
				buffer_data0[buffer_index2++] = data_receiv;
			} else if (buffer_index1 == 1) {
				buffer_data1[buffer_index2++] = data_receiv;
			} else if (buffer_index1 == 2) {
				buffer_data2[buffer_index2++] = data_receiv;
			} else if (buffer_index1 == 3) {
				buffer_data3[buffer_index2++] = data_receiv;
			} else if (buffer_index1 == 4) {
				buffer_data4[buffer_index2++] = data_receiv;
			}
		}

		if (buffer_index2 == 7) {
			buffer_index2 = 0;

			buffer_ready[buffer_index1] = 1;

			if (buffer_index1 < 4) { // if (buffer_index1 < 2) {
				buffer_index1++;
			} else {
				buffer_index1 = 0;
			}
		}

	}

//    if (flags & 0x01)
//    {
//        // store received data in buffer
//        UART_RX_Buffer[UART_RX_Buffer_Position] = SBUF;
//        UART_RX_Buffer_Position++;
//
//        // set to beginning of buffer if end is reached
//        if (UART_RX_Buffer_Position == UART_RX_BUFFER_SIZE)
//        {
//            UART_RX_Buffer_Position = 0;
//        }
//    }

//    // transmit byte
//    if (flags & 0x02)
//    {
//        if (UART_Buffer_Write_Len > 0)
//        {
//            uart_write(UART_TX_Buffer[UART_Buffer_Write_Position]);
//            UART_Buffer_Write_Position++;
//            UART_Buffer_Write_Len--;
//
//            gTXFinished = false;
//        } else {
//            gTXFinished = true;
//        }
//
//
//        if (UART_Buffer_Write_Position == UART_TX_BUFFER_SIZE)
//        {
//            UART_Buffer_Write_Position = 0;
//        }
//    }
}

// we avoid the wait until finished loop of original portisch
// but can achieve the same behavior with calling functions
bool is_uart_tx_finished(void) {
	return gTXFinished;
}

bool is_uart_tx_buffer_empty(void) {
//    if ( UART_Buffer_Write_Len > 0 )
//    {
//        return false;
//    }

	return true;
}

//************************************************************************
//Function: uart_getc()
//Purpose:  return byte from ringbuffer
//Returns:  lower byte:  received byte from ringbuffer
//          higher byte: last receive error
//************************************************************************
unsigned int uart_getc(void) {
	unsigned int rxdata = 0;

//    if ( UART_Buffer_Read_Position == UART_RX_Buffer_Position )
//    {
//        // no data available
//        return UART_NO_DATA;
//    }
//
//    // get data from receive buffer
//    rxdata = UART_RX_Buffer[UART_Buffer_Read_Position];
//    UART_Buffer_Read_Position++;
//
//    if (UART_Buffer_Read_Position == UART_RX_BUFFER_SIZE)
//    {
//        UART_Buffer_Read_Position = 0;
//    }
//
//    // FIXME: can not see where lastRxError is ever set?
//    //rxdata |= (lastRxError << 8);
//    //lastRxError = 0;

	return rxdata;
}

//************************************************************************
//Function: uart_putc()
//Purpose:  write byte to ringbuffer for transmitting via UART
//Input:    byte to be transmitted
//Returns:  none
//************************************************************************
void uart_putc(const uint8_t txdata) {
//    if (UART_TX_Buffer_Position == UART_TX_BUFFER_SIZE)
//    {
//        UART_TX_Buffer_Position = 0;
//    }
//
//    UART_TX_Buffer[UART_TX_Buffer_Position] = txdata;
//    UART_TX_Buffer_Position++;
//    UART_Buffer_Write_Len++;
	(void) txdata;
}

//void uart_put_command(const uint8_t command)
//{
//    // in other words 0xAA, sonoff convention maybe?
//    uart_putc(RF_CODE_START);
//    // defined here: https://github.com/Portisch/RF-Bridge-EFM8BB1/wiki/Commands
//    uart_putc(command);
//    // in other words 0x55
//    uart_putc(RF_CODE_STOP);
//}
