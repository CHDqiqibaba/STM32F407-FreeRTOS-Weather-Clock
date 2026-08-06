#ifndef __LPS22HH_H
#define __LPS22HH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "i2c.h"
#include <stdint.h>

typedef struct
{
    int32_t pressure_x100;     /* hPa * 100, example: 100865 = 1008.65 hPa */
    int32_t temperature_x100;  /* C * 100, example: 2534 = 25.34 C */
} LPS22HH_Data_t;

uint8_t LPS22HH_Init(void);
uint8_t LPS22HH_Read(LPS22HH_Data_t *data);
void LPS22HH_PrintValue(const LPS22HH_Data_t *data);

#ifdef __cplusplus
}
#endif

#endif