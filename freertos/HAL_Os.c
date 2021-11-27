#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "queue.h"
#include "task.h"
#include "HAL_Os.h"

#include "timers.h"

//#include use_queue_c

// TODO platform dependant
void HAL_SleepMs( unsigned int ms)
{
    TickType_t ticks = ms / portTICK_PERIOD_MS * 10;
    vTaskDelay(ticks ? ticks : 1); /* Minimum delay = 1 tick */
    return;
}

int HAL_Snprintf(char *str, const int len, const char *fmt, ...)
{
    va_list args;
    int     rc;
    va_start(args, fmt);
    rc = vsnprintf(str, len, fmt, args);
    va_end(args);
    return rc;
}

void *HAL_Malloc(unsigned int size)
{
    return pvPortMalloc(size);
}

void HAL_Free(void *ptr)
{
    if (ptr)
        vPortFree(ptr);
}

unsigned int HAL_Get_Free_Heap_Size()
{
    return xPortGetFreeHeapSize();
}

unsigned int HAL_Get_Min_Ever_Free_Heap_Size()
{
    return xPortGetMinimumEverFreeHeapSize();
}
#ifdef DEBUG_VERSION
void HAL_Get_Task_info(char *buffer)
{
    vTaskList((char *) buffer);
    HAL_Printf("任务名      任务状态 优先级   剩余栈 任务序号\r\n");
    HAL_Printf("\r\n%s\r\n", buffer);
    HAL_Printf("\r\nFree_Heap:%d,Min_Ever_Free_Heap:%d\r\n", HAL_Get_Free_Heap_Size(), HAL_Get_Min_Ever_Free_Heap_Size());
}
#endif

void HAL_Get_Task_List(uint8_t * buffer)
{
    vTaskList((uint8_t *) buffer);
    HAL_Printf("\n\r任务名  状态 优先级 剩余栈 序号");
    HAL_Printf("\n%s", buffer);
    vPortFree(buffer);
    HAL_Printf("Free_Heap:%d,Min_Ever_Free_Heap:%d\r\n", HAL_Get_Free_Heap_Size(), HAL_Get_Min_Ever_Free_Heap_Size());
}
/*
void *HAL_MutexCreate(void)
{
#ifdef MULTITHREAD_ENABLED
    xSemaphoreHandle mutex = xSemaphoreCreateMutex();
    if (NULL == mutex)
    {
        HAL_Printf("%s: xSemaphoreCreateMutex failed\n", __FUNCTION__);
        return NULL;
    }
    return mutex;
#else
    return (void *)0xFFFFFFFF;
#endif
}

void HAL_MutexDestroy(void *mutex)
{
#ifdef MULTITHREAD_ENABLED
    if (!mutex)
    {
        HAL_Printf("%s: invalid mutex\n", __FUNCTION__);
        return;
    }
    if (xSemaphoreTake(mutex, portMAX_DELAY) != pdTRUE)
    {
        HAL_Printf("%s: xSemaphoreTake failed\n", __FUNCTION__);
    }
    if (xSemaphoreGive(mutex) != pdTRUE)
    {
        HAL_Printf("%s: xSemaphoreGive failed\n", __FUNCTION__);
        return;
    }
    vSemaphoreDelete(mutex);
#else
    return;
#endif
}

void HAL_MutexLock(void *mutex)
{
#ifdef MULTITHREAD_ENABLED
    if (!mutex)
    {
        HAL_Printf("%s: invalid mutex\n", __FUNCTION__);
        return;
    }
    if (xSemaphoreTake(mutex, portMAX_DELAY) != pdTRUE)
    {
        HAL_Printf("%s: xSemaphoreTake failed\n", __FUNCTION__);
        return;
    }
#else
    return;
#endif
}

int HAL_MutexTryLock(void *mutex)
{
#ifdef MULTITHREAD_ENABLED
    if (!mutex)
    {
        HAL_Printf("%s: invalid mutex\n", __FUNCTION__);
        return -1;
    }
    if (xSemaphoreTake(mutex, 0) != pdTRUE)
    {
        //HAL_Printf("%s: xSemaphoreTake failed\n", __FUNCTION__);
        return -1;
    }
    return 0;
#else
    return 0;
#endif
}

void HAL_MutexUnlock(void *mutex)
{
#ifdef MULTITHREAD_ENABLED
    if (!mutex)
    {
        HAL_Printf("%s: invalid mutex\n", __FUNCTION__);
        return;
    }
    if (xSemaphoreGive(mutex) != pdTRUE)
    {
        HAL_Printf("%s: xSemaphoreGive failed\n", __FUNCTION__);
        return;
    }
#else
    return;
#endif
}
*/
#ifdef MULTITHREAD_ENABLED

