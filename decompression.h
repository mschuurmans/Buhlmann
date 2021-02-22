#ifndef __DECOMPRESSION_H_
#define __DECOMPRESSION_H_

#include "gas.h"

struct decompression_operations {
	int (*dive)(long cur_time);
	int (*set_gas)(struct gas *);
	int (*init)();
};

int decompression_register(struct decompression_operations *ops);
int decompression_dive(long cur_time);
int decompression_set_gas(struct gas *);

#endif
