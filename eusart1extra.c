#include "mcc_generated_files/eusart1.h"
#include "eusart1extra.h"
#include <stdio.h>

void serial1Write(uint8_t * buf, uint8_t size){
    for(uint8_t i = 0 ; i < size ; i++)
        EUSART1_Write(buf[i]);
}

void serial1Read(uint8_t * buf, uint8_t size){
    for(uint8_t i = 0 ; i < size ; i++)
        buf[i] = EUSART1_Read();
}
