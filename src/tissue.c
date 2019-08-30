#include "tissue.h"

void tissue_set_load(struct TISSUE *tissue, double load)
{
	if (tissue)
		tissue->load = load;
}
