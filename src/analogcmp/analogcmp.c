/*
 *  AVR Analog Comparator Library
 *
 *  Description:    This files contains functions for using the AVR
 *                  Analog Comparator.
 *
 *  Table of Contents:
 *
 *  Revision History:
 *     12/01/2012   Steven Okai     Initial revision.
 *     12/21/2012   Shir Aharon     Alignment
 *
 *
 */

#include <avr/io.h>
#include "analogcmp.h"
#include "genio.h"

#define AC_ACMUXCTRL_OFFSET 0x02;
#define AC_CTRLA_OFFSET     0x04;

// TODO: make modifier for voltage scaler (decide whether to make separate function or not)
// TODO: make modifier for cmp output to pin
void SetSignalCmp(uint8_t *analogCmp, uint8_t cmpNum, uint8_t hysteresis, uint8_t intMode,
                  uint8_t intLevel, uint8_t posIn, uint8_t negIn) {

    uint8_t *ACCTRL;
    uint8_t *ACMUXCTRL;
    uint8_t *CTRLA;

    // Get address of control registers
    ACCTRL = analogCmp + cmpNum;
    ACMUXCTRL = analogCmp + AC_ACMUXCTRL_OFFSET + cmpNum;
    CTRLA = analogCmp + AC_CTRLA_OFFSET;

    // TODO: Change constants so shifts are unnecessary
    // Set interrupt mode/level and hysteresis mode, then enable the comparator
    *ACCTRL = ((intMode << 6) | (intLevel << 4) | (hysteresis << 1) | (uint8_t) (AC_ENABLE)) | (0x8);

    // TODO: Clean up how positive and negative inputs get assigned
    // Assign +/- inputs for comparator
    *ACMUXCTRL = ((posIn << 3) | (negIn));

    *CTRLA = 3;

    SetPinDirection(0x0600, 7, IO_DIR_OUTPUT);

    return;

}
