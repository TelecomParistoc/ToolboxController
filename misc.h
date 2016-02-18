/* 
 * File:   misc.h
 * Author: Arnaud "JS" Bonetti
 *
 * Contains functions implementing simple services
 */

#ifndef MISC_H
#define	MISC_H

#include <stdint.h>

inline void sensorManager();
inline void collisionManager();

int8_t getButtons();
int8_t getSensors();
int8_t getCollisions();

void setCollisionsMask(int8_t mask);
void setSensorsMask(int8_t mask);

void setLEDs(int8_t leds);
void setOnlyLEDs(int8_t leds);
void clearOnlyLEDs(int8_t leds);

void setPWM1(uint8_t value);
void setPWM2(uint8_t value);
void setPWM3(uint8_t value);
void setPWM4(uint8_t value);

#endif	/* MISC_H */

