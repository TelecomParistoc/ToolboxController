#ifndef AX12_H
#define AX12_H

#include <stdint.h>

typedef enum {
    WHEEL_MODE,
    DEFAULT_MODE,
    MOVING_POS,
    MOVING_POLL
} AX12state;

typedef enum {
    NONE,
    SET_SPEED_WHEEL,
    SET_SPEED_DEFAULT,
    SET_POSITION,
    SET_TORQUE
} AX12order;

/* called once on startup */
void ax12Setup();

/* called in the main loop : performs all the needed updates */
void ax12Manager();

extern volatile uint8_t activeID;
extern volatile AX12state state;
extern volatile AX12order order;
extern volatile int16_t position;
extern volatile int16_t parameter;

#endif