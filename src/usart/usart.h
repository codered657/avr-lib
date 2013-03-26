/*
 *  AVR USART Library
 *
 *  Description: This files contains functions for using the AVR USART.
 *
 *  Table of Contents:
 *
 *  Revision History:
 *     11/16/2012   Steven Okai     Initial revision.
 *     12/21/2012   Shir Aharon     Include guard, alignment
 *
 */

// Include guard
#ifndef __USART__
#define __USART__

#include <avr/io.h>

#define USART_TXEN_BIT          0x08
#define USART_RXEN_BIT          0x10
#define USART_ASYNC_MODE        0x00
#define USART_SYNC_MODE         0x10
#define USART_PARITY_DISABLED   0x00
#define USART_EVEN_PARITY       0x20
#define USART_ODD_PARITY	    0x30
#define USART_ONE_STOP_BIT      0x00
#define USART_TWO_STOP_BITS     0x08
#define USART_CHAR_SIZE_8       0x03
#define USART_ASYNC_2X_ON       0x04
#define USART_ASYNC_2X_OFF      0x00

#define USART_CMODE_BITS        0xC0
#define USART_PARITY_BITS       0x30
#define USART_SBMODE_BITS       0x08
#define USART_CHSIZE_BITS       0x03

#define USART_CTRL_B_OFFSET         0x04
#define USART_CTRL_C_OFFSET         0x05
#define USART_BAUD_CTRL_A_OFFSET    0x06
#define USART_BAUD_CTRL_B_OFFSET    0x07
#define USART_STATUS_OFFSET         0x01

#define USART_DIR_MASK          0xE7

#define USART_STATUS_DREIF      0x20

#define USART_TXD1_PIN          7

/* Takes a pointer to a USART and initializes it based on the passed mode (transmit, receive, or both)
   char size, */
void InitUSART(uint8_t *USART, uint8_t *port, uint8_t direction, uint8_t baud2X, int8_t baudScale, uint16_t baudSel);
void SetUSARTDirection(uint8_t *USART, uint8_t direction);
void SetUSARTBaudRate(uint8_t *USART, uint8_t baud2X, int8_t baudScale, uint16_t baudSel);
void TxUSARTByte(uint8_t *USART, uint8_t txByte);
uint8_t TxReady(uint8_t *USART);

#endif // USART
