# 3Dmath

## Notes

***3D数学基础：图形与游戏开发全书总结导航***

***只讨论重点***

***
## Pages

- 3D变换
  - 基础知识
  - 3D向量类
  - MathUtil类
  - 欧拉角类
  - 四元数类
  - 旋转矩阵类
  - 4x3矩阵类
- 几何图元
  - AABB类
- 几何检测
  - 三角网格类 
- 图形管道
- 裁剪空间

***

## 3D变换
***

### 基础知识

***

#### 向量点乘

点乘结果描述了两个向量的相似程度，点乘结果越大，两向量夹角越小，点乘为0时，两向量垂直
点乘<0时，角度为钝角

**向量投影**

详情见书本p49

#### 向量叉乘

得到一个垂直于原来两个向量的向量

叉乘的模长也等于以原来两个向量为边的平行四边形面积

***

#### 矩阵

#### 矩阵定义(图形学多用4x3矩阵和3x3矩阵)


      m11  m12  m13          m11  m12  m13

M4x3= m21  m22  m23    M3x3= m21  m22  m23
      
      m31  m32  m33          m31  m32  m33
      
      m41  m42  m43

**行数列数相同的叫方阵**

***Directx使用行向量，OpenGL使用列向量***
***

#### 矩阵线性变换
***


**2D旋转**   

见书p88 公式8.1
***
**3D旋转**

绕坐标轴旋转  见书p90-p91

绕任意轴旋转  见书p94 公式8.5
***

**缩放**

沿任意轴的2d缩放矩阵  p97  公式8.8


沿任意轴缩放  p98  公式8.9

***

**正交投影**

p99-p101

***

**镜像**

使缩放因子为-1，沿通过原点且垂直于n的反射轴来进行镜像变换(n为2d单位向量)

沿任意轴镜像的2D矩阵  p101 公式8.17

沿通过原点且垂直于n的平面来进行镜像变换

沿任意轴镜像的3D矩阵  p102 公式8.18

***

**切变**

p103

***

**线性变换和仿射变换的定义**

如果映射F保持了基本运算：加法和数量乘，那么就可以称该映射为线性的

仿射变换是指线性变换后接着平移。任何线性变换都是仿射变换，但不是所有仿射变换都是线性变换

***

**行列式**

2x2矩阵的行列式  p109  公式9.1

3x3矩阵的行列式  p110  公式9.2

代数余子数  p111  公式9.3

矩阵的行列式的几何解释：

2D中，行列式等于以基向量为两边的平行四边形的有符号面积

3D中，行列式等于以变换后的基向量为三边的平行六面体的有符号体积

如果矩阵行列式为0，那么该矩阵包含投影。如果矩阵行列式为负，那么该矩阵包含镜像

***

#### 矩阵仿射变换

**矩阵的逆(只能用于方阵)**

MM^-1=I(I是单位矩阵)

计算矩阵M的代数余子数矩阵C

标准伴随矩阵adjM是C的转置

M^-1=adjM/|M|

矩阵的逆可以计算矩阵的反向变换，也就是能用于撤销矩阵变换

***

**正交矩阵**

MM^T=I(I是单位矩阵)

M^T=M^-1

平移，旋转，镜像是仅有的正交矩阵

行列式为+-1

***

**4x4矩阵 透视投影**

p128  公式9.13

***

#### 欧拉角

**使用heading-pitch-bank约定**
**欧拉角表示旋转序列，从惯性->物体坐标系**

***

#### 四元数

**定义**

q=[w,v]  q=[w,(x,y,z)]

**旋转**

绕x轴旋转  设p为角度  q=[cosp/2 (sin(p/2),0,0)]

绕y轴旋转  q=[cosp/2 (0,sin(p/2),0)]

绕z轴旋转  q=[cosp/2 (0,0,sin(p/2))]

绕n(任意轴)旋转  p144  公式10.4

**模**

p145  公式10.6

**四元数共轭和逆**

共轭  q=[w -v]=[w (-x,-y,-z)]

逆  q^-1=q/||q||

***

**四元数乘法(叉乘)**

p148  公式10.11,10.12

