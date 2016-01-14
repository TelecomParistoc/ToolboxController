/* 
 * File:   eusart1extra.h
 * Author: tanguy
 *
 * Created on 14 janvier 2016, 23:02
 */

#ifndef EUSART1EXTRA_H
#define	EUSART1EXTRA_H

#include <stdint.h>

void serial1Write(uint8_t * buf, uint8_t n);
void serial1Read(uint8_t * buf, uint8_t n);

#endif	/* EUSART1EXTRA_H */

