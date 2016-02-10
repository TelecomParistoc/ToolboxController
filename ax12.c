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
volatile AX12order order;
volatile int16_t position;
volatile int16_t parameter;

// Initializes all Ax-12
static void initAll();

// Writes len first values in array vals in registers beginning at reg of Ax-12(id)
static void axWrite(uint8_t reg, uint8_t * vals, uint8_t len);

// Asks to read len registers starting with register reg fom Ax-12(id)
static void axRead(uint8_t reg, uint8_t len);

// Reads the answer of the last axRead call
static void readBuffer();

// sets cons as goal position for Ax-12(id)
static void setPosition(uint16_t cons);

// sets cons as goal speed for Ax-12(id)
static void setSpeed(uint16_t cons);

// sets cons as max torque for Ax-12(id)
static void setMaxTorque(uint16_t cons);

// puts Ax-12(id) in wheel mode
static void setWheelMode();

// puts Ax-12(id) in the default mode
static void setDefaultMode();

// asks the position of an Ax-12
static void getPosition();

// checks if Ax-12 is moving
static void isMoving();

/* called once on startup */
void ax12Setup() {
    printf("Hello World !\n");
    activeID = 254;
    state = WHEEL_MODE;
    initAll();
}

/* called in the main loop : performs all the needed updates */
void ax12Manager() {
    if(order != NONE){
        switch(order){
            case SET_SPEED_WHEEL:
                break;
            case SET_SPEED_DEFAULT:
                break;
            case SET_POSITION:
                break;
            case SET_TORQUE:
                break;
        }
        order = NONE;
        return;
    }
    if(answer_status == 1){
        readBuffer();
        answer_status = 0;
    }
}

void axWrite(uint8_t reg, uint8_t * vals, uint8_t len) {
  uint8_t buff[20];
  buff[0] = 0xFF;
  buff[1] = 0xFF;
  buff[2] = activeID;
  buff[3] = len + 3;
  buff[4] = 0x03;
  buff[5] = reg;
  uint8_t checksum = 0;
  for(uint8_t i = 0 ; i < len ; i ++){
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
  for(uint8_t i = 0 ; i < 4 ; i ++)
      EUSART1_Read();
  if (EUSART1_Read() & 32 == 32)
      raiseInterrupt(AX12_FORCING);
  if (expected_answer_length == 8){
      position = EUSART1_Read();  
      position += (EUSART1_Read() << 8);
  } else {
      if(EUSART1_Read() == 1)
          raiseInterrupt(AX12_FINISHED_MOVE);
  }
  printf("On lit %d\n", position);
}

void initAll() {
  uint8_t buff[2];
  buff[0] = 255;
  buff[1] = 3;
  axWrite(34, buff, 2);
  buff[0] = 1;
  axWrite(24, buff, 1); // Enable torque
  axWrite(16, buff, 1); // Status return only if READ
  buff[0] = 2;
  axWrite(18, buff, 1); // Shutdown ssi surchauffe
}

void setPosition(uint16_t cons) {
  uint8_t buff[2];
  buff[0] = (uint8_t) cons;
  buff[1] = cons >> 8;
  axWrite(30, buff, 2);
}

void setSpeed(uint16_t cons) {
  uint8_t buff[2];
  buff[0] = (uint8_t) cons;
  buff[1] = cons >> 8;
  axWrite(32, buff, 2);
}

void setMaxTorque(uint16_t cons) {
  uint8_t buff[2];
  buff[0] = (uint8_t) cons;
  buff[1] = cons >> 8;
  axWrite(34, buff, 2);
}

void setWheelMode() {
  uint8_t buff[4];
  for(int i = 0 ; i < 4 ; i ++)
      buff[i] = 0;
  axWrite(6, buff, 4);
}

void setDefaultMode() {
  uint8_t buff[4];
  buff[0] = 0;
  buff[1] = 0;
  buff[2] = 255;
  buff[3] = 3;
  axWrite(6, buff, 4);
}

void getPosition() {
  expected_answer_length = 8;
  answer_status = 0;
  axRead(36, 2);
}

void isMoving() {
  expected_answer_length = 7; 
  axRead(46, 1);
}