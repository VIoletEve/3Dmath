
#include <assert.h>
#include <math.h>

#include "Matrix4x3.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "RotationMatrix.h"
#include "Vector3.h"
#include "MathUtil.h"

//置为单位矩阵
void Matrix4x3::identity() {
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m21 = 0.0f; m22 = 0.0f; m23 = 1.0f;
	tx = 0.0f; ty = 0.0f; tz = 1.0f;
}

//清除位移
void Matrix4x3::zeroTranslation() {
	tx = ty = tz = 0.0f;
}

//位移不改变3x3部分
void Matrix4x3::setTranslation(const Vector3& d) {
	tx = d.x; ty = d.y; tz = d.z;
}

//位移并清空旋转
void Matrix4x3::setupTranslation(const Vector3& d) {
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m21 = 0.0f; m22 = 0.0f; m23 = 1.0f;
	tx = d.x; ty = d.y; tz = d.z;
}

//构造局部->父空间变换矩阵，通常用于物体->世界空间
void Matrix4x3::setupLocalToParent(const Vector3& pos, const EulerAngles& orient) {
	//欧拉角构造旋转矩阵，二者都是表示惯性到物体
	RotationMatrix orientMatrix;
	orientMatrix.setup(orient);

	//调用下面的从旋转矩阵构造4x3矩阵函数
	setupLocalToParent(pos, orientMatrix);
}

//旋转矩阵和位移构造4x3矩阵(世界空间)
void Matrix4x3::setupLocalToParent(const Vector3& pos, const RotationMatrix& orient) {
	//旋转矩阵是惯性到物体，转置成物体到惯性
	m11 = orient.m11; m12 = orient.m21; m13 = orient.m31;
	m21 = orient.m12; m22 = orient.m22; m23 = orient.m32;
	m31 = orient.m13; m32 = orient.m23; m33 = orient.m33;
	//平移部分
	tx = pos.x; ty = pos.y; tz = pos.z;
}

//构造父空间到局部空间的矩阵，世界->物体
void Matrix4x3::setupParentToLocal(const Vector3& pos, const EulerAngles& orient) {
	RotationMatrix orientMatrix;
	orientMatrix.setup(orient);
	setupParentToLocal(pos, orientMatrix);

}

//从旋转矩阵构造向量父空间到局部空间的矩阵
void Matrix4x3::setupParentToLocal(const Vector3& pos, const RotationMatrix& orient) {
	m11 = orient.m11; m12 = orient.m12; m13 = orient.m13;
	m21 = orient.m21; m22 = orient.m22; m23 = orient.m23;
	m31 = orient.m31; m32 = orient.m32; m33 = orient.m33;

	//先旋转平移部分，再平移负的量
	tx = -(pos.x * m11 + pos.y * m21 + pos.z * m31);
	ty = -(pos.x * m12 + pos.y * m22 + pos.z * m32);
	tz = -(pos.x * m13 + pos.y * m23 + pos.z * m33);
}

//构造绕坐标轴旋转的矩阵
void Matrix4x3::setupRotate(int axis, float theta) {
	float s, c;
	sinCos(&s, &c, theta);

	switch (axis)
	{
	case 1:
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = c; m23 = s;
		m21 = 0.0f; m22 = -s; m23 = c;
		break;
	case 2:
		m11 = c; m12 = 0.0f; m13 = -s;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m21 = s; m22 = 0.0f; m23 = c;
		break;
	case 3:
		m11 = c; m12 = s; m13 = 0.0f;
		m21 = -s; m22 = c; m23 = 0.0f;
		m21 = 0.0f; m22 = 0.0f; m23 = 1.0f;
		break;

	default:
		assert(false);
	}

	tx = ty = tz = 0.0f;
}

//构造绕任意轴旋转的矩阵
void Matrix4x3::setupRotate(const Vector3& axis, float theta) {
	//检测正则化
	assert(fabs(axis * axis - 1.0f) < .0001f);

	float s, c;
	sinCos(&s, &c, theta);

	//根据绕任意轴旋转的公式
	float a = 1.0f - c;
	float ax = a * axis.x;
	float ay = a * axis.y;
	float az = a * axis.z;

	m11 = ax * axis.x + c;
	m12 = ax * axis.y + axis.z * s;
	m13 = ax * axis.z - axis.y * s;

	m21 = ay * axis.x - axis.z * s;
	m22 = ay * axis.y + c;
	m23 = ay * axis.z + axis.x * s;

	m31 = az * axis.x + axis.y * s;
	m32 = az * axis.y - axis.x * s;
	m33 = az * axis.z + c;

	tx = ty = tz = 0.0f;
}


