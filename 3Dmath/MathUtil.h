#pragma once

#include <math.h>

//圆周率
const float kPi = 3.14159265f;
const float k2Pi = kPi * 2.0f;
const float kpiOver2 = kPi / 2.0f;
const float k1OverPi = 1.0f / kPi;
const float k1Over2Pi = 1.0f / k2Pi;

//将角度限制在-pi到pi的区间
extern float wrapPi(float theta);

//安全反三角函数
extern float safeAcos(float x);

inline void sinCos(float* returnSin, float* returnCos, float theta) {
	*returnSin = sin(theta);
	*returnCos = cos(theta);
}

