#include<rtl.h>
#include<lpc21xx.h>
__task void job1(void);
unsigned char count;
int main(void)
{
	os_sys_init(job1);
	while(1);
}
__task void job1(void)
{
	while(1)
	{
		count++ ;
	}
}
