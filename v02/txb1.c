#define F_CPU 1000000UL
#include <avr/io.h>
#include <string.h>
#include <util/delay.h>


int init(void){
	DDRC=0xff;
	PORTC=(1<<PC5); // USING PC5 for just blinking. will use PC4 for tx signal.
	return 0;
}

int sendseq(void){
	PORTC|=(1<<PC4)|(1<<PC5);
	_delay_ms(5000);
	PORTC&=~((1<<PC4)|(1<<PC5));
	_delay_ms(1000);
	return 0;
}

int main(void){
	init();
	while(1){
		sendseq();
		}
}
	


