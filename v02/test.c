#define F_CPU 1000000UL

#include <avr/io.h>
#include "uart.h"
#include <util/delay.h>

int main(void){
	uartinit(12);
	DDRC=0xff;
	PORTC=(1<<PC4);
	while(1){
		tx_char('a');
		PORTC^=(1<<PC4);
		_delay_ms(1000);
	}

}
