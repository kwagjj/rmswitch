
void uartinit(unsigned int baud)
{
	
	UBRR0H=(unsigned char) (baud>>8);
	UBRR0L=(unsigned char) baud;

	UCSR0C=(0<<USBS0) | (1<<UCSZ01) | (1<<UCSZ00);

	UCSR0B=(1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02) | (1<<RXCIE0);
}

void tx_char(unsigned char data)
{
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0=data;
}

void tx_str(char *str)
{
	int i=0;
	while(str[i]!='\0')
	{
		tx_char(str[i]);
		i++;
	}
}


unsigned char rx_char(void) //modified to repeat its input to PC.
{
	unsigned char result;
	while( (UCSR0A & (1<<RXC0))==0);
	result=UDR0;
	if(result=='\r'){
		tx_char('\n');
	}
	else{
		tx_char(result);
	}
	
	return result;
}

void rx_str(char *str)
{
	int i=0;
	for(i=0;i<100;i++)
	{
		str[i]=rx_char();
		if(str[i]=='\r'){ // for my laptop, use \r instead of \n. perhaps putty dependent?
			str[i]='\0';
			break;
		}
	}

}

