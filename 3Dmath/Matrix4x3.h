#pragma once

#ifndef __MATRIX4x3_H_INCLUDED__
#define __MATRIX4x3_H_INCLUDED__

class Vector3;
class EulerAngles;
class Quaternion;
class RotationMatrix;

class Matrix4x3
{
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;
	float tx, ty, tz;
	
	//单位矩阵
	void identity();

	//平移部分
	void zeroTranslation();
	void setTranslation(const Vector3& d);
	void setupTranslation(const Vector3& d);

	//将欧拉角或旋转矩阵转换为4x3矩阵，使pos在父空间和局部空间变换
	void setupLocalToParent(const Vector3& pos, const EulerAngles& orient);
	void setupLocalToParent(const Vector3& pos, const RotationMatrix& orient);
	void setupParentToLocal(const Vector3& pos, const EulerAngles& orient);
	void setupParentToLocal(const Vector3& pos, const RotationMatrix& orient);

	//构造绕坐标轴旋转的矩阵
	void setupRotate(int axis, float theta);
	//构造绕任意轴旋转的矩阵
	void setupRotate(const Vector3& axis, float theta);

	//四元数构造旋转矩阵
	void fromQuaternion(const Quaternion& q);

	//沿坐标轴缩放的矩阵
	void setupScale(const Vector3& s);

	//沿任意轴缩放的矩阵
	void seteupScaleAlongAxis(const Vector3& axis, float k);

	//切变矩阵
	void setupShear(int axis, float s, float t);
	//投影矩阵，投影平面过原点
	void setupProject(const Vector3& n);
	//反射矩阵
	void setupReflect(int axis, float k = 0.0f);
	//沿任意平面反射矩阵
	void setupReflect(const Vector3& n);
};

//点变换或矩阵连接
Vector3 operator*(const Vector3& p, const Matrix4x3& m);
Matrix4x3 operator*(const Matrix4x3& a, const Matrix4x3& b);

//同上
Vector3& operator*=(Vector3& p, const Matrix4x3& m);
Matrix4x3 operator*=(const Matrix4x3& a, const Matrix4x3& b);

//计算3x3部分的行列式值
float determinant(const Matrix4x3& m);
//计算矩阵的逆
Matrix4x3 inverse(const Matrix4x3& m);
//获取矩阵平移部分
Vector3 getTranslation(const Matrix4x3& m);

//从局部矩阵->父矩阵或反过来获取位置
Vector3 getPositionFromParentToLocalMatrix(const Matrix4x3& m);
Vector3 getPositionFromLocalToParentMatrix(const Matrix4x3& m);

#endif // !__MATRIX4x3_H_INCLUDED__