#ifndef AX12_I2C_H
#define	AX12_I2C_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void masterSetActiveIdWheel(int16_t id);

    void masterSetActiveIdDefault(int16_t id);

    void masterSetSpeed(int16_t param);

    void masterSetPosition(int16_t param);

    void masterSetTorque(int16_t param);
    
    void masterReset();
    
    int16_t masterGetPosition();

#ifdef	__cplusplus
}
#endif

#endif	/* AX12_I2C_H */

