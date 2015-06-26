#define F_CPU 1000000UL
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>
#include <avr/interrupt.h>


int init(void){
	DDRC=0xff;
	PORTC=0;
	DDRB=0; // USE B PINS FOR READING INPUT
	return 0;
}

int rxcheck(void){
	if(PINB&(1<<PB0)){
		PORTC=(1<<PC5); // PC5 WILL BE LED BLINKING
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
	


