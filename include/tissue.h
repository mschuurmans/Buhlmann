#ifndef __tissue_h_
#define __tissue_h_

struct TISSUE {
	double a; // Buhlmann a value [bar]
	double b; // Buhlmann b value [bar]
	double k; // Buhlmann k value calculated from half time [1/s]

	double load; // actual tissue load [bar]
};

/*!
 * Sets the actuall tissue load on given tissue
 */
extern void tissue_set_load(struct TISSUE*, double);

#endif
