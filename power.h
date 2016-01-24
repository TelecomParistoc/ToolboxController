
#ifndef POWER_H
#define	POWER_H

#include <stdint.h>

inline void powerManager();
void setCCP5period(uint16_t period);

// I2C getters
int8_t getMotorPowerLevel();
int8_t getLogicPowerLevel();

#endif	/* POWER_H */

