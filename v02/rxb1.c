#define F_CPU 1000000UL
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SAMPLESIZE 4

int init(void){
	DDRC=0xff;
	PORTC=0;
	DDRB=0; // USE B PINS FOR READING INPUT
	return 0;
}


int polling(void){
	int threshold=0.5;
	int sample[SAMPLESIZE];
	int i;
	for(i=0;i<SAMPLESIZE;i++){
		if(PINB&(1<<PB0)){
			sample[i]=1;
		}
		else{
			sample[i]=0;
		}
		_delay_ms(5);
	}

	int sum=0;
	for(i=0;i<SAMPLESIZE;i++){
		sum+=sample[i];
	}

	if(sum>(SAMPLESIZE*threshold)){
		return 1;
	}
	else{
		return 0;
	}
}

int rxcheck(void){
	int pollcheck=polling();
	if(pollcheck==1){
		PORTC=(1<<PC3);
	}
	else{
		PORTC=0;
	}

	return 0;
}


int main(void){
	init();
	while(1){
		rxcheck();
		}

}
	


