#pragma once
#include <cstdlib>
#include <cstring>
#include <cstdio>
namespace FFMPEG
{
	int VideotoImage(const char* videoPath,//将路径为videoPath的视频
		const char* imagePath,             //保存到目录imagePath中
		const char* imageFormat);          //拆解成后缀名为imageFormat的帧图像
	int ImagetoVideo(const char* imagePath,//将所在文件夹的路径为imagePath
		const char* imageFormat,           //后缀名为imageFormat的图像
		const char* videoPath,             //合成的视频保存到路径videopath
		unsigned rawFrameRates = 10,       //将原图片序列视为多少帧率（输出时长等于总帧数除以源帧率）
		unsigned outputFrameRates = 10,    //实际输出帧率（如果大于源帧率则插帧，小于源帧率则掉帧）
		unsigned kbps = 0);                //帧率为kbps，默认为0，即ffmpeg自动决定帧率
	//掉帧将会严重影响信息传输，故通常不应该出现输出帧率小于源帧率的情况。
}