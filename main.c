//ICC-AVR application builder : 2021/10/16 15:41:33
// Target : M16
// Crystal: 16.000Mhz

#include "app.h"
#include "FreeRTOS.h"
#include "task.h"
#include "HAL_Os.h"

void delay(uint ms)
{
        uint i,j;
	   for(i=0;i<ms;i++)
	   {
	   for(j=0;j<1141;j++);
       }
}

void port_init(void)
{
 PORTA = 0x00;
 DDRA  = 0x00;
 PORTB = 0x00;
 DDRB  = 0x00;
 PORTC = 0x00; //m103 output only
 DDRC  = 0x00;
 PORTD = 0x00;
 DDRD  = 0x00;
 
 digital_port_init();
 
 key_init();
 
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
 timer2_init();
 timer0_init();
 //adc_init();
 uart0_init();
 
 MCUCSR |= 1 << JTD; //��ֹJTAG�ӿ�
 MCUCSR |= 1 << JTD; //��Ҫ�������β������ܱ���Чִ��

 MCUCR = 0x00;
 GICR  = 0xC0;
 //TIMSK |= 0xc0; //timer2 
 //TIMSK |= 0x03; //timer0 interrupt sources
 TIMSK = 0xC3;
 _SEI(); //re-enable interrupts
 //all peripherals are now initialized
}

#ifdef use_freertos

TaskHandle_t xhandle = (void *)0;
TaskHandle_t xhandle1 = (void *)0;
TaskHandle_t xhandle_tasklist = (void *)0;

void thread_func()
{
    while (1)
    {
        digital_show_one_num(7, 8);
        HAL_SleepMs(30);
    }
}

void thread_func1()
{
    uint8_t temp = malloc(8);
    temp = 100;
    while (1)
    {
        digital_show_one_num(2, 7);
        HAL_SleepMs(30);
        temp--;
        if (temp < 0)
        break;
    }
}

void thread_func_tasklist()
{
    char *buffer = NULL;
    buffer = pvPortMalloc(512);

    while (1)
    {
        vTaskList((char *) buffer);
        usart_transmit_str("任务名      任务状态 优先级   剩余栈 任务序号\r\n");
        usart_transmit_str("\r\n%s\r\n", buffer);
        vPortFree(buffer);
    }
}

#endif

int main()
{
  int ret = 1;
  init_devices();
  digital_show_one_num(1,1);

  //printf("%d", temp);
  //num = start_adc();
 //RTEEPROMwrite(0X01,1);
 //num = RTEEPROMread(0x01);
 #ifdef use_freertos
  ThreadParams ThreadParam;
  ThreadParam.thread_name = "123";
  ThreadParam.priority    = 4;
  ThreadParam.user_arg    = NULL;
  ThreadParam.stack_size  = 50;
  ThreadParam.thread_id = xhandle;
  ThreadParam.thread_func = thread_func;
  ret = HAL_ThreadCreate(&ThreadParam);

  ThreadParam.thread_name = "456";
  ThreadParam.priority    = 4;
  ThreadParam.user_arg    = NULL;
  ThreadParam.stack_size  = 50;
  ThreadParam.thread_id = xhandle1;
  ThreadParam.thread_func = thread_func1;
  ret = HAL_ThreadCreate(&ThreadParam);

  ThreadParam.thread_name = "tasklist";
  ThreadParam.priority    = 4;
  ThreadParam.user_arg    = NULL;
  ThreadParam.stack_size  = 1024;
  ThreadParam.thread_id   = xhandle_tasklist;
  ThreadParam.thread_func = thread_func1;
  ret = HAL_ThreadCreate(&ThreadParam);
  HAL_Thread_Scheduler();
#endif
  //主程序不能结束，否则定时器停止，外部中断也是
  //main fuction caan not stop , or the system will stop
  //usart_transmit_str("33333333333333");
      //myprintf("%d", 12);
  while (1)
  {
    //myprintf("22222");
    usart_transmit_str("4444444444444");
  }
  

  return 0;
}