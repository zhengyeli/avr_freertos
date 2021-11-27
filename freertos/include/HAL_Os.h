#ifndef HAL_OS_H_
#define HAL_OS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


#define _IN_ /* indicate an input parameter */
#define _OU_ /* indicate a output parameter */
#define HAL_SEMA_WAIT_MAX_DELAY         0xFFFFFFFF

enum
{
    QCLOUD_RET_SUCCESS = 0,
    QCLOUD_ERR_INVAL = 1,
    QCLOUD_ERR_FAILURE = 2,
};

typedef void (*ThreadRunFunc)(void *arg);

typedef struct ThreadParams
{
    char         *thread_name;
    unsigned int      thread_id;
    ThreadRunFunc thread_func;
    void         *user_arg;
    uint16_t      priority;
    unsigned int      stack_size;
} ThreadParams;

/**
 * @brief Create a thread/task
 *
 * @param params    thread parameters
 * @return 0 when success, or error code otherwise
 */
int HAL_ThreadCreate(ThreadParams *params);

/**
*  freertos task delete
*/
void HAL_ThreadFree();

void HAL_Thread_Scheduler();


/**
 * @brief create semaphore
 *
 * @return a valid semaphore handle when success, or NULL otherwise
 */
void *HAL_SemaphoreCreate(void);

/**
 * @brief Destroy semaphore
 * @param sem   semaphore handle
 */
void HAL_SemaphoreDestroy(void *sem);

/**
 * @brief Post semaphore
 * @param sem   semaphore handle
 */
void HAL_SemaphorePost(void *sem);

/**
 * @brief Wait for semaphore
 * @param sem           semaphore handle
 * @param timeout_ms    waiting timeout value (unit: ms)
 * @return QCLOUD_RET_SUCCESS for success, or err code for failure
 */
int HAL_SemaphoreWait(void *sem, unsigned int timeout_ms);

/**
 * @brief Create mutex
 *
 * @return a valid mutex handle when success, or NULL otherwise
 */
void *HAL_MutexCreate(void);

/**
 * @brief Destroy mutex
 *
 * @param mutex     mutex handle
 */
void HAL_MutexDestroy(_IN_ void *mutex);

/**
 * @brief Lock a mutex in blocking way
 *
 * @param mutex     mutex handle
 */
void HAL_MutexLock(_IN_ void *mutex);

/**
 * @brief Lock a mutex in non-blocking way
 *
 * @param mutex     mutex handle
 * @return 0 for success, or err code for failure
 */
int HAL_MutexTryLock(_IN_ void *mutex);

/**
 * @brief Unlock/release mutex
 *
 * @param mutex     mutex handle
 */
void HAL_MutexUnlock(_IN_ void *mutex);

/**
 * @brief Malloc memory
 *
 * @param size   Expected memory size (unit: byte)
 * @return       pointer to the memory
 */
void *HAL_Malloc(_IN_ unsigned int size);

/**
 * @brief Free memory
 *
 * @param ptr   pointer to the pre-malloc memory
 */
void HAL_Free(_IN_ void *ptr);


/**
*@brief Get Free Heap Size
*/
unsigned int HAL_Get_Free_Heap_Size();

/**
*@brief Get Min Ever Free Heap Size
*/
unsigned int HAL_Get_Min_Ever_Free_Heap_Size();

/**
* Get task list info
*/
void HAL_Get_Task_List();

/*
* Get task run time state
*/
void HAL_Get_Task_time_state();


/*
* Queue
*/
int HAL_QueuePushFromISR(void *queue, void *item, bool wakeup);
int HAL_QueuePush(void *queue, void *item);
int HAL_QueuePull(void *queue, void *item);
void *HAL_QueueInit(unsigned int item_size, unsigned int length);


/**
 * @brief Print data to console in format
 *
 * @param fmt   print format
 * @param ...   variable number of arguments
 */
//void HAL_Printf(_IN_ const char *fmt, ...);
#define HAL_Printf(fmt, arg...)     \
    do {\
        {\
            printf(fmt"\r", ##arg);\
        } \
    }while(0)


/**
 * @brief Print data to string in format
 *
 * @param str   destination string
 * @param len   Max size of the output
 * @param fmt   print format
 * @param ...   variable number of arguments
 * @return      number of bytes that print successfull
 */
int HAL_Snprintf(_IN_ char *str, const int len, const char *fmt, ...);

/**
 Print data to string in format
  *
  * @param str   destination string
  * @param len   Max size of the output
  * @param fmt   print format
  * @param ap    arguments list
  * @return      number of bytes that print successfull

 */
int HAL_Vsnprintf(_OU_ char *str, _IN_ const int len, _IN_ const char *fmt, _IN_ va_list ap);


/**
 * @brief Delay operation in blocking way
 *
 * @param ms sleep interval in millisecond
 */
void HAL_DelayMs(_IN_ unsigned int ms);

/**
 * @brief Sleep for a while
 *
 * @param ms sleep interval in millisecond
 */
void HAL_SleepMs(_IN_ unsigned int ms);


/**
*   reboot device
*/
void HAL_DeviceReboot(void);

/**
*   get tick count
*/
unsigned int HAL_GetTickCount();

/**
*   get tick count from isr
*/
unsigned int HAL_GetTickCountFromISR();

/**
*   HAL_TimerInit
*/
void *HAL_TimerInit(ThreadRunFunc func, void *args, bool repeat);

/**
*   Start Timer
*/
bool HAL_TimerStart(void *ptimer, unsigned int ms);

/**
*   Reset Timer
*/
bool HAL_TimerReset(void *ptimer);

/**
*   Start Timer Delete
*/
bool HAL_TimerDestroy(void *ptimer);

/**
*   Get Timer info
*/
void *HAL_TimerGetArgs(void *ptimer);

#ifdef __cplusplus
}
#endif

#endif /* HAL_OS_H_ */
