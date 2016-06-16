

#ifndef I2C_INTERFACE_H
#define	I2C_INTERFACE_H

/******************      SIMPLE COMMANDS      ******************/
//(no arguments) : have to be mapped between 0x00 and 0x3F
#define NUM_W0_CMD 1 // total number of commands, at least 1
// the higher command should be lower than 0x00 + NUM_W0_CMD

/***************     8-bit GET/SET COMMANDS     ***************/
// (int8 arguments) : have to be mapped between 0x40 and 0x7F
#define NUM_W8_CMD 10 // total number of SET commands, at least 1
#define NUM_R8_CMD 6 // total number of GET commands, at least 1
// the higher command should be lower than 0x40 + NUM_x8_CMD

// write only
#define PWM1 0x41
#define PWM2 0x42
#define PWM3 0x43
#define PWM4 0x44
#define LEDS 0x45
#define LEDSSO 0x46
#define LEDSCO 0x47
#define COLLMASK 0x48
#define SENMASK 0x49

// read only
#define INTERRUPT_STATUS 0x40
#define MOTOR_POWER_LEVEL 0x41
#define LOGIC_POWER_LEVEL 0x42
#define BUTTONS 0x43
#define SENSORS 0x44
#define COLLISIONS 0x45

/***************     16-bit GET/SET COMMANDS     ***************/
// (int16 arguments) : have to be mapped between 0x80 and 0xFF
#define NUM_W16_CMD 1 // total number of SET commands, at least 1
#define NUM_R16_CMD 1 // total number of GET commands, at least 1
// the higher command should be lower than 0x80 + NUM_W16_CMD

// initialize e-i2c and configure the handlers here
void configureI2Cinterface();

#endif	/* I2C_INTERFACE_H */

