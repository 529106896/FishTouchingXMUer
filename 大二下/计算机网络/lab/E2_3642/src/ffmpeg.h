#pragma once
#include <cstdlib>
#include <cstring>
#include <cstdio>
namespace FFMPEG
{
	int VideotoImage(const char* videoPath,//��·��ΪvideoPath����Ƶ
		const char* imagePath,             //���浽Ŀ¼imagePath��
		const char* imageFormat);          //���ɺ�׺��ΪimageFormat��֡ͼ��
	int ImagetoVideo(const char* imagePath,//�������ļ��е�·��ΪimagePath
		const char* imageFormat,           //��׺��ΪimageFormat��ͼ��
		const char* videoPath,             //�ϳɵ���Ƶ���浽·��videopath
		unsigned rawFrameRates = 10,       //��ԭͼƬ������Ϊ����֡�ʣ����ʱ��������֡������Դ֡�ʣ�
		unsigned outputFrameRates = 10,    //ʵ�����֡�ʣ��������Դ֡�����֡��С��Դ֡�����֡��
		unsigned kbps = 0);                //֡��Ϊkbps��Ĭ��Ϊ0����ffmpeg�Զ�����֡��
	//��֡��������Ӱ����Ϣ���䣬��ͨ����Ӧ�ó������֡��С��Դ֡�ʵ������
}