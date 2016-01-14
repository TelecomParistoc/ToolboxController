#ifndef AX12_H
#define AX12_H

void axWrite(char id, char reg, char val);

/* TODO : return value*/

void axRead(char id, char reg, char len);

void setAxPosition(char id, int p);
void setAxSpeed(char id, int p);
void setWheelMode(char id);
void setDefaultMode(char id);
void restart(char id);
char readToFlush();
char isForcing(char id);

#define axid 133
#define axid2 143

#endif