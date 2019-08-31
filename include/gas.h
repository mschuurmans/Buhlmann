#ifndef __GAS_H_
#define __GAS_H_

/*!
 * Gases are in percentage
 * 
 * eg: 21 o2
 */
struct GAS {
	double o2;
	double he;
	double n2;
};

int gas_init(struct GAS *, double, double);
double gas_percent_to_partial(double);

/*!
 * Returns the partial pressure of the gas based on the
 * current depth in bars
 */
double gas_get_partial_pressure(struct GAS *, double);

#endif
