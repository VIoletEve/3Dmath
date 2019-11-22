# 3D-math-foundation

## Pages

* 3D向量类
* 欧拉角类
* 四元数类
* 旋转矩阵类
* 4x3矩阵类
* AABB类
* 三角网格类

### 3D向量类

```
Vector3.h

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

Vector3.cpp

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
```

向量点乘



**how old are you**
*could you?*
~~adfaosajfs~~

* list1
* list2

1. Vector
2. Matrix
3. EulerAngle

> first line words
***

`<hello world>`

```python
    def add(a,b):
      return a+b
```
