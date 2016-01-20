#include "power.h"
#include "mcc_generated_files/adc.h"
#include <xc.h>
#include <stdint.h>

// if the battery voltage is under this threshold (about 6V), the battery is likely 
// to be either disconnect or kaput (Ja, Ja, Ja). Power level will be 0
#define LOW_THRESHOLD 433

uint8_t logicPowerLevel = 0;

inline void powerManager() {
    static unsigned char counter = 0;
    if(ADC_IsConversionDone()) {
        counter++;
        // skip some calls to wait inbetween conversions
        if(counter&0x80) { 
            counter = 0;
            ADC_StartConversion(channel_AN0);
        } else if(!counter) { // means a conversion has just finished
            uint16_t powerLevel = ADC_GetConversionResult();
            if(powerLevel < LOW THRESHOLD) {
                logicPowerLevel = 0;
            } else {
                logicPowerLevel = (powerLevel - LOW_THRESHOLD) >> 1;
            }
        } 
    }
}