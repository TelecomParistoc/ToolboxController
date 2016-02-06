#ifndef AX12_H
#define AX12_H

#include <stdint.h>

/* called once on startup */
void ax12Setup();

/* called in the main loop : performs all the needed updates */
void ax12Manager();

#endif