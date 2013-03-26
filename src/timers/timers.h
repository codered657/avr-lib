/*
 *  AVR Timer Library
 *
 *  Description: This files contains functions for using the AVR Timers.
 *
 *  Table of Contents:
 *
 *  Revision History:
 *     11/16/2012   Steven Okai     Initial revision.
 *
 *
 */

#include <avr/io.h>

#define NUM_PRESCALE_MODES 7
#define TIMER_CTRLA_OFFSET 0x00
#define TIMER_CTRLB_OFFSET 0x01
#define TIMER_CTRLC_OFFSET 0x02
#define TIMER_CTRLD_OFFSET 0x03
#define TIMER_CTRLE_OFFSET 0x04
#define TIEMR_CCA_OFFSET 0x028
#define TIMER_CCAL_OFFSET 0x28
#define TIMER_CCAH_OFFSET 0x29
#define TIMER_INTCTRLA_OFFSET 0x06
#define TIMER_INTCTRLB_OFFSET 0x07
#define TIMER_PER_OFFSET 0x26

#define TIMER_PRESCALE_1 1
#define TIMER_PRESCALE_2 2
#define TIMER_PRESCALE_4 3
#define TIMER_PRESCALE_8 4
#define TIMER_PRESCALE_64 5 
#define TIMER_PRESCALE_256 6
#define TIMER_PRESCALE_1024 7

//void FreqGenMode(uint8_t *timer, uint8_t *outputPort, float freq);
void TickMode(uint8_t *toneTimer, uint8_t *tickTimer, float tickFreq);
void SetNormalMode(uint8_t *timer, uint16_t maxCount, uint8_t prescaleMode, uint8_t intLevel);
void DisableTimer(uint8_t *timer);
void EnableTimer(uint8_t *timer, uint8_t intLevel);
void FreqGenMode(uint8_t *timer, uint8_t *outputPort, uint8_t prescaleMode, uint16_t CCA);
