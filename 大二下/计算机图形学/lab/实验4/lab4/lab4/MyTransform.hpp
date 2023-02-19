#pragma once

#include <Eigen/Core>
#include <iostream>
using namespace std;
#define PI 3.1415927

extern Eigen::Matrix4f mModelView;
extern Eigen::Matrix4f mProjection;
extern Eigen::Matrix4f mViewPort;

//此函数可随意改动
void Test()
{
	//关于eigen的用法，可参考：
	//http://eigen.tuxfamily.org/dox/group__QuickRefPage.html
	
	//矩阵用法
	Eigen::Matrix4f m;
	m.setZero();
	m(0, 0) = 1;
	m(3, 3) = 1;
	m(1, 1) = 2.3;   m(1, 2) = 0.99;
	m(2, 1) = 1.1;   m(2, 2) = 0;
	cout << "Matrix:" << endl;
	cout << m << endl;

	//向量用法
	Eigen::Vector4f v;
	v[0] = 1.0;
	v[1] = 2.0;
	v[2] = 3.0;
	v[3] = 1.0;
	v.normalize();//归一化
	//归一化就是要把需要处理的数据经过处理后（通过某种算法）限制在你需要的一定范围内。
	//归一化的目的简而言之，是使得没有可比性的数据变得具有可比性，
	//同时又保持相比较的两个数据之间的相对关系，如大小关系；
	//或是为了作图，原来很难在一张图上作出来，归一化后就可以很方便的给出图上的相对位置等。
	//归一化的方式和范围可以自己确定

	//输出矩阵与向量相乘的结果
	cout << "result:" << endl;
	cout << m * v << endl;
}

//此函数不许改动
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

//绕x轴旋转angle角度
Eigen::Matrix4f myRotateX(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	
	//请在下面空白处完成此函数

	//m.setIdentity();//这句应该去掉
	m(0, 0) = 1.0;
	m(3, 3) = 1.0;
	m(1, 1) = cos(angle);
	m(2, 2) = cos(angle);
	m(2, 1) = sin(angle);
	m(1, 2) = -sin(angle);

	//请在上面空白处完成此函数

	mModelView *= m;
	//cout << m << endl;
	return m;
}

//绕y轴旋转angle角度
Eigen::Matrix4f myRotateY(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	
	//请在下面空白处完成此函数

	//m.setIdentity();//这句应该去掉
	m(0, 0) = cos(angle);
	m(3, 3) = 1.0;
	m(1, 1) = 1.0;
	m(2, 2) = cos(angle);
	m(0, 2) = sin(angle);
	m(2, 0) = -sin(angle);
	//m.normalize();
	//请在上面空白处完成此函数

	mModelView *= m;
	//cout << m << endl;
	return m;
}

//绕z轴旋转angle角度
Eigen::Matrix4f myRotateZ(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	
	//请在下面空白处完成此函数

	//m.setIdentity();//这句应该去掉
	m(2, 2) = 1.0;
	m(3, 3) = 1.0;
	m(0, 0) = cos(angle);
	m(1, 1) = cos(angle);
	m(0, 1) = -sin(angle);
	m(1, 0) = sin(angle);
	//请在上面空白处完成此函数

	mModelView *= m;
	//cout << m << endl;
	return m;
}


//平移x、y、z
Eigen::Matrix4f myTranslate(float x, float y, float z)
{
	Eigen::Matrix4f m;
	m.setZero();
	
	//请在下面空白处完成此函数
	
	//m.setIdentity();//这句应该去掉
	m(0, 0) = 1.0;
	m(1, 1) = 1.0;
	m(2, 2) = 1.0;
	m(3, 3) = 1.0;
	m(0, 3) = x;
	m(1, 3) = y;
	m(2, 3) = z;
	//用Sleep来控制一下速度，不然转的太快了
	Sleep(3);

	//请在上面空白处完成此函数

	mModelView *= m;
	//cout << m << endl;
	return m;
}

//绕轴(x,y,z)(注意:可能未归一化） 旋转angle角度
Eigen::Matrix4f myRotate(float angle, float x, float y, float z)
{
	float theta = angle / 180.0 * PI;

	Eigen::Matrix4f m;
	
	//请在下面空白处完成此函数

	//m.setIdentity();//这句应该去掉
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

	//请在上面空白处完成此函数

	mModelView *= m;

	return m;
}