#include "power.h"
#include "mcc_generated_files/adc.h"
#include "mcc_generated_files/pin_manager.h"
#include <xc.h>

// if the battery voltage is under this threshold (about 6V), the battery is likely 
// to be either disconnect or kaput (Ja, Ja, Ja). Power level will be 0
#define LOGIC_LOW_THRESHOLD 433
#define MOTOR_LOW_THRESHOLD 175

#define LOGIC_LOW_BAT 161
#define LOGIC_MIDDLE_BAT 197

#define MOTOR_LOW_BAT 48
#define MOTOR_MIDDLE_BAT 29

// battery voltage = (logicPowerLevel*2 + 433)*0.0139 (in volts)
uint8_t logicPowerLevel = 0;
// period = (motorPowerLevel+175)*2 (in microseconds)
// battery voltage = 10*R*C/period (in volts with period in seconds)
uint8_t motorPowerLevel = 0;

uint16_t motorPowerLevelPeriod = 0;

static void updateMotorPowerLEDs() {
    if(motorPowerLevel < MOTOR_LOW_BAT)
        MOTORG_SetHigh();
    else
        MOTORG_SetLow();
    if(motorPowerLevel > MOTOR_MIDDLE_BAT)
        MOTORR_SetHigh();
    else
        MOTORR_SetLow();
}
static void updateLogicPowerLEDs() {
    if(logicPowerLevel > LOGIC_LOW_BAT)
        LOGICG_SetHigh();
    else
        LOGICG_SetLow();
    if(logicPowerLevel < LOGIC_MIDDLE_BAT)
        LOGICR_SetHigh();
    else
        LOGICR_SetLow();
}

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
                updateLogicPowerLEDs();
            }
            counter++;
        }
    }
    if(motorPowerLevelPeriod) {
        uint16_t period = motorPowerLevelPeriod;
        motorPowerLevelPeriod = 0; // we won't process this again until it is updated
        
        if(period < MOTOR_LOW_THRESHOLD)
            motorPowerLevel = 0;
        else {
            period -= MOTOR_LOW_THRESHOLD;
            if(period > 255)
                motorPowerLevel = 255;
            else
                motorPowerLevel = period;
        }
        updateMotorPowerLEDs();
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

int8_t getMotorPowerLevel() {
    return motorPowerLevel;
}

int8_t getLogicPowerLevel() {
    return logicPowerLevel;
}