#pragma once

#ifndef __QUATERNION_H_INCLUDED__
#define __QUATERNION_H_INCLUDED__

class Vector3;
class EulerAngles;
class Quaternion
{
public:
	
	float w, x, y, z;

	void identity() { w = 1.0f; x = y = z = 0.0f; }

	void setToRotateX(float theta);
	void setToRotateY(float theta);
	void setToRotateZ(float theta);
	void setToRotateAxis(const Vector3& axis,float theta);

	void setToRotateObjectToInertial(const EulerAngles& orientation);
	void setToRotateInertialToObject(const EulerAngles& orientation);

	Quaternion operator*(const Quaternion& a)const;

	Quaternion &operator*=(const Quaternion& a);

	void normalize();

	float getRotationAngle()const;
	Vector3 getRotationAxis()const;

};

extern const Quaternion kQuaternionIdentity;

extern float dotProduct(const Quaternion& a, const Quaternion& b);

extern Quaternion slerp(const Quaternion& p, const Quaternion& q, float t);

extern Quaternion conjugate(const Quaternion& q);

extern Quaternion pow(const Quaternion& q, float exponent);

#endif // !__QUATERNION_H_INCLUDED__

