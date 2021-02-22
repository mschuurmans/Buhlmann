#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "log.h"
#include "gas.h"
#include "decompression.h"
#include "timer.h"
#include "zhl16.h"

void main_tick(int);

int main(int argc, char** argv)
{
	log_info("Starting buhlman");

	struct gas gas;

	gas_init(&gas, 21, 35);

	log_info("Set gas to %f", gas.o2);

	zhl16_init();
	decompression_set_gas(&gas);

	timer_start(main_tick);

	for (;;) {
		sleep(10);
	}

	return 0;	
}

void main_tick(int sig)
{
	decompression_dive(time(NULL));
	zhl16_print();
}
