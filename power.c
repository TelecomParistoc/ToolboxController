#include "power.h"
#include "mcc_generated_files/adc.h"
#include <xc.h>

// if the battery voltage is under this threshold (about 6V), the battery is likely 
// to be either disconnect or kaput (Ja, Ja, Ja). Power level will be 0
#define LOGIC_LOW_THRESHOLD 433
#define MOTOR_LOW_THRESHOLD 175

uint8_t logicPowerLevel = 0;
uint8_t motorPowerLevel = 0;

uint16_t motorPowerLevelPeriod = 0;

inline void powerManager() {
    static unsigned char counter = 0;
    if(ADC_IsConversionDone()) {
        // skip some calls to wait in between conversions
        if(counter&0x80) { 
            counter = 0;
            ADC_StartConversion(channel_AN0);
        } else {
            if(!counter) { // means a conversion has just finished
                uint16_t powerLevel = ADC_GetConversionResult();
                if(powerLevel < LOGIC_LOW_THRESHOLD) {
                    logicPowerLevel = 0;
                } else {
                    logicPowerLevel = (powerLevel - LOGIC_LOW_THRESHOLD) >> 1;
                }
            }
            counter++;
        }
    }
    if(motorPowerLevelPeriod) {
        motorPowerLevelPeriod = (motorPowerLevelPeriod >> 1);
        if(motorPowerLevelPeriod < MOTOR_LOW_THRESHOLD)
            motorPowerLevel = 0;
        else {
            motorPowerLevelPeriod -= MOTOR_LOW_THRESHOLD;
            if(motorPowerLevelPeriod > 255)
                motorPowerLevel = 255;
            else
                motorPowerLevel = motorPowerLevelPeriod;
        }
        motorPowerLevelPeriod = 0;
    }
}

void setCCP5period(uint16_t period) {
    static char isValid = 0;
    // if timer overflown, ignore next measure
    if(period == 0) {
        isValid = 0;
        return;
    }
    if(isValid)
        motorPowerLevelPeriod = period;
    isValid = 1;
}