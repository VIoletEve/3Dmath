#pragma once

#ifndef __EULERANGLES_H_INCLUDED__
#define __EULERANGLES_H_INCLUDED__


class Quaternion;
class Matrix4x3;
class RotationMatrix;

class EulerAngles
{
public:
	//y��
	float heading;
	//x��
	float pitch;
	//z��
	float bank;

	EulerAngles(){}

	EulerAngles(float h,float p,float b):heading(h),pitch(p),bank(b){}

	//����
	void identity() { heading = pitch = bank = 0.0f; }

	//���Ƽ�ŷ����
	void canonize();

	//����Ԫ��ת��Ϊŷ����
	//�����嵽����
	void fromObjectToInertialQuaternion(const Quaternion& q);
	//�ӹ��Ե�����
	void fromInertialToObjectQuaternion(const Quaternion& q);

	//�Ӿ���ŷ����
	//�����嵽����ռ�
	void fromObjectToWorldMatrix(const Matrix4x3& m);
	//�����絽����ռ�
	void fromWorldToObjectMatrix(const Matrix4x3& m);

	//����ת�����ȡŷ����
	void fromRotationMatrix(const RotationMatrix& m);

	
};

//ȫ�ֵ�λŷ����
extern const EulerAngles kEulerAnglesIdentity;


#endif // !__QUATERNION_H_INCLUDED__


