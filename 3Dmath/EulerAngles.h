#pragma once

#ifndef __EULERANGLES_H_INCLUDED__
#define __EULERANGLES_H_INCLUDED__


class Quaternion;
class Matrix4x3;
class RotationMatrix;

class EulerAngles
{
public:
	//y轴
	float heading;
	//x轴
	float pitch;
	//z轴
	float bank;

	EulerAngles(){}

	EulerAngles(float h,float p,float b):heading(h),pitch(p),bank(b){}

	//置零
	void identity() { heading = pitch = bank = 0.0f; }

	//限制集欧拉角
	void canonize();

	//从四元数转换为欧拉角
	//从物体到惯性
	void fromObjectToInertialQuaternion(const Quaternion& q);
	//从惯性到物体
	void fromInertialToObjectQuaternion(const Quaternion& q);

	//从矩阵到欧拉角
	//从物体到世界空间
	void fromObjectToWorldMatrix(const Matrix4x3& m);
	//从世界到物体空间
	void fromWorldToObjectMatrix(const Matrix4x3& m);

	//从旋转矩阵获取欧拉角
	void fromRotationMatrix(const RotationMatrix& m);

	
};

//全局单位欧拉角
extern const EulerAngles kEulerAnglesIdentity;


#endif // !__QUATERNION_H_INCLUDED__


