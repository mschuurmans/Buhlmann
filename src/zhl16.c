#include <stdio.h>
#include <math.h>

#include "zhl16.h"
#include "tissue.h"

struct TISSUE tissues[16];
struct GAS *current_gas;
double gradient_factor_low = 0.2;
double gradient_factor_high = 0.7;

void zhl16_update_tissue_loads(double, double, double);

void zhl16_set_current_gas(struct GAS *gas)
{
	current_gas = gas;
}

void zhl16_set_gradient_factors(double low, double high)
{
	gradient_factor_low = low / 100;
	gradient_factor_high = high / 100;
}

void zhl16_print_tissue_state(void)
{
	int i;
	for (i = 0; i < 16; i++) {
		printf("Tissue[%d]:\ta: %f, b: %f, k: %.17f, load: %f\n", i, tissues[i].a, tissues[i].b, tissues[i].k, tissues[i].load);
	}
}


// TODO Move somewhere else?
double previous_pressure = 0;

void zhl16_dive(double pressure, double delta)
{
	double r = (gas_get_partial_pressure(current_gas, pressure) - gas_get_partial_pressure(current_gas, previous_pressure)) / delta;

	zhl16_update_tissue_loads(gas_get_partial_pressure(current_gas, previous_pressure), r, delta);

	previous_pressure = pressure;
}

double zhl16_get_ptol(double ambient, double a, double b, double gf)
{
	return a * gf + ((ambient * (gf - gf * b + b)) / b);
}

double zhl16_haldane_time(double k, double ptol, double load, double partial)
{
	double logArg = (ptol - partial) / (load - partial);

	if (logArg < 0)
		printf("Logarg < 0 in haldane time\n");

	return -(1 / k) * log(logArg);
}

double zhl16_get_ndl(double pressure)
{
	double ndl = 5940; // is 99 minutes in seconds..

	int i;
	for (i = 0; i < 16; i++) {
		double ptol = zhl16_get_ptol(1, tissues[i].a, tissues[i].b, gradient_factor_high);

		// Only if compartment is under pTol otherwise ndl is -1 and others are irrelevant
		if (tissues[i].load < ptol) {
			//printf("Partial pressure: %f - ptol: %f - tissue load: %f\n", gas_get_partial_pressure(current_gas, pressure), ptol, tissues[i].load);
			if (ptol < gas_get_partial_pressure(current_gas, pressure)) { // if ptol can be reached

				double tmp = zhl16_haldane_time(tissues[i].k, ptol, tissues[i].load, gas_get_partial_pressure(current_gas, pressure));
				printf("NDL: %f - NDLI: %f\n", ndl, tmp);

				if (tmp < ndl) 
					ndl = tmp;
			}
		} else {
			ndl = -1;
			break;
		}
	}

	return ndl;
}

void zhl16_update_tissue_loads(double pressure, double r, double time)
{
	double k;
	double tmp;

	int i;
	for (i = 0; i < 16; i++) {
		k = tissues[i].k;
		tmp = tissues[i].load;

		tissue_set_load(&tissues[i], (pressure + r * (time - (1/k)) - (pressure-tmp - (r/k)) * exp(-k*time)));
	}
}

void zhl16_init(struct GAS *gas)
{
	printf("Initializing zhl16 tissues\n");
	zhl16_set_current_gas(gas);
	
	// TODO set initial load (based on current pressure and/or left over from previous dive?)
	tissue_init(&tissues[0], 1.1696,	0.5578, 0.00231049060186648, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[1], 1.0, 		0.6514, 0.00144405662616655, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[2], 0.8618, 	0.7222, 0.00092419624074659, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[3], 0.7562, 	0.7825, 0.00062445691942338, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[4], 0.62,		0.8124, 0.00042786862997528, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[5], 0.5043,	0.8434, 0.00030163062687552, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[6], 0.441,		0.8693, 0.00021275235744627, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[7], 0.4, 		0.891,	0.00015003185726406, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[8], 0.375, 	0.9092, 0.00010598580742507, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[9], 0.35, 		0.9222, 0.00007912639047488, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[10], 0.3295, 	0.9319, 0.00006177782357932, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[11], 0.3065, 	0.9403, 0.00004833662347001, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[12], 0.2835, 	0.9477, 0.00003787689511257, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[13], 0.261, 	0.9544, 0.00002962167438290, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[14], 0.248, 	0.9602, 0.00002319769680589, gas_get_partial_pressure(current_gas, 1));
	tissue_init(&tissues[15], 0.2327, 	0.9653, 0.00001819283938478, gas_get_partial_pressure(current_gas, 1));

	printf("Tissue: %f\n", tissues[0].load);
}
