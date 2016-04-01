#include "ax12.h"
#include "mcc_generated_files/eusart1.h"
#include <stdint.h>
#include <stdio.h>
#include <xc.h>
#include "interrupts.h"

#define axid  129
#define axid2 130

/*Ax 12 qui contrôle l'aimant*/

#define vertical 532
#define lacher 300

/*Ax 12 qui positionne le système de pêche*/

#define rentre 770
#define horiz 480

/*Ax 12 pince sens horaire*/
#define hrentre 757
#define hsorti  338

/*Ax 12 pince sens trigo*/
#define trentre 330
#define tsorti  670

volatile uint8_t activeID;
volatile AX12state state;
volatile consign_buffer consigns;
volatile int16_t position;
volatile int16_t parameter;
volatile uint8_t forcing;

static uint16_t count;
//static uint16_t max;

static int spam;

// Initializes all Ax-12
static void initAll();

// Writes len first values in array vals in registers beginning at reg of Ax-12(id)
static void axWrite(uint8_t reg, uint8_t * vals, uint8_t len);

// Asks to read len registers starting with register reg fom Ax-12(id)
static void axRead(uint8_t reg, uint8_t len);

// Reads the answer of the last axRead call
static void readBuffer();

// sets parameter as goal position for Ax-12(id)
static void setPosition();

// sets parameter as goal speed for Ax-12(id)
static void setSpeed();

// sets parameter as max torque for Ax-12(id)
static void setMaxTorque();

// puts Ax-12(id) in wheel mode
static void setWheelMode();

// puts Ax-12(id) in the default mode
static void setDefaultMode();

// asks the position of an Ax-12
static void getPosition();

// checks if Ax-12 is moving
static void isMoving();

static int debug;

/* called once on startup */
void ax12Setup() {
    printf("Hello World !\n");
    consigns.begin = 0;
    consigns.end = 0;
    spam = 0;
    initAll();
}

/* called in the main loop : performs all the needed updates */
void ax12Manager() {
    if (answer_status == 1) {
        count ++;
        if(count == 1500){
            count = 0;
            answer_status = 0;
            printf("Ax-12 %d timeout\n", activeID);
            clearBuffer();
        }
        return;
    }
    if (answer_status == 2) {
        //if(count > max){
        //    max = count;
        //    printf("Count : %d\n", count);
        //}
        readBuffer();
        return;
    }
    if (consigns.begin != consigns.end) {
        int current = (consigns.begin + 1) % 10;
        switch (consigns.orders[current].order) {
            case SET_MODE:
                position = -1;
                if(consigns.orders[current].param < 1000){
                    activeID = consigns.orders[current].param;
                    state = DEFAULT_MODE;
                    setDefaultMode();
                    getPosition();
                } else {
                    activeID = consigns.orders[current].param - 1000;
                    state = WHEEL_MODE;
                    setWheelMode();
                }
                printf("Mode set for %d\n", activeID);
                break;
            case SET_SPEED:
                parameter = consigns.orders[current].param;
                setSpeed();
                printf("Set speed %d\n", parameter);
                break;
            case SET_POSITION:
                parameter = consigns.orders[current].param;
                setPosition();
                printf("Set position %d\n", parameter);
                break;
            case SET_TORQUE:
                parameter = consigns.orders[current].param;
                setMaxTorque();
                printf("Set torque %d\n", parameter);
                break;
            case RESET:
                initAll();
                printf("Reset ax-12\n");
                break;
        }
        if (spam){
            consigns.begin = current;
            spam = 0;
        }
        else{
            spam = 1;
        }
        return;
    }
    switch (state) {
        case DEFAULT_MODE:
            getPosition();
            break;
        case MOVING_ASK_POS:
            getPosition();
            break;
        case MOVING_ASK_FINISHED:
            isMoving();
            break;
        case WHEEL_MODE:
            break;
    }
}