//freertos task delete
void HAL_ThreadFree()
{
    vTaskDelete(NULL);
}

// platform-dependant thread create function
int HAL_ThreadCreate(ThreadParams *params)
{
    if (params == NULL)
        return QCLOUD_ERR_INVAL;
    if (params->thread_name == NULL)
    {
       // HAL_Printf("thread name is required for FreeRTOS platform!\n");
        return QCLOUD_ERR_INVAL;
    }
    int ret = xTaskCreate(params->thread_func, params->thread_name, params->stack_size, (void *)params->user_arg,
                          params->priority, (void *)&params->thread_id);
    if (ret != pdPASS)
    {
        //HAL_Printf("%s: xTaskCreate failed: %d\n", __FUNCTION__, ret);
        return QCLOUD_ERR_FAILURE;
    }
    return QCLOUD_RET_SUCCESS;
}

void  HAL_Thread_Scheduler()
{
    vTaskStartScheduler();
}
#endif


#ifdef use_queue_c
/*Queue Init*/
void *HAL_QueueInit(unsigned int item_size, unsigned int length)
{
    QueueHandle_t queueHandle = xQueueCreate(item_size, length);
    if (queueHandle == NULL)
    {
        HAL_Printf("%s: xSemaphoreCreateMutex failed\n", __FUNCTION__);
    }
    return queueHandle;
}

/*Queue delete*/
void HAL_QueueDelete(void *queue)
{
    vQueueDelete((QueueHandle_t)queue);
}

/*Queue Push*/
int HAL_QueuePush(void *queue, void *item)
{
    if (uxQueueSpacesAvailable((QueueHandle_t)queue) <= 0)
    {
        //HAL_Printf("push queue: %d wait: %d free :%d\r\n", uxQueueSpacesAvailable((QueueHandle_t)queue), uxQueueMessagesWaiting((QueueHandle_t)queue), HAL_Get_Free_Heap_Size());
        return -1;
    }

    return (xQueueSendToBack((QueueHandle_t)queue, item, portMAX_DELAY) == pdPASS) ? 0 : -1;
}

/*Queue Pull*/
int HAL_QueuePull(void *queue, void *item)
{
    return (xQueueReceive((QueueHandle_t)queue, item, portMAX_DELAY) == pdPASS) ? 0 : -1;
}

/*Queue Push from ISR*/
int HAL_QueuePushFromISR(void *queue, void *item, bool wakeup)
{
    return (xQueueSendToBackFromISR((QueueHandle_t)queue, item, (BaseType_t *)&wakeup) == pdPASS) ? 0 : -1;
}

void *HAL_SemaphoreCreate(void)
{
    //return (void *)osSemaphoreCreate(NULL, 1);
}

void HAL_SemaphoreDestroy(void *sem)
{
    //osStatus ret;
    //ret = osSemaphoreDelete((osSemaphoreId)sem);
   // if (osOK != ret)
    {
       // printf("HAL_SemaphoreDestroy err, err:%d\n\r", ret);
    }
}

void HAL_SemaphorePost(void *sem)
{
    //osStatus ret;
   // ret = osSemaphoreRelease((osSemaphoreId)sem);
    //if (osOK != ret)
    {
        //printf("HAL_SemaphorePost err, err:%d\n\r", ret);
    }
}

int HAL_SemaphoreWait(void *sem, unsigned int timeout_ms)
{
    //return osSemaphoreWait((osSemaphoreId)sem, timeout_ms);
}

#endif

/*
unsigned int HAL_GetTickCount()
{
    return xTaskGetTickCount();
}

unsigned int HAL_GetTickCountFromISR()
{
    return xTaskGetTickCountFromISR();
}*/



#if configUSE_TIMERS == 1

void *HAL_TimerInit(ThreadRunFunc func, void *args, bool repeat)
{
    return (void *)xTimerCreate("Os_Timer", portMAX_DELAY, repeat, args, (TimerCallbackFunction_t)func);
}

bool HAL_TimerStart(void *ptimer, unsigned int ms)
{
    return xTimerChangePeriod((TimerHandle_t)ptimer, pdMS_TO_TICKS(ms), 0);
}

bool HAL_TimerStop(void *ptimer)
{
    return xTimerStop((TimerHandle_t)ptimer, 0);
}

bool HAL_TimerReset(void *ptimer)
{
    return xTimerReset((TimerHandle_t)ptimer, portMAX_DELAY);
}

bool HAL_TimerDestroy(void *ptimer)
{
    return xTimerDelete((TimerHandle_t)ptimer, 0);
}

void *HAL_TimerGetArgs(void *ptimer)
{
    return pvTimerGetTimerID((TimerHandle_t)ptimer);
}


#endif