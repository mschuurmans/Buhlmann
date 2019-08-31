#include <stdio.h>
#include "zhl16.h"
#include "timer.h"
#include <unistd.h>
#include <stdlib.h>
#include "gas.h"

void main_tick(int);

int main(int argc, char** argv) 
{
	struct GAS gas;

	if (gas_init(&gas, 5, 35)) {
		printf("Gas is incorrect!\n");
		exit(1);
	}

	zhl16_init(&gas);
	zhl16_print_tissue_state();

	timer_start(main_tick);

	for(;;) {
		sleep(10);	
	}
}

void main_tick(int sig)
{
	// zhl dive...
	printf("Registering dive point\n");

	int i;
	for (i = 0; i < 60; i++ ) {
		zhl16_dive(3, 1);
	}

	printf("NDL: %f seconds is minutes: %f\n", zhl16_get_ndl(3), zhl16_get_ndl(3) / 60);
}
