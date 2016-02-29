#include "ax12-i2c.h"
#include "ax12.h"
#include <stdio.h>

static void setCommand(AX12order consign, int16_t param);

void masterSetActiveIdWheel(uint8_t id) {
    activeID = id;
    position = -1;
    forcing = 0;
    state = WHEEL_MODE;
    setCommand(SET_MODE, 0);
}

void masterSetActiveIdDefault(uint8_t id) {
    activeID = id;
    position = -1;
    forcing = 0;
    state = DEFAULT_MODE;
    setCommand(SET_MODE, 0);
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

int16_t masterGetPosition() {
    return position;
}

static void setCommand(AX12order consign, int16_t param) {
    order = consign;
    parameter = param;
}
