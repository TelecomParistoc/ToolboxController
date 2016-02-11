#include "ax12-i2c.h"
#include "ax12.h"

static void setCommand(AX12order consign, int16_t param);

void masterSetActiveIdWheel(uint8_t id) {
    activeID = id;
    position = -1;
    order = NONE;
    state = WHEEL_MODE;
}

void masterSetActiveIdDefault(uint8_t id) {
    activeID = id;
    position = -1;
    order = NONE;
    state = DEFAULT_MODE;
}

void masterSetSpeedWheel(int16_t param) {
    setCommand(SET_SPEED_WHEEL, param);
}

void masterSetSpeedDefault(int16_t param) {
    setCommand(SET_SPEED_DEFAULT, param);
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
