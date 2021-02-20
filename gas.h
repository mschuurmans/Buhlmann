#ifndef __GAS_H_
#define __GAS_H_

struct GAS {
	double o2;
	double n2;
};

int gas_init(struct GAS *, double);

#endif
