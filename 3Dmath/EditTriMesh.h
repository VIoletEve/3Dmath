#pragma once

#ifndef __EDITTRIMESH_H_INCLUDED__
#define __EDITTRIMESH_H_INCLUDED__

#include "Vector3.h"
#include "Matrix4x3.h"

class EditTriMesh
{
public:

	//������
	class Vertex {
	public:
		Vertex() { setDefaults(); }
		void setDefaults();

		//3d����
		Vector3 p;
		//uvֵ
		float u, v;
		//���㼶���淨����
		Vector3 normal;
		//���߱���
		int mark;
	};

	//��������
	class Tri {
	public:
		Tri() { setDefaults(); }
		void setDefaults();

		//�涥��
		struct Vert
		{
			int index;
			float u, v;
		};
		Vert v[3];
		//���淨����
		Vector3 normal;

		//����������Ĳ���
		int part;
		//�����б�����
		int material;
		//���߱���
		int mark;
		//�ж��ǲ����˻�������
		bool isDegenerate()const;

		//����δʹ�õĶ�������
		int findVertex(int vertexIndex)const;
	};

	//������
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
		
		//�ж����������Ƿ��غϵ��ݲ�
		float coincidentVertexTolerance;
		//�����νǶ��ݲ�
		float cosOfEdgeAngleTolerance;

		void setEdgeAngleToleranceInDegrees(float degrees);

	};

	EditTriMesh();
	EditTriMesh(const EditTriMesh& x);
	~EditTriMesh();
	//������
	EditTriMesh& operator=(const EditTriMesh& src);

	//��������
	int vertexCount()const { return vCount; }
	int triCount()const { return tCount; }
	int materialCount()const { return mCount; }

	//ͨ��������ȡ��Ӧ�Ķ���
	Vertex& vertex(int vertexIndex);
	const Vertex& vertex(int vertexIndex)const;

	Tri& tri(int triIndex);
	const Tri& tri(int triIndex)const;

	Material& material(int materialIndex);
	const Material& material(int materialIndex)const;

	//��������Ϊ��
	void empty();

	//�����б��С
	void setVertexCount(int vc);
	void setTriCount(int tc);
	void setMaterialCount(int mc);

	//��������λ򶥵����ʣ������¼���Ԫ�ص�����
	int addTri();
	int addTri(const Tri& t);
	int addVertex();
	int addVertex(const Vertex& v);
	int dupVertex(int srcVertexIndex);
	int addMaterial(const Material& m);

	//��������mark����
	void markAllVertices(int mark);
	void markAllTris(int mark);
	void markAllMaterials(int mark);

	//ɾ������
	void deleteVertex(int vertexIndex);
	void deleteTri(int triIndex);
	void deleteMaterial(int materialIndex);
	void deleteUnusedMaterial();
	void deleteMarkedTris(int mark);
	void deleteDegenerateTris();

	//�������������
	void detachAllFaces();

	//�任���ж���
	void transformVertices(const Matrix4x3& m);
	//���������εı��淨����
	void computeOneTriNormal(int triIndex);
	void computeOneTriNormal(Tri& t);
	void computeTriNormals();

	//���㶥�㷨����
	void computeVertexNormals();
	//�Ż�����˳��
	void optimizeVertexOrder(bool removeUnusedVertices);
	//���ݲ�������
	void sortTrisByMaterial();
	//���Ӷ���
	void weldVertices(const OptimationParameters& opt);
	//ȷ������uvֵ��ȷ
	void copyUvsIntoVertices();
	//���������Ż���Ϊ������Ⱦ׼����ģ��
	void optimizeForRendering();

	//���뵼��s3d�ļ�
	bool importS3d(const char* filename, char* returnErrMsg);
	bool exportS3d(const char* filename, char* returnErrMsg);

	//������
	void validityCheck();
	bool validityCheck(char* returnErrMsg);

private:
	//�����б�
	int vAlloc;
	int vCount;
	Vertex* vList;
	int tAlloc;
	int tCount;
	Tri* tList;
	int mCount;
	Material* mList;
	//ʵ��ϸ��
	void construct();
};

#endif // !__EDITTRIMESH_H_INCLUDED__