#include "gas.h"

int gas_init(struct gas *gas, float oxygen, float helium)
{
	if (gas) {
		gas->o2 = oxygen;
		gas->n2 = 100 - oxygen;
		gas->he = helium;

		if ((gas->o2 + gas->n2 + gas->he - 100) != 0)
			return -1;

		return 0;
	}

	return -1;
}