//从四元数转换到矩阵
void Matrix4x3::fromQuaternion(const Quaternion& q) {
	
	float ww = 2.0f * q.w;
	float xx = 2.0f * q.x;
	float yy = 2.0f * q.y;
	float zz = 2.0f * q.z;

	m11 = 1.0f - yy * q.y - zz * q.z;
	m12 = xx * q.y + ww * q.z;
	m13 = xx * q.z - ww * q.x;

	m21 = xx * q.y - ww * q.z;
	m22 = 1.0f - xx * q.x - zz * q.z;
	m23 = yy * q.z + ww * q.x;

	m31 = xx * q.z + ww*q.y;
	m32 = yy * q.z - ww * q.x;
	m33 = 1.0f - xx * q.x - yy * q.y;

	//四元数没有位移
	tx = ty = tz = 0.0f;
}

//缩放
void Matrix4x3::setupScale(const Vector3& s) {
	m11 = s.x; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = s.y; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = s.z;

	tx = ty = tz = 0.0f;
}

//沿任意轴缩放，k是缩放因子
void Matrix4x3::seteupScaleAlongAxis(const Vector3& axis, float k) {
	//检测缩放轴是否是单位向量
	assert(fabs(axis * axis - 1.0f) < .0001f);

	//根据沿任意轴的3d缩放矩阵公式
	float a = k - 1.0f;
	float ax = a * axis.x;
	float ay = a * axis.y;
	float az = a * axis.z;

	m11 = ax * axis.x + 1.0f;
	m22 = ay * axis.y + 1.0f;
	m32 = az * axis.z + 1.0f;

	m12 = m21 = ax * axis.y;
	m13 = m31 = ax * axis.z;
	m23 = m32 = ay * axis.z;

	tx = ty = tz = 0.0f;
}

//切变矩阵，axis表示用哪个轴切变
void Matrix4x3::setupShear(int axis, float s, float t) {
	switch (axis)
	{
	case 1://用x切变y和z
		m11 = 1.0f; m12 = s; m13 = t;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m21 = 0.0f; m22 = 0.0f; m23 = 1.0f;
		break;

	case 2://用y切变x和z
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = s; m22 = 1.0f; m23 = t;
		m21 = 0.0f; m22 = 0.0f; m23 = 1.0f;
		break;
	case 3://用z切变x和y
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m21 = s; m22 = t; m23 = 1.0f;
		break;
	default:
		assert(false);
	}

	tx = ty = tz = 0.0f;
}

//投影矩阵，投影平面过原点，且垂直于单位向量n
void Matrix4x3::setupProject(const Vector3& n) {
	assert(fabs(n * n - 1.0f) < 0.0001f);

	m11 = 1.0f - n.x * n.x;
	m22 = 1.0f - n.y * n.y;
	m33 = 1.0f - n.z * n.z;

	m12 = m21 = -n.x * n.y;
	m13 = m31 = -n.x * n.z;
	m23 = m32 = -n.y * n.z;

	tx = ty = tz = 0.0f;
}

//反射(镜像)矩阵，镜像平面平行于坐标平面，沿axis=k平面
void Matrix4x3::setupReflect(int axis, float k) {

	switch (axis)
	{
	case 1:
		m11 = -1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m21 = 0.0f; m22 = 0.0f; m23 = 1.0f;

		tx = 2.0f * k; ty = 0.0f; tz = 0.0f;
		break;
	case 2:
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = -1.0f; m23 = 0.0f;
		m21 = 0.0f; m22 = 0.0f; m23 = 1.0f;

		tx = 0.0f; ty = 2.0f * k; tz = 0.0f;
		break;
	case 3:
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m21 = 0.0f; m22 = 0.0f; m23 = -1.0f;

		tx = 0.0f; ty = 0.0f; tz = 2.0f * k;
		break;

	default:
		assert(false);
	}
}

