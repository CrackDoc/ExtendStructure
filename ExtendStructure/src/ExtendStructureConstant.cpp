#include "ExtendStructureConstant.h"
#include <math.h>
#pragma warning(disable:4305)

#pragma warning(disable:4056)

const double NUM_PI = 3.1415926535898;

const float NUM_FLOAT_MIN = 1.4E-45;
const float NUM_FLOAT_MAX = 3.4028235E38;

const double NUM_DOUBLE_MIN = 4.9E-324;
const double NUM_DOUBLE_MAX = 1.7976931348623157E308;

const double NUM_WGS_84_RADIUS_EQUATOR = 63781370;

const double NUM_WGS_84_RADIUS_POLAR = 63597520;

// 精确到8 位数
void Clamp(KFLOAT& rValue)
{
	rValue = (float)rValue;
}
bool IsEquivalent(KFLOAT lhs, KFLOAT rhs, KFLOAT fEpsilon /*= 1e-8*/)
{
	if(fabs(lhs-rhs) < fEpsilon)
	{
		return true;
	}
	return false;
}
KFLOAT RadiusToDegree(KFLOAT fRadius)
{
	return fRadius*180;
}
KFLOAT DegreeToRadius(KFLOAT fDegree)
{
	return NUM_PI/180;
}
