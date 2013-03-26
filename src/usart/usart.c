/*
 *  AVR USART Library
 *
 *  Description: This files contains functions for using the AVR USART.
 *
 *  Table of Contents:
 *
 *  Revision History:
 *     11/16/2012   Steven Okai     Initial revision.
 *     12/21/2012   Shir Aharon     Alignment, moved constants to general file
 *
 */

#include <avr/io.h>
#include "usart.h"
#include "genio.h"
#include "../general/global_def.h"    // Used for true/false and byte masks

#define CPU_FREQ        0

#define AVR_F_CLK       32000000

#define USART_BSCALE    0

// May want to use defines to change this based on clock speed and BSCALE
#define USART_BAUD_9600_BSEL    416


// Declare a constant array for accessing the bits for the correct directional mode
const uint8_t USART_DIRECTION[] = {USART_TXEN_BIT, USART_RXEN_BIT, USART_TXEN_BIT | USART_RXEN_BIT};

/* Takes a pointer to a USART and initializes it based on the passed mode (transmit, receive, or both)
   char size, */
void InitUSART(uint8_t *USART, uint8_t *port, uint8_t direction, uint8_t baud2X, int8_t baudScale, uint16_t baudSel) {

    // Initialize

//1. Set the TxD pin value high, and optionally set the XCK pin low.
//2. Set the TxD and optionally the XCK pin as output. NEED PORT DIRECTION REGISTER
//3. Set the baud rate and frame format.
//4. Set the mode of operation (enables XCK pin output in synchronous mode).
//5. Enable the transmitter or the receiver, depending on the usage.

    // TODO: Add an argument that lets you pick which of the USARTS on a port youa re using
    // TODO: Set the TxD pin value high, and optionally set the XCK pin low.
    SetPin(port, USART_TXD1_PIN, IO_PIN_HIGH);

    // TODO: Set the TxD and optionally the XCK pin as output.
    SetPinDirection(port, USART_TXD1_PIN, IO_DIR_OUTPUT);

    // TODO: Set receive pin to input
    // Set the direction of the USART
    SetUSARTDirection(USART, direction);

	// Set the baud rate
    SetUSARTBaudRate(USART, baud2X, baudScale, baudSel);

    // Set default frame format (8-bit char size, no parity, 1 stop bit)
    SetCharSize(USART, USART_CHSIZE_BITS);
    SetParity(USART, USART_PARITY_DISABLED);
    SetStopBits(USART, USART_ONE_STOP_BIT);

    // TODO: Set the mode of operation (enables XCK pin output in synchronous mode).
    // Set the communication mode to asynchronous
    SetComMode(USART, USART_ASYNC_MODE);

    return;

}

void SetUSARTDirection(uint8_t *USART, uint8_t direction) {

	// Get the address of ctrl register B for USART
	uint8_t *CtrlB;
    CtrlB = USART + USART_CTRL_B_OFFSET;

	// Mask out direction bits to keep other settings, then set direction
	*CtrlB = (*CtrlB & USART_DIR_MASK) | USART_DIRECTION[direction];

	return;

}

void SetUSARTBaudRate(uint8_t *USART, uint8_t baud2X, int8_t baudScale, uint16_t baudSel) {

    uint8_t *BAUDCTRLA;
    uint8_t *BAUDCTRLB;
    uint8_t *CTRLB;

    uint8_t CTRLBVal;

    // Get the addresses of baud control registers
    BAUDCTRLA = USART + USART_BAUD_CTRL_A_OFFSET;
    BAUDCTRLB = USART + USART_BAUD_CTRL_B_OFFSET;
    CTRLB = USART + USART_CTRL_B_OFFSET;

    // The low 8-bits of baud select value go to baud ctrl A
    *BAUDCTRLA = (uint8_t) (baudSel & LOW_BYTE_MASK);

    // The high 4-bits of baud select value and the scale factor go to baud ctrl B
    *BAUDCTRLB = ((baudScale << 4) | (uint8_t) (baudSel >> 8));

    // Get the current control reg. B settings and clear CLK2X bit
    CTRLBVal = *CTRLB & (~USART_ASYNC_2X_ON);

    // Set the CLK2X bit based on passed setting
    *CTRLB = CTRLBVal | baud2X;

    return;

}
/*
void SetUSARTBaudRate(uint8_t *USART, uint16_t BaudRate) {

    uint16_t BaudValue;
    uint8_t LowBaudValue;
    uint8_t HighBaudValue;
    uint8_t *BaudCtrlA;
    uint8_t *BaudCtrlB;

	// Get the baud value to write to the baud registers
    BaudValue = (CPU_FREQ/(BaudRate*16)) - 1;

	// Get the low byte of the baud value
	LowBaudValue = BaudValue & LOW_BYTE_MASK;

	// Get the high byte of the baud value
	HighBaudValue = (BaudValue & HIGH_BYTE_MASK) >> 8;

	// TODO: calculate baud scale

	// Get the address of baud ctrl registers A and B
	BaudCtrlA = USART + USART_BAUD_CTRL_A_OFFSET; // Careful this may dereference!
	BaudCtrlB = USART + USART_BAUD_CTRL_B_OFFSET;

	// Write the new baud values
	*BaudCtrlA = LowBaudValue;
	*BaudCtrlB = HighBaudValue;

	return;
}
*/

void SetComMode(uint8_t *USART, uint8_t comMode) {

    uint8_t *CTRLC;

    // Get address of control register C
    CTRLC = USART + USART_CTRL_C_OFFSET;

    // Set new com. mode while preserving other settings
    *CTRLC = (*CTRLC & (~USART_CMODE_BITS)) | (comMode);

    return;
}

void SetParity(uint8_t *USART, uint8_t parity) {

    uint8_t *CTRLC;

    // Get address of control register C
    CTRLC = USART + USART_CTRL_C_OFFSET;

    // Set new parity mode while preserving other settings
    *CTRLC = (*CTRLC & (~USART_PARITY_BITS)) | (parity);

    return;

}

void SetStopBits(uint8_t *USART, uint8_t stopBitMode) {

    uint8_t *CTRLC;

    // Get address of control register C
    CTRLC = USART + USART_CTRL_C_OFFSET;

    // Set new stop bit mode while preserving other settings
    *CTRLC = (*CTRLC & (~USART_SBMODE_BITS)) | (stopBitMode);

    return;

}

void SetCharSize(uint8_t *USART, uint8_t charSizeMode) {

    uint8_t *CTRLC;

    // Get address of control register C
    CTRLC = USART + USART_CTRL_C_OFFSET;

    // Set new character size while preserving other settings
    *CTRLC = (*CTRLC & (~USART_CHSIZE_BITS)) | (charSizeMode);

    return;

}

void TxUSARTByte(uint8_t *USART, uint8_t txByte) {

    // Wait until USART is ready to transmitted
    while (TxReady(USART) == FALSE);

    // Send the byte
    *USART = txByte;

    return;

}

uint8_t TxReady(uint8_t *USART) {

    uint8_t *STATUS;
    uint8_t TxRdyBit;
    uint8_t TxRdy;

    // Get address of the status register
    STATUS = USART + USART_STATUS_OFFSET;

    // Get only the transmit ready bit
    TxRdyBit = (*STATUS & USART_STATUS_DREIF);

    if (TxRdyBit == 0) {
    // If the transmit ready bit is not set, not ready
        TxRdy = FALSE;

    } else {
    // Otherwise ready to transmit
        TxRdy = TRUE;

    }

    return TxRdy;

}


// MIGHT WANT TO WRITE QUEUES library for int base receive!!!

