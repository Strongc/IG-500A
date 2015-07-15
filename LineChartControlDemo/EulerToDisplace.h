#include "stdafx.h"
#include "MyMatrix.h"

struct  Euler
{
	float roll;
	float pitch;
	float yaw;
};

struct Speed{
	float xspeed;
	float yspeed;
	float zspeed;
};

/*
DCM=
cos2cos3 sin1sin2cos3−cos1sin3 cos1sin2sin3+sin1sin3
cos2sin3 sin1sin2sin3+cos1cos3 cos1sin2sin3−sin1cos3
−sin2    sin1cos2              cos1cos2
*/
void getDCM(Euler *state, float **dcm);
