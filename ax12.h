#ifndef AX12_H
#define AX12_H

#include <stdint.h>

/* called once on startup */
void ax12Setup();

/* called in the main loop : performs all the needed updates */
void ax12Manager();

void axWrite(char id, char reg, char val);

/* TODO : return value*/

void axRead(char id, char reg, char len);

void setAxPosition(char id, int p);
void setAxSpeed(char id, int p);
void setWheelMode(char id);
void setDefaultMode(char id);
void initAll();
char readToFlush();
uint16_t getPosition(uint8_t id);
char isForcing(char id);

#define axid 121
#define axid2 143

#endif