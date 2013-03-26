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
 *     12/21/2012   Shir Aharon     Include guard, alignment
 *
 */

// Include guard
#ifndef __CHAR_DISPLAY__
#define __CHAR_DISPLAY__

#include <avr/io.h>
#define DISPLAY_NUM_ROWS        4
#define DISPLAY_CHAR_PER_ROW    16

typedef struct {

    // USART used for display
    uint8_t *USART;

} CharDisplay;

void InitCharDisplay(CharDisplay *display, uint8_t *USART, uint8_t *port);
void SendDisplayCmd(CharDisplay *display, uint8_t cmd, uint8_t specialCmd);
void DisplayWriteChar(CharDisplay *display, uint8_t character);
void DisplayWriteCharToPosition(CharDisplay *display, uint8_t character, uint8_t row, uint8_t position);
void ClearDisplay(CharDisplay *display);
void CursorRight(CharDisplay *display);
void CursorLeft(CharDisplay *display);
void ScrollRight(CharDisplay *display);
void ScrollLeft(CharDisplay *display);
void DisplayOn(CharDisplay *display);
void DisplayOff(CharDisplay *display);
void UnderlineCursorOn(CharDisplay *display);
void BoxCursorOn(CharDisplay *display);
void CursorOff(CharDisplay *display);
void SetCursorPosition(CharDisplay *display, uint8_t row, uint8_t position);
void SetBacklight(CharDisplay *display, uint8_t brightness);
// Write function to set baud rate

void DisplayWriteStrToPosition(CharDisplay *display, uint8_t *str, uint8_t strLen,
                               uint8_t row, uint8_t position);

#endif // __CHAR_DISPLAY__
