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
 *     12/21/2012   Shir Aharon     Include guard, alignment
 *
 */

// Include guard
#ifndef __ANALOG_CMP__
#define __ANALOG_CMP__

#define AC_HYSMODE_OFF      0x00
#define AC_HYSMODE_SMALL    0x01
#define AC_HYSMODE_LARGE    0x02

#define AC_POS_IN_PIN0      0x00
#define AC_POS_IN_PIN1      0x01
#define AC_POS_IN_PIN2      0x02
#define AC_POS_IN_PIN3      0x03
#define AC_POS_IN_PIN4      0x04
#define AC_POS_IN_PIN5      0x05
#define AC_POS_IN_PIN6      0x06
#define AC_POS_IN_DAC       0x07

#define AC_NEG_IN_PIN0      0x00
#define AC_NEG_IN_PIN1      0x01
#define AC_NEG_IN_PIN3      0x02
#define AC_NEG_IN_PIN5      0x03
#define AC_NEG_IN_PIN7      0x04
#define AC_NEG_IN_DAC       0x05
#define AC_NEG_IN_BANDGAP   0x06
#define AC_NEG_IN_SCALER    0x07

#define AC_INTMODE_BOTHEDGES    0x00
#define AC_INTMODE_FALLING      0x02
#define AC_INTMODE_RISING       0x03

#define AC_ENABLE           0x01

void SetSignalCmp(uint8_t *analogCmp, uint8_t cmpNum, uint8_t hysteresis, uint8_t intMode, uint8_t intLevel, uint8_t posIn, uint8_t negIn);

#endif //__ANALOG_CMP__
