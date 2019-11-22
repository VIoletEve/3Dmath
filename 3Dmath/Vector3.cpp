#include "Vector3.h"

//向量模
inline float vectorMag(const Vector3& v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//叉乘
inline Vector3 crossProduct(const Vector3&a,const Vector3&b) {
	return Vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

inline Vector3 operator*(float k, const Vector3& v) {
	return Vector3(k * v.x, k * v.y, k * v.z);
}


inline float distance(const Vector3& a, const Vector3& b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

//全局单位向量
extern const Vector3 kZeroVector;