#ifndef __AHT20_H
#define __AHT20_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "i2c.h"
#include <stdint.h>

typedef struct
{
    int32_t temperature_x100;
    uint32_t humidity_x100;
} AHT20_Data_t;

uint8_t AHT20_Init(void);
uint8_t AHT20_Read(AHT20_Data_t *data);
void AHT20_PrintValue(const AHT20_Data_t *data);

#ifdef __cplusplus
}
#endif

#endif
