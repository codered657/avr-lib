/*
 *  AVR MAX6818 Keypad Debouncer Library
 *
 *  Description:    This files contains functions for using and
 *                  accessing the MAX6818 keypad debouncer.
 *
 *  Table of Contents:
 *
 *  Revision History:
 *     12/01/2012   Steven Okai     Initial revision.
 *     12/21/2012   Shir Aharon     Alignment, moved constants to general file
 *
 */

// TODO: Set to use preprocessor to generalize out the avr include statements
#include <avr/io.h>
#include <util/atomic.h>
#include "max6818.h"
#include "genio.h"
#include "../general/global_def.h"    // Used for true/false definitions

// TODO: add bit number arguments for which bit of ports to use for interrupt and acknowledge
void InitKeypad(Keypad *keypad, uint8_t *keysInPort, uint8_t *keyInterruptPort,
                uint8_t intPin, uint8_t *keyAckPort, uint8_t ackPin) {

    uint8_t *keyAckPort_DIRSET;
    uint8_t *keysInPort_DIR;
    uint8_t *keyInterruptPort_DIRCLR;

    // Get addresses of registers
    keyAckPort_DIRSET = keyAckPort + IO_DIRSET_OFFSET;
    keysInPort_DIR = keysInPort + IO_DIR_OFFSET;
    keyInterruptPort_DIRCLR = keyInterruptPort + IO_DIRCLR_OFFSET;

    // Set the port to use as the keypad parallel input
    keypad->keysInPort = keysInPort;

    // Set the port used for interrupts for the keypad
    keypad->keyInterruptPort = keyInterruptPort;

    // Set the port used for keypad acknowledge
    keypad->keyAckPort = keyAckPort;

    // No key initially available
    keypad->keyAvailable = FALSE;

    // Set up interrupts for the keypad
    // Set to active low level triggering to match MAX6818 nCH pin
    //EnablePinInt(keyInterruptPort, intPin, 0, INT_LEVEL_HIGH, IO_PINCTRL_ISC_LEVEL, TRUE);
    //EnablePinInt(keyInterruptPort, intPin, 0, INT_LEVEL_HIGH, IO_PINCTRL_ISC_RISING, TRUE);
    EnablePinInt(keyInterruptPort, intPin, 0, INT_LEVEL_HIGH, IO_PINCTRL_ISC_FALLING, TRUE);

    // Set interrupt pin to input
    SetPinDirection(keyInterruptPort, intPin, IO_DIR_INPUT);

    // Set up keypad acknowledge port
    //keypad->ackPortBit = (1 << ackPin); // Specify which bit to use
    keypad->ackPortBit = ackPin; // Specify which bit to use
    SetPinDirection(keyAckPort, ackPin, IO_DIR_OUTPUT); // Set ack pin to output
    SetPin(keyAckPort, ackPin, IO_PIN_LOW); // Initially disabled (active low)
    SetPin(keyAckPort, ackPin, IO_PIN_HIGH); // Initially disabled (active low)

    // Set key input port to all inputs
    SetPortDirection(keysInPort, IO_DIR_INPUT);

    return;

}

// Interrupt handler
void ReadKeypad(Keypad *keypad) {

    uint8_t *OUTSET;
    uint8_t *OUTCLR;
    uint8_t *KEYIN_REG;

    // Get addresses of registers
    OUTSET = (keypad->keyAckPort) + IO_OUTSET_OFFSET;
    OUTCLR = (keypad->keyAckPort) + IO_OUTCLR_OFFSET;
    KEYIN_REG = (keypad->keysInPort) + IO_IN_OFFSET;

    // Enable reads from the debouncer (active low)
    SetPin(keypad->keyAckPort, keypad->ackPortBit, IO_PIN_LOW);

    // Read the key press from the debouncer
    keypad->debouncedKey = (*KEYIN_REG);

    // Mark that a key is available
    keypad->keyAvailable = TRUE;

    // Disable the debouncer again to acknowledge the read (active low)
    SetPin(keypad->keyAckPort, keypad->ackPortBit, IO_PIN_HIGH);

    return;
}

uint8_t KeyAvailable(Keypad *keypad) {

    // Return whether key is available or not
    return (keypad->keyAvailable);

}

uint8_t GetKey(Keypad *keypad) {

    uint8_t keys;

    // TODO: might not need to do atomically if willing to lose a key
    // Make sure execute atomically to prevent lost key
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {

        // Get the debounced key
        keys = keypad->debouncedKey;

        // Clear the key available flag to acknowledge
        keypad->keyAvailable = FALSE;

    }

    return keys;

}
