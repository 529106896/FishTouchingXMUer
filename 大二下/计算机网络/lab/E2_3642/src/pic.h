#pragma once
#include <opencv.hpp>
#include <cstdio>

namespace ImgParse
{
	using namespace cv;

	using namespace std;

	namespace QrcodeParse
	{

		struct ParseInfo;

		double Cal3NumVariance(const int a, const int b, const int c);

		bool IsQrBWRateLegal(const float rate);

		bool BWRatePreprocessing(Mat& image, vector<int>& vValueCount);

		bool IsQrBWRateXLabel(Mat& image);

		bool IsQrBWRate(Mat& image);

		bool IsQrSizeLegal(const Size2f& qrSize, const Size2f&& imgSize);

		bool IsQrPoint(const vector<Point>& contour, const Mat& img);

		Mat ImgPreprocessing(const Mat& srcImg);

		bool ScreenQrPoint(const Mat& srcImg, vector<vector<Point>>& qrPoints);

		bool isRightAngleExist(const Point& point0, const Point& point1, const Point& point2);

		bool DumpExcessQrPoint(vector<vector<Point>>& qrPoints);

		void AdjustPointsOrder(vector<vector<Point>>& src3Points);

		bool Main(const Mat& srcImg, vector<vector<Point>>& qrPoints);

		bool Main(const Mat& srcImg, Mat& disImg, vector<ParseInfo>& Points3Info);

		void __DisPlay(const char* ImgPath);

		void __DisPlay2(const char* ImgPath);

		void __DisPlay3(const char* ImgPath);
	}
	Mat Rotation_90(const Mat& srcImg);

	Point2f CalRectCenter(const vector<Point>& contours);

	bool IsClockWise(const Point& basePoint, const Point& point1, const Point& point2);

	float Cal3PointAngle(const Point& point0, const Point& point1, const Point& point2);

	Mat CropRect(const Mat& srcImg, const RotatedRect& rotatedRect);

	float distance(const Point2f& a, const Point2f& b);

	Point CalForthPoint(const Point& poi0, const Point& poi1, const Point& poi2);

	pair<float, float> CalExtendVec(const Point2f& poi0, const Point2f& poi1, const Point2f& poi2, float bias);

	Mat CropParallelRect(const Mat& srcImg, const vector<Point2f>& srcPoints, Size size);

	bool isRightlAngle(float angle);

	bool IsQrTypeRateLegal(float rate);

	bool isLegalDistanceRate(float rate);

	bool FindForthPoint(vector<QrcodeParse::ParseInfo>& PointsInfo);

	bool Main(const Mat& srcImg, Mat& disImg);

	void __DisPlay(const char* ImgPath);

	void Resize(Mat& mat);

}