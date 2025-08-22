#include "stm32f10x.h"
#include "buzzer.h"

void buzzer_init(void)
{
	// PA6
	RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
	GPIOA->CRL&=~(0xF<<24);
	GPIOA->CRL|=(1<<24);
}
void buzzer_enabled(void)
{
	GPIOA->ODR|=(1<<6);
}
void buzzer_disabled(void)
{
	GPIOA->ODR&=~(1<<6);
}
