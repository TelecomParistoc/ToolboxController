#include "ax12.h"
#include "eusart1extra.h"
#include <stdint.h>
#include <stdio.h>
#include "mcc_generated_files/pin_manager.h"
#include <xc.h>

char error;

/* called once on startup */
void ax12Setup() {
    printf("Hello World !\n");
    initAll();
    setDefaultMode(axid);
    setDefaultMode(axid2);
    setSpeed(axid, 50);
    setSpeed(axid2, 50);
    //printf("La position est : %d\n", getPosition(axid));
    //setPosition(axid, rentre);
    //setPosition(axid2, vertical);
    setPosition(axid, horiz);
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
    setPosition(axid2, lacher);
}

/* called in the main loop : performs all the needed updates */
void ax12Manager() {
    
}

void axWrite(uint8_t id, uint8_t reg, uint8_t * vals, uint8_t len) {
  uint8_t buff[20];
  buff[0] = 0xFF;
  buff[1] = 0xFF;
  buff[2] = id;
  buff[3] = 0x04;
  buff[4] = 0x03;
  buff[5] = reg;
  int foo = 0;
  for(uint8_t i = 0 ; i < len ; i ++){
      buff[6 + i] = vals[i];
      foo += vals[i];
  }
  foo += (7 + id + reg);
  buff[6 + len] = 255 -(foo % 256);
  serial1Write(buff, 7 + len);
  if(id != 254)
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

void initAll() {
  uint8_t buff[2];
  buff[0] = 255;
  buff[1] = 3;
  axWrite(254, 34, buff, 2);
  buff[0] = 1;
  axWrite(0xFE, 24, buff, 1); // Enable torque
  buff[0] = 2;
  axWrite(254, 18, buff, 1); // Shutdown ssi surchauffe
}

void setPosition(uint8_t id, int p) {
  uint8_t buff[2];
  buff[0] = p % 256;
  buff[1] = p / 256;
  axWrite(id, 30, buff, 2);
}

void setSpeed(uint8_t id, int p) {
  uint8_t buff[2];
  buff[0] = p % 256;
  buff[1] = p / 256;
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

uint8_t readToFlush() {
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

uint8_t isMoving(uint8_t id) {
  axRead(id, 46, 1);
  uint8_t answ[20];
  uint8_t len;
  serial1Read(answ, 4);
  len = answ[3];
  serial1Read(answ, len);
  error = answ[0];
  if(error != 0)
      printf("Erreur : %d\n", error);
  return answ[1];
}