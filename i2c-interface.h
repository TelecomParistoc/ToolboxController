

#ifndef I2C_INTERFACE_H
#define	I2C_INTERFACE_H

/******************      SIMPLE COMMANDS      ******************/
//(no arguments) : have to be mapped between 0x00 and 0x3F
#define NUM_W0_CMD 1 // total number of commands, at least 1
// the higher command should be lower than 0x00 + NUM_W0_CMD


/***************     8-bit GET/SET COMMANDS     ***************/
// (int8 arguments) : have to be mapped between 0x40 and 0x7F
#define NUM_W8_CMD 1 // total number of SET commands, at least 1
#define NUM_R8_CMD 1 // total number of GET commands, at least 1
// the higher command should be lower than 0x40 + NUM_x8_CMD


/***************     16-bit GET/SET COMMANDS     ***************/
// (int16 arguments) : have to be mapped between 0x80 and 0xFF
#define NUM_W16_CMD 1 // total number of SET commands, at least 1
#define NUM_R16_CMD 1 // total number of GET commands, at least 1
// the higher command should be lower than 0x80 + NUM_W16_CMD


// initialize e-i2c and configure the handlers here
void configureI2Cinterface();

#endif	/* I2C_INTERFACE_H */

