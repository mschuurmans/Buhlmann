#include <stddef.h>
#include <errno.h>

#include "decompression.h"
#include "gas.h"
#include "log.h"

struct decompression_operations *decompression_operations = NULL;

int decompression_register(struct decompression_operations *ops)
{
	if (!ops || decompression_operations)
		return -EINVAL;

	decompression_operations = ops;

	log_trace("Decompression operations has been set.");

	return 0;
}

int decompression_dive(long cur_time)
{
	return decompression_operations->dive(cur_time);
}

int decompression_set_gas(struct gas *gas)
{
	return decompression_operations->set_gas(gas);
}
