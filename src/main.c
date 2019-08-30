#include <stdio.h>
#include "tissue.h"

int main(int argc, char** argv) 
{
	printf("Hello\n");

	struct TISSUE tissue;

	tissue_set_load(&tissue, 10);

	printf("Tissue: %f\n", tissue.load);
}


