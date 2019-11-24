
#include <math.h>
#include <assert.h>


#include "Quaternion.h"
#include "MathUtil.h"
#include "Vector3.h"
#include "EulerAngles.h"
#include "Vector3.cpp"

const Quaternion kQuaternionIdentity = {
	1.0f,0.0f,0.0f,0.0f
};

//x旋转
void Quaternion::setToRotateX(float theta) {
	float thetaOver2 = theta * 0.5f;

	w = cos(thetaOver2);
	x = sin(thetaOver2);
	y = 0.0f;
	z = 0.0f;
}

//y旋转
void Quaternion::setToRotateY(float theta) {
	float thetaOver2 = theta * 0.5f;

	w = cos(thetaOver2);
	x = 0.0f;
	y = sin(thetaOver2);
	z = 0.0f;
}

//绕z旋转
void Quaternion::setToRotateZ(float theta) {
	float thetaOver2 = theta * 0.5f;

	w = cos(thetaOver2);
	x = 0.0f;
	y = 0.0f;
	z = sin(thetaOver2);
}

//绕axis旋转theta
void Quaternion::setToRotateAxis(const Vector3& axis, float theta) {
	//旋转轴必须标准化
	assert(fabs(vectorMag(axis) - 1.0f) < .01f);
	
	float thetaOver2 = theta * .5f;
	float sinThetaOver2 = sin(thetaOver2);

	w = cos(thetaOver2);
	x = axis.x * sinThetaOver2;
	y = axis.y * sinThetaOver2;
	z = axis.z * sinThetaOver2;

}

//从欧拉角构造物体到惯性四元数
void Quaternion::setToRotateObjectToInertial(const EulerAngles& orientation) {
	float sp, sb, sh;
	float cp, cb, ch;
	sinCos(&sp, &cp, orientation.pitch * 0.5f);
	sinCos(&sb, &cb, orientation.bank * 0.5f);
	sinCos(&sh, &ch, orientation.heading * 0.5f);

	w = ch * cp * cb + sh * sp * sb;
	x = ch * sp * cb + sh * cp * sb;
	y = -ch * sp * sb + sh * cp * cb;
	z = -sh * sp * cb + ch * cp * sb;

}

//从欧拉角构造惯性到物体四元数，与上面共轭
void Quaternion::setToRotateInertialToObject(const EulerAngles& orientation) {
	float sp, sb, sh;
	float cp, cb, ch;
	sinCos(&sp, &cp, orientation.pitch * 0.5f);
	sinCos(&sb, &cb, orientation.bank * 0.5f);
	sinCos(&sh, &ch, orientation.heading * 0.5f);

	w = ch * cp * cb + sh * sp * sb;
	x = -ch * sp * cb - sh * cp * sb;
	y = ch * sp * sb - sh * cp * cb;
	z = sh * sp * cb - ch * cp * sb;
	
}

//四元数叉乘
Quaternion Quaternion::operator*(const Quaternion& a)const {
	Quaternion result;

	result.w = w * a.w - x * a.x - y * a.y - z * a.z;
	result.x = w * a.x + x * a.w + z * a.y - y * a.z;
	result.y = w * a.y + y * a.w + x * a.z - z * a.x;
	result.z = w * a.z + z * a.w + y * a.x - x * a.y;

	return result;
}

Quaternion &Quaternion::operator*=(const Quaternion& a) {

	*this = *this * a;
	return *this;
}

//正则化
void Quaternion::normalize() {

	//计算四元数的模
	float mag = (float)sqrt(w * w + x * x + y * y + z * z);

	//检查长度，防止除零错误
	if (mag > 0.0f) {
		
		float oneOverMag = 1.0f / mag;
		w *= oneOverMag;
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
	}
	else {
		assert(false);
		identity();
	}
}

//返回旋转角
float Quaternion::getRotationAngle()const {
	float thetaOver2 = safeAcos(w);
	return thetaOver2 * 2.0f;
}

//返回旋转轴
Vector3 Quaternion::getRotationAxis()const {

	//计算sin^2(theta/2)
	float sinThetaOver2Sq = 1.0f - w * w;

	if (sinThetaOver2Sq <= 0.0f) {
		return Vector3(1.0f, 0.0f, 0.0f);
	}

	//计算1/sin(theta/2)
	float oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);

	return Vector3(x * oneOverSinThetaOver2, y * oneOverSinThetaOver2, z * oneOverSinThetaOver2);
}


//四元数点乘
extern float dotProduct(const Quaternion& a, const Quaternion& b) {
	return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
}

//球面线性插值
extern Quaternion slerp(const Quaternion& q0, const Quaternion& q1, float t) {
	if (t <= 0.0f)return q0;
	if (t >= 1.0f)return q1;

	float cosOmega = dotProduct(q0, q1);

	float q1w = q1.w;
	float q1x = q1.x;
	float q1y = q1.y;
	float q1z = q1.z;

	if (cosOmega < 0.0f) {
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;
		cosOmega = -cosOmega;
	}

	assert(cosOmega <= 1.0f);

	float k0, k1;
	if (cosOmega > 0.9999f) {
		k0 = 1.0f - t;
		k1 = t;
	}
	else {
		float sinOmega = sqrt(1.0f - cosOmega * cosOmega);

		float omega = atan2(sinOmega, cosOmega);

		float oneOverSinOmerga = 1.0f / sinOmega;

		k0 = sin((1.0f - t) * omega) * oneOverSinOmerga;
		k1 = sin(t * omega) * oneOverSinOmerga;
	}

	Quaternion result;
	result.x = k0 * q0.x + k1 * q1x;
	result.y = k0 * q0.y + k1 * q1y;
	result.z = k0 * q0.z + k1 * q1z;
	result.w = k0 * q0.w + k1 * q1w;

	return result;

}

//共轭
extern Quaternion conjugate(const Quaternion& q) {
	Quaternion result;
	result.w = q.w;

	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;

	return result;
}

//四元数幂
extern Quaternion pow(const Quaternion& q, float exponent) {
	if (fabs(q.w) > .9999f) {
		return q;
	}

	float alpha = acos(q.w);

	float newAlpha = alpha * exponent;

	Quaternion result;
	result.w = cos(newAlpha);

	float mult = sin(newAlpha) / sin(alpha);
	result.x = mult * q.x;
	result.y = mult * q.y;
	result.z = mult * q.z;

	return result;
}
