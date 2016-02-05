#include "power.h"
#include "mcc_generated_files/adc.h"
#include "mcc_generated_files/pin_manager.h"
#include <xc.h>
#include <stdio.h>

// if the battery voltage is under this threshold (about 6V), the battery is likely 
// to be either disconnect or kaput (Ja, Ja, Ja). Power level will be 0
#define LOGIC_LOW_THRESHOLD 448
#define MOTOR_LOW_THRESHOLD 300

#define LOGIC_LOW_BAT 153
#define LOGIC_MIDDLE_BAT 185

#define MOTOR_LOW_BAT 88
#define MOTOR_MIDDLE_BAT 53

// battery voltage = (logicPowerLevel*2 + 448)*0.0139 (in volts)
uint8_t logicPowerLevel = 0;
// period = (motorPowerLevel+300)*2 (in microseconds)
// battery voltage = 10*R*C/period (in volts with period in seconds)
uint8_t motorPowerLevel = 0;

uint16_t motorPowerLevelPeriod = 0;

static void updateMotorPowerLEDs() {
    if(motorPowerLevel < MOTOR_LOW_BAT)
        MOTORG_SetLow();
    else
        MOTORG_SetHigh();
    if(motorPowerLevel > MOTOR_MIDDLE_BAT)
        MOTORR_SetLow();
    else
        MOTORR_SetHigh();
}
static void updateLogicPowerLEDs() {
    if(logicPowerLevel > LOGIC_LOW_BAT)
        LOGICG_SetLow();
    else
        LOGICG_SetHigh();
    if(logicPowerLevel < LOGIC_MIDDLE_BAT)
        LOGICR_SetLow();
    else
        LOGICR_SetHigh();
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
        // turn of the LED
        MOTORR_SetHigh();
        MOTORG_SetHigh();
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