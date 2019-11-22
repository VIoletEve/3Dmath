#pragma once

#ifndef __EDITTRIMESH_H_INCLUDED__
#define __EDITTRIMESH_H_INCLUDED__

#include "Vector3.h"
#include "Matrix4x3.h"

class EditTriMesh
{
public:

	//顶点类
	class Vertex {
	public:
		Vertex() { setDefaults(); }
		void setDefaults();

		//3d坐标
		Vector3 p;
		//uv值
		float u, v;
		//顶点级表面法向量
		Vector3 normal;
		//工具变量
		int mark;
	};

	//三角形类
	class Tri {
	public:
		Tri() { setDefaults(); }
		void setDefaults();

		//面顶点
		struct Vert
		{
			int index;
			float u, v;
		};
		Vert v[3];
		//表面法向量
		Vector3 normal;

		//属于网格的哪部分
		int part;
		//材质列表索引
		int material;
		//工具变量
		int mark;
		//判断是不是退化三角形
		bool isDegenerate()const;

		//返回未使用的顶点索引
		int findVertex(int vertexIndex)const;
	};

	//材质类
	class Material {
	public:
		Material() { setDefaults(); }
		void setDefaults();

		char diffuseTextureName[256];

		int mark;
	};

	class OptimationParameters {
	public:
		OptimationParameters() { setDefaults(); }
		void setDefaults();
		
		//判断两个顶点是否重合的容差
		float coincidentVertexTolerance;
		//三角形角度容差
		float cosOfEdgeAngleTolerance;

		void setEdgeAngleToleranceInDegrees(float degrees);

	};

	EditTriMesh();
	EditTriMesh(const EditTriMesh& x);
	~EditTriMesh();
	//网格复制
	EditTriMesh& operator=(const EditTriMesh& src);

	//返回数量
	int vertexCount()const { return vCount; }
	int triCount()const { return tCount; }
	int materialCount()const { return mCount; }

	//通过索引获取相应的对象
	Vertex& vertex(int vertexIndex);
	const Vertex& vertex(int vertexIndex)const;

	Tri& tri(int triIndex);
	const Tri& tri(int triIndex)const;

	Material& material(int materialIndex);
	const Material& material(int materialIndex)const;

	//重置网格为空
	void empty();

	//设置列表大小
	void setVertexCount(int vc);
	void setTriCount(int tc);
	void setMaterialCount(int mc);

	//添加三角形或顶点或材质，返回新加入元素的索引
	int addTri();
	int addTri(const Tri& t);
	int addVertex();
	int addVertex(const Vertex& v);
	int dupVertex(int srcVertexIndex);
	int addMaterial(const Material& m);

	//设置所有mark变量
	void markAllVertices(int mark);
	void markAllTris(int mark);
	void markAllMaterials(int mark);

	//删除操作
	void deleteVertex(int vertexIndex);
	void deleteTri(int triIndex);
	void deleteMaterial(int materialIndex);
	void deleteUnusedMaterial();
	void deleteMarkedTris(int mark);
	void deleteDegenerateTris();

	//逐个分离所有面
	void detachAllFaces();

	//变换所有顶点
	void transformVertices(const Matrix4x3& m);
	//计算三角形的表面法向量
	void computeOneTriNormal(int triIndex);
	void computeOneTriNormal(Tri& t);
	void computeTriNormals();

	//计算顶点法向量
	void computeVertexNormals();
	//优化顶点顺序
	void optimizeVertexOrder(bool removeUnusedVertices);
	//根据材质排序
	void sortTrisByMaterial();
	//焊接顶点
	void weldVertices(const OptimationParameters& opt);
	//确保顶点uv值正确
	void copyUvsIntoVertices();
	//进行所有优化，为快速渲染准备好模型
	void optimizeForRendering();

	//导入导出s3d文件
	bool importS3d(const char* filename, char* returnErrMsg);
	bool exportS3d(const char* filename, char* returnErrMsg);

	//调试用
	void validityCheck();
	bool validityCheck(char* returnErrMsg);

private:
	//网格列表
	int vAlloc;
	int vCount;
	Vertex* vList;
	int tAlloc;
	int tCount;
	Tri* tList;
	int mCount;
	Material* mList;
	//实现细节
	void construct();
};

#endif // !__EDITTRIMESH_H_INCLUDED__