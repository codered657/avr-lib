/*
 *  AVR Ring Buffer Library
 *
 *  Description: This files contains functions for using ring buffers.
 *
 *  Table of Contents:
 *
 *  Revision History:
 *     12/01/2012   Steven Okai     Initial revision.
 *
 *
 */

// TODO: Set to use preprocessor to generalize out the avr include statements
#include <avr/io.h>

typedef struct {

    // Head pointer
    uint8_t headPtr;
    
    // Tail pointer
    uint8_t tailPtr;
    
    // Number of elements currently in queue
    uint8_t numElements;
    
    // Size of the array for the buffer
    uint8_t arraySize;
    
    // Pointer to the array used as the buffer
    uint8_t *bufferArray;
    
} RingBuf;

void InitRingBuf(RingBuf *buffer, uint8_t arraySize, uint8_t *bufferArray) {
    
    // Initialize the head and tail pointers to empty condition
    buffer->headPtr = 0;
    buffer->tailPtr = 0;
    
    // No elements in buffer initially
    buffer->numElements = 0;
    
    // Set the size of the array for the buffer
    buffer->arraySize = arraySize;
    
    // Set pointer the actual buffer array
    buffer->bufferArray = bufferArray;
    
    return;
    
}