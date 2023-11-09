#include<rtl.h>
#include<lpc21xx.h>
__task void job1(void);
__task void job2(void);
__task void job3(void);
unsigned char count;
unsigned char count1;
unsigned char count2;
int main(void)
{
	os_sys_init(job1);
	while(1);
}
__task void job1(void)
{
	os_tsk_create(job2,3);
	while(1)
	{
		count++ ;
	}
}
__task void job2(void)
{
	os_tsk_create(job3,4);
	while(1)
	{
		count1++ ;
	}
}
__task void job3(void)
{
	while(1)
	{
		count2++ ;
		os_tsk_prio_self(2);
	}
}
