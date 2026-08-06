#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>
#include "stm32f4xx.h"

extern uint32_t SystemCoreClock;

/*-----------------------------------------------------------
 * Hardware and tick configuration
 *----------------------------------------------------------*/
#define configCPU_CLOCK_HZ                      ( SystemCoreClock )
#define configTICK_RATE_HZ                      ( ( TickType_t ) 1000 )
#define configTICK_TYPE_WIDTH_IN_BITS           TICK_TYPE_WIDTH_32_BITS

/*-----------------------------------------------------------
 * Scheduler configuration
 *----------------------------------------------------------*/
#define configUSE_PREEMPTION                    1
#define configUSE_TIME_SLICING                  1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1
#define configUSE_TICKLESS_IDLE                 0
#define configMAX_PRIORITIES                    8
#define configMINIMAL_STACK_SIZE                ( ( uint16_t ) 128 )
#define configMAX_TASK_NAME_LEN                 16
#define configIDLE_SHOULD_YIELD                 1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES   1
#define configQUEUE_REGISTRY_SIZE               8
#define configENABLE_BACKWARD_COMPATIBILITY     0
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 0
#define configUSE_MINI_LIST_ITEM                1
#define configSTACK_DEPTH_TYPE                  size_t
#define configMESSAGE_BUFFER_LENGTH_TYPE        size_t
#define configUSE_NEWLIB_REENTRANT              0

/*-----------------------------------------------------------
 * Memory allocation
 *
 * This heap is FreeRTOS heap, not the whole STM32 SRAM.
 * Task stacks, queues, semaphores, timers, event groups and stream buffers
 * created by FreeRTOS dynamic APIs come from this heap.
 *----------------------------------------------------------*/
#define configSUPPORT_STATIC_ALLOCATION         0
#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configTOTAL_HEAP_SIZE                   ( ( size_t ) ( 40 * 1024 ) )
#define configAPPLICATION_ALLOCATED_HEAP         0
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP 0
#define configENABLE_HEAP_PROTECTOR             0
#define configHEAP_CLEAR_MEMORY_ON_FREE         1

/*-----------------------------------------------------------
 * Hook functions
 *----------------------------------------------------------*/
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configUSE_MALLOC_FAILED_HOOK            1
#define configUSE_DAEMON_TASK_STARTUP_HOOK      0
#define configCHECK_FOR_STACK_OVERFLOW          2

#define configASSERT( x )                       \
    do                                         \
    {                                          \
        if( ( x ) == 0 )                       \
        {                                      \
            __disable_irq();                   \
            for( ;; )                          \
            {                                  \
            }                                  \
        }                                      \
    } while( 0 )

/*-----------------------------------------------------------
 * Software timers
 *----------------------------------------------------------*/
#define configUSE_TIMERS                        1
#define configTIMER_TASK_PRIORITY               ( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH                10
#define configTIMER_TASK_STACK_DEPTH            256

/*-----------------------------------------------------------
 * FreeRTOS kernel objects
 *----------------------------------------------------------*/
#define configUSE_TASK_NOTIFICATIONS            1
#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_COUNTING_SEMAPHORES           1
#define configUSE_QUEUE_SETS                    0
#define configUSE_EVENT_GROUPS                  1
#define configUSE_STREAM_BUFFERS                1
#define configUSE_SB_COMPLETED_CALLBACK         0
#define configUSE_APPLICATION_TASK_TAG          0
#define configUSE_POSIX_ERRNO                   0

/*-----------------------------------------------------------
 * Run time stats and debug helpers
 *----------------------------------------------------------*/
#define configGENERATE_RUN_TIME_STATS           0
#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    1
#define configSTATS_BUFFER_MAX_LENGTH           0xFFFF

/*-----------------------------------------------------------
 * Co-routines are legacy. Do not use them in this project.
 *----------------------------------------------------------*/
#define configUSE_CO_ROUTINES                   0
#define configMAX_CO_ROUTINE_PRIORITIES         1

/*-----------------------------------------------------------
 * Cortex-M4 interrupt priority configuration
 *
 * STM32F407 uses 4 implemented priority bits: logical priority 0..15.
 * Lower number means higher interrupt priority.
 *
 * Interrupts that call FreeRTOS FromISR APIs must use logical priority
 * 5 or lower urgency, for example 5, 6, 7 ... 15.
 *----------------------------------------------------------*/
#define configPRIO_BITS                                 4
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5

/* Keil ARMCC/RVDS assembles port.c asm functions directly, so keep these
 * shifted priorities as plain constants instead of C expressions.
 * 15 << (8 - 4) = 0xF0, 5 << (8 - 4) = 0x50. */
#define configKERNEL_INTERRUPT_PRIORITY                 0xF0
#define configMAX_SYSCALL_INTERRUPT_PRIORITY            0x50
#define configMAX_API_CALL_INTERRUPT_PRIORITY           configMAX_SYSCALL_INTERRUPT_PRIORITY

/*-----------------------------------------------------------
 * Cortex-M exception handler mapping for Keil ARMCC / RVDS ARM_CM4F port.
 *
 * SysTick is used by FreeRTOS.
 * TIM7 remains the HAL timebase and keeps calling HAL_IncTick().
 *
 * Because these aliases make port.c provide SVC_Handler, PendSV_Handler and
 * SysTick_Handler, the empty CubeMX handlers with the same names in
 * stm32f4xx_it.c must be removed or disabled before linking.
 *----------------------------------------------------------*/
#define vPortSVCHandler                         SVC_Handler
#define xPortPendSVHandler                      PendSV_Handler
#define xPortSysTickHandler                     SysTick_Handler
#define configCHECK_HANDLER_INSTALLATION        1

/*-----------------------------------------------------------
 * Optional API inclusion
 *----------------------------------------------------------*/
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_xTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_uxTaskGetStackHighWaterMark     1
#define INCLUDE_xTaskGetIdleTaskHandle          0
#define INCLUDE_eTaskGetState                   1
#define INCLUDE_xTimerPendFunctionCall          1
#define INCLUDE_xTaskAbortDelay                 0
#define INCLUDE_xTaskGetHandle                  1
#define INCLUDE_xTaskResumeFromISR              1

#endif /* FREERTOS_CONFIG_H */


