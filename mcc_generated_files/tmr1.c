
/**
  Section: Included Files
 */

#include <xc.h>
#include "tmr1.h"
#include "../power.h"
/**
  Section: Global Variable Definitions
 */
volatile uint16_t timer1ReloadVal;

/**
  Section: TMR1 APIs
 */

void TMR1_Initialize(void) {
    //Set the Timer to the options selected in the GUI

    //T1CKPS 1:8; TMR1CS FOSC/4; T1OSCEN disabled; T1SYNC do_not_synchronize; T1RD16 disabled; TMR1ON disabled; 
    T1CON = 0x34;

    //T1GTM disabled; T1GGO done; T1GPOL low; T1GVAL disabled; TMR1GE disabled; T1GSS T1G; T1GSPM disabled; 
    T1GCON = 0x00;

    //TMR1H 0; 
    TMR1H = 0x00;

    //TMR1L 0; 
    TMR1L = 0x00;

    // Load the TMR value to reload variable
    timer1ReloadVal = TMR1;

    // Clearing IF flag before enabling the interrupt.
    PIR1bits.TMR1IF = 0;

    // Enabling TMR1 interrupt.
    PIE1bits.TMR1IE = 1;

    // Start TMR1
    TMR1_StartTimer();
}

void TMR1_StartTimer(void) {
    // Start the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 1;
}

void TMR1_StopTimer(void) {
    // Stop the Timer by writing to TMRxON bit
    T1CONbits.TMR1ON = 0;
}

uint16_t TMR1_ReadTimer(void) {
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;

    readValLow = TMR1L;
    readValHigh = TMR1H;

    readVal = ((uint16_t) readValHigh << 8) | readValLow;

    return readVal;
}

void TMR1_WriteTimer(uint16_t timerVal) {
    if (T1CONbits.T1SYNC == 1) {
        // Stop the Timer by writing to TMRxON bit
        T1CONbits.TMR1ON = 0;

        // Write to the Timer1 register
        TMR1H = (timerVal >> 8);
        TMR1L = (uint8_t) timerVal;

        // Start the Timer after writing to the register
        T1CONbits.TMR1ON = 1;
    } else {
        // Write to the Timer1 register
        TMR1H = (timerVal >> 8);
        TMR1L = (uint8_t) timerVal;
    }
}

void TMR1_Reload(void) {
    // Write to the Timer1 register
    TMR1H = (timer1ReloadVal >> 8);
    TMR1L = (uint8_t) timer1ReloadVal;
}

void TMR1_StartSinglePulseAcquisition(void) {
    T1GCONbits.T1GGO = 1;
}

uint8_t TMR1_CheckGateValueStatus(void) {
    return T1GCONbits.T1GVAL;
}

void TMR1_ISR(void) {

    // Clear the TMR1 interrupt flag
    PIR1bits.TMR1IF = 0;

    // Write to the Timer1 register
    TMR1H = (timer1ReloadVal >> 8);
    TMR1L = (uint8_t) timer1ReloadVal;

    // next CCP5 measure won't be valid
    setCCP5period(0);
}


/**
 End of File
 */
