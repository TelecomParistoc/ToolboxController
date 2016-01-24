
#include <xc.h>
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void) {
    LATA = 0x00;
    TRISA = 0x03;
    ANSELA = 0x03;

    LATB = 0x00;
    TRISB = 0xFF;
    ANSELB = 0x00;
    WPUB = 0x00;

    LATC = 0x18;
    TRISC = 0xF8;
    ANSELC = 0x00;

    LATD = 0x00;
    TRISD = 0xFC;
    ANSELD = 0x00;

    LATE = 0x00;
    TRISE = 0x04;
    ANSELE = 0x00;

    INTCON2bits.nRBPU = 0x01;


}
/**
 End of File
 */