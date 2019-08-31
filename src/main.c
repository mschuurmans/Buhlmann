#include <stdio.h>
#include "zhl16.h"
#include "timer.h"
#include <unistd.h>

int main(int argc, char** argv) 
{
	zhl16_init();
	zhl16_print_tissue_state();

	timer_start(timer_callback);
	for(;;) {
		sleep(10);	
	}
}