四元数乘积的模等于模的乘积，这个结论保证了两个单位四元数相乘的结果还是单位四元数

四元数乘积的逆等于各个四元数逆以相反的顺序相乘

[w1 v1][w2 v2]=[w1w2-v1v2 wv2+w2v1+v1v2]


***

**四元数插值-slerp**

p156

**四元数样条-squad**

p158  公式10.20

***

#### 表达形式之间的转化

***

**欧拉角->矩阵**

将欧拉角各个轴的旋转转换为相应的旋转矩阵(惯性->物体)(欧拉角公式明确指明是物体和坐标空间旋转，但我们需要的是变换"点"的矩阵，所以要用相反的旋转量)

将各个轴的旋转矩阵相乘得到惯性->物体坐标空间的旋转矩阵  p161  公式10.21

获取物体->惯性矩阵应该使用惯性->物体旋转矩阵的逆，因为旋转矩阵是正交的，所以矩阵的逆等于矩阵转置

得到物体->惯性旋转矩阵  p162  公式10.22

***

**矩阵->欧拉角**

从公式10.21解得：

p=asin(-m23)  b=atan2(m21,m22)  h=atan2(m13,m33)

如果cosp=0，p=+-90°也就是发生了万向锁,则将所有绕竖直轴的旋转都赋给heading，bank=0，所以b=0,sinb=0，cosb=1，带入公式10.21

h=atan2(-m31,m11)

***

**四元数->矩阵**

利用绕任意轴旋转矩阵  p94 公式8.5   绕任意轴旋转四元数  p144  公式10.4

能构造出一个完整旋转矩阵  p167  公式10.23

***

**矩阵->四元数**

利用四元数->矩阵  公式10.23  计算对角线元素的和/差的平方根解得  见书p168

**欧拉角->四元数**

设欧拉角变量为h,p,b，分别对应绕y，x，z轴旋转的四元数，和欧拉角->矩阵中一样用负旋转量

将hpb相乘连接得到惯性->物体四元数  p171  公式10.24

共轭得到物体->惯性四元数  p171  公式10.25

***

**四元数->欧拉角**

根据(矩阵->欧拉角公式)把欧拉角转为旋转矩阵形式

再从矩阵获取四元数(四元数->矩阵公式)

带入得  p172(惯性->物体)

要从物体->惯性四元数获取欧拉角只需将四元数共轭

***

### 3D向量类

-[3D向量类头文件](3Dmath/Vector3.h)

-[3D向量类cpp文件](3Dmath/Vector3.cpp)

***


### MathUtil类

-[MathUtil类头文件](3Dmath/MathUtil.h)

-[MathUtil类cpp文件](3Dmath/MathUtil.cpp)

#### 万向锁


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


### 四元数类

-[四元数头文件](3Dmath/Quaternion.h)

-[四元数cpp文件](3Dmath/Quaternion.cpp)


***

### 旋转矩阵类

-[旋转矩阵头文件](3Dmath/RotationMatrix.h)

-[旋转矩阵cpp文件](3Dmath/RotationMatrix.cpp)


***

### 4x3矩阵类

-[4x3矩阵头文件](3Dmath/Matrix4x3.h)

-[4x3矩阵cpp文件](3Dmath/Matrix4x3.cpp)

***

矩阵的刚体变换

```
//从父->局部(世界->物体)变换矩阵中提取物体的位置
//矩阵的刚体变换
Vector3 getPositionFromParentToLocalMatrix(const Matrix4x3& m) {
	return Vector3{
		-(m.tx * m.m11 + m.ty * m.m12 + m.tz * m.m13),
		-(m.tx * m.m21 + m.ty * m.m22 + m.tz * m.m23),
		-(m.tx * m.m31 + m.ty * m.m32 + m.tz * m.m33)
	};
}
```

***

## 几何图元

### 射线

p(t)=p0+td  p0是射线起点坐标，t是长度,d是方向单位向量

### 直线

ax+by=d  p×n=d  向量n=[a,b]

### 球
||p-c||=r  c表示球心，r表示半径


### 矩形边界框(AABB)

