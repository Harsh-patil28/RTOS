#include<rtl.h>
#include<lpc21xx.h>
__task void job1(void);
__task void job2(void);
unsigned char count;
unsigned char count1;
int main(void)
{
	os_sys_init(job1);
	while(1);
}
__task void job1(void)
{
	os_tsk_create(job2,2);
	while(1)
	{
		count++ ;
	}
}
__task void job2(void)
{
	while(1)
	{
		count1++ ;
	}
}
