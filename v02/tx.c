#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"

#define RFPORT PORTC
#define RFPIN PC5
#define BITPERIOD 9 // in ms unit

static char data='a';
static int data_send_bit=0;
static int count=0;

int init(void){
	DDRC=0xff;
	PORTC=0;
	
	TCCR0A=(1<<WGM01);
	TCCR0B=(1<<CS01)|(1<<CS00);
	TCNT0=0;
	OCR0A=15;
	TIMSK0=(1<<OCIE0A);
	sei();

	return 0;
}

void send_on(void){
	RFPORT|=(1<<RFPIN);
	
}

void send_off(void){
	RFPORT&=~(1<<RFPIN);
}

ISR(TIMER0_COMPA_vect){ // approx 2ms period.
	if(count%10==0){
		if(data_send_bit>7){
			data_send_bit=0;
		}

		if(data&(1<<(7-data_send_bit))){
			send_on();
		}
		else{
			send_off();
		}

		data_send_bit++;
		count=0;
	}
	count++;
}

int main(void){

	init();
	while(1){
	}

	return 0;
}

