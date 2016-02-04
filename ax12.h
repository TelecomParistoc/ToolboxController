#ifndef AX12_H
#define AX12_H

#include <stdint.h>

/* called once on startup */
void ax12Setup();

/* called in the main loop : performs all the needed updates */
void ax12Manager();

// initializes all Ax-12
void initAll();

// Writes len first values in array vals in registers beginning at reg of Ax-12(id)
void axWrite(uint8_t id, uint8_t reg, uint8_t * vals, uint8_t len);

// reads len registers starting with register reg fom Ax-12(id)
void axRead(uint8_t id, uint8_t reg, uint8_t len);

// sets p as goal position for Ax-12(id)
void setPosition(uint8_t id, uint16_t cons);

// sets p as goal speed for Ax-12(id)
void setSpeed(uint8_t id, uint16_t cons);

// puts Ax-12(id) in wheel mode
void setWheelMode(uint8_t id);

// puts Ax-12(id) in the default mode
void setDefaultMode(uint8_t id);

// called by USART Interrupt
void readBuffer();

// returns the position of an Ax-12
void getPosition(uint8_t id);

// polls if Ax-12 is moving or forcing
void Polling(uint8_t id);

#define axid 121
#define axid2 148

/*Ax 12 qui contrôle l'aimant*/

#define vertical 532
#define lacher 300

/*Ax 12 qui positionne le système de pêche*/

#define rentre 770
#define horiz 480

#endif