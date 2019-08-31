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

	if (gas_init(&gas, 21, 35)) {
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

	zhl16_dive(2.25, 60);

	//printf("NDL: %f seconds minutes: %f\n", zhl16_get_ndl(3), zhl16_get_ndl(3) / 60);
	zhl16_get_ndl(3);
}
