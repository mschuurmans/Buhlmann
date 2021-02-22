#ifndef __GAS_H_
#define __GAS_H_

struct gas {
	double o2;
	double n2;
};

int gas_init(struct gas *, double);

#endif