/*
 * Allows you to send data to an AX12
 * 
 * A message has the following format : 
 * 	0xFF 0xFF ID LENGTH INSTRUCTION PARAM_1 ... PARAM_N CHECK_SUM
 * Explanation of the message format :
 * 		-0xFF 0xFF : indicates the start of an incoming packet.
 * 		-ID : the ID of the AX12 you want to send the message
 *				if the value 0xFE is used, the message is broadcasted
 *				to all the devices in the network	
 *		-LENGTH : length of the packet = N + 2 with N being
 *						the number of parameters
 *		-INSTRUCTION : what should the device do
 *		-PARAM(s) : guess by yourself
 *		-CHECK_SUM : = ~(ID + LENGTH + INSTRUCTION + PARAM_1
 *					+ ... + PARAM_N) % 256
 *					~ : NOT logical operation
 *
 * For a list of the possible OPERATIONS and the related PARAM, see the
 * AX12 datasheet (available on the Google Drive of Telecom Robotics)
 */

void axWrite(uint8_t reg, uint8_t * vals, uint8_t len) {
    uint8_t buff[20];
    buff[0] = 0xFF;
    buff[1] = 0xFF;
    buff[2] = activeID;
    buff[3] = len + 3;
    buff[4] = 0x03;
    buff[5] = reg;
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < len; i++) {
        buff[6 + i] = vals[i];
        checksum += vals[i];
    }
    checksum += len + 6 + activeID + reg;
    buff[6 + len] = 255 - checksum;
    serial1Write(buff, 7 + len);
}

void axRead(uint8_t reg, uint8_t len) {
    uint8_t buff[8];
    buff[0] = 0xFF;
    buff[1] = 0xFF;
    buff[2] = activeID;
    buff[3] = 0x04;
    buff[4] = 0x02;
    buff[5] = reg;
    buff[6] = len;
    uint8_t checksum = 6 + activeID + reg + len;
    buff[7] = 255 - checksum;
    serial1Write(buff, 8);
}

void readBuffer() {
    for (uint8_t i = 0; i < 4; i++)
        EUSART1_Read();
    if (EUSART1_Read() & 32 == 32)
        if (! forcing){
            raiseInterrupt(AX12_FORCING);
            forcing = 1;
        }
    if (expected_answer_length == 8) {
        position = EUSART1_Read();
        position += (EUSART1_Read() << 8);
        if (state != DEFAULT_MODE)
            state = MOVING_ASK_FINISHED;
    } else {
        int foo = EUSART1_Read();
        if (foo == 0) {
            raiseInterrupt(AX12_FINISHED_MOVE);
            state = DEFAULT_MODE;
            answer_status = 0;
            EUSART1_Read();
            return;
        }
        state = MOVING_ASK_POS;
    }
    EUSART1_Read();
    answer_status = 0;
}

void initAll() {
    activeID = 254;
    state = WHEEL_MODE;
    position = -1;
    forcing = 0;
    answer_status = 0;
    count = 0;
    uint8_t buff[2];
    buff[0] = 1;
    axWrite(24, buff, 1); // Disable torque
    buff[0] = 255;
    buff[1] = 3;
    axWrite(34, buff, 2); // Sets Max Torque to maximum value
    buff[0] = 2;
    axWrite(18, buff, 1); // Shutdown ssi surchauffe
    buff[0] = 1;
    axWrite(16, buff, 1); // Status return only if READ
    axWrite(24, buff, 1); // Enable torque
}

void setPosition() {
    forcing = 0;
    state = MOVING_ASK_FINISHED;
    uint8_t buff[2];
    buff[0] = (uint8_t) parameter;
    buff[1] = parameter >> 8;
    axWrite(30, buff, 2);
}

void setSpeed() {
    uint8_t buff[2];
    buff[0] = (uint8_t) parameter;
    buff[1] = parameter >> 8;
    axWrite(32, buff, 2);
}

void setMaxTorque() {
    uint8_t buff[2];
    buff[0] = (uint8_t) parameter;
    buff[1] = parameter >> 8;
    axWrite(34, buff, 2);
}

void setWheelMode() {
    state = WHEEL_MODE;
    uint8_t buff[4];
    for (int i = 0; i < 4; i++)
        buff[i] = 0;
    axWrite(6, buff, 4);
}

void setDefaultMode() {
    state = DEFAULT_MODE;
    uint8_t buff[4];
    buff[0] = 0;
    buff[1] = 0;
    buff[2] = 255;
    buff[3] = 3;
    axWrite(6, buff, 4);
}

void getPosition() {
    expected_answer_length = 8;
    count = 0;
    answer_status = 1;
    axRead(36, 2);
}

void isMoving() {
    expected_answer_length = 7;
    count = 0;
    answer_status = 1;
    axRead(46, 1);
}
