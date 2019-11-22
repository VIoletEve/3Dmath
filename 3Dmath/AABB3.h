#pragma once
#ifndef __AABB3_H_INCLUDE__
#define __AABB3_H_INCLUDE__

#include "Vector3.h"
#include "Matrix4x3.h"
#include <assert.h>

class AABB3
{
public:
	Vector3 min;
	Vector3 max;

	Vector3 size()const { return max - min; }

	float xSize() { return max.x - min.x; }
	float ySize() { return max.y - min.y; }
	float zSize() { return max.z - min.z; }

	Vector3 center()const{ return (max + min) * 0.5f; }

	Vector3 corner(int i)const;

	void empty();

	bool isEmpty()const;

	void add(const Vector3& v);
	void add(const AABB3& box);

	bool contains(const Vector3& v)const;

	void setToTransformedBox(const AABB3& box, const Matrix4x3& m);

	//计算AABB3最近点
	Vector3 closePointTo(const Vector3& v)const;

	//计算射线与AABB3的相交性检测
	float rayInsertect(const Vector3& rayOrg, const Vector3& rayDelta, Vector3* returnNormal)const;
	//计算与圆的相交性检测
	bool intersectsSphere(const Vector3& center, float radius)const;
	//判断AABB在平面的哪一面
	int classifyPlane(const Vector3& n, float d)const;
	//与平面的动态相交性检测
	float intersectPlane(const Vector3& n, float planeD, const Vector3& dir)const;
	 
};
//两个AABB3的静态相交性检测
bool intersectAABBs(const AABB3& box1, const AABB3& box2, AABB3* boxIntersect = 0);
//两个AABB3的动态相交性检测
float intersectMovingAABB(const AABB3& stationaryBox, const AABB3& movingBox, const Vector3& d);

#endif // !__AABB3_H_INCLUDE__