#include "ax12.h"
#include "eusart1extra.h"
#include <stdint.h>
#include <stdio.h>
#include "mcc_generated_files/pin_manager.h"
#include <xc.h>

/* called once on startup */
void ax12Setup() {
    printf("Hello World !\n");
    initAll();
    axWrite(axid, 24, 1); // Enable Torque
    axWrite(axid, 18, 34); // Shutdown ssi surchauffe
    axWrite(axid2, 24, 1); // Enable Torque
    axWrite(axid2, 18, 34); // Shutdown ssi surchauffe
    setDefaultMode(axid);
    setDefaultMode(axid2);
    setAxSpeed(axid, 50);
    setAxSpeed(axid2, 50);
    //setAxPosition(axid, rentre);
    //setAxPosition(axid2, vertical);
    setAxPosition(axid, horiz);
    printf("Descendu1");
    while(!SEN3_GetValue());
    setAxPosition(axid, rentre);
    printf("Monte1");
    while(!SEN3_GetValue());
    setAxPosition(axid, horiz);
    printf("Descendu2");
    while(!SEN3_GetValue());
    setAxPosition(axid, rentre);
    printf("Monte2");
    while(!SEN3_GetValue());
    setAxPosition(axid, horiz);
    printf("Descendu3");
    while(!SEN3_GetValue());
    setAxPosition(axid2, lacher);
    //printf("La position est : %d\n", getPosition(axid));
}

/* called in the main loop : performs all the needed updates */
void ax12Manager() {
    
}


void axWrite(uint8_t id, uint8_t reg, uint8_t val) {
  uint8_t buff[8];
  buff[0] = 0xFF;
  buff[1] = 0xFF;
  buff[2] = id;
  buff[3] = 0x04;
  buff[4] = 0x03;
  buff[5] = reg;
  buff[6] = val;
  int foo = (7+id+reg+val) % 256;
  buff[7] = 255-foo;
  serial1Write(buff, 8);
  readToFlush();
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
  int foo = (6+id+reg+len) % 256;
  buff[7] = 255-foo;
  serial1Write(buff, 8);
}

void setAxPosition(uint8_t id, int p) {
  uint8_t buff[9];
  uint8_t low = p % 256;
  uint8_t high = p / 256;
  buff[0] = 0xFF;
  buff[1] = 0xFF;
  buff[2] = id;
  buff[3] = 0x05;
  buff[4] = 0x03;
  buff[5] = 30;
  buff[6] = low;
  buff[7] = high;
  int foo = (38+id+buff[6]+buff[7]) % 256;
  buff[8] = 255-foo;
  serial1Write(buff, 9);
  readToFlush();
}

void setAxSpeed(uint8_t id, int p) {
  uint8_t buff[9];
  uint8_t low = p % 256;
  uint8_t high = p / 256;
  buff[0] = 0xFF;
  buff[1] = 0xFF;
  buff[2] = id;
  buff[3] = 0x05;
  buff[4] = 0x03;
  buff[5] = 32;
  buff[6] = low;
  buff[7] = high;
  int foo = (40+id+buff[6]+buff[7]) % 256;
  buff[8] = 255-foo;
  serial1Write(buff, 9);
  readToFlush();
}

void setWheelMode(uint8_t id) {
  uint8_t buff[11];
  buff[0] = 0xFF;
  buff[1] = 0xFF;
  buff[2] = id;
  buff[3] = 0x07;
  buff[4] = 0x03;
  buff[5] = 6;
  buff[6] = 0;
  buff[7] = 0;
  buff[8] = 0;
  buff[9] = 0;
  int foo = (16+id) % 256;
  buff[10] = 255-foo;
  serial1Write(buff, 11);
  readToFlush();
}

void setDefaultMode(uint8_t id) {
  uint8_t buff[11];
  buff[0] = 0xFF;
  buff[1] = 0xFF;
  buff[2] = id;
  buff[3] = 0x07;
  buff[4] = 0x03;
  buff[5] = 6;
  buff[6] = 0;
  buff[7] = 0;
  buff[8] = 255;
  buff[9] = 3;
  int foo = (16+258+id) % 256;
  buff[10] = 255-foo;
  serial1Write(buff, 11);
  readToFlush();
}

void initAll() {
  uint8_t buff[9];
  buff[0] = 0xFF;
  buff[1] = 0xFF;
  buff[2] = 0xFE;
  buff[3] = 0x05;
  buff[4] = 0x03;
  buff[5] = 34;
  buff[6] = 255;
  buff[7] = 3;
  int foo = (34+258+8+254) % 256;
  buff[8] = 255-foo;
  serial1Write(buff, 9);
}


uint8_t readToFlush() {
  //delay(40);
  uint8_t answ[20];
  uint8_t len;
  serial1Read(answ, 4);
  len = answ[3];
  serial1Read(answ, len);
  return answ[0];
}

uint16_t getPosition(uint8_t id) {
  axRead(id, 36, 2);
  uint8_t answ[20];
  uint8_t len;
  serial1Read(answ, 4);
  len = answ[3];
  serial1Read(answ, len);
  return 256*answ[2] + answ[1];
}

uint8_t isForcing(uint8_t id) {
  uint8_t buff[6];
  buff[0] = 0xFF;
  buff[1] = 0xFF;
  buff[2] = id;
  buff[3] = 0x02;
  buff[4] = 0x01;
  int foo = (3+id) % 256;
  buff[5] = 255-foo;
  serial1Write(buff, 6);
  uint8_t error = readToFlush();
  return ((error & 32) == 32);
}