AABB内的点都满足Xmin<X<Xmax,Ymin<Y<Ymax,Zmin<Z<Zmax,

所以AABB类的定义就是Pmin=[Xmin,Ymin,Zmin]   Pmax=[Xmax,Ymax,Zmax]

中心点c=(Pmin+Pmax)/2

"尺寸向量"(包含矩形边界框的长宽高)s=Pmax-Pmin

变换AABB，我们只要求变换后的Pmin和Pmax就可以了


### 平面

p×n=d   n是法向量  d是原点到平面的距离

用三个点定义平面(p1,p2,p3)

按顺时针构造向量e1(p1->p2),e3(p2->p3),n是平面的法向量

e1=p2-p1,e3=p3-p2,n=(e3xe1)/||e3xe1||

点到平面的距离  a=qxn-d  p242  公式12.14


### 三角形

三个顶点(v1,v2,v3)

e1=v3-v2  e2=v1-v3  e3=v2-v1  l1=||e1||  l2=||e2||   l3=||e3||

三角形边长  p=l1+l2+l3

**三角形面积**

海伦公式

s=(l1+l2+l3)/2=p/2

A=s(s-l1)(s-l2)(s-l3)的平方根

更简单的可以用向量叉乘的模来得到以e1和e2为边的平行四边形面积

A=||e1xe2||/2

***

### 重心坐标空间

```
//计算3d重心坐标，v是三角形顶点，要求重心坐标的点p，b是保存的重心坐标
bool computeBarycentricCoords3d(const Vector3 v[3], const Vector3& p, float b[3]) {
	//计算两个边向量
	Vector3 d1 = v[1] - v[0];
	Vector3 d2 = v[2] - v[1];
	//用叉乘计算法向量(无需正则化)
	Vector3 n = crossProduct(d1, d2);

	//判断法向量中占优势的轴，选择投影平面
	float u1, u2, u3, u4;
	float v1, v2, v3, v4;

	if ((fabs(n.x) >= fabs(n.y)) && (fabs(n.x) >= fabs(n.z))) {
		//抛弃x，向yz平面投影
		u1 = v[0].y - v[2].y;
		u2 = v[1].y - v[2].y;
		u3 = p.y - v[0].y;
		u4 = p.y - v[2].y;

		v1 = v[0].z - v[2].z;
		v2 = v[1].z - v[2].z;
		v3 = p.z - v[0].z;
		v4 = p.z - v[2].z;

	}
	else if (fabs(n.y) >= fabs(n.z)) {
		//抛弃y，向xz平面投影
		u1 = v[0].z - v[2].z;
		u2 = v[1].z - v[2].z;
		u3 = p.z - v[0].z;
		u4 = p.z - v[2].z;

		v1 = v[0].x - v[2].x;
		v2 = v[1].x - v[2].x;
		v3 = p.x - v[0].x;
		v4 = p.x - v[2].x;
	}
	else {
		u1 = v[0].x - v[2].x;
		u2 = v[1].x - v[2].x;
		u3 = p.x - v[0].x;
		u4 = p.x - v[2].x;

		v1 = v[0].y - v[2].y;
		v2 = v[1].y - v[2].y;
		v3 = p.y - v[0].y;
		v4 = p.y - v[2].y;

	}

	//计算分母,并判断是否合法
	float denom = v1 * u2 - v2 * u1;
	if (denom == 0.0f) {
		//退化三角形-面积为0的三角形
		return false;
	}
	//计算重心坐标
	float oneOverDenom = 1.0f / denom;
	b[0] = (v4 * u2 - v2 * u4) * oneOverDenom;
	b[1] = (v1 * u3 - v3 * u1) * oneOverDenom;
	b[2] = 1.0f - b[0] - b[1];

	return true;

}
```

***

### 特殊点
- 重点
- 内心
- 外心

重心是三角形的最佳平衡点，它是三角形三条中线的交点

Cgrav=(v1+v2+v3)/3

重心坐标(1/3,1/3,1/3)

内心是到三角形各边相等的点，它是三角形内接圆的圆心

CIn=(l1v1+l2v2+l3v3)/p   p是三角形周长l1+l2+l3

