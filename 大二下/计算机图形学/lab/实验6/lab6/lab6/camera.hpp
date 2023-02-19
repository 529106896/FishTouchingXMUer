#pragma once
#include "ray.hpp"
#include <Eigen/Core>
using namespace Eigen;

class Camera
{
public:
	Camera()
	{
		//ע�⣺����Ϊ�˷��㣬ֱ�Ӱ��⼸������д����
		_origin = Vector3f(0, 0, 0);
		_lower_left_corner = Vector3f(-2.0, -1.5, -1.0);
		_horizontal = Vector3f(4.0, 0.0, 0.0);
		_vetical = Vector3f(0.0, 3.0, 0.0);
	}

	Ray GenerateRay(float u, float v)
	{
		//��ĵ��˺�����ʹ��������ȷ�Ĺ���
		return Ray(_origin, _lower_left_corner + u * _horizontal + v * _vetical - _origin);
	}

	Vector3f _origin;//�������
	Vector3f _lower_left_corner;//����ƽ�����½�
	Vector3f _horizontal;//����ƽ���ˮƽ������ע�����ﲻ�ǹ�һ�����������Ǵ����½�ָ�����Ͻǵ�����
	Vector3f _vetical;//����ƽ�����ֱ������ע�����ﲻ�ǹ�һ�����������Ǵ����½�ָ�����½ǵ�����
};