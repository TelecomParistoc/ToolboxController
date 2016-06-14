
#ifndef FIFO_H
#define	FIFO_H

#include <stdint.h>

struct fifo {
    uint8_t* buffer;
    uint8_t size;
    uint8_t head;
    uint8_t tail;
    uint8_t fill;
};

struct fifo createFifo(uint8_t* buffer, uint8_t size);

void writeFifo(struct fifo* queue, uint8_t value);
uint8_t readFifo(struct fifo* queue);


#endif	/* FIFO_H */

