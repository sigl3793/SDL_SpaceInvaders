#include "stdafx.h"
#include "Utility.h"

float Utility::RandomFloat(float p_fMin, float p_fMax)
{
	return (p_fMin + (p_fMax - p_fMin) * ((float)rand() / (float)RAND_MAX));
}
