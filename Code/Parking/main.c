#include "main.h"

char str1[20],str2[20];
int count=0;
int parking_slots[3];
int total_slots = 3;
int available_slots = 3;
char S1='E',S2='E',S3='E';

int main(void)
{
	systick_init();
	infrared_init();
	servo_start();
	xetgoc1(0);
	
	timer_init();
	buzzer_init();
	lcd_i2c_init();
	
	lcd_i2c_msg(1,1," Smart Parking");
	lcd_i2c_msg(2,2,"KS-IOT & VTN");
	//while(1);
	DelayMs(2000);
	lcd_clear_line2();
	lcd_i2c_msg(2,8,"3");
	DelayMs(1000);
	lcd_i2c_msg(2,8,"2");
	DelayMs(1000);
	lcd_i2c_msg(2,8,"1");
	DelayMs(1000);
	lcd_i2c_msg(2,8,"0");
	DelayMs(50);
	lcd_clear_line2();
	lcd_i2c_msg(2,6,"Start");
	DelayMs(500);
	
	lcd_clear();
	sprintf(str1,"S1:%c  S2:%c  S3:%c",S1,S2,S3);
	lcd_i2c_msg(1,0,str1);
	sprintf(str2, "Free slots:%d", available_slots);
	lcd_i2c_msg(2,2,str2);
		while(1)
	{
		// Check xe vao	
		if (debounce(4)&& available_slots >0)
		{
			xetgoc1(100);
			lcd_clear_line2();
			lcd_i2c_msg(2,3,"Gate open");
			DelayMs(500);
			while(!debounce(3));
			lcd_clear_line2();
			timer_enabled();
			lcd_i2c_msg(2,2,"Car entered");
			DelayMs(1000);
			xetgoc1(0);
			DelayMs(1000);
			available_slots--;
			lcd_clear_line2();
			sprintf(str2, "Free slots:%d", available_slots);
			lcd_i2c_msg(2,2,str2);
			while(debounce(3));
		}
		else if (debounce(4)&& available_slots==0)
		{
			lcd_clear_line2();
			while(1)
			{
				lcd_i2c_msg(2,2, "Parking full");
				buzzer_enabled();
				DelayMs(300);
				buzzer_disabled();
				DelayMs(100);
				if (!debounce(4)) 
				{
					lcd_clear_line2();
					sprintf(str2, "Free slots:%d", available_slots);
					lcd_i2c_msg(2,2,str2);
					break;
				}
			}
		}
		
		// Check xe ra
		if (debounce(3) && available_slots < total_slots)
		{
			xetgoc1(100);
			lcd_clear_line2();
			lcd_i2c_msg(2,3,"Gate open");
			DelayMs(500);
			while(!debounce(4));
			lcd_clear_line2();
			timer_enabled();
			lcd_i2c_msg(2,3,"Car exited");
			DelayMs(1000);
			xetgoc1(0);
			DelayMs(1000);
			available_slots++;
			lcd_clear_line2();
			sprintf(str2, "Free slots:%d", available_slots);
			lcd_i2c_msg(2,2,str2);
			while(debounce(4));
		}
		
		S1 = (debounce(0))? 'O':'E';
		S2 = (debounce(1))? 'O':'E';
		S3 = (debounce(2))? 'O':'E';
		sprintf(str1,"S1:%c  S2:%c  S3:%c",S1,S2,S3);
		lcd_i2c_msg(1,0,str1);
		
	}
}
void TIM2_IRQHandler(void)
{
	TIM2->SR&=~(1<<0);
	if (count>=500)
	{
		count=0;
		buzzer_disabled();	
		timer_disabled();
	}
	else
	{
		count++;
		buzzer_enabled();
	}
}