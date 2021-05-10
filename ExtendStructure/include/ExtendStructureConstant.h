#ifndef ExtendStructureConstant_h__
#define ExtendStructureConstant_h__

#include <string>
#include "ExtendStructureExport.h"

typedef double KFLOAT;

extern ExtendStructure_EXPORT const double NUM_DOUBLE_MIN;
extern ExtendStructure_EXPORT const double NUM_DOUBLE_MAX;
extern ExtendStructure_EXPORT const float NUM_FLOAT_MIN;
extern ExtendStructure_EXPORT const float NUM_FLOAT_MAX;
extern ExtendStructure_EXPORT const double NUM_PI;

extern ExtendStructure_EXPORT const double NUM_WGS_84_RADIUS_EQUATOR;
extern ExtendStructure_EXPORT const double NUM_WGS_84_RADIUS_POLAR;

extern "C" ExtendStructure_EXPORT void Clamp(KFLOAT& rValue);

extern "C" ExtendStructure_EXPORT bool IsEquivalent(KFLOAT lhs, KFLOAT rhs, KFLOAT fEpsilon = 1e-8);

extern "C" ExtendStructure_EXPORT KFLOAT RadiusToDegree(KFLOAT fRadius);

extern "C" ExtendStructure_EXPORT KFLOAT DegreeToRadius(KFLOAT fDegree);

#endif // ExtendStructureConstant_h__
