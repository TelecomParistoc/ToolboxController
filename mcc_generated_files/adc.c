
/**
  Section: Included Files
 */

#include <xc.h>
#include "adc.h"

/**
  Section: ADC Module APIs
 */

void ADC_Initialize(void) {
    // set the ADC to the options selected in the User Interface

    // GO_nDONE stop; ADON enabled; CHS AN0; 
    ADCON0 = 0x01;

    // PVCFG VDD; TRIGSEL CTMU; NVCFG VSS; 
    ADCON1 = 0x80;

    // ADFM right; ACQT 20; ADCS FOSC/64; 
    ADCON2 = 0xBE;

    // ADRESL 0x0; 
    ADRESL = 0x00;

    // ADRESH 0x0; 
    ADRESH = 0x00;

}

void ADC_StartConversion(adc_channel_t channel) {
    // select the A/D channel
    ADCON0bits.CHS = channel;

    // Turn on the ADC module
    ADCON0bits.ADON = 1;


    // Start the conversion
    ADCON0bits.GO_nDONE = 1;
}

bool ADC_IsConversionDone() {
    // Start the conversion
    return (!ADCON0bits.GO_nDONE);
}

adc_result_t ADC_GetConversionResult(void) {
    // Conversion finished, return the result
    return ((ADRESH << 8) + ADRESL);
}

adc_result_t ADC_GetConversion(adc_channel_t channel) {
    // Select the A/D channel
    ADCON0bits.CHS = channel;

    // Turn on the ADC module
    ADCON0bits.ADON = 1;


    // Start the conversion
    ADCON0bits.GO_nDONE = 1;

    // Wait for the conversion to finish
    while (ADCON0bits.GO_nDONE) {
    }

    // Conversion finished, return the result
    return ((ADRESH << 8) + ADRESL);
}
/**
 End of File
 */