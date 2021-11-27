//ICC-AVR application builder : 2021/10/16 15:41:33
// Target : M16
// Crystal: 16.000Mhz

#include "app.h"
#include "FreeRTOS.h"
#include "task.h"
#include "HAL_Os.h"

void delay(uint ms)
{
  uint i, j;
  for (i = 0; i < ms; i++)
  {
    for (j = 0; j < 1141; j++)
      ;
  }
}

void port_init(void)
{
  PORTA = 0x00;
  DDRA = 0x00;
  PORTB = 0x00;
  DDRB = 0x00;
  PORTC = 0x00; //m103 output only
  DDRC = 0x00;
  PORTD = 0x00;
  DDRD = 0x00;

  //digital_port_init();

  uart0_port_init();

  int_port_init();
}

//call this routine to initialize all peripherals
void init_devices(void)
{
  //stop errant interrupts until set up
  _CLI(); //disable all interrupts
  port_init();
  //watchdog_init();
  //adc_init();
  uart0_init();

  //MCUCSR |= 1 << JTD; //
  //MCUCSR |= 1 << JTD; //

  GICR = 0xC0;
  //TIMSK |= 0xc0; //timer2
  //TIMSK |= 0x03; //timer0 interrupt sources
  TIMSK = 0xC3;
  _SEI(); //re-enable interrupts
          //all peripherals are now initialized
}

#ifdef use_freertos

TaskHandle_t xhandle = NULL;
TaskHandle_t xhandle1 = NULL;
//TaskHandle_t xhandle_tasklist = (void *)0;

void thread_func()
{
  while (1)
  {
    //printf("1");
//printf("11111111111111");
    usart_transmit_str("--\n");
    HAL_SleepMs(1000);
  }
}

void thread_func1()
{
  unsigned char i = 0;
  while (1)
  {
    //printf("%d\n",i);
    i = i + 1;
    //digital_show_one_num(7, 8);
    usart_transmit_str("11\n");
    HAL_SleepMs(1000);
  }
}

#endif


int main()
{

#if use_heap5 == 1
  static unsigned char ucHeap[configTOTAL_HEAP_SIZE];

  HeapRegion_t xHeapRegions[] =
      {
          {ucHeap, sizeof(ucHeap)}, //<< Defines a block of 0x10000 bytes starting at address 0x80000000
          //{ ( uint8_t * ) 0x90000000UL, 0xa0000 }, //<< Defines a block of 0xa0000 bytes starting at address of 0x90000000
          {NULL, 0} //<< Terminates the array.
      };

  vPortDefineHeapRegions(xHeapRegions);
#endif
  int ret = 1;
  init_devices();

  //printf("%d", temp);
  //num = start_adc();
//RTEEPROMwrite(0X01,1);
//num = RTEEPROMread(0x01);
#ifdef use_freertos

  ThreadParams ThreadParam;
  ThreadParam.thread_name = "task1";
  ThreadParam.priority = 4;
  ThreadParam.user_arg = NULL;
  ThreadParam.stack_size = 50;
  ThreadParam.thread_id = xhandle;
  ThreadParam.thread_func = thread_func;
  ret = HAL_ThreadCreate(&ThreadParam);
  if (ret != QCLOUD_RET_SUCCESS)
  {
    usart_transmit_str("1task-ThreadCreate-is-fail\n");
  }
  
  ThreadParam.thread_name = "task2";
  ThreadParam.priority = 4;
  ThreadParam.user_arg = NULL;
  ThreadParam.stack_size = 100;
  ThreadParam.thread_id = xhandle1;
  ThreadParam.thread_func = thread_func1;
  ret = HAL_ThreadCreate(&ThreadParam);
  if (ret != QCLOUD_RET_SUCCESS)
  {
    usart_transmit_str("2task-ThreadCreate-is-fail\n");
  }
  HAL_Thread_Scheduler();
#endif
  //主程序不能结束，否则定时器停止，外部中断也是
  //main fuction caan not stop , or the system will stop
  //usart_transmit_str("33333333333333");
  while (1)
  {
    usart_transmit_str("freertos start fail,i am [false]\n");
    break;
  }

  return 0;
}