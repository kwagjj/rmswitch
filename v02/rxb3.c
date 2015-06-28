#define F_CPU 1000000UL
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"

#define SAMPLE_PER_BIT 10
#define START_CHAR 'a'

static int current_sample_num=0;
static char inputbuffer=NULL;
static int sampling_sum=0;

int init(void){
	DDRC=0xff;
	PORTC=0;
	DDRB=0; // USE B PINS FOR READING INPUT

	TCCR0A=(1<<WGM01);
	TCCR0B=(1<<CS01)|(1<<CS00);
	TCNT0=0;
	OCR0A=15;
	TIMSK0=(1<<OCIE0A);
	sei();
	return 0;
}


ISR(TIMER0_COMPA_vect){ // every 1ms approx.

	if(current_sample_num>=SAMPLE_PER_BIT){
		current_sample_num=0;
		sampling_sum=0;
	}
	if(current_sample_num<SAMPLE_PER_BIT){
		if(PINB&(1<<PB0)){
			sampling_sum++;
		}
	}

	if(current_sample_num==SAMPLE_PER_BIT-1){ // need to evaluate bit samples and insert correct bit value to inputbuffer

		inputbuffer>>1;
		if(sampling_sum>(SAMPLE_PER_BIT/2)){
			inputbuffer|=0x80; // in binary: 0b1000 0000 so that msb is set to 1
		} // if not bigger than sample_per_bit/2, then it will remain 0;
	}

	current_sample_num++;


}



int inputbuffer_check(void){
	if(inputbuffer=='a'){
		PORTC^=(1<<PC4);
		_delay_ms(1000);
}


int main(void){
	init();
	while(1){
		
		inputbuffer_check()	
		}

}
	


