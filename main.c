#include "mcc_generated_files/mcc.h"
#include "i2c-interface.h"
#include "ax12.h"
#include "power.h"
#include "misc.h"
#include "mcc_generated_files/pin_manager.h"
#include <stdio.h>
/*
                         Main application
 */
void main(void) {
    // Initialize the device
    SYSTEM_Initialize();
    // Initialize the I2C interface
    configureI2Cinterface();
    
    // Enable high priority global interrupts
    INTERRUPT_GlobalInterruptHighEnable();
    // Enable low priority global interrupts.
    INTERRUPT_GlobalInterruptLowEnable();
    
    ax12Setup();
    while (1) {
        ax12Manager();
        /*sensorManager();
        collisionManager();
        powerManager();*/
    }
}
/**
 End of File
 */