#include "stm32f10x.h"
#include "timer.h"

void timer_init(void)
{
	RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;
	TIM2->PSC=1;
	TIM2->ARR = 35999;
	TIM2->DIER|=(1<<0);
	NVIC->ISER[0]|=(1<<28);
}
void timer_enabled(void)
{
	TIM2->CR1|=(1<<0);
}
void timer_disabled(void)
{
	TIM2->CR1&=~(1<<0);
}
