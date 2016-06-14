#include "ax12.h"
#include "mcc_generated_files/eusart1.h"
#include <stdint.h>
#include <stdio.h>
#include <xc.h>
#include "interrupts.h"
#include "fifo.h"

typedef enum {
    NO_ANSWER,
    CHECK_ANSWER,
    STORE_ANSWER
} answer_type;

static uint8_t sendBuffer[100];
static struct fifo sendFifo;

static uint8_t idBuffer[10];
static uint16_t argBuffer[10];
struct fifo receiveFifo;

uint16_t axArg = 0;

void setArg8(uint8_t arg) {
    axArg = arg;
}
void setArg16(uint16_t arg) {
    axArg = arg;
}
uint8_t getAnswer8() {
    return argBuffer[receiveFifo.tail];
}
uint16_t getAnswer16() {
    return argBuffer[receiveFifo.tail];
}
uint8_t getAnswerID() {
    return readFifo(&receiveFifo);
}

//add a packet to the fifo
static void queuePacket(uint8_t id, uint8_t type, uint8_t cmd, uint8_t paramLength, uint16_t param) {
    uint8_t length = type == 0x01 ? 2 : 3 + paramLength;
    writeFifo(&sendFifo, id);
    writeFifo(&sendFifo, length);
    writeFifo(&sendFifo, type);
    if(paramLength>0) {
        writeFifo(&sendFifo, cmd);
        writeFifo(&sendFifo, param & 0xFF);
    }
    if(paramLength==2)
        writeFifo(&sendFifo, param >> 8);
}
// add a read8 packet to the fifo
void axRead8(uint16_t arg) {
    queuePacket(arg >> 8, 0x02, arg&0xFF, 1, 1);
}
// add a read16 packet to the fifo
void axRead16(uint16_t arg) {
    queuePacket(arg >> 8, 0x02, arg&0xFF, 1, 2);
}
// add a write8 packet to the fifo
void axWrite8(uint16_t arg) {
    queuePacket(arg >> 8, 0x03, arg&0xFF, 1, axArg);
}
// add a write16 packet to the fifo
void axWrite16(uint16_t arg) {
    queuePacket(arg >> 8, 0x03, arg&0xFF, 2, axArg);
}
// add a status packet to the fifo
void axStatus(uint8_t arg) {
    queuePacket(arg, 0x01, 0, 0, 0);
}
void axSetPosition(uint8_t id) {
    queuePacket(id, 0x03, 0x08, 2, 0x03FF); // default mode
    queuePacket(id, 0x03, 0x1E, 2, axArg); // set goal position
}
void axSetSpeedWheel(uint8_t id) {
    queuePacket(id, 0x03, 0x08, 2, 0); // wheel mode
    queuePacket(id, 0x03, 0x20, 2, axArg); // set goal speed
}
// send the next packet in the fifo
static answer_type axSendPacket() {
    uint8_t checksum, id, instruction, length, i, tmp;
    id = readFifo(&sendFifo);
    instruction = readFifo(&sendFifo);
    length = readFifo(&sendFifo);
    checksum = id+instruction+length;
    EUSART1_Write(0xFF);
    EUSART1_Write(0xFF);
    EUSART1_Write(id);
    EUSART1_Write(length);
    EUSART1_Write(instruction);
    // send parameters
    for(i=2; i<length; i++) {
        tmp = readFifo(&sendFifo);
        checksum += tmp;
        EUSART1_Write(tmp);
    }
    EUSART1_Write(~checksum); // checksum
    if(id==0xFE)
        return NO_ANSWER;
    if(instruction==0x03)
        return CHECK_ANSWER;
    return STORE_ANSWER;
}

/* called once on startup */
void ax12Setup() {
    // TODO : init fifo
    
}

/* called in the main loop : performs all the needed updates */
void ax12Manager() {
    static answer_type expectingAnswer = NO_ANSWER;
    // when we're not waiting for an answer and there's some packet to send
    if(expectingAnswer == NO_ANSWER && sendFifo.fill != 0){
        expectingAnswer = axSendPacket();
    } else {
        // TODO: handle answers and errors
    }
}