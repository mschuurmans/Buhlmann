#include "decompression.h"
#include "zhl16.h"
#include "log.h"

int zhl16_dive(double pressure)
{
	log_debug("Dive");
	return 0;
}

int zhl16_set_gas(struct GAS *gas)
{
	log_debug("Updating gas");

	return 0;
}

struct decompression_operations zhl_ops = {
	.dive = &zhl16_dive,
	.set_gas = &zhl16_set_gas
};


int zhl16_init()
{
	log_info("Initializing zhl16 algorithm");

	decompression_register(&zhl_ops);

	return 0;
}
