#ifndef __DECOMPRESSION_H_
#define __DECOMPRESSION_H_

#include "gas.h"

struct decompression_operations {
	int (*dive)(double pressure);
	int (*set_gas)(struct GAS *);
	int (*init)();
};

int decompression_register(struct decompression_operations *ops);
int decompression_dive(double pressure);
int decompression_set_gas(struct GAS *);

#endif
