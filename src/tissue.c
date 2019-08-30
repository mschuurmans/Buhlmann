#include "tissue.h"

void tissue_init(struct TISSUE *tissue, double a, double b, double k, double initial_load)
{
	if (tissue) {
		tissue->a = a;
		tissue->b = b;
		tissue->k = k;

		tissue_set_load(tissue, initial_load);
	}
}

void tissue_set_load(struct TISSUE *tissue, double load)
{
	if (tissue)
		tissue->load = load;
}
