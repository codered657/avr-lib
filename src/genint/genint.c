/*
 *  AVR General Interrupt Library
 *
 *  Description:    This files contains functions and definitions for
 *                  AVR general interrupts.
 *
 *  Table of Contents:
 *
 *  Revision History:
 *     12/09/2012   Steven Okai     Initial revision.
 *     12/21/2012   Shir Aharon     Alignment
 *
 */

#include <avr/io.h>
#include "genint.h"

#define INT_PMIC_CTRL_OFFSET    0x02
#define INT_PMIC_BASE_ADDRESS   0x00A0

EnableIntLevel(uint8_t level) {

    uint8_t *CTRL;

    // Get address of interrupt control register
    CTRL = INT_PMIC_BASE_ADDRESS + INT_PMIC_CTRL_OFFSET;

    // Set correct bit to enable desired interrupt level
    *CTRL = (*CTRL) | (level << 1);

    return;

}
