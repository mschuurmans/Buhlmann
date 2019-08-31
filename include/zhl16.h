#ifndef __zhl16_
#define __zhl16_

#include "gas.h"

/*!
 * Initialises all the tissues
 *
 * given gas is current gas
 */
extern void zhl16_init(struct GAS *);

extern void zhl16_print_tissue_state(void);
extern void zhl16_dive(double, double);
extern void zhl16_set_current_gas(struct GAS *);

/*!
 * Sets the gradient low/high
 *
 * eg: 20/70
 */
extern void zhl16_set_gradient_factors(double, double);

extern double zhl16_get_ndl(double);
#endif
