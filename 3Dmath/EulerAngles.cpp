

#include <math.h>
#include "Quaternion.h"
#include "EulerAngles.h"
#include "MathUtil.h"
#include "Matrix4x3.h"
#include "RotationMatrix.h"


const EulerAngles kEulerAnglesIdentity(0.0f, 0.0f, 0.0f);

//限制欧拉角 
void EulerAngles::canonize() {

	//将pitch轴限制到-pi到pi之间
	pitch = wrapPi(pitch);

	//将pitch轴限制到-pi/2到pi/2之间
	if (pitch < -kpiOver2) {
		pitch = -kPi - pitch;
		heading += kPi;
		bank += kPi;
	}
	else if (pitch > kpiOver2) {
		pitch = kPi - pitch;
		heading += kPi;
		bank += kPi;
	}

	//检查万向锁
	if (fabs(pitch) > kpiOver2 - 1e-4) {
		//在万向锁中，将所有绕垂直轴的旋转给heading
		heading += bank;
		bank = 0.0f;
	}
	else {
		//如果没产生万向锁，将bank限制到限制集中
		bank = wrapPi(bank);
	}

	//限制heading
	heading = wrapPi(heading);
}

//从物体到惯性四元数转换为欧拉角
void EulerAngles::fromObjectToInertialQuaternion(const Quaternion& q) {
	//计算sin(pitch)
	float sp = -2.0f * (q.y * q.z - q.w * q.x);
	
	//检查万向锁
	if (fabs(sp) > 0.9999f) {
		pitch = kpiOver2 * sp;

		heading = atan2(-q.x * q.z - q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
		bank = 0.0f;

	}
	else {
		pitch = asin(sp);
		heading = atan2(q.x * q.z + q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
		bank = atan2(q.x * q.y + q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
	}
}

//从惯性到物体四元数转换为欧拉角
void EulerAngles::fromInertialToObjectQuaternion(const Quaternion& q) {
	//计算sin(pitch)
	float sp = -2.0f * (q.y * q.z + q.w * q.x);

	//检查万向锁
	if (fabs(sp) > 0.9999f) {

		pitch = kpiOver2 * sp;

		heading = atan2(-q.x * q.z - q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
		bank = 0.0f;
	}
	else {
		pitch = asin(sp);
		heading = atan2(q.x * q.z - q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
		bank = atan2(q.x * q.y - q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
	}

}

//从物体到世界坐标系变换矩阵获取欧拉角
void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3& m) {
	//计算sin(pitch)
	float sp = -m.m32;
	//检查万向锁
	if (fabs(sp) > 0.99999f) {
		pitch = kpiOver2 * sp;
		heading = atan2(-m.m23, m.m11);
		bank = 0.0f;
	}
	else {
		pitch = asin(sp);
		heading = atan2(m.m31, m.m33);
		
		bank = atan2(m.m12, m.m22);
	}
}

//从世界到物体坐标系变换矩阵获取欧拉角
void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3& m) {
	float sp = -m.m23;
	//检查万向锁
	if (fabs(sp) > 0.99999f) {
		pitch = kpiOver2 * sp;
		heading = atan2(-m.m31, m.m11);
		bank = 0.0f;
	}
	else {
		pitch = asin(sp);
		heading = atan2(m.m13, m.m33);
		
		bank = atan2(m.m21, m.m22);
	}
}

//从旋转矩阵转换为欧拉角和从世界到物体是一样的
void EulerAngles::fromRotationMatrix(const RotationMatrix& m) {
	float sp = -m.m23;
	//检查万向锁

	if (fabs(sp) > 0.99999f) {
		pitch = kpiOver2 * sp;
		heading = atan2(-m.m31, m.m11);
		bank = 0.0f;
	}
	else {
		pitch = asin(sp);
		heading = atan2(m.m13, m.m33);
		bank = atan2(m.m21, m.m22);
	}
}
