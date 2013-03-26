/*
 *  AVR Timer Library
 *
 *  Description: This files contains functions for using the AVR Timers.
 *
 *  Table of Contents:
 *
 *  Revision History:
 *     11/16/2012   Steven Okai     Initial revision.
 *     12/21/2012   Shir Aharon     Alignment, moved constants to general file
 *
 */

#include <avr/io.h>
#include <util/atomic.h>
#include "timers.h"
#include "genio.h"
#include "../general/global_def.h"    // Used for byte masks definitions

#define MIN_CCA             100

#define PORT_DIRSET_OFFSET  0x01;

#define NORMAL_MODE         0x00
#define FREQ_MODE           0x01
#define CCAEN               0x10
#define NO_EVENT_ACTION     0x00

#define INT_LEVEL_DISABLED  0x00
#define INT_LEVEL_LOW       0x01
#define INT_LEVEL_MED       0x02
#define INT_LEVEL_HIGH      0x03

// Array of prescale modes
const static uint16_t PrescalerModes[NUM_PRESCALE_MODES] = {1, 2, 4, 8, 64, 256, 1024};

// Function prototypes
//void FreqGenMode(uint8_t *timer, uint8_t *outputPort, float freq);
void TickMode(uint8_t *toneTimer, uint8_t *tickTimer, float tickFreq);

/*
void FreqGenMode(uint8_t *timer, uint8_t *outputPort, float freq) {

    uint8_t *CTRLA;
    uint8_t *CTRLB;
    uint8_t *CCAL;
    uint8_t *CCAH;
    uint8_t *DIRSET;
    uint16_t CCA = 0;

    // Get address of registers
    CTRLA = timer + TIMER_CTRLA_OFFSET;
    CTRLB = timer + TIMER_CTRLB_OFFSET;
    CCAL = timer + TIMER_CCAL_OFFSET;
    CCAH = timer + TIMER_CCAH_OFFSET;
    DIRSET = outputPort + PORT_DIRSET_OFFSET;

    // Set mode to frequency mode
    uint8_t i = NUM_PRESCALE_MODES;

    // TODO: Can change this to look at the percent difference between the float
    //       and int-truncated CCA to see if precision is acceptable
    // Try all prescalers, starting from the largest, until minimum precision is met
    while ((CCA < MIN_CCA) && (i > 0)) {

        // Try next prescale mode
        i--;

        // Get the CCA value for specified frequency and prescaler
        uint16_t CCA = (uint16_t) FREQ_CLK_PER/(2*PrescalerModes[i]*freq);

        // Make sure CCA won't be negative
        if (CCA >= 1) {
            // Subtract 1 to get final CCA
            CCA -= 1;

        } else {
            // Otherwise default to 0
            CCA = 0;

        }

    }

    // Set Control Register A with correct prescale mode
    *CTRLA = i + 1; // Add 1 to the prescale index to accommodate for OFF mode

    // Set CCA for desire frequency
    // Set the low byte of the CCA
	*CCAL = CCA & LOW_BYTE_MASK;

	// Set the high byte of the CCA
	*CCAH = (CCA & HIGH_BYTE_MASK) >> 8;

    // Set to Frequency Generation Mode
    *CTRLB = FREQ_MODE | CCAEN;

    // Set pin on port to output waveform
    *DIRSET = 0x01;

    return;
}
*/


void FreqGenMode(uint8_t *timer, uint8_t *outputPort, uint8_t prescaleMode, uint16_t CCA) {

    // Declare pointers to control registers
    uint8_t *CTRLA;
    uint8_t *CTRLB;
    uint8_t *CCAL;
    uint8_t *CCAH;
    uint8_t *DIRSET;

    // Get address of registers
    CTRLA = timer + TIMER_CTRLA_OFFSET;
    CTRLB = timer + TIMER_CTRLB_OFFSET;
    CCAL = timer + TIMER_CCAL_OFFSET;
    CCAH = timer + TIMER_CCAH_OFFSET;
    DIRSET = outputPort + PORT_DIRSET_OFFSET;

    // Set Control Register A with correct prescale mode
    *CTRLA = prescaleMode;

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {

        // Set CCA for desire frequency
        *CCAL = CCA & LOW_BYTE_MASK; // Set the low byte of the CCA
        *CCAH = (CCA & HIGH_BYTE_MASK) >> 8; // Set the high byte of the CCA

    }

    // Set to Frequency Generation Mode
    *CTRLB = FREQ_MODE | CCAEN;

    // Set pin on port to output waveform
    SetPinDirection(outputPort, 0, IO_DIR_OUTPUT);
    //*DIRSET = 0x01;

    return;

}

void TickMode(uint8_t *toneTimer, uint8_t *tickTimer, float tickFreq) {

    // See if desired tick rate can be accomplished with 1 timer

        // If so, then set 1st tick timer

        // If not, then set both tick timers

    // Set tone generation timer

    // Install handler

    // NOTE: may need to disable interrupts during this function

    // Need constant for dominant tick and offbeat tick

    return;
}

void SetNormalMode(uint8_t *timer, uint16_t maxCount, uint8_t prescaleMode, uint8_t intLevel) {

    uint8_t *CTRLA;
    uint8_t *CTRLB;
    uint8_t *CTRLC;
    uint8_t *CTRLD;
    uint8_t *CTRLE;
    uint8_t *INTCTRLA;
    uint16_t *PER;

    // Get address of registers
    CTRLA = timer + TIMER_CTRLA_OFFSET;
    CTRLB = timer + TIMER_CTRLB_OFFSET;
    CTRLC = timer + TIMER_CTRLC_OFFSET;
    CTRLD = timer + TIMER_CTRLD_OFFSET;
    CTRLE = timer + TIMER_CTRLE_OFFSET;
    INTCTRLA = timer + TIMER_INTCTRLA_OFFSET;
    PER = timer + TIMER_PER_OFFSET;

    // Set prescaler for the timer
    //*CTRLA = prescaleMode; // Ctrl register value is prescale mode + 1
    *CTRLA = 7;

    // Set timer to normal mode
    *CTRLB = NORMAL_MODE;

    //
    *CTRLC = 0;

    // No event actions used
    *CTRLD = NO_EVENT_ACTION;

    // Set counter to normal mode (16-bit)
    *CTRLE = NORMAL_MODE;

    // Enable interrupts on overflow
    EnableTimer(timer, intLevel);

    // Set max count for the timer
    *PER = maxCount;

    return;

}

void DisableTimer(uint8_t *timer) {

    uint8_t *INTCTRLA;
    INTCTRLA = timer + TIMER_INTCTRLA_OFFSET;

    // Disable the timer
    *INTCTRLA = INT_LEVEL_DISABLED;

    return;

}

void EnableTimer(uint8_t *timer, uint8_t intLevel) {

    uint8_t *INTCTRLA;
    INTCTRLA = timer + TIMER_INTCTRLA_OFFSET;

    // Enable timer with passed level
    *INTCTRLA = intLevel;

    return;

}
