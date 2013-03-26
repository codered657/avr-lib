/*
 *  AVR Character Display Library
 *
 *  Description:    This files contains functions for displaying messages
 *                  on a serial 16-character display.
 *
 *  Table of Contents:
 *
 *  Special Notes:  Only works for character displays in which the number of rows is a power of 2.
 *
 *  Revision History:
 *     11/30/2012   Steven Okai     Initial revision.
 *     12/21/2012   Shir Aharon     Alignment, moved constants to general file
 *
 */

#include <util/delay.h>
#include "chardisplay.h"
#include "usart.h"
#include "../../../global_def.h"    // Used for true/false

// Might want to use static const keyword instead of preprocessor define
#define DISPLAY_CMD_CLEAR               0x01
#define DISPLAY_CMD_CURSOR_RIGHT        0x14
#define DISPLAY_CMD_CURSOR_LEFT         0x10
#define DISPLAY_CMD_SCROLL_RIGHT        0x1C
#define DISPLAY_CMD_SCROLL_LEFT         0x18
#define DISPLAY_CMD_DISPLAY_ON          0x0C
#define DISPLAY_CMD_DISPLAY_OFF         0x08
#define DISPLAY_CMD_UNDERLINE_CURSOR_ON 0x0E
#define DISPLAY_CMD_BOX_CURSOR_ON       0x0D
#define DISPLAY_CMD_CURSOR_OFF          0x0C
#define DISPLAY_CMD_SET_CURSOR_POSITION 0x80

// Types of display commands
#define DISPLAY_CMD                     0xFE
#define DISPLAY_CMD_SPECIAL             0x7C

// Brightness symbols
#define DISPLAY_BRIGHTNESS_RANGE         29
#define DISPLAY_BRIGHTNESS_BASE         128

// Might want to use enum
const uint8_t DISPLAY_ROW_OFFSETS[4] = {0, 64, 16, 80};

void InitCharDisplay(CharDisplay *display, uint8_t *USART, uint8_t *port) {

    // Set the USART used for the display
    display->USART = USART;

    // TODO: Initialize the USART for use with the display
    InitUSART(USART, port, 0, USART_ASYNC_2X_ON, 5, 12);
        // Set to transmit only
        // Set correct baud rate (use constant/default)

    return;

}

void SendDisplayCmd(CharDisplay *display, uint8_t cmd, uint8_t specialCmd) {

    // Send appropriate command flag
    if (specialCmd == FALSE) {
    // If not a special command, send the normal command flag
        TxUSARTByte(display->USART, DISPLAY_CMD);

    } else {
    // Otherwise, send the special command flag
        TxUSARTByte(display->USART, DISPLAY_CMD_SPECIAL);

    }

    // Now send the command
    TxUSARTByte(display->USART, cmd);

    return;

}

void DisplayWriteChar(CharDisplay *display, uint8_t character) {

    // Send character over UART
    TxUSARTByte(display->USART, character);

    return;

}

void DisplayWriteCharToPosition(CharDisplay *display, uint8_t character, uint8_t row, uint8_t position) {

    // Move cursor to correct position
    SetCursorPosition(display, row, position);

    // Write the character to the display
    DisplayWriteChar(display, character);

    return;

}

void ClearDisplay(CharDisplay *display) {

    // Send the clear display command over the UART
    SendDisplayCmd(display, DISPLAY_CMD_CLEAR, FALSE);

    return;

}

void CursorRight(CharDisplay *display) {

    // Send the command to move the cursor to the right one spot
    SendDisplayCmd(display, DISPLAY_CMD_CURSOR_RIGHT, FALSE);

    return;

}

void CursorLeft(CharDisplay *display) {

    // Send the command to move the cursor to the left one spot
    SendDisplayCmd(display, DISPLAY_CMD_CURSOR_LEFT, FALSE);

    return;

}

void ScrollRight(CharDisplay *display) {

    // Send the command to scroll to the right
    SendDisplayCmd(display, DISPLAY_CMD_SCROLL_RIGHT, FALSE);

    return;

}

void ScrollLeft(CharDisplay *display) {

    // Send the command to scroll to the left
    SendDisplayCmd(display, DISPLAY_CMD_SCROLL_LEFT, FALSE);

    return;

}

void DisplayOn(CharDisplay *display) {

    // Send the command to turn display on
    SendDisplayCmd(display, DISPLAY_CMD_DISPLAY_ON, FALSE);

    return;

}

void DisplayOff(CharDisplay *display) {

    // Send the command to turn the display off
    SendDisplayCmd(display, DISPLAY_CMD_DISPLAY_OFF, FALSE);

    return;

}

void UnderlineCursorOn(CharDisplay *display) {

    // Send the command to turn the underline cursor on
    SendDisplayCmd(display, DISPLAY_CMD_UNDERLINE_CURSOR_ON, FALSE);

    return;

}

void BoxCursorOn(CharDisplay *display) {

    // Send the command to turn the box cursor on
    SendDisplayCmd(display, DISPLAY_CMD_BOX_CURSOR_ON, FALSE);

    return;

}

void CursorOff(CharDisplay *display) {

    // Send the command to turn the cursor off
    SendDisplayCmd(display, DISPLAY_CMD_CURSOR_OFF, FALSE);

    return;

}

void SetCursorPosition(CharDisplay *display, uint8_t row, uint8_t position) {

    uint8_t cursorOffset;

    // Take the modulus of the row number to insure its valid
    //row = row & (DISPLAY_NUM_ROWS - 1);

    // Calculate the position offset
    cursorOffset = DISPLAY_ROW_OFFSETS[row] + position;

    // Send the command to set the cursor position
    SendDisplayCmd(display, DISPLAY_CMD_SET_CURSOR_POSITION + cursorOffset, FALSE);

    return;

}

void SetBacklight(CharDisplay *display, uint8_t brightness) {

    uint8_t brightnessOffset;

    // Scale to brightness range
    brightness = brightness % 100; // Bound to 100%
    brightnessOffset = (brightness * DISPLAY_BRIGHTNESS_RANGE)/100;

    // Send command to set the brightness of the display
    SendDisplayCmd(display, DISPLAY_BRIGHTNESS_BASE + brightnessOffset, TRUE);

    return;

}

// Write function to set baud rate

void DisplayWriteStrToPosition(CharDisplay *display, uint8_t *str, uint8_t strLen,
                               uint8_t row, uint8_t position) {

    uint8_t i_str;
    uint8_t i_row;
    uint8_t j_col;
    uint8_t startingCol;

    i_str = 0;
    startingCol = position;

    // Start as starting row
    for (i_row = row; i_row < DISPLAY_NUM_ROWS/2; i_row++) {

        // Start at starting column/position
        for (j_col = startingCol; j_col < DISPLAY_CHAR_PER_ROW; j_col++) {

            if (i_str < strLen) {
                // Write string until end of row
                DisplayWriteCharToPosition(display, str[i_str], i_row, j_col);
                _delay_ms(1000);
                i_str++;
            }

        }

        // On next row, start at beginning of row
        startingCol = 0;

    }

    return;

}
