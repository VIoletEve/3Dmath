#pragma once

#include <math.h>

class Vector3 {
public:
	float x, y, z;
	Vector3(){}
	
	Vector3(float vx,float vy,float vz):x(vx),y(vy),z(vz){}

	Vector3(const Vector3& v) :x(v.x), y(v.y), z(v.z) {}

	Vector3& operator=(const Vector3& v) {
		x = v.x; y = v.y; z = v.z;
		return *this;
	}

	bool operator==(const Vector3& v)const {
		return x == v.x && y == v.y && z == v.z;
	}

	bool operator!=(const Vector3& v)const {
		return x != v.x && y != v.y && z != v.z;
	}

	Vector3 operator+(const Vector3& v)const {
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	Vector3 operator-(const Vector3& v)const {
		return Vector3(x - v.x, y - v.y, z - v.z);
	}


	Vector3 operator*(float a)const {
		return Vector3(x * a, y * a, z * a);
	}

	Vector3 operator/(float a)const {
		float oneOverA = 1.0f / a;
		return Vector3(x * oneOverA, y * oneOverA, z * oneOverA);
	}

	Vector3& operator+=(const Vector3& v) {
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& v) {
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	Vector3& operator*=(float a) {
		x *= a; y *= a; z *= a;
		return *this;
	}

	Vector3& operator/=(float a) {
		float oneOverA = 1.0f / a;
		x *= oneOverA; y *= oneOverA; z *= oneOverA;
		return *this;
	}

	void zero() { x = y = z = 0; }

	Vector3 operator-()const { return Vector3(-x, -y, -z); }
	
	//标准化
	void normalize() {
		float magSq = x * x + y * y + z * z;
		if (magSq > 0.0f) {
			float oneOverMag = 1.0f / sqrt(magSq);
			x *= oneOverMag;
			y *= oneOverMag;
			z *= oneOverMag;
		}
			
	}
	
	//点乘
	float operator*(const Vector3& v) const{
		return x * v.x + y * v.y + z * v.z;
	}


};
