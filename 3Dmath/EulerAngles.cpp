

#include <math.h>
#include "Quaternion.h"
#include "EulerAngles.h"
#include "MathUtil.h"
#include "Matrix4x3.h"
#include "RotationMatrix.h"


const EulerAngles kEulerAnglesIdentity(0.0f, 0.0f, 0.0f);

//����ŷ���� 
void EulerAngles::canonize() {

	//��pitch�����Ƶ�-pi��pi֮��
	pitch = wrapPi(pitch);

	//��pitch�����Ƶ�-pi/2��pi/2֮��
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

	//���������
	if (fabs(pitch) > kpiOver2 - 1e-4) {
		//���������У��������ƴ�ֱ�����ת��heading
		heading += bank;
		bank = 0.0f;
	}
	else {
		//���û��������������bank���Ƶ����Ƽ���
		bank = wrapPi(bank);
	}

	//����heading
	heading = wrapPi(heading);
}

//�����嵽������Ԫ��ת��Ϊŷ����
void EulerAngles::fromObjectToInertialQuaternion(const Quaternion& q) {
	//����sin(pitch)
	float sp = -2.0f * (q.y * q.z - q.w * q.x);
	
	//���������
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

//�ӹ��Ե�������Ԫ��ת��Ϊŷ����
void EulerAngles::fromInertialToObjectQuaternion(const Quaternion& q) {
	//����sin(pitch)
	float sp = -2.0f * (q.y * q.z + q.w * q.x);

	//���������
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

//�����嵽��������ϵ�任�����ȡŷ����
void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3& m) {
	//����sin(pitch)
	float sp = -m.m32;
	//���������
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

//�����絽��������ϵ�任�����ȡŷ����
void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3& m) {
	float sp = -m.m23;
	//���������
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

//����ת����ת��Ϊŷ���Ǻʹ����絽������һ����
void EulerAngles::fromRotationMatrix(const RotationMatrix& m) {
	float sp = -m.m23;
	//���������

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
