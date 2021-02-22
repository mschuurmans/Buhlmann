#include "tissue.h"

void tissue_init(struct tissue *tissue, double a, double b, double initial_load)
{
	if (tissue) {
		tissue->a = a;
		tissue->b = b;
		
		tissue_set_load(tissue, initial_load);
	}
}

void tissue_set_load(struct tissue *tissue, double load)
{
	if (tissue)
		tissue->load = load;
}
