#include "stm32f10x.h"
#include "servo.h"

void servo_init(void)
{
	// TIM4 - CH3 - PB8  // CH4 PB9;
	RCC->APB2ENR|=(1<<0)|(1<<3);
	GPIOB->CRH&=~(0xF<<0)&~(0xF<<4);
	GPIOB->CRH|=(9<<0)|(9<<4);
	RCC->APB1ENR|=(1<<2);
	TIM4->PSC=49;
	TIM4->ARR=28799;
	TIM4->CCR3 =720;
	TIM4->CCR4 =720;
	TIM4->CCMR2|=(6<<4)|(6<<12);
	TIM4->CCER|=(1<<8)|(1<<12);
}
void servo_enabled(void)
{
	TIM4->CR1|=(1<<0);
}
void servo_start(void)
{
	servo_init();
	servo_enabled();
}
void xetgoc1(int angle)
{
	TIM4->CCR3 = 720 + (angle * 16);
}
void xetgoc2(int angle)
{
	TIM4->CCR4 = 720 + (angle * 16);
}
