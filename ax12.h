#ifndef AX12_H
#define AX12_H

#include <stdint.h>

/* called once on startup */
void ax12Setup();

/* called in the main loop : performs all the needed updates */
void ax12Manager();

/* set argument of a future write*/
void setArg8(uint8_t arg);
void setArg16(uint16_t arg);

/* get answer argument (the answer are stored in a FIFO) */
uint8_t getAnswer8();
uint16_t getAnswer16();
/* get answer ID (and consume the answer in FIFO, next read will return next answer in FIFO) */
uint8_t getAnswerID();

/* add a read8 packet to the fifo */
void axRead8(uint16_t arg);
/* add a read16 packet to the fifo */
void axRead16(uint16_t arg);
/* add a write8 packet to the fifo */
void axWrite8(uint16_t arg);
/* add a write16 packet to the fifo */
void axWrite16(uint16_t arg);
/* add a status packet to the fifo */
void axStatus(uint8_t arg);
/* set mode to default and set position */
void axSetPosition(uint8_t id);
/* set mode to wheel and set speed */
void axSetSpeedWheel(uint8_t id);

#endif