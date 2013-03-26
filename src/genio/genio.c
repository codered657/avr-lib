/*
 *  AVR General I/O Library
 *
 *  Description:    This files contains functions and definitions for
 *                  AVR general I/O.
 *
 *  Table of Contents:
 *
 *  Revision History:
 *     12/02/2012   Steven Okai     Initial revision.
 *     12/21/2012   Shir Aharon     Alignment, moved constants to general file
 *
 */

#include <avr/io.h>
#include "genio.h"
#include "../general/global_def.h"    // Used for true/false definitions


void EnablePinInt(uint8_t *port, uint8_t pin, uint8_t intNum, uint8_t intLevel,
                  uint8_t intType, uint8_t inverted) {

    uint8_t *INTMASK;
    uint8_t *INTCTRL;
    uint8_t *PINCTRL;

    // Get addresses of registers
    INTMASK = port + IO_INTMASK_BASE_OFFSET + intNum;
    INTCTRL = port + IO_INTCTRL_OFFSET;

    // Set pin to input
    SetPinDirection(port, pin, IO_DIR_INPUT);

    // Set to interrupt off of input to pin
    // TODO: Write function to be able to generate interrupts off of additional pins
    *INTMASK = (1 << pin);

    // Set interrupt level
    *INTCTRL = intLevel;

    // Set whether pin is inverted or not
    SetPinInversion(port, pin, inverted);

    // Set interrupt type (edge, level, etc.)
    SetPinSense(port, pin, intType);

    return;

}

void SetPinDirection(uint8_t *port, uint8_t pin, uint8_t direction) {

    uint8_t *DIRCLR;
    uint8_t *DIRSET;

    // Get address of registers
    DIRCLR = port + IO_DIRCLR_OFFSET;
    DIRSET = port + IO_DIRSET_OFFSET;

    if (direction == IO_DIR_OUTPUT) {
    // If specified direction is output, set as so

        // Get address of register to set to output
        DIRSET = port + IO_DIRSET_OFFSET;

        // Set the appropriate pin to output
        *DIRSET = (1 << pin);

    } else {
    // Otherwise, set to input

        // Get the address of register to set to input
        DIRCLR = port + IO_DIRCLR_OFFSET;

        // Set the appropriate pin to input
        *DIRCLR = (1 << pin);

    }

    return;
}

void SetPinInversion(uint8_t *port, uint8_t pin, uint8_t inverted) {

    uint8_t *PINCTRL;
    uint8_t PINCTRLValue;

    // Get address of register
    PINCTRL = port + IO_PINCTRL_BASE_OFFSET + pin;

    // Read PINCTRL register to get previous settings
    PINCTRLValue = *PINCTRL;

    // Add in pin inversion settings
    if (inverted == TRUE) {
    // If set to invert, set invert bit in register
        *PINCTRL = (PINCTRLValue | IO_PINCTRL_INVEN);

    } else {
    // Otherwise, clear the invert bit in register
        *PINCTRL = (PINCTRLValue & (~IO_PINCTRL_INVEN));
    }

    return;

}

void SetPinSense(uint8_t *port, uint8_t pin, uint8_t sense) {

    uint8_t *PINCTRL;
    uint8_t PINCTRLValue;

    // Get address of register
    PINCTRL = port + IO_PINCTRL_BASE_OFFSET + pin;

    // Read PINCTRL register to get previous settings, clearing sense bits
    PINCTRLValue = ((*PINCTRL) & IO_PINCTRL_ISC_CLR_BITS);

    // Set sense bits and write back
    *PINCTRL = (PINCTRLValue | sense);

    return;

}

void SetPortDirection(uint8_t *port, uint8_t direction) {

    uint8_t *DIR;

    // Get address of registers
    DIR = port + IO_DIR_OFFSET;

    if (direction == IO_DIR_OUTPUT) {
    // If specified direction is output, set as so
        *DIR = IO_DIR_ALL_OUTPUT;

    } else {
    // Otherwise, set to input
        *DIR = IO_DIR_ALL_INPUT;

    }

    return;

}

void SetPin(uint8_t *port, uint8_t pin, uint8_t pinValue) {

    uint8_t *OUTSET;
    uint8_t *OUTCLR;

    // Get addresses port registers
    OUTSET = port + IO_OUTSET_OFFSET;
    OUTCLR = port + IO_OUTCLR_OFFSET;

    if (pinValue == IO_PIN_LOW) {
    // Set desired bit of OUTCLR register to clear pin
        *OUTCLR = (1 << pin);

    } else {
        // Set desired bit of OUTSET register to set pin
        *OUTSET = (1 << pin);

    }

    return;

}

void SetPort(uint8_t *port, uint8_t portValue) {

    uint8_t *OUTPUT;

    // Get address of output register for port
    OUTPUT = port + IO_OUT_OFFSET;

    // Output passed value on the port
    *OUTPUT = portValue;

    return;

}