#ifndef __DIVE_H_
#define __DIVE_H_

#include <stdlib.h>
#include <stdbool.h>

struct dive {
	float	depth;
	float	depth_old;
	float	depth_max;
	long	last_time;
	float	p_amb_air;	/* Air pressure */
	float	p_amb;		/*Ambient pressure */
	float	pp_n2;
	float	pp_he;
	float	pp_o2;
	float	perc_n2;
	float	perc_o2;
	float	perc_he;
	float	te_min;		/* Smalled no decompression limit */
	float	pp_amb_tol_max; /* Max tol. ambient pressure */
	float	depth_tol_min;	/* Min tol. depth */
	int	def_cmpt;	/* Defining compartment */
	float	compart[16][3]; /* Compart model array */
	bool	deco;		/* Indicates if this is a deco dive */
};

#define C_N_T1_2	0
#define C_N_A		1
#define C_N_B		2
#define C_H_T1_2	3
#define C_H_A		4
#define C_H_B		5
#define M_PAMBTOL	0
#define M_PIG_N2	1
#define M_PIG_HE	2
#define M_TE_N2		3
#define M_TE_HE		4

#define P_AMB_AIR 1.01325
#ifdef WITH_STEAM_PRESSURE
#define P_STEAM 0.0567
#else
#define P_STEAM 0.0
#endif

#endif
