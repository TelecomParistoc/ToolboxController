#include "misc.h"
#include "interrupts.h"
#include "mcc_generated_files/epwm1.h"
#include "mcc_generated_files/epwm2.h"
#include "mcc_generated_files/epwm3.h"
#include "mcc_generated_files/pwm4.h"
#include "mcc_generated_files/pin_manager.h"
#include <xc.h>

static uint8_t sensorsMask = 0xFF;
static uint8_t collisionsMask = 0xFF;
static int8_t lastSensors = 0;
static int8_t lastCollisions = 0;

// we can't use getCollisions since it's used in interrupts
static inline int8_t getColls() {
    int8_t result = 0;
    if(DETEC1_GetValue())
        result = 0x01;
    if(DETEC2_GetValue())
        result += 0x02;
    if(DETEC3_GetValue())
        result += 0x04;
    if(DETEC4_GetValue())
        result += 0x08;
    if(DETEC5_GetValue())
        result += 0x10;
    result = result & collisionsMask;
    return result;
}
// we can't use getSensors since it's used in interrupts
static inline int8_t getSens() {
    int8_t result = 0;
    if(SEN1_GetValue())
        result = 0x01;
    if(SEN2_GetValue())
        result += 0x02;
    if(SEN3_GetValue())
        result += 0x04;
    if(SEN4_GetValue())
        result += 0x08;
    if(SEN5_GetValue())
        result += 0x10;
    return result & sensorsMask;
}

inline void sensorManager() {
    // when a sensor changes
    if(getSens() != lastSensors) {
        raiseInterrupt(SENSOR_CHANGE);
        lastSensors = getSens();
    }
}
inline void collisionManager() {
    // when a collision detector changes
    if(getColls() != lastCollisions) {
        raiseInterrupt(COLLISION_CHANGE);
        lastCollisions = getColls();
    }
}

int8_t getButtons() {
    int8_t result = 0;
    if(BT1_GetValue())
        result = 0x01;
    if(BT2_GetValue())
        result += 0x02;
    if(BT3_GetValue())
        result += 0x04;
    return result;
}
int8_t getSensors() {
    int8_t result = 0;
    if(SEN1_GetValue())
        result = 0x01;
    if(SEN2_GetValue())
        result += 0x02;
    if(SEN3_GetValue())
        result += 0x04;
    if(SEN4_GetValue())
        result += 0x08;
    if(SEN5_GetValue())
        result += 0x10;
    return result;
}
int8_t getCollisions() {
    int8_t result = 0;
    if(DETEC1_GetValue())
        result = 0x01;
    if(DETEC2_GetValue())
        result += 0x02;
    if(DETEC3_GetValue())
        result += 0x04;
    if(DETEC4_GetValue())
        result += 0x08;
    if(DETEC5_GetValue())
        result += 0x10;
    return result;
}

void setSensorsMask(int8_t mask) {
    sensorsMask = mask;
    lastSensors = lastSensors & mask;
}
void setCollisionsMask(int8_t mask) {
    collisionsMask = mask;
    lastCollisions = lastCollisions & mask;
}

void setLEDs(int8_t leds) {
    if(leds&0x01)
        LED1_SetHigh();
    else
        LED1_SetLow();
    if(leds&0x02)
        LED2_SetHigh();
    else
        LED2_SetLow();
    if(leds&0x04)
        LED3_SetHigh();
    else
        LED3_SetLow();
    if(leds&0x08)
        LED4_SetHigh();
    else
        LED4_SetLow();
}
void setOnlyLEDs(int8_t leds) {
    if(leds&0x01)
        LED1_SetHigh();
    if(leds&0x02)
        LED2_SetHigh();
    if(leds&0x04)
        LED3_SetHigh();
    if(leds&0x08)
        LED4_SetHigh();
}
void clearOnlyLEDs(int8_t leds) {
    if(leds&0x01)
        LED1_SetLow();
    if(leds&0x02)
        LED2_SetLow();
    if(leds&0x04)
        LED3_SetLow();
    if(leds&0x08)
        LED4_SetLow();
}
void setPWM1(uint8_t value) {
    uint16_t dc = value << 1;
    EPWM3_LoadDutyValue(dc);
}
void setPWM2(uint8_t value) {
    uint16_t dc = value << 1;
    EPWM2_LoadDutyValue(dc);
}
void setPWM3(uint8_t value) {
    uint16_t dc = value << 1;
    EPWM1_LoadDutyValue(dc);
}
void setPWM4(uint8_t value) {
    uint16_t dc = value << 1;
    PWM4_LoadDutyValue(dc);
}
