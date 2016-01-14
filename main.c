#include "mcc_generated_files/mcc.h"
#include "i2c-interface.h"
#include "mcc_generated_files/eusart1.h"
#include "ax12.h"

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

    while (1) {
        EUSART1_Initialize();
        restart(axid);  
        restart(axid2);
        axWrite(axid, 24, 1); // Enable Torque
        axWrite(axid2, 24, 1);
        //delay(100);
        axWrite(axid, 18, 2); // Shutdown ssi surchauffe
        axWrite(axid2, 18, 2);
        //delay(100);
        setWheelMode(axid);
        setWheelMode(axid2);  
        //delay(100);
        setAxSpeed(axid, 1023);
        setAxSpeed(axid2, 2047);
        while(1);
    }
}
/**
 End of File
 */