#include "i2c.h"
#include "pcf8574.h"
#include "systick_time.h"
#include "lcd-i2c.h"

// I2c adjust 4 wire data tx
void lcd_i2c_data(unsigned char data)
{
	PCF8574_tx_byte(0x09);
	DelayUs(10);
	PCF8574_tx_byte(0x0D);
	DelayUs(5);
	PCF8574_tx_byte(((data & 0x00f0) | 0x0D));
	DelayUs(10);
	PCF8574_tx_byte(((data & 0x00f0) | 0x09));
	
	DelayUs(20);
	
	PCF8574_tx_byte(0x0D);
	DelayUs(5);
	PCF8574_tx_byte((((data << 4) & 0x00f0) | 0x0D));
	DelayUs(10);
	PCF8574_tx_byte((((data << 4) & 0x00f0) | 0x09));
}

void lcd_i2c_cmd(unsigned char data)
{
	PCF8574_tx_byte(0x08);
	DelayUs(10);
	PCF8574_tx_byte(0x0C);
	DelayUs(5);
	PCF8574_tx_byte(((data & 0x00f0) | 0x0C));
	DelayUs(10);
	PCF8574_tx_byte(((data & 0x00f0) | 0x08));
	DelayUs(20);
	PCF8574_tx_byte(0x0C);
	DelayUs(5);
	PCF8574_tx_byte((((data << 4) & 0x00f0) | 0x0C));
	DelayUs(10);
	PCF8574_tx_byte((((data << 4) & 0x00f0) | 0x08));
}

void lcd_i2c_init()
{
  i2c_init();
	DelayMs(20);
	PCF8574_tx_byte(0x08);
	DelayUs(10);
	PCF8574_tx_byte(0x0C);
	DelayUs(5);
	PCF8574_tx_byte(0x3C);
	DelayUs(10);

	PCF8574_tx_byte(0x38);
	
	DelayMs(10);
	

	PCF8574_tx_byte(0x08);
	DelayUs(10);
	PCF8574_tx_byte(0x0C);
	DelayUs(5);
	PCF8574_tx_byte(0x3C);
	DelayUs(10);
	PCF8574_tx_byte(0x38);
	
	DelayMs(1);

	PCF8574_tx_byte(0x08);
	DelayUs(10);
	PCF8574_tx_byte(0x0C);
	DelayUs(5); 
	PCF8574_tx_byte(0x3C);
	DelayUs(10);
	PCF8574_tx_byte(0x38);
	
	DelayMs(1);
	PCF8574_tx_byte(0x08);
	DelayUs(10);
	PCF8574_tx_byte(0x0C);
	DelayUs(5);
	PCF8574_tx_byte(0x2C);
	DelayUs(10);
	PCF8574_tx_byte(0x28);

	lcd_i2c_cmd(0x2C); // 4 bit communication mode / 2 lines
	DelayMs(5);
	lcd_i2c_cmd(0x0C); // Display ON
	DelayMs(5);
	lcd_i2c_cmd(0x01); // Clear Display
	DelayMs(5);
	lcd_i2c_cmd(0x02); // Get back to initial address
	DelayMs(5);
}
void lcd_i2c_send(char str[])
{
	int i = 0;
		while(str[i])
		{
			lcd_i2c_data(str[i]);
			i++;
			DelayUs(100);
		}
}
void lcd_i2c_msg(unsigned char line_1_2, unsigned char pos_0_16, char msg[])
{
	short pos = 0;
	if(line_1_2==1)
	{
		pos = 0;
	}
	else if(line_1_2==2)
	{
		pos = 0x40;
	}
	lcd_i2c_cmd(0x80 +pos + pos_0_16);
	DelayUs(100);
	lcd_i2c_send(msg);
}
// Hàm xóa màn hình
void lcd_clear(void) 
{
    lcd_i2c_cmd(0x01); // Clear Display
    DelayMs(2);
}
void lcd_clear_line1(void)
{
	lcd_i2c_cmd(0x80); 
	DelayMs(2);
	lcd_i2c_msg(1,0,"                "); 
}
void lcd_clear_line2(void)
{
	lcd_i2c_cmd(0xC0); 
	DelayMs(2);
	lcd_i2c_msg(2,0,"                "); 
}
