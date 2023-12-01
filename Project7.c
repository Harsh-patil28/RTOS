#include<rtl.h>
#include<lpc21xx.h>
#include<stdio.h>
OS_TID tsk1,tsk2;
int  cnt1,cnt2,i;
__task void job1(void);
__task void job2(void);

__task void job1(void)
{
	IODIR0 = 0x000F0000;
	os_tsk_prio_self(1);
	tsk2 = os_tsk_create(job2,0);
	while(1)
	{
		for(i=0; i<1000000;i++)
		{
			IOSET0 = 0x000F0000;
		}
		os_tsk_prio(tsk2,2);
	}
}

__task void job2(void)
{
	IODIR0 = 0x000F0000;
	while(1)
	{
	IOCLR0 = 0x000F0000;	
	for(i=0 ; i<1000000; i++);
	IOSET0 = 0x000F0000;
	for(i=0 ; i<1000000; i++);
	}		
}

int main(void)
{
	cnt1 = 0;
	cnt2 = 0;
	os_sys_init(job1);
	while(1);
}
