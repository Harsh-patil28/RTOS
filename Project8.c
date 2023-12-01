#include<lpc21xx.h>
#include<rtl.h>
#include<stdio.h>
void sev(void);
void lcd(void);
void cmd(unsigned int);
void data(unsigned int);
void delay(unsigned int);
void delay1(void);
void init_serial(void);
unsigned int counter1,i;
char arr1[20];
unsigned int disp[16]={0x003F0000,0x00060000,0x005B0000,0x004F0000,0x00660000,0x006D0000,0x007D0000,0x00070000,0x007F0000,0x006F0000};
__task void job1(void);
__task void job2(void);
__task void job1(void)
{
os_tsk_create(job2,0);
while(1)
{
sev();
}
}
__task void job2(void)
{
IODIR0=0x000F0000;                  
while(1)
{
IOCLR0=0x000F0000;                //Leds ON
for(i=0;i<100000;i++);
for(i=0;i<100000;i++);
IOSET0=0x000F0000;                //Leds OFF
for(i=0;i<100000;i++);
for(i=0;i<100000;i++);
}
}
void delay1(void)
{
unsigned long int j;
for(j=0;j<650000;j++);
}
void sev(void)
{
IODIR0=0xF0FF0000;                //making Po.16 to Po.23 and Po.28 to Po.31 output line
IOSET0=0XF0000000;
for(i=0;i<10;i++)
{
IOSET0 |=disp[i];
delay1();
delay1();
IOCLR0=0X00FF0000;
}
}
int main(void)
{
os_sys_init(job1);
while(1);
}
