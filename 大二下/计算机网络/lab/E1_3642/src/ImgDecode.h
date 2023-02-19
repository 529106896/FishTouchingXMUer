#pragma once
#include <opencv2/opencv.hpp>
#define Show_Img(src) do\
{\
	cv::imshow("src", src);\
	cv::waitKey();\
}while (0);
namespace ImageDecode
{
	using namespace std;
	using namespace cv;
	struct ImageInfo
	{
		vector<unsigned char> Info;
		uint16_t CheckCode;
		uint16_t FrameBase;
		bool IsStart;
		bool IsEnd;
	};
	constexpr int BytesPerFrame = 3738;
	constexpr int FrameSize = 108;
	constexpr int FrameOutputRate = 10;
	constexpr int SafeAreaWidth = 2;
	constexpr int QrPointSize = 18;
	constexpr int SmallQrPointbias = 6;
	constexpr int RectAreaCount = 7;
	bool Main(Mat& mat, ImageInfo& imageInfo);
}