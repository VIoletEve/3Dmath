# 3D-math-foundation

## Notes

***3D数学基础：图形与游戏开发全书总结提炼***
***简介只讨论重点***

## Pages

- 3D变换
 - 设计决策
 - 基础知识
 - 3D向量类
 - MathUtil类
 - 欧拉角类
 - 四元数类
 - 旋转矩阵类
 - 4x3矩阵类
- 几何图元
 - AABB类
 - 三角网格类

***

## 3D变换
### 设计决策

### 3D向量类

-[3D向量类头文件](3Dmath/Vector3.h)
-[3D向量类cpp文件](3Dmath/Vector3.cpp)

***

#### 向量点乘
点乘结果描述了两个向量的相似程度，点乘结果越大，两向量夹角越小，点乘为0时，两向量垂直
点乘<0时，角度为钝角

-向量投影
详情见书本5.10.3节

#### 向量叉乘
得到一个垂直于原来两个向量的向量
叉乘的模长也等于以原来两个向量为边的平行四边形面积

***

### MathUtil类

-[MathUtil类头文件](3Dmath/MathUtil.h)
-[MathUtil类cpp文件](3Dmath/MathUtil.cpp)

#### 重点


```
//将角度限制在-pi到pi的区间
float wrapPi(float theta) {
	theta += kPi;
	theta -= floor(theta * k1Over2Pi) * k2Pi;
	theta -= kPi;
	return theta;
}

```

**和acos(x)函数相同，但如果x超出范围返回最为接近的有效值**
**返回值在0到pi之间**

```
//安全反三角函数
float safeAcos(float x) {
	if (x <= -1.0f) {
		return kPi;
	}
	if (x >= 1.0f) {
		return 0.0f;
	}

	return acos(x);
}
```
***

### 欧拉角类

-[欧拉角类头文件](3Dmath/EulerAngles.h)
-[欧拉角类cpp文件](3Dmath/EulerAngles.cpp)

#### 欧拉角定义

**使用heading-pitch-bank约定**
**欧拉角表示旋转序列，从惯性->物体坐标系**

#### 限制集

```
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
```


#### 四元数->欧拉角 物体->惯性 惯性->物体

根据矩阵->欧拉角公式把欧拉角转为旋转矩阵形式
**cosp=0说明发生了万向锁
**
p=asin(-m23)
h=atan2(m13,m33)
  atan2(-m31,m11)(若cosp=0)
b=atan2(m21,m22)
  0		(若cosp=0)

**

**再从矩阵获取四元数(四元数->矩阵公式)
m23=2yz+2wx
m13=2xz-2wy
m33=1-2x^2-2y^2...
带入得
p=asin(-2(yz+wx))
h=- atan2(xz-wy,1/2-x^2-y^2)
  - atan2(-xz-wy,1/2-y^2-z^2)若cosp=0
**b=- atan2(xy-wz,1/2-x^2-z^2)
  - 0  	(若cosp=0)










