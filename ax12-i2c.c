#include "ax12-i2c.h"
#include "ax12.h"
#include <stdio.h>

extern volatile consign_buffer consigns;

static void setCommand(AX12order axorder, int16_t param) {
    int next = (consigns.end + 1) % 20;
    consigns.orders[next].order = axorder;
    consigns.orders[next].param = param;
    consigns.end = next;
}

void masterSetActiveIdWheel(int16_t id) {
    setCommand(SET_MODE, id + 1000);
}

void masterSetActiveIdDefault(int16_t id) {
    setCommand(SET_MODE, id);
}

void masterSetSpeed(int16_t param) {
    setCommand(SET_SPEED, param);
}

void masterSetPosition(int16_t param) {
    setCommand(SET_POSITION, param);
}

void masterSetTorque(int16_t param) {
    setCommand(SET_TORQUE, param);
}

void masterReset() {
    setCommand(RESET, 0);
}

int16_t masterGetPosition() {
    return position;
}