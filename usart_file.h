/*
 * usart_file.h
 *
 * Created: 02-Dec-20 9:49:13 AM
 *  Author: Riya
 */ 


#ifndef USART_FILE_H_
#define USART_FILE_H_

void usart_init(unsigned int baud)
{
	//Only Works For the clock frequency 8Mhz with U2X=0 as of now
	unsigned int UBR_val;
	UCSRB |= (1<<RXEN)|(1<<TXEN);
	UCSRC |= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	UBR_val = (500000/baud) - 1;
	UBRRL = UBR_val;  // Only lower 8 bits will be stored remaining upper 4 bits will be neglected. If there is any upper 4 bits (only in case of 1200)
	UBRRH = (UBR_val>>8); //lower 8 bits will be flushed due to shift. Only upper 8 bits remain. and will be stored in UBRRH (only in case of 1200)
	
	
}
void usart_send_char(unsigned char ch)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR = ch;
}
void usart_send_str(unsigned char *str)
{
	while(*str!='\0')
	{
		while(!(UCSRA & (1<<UDRE)));
		UDR = *str;
		str++;
	}
}

unsigned char usart_receive()
{
	while(!(UCSRA & (1<<RXC)));
	return UDR;
}

unsigned char usart_receive_string()
{
	unsigned char i=0;
	char str[13];
	for(i=0;i<13;i++)
	{
		str[i] = usart_receive();				// this will take in 12 digit RFID number
	}
	return *str;
}

#endif /* USART_FILE_H_ */
