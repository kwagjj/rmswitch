#include <stdio.h>

#define clk 1000000

int main(void){

	float prescaler,period;
	printf("prescaler: ");
	scanf("%f",&prescaler);
	printf("wanted period(ms):");
	scanf("%f",&period);

	float ocvalue;
	ocvalue=(clk/prescaler)*period/1000;

	printf("ocvalue: %.2f\n",ocvalue);

	return 0;	
}
