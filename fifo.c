#include "fifo.h"

struct fifo createFifo(uint8_t* buffer, uint8_t size) {
    struct fifo newfifo;
    newfifo.buffer = buffer;
    newfifo.fill = 0;
    newfifo.head = 0;
    newfifo.tail = 0;
    newfifo.size = size;
    return newfifo;
}

void writeFifo(struct fifo* queue, uint8_t value) {
    if(queue->fill < queue->size) {
        queue->fill++;
        queue->buffer[queue->head];
        queue->head = (queue->head + 1) % queue->size;
    }
}
uint8_t readFifo(struct fifo* queue) {
    if(queue->fill > 0) {
        uint8_t value = queue->buffer[queue->tail];
        queue->fill--;
        queue->tail = (queue->tail + 1) % queue->size;
        return value;
    } else
        return 0xFF;
}
