#include "log.h"
#include "gas.h"

int main(int argc, char** argv)
{
	log_info("Starting buhlman");

	struct GAS gas;

	gas_init(&gas, 21);

	log_info("Set gas to %f", gas.o2);

	return 0;	
}
