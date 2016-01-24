
#include <xc.h>
#include "ccp5.h"
#include "tmr1.h"
#include "../power.h"

/**
  Section: Capture Module APIs
 */

void CCP5_Initialize(void) {
    // Set the CCP5 to the options selected in the User Interface

    // DC5B LSBs; CCP5M capture_risingedge; 
    CCP5CON = 0x05;

    // CCPR5L 0x0; 
    CCPR5L = 0x00;

    // CCPR5H 0x0; 
    CCPR5H = 0x00;

    // Clear the CCP5 interrupt flag
    PIR4bits.CCP5IF = 0;

    // Enable the CCP5 interrupt
    PIE4bits.CCP5IE = 1;

    // Selecting Timer1
    CCPTMRS1bits.C5TSEL = 0x0;
}

void CCP5_CaptureISR(void) {
    CCP_PERIOD_REG_T module;

    // Clear the CCP5 interrupt flag
    PIR4bits.CCP5IF = 0;

    // Copy captured value.
    module.ccpr5l = CCPR5L;
    module.ccpr5h = CCPR5H;

    TMR1_WriteTimer(0);
    setCCP5period(module.ccpr5_16Bit);
}

/**
 End of File
 */