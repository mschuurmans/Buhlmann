#include "gas.h"

int gas_init(struct GAS *gas, double oxygen)
{
	if (gas) {
		gas->o2 = oxygen;
		gas->n2 = 100 - oxygen;

		if ((gas->o2 + gas->n2 - 100) != 0)
			return -1;

		return 0;
	}

	return -1;
}
