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
volatile uint8_t update_flag;

static uint16_t count;
static int spam;

/* filter position values with a 3 values median filter 
 * after each sample, call this function with the raw position. Returns 
 * the filtered value. Works only if called once and only once per sample*/
static int16_t positionMedianFilter(int16_t newValue) {
    static int16_t last, beforeLast;
    int16_t median;
    if(last >= newValue) {
        if(beforeLast >= newValue)
            median = last >= beforeLast ? beforeLast : last;
        else
            median = newValue;
    } else {
        if(beforeLast >= newValue)
            median = newValue;
        else
            median = last < beforeLast ? beforeLast : last;
    }
    beforeLast = last;
    last = newValue;
    return median;
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

// Writes len first values in array vals in registers beginning at reg of Ax-12(id)
static void axWrite(uint8_t reg, uint8_t * vals, uint8_t len) {
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

// Asks to read len registers starting with register reg fom Ax-12(id)
static void axRead(uint8_t reg, uint8_t len) {
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

// Reads the answer of the last axRead call
static void readBuffer() {
    uint8_t checksum = 0;
    uint8_t tmp;
    int16_t pos;
    for (uint8_t i = 0; i < 2; i++)
        EUSART1_Read();
    for (uint8_t i = 0; i < 2; i++)
        checksum += EUSART1_Read();
    tmp = EUSART1_Read();
    checksum += tmp;
    if (tmp & 32 == 32)
        if (! forcing){
            raiseInterrupt(AX12_FORCING);
            forcing = 1;
        }
    if (expected_answer_length == 8) {
        tmp = EUSART1_Read();
        checksum += tmp;
        pos = tmp;
        tmp = EUSART1_Read();
        checksum += tmp;
        pos += (tmp << 8);
        tmp = tmp = EUSART1_Read();
        if(tmp == 255 - checksum)
            position = positionMedianFilter(pos);
        else
            printf("Corrupted answer 1, expected %d but got %d\n", tmp, 255 - checksum);
        if (state != DEFAULT_MODE)
            state = MOVING_ASK_FINISHED;
        answer_status = 0;
    } else {
        tmp = EUSART1_Read();
        checksum += tmp;
        if(EUSART1_Read() == 255 - checksum){
            if (tmp == 0) {
                raiseInterrupt(AX12_FINISHED_MOVE);
                answer_status = 0;
                state = DEFAULT_MODE;
                return;
            }
        }
        else {
            printf("Corrupted answer 2\n");
        }
        answer_status = 0;
        state = MOVING_ASK_POS;
        return;
    }
}

// Initializes all Ax-12
static void initAll() {
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

// sets parameter as goal position for Ax-12(id)
static void setPosition() {
    forcing = 0;
    state = MOVING_ASK_FINISHED;
    uint8_t buff[2];
    buff[0] = (uint8_t) parameter;
    buff[1] = parameter >> 8;
    axWrite(30, buff, 2);
}

// sets parameter as goal speed for Ax-12(id)
static void setSpeed() {
    uint8_t buff[2];
    buff[0] = (uint8_t) parameter;
    buff[1] = parameter >> 8;
    axWrite(32, buff, 2);
}

// sets parameter as max torque for Ax-12(id)
static void setMaxTorque() {
    uint8_t buff[2];
    buff[0] = (uint8_t) parameter;
    buff[1] = parameter >> 8;
    axWrite(34, buff, 2);
}

// puts Ax-12(id) in wheel mode
static void setWheelMode() {
    state = WHEEL_MODE;
    uint8_t buff[4];
    for (int i = 0; i < 4; i++)
        buff[i] = 0;
    axWrite(6, buff, 4);
}

// puts Ax-12(id) in the default mode
static void setDefaultMode() {
    state = DEFAULT_MODE;
    uint8_t buff[4];
    buff[0] = 0;
    buff[1] = 0;
    buff[2] = 255;
    buff[3] = 3;
    axWrite(6, buff, 4);
}

// asks the position of an Ax-12
static void getPosition() {
    expected_answer_length = 8;
    count = 0;
    answer_status = 1;
    axRead(36, 2);
}

// checks if Ax-12 is moving
static void isMoving() {
    expected_answer_length = 7;
    count = 0;
    answer_status = 1;
    axRead(46, 1);
}

/* called once on startup */
static void ax12Setup() {
    printf("Hello World !\n");
    consigns.begin = 0;
    consigns.end = 0;
    spam = 0;
    initAll();
}

/* called in the main loop : performs all the needed updates */
static void ax12Manager() {
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
        readBuffer();
        return;
    }
    if (consigns.begin != consigns.end) {
        int current = (consigns.begin + 1) % 20;
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
    if(update_flag) {
        update_flag = 0;
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
}