#pragma once

#include <Eigen/Core>
#include <iostream>
using namespace std;
#define PI 3.1415927

extern Eigen::Matrix4f mModelView;
extern Eigen::Matrix4f mProjection;
extern Eigen::Matrix4f mViewPort;

//�˺���������Ķ�
void Test()
{
	//����eigen���÷����ɲο���
	//http://eigen.tuxfamily.org/dox/group__QuickRefPage.html
	
	//�����÷�
	Eigen::Matrix4f m;
	m.setZero();
	m(0, 0) = 1;
	m(3, 3) = 1;
	m(1, 1) = 2.3;   m(1, 2) = 0.99;
	m(2, 1) = 1.1;   m(2, 2) = 0;
	cout << "Matrix:" << endl;
	cout << m << endl;

	//�����÷�
	Eigen::Vector4f v;
	v[0] = 1.0;
	v[1] = 2.0;
	v[2] = 3.0;
	v[3] = 1.0;
	v.normalize();//��һ��
	//��һ������Ҫ����Ҫ��������ݾ��������ͨ��ĳ���㷨������������Ҫ��һ����Χ�ڡ�
	//��һ����Ŀ�ļ����֮����ʹ��û�пɱ��Ե����ݱ�þ��пɱ��ԣ�
	//ͬʱ�ֱ�����Ƚϵ���������֮�����Թ�ϵ�����С��ϵ��
	//����Ϊ����ͼ��ԭ��������һ��ͼ������������һ����Ϳ��Ժܷ���ĸ���ͼ�ϵ����λ�õȡ�
	//��һ���ķ�ʽ�ͷ�Χ�����Լ�ȷ��

	//���������������˵Ľ��
	cout << "result:" << endl;
	cout << m * v << endl;
}

//�˺�������Ķ�
vector<Eigen::Vector3f> VertexTransform(vector<Eigen::Vector3f> vertices)
{
	vector<Eigen::Vector3f> rlt(vertices.size());
	Eigen::Vector4f v;

	Eigen::Matrix4f M = mViewPort * mProjection * mModelView;

	for (int i = 0; i < vertices.size(); ++i)
	{
		v[3] = 1.0;
		v.head<3>() = vertices[i];

		v = M * v;
		rlt[i][0] = v[0] / v[3];
		rlt[i][1] = v[1] / v[3];
		rlt[i][2] = v[2] / v[3];
	}
	return rlt;
}

//��x����תangle�Ƕ�
Eigen::Matrix4f myRotateX(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	
	//��������հ״���ɴ˺���

	//m.setIdentity();//���Ӧ��ȥ��
	m(0, 0) = 1.0;
	m(3, 3) = 1.0;
	m(1, 1) = cos(angle);
	m(2, 2) = cos(angle);
	m(2, 1) = sin(angle);
	m(1, 2) = -sin(angle);

	//��������հ״���ɴ˺���

	mModelView *= m;
	//cout << m << endl;
	return m;
}

//��y����תangle�Ƕ�
Eigen::Matrix4f myRotateY(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	
	//��������հ״���ɴ˺���

	//m.setIdentity();//���Ӧ��ȥ��
	m(0, 0) = cos(angle);
	m(3, 3) = 1.0;
	m(1, 1) = 1.0;
	m(2, 2) = cos(angle);
	m(0, 2) = sin(angle);
	m(2, 0) = -sin(angle);
	//m.normalize();
	//��������հ״���ɴ˺���

	mModelView *= m;
	//cout << m << endl;
	return m;
}

//��z����תangle�Ƕ�
Eigen::Matrix4f myRotateZ(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	
	//��������հ״���ɴ˺���

	//m.setIdentity();//���Ӧ��ȥ��
	m(2, 2) = 1.0;
	m(3, 3) = 1.0;
	m(0, 0) = cos(angle);
	m(1, 1) = cos(angle);
	m(0, 1) = -sin(angle);
	m(1, 0) = sin(angle);
	//��������հ״���ɴ˺���

	mModelView *= m;
	//cout << m << endl;
	return m;
}


//ƽ��x��y��z
Eigen::Matrix4f myTranslate(float x, float y, float z)
{
	Eigen::Matrix4f m;
	m.setZero();
	
	//��������հ״���ɴ˺���
	
	//m.setIdentity();//���Ӧ��ȥ��
	m(0, 0) = 1.0;
	m(1, 1) = 1.0;
	m(2, 2) = 1.0;
	m(3, 3) = 1.0;
	m(0, 3) = x;
	m(1, 3) = y;
	m(2, 3) = z;
	//��Sleep������һ���ٶȣ���Ȼת��̫����
	Sleep(3);

	//��������հ״���ɴ˺���

	mModelView *= m;
	//cout << m << endl;
	return m;
}

//����(x,y,z)(ע��:����δ��һ���� ��תangle�Ƕ�
Eigen::Matrix4f myRotate(float angle, float x, float y, float z)
{
	float theta = angle / 180.0 * PI;

	Eigen::Matrix4f m;
	
	//��������հ״���ɴ˺���

	//m.setIdentity();//���Ӧ��ȥ��
	m.setZero();
	m(3, 3) = 1;
	m(0, 0) = x * x + (1 - x * x) * cos(angle);
	m(0, 1) = x * y * (1 - cos(angle)) - z * cos(angle);
	m(0, 2) = x * z * (1 - cos(angle)) + y * sin(angle);
	m(1, 0) = x * y * (1 - cos(angle)) + z * sin(angle);
	m(1, 1) = y * y + (1 - y * y) * cos(angle);
	m(1, 2) = y * z * (1 - cos(angle)) - x * sin(angle);
	m(2, 0) = x * z * (1 - cos(angle)) - y * sin(angle);
	m(2, 1) = y * z * (1 - cos(angle)) + x * sin(angle);
	m(2, 2) = z * z + (1 - z * z) * cos(angle);

	//��������հ״���ɴ˺���

	mModelView *= m;

	return m;
}