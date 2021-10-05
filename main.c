/*
 * 18ec020_PROJECT_FINAL.c 
 *
 * Created: 30-09-2020 16:12:50
 * Author : Riya
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include "usart_file.h"
#include "lcd_file.h"


//defining pin number on ports
#define rs 0
//RW will be permanently grounded
#define en 1
#define buzzer 2

//data pins for LCD
#define pin0 4
#define pin1 5
#define pin2 6
#define pin3 7

int count1=0, count2=0, count3=0;
char result[10];
char rx_data[50],rfid[13],ch=0;
unsigned int i;

int main()
{
	DDRB |= (1<<rs)|(1<<en)|(1<<buzzer);
	DDRC &= ~((1<<pin0)|(1<<pin1)|(1<<pin2)|(1<<pin3));
	PORTB |= (1<<buzzer);
	
	usart_init(9600);					//usart initialize
	lcd_init();							//LCD initialize
	
	lcdstring("  RFID Based    ");
	lcdcmd(0xC0);						//Second Row
	lcdstring("Attendance System");
	_delay_ms(500);
	
	while(1)
	{
		lcdcmd(0x01);					//clear display
		lcdstring("Place Your Card:");
		lcdcmd(0xC0);					// cursor to second row
		i=0;
		
		for(i=0;i<12;i++)
		rfid[i] = usart_receive();				// this will take in 12 digit RFID number
		rfid[i]='\0';					// after the last iteration i will be 13 and we will push null character
		lcdcmd(0x01);					//clear display
		
		lcdstring("Your ID No. is:");
		lcdcmd(0xC0);					// cursor to second row
		
		for(i=0;i<12;i++)				// Loop will send individual characters of RFID number to LCD data
		lcddata(rfid[i]);
		_delay_ms(500);
		
		if(strncmp(rfid,"160066A5EC39",12)==0)			//Predefined ID number
		{
			count1++;
			lcdcmd(0x01);
			lcdstring(" Attendance ");
			lcdcmd(0xC0);
			lcdstring(" Registered");
			_delay_ms(2000);
			lcdcmd(0x01);
			lcdstring(" Student1 ");
			lcdcmd(0xC0);
			lcdstring("Attnd. No.: ");
			//sprintf(result, "%d", count1);
			itoa(count1,result,10);
			lcdstring(result);
			_delay_ms(2000);
		}
		
		else if(strncmp(rfid,"160066BD7AB7",12)==0)
		{
			count2++;
			lcdcmd(0x01);
			lcdstring(" Attendance ");
			lcdcmd(0xC0);
			lcdstring(" Registered");
			_delay_ms(2000);
			lcdcmd(0x01);
			lcdstring(" Student2 ");
			lcdcmd(0xC0);
			lcdstring("Attnd. No.: ");
			//sprintf(result, "%d", count2);
			itoa(count2,result,10);
			lcdstring(result);
			_delay_ms(2000);
		}
		
		else if(strncmp(rfid,"160066203060",12)==0)
		{
			count3++;
			lcdcmd(0x01);
			lcdstring(" Attendance ");
			lcdcmd(0xC0);
			lcdstring(" Registered");
			_delay_ms(2000);
			lcdcmd(0x01);
			lcdstring(" Student3 ");
			lcdcmd(0xC0);
			lcdstring("Attnd. No.: ");
			//sprintf(result, "%d", count3);
			itoa(count3,result,10);
			lcdstring(result);
			_delay_ms(2000);
		}

		else
		{
			lcdcmd(0x01);
			lcdstring("Invalid Card");
			PORTB &= ~(1<<buzzer);
			_delay_ms(500);
			PORTB |= (1<<buzzer);
		}
	}
}







