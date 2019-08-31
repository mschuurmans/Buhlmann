#include "gas.h"

int gas_init(struct GAS *gas, double o2, double he)
{
	if (gas) {
		gas->o2 = o2;
		gas->he = he;
		gas->n2 = 100 - o2 - he;

		return gas->o2 + gas->he + gas->n2 - 100;
	}

	return 0;
}

double gas_percent_to_partial(double percent)
{
	return (percent / 100);
}

double gas_get_partial_pressure(struct GAS *gas, double depth_in_bar)
{
	// 0.0627 is water vapor pressure in bar
	return gas_percent_to_partial(gas->n2) * (depth_in_bar - 0.0627);	
}
