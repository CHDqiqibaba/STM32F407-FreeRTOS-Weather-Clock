/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    rtc.c
  * @brief   This file provides code for the configuration
  *          of the RTC instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */
#include "app_log.h"
#include "app_time.h"
#include <stdio.h>

#define RTC_LSI_ASYNCH_PREDIV 127U
#define RTC_LSI_SYNCH_PREDIV  249U

static uint8_t RTC_WaitFlag(uint32_t flag, FlagStatus status, uint32_t timeout_ms)
{
  uint32_t start_tick = HAL_GetTick();

  while (__HAL_RCC_GET_FLAG(flag) != status)
  {
    if ((HAL_GetTick() - start_tick) > timeout_ms)
    {
      return 0;
    }
  }

  return 1;
}

static void RTC_PrintClockState(const char *tag)
{
  APP_LOG_DEBUG("%s BDCR=0x%08lX CSR=0x%08lX\r\n",
                tag,
                (unsigned long)RCC->BDCR,
                (unsigned long)RCC->CSR);
}

static uint8_t RTC_ConfigClockLSI(RTC_HandleTypeDef *rtcHandle)
{
  __HAL_RCC_LSI_ENABLE();
  if (RTC_WaitFlag(RCC_FLAG_LSIRDY, SET, 1000U) == 0U)
  {
    APP_LOG_ERROR("RTC LSI ready timeout\r\n");
    return 0;
  }

  if ((RCC->BDCR & RCC_BDCR_RTCSEL) != RCC_RTCCLKSOURCE_LSI)
  {
    if ((RCC->BDCR & RCC_BDCR_RTCSEL) != 0U)
    {
      APP_LOG_ERROR("RTC source switch needs backup reset\r\n");
      __HAL_RCC_BACKUPRESET_FORCE();
      __HAL_RCC_BACKUPRESET_RELEASE();
    }

    __HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSI);
  }

  rtcHandle->Init.AsynchPrediv = RTC_LSI_ASYNCH_PREDIV;
  rtcHandle->Init.SynchPrediv = RTC_LSI_SYNCH_PREDIV;
  __HAL_RCC_RTC_ENABLE();
  APP_LOG_BOOT("RTC clock source: LSI\r\n");
  RTC_PrintClockState("RTC clock after LSI");

  return 1;
}

static uint8_t RTC_ConfigClock(RTC_HandleTypeDef *rtcHandle)
{
  uint32_t current_source;

  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWR_EnableBkUpAccess();

  RTC_PrintClockState("RTC clock before");

  current_source = RCC->BDCR & RCC_BDCR_RTCSEL;

  if (current_source == RCC_RTCCLKSOURCE_LSE)
  {
    if ((RCC->BDCR & RCC_BDCR_LSEON) == 0U)
    {
      __HAL_RCC_LSE_CONFIG(RCC_LSE_ON);
    }

    if (RTC_WaitFlag(RCC_FLAG_LSERDY, SET, RCC_LSE_TIMEOUT_VALUE))
    {
      __HAL_RCC_RTC_ENABLE();
      APP_LOG_BOOT("RTC clock source: existing LSE\r\n");
      RTC_PrintClockState("RTC clock after LSE");
      return 1;
    }

    APP_LOG_ERROR("RTC existing LSE ready timeout\r\n");
    return RTC_ConfigClockLSI(rtcHandle);
  }

  if (current_source == RCC_RTCCLKSOURCE_LSI)
  {
    return RTC_ConfigClockLSI(rtcHandle);
  }

  __HAL_RCC_LSE_CONFIG(RCC_LSE_ON);
  if (RTC_WaitFlag(RCC_FLAG_LSERDY, SET, RCC_LSE_TIMEOUT_VALUE))
  {
    __HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSE);
    __HAL_RCC_RTC_ENABLE();
    APP_LOG_BOOT("RTC clock source: new LSE\r\n");
    RTC_PrintClockState("RTC clock after LSE");
    return 1;
  }

  APP_LOG_ERROR("RTC new LSE ready timeout, try LSI\r\n");
  return RTC_ConfigClockLSI(rtcHandle);
}

static uint8_t RTC_IsCalendarValid(const RTC_TimeTypeDef *time,
                                   const RTC_DateTypeDef *date)
{
  if (time == NULL || date == NULL)
  {
    return 0;
  }

  if (date->Year < 24U || date->Month < 1U || date->Month > 12U ||
      date->Date < 1U || date->Date > 31U ||
      time->Hours > 23U || time->Minutes > 59U || time->Seconds > 59U)
  {
    return 0;
  }

  return 1;
}

static uint8_t RTC_ReadAndPrintCalendar(const char *tag)
{
  RTC_TimeTypeDef time = {0};
  RTC_DateTypeDef date = {0};

  if (HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN) != HAL_OK)
  {
    APP_LOG_ERROR("%s RTC read time failed\r\n", tag);
    return 0;
  }

  if (HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN) != HAL_OK)
  {
    APP_LOG_ERROR("%s RTC read date failed\r\n", tag);
    return 0;
  }

  APP_LOG_BOOT("%s RTC calendar: 20%02u-%02u-%02u %02u:%02u:%02u\r\n",
               tag,
               date.Year,
               date.Month,
               date.Date,
               time.Hours,
               time.Minutes,
               time.Seconds);

  return RTC_IsCalendarValid(&time, &date);
}

/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    APP_LOG_ERROR("RTC HAL init failed, ISR=0x%08lX\r\n",
                  (unsigned long)RTC->ISR);
    RTC_PrintClockState("RTC HAL init fail");
    return;
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
  uint32_t rtc_bkp;
  uint8_t calendar_valid;

  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWR_EnableBkUpAccess();

  rtc_bkp = HAL_RTCEx_BKUPRead(&hrtc, APP_RTC_BKP_REG);
  APP_LOG_BOOT("RTC BKP: 0x%08lX\r\n", (unsigned long)rtc_bkp);

  if (rtc_bkp == APP_RTC_BKP_MAGIC)
  {
    calendar_valid = RTC_ReadAndPrintCalendar("RTC backup");
    if (calendar_valid)
    {
      APP_LOG_BOOT("RTC backup valid, keep calendar\r\n");
      return;
    }

    APP_LOG_ERROR("RTC backup magic valid, but calendar invalid\r\n");
    HAL_RTCEx_BKUPWrite(&hrtc, APP_RTC_BKP_REG, 0U);
  }

  APP_LOG_BOOT("RTC backup invalid, set default calendar\r\n");

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */
  APP_LOG_BOOT("RTC default calendar set, wait SNTP sync\r\n");

  /* USER CODE END RTC_Init 2 */

}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    if (RTC_ConfigClock(rtcHandle) == 0U)
    {
      APP_LOG_ERROR("RTC clock config failed, RTC disabled\r\n");
      return;
    }

  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{

  if(rtcHandle->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
