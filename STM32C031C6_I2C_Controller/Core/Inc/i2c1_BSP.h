#ifndef I2C1_BSP_H
#define I2C1_BSP_H

#include "error_codes.h"
#include "stm32c0xx.h"
#include <stdint.h>

ErrorCode_t initCTRL_I2C1(void);
ErrorCode_t transmitCTRL_I2C1(uint8_t address, uint8_t *transmitBuffer, uint8_t size);
ErrorCode_t receiveCTRL_I2C1(uint8_t address, uint8_t *readBuffer, uint8_t size);


#endif

