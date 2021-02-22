#include <time.h>
#include <math.h>

#include "decompression.h"
#include "zhl16.h"
#include "dive.h"
#include "gas.h"
#include "log.h"

struct gas *current_gas = NULL;

struct dive dive;

float buhlmann_compart_model[16][3] = {
	/* P.a.tol	p.i.g	p.i.g */
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
	{0.0,		0.0,	0.0},
};

/* TODO do we need 8? */
const float buhlmann_compart_const[16][8] = {
	{4.0,	1.2599,	0.5050,	1.5,	1.7435,		0.1911},
	{8.0,	1.0,	0.6514,	3.0,	1.3838,		0.4295},
	{12.5,	0.8618,	0.7222,	4.7,	1.1925,		0.5446},
	{18.5,	0.7562,	0.7725,	7.0,	1.0465,		0.6265},
	{27.0,	0.6667,	0.8125,	10.2,	0.9226,		0.6917},
	{38.3,	0.5933,	0.8434,	14.5,	0.8211,		0.7420},
	{54.3,	0.5282,	0.8693,	20.5,	0.7309, 	0.7820},
	{77.0,	0.4701,	0.8910,	29.1,	0.6506,		0.8195},
	{109.0,	0.4187,	0.9092,	41.1,	0.5794,		0.8491},
	{146,0,	0.3798,	0.9222,	55.1,	0.5256,		0.8703},
	{187.0,	0.3497,	0.9319,	70.6,	0.4840,		0.8860},
	{239.0,	0.3223,	0.9403,	90.2,	0.4460,		0.8997},
	{305.0,	0.2971,	0.9477,	115.1,	0.4112,		0.9118},
	{390.0,	0.2737,	0.9544,	147.2,	0.3788,		0.9226},
	{498.0,	0.2523,	0.9602,	187.9,	0.3492,		0.9321},
	{635.0,	0.2327,	0.9653,	239.6,	0.3220,		0.9404}
};

void calculate_pressure(struct dive *d)
{
	d->p_amb = P_AMB_AIR + d->depth;
	d->pp_n2 = d->perc_n2 * (d->p_amb - P_STEAM);
	d->pp_o2 = d->perc_o2 * (d->p_amb);
	d->pp_he = d->perc_he * (d->p_amb - P_STEAM);
}

/*
 * TODO
 * We now have the dive object in the zhl16 class. 
 * Maybe split this up later to support multiple algorithms.
 *
 * Also now it's difficult to set the current depth on the dive object
 * itself, split it?
 */
int zhl16_dive(long cur_time)
{
	log_debug("Dive");

	unsigned char i;
	float *cur_comp, acor, bcor;
	const float *cur_comp_const;

	calculate_pressure(&dive);

	dive.depth_old = dive.depth;

	if (!dive.deco)
		dive.te_min = 999.0;

	dive.pp_amb_tol_max = 0.0;
	dive.def_cmpt = 0;

	if (dive.depth > dive.depth_max)
		dive.depth_max = dive.depth;

	float delta = ((float)(dive.last_time - cur_time)) / 60;

	for (i = 0; i < 16; i++) {
		cur_comp = dive.compart[i];
		cur_comp_const = buhlmann_compart_const[i];


		/* 
		 * tissue saturation 
		 * pt.   i.g.  (tE) = pt.  i.g.  (t0) + [pli.g.  -pt.   i.g.  (t0)]*[l  - 2A(-tE / tl/2)] 
		 */
		cur_comp[M_PIG_N2] = cur_comp[M_PIG_N2] + (dive.pp_n2 - cur_comp[M_PIG_N2]) * (1 - pow(2, delta / cur_comp_const[C_N_T1_2]));
		cur_comp[M_PIG_HE] = cur_comp[M_PIG_HE] + (dive.pp_he - cur_comp[M_PIG_HE]) * (1 - pow(2, delta / cur_comp_const[C_H_T1_2]));

		/*
		 * Tolerated ambient pressure
		 *
		 * pamb. tol. = (pt. ig. -a) * b
		 */

		acor = (cur_comp_const[C_N_A] * cur_comp[M_PIG_N2] + cur_comp_const[C_H_A] * cur_comp[M_PIG_HE]) / (cur_comp[M_PIG_N2] + cur_comp[M_PIG_HE]);
		bcor = (cur_comp_const[C_N_B] * cur_comp[M_PIG_N2] + cur_comp_const[C_H_B] * cur_comp[M_PIG_HE]) / (cur_comp[M_PIG_N2] + cur_comp[M_PIG_HE]);

		cur_comp[M_PAMBTOL] = (cur_comp[M_PIG_N2] + cur_comp[M_PIG_HE] - acor) * bcor;

		if (cur_comp[M_PAMBTOL] > dive.pp_amb_tol_max) {
			dive.pp_amb_tol_max = cur_comp[M_PAMBTOL];
			dive.def_cmpt = i + 1;
		}
	}

	dive.depth_tol_min = dive.pp_amb_tol_max - P_AMB_AIR;

	dive.last_time = cur_time;

	return 0;
}

int zhl16_set_gas(struct gas *gas)
{
	log_debug("Updating gas");

	current_gas = gas;

	dive.perc_n2 = gas->n2 / 100;
	dive.perc_o2 = gas->o2 / 100;
	dive.perc_he = gas->he / 100;

	return 0;
}

struct decompression_operations zhl_ops = {
	.dive = &zhl16_dive,
	.set_gas = &zhl16_set_gas
};


int zhl16_init()
{
	int i;

	log_info("Initializing zhl16 algorithm");

	decompression_register(&zhl_ops);

	/* TODO get current time */
	long cur_time = time(NULL);

	/* Set all the dive variables */
	dive.deco = 0;
	dive.depth = 0.0;
	dive.depth_old = 0.0;
	dive.last_time = cur_time;
	dive.p_amb = 0.0;
	dive.pp_n2 = 0.0;
	dive.pp_o2 = 0.0;
	dive.pp_he = 0.0;

	/* TODO Base gas on current gas */
	dive.perc_n2 = 0.78084;
	dive.perc_o2 = 0.209476;
	dive.perc_he = 0.00000524;

	dive.te_min = 999;
	dive.depth_max = 0.0;
	dive.depth_tol_min = 0.0;

	/* Set initial load */
	memcpy(dive.compart, buhlmann_compart_model, sizeof(buhlmann_compart_model));

	calculate_pressure(&dive);

	for (i = 0; i < 16; i++) {
		dive.compart[i][M_PIG_N2] = dive.pp_n2;
		dive.compart[i][M_PIG_HE] = dive.pp_he;
	}


	return 0;
}

void zhl16_print()
{
	int i;

	for (i = 0; i < 16; i++) {
		log_debug("Tissue [%d] N2: %f, HE: %f", i, dive.compart[i][M_PIG_N2], dive.compart[i][M_PIG_HE]);
	}
}
