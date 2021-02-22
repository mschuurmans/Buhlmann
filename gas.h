#ifndef __GAS_H_
#define __GAS_H_

struct gas {
	float o2;
	float n2;
	float he;
};

int gas_init(struct gas *, float, float);

#endif
