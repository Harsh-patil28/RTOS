#include<rtl.h>
#include<lpc21xx.h>
#include<stdio.h>
__task void task2(void);
void init_serial(void);          //initialize serial interface

unsigned char msg1[]="hello from task1\r\n", msg2[]=" hello from task2\n";
unsigned int j,i=0;
OS_TID tsk1,tsk2;
OS_SEM semaphore1;

// Task 1 High priority - Active every 3 ticks

__task void task1(void)
{
	OS_RESULT ret;
	os_tsk_prio_self(2);
	tsk2 = os_tsk_create(task2,1);
	while(1)
	{
		os_dly_wait(3);
		ret = os_sem_wait(semaphore1, 0x01);
		if(ret == OS_R_SEM)
		{
			while(msg1[i] != '\0')
			{
				while(!(U0LSR & 0x02));
                                        U0THR = msg1[i];i++;
			}
			i = 0;
			os_sem_send(semaphore1);
		}
	}
}

//Task 2 - Low Priority 

__task void task2(void)
{
	while(1)
	{
		os_sem_wait(semaphore1, 0x01);
		while(msg2[i] !='\0')
		{
			while(!(U0LSR & 0x20));
			U0THR = msg2[i];
			i++;
		}
		i = 0;
		os_sem_send(semaphore1);
	}
}

// init serial

void init_serial (void)
{
	PINSEL0 = 0x0000005;
	U0LCR = 0x083;
	U0DLL = 0x61;
	U0LCR = 0x03;
}

//Main

int main(void)
{
	init_serial();
	os_sem_init(semaphore1,1);
	os_sys_init(task1);
}
