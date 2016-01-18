
/**
  Section: Included Files
 */
#include "eusart1.h"

/**
  Section: EUSART1 APIs
 */

void EUSART1_Initialize(void) {
    // Set the EUSART1 module to the options selected in the user interface.

    // ABDOVF no_overflow; RCIDL idle; BRG16 16bit_generator; WUE disabled; CKTXP async_noninverted_sync_fallingedge; ABDEN disabled; DTRXP not_inverted; 
    BAUD1CON = 0x48;

    // SPEN enabled; OERR no_error; RX9 8-bit; RX9D 0x0; CREN enabled; ADDEN disabled; SREN disabled; FERR no_error; 
    RC1STA = 0x90;

    // TRMT TSR_empty; TX9 8-bit; TX9D 0x0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave_mode; 
    TX1STA = 0x26;

    // Baud Rate = 115200; SPBRGL 34; 
    SPBRG1 = 0x22;

    // Baud Rate = 115200; SPBRGH 0; 
    SPBRGH1 = 0x00;

}

uint8_t EUSART1_Read(void) {

    while (!PIR1bits.RC1IF) {
    }

    if (1 == RC1STAbits.OERR) {
        // EUSART1 error - restart

        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }

    return RCREG1;
}

void EUSART1_Write(uint8_t txData) {
    while (0 == PIR1bits.TX1IF) {
    }

    TXREG1 = txData; // Write the data byte to the USART.
}
/**
  End of File
 */
