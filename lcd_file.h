/*
 * lcd_file.h
 *
 * Created: 02-Dec-20 10:39:13 AM
 *  Author: Riya
 */ 


#ifndef LCD_FILE_H_
#define LCD_FILE_H_
#define rs 0
//RW will be permanently grounded
#define en 1
void daten()
{
	PORTB |= (1<<rs);	//for data rs = 1
	PORTB |= (1<<en);	//RS = 1 WHICH MEANS WE ARE USING DATA REGISTER
	_delay_ms(10);
	PORTB &= ~(1<<en);
}


void lcddata(char ch)
{
	PORTC = ch & 0xf0;          //4 bit mod hence character is transmitted 4 bits at a time (Lower 4 bits)
	daten();
	PORTC = (ch<<4) & 0xf0;		//Higher 4 bits. Lower 4 bits is masked
	daten();
}


void cmden(void)
{
	PORTB &= ~(1<<rs);   //for command rs = 0
	PORTB |= (1<<en);	//RS = 1 WHICH MEANS WE ARE USING COMMAND REGISTER
	_delay_ms(10);
	PORTB &= ~(1<<en);
}


void lcdcmd(char ch)
{
	PORTC = ch & 0xf0;			//4 bit mod hence character is transmitted 4 bits at a time (Lower 4 bits)
	cmden();
	PORTC = (ch<<4) & 0xf0;		//Higher 4 bits. Lower 4 bits is masked
	cmden();
}


void lcdstring(char *str)
{
	while(*str)					//while *str is not null it will iterate
	{
		lcddata(*str);
		str++;
	}
}


void lcd_init(void)
{
	lcdcmd(0x02);	//return home
	lcdcmd(0x28);	//4bit mode
	lcdcmd(0x0E);	//visualize cursor
	lcdcmd(0x01);	//clear LCD
}



#endif /* LCD_FILE_H_ */