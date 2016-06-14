#include "i2c-interface.h"
#include "e-i2c.h"
#include "interrupts.h"
#include "power.h"
#include "misc.h"
#include "ax12.h"

// initialize e-i2c and configure the handlers here

void configureI2Cinterface() {
    ei2cInit(); // initialize e-I2C library

    // simple write commands

    //8 bit write commands
    map8write(PWM1, setPWM1);
    map8write(PWM2, setPWM2);
    map8write(PWM3, setPWM3);
    map8write(PWM4, setPWM4);
    map8write(LEDS, setLEDs);
    map8write(LEDSSO, setOnlyLEDs);
    map8write(LEDSCO, clearOnlyLEDs);
    map8write(COLLMASK, setCollisionsMask);
    map8write(SENMASK, setSensorsMask);
    map8write(AXARG8, setArg8);
    map8write(AXPOS, axSetPosition);
    map8write(AXWHEEL, axSetSpeedWheel);
    map8write(AXSTATUS, axStatus);
    
    //8 bit read commands
    map8read(INTERRUPT_STATUS, readStatus);
    map8read(MOTOR_POWER_LEVEL, getMotorPowerLevel);
    map8read(LOGIC_POWER_LEVEL, getLogicPowerLevel);
    map8read(BUTTONS, getButtons);
    map8read(SENSORS, getSensors);
    map8read(COLLISIONS, getCollisions);
    map8read(AXARG8, getAnswer8);
    map8read(AXANSID, getAnswerID);
    
    // 16 bit write commands
    map16write(AXREAD8, axRead8);
    map16write(AXREAD16, axRead16);
    map16write(AXWRITE8, axWrite8);
    map16write(AXWRITE16, axWrite16);
    map16write(AXARG16, setArg16);

    //16 bit read commands
    map16read(AXARG16, getAnswer16);
}
