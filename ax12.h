#ifndef AX12_H
#define AX12_H

#include <stdint.h>

/* called once on startup */
void ax12Setup();

/* called in the main loop : performs all the needed updates */
void ax12Manager();

// initializes all Ax-12
void initAll();

// Writes val in register reg of Ax-12(id)
void axWrite(char id, char reg, char val);

// reads len registers starting with register reg fom Ax-12(id)
void axRead(char id, char reg, char len);

// sets p as goal position for Ax-12(id)
void setPosition(char id, int p);

// sets p as goal speed for Ax-12(id)
void setSpeed(char id, int p);

// puts Ax-12(id) in wheel mode
void setWheelMode(char id);

// puts Ax-12(id) in the default mode
void setDefaultMode(char id);

// to flush a status packet from an Ax-12
char readToFlush();

// returns the position of an Ax-12
uint16_t getPosition(uint8_t id);

// returns true if Ax-12(id) is forcing
char isForcing(char id);

// returns true if Ax-12(id) is moving by its own power
char isMoving(char id);



#define axid 121
#define axid2 148

/*Ax 12 qui contrôle l'aimant*/

#define vertical 532
#define lacher 300

/*Ax 12 qui positionne le système de pêche*/

#define rentre 777
#define horiz 463

#endif