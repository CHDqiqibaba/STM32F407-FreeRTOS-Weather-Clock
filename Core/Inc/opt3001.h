#ifndef __OPT3001_H
#define __OPT3001_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "i2c.h"
#include <stdint.h>

typedef struct
{
    uint32_t lux_x100;

    uint16_t raw;
    uint8_t exponent;
    uint16_t mantissa;
} OPT3001_Data_t;

uint8_t OPT3001_Init(void);
uint8_t OPT3001_Read(OPT3001_Data_t *data);
void OPT3001_PrintValue(const OPT3001_Data_t *data);

#ifdef __cplusplus
}
#endif

#endif