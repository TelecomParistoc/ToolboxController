#ifndef AX12_H
#define AX12_H

#include <stdint.h>

typedef enum {
    WHEEL_MODE,
    DEFAULT_MODE,
    MOVING_ASK_POS,
    MOVING_ASK_FINISHED,
} AX12state;

typedef enum {
    NONE,
    SET_MODE,
    SET_SPEED,
    SET_POSITION,
    SET_TORQUE,
    RESET
} AX12order;

typedef struct {
    AX12order order;
    int16_t   param;
} consign;

typedef struct {
    consign orders[20];
    int begin;
    int end;
} consign_buffer;

/* called once on startup */
void ax12Setup();

/* called in the main loop : performs all the needed updates */
void ax12Manager();

extern volatile consign_buffer consigns;
extern volatile int16_t position;
extern volatile uint8_t forcing;
extern volatile uint8_t update_flag;

#endif