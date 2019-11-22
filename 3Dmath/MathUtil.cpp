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

//计算3d重心坐标
bool computeBarycentricCoords3d(const Vector3 v[3], const Vector3& p, float b[3]) {

	Vector3 d1 = v[1] - v[0];
	Vector3 d2 = v[2] - v[1];

	Vector3 n = crossProduct(d1, d2);

	float u1, u2, u3, u4;
	float v1, v2, v3, v4;

	if ((fabs(n.x) >= fabs(n.y)) && (fabs(n.x) >= fabs(n.z))) {

		u1 = v[0].y - v[2].y;
		u2 = v[1].y - v[2].y;
		u3 = p.y - v[0].y;
		u4 = p.y - v[2].y;

		v1 = v[0].z - v[2].z;
		v2 = v[1].z - v[2].z;
		v3 = p.z - v[0].z;
		v4 = p.z - v[2].z;

	}
	else if (fabs(n.y) >= fabs(n.z)) {

		u1 = v[0].z - v[2].z;
		u2 = v[1].z - v[2].z;
		u3 = p.z - v[0].z;
		u4 = p.z - v[2].z;

		v1 = v[0].x - v[2].x;
		v2 = v[1].x - v[2].x;
		v3 = p.x - v[0].x;
		v4 = p.x - v[2].x;
	}
	else {
		u1 = v[0].x - v[2].x;
		u2 = v[1].x - v[2].x;
		u3 = p.x - v[0].x;
		u4 = p.x - v[2].x;

		v1 = v[0].y - v[2].y;
		v2 = v[1].y - v[2].y;
		v3 = p.y - v[0].y;
		v4 = p.y - v[2].y;

	}
}