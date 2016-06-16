/* 
 * File:   interrupts.h
 * Author: Arnaud "JS" Bonetti
 *
 * contains methods the send interrupts to the Raspberry Pi
 */

#ifndef INTERRUPTS_H
#define	INTERRUPTS_H

#include <stdint.h>

typedef enum {
    SENSOR_CHANGE = 0x04,
    COLLISION_CHANGE = 0x08
} interrupt_source;

// get all the set flags. Once read all the flags are cleared, and INTOUT is set as INPUT
int8_t readStatus();

// send an interrupt to the raspberry pi
void raiseInterrupt(interrupt_source src);

#endif	/* INTERRUPTS_H */