内心的重心坐标为(l1/p,l2/p,l3/p)

内切圆半径rIn=A/p

外心是三角形中到各顶点距离相等的点，它是三角形外接圆的圆心

见p254


### 多边形

3D中用角度和判断凸多边形

```

bool isConvex(int n,const Vector3 vl[]){
	float angleSum=0.0f;

	//遍历多边形顶点，将角度相加
	for(int i=0;i!=n;++i){
		//计算边向量，注意第一个和最后一个顶点
		Vector3 e1;
		if(i==0){
			e1=vl[n-1]-vl[i];
		}else{
			e1=vl[i-1]-vl[i];
		}
		Vector3 e2;
		if(i==n-1){
			e2=vl[0]-vl[i];
		}else{
			e2=vl[i+1]-vl[i];
		}

		//标准化计算点乘
		e1.normalize();
		e2.normalize();

		float dot=e1*e2;

		//用安全反三角函数得到角度
		float theta=safeAcos(dot);

		angleSum+=theta;
	}

	//计算内角和
	float convexAngleSum=(float)(n-2)*kpi;

	if(angleSum<convexAngleSum-(float)n*0.0001f){
		//凹多边形
		return false
	}

	//凸多边形
	return true;

}

```

***
## 几何检测

### AABB类

-[AABB类头文件](3Dmath/AABB3.h)

-[AABB类cpp文件](3Dmath/AABB3.cpp)



**AABB和平面的相交性检测**

**静态检测**

判断AABB在平面的哪一面或者相交，只需求向量法向量n和AABB的顶点点积

只需要求最小点积和最大点积，如果n.x>0,那么和min.x得到最小点积，和max.x得到最大点积，若n.x<0则相反

求出每个分量的最小最大点积加起来则得到最小点积和最大点积

运用向量投影的知识我们知道，如果求出的最小点积都大于d(原点到平面的距离),那么AABB都在平面正面

如果求出的最大点积都小于d，那么AABB都在平面反面，否则相交

```
//判断AABB在平面的哪一面
int AABB3::classifyPlane(const Vector3& n, float d)const {
	//求最小点乘和最大点乘也就是距离
	float minD, maxD;
	//如果法向量x轴分量>0，和min.x获得最小点乘的x分量，和max.x获得最大点乘的x分量
	if (n.x > 0.0f) {
		minD = n.x * min.x; maxD = n.x * max.x;

	}
	else {
		minD = n.x * max.x; maxD = n.x * min.x;
	}
	if (n.y > 0.0f) {
		minD += n.y * min.y; maxD += n.y * max.y;

	}
	else {
		minD += n.y * max.y; maxD += n.y * min.y;
	}
	if (n.z > 0.0f) {
		minD += n.z * min.z; maxD += n.z * max.z;

	}
	else {
		minD += n.z * max.z; maxD += n.z * min.z;
	}

	//如果最小距离都大于d，则全在平面正面
	if (minD >= d) {
		return +1;
	}
	//如果最大距离都小于d，则全在平面背面
	if (maxD <= d) {
		return -1;
	}
	//否则，相交
	return 0;
}
```

**动态检测**

先用点乘求出是否是与平面正面的相交

再用最近点带入射线与平面相交的公式，得出是否相交，如果没相交返回距离

```

//与平面的动态相交性检测，dir是AABB的移动方向
//把平面当做静止，只探索与平面正面的相交
float AABB3::intersectPlane(const Vector3& n, float planeD, const Vector3& dir)const {
	//检测正则化
	assert(fabs(n * n - 1.0f) < .0001f);
	assert(fabs(dir * dir - 1.0f) < .0001f);

	const float kNoIntersection = 1e30f;
	//计算夹角，确保是往平面正面移动
	float dot = n * dir;
	//如果大于0，说明是锐角与平面法向量同一方向，这样说明不会相交或者与平面背面相交
	if (dot >= 0.0f) {
		return kNoIntersection;
	}
	//求最小最大点乘，也就是距离
	float minD, maxD;
	if (n.x > 0.0f) {
		minD = n.x * min.x; maxD = n.x * max.x;
	}
	else {
		minD = n.x * max.x; maxD = n.x * min.x;
	}
	if (n.y > 0.0f) {
		minD += n.y * min.y; maxD += n.y * max.y;

	}
	else {
		minD += n.y * max.y; maxD += n.y * min.y;
	}
	if (n.z > 0.0f) {
		minD += n.z * min.z; maxD += n.z * max.z;

	}
	else {
		minD += n.z * max.z; maxD += n.z * min.z;
	}
	//在平面背面不考虑
	if (maxD <= planeD) {
		return kNoIntersection;
	}
	//将最近的点带入标准射线方程(利用射线与平面相交性公式)
	float t = (planeD - minD) / dot;
	//检测是否已经穿过
	if (t < 0.0f) {
		return 0.0f;
	}
	//返回。如果结果大于1，则没有及时到达平面，需要调用者进行检查
	return t;
}

```

