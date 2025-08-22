#include "infraredsensor.h"
#include "stm32f10x.h"
#include "systick_time.h"

void infrared_init(void)
{
	// PA0->PA4
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
	GPIOA->CRL&=~(0xF<<0)&~(0xF<<4)&~(0xF<<8)&~(0xF<<12)&~(0xF<<16);
	GPIOA->CRL|=(8<<0)|(8<<4)|(8<<8)|(8<<12)|(8<<16);
	GPIOA->ODR|=(1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4);
}
int read_sensor1(void)
{
	return (GPIOA->IDR&(1<<4))>>4;
}
int read_sensor2(void)
{
	return (GPIOA->IDR&(1<<3))>>3;
}
int read_sensor3(void)
{
	return (GPIOA->IDR&(1<<0))>>0;
}
int read_sensor4(void)
{
	return (GPIOA->IDR&(1<<1))>>1;
}
int read_sensor5(void)
{
	return (GPIOA->IDR&(1<<2))>>2;
}
int debounce(int sensor)
{
	if (!(GPIOA->IDR&(1<<sensor)))
	{
		DelayMs(50);
		if (!(GPIOA->IDR&(1<<sensor))) return 1;
	}
	return 0;
}
