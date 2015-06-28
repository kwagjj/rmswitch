#define F_CPU 1000000UL
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"

#define SAMPLE_PER_BIT 10
#define START_CHAR 'a'
#define ACT_WAIT_PERIOD 3000	// in ms unit

static int current_sample_num=0;
static char inputbuffer=NULL;
static int sampling_sum=0;
static int returnbit=0;	// decided bit value after sampling for one bit
static int start_rx=0;	// set to 1, start receiving bytes
static int cd_ib=0;	// countdown of inputbuffer
static char input[3];	// will save three serial chars after start byte('a')
static uint8_t input_count=0; // used for counting input[] insertions.
static uint8_t wait_activate=0; // set to 1 when in phase of countdowning for activation
static int activate_cd=ACT_WAIT_PERIOD; // activate countdown. used for delaying any further rx for preset duration.


int init(void){
	DDRC=0xff;
	PORTC=0;
	DDRB=0; // USE B PINS FOR READING INPUT

	uartinit(12);

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
		if(sampling_sum>(SAMPLE_PER_BIT/2)){
			returnbit=1;
		}
		else{
			returnbit=0;
		}

	}

	current_sample_num++;
	if(wait_activate==1){
		if(activate_cd<=0){

			wait_activate=0;
			activate_cd=ACT_WAIT_PERIOD;
		}
		activate_cd--;
	}
	
}

int bitprocess(void){
	if(returnbit>1){ // when bit has already been processed. return right away to avoid redundant processing.
		return 1;
	}
	
	inputbuffer=inputbuffer<<1;
	inputbuffer|=returnbit;

	returnbit=2; // make it not 0 or 1. any value higher than 1.
	if(start_rx==1){
		cd_ib++;
	}

	return 0; // return 0 when has processed a bit properly


}

int inputbuffer_check(void){
	if(inputbuffer=='a'){
		start_rx=1;
}
	return 0;
}

void activate(void){
	PORTC^=(1<<PC3);
	wait_activate=1;
}

int evaluate(void){
	int i;
	for(i=0;i<3;i++){
		if(!(input[i]=='a')){
			return 1;
		}
	}

	activate();
	return 0;
}


int main(void){
	_delay_ms(1000);
	init();
	while(1){	
			if(!bitprocess()){
				if(start_rx==0){
					if(!wait_activate){	// when wait_activate=0, then do inputbuffer check
						inputbuffer_check();
					}
				}
				else{
					if(cd_ib==8){
						tx_char(inputbuffer);
						input[input_count]=inputbuffer;
						// tx_char(inputbuffer);
						input_count++;	
						if(input_count>2){
							evaluate();
							input_count=0;
							start_rx=0; // stop proper rx
						}

					
						cd_ib=0;
					}
				}
				// check buffer once. 
			}
		}

	return 0;

}
	


