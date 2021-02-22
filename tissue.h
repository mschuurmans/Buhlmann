#ifndef __TISSUE_H_
#define __TISSUE_H_

struct tissue {
	double a; /* Buhlmann a value */
	double b; /* Buhlmann b value */

	double load; // actual tissue load.
};

extern void tissue_set_load(struct tissue*, double);
extern void tissue_init(struct tissue*, double, double, double);

#endif
