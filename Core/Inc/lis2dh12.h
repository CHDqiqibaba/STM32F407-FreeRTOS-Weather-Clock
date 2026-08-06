#ifndef __LIS2DH12_H
#define __LIS2DH12_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "i2c.h"
#include <stdint.h>

typedef enum
{
    LIS2DH12_MOTION_STABLE = 0,
    LIS2DH12_MOTION_MOVING
} LIS2DH12_MotionState_t;

typedef struct
{
    int32_t x_mg;
    int32_t y_mg;
    int32_t z_mg;

    uint32_t diff_mg;
    LIS2DH12_MotionState_t motion;
} LIS2DH12_Data_t;

uint8_t LIS2DH12_Init(void);
uint8_t LIS2DH12_Read(LIS2DH12_Data_t *data);
void LIS2DH12_PrintValue(const LIS2DH12_Data_t *data);

#ifdef __cplusplus
}
#endif

#endif