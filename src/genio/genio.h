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
 *     12/21/2012   Shir Aharon     Include guard, alignment
 *
 */

 // Include guard
#ifndef __GEN_IO__
#define __GEN_IO__

#define IO_DIR_OFFSET           0x00
#define IO_DIRSET_OFFSET        0x01
#define IO_DIRCLR_OFFSET        0x02
#define IO_OUT_OFFSET           0x04
#define IO_OUTSET_OFFSET        0x05
#define IO_OUTCLR_OFFSET        0x06
#define IO_IN_OFFSET            0x08
#define IO_PINCTRL_BASE_OFFSET  0x10
#define IO_INTMASK_BASE_OFFSET  0x0A
#define IO_INTCTRL_OFFSET       0x09

#define IO_DIR_ALL_INPUT        0x00
#define IO_DIR_ALL_OUTPUT       0xFF

#define IO_DIR_OUTPUT           0x01
#define IO_DIR_INPUT            0x00

#define IO_PINCTRL_INVEN        0x40

#define IO_PINCTRL_ISC_CLR_BITS         0x07
#define IO_PINCTRL_ISC_BOTHEDGES        0x00
#define IO_PINCTRL_ISC_RISING           0x01
#define IO_PINCTRL_ISC_FALLING          0x02
#define IO_PINCTRL_ISC_LEVEL            0x03
#define IO_PINCTRL_ISC_INPUT_DISABLED   0x07

#define IO_PIN_LOW              0
#define IO_PIN_HIGH             1

#define INT_LEVEL_DISABLED      0x00
#define INT_LEVEL_LOW           0x01
#define INT_LEVEL_MED           0x02
#define INT_LEVEL_HIGH          0x03

// TODO: Write setup functions for port directions, interrupts, etc

void EnablePinInt(uint8_t *port, uint8_t pin, uint8_t intNum, uint8_t intLevel, uint8_t intType, uint8_t inverted);
void SetPinDirection(uint8_t *port, uint8_t pin, uint8_t direction);
void SetPinInversion(uint8_t *port, uint8_t pin, uint8_t inverted);
void SetPinSense(uint8_t *port, uint8_t pin, uint8_t sense);
void SetPortDirection(uint8_t *port, uint8_t direction);
void SetPin(uint8_t *port, uint8_t pin, uint8_t pinValue);
void SetPort(uint8_t *port, uint8_t portValue);

#endif // __GEN_IO__