//绕任意通过原点的平面反射(镜像)，且垂直于单位向量v
void Matrix4x3::setupReflect(const Vector3& v) {
	assert(fabs(v * v - 1.0f) < 0.0001f);

	float ax = -2.0f * v.x;
	float ay = -2.0f * v.y;
	float az = -2.0f * v.z;

	m11 = 1.0f + ax * v.x;
	m22 = 1.0f + ay * v.y;
	m33 = 1.0f + az * v.z;

	m12 = m21 = ax * v.y;
	m13 = m31 = ax * v.z;
	m23 = m32 = ax * v.z;

	tx = ty = tz = 0.0f;

}

//对向量p执行m矩阵变换
Vector3 operator*(const Vector3& p, const Matrix4x3& m) {
	return Vector3{
		p.x * m.m11 + p.y * m.m21 + p.z * m.m31 + m.tx,
		p.x * m.m12 + p.y * m.m22 + p.z * m.m32 + m.tx,
		p.x * m.m13 + p.y * m.m23 + p.z * m.m33 + m.tz
	};

}

Vector3& operator*=(Vector3& p, const Matrix4x3& m) {
	p = p * m;
	return p;
		
}

//矩阵相乘连接
Matrix4x3 operator*(const Matrix4x3& a, const Matrix4x3& b) {

	Matrix4x3 r;
	
	r.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
	r.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
	r.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;

	r.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
	r.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
	r.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;

	r.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
	r.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
	r.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;

	r.tx = a.tx * b.m11 + a.ty * b.m21 + a.tz * b.m31 + b.tx;
	r.ty = a.tx * b.m12 + a.ty * b.m22 + a.tz * b.m32 + b.tx;
	r.tz = a.tx * b.m13 + a.ty * b.m23 + a.tz * b.m33 + b.tx;

	return r;
}


Matrix4x3 operator*=(Matrix4x3& a, const Matrix4x3& b) {
	a = a * b;
	return a;
		
}

//矩阵行列式
float determinant(const Matrix4x3& m) {
	return
		m.m11 * (m.m22 * m.m33 - m.m23 * m.m32)
		+ m.m12 * (m.m23 * m.m31 - m.m21 * m.m33)
		+ m.m13 * (m.m21 * m.m32 - m.m22 * m.m31);
}

//矩阵的逆
Matrix4x3 inverse(const Matrix4x3& m) {
	float det = determinant(m);
	//如果行列式为0，则说明没有矩阵的逆
	assert(fabs(det) > 0.000001f);

	float oneOverDet = 1.0f / det;

	Matrix4x3 r;

	r.m11 = (m.m22 * m.m33 - m.m23 * m.m32) * oneOverDet;
	r.m12 = (m.m13 * m.m32 - m.m12 * m.m33) * oneOverDet;
	r.m13 = (m.m12 * m.m23 - m.m13 * m.m22) * oneOverDet;

	r.m21 = (m.m23 * m.m31 - m.m21 * m.m33) * oneOverDet;
	r.m22 = (m.m11 * m.m33 - m.m13 * m.m31) * oneOverDet;
	r.m23 = (m.m13 * m.m21 - m.m11 * m.m23) * oneOverDet;

	r.m31 = (m.m21 * m.m32 - m.m22 * m.m31) * oneOverDet;
	r.m32 = (m.m12 * m.m31 - m.m11 * m.m32) * oneOverDet;
	r.m33 = (m.m11 * m.m22 - m.m12 * m.m21) * oneOverDet;

	r.tx = -(m.tx * r.m11 + m.ty * r.m21 + m.tz * r.m31);
	r.ty = -(m.tx * r.m12 + m.ty * r.m22 + m.tz * r.m32);
	r.tz = -(m.tx * r.m13 + m.ty * r.m23 + m.tz * r.m33);

	return r;

}

//提取平移部分
Vector3 getTranslation(const Matrix4x3& m) {
	return Vector3(m.tx, m.ty, m.tz);
}

//从父->局部(世界->物体)变换矩阵中提取物体的位置
//矩阵的刚体变换
Vector3 getPositionFromParentToLocalMatrix(const Matrix4x3& m) {
	return Vector3{
		-(m.tx * m.m11 + m.ty * m.m12 + m.tz * m.m13),
		-(m.tx * m.m21 + m.ty * m.m22 + m.tz * m.m23),
		-(m.tx * m.m31 + m.ty * m.m32 + m.tz * m.m33)
	};
}


//从局部->父(物体->世界)变换矩阵中提取物体位置
Vector3 getPositionFromLocalToParentMatrix(const Matrix4x3& m) {
	return Vector3(m.tx, m.ty, m.tz);
}





