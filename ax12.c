#include "ax12.h"
#include "mcc_generated_files/eusart1.h"
#include <stdint.h>
#include <stdio.h>
#include <xc.h>

#define axid 121
#define axid2 148

/*Ax 12 qui contrôle l'aimant*/

#define vertical 532
#define lacher 300

/*Ax 12 qui positionne le système de pêche*/

#define rentre 770
#define horiz 480

static uint16_t interrupt_answer;

// Initializes all Ax-12
static void initAll();

// Writes len first values in array vals in registers beginning at reg of Ax-12(id)
static void axWrite(uint8_t id, uint8_t reg, uint8_t * vals, uint8_t len);

// Asks to read len registers starting with register reg fom Ax-12(id)
static void axRead(uint8_t id, uint8_t reg, uint8_t len);

// Reads the answer of the last axRead call
static void readBuffer();

// sets p as goal position for Ax-12(id)
static void setPosition(uint8_t id, uint16_t cons);

// sets p as goal speed for Ax-12(id)
static void setSpeed(uint8_t id, uint16_t cons);

// puts Ax-12(id) in wheel mode
static void setWheelMode(uint8_t id);

// puts Ax-12(id) in the default mode
static void setDefaultMode(uint8_t id);

// asks the position of an Ax-12
static void getPosition(uint8_t id);

// checks if Ax-12 is moving
static void isMoving(uint8_t id);

/* called once on startup */
void ax12Setup() {
    printf("Hello World !\n");
    initAll();
    setDefaultMode(axid);
    setDefaultMode(axid2);
    setSpeed(axid, 50);
    setSpeed(axid2, 50);
    getPosition(axid);
    //getPosition(axid2);
    //setPosition(axid, rentre);
    /*setPosition(axid, horiz);
    while(isMoving(axid));
    printf("Descendu1\n");
    setPosition(axid, rentre);
    while(isMoving(axid));
    printf("Monte1\n");
    setPosition(axid, horiz);
    while(isMoving(axid));
    printf("Descendu2\n");
    setPosition(axid, rentre);
    while(isMoving(axid));
    printf("Monte2\n");
    setPosition(axid, horiz);
    while(isMoving(axid));
    printf("Descendu3\n");
    setPosition(axid2, lacher);*/
}

/* called in the main loop : performs all the needed updates */
void ax12Manager() {
    if(answer_status == 1)
        readBuffer();
}

void axWrite(uint8_t id, uint8_t reg, uint8_t * vals, uint8_t len) {
  uint8_t buff[20];
  buff[0] = 0xFF;
  buff[1] = 0xFF;
  buff[2] = id;
  buff[3] = len + 3;
  buff[4] = 0x03;
  buff[5] = reg;
  uint8_t checksum = 0;
  for(uint8_t i = 0 ; i < len ; i ++){
      buff[6 + i] = vals[i];
      checksum += vals[i];
  }
  checksum += len + 6 + id + reg;
  buff[6 + len] = 255 - checksum;
  serial1Write(buff, 7 + len);
}

void axRead(uint8_t id, uint8_t reg, uint8_t len) {
  uint8_t buff[8];
  buff[0] = 0xFF;
  buff[1] = 0xFF;
  buff[2] = id;
  buff[3] = 0x04;
  buff[4] = 0x02;
  buff[5] = reg;
  buff[6] = len;
  uint8_t checksum = 6 + id + reg + len;
  buff[7] = 255 - checksum;
  serial1Write(buff, 8);
}

void readBuffer() {
  for(uint8_t i = 0 ; i < 5 ; i ++)
      EUSART1_Read();
  interrupt_answer = EUSART1_Read();
  if (expected_answer_length == 8)
      interrupt_answer += (EUSART1_Read() << 8); 
  EUSART1_Read();
  //TODO interrupter le Raspberry Pi
  printf("On lit %d\n", interrupt_answer);
  answer_status = 0;
}

void initAll() {
  uint8_t buff[2];
  buff[0] = 255;
  buff[1] = 3;
  axWrite(254, 34, buff, 2);
  buff[0] = 1;
  axWrite(254, 24, buff, 1); // Enable torque
  axWrite(254, 16, buff, 1); // Status return only if READ
  buff[0] = 2;
  axWrite(254, 18, buff, 1); // Shutdown ssi surchauffe
}

void setPosition(uint8_t id, uint16_t cons) {
  uint8_t buff[2];
  buff[0] = (uint8_t) cons;
  buff[1] = cons >> 8;
  axWrite(id, 30, buff, 2);
}

void setSpeed(uint8_t id, uint16_t cons) {
  uint8_t buff[2];
  buff[0] = (uint8_t) cons;
  buff[1] = cons >> 8;
  axWrite(id, 32, buff, 2);
}

void setWheelMode(uint8_t id) {
  uint8_t buff[4];
  for(int i = 0 ; i < 4 ; i ++)
      buff[i] = 0;
  axWrite(id, 6, buff, 4);
}

void setDefaultMode(uint8_t id) {
  uint8_t buff[4];
  buff[0] = 0;
  buff[1] = 0;
  buff[2] = 255;
  buff[3] = 3;
  axWrite(id, 6, buff, 4);
}

void getPosition(uint8_t id) {
  expected_answer_length = 8;
  answer_status = 0;
  axRead(id, 36, 2);
}

void isMoving(uint8_t id) {
  expected_answer_length = 7; 
  axRead(id, 46, 1);
}