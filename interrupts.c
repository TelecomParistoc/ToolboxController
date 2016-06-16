#include "interrupts.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/interrupt_manager.h"
#include <xc.h>
#include <stdio.h>

uint8_t interruptFlags = 0;

// get all the set flags. Once read all the flags are cleared
int8_t readStatus() {
    int8_t status = interruptFlags;
    INTOUT_SetDigitalInput();
    interruptFlags = 0;
    return status;
}

void raiseInterrupt(interrupt_source src) {
    interruptFlags |= (uint8_t) src;
    INTOUT_SetDigitalOutput();
    INTOUT_SetHigh();
}

