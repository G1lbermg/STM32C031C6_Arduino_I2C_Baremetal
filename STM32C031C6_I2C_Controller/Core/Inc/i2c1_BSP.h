#ifndef I2C1_BSP_H
#define I2C1_BSP_H

#include "stm32c0xx.h"
#include <stdint.h>

void I2C1_Init(void);
void I2C1_Transmit(uint8_t address, uint8_t *transmitBuffer, uint8_t size);
void I2C1_Receive(uint8_t address, uint8_t *readBuffer, uint8_t size);


#endif

