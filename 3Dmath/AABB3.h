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

	//����AABB3�����
	Vector3 closePointTo(const Vector3& v)const;

	//����������AABB3���ཻ�Լ��
	float rayInsertect(const Vector3& rayOrg, const Vector3& rayDelta, Vector3* returnNormal)const;
	//������Բ���ཻ�Լ��
	bool intersectsSphere(const Vector3& center, float radius)const;
	//�ж�AABB��ƽ�����һ��
	int classifyPlane(const Vector3& n, float d)const;
	//��ƽ��Ķ�̬�ཻ�Լ��
	float intersectPlane(const Vector3& n, float planeD, const Vector3& dir)const;
	 
};
//����AABB3�ľ�̬�ཻ�Լ��
bool intersectAABBs(const AABB3& box1, const AABB3& box2, AABB3* boxIntersect = 0);
//����AABB3�Ķ�̬�ཻ�Լ��
float intersectMovingAABB(const AABB3& stationaryBox, const AABB3& movingBox, const Vector3& d);

#endif // !__AABB3_H_INCLUDE__