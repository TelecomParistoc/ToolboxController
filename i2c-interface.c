#include "i2c-interface.h"
#include "e-i2c.h"

void clearCoderCounters();
int8_t getStatus();

// initialize e-i2c and configure the handlers here
void configureI2Cinterface() {
    ei2cInit(); // initialize e-I2C library
    
    // simple write commands
    
    //8 bit write commands
    
    //8 bit read commands
    
    // 16 bit write commands
    
    //16 bit read commands

}
