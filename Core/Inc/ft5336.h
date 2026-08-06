#ifndef __FT5336_H
#define __FT5336_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdint.h>

#define FT5336_MAX_POINTS  10

typedef struct
{
    uint8_t touched;
    uint8_t points;
    uint16_t x[FT5336_MAX_POINTS];
    uint16_t y[FT5336_MAX_POINTS];
} FT5336_TouchData_t;

uint8_t FT5336_Init(void);
uint8_t FT5336_ReadTouch(FT5336_TouchData_t *touch);

uint8_t FT5336_IsIntActive(void);
void FT5336_NotifyIrq(void);
uint8_t FT5336_GetIrqFlag(void);
void FT5336_ClearIrqFlag(void);

#ifdef __cplusplus
}
#endif

#endif
