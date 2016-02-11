#ifndef AX12_I2C_H
#define	AX12_I2C_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void masterSetActiveIdWheel(uint8_t id);

    void masterSetActiveIdDefault(uint8_t id);

    void masterSetSpeedWheel(int16_t param);

    void masterSetSpeedDefault(int16_t param);

    void masterSetPosition(int16_t param);

    void masterSetTorque(int16_t param);
    
    int16_t masterGetPosition();

#ifdef	__cplusplus
}
#endif

#endif	/* AX12_I2C_H */

