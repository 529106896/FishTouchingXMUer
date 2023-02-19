#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <iostream>
using namespace std;
#define PI 3.1415927

extern Eigen::Matrix4f mModelView;
extern Eigen::Matrix4f mProjection;
extern Eigen::Matrix4f mViewPort;


void Test()
{
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

	//输出矩阵与向量相乘的结果
	cout << "result:" << endl;
	cout << m * v << endl;
}

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

Eigen::Matrix4f myLookAt(float ex, float ey, float ez, float atx, float aty, float atz, float upx, float upy, float upz)
{
	Eigen::Matrix4f m;
	m.setZero();

	//gluLookAt();
	//请在下面空白处完成此函数

	float fx = atx - ex;
	float fy = atx - ey;
	float fz = atz - ez;
	float rlf = 1.0 / sqrt(fx * fx + fy * fy + fz * fz);
	fx *= rlf;
	fy *= rlf;
	fz *= rlf;
	
	float sx = fy * upz - fz * upy;
	float sy = fz * upx - fx * upz;
	float sz = fx * upy - fy * upx;
	float rls = 1.0 / sqrt(sx * sx + sy * sy + sz * sz);
	sx *= rls;
	sy *= rls;
	sz *= rls;

	float ux = sy * fz - sz * fy;
	float uy = sz * fx - sx * fz;
	float uz = sx * fy - sy * fx;

	m(0,0) = sx; m(0,1) = ux; m(0,2) = -fx;
	m(1,0) = sy; m(1,1) = uy; m(1,2) = -fy;
	m(2,0) = sz; m(2,1) = uz; m(2,2) = -fz;
	m(3,3) = 1;

	//请在上面空白处完成此函数

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateX(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	float costheta = cos(theta);
	float sintheta = sin(theta);
	m(0, 0) = 1;
	m(3, 3) = 1;
	m(1, 1) = costheta;   m(1, 2) = -sintheta;
	m(2, 1) = sintheta;   m(2, 2) = costheta;

	mModelView *= m;
	return m;
}

Eigen::Matrix4f myRotateY(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	float costheta = cos(theta);
	float sintheta = sin(theta);
	m(1, 1) = 1;
	m(3, 3) = 1;
	m(0, 0) = costheta;   m(0, 2) = sintheta;
	m(2, 0) = -sintheta;   m(2, 2) = costheta;

	mModelView *= m;
	//cout << m << endl;
	return m;
}

Eigen::Matrix4f myRotateZ(float angle)
{
	float theta = angle / 180.0 * PI;
	Eigen::Matrix4f m;
	m.setZero();
	float costheta = cos(theta);
	float sintheta = sin(theta);
	m(2, 2) = 1;
	m(3, 3) = 1;
	m(0, 0) = costheta;   m(0, 1) = -sintheta;
	m(1, 0) = sintheta;   m(1, 1) = costheta;

	mModelView *= m;
	//cout << m << endl;
	return m;
}


Eigen::Matrix4f myTranslate(float x, float y, float z)
{
	Eigen::Matrix4f m;
	m.setZero();
	m(0, 0) = 1;
	m(1, 1) = 1;
	m(2, 2) = 1;
	m(3, 3) = 1;

	m(0, 3) = x;
	m(1, 3) = y;
	m(2, 3) = z;

	mModelView *= m;

	//cout << m << endl;
	return m;
}

Eigen::Matrix4f myRotate(float angle, float x, float y, float z)
{
	float theta = angle / 180.0 * PI;

	Eigen::Matrix4f m;

	m.setIdentity();//To be modified

	mModelView *= m;

	return m;
}

Eigen::Matrix4f myFrustum(float l, float r, float b, float t, float n, float f)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数

	m(0, 0) = 2 * n / (r - l);
	m(1, 1) = 2 * n / (t - b);
	m(0, 2) = (r + l) / (r - l);
	m(1, 2) = (t + b) / (t - b);
	m(2, 2) = (-1) * ((f + n) / (f - n));
	m(3, 2) = -1;
	m(2, 3) = (-1) * (2 * f * n) / (f - n);


	//请在上面空白处完成此函数

	mProjection *= m;
	return m;
}

Eigen::Matrix4f myOrtho(float l, float r, float b, float t, float n, float f)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数

	m(0, 0) = 2 / (r - l);
	m(1, 1) = 2 / (t - b);
	m(2, 2) = (-2) / (f - n);
	m(0, 3) = (-1) * (r + l) / (r - l);
	m(1, 3) = (-1) * (t + b) / (t - b);
	m(2, 3) = (-1) * (f + n) / (f - n);
	m(3, 3) = 1;

	//请在上面空白处完成此函数

	mProjection *= m;

	return m;
}

Eigen::Matrix4f myViewPort(float x, float y, float w, float h)
{
	Eigen::Matrix4f m;
	m.setZero();

	//请在下面空白处完成此函数


	float myfar = -1.0;
	float mynear = 1.0;
	float surfaceHeight = 500;
	float sx = w / 2.0;
	float ox = sx + x;
	float sy = h / 2.0;
	float oy = sy + surfaceHeight - h - y;
	float A = (myfar - mynear) / 2.0;
	float B = (myfar + mynear) / 2.0;
	m(0, 0) = sx;
	m(0, 3) = ox;
	m(1, 1) = -sy;
	m(1, 3) = oy;
	m(2, 2) = A;
	m(2, 3) = B;
	m(3, 3) = 1.0;


	//请在上面空白处完成此函数

	mViewPort = m;

	return m;
}