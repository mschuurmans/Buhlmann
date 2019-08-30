#include <stdio.h>

#include "zhl16.h"
#include "tissue.h"

struct TISSUE tissues[16];

void zhl16_init(void)
{
	printf("Initializing zhl16 tissues\n");

	
	// TODO set initial load (based on current pressure and/or left over from previous dive?)
	tissue_init(&tissues[0], 1.1696, 0.5578, 0.00231049060186648, 0);
	tissue_init(&tissues[1], 1.0, 0.6514, 0.00144405662616655, 0);
	tissue_init(&tissues[2], 0.8618, 0.7222, 0.00092419624074659, 0);
	tissue_init(&tissues[3], 0.7562, 0.7825, 0.00062445691942338, 0);
	tissue_init(&tissues[4], 0.62, 0.8124, 0.00042786862997528, 0);
	tissue_init(&tissues[5], 0.5043, 0.8434, 0.00030163062687552, 0);
	tissue_init(&tissues[6], 0.441, 0.8693, 0.00021275235744627, 0);
	tissue_init(&tissues[7], 0.4, 0.891, 0.00015003185726406, 0);
	tissue_init(&tissues[8], 0.375, 0.9092, 0.00010598580742507, 0);
	tissue_init(&tissues[9], 0.35, 0.9222, 0.00007912639047488, 0);
	tissue_init(&tissues[10], 0.3295, 0.9319, 0.00006177782357932, 0);
	tissue_init(&tissues[11], 0.3065, 0.9403, 0.00004833662347001, 0);
	tissue_init(&tissues[12], 0.2835, 0.9477, 0.00003787689511257, 0);
	tissue_init(&tissues[13], 0.261, 0.9544, 0.00002962167438290, 0);
	tissue_init(&tissues[14], 0.248, 0.9602, 0.00002319769680589, 0);
	tissue_init(&tissues[15], 0.2327, 0.9653, 0.00001819283938478, 0);

	printf("Tissue: %f\n", tissues[0].load);
}

void zhl16_print_tissue_state(void)
{
	int i;
	for (i = 0; i < 16; i++) {
		printf("Tissue[%d]:\ta: %f, b: %f, k: %.17f, load: %f\n", i, tissues[i].a, tissues[i].b, tissues[i].k, tissues[i].load);
	}
}
