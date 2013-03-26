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
 *
 *
 */

typedef struct {
    
    // Pointer to key input port
    uint8_t *keysInPort;
    
    // Pointer to key interrupt port
    uint8_t *keyInterruptPort;
    
    // Pointer to keypad acknowledge port
    uint8_t *keyAckPort;
    
    // Bit pattern for acknowledging keypad read
    uint8_t ackPortBit;
    
    // Key available flag
    uint8_t keyAvailable;
    
    // Debounced key
    uint8_t debouncedKey;
    
} Keypad;

void InitKeypad(Keypad *keypad, uint8_t *keysInPort, uint8_t *keyInterruptPort, uint8_t intPin, uint8_t *keyAckPort, uint8_t ackPin);
void ReadKeypad(Keypad *keypad);
uint8_t KeyAvailable(Keypad *keypad);
uint8_t GetKey(Keypad *keypad);
