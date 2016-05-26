/*
  Section: Included Files
 */
#include "eusart1.h"
#include <stdio.h>

/**
  Section: Macro Declarations
 */
#define EUSART1_TX_BUFFER_SIZE 8
#define EUSART1_RX_BUFFER_SIZE 8

/**
  Section: Global Variables
 */

static uint8_t eusart1TxHead = 0;
static uint8_t eusart1TxTail = 0;
static uint8_t eusart1TxBuffer[EUSART1_TX_BUFFER_SIZE];
volatile uint8_t eusart1TxBufferRemaining;

static uint8_t eusart1RxHead = 0;
static uint8_t eusart1RxTail = 0;
static uint8_t eusart1RxBuffer[EUSART1_RX_BUFFER_SIZE];
volatile uint8_t eusart1RxCount;

/**
  Section: EUSART1 APIs
 */

void EUSART1_Initialize(void) {
    // disable interrupts before changing states
    PIE1bits.RC1IE = 0;
    PIE1bits.TX1IE = 0;

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


    // initializing the driver state
    eusart1TxHead = 0;
    eusart1TxTail = 0;
    eusart1TxBufferRemaining = sizeof (eusart1TxBuffer);

    eusart1RxHead = 0;
    eusart1RxTail = 0;
    eusart1RxCount = 0;

    // enable receive interrupt
    PIE1bits.RC1IE = 1;
}

uint8_t EUSART1_Read(void) {
    uint8_t readValue = 0;

    while (0 == eusart1RxCount) {
    }

    PIE1bits.RC1IE = 0;

    readValue = eusart1RxBuffer[eusart1RxTail++];
    if (sizeof (eusart1RxBuffer) <= eusart1RxTail) {
        eusart1RxTail = 0;
    }
    eusart1RxCount--;
    PIE1bits.RC1IE = 1;

    printf("%d ", readValue);
    return readValue;
}

void EUSART1_Write(uint8_t txData) {
    while (0 == eusart1TxBufferRemaining) {
    }

    if (0 == PIE1bits.TX1IE) {
        TXREG1 = txData;
    } else {
        PIE1bits.TX1IE = 0;
        eusart1TxBuffer[eusart1TxHead++] = txData;
        if (sizeof (eusart1TxBuffer) <= eusart1TxHead) {
            eusart1TxHead = 0;
        }
        eusart1TxBufferRemaining--;
    }
    PIE1bits.TX1IE = 1;
}

void EUSART1_Transmit_ISR(void) {

    // add your EUSART1 interrupt custom code
    if (sizeof (eusart1TxBuffer) > eusart1TxBufferRemaining) {
        TXREG1 = eusart1TxBuffer[eusart1TxTail++];
        if (sizeof (eusart1TxBuffer) <= eusart1TxTail) {
            eusart1TxTail = 0;
        }
        eusart1TxBufferRemaining++;
    } else {
        PIE1bits.TX1IE = 0;
    }
}

void EUSART1_Receive_ISR(void) {
    if (1 == RC1STAbits.OERR) {
        // EUSART1 error - restart

        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }

    // buffer overruns are ignored
    eusart1RxBuffer[eusart1RxHead++] = RCREG1;
    if (sizeof (eusart1RxBuffer) <= eusart1RxHead) {
        eusart1RxHead = 0;
    }
    eusart1RxCount++;
    if(eusart1RxCount == expected_answer_length){
        answer_status = 2;
    }
}

void clearBuffer() {
    while(eusart1RxCount)
        EUSART1_Read();
}

void serial1Write(uint8_t * buf, uint8_t size){
    for(uint8_t i = 0 ; i < size ; i++)
        EUSART1_Write(buf[i]);
}
/**
  End of File
 */