**AABB与AABB的动态检测

```
//两个AABB3的动态相交性检测,如果返回值>1则未相交
float intersectMovingAABB(const AABB3& stationaryBox, const AABB3& movingBox, const Vector3& d) {

	const float kNoIntersection = 1e30f;
	//初始化时间区间,以包含需要考虑的全部时间段
	float tEnter = 0.0f;
	float tLeave = 1.0f;
	//如果在x轴上的位移为0，则检测x分量是否相交
	if (d.x == 0.0f) {

		if(
			(stationaryBox.min.x>=movingBox.max.x)||(stationaryBox.max.x<=movingBox.min.x)
			)
		{
			return kNoIntersection;
		}

	}
	else
	{
		float oneOverD = 1.0f / d.x;

		float xEnter = (stationaryBox.min.x - movingBox.max.x) * oneOverD;
		float xLeave = (stationaryBox.max.x - movingBox.min.x) * oneOverD;

		if (xEnter > xLeave) {
			swap(xEnter, xLeave);
		}

		if (xEnter > tEnter)tEnter = xEnter;
		if (xLeave < tLeave)tLeave = xLeave;

		if (tEnter > tLeave) {
			return kNoIntersection;
		}
	}

	if (d.y == 0.0f) {

		if (
			(stationaryBox.min.y >= movingBox.max.y) || (stationaryBox.max.y <= movingBox.min.y)
			)
		{
			return kNoIntersection;
		}

	}
	else
	{
		float oneOverD = 1.0f / d.y;

		float yEnter = (stationaryBox.min.y - movingBox.max.y) * oneOverD;
		float yLeave = (stationaryBox.max.y - movingBox.min.y) * oneOverD;

		if (yEnter > yLeave) {
			swap(yEnter, yLeave);
		}

		if (yEnter > tEnter)tEnter = yEnter;
		if (yLeave < tLeave)tLeave = yLeave;

		if (tEnter > tLeave) {
			return kNoIntersection;
		}
	}

	if (d.z == 0.0f) {

		if (
			(stationaryBox.min.z >= movingBox.max.z) || (stationaryBox.max.z <= movingBox.min.z)
			)
		{
			return kNoIntersection;
		}

	}
	else
	{
		float oneOverD = 1.0f / d.z;

		float zEnter = (stationaryBox.min.z - movingBox.max.z) * oneOverD;
		float zLeave = (stationaryBox.max.z - movingBox.min.z) * oneOverD;

		if (zEnter > zLeave) {
			swap(zEnter, zLeave);
		}

		if (zEnter > tEnter)tEnter = zEnter;
		if (zLeave < tLeave)tLeave = zLeave;

		if (tEnter > tLeave) {
			return kNoIntersection;
		}
	}

	return tEnter;
}
```
***
## 三角网格类

-[三角网格类头文件](3Dmath/EditTriMesh.h)

***

## 图形管道(流水线)
- 建立场景
- 可见性检测
- 设置物体级的渲染状态
- 几何体的生成与提交
- 变换与光照
- 背面剔除与裁剪
- 投影到屏幕空间
- 光栅化
- 像素着色

***

### 裁剪空间

OpenGL风格的DIP矩阵  p329  公式15.4

DirectX风格的DIP矩阵  p329  公式15.5

***


