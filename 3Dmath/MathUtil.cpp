#include "MathUtil.h"

#include "Vector3.h"
#include "Vector3.cpp"

const Vector3 kZeroVector(0.0f, 0.0f, 0.0f);

//将角度限制在-pi到pi的区间
float wrapPi(float theta) {
	theta += kPi;
	theta -= floor(theta * k1Over2Pi) * k2Pi;
	theta -= kPi;
	return theta;
}

//安全反三角函数
float safeAcos(float x) {
	if (x <= -1.0f) {
		return kPi;
	}
	if (x >= 1.0f) {
		return 0.0f;
	}

	return acos(x);
}

