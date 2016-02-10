#ifndef AX12_H
#define AX12_H

#include <stdint.h>

typedef enum {
    WHEEL_MODE,
    DEFAULT_MODE,
    MOVING
} AX12state;
/* called once on startup */
void ax12Setup();

/* called in the main loop : performs all the needed updates */
void ax12Manager();

extern volatile uint8_t activeID;
extern volatile AX12state state;
extern volatile uint8_t command;

#endif