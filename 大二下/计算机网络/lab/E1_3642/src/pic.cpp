#include"pic.h"
//����ļ�������Ƶ�в�����֡���ض�λ��ԭʼ��ά��
// ��������������������debug
//#define FIND_QRPOINT_DEBUG 1
//#define CropParallelRect_DEBUG 1
#define Show_Img(src) do\
{\
	imshow("DEBUG", src);\
	waitKey();\
}while (0);
namespace ImgParse
{
	constexpr float MinRightAngel = 75.0, MaxRightAngel = 105.0;
	constexpr float MaxQrTypeRate = 2.2, minQrTypeRate = 1.8;
	constexpr float MaxDistanceRate = 1.1, minDistanceRate = 0.9;
	Mat Rotation_90(const Mat& srcImg)
	{   //����ָ������90�Ⱥ�Ŀ���
		Mat tempImg;
		transpose(srcImg, tempImg);
		flip(tempImg, tempImg, 1);
		return tempImg;
	}
	Point2f CalRectCenter(const vector<Point>& contours)
	{
		//�ҵ�����ȡ���������ĵ�
		//����ȡ������С�����εı߽���ÿ���ܳ���������ȡһ��������꣬������ȡ�ĸ����ƽ�����꣨��ΪС�����εĴ������ģ�
		float centerx = 0, centery = 0;
		int n = contours.size();
		centerx = (contours[n / 4].x + contours[n * 2 / 4].x + contours[3 * n / 4].x + contours[n - 1].x) / 4;
		centery = (contours[n / 4].y + contours[n * 2 / 4].y + contours[3 * n / 4].y + contours[n - 1].y) / 4;
		return Point2f(centerx, centery);
	}
	bool IsClockWise(const Point& basePoint, const Point& point1, const Point& point2)
	{   //�ж�point1��point2��˳��ʱ���ϵ
		float ax = point1.x - basePoint.x, ay = point1.y - basePoint.y;
		float bx = point2.x - basePoint.x, by = point2.y - basePoint.y;
#ifdef FIND_QRPOINT_DEBUG
		puts(((ax * by - bx * ay) > 0) ? "ClockWise" : "Anti-ClockWise");
#endif 
		return (ax * by - bx * ay) > 0;
		//�����2λ�ڵ�1��˳ʱ�뷽�򣬷����棬���򷵻ؼ�
	}
	float Cal3PointAngle(const Point& point0, const Point& point1, const Point& point2)
	{
		float dx1 = point1.x - point0.x, dy1 = point1.y - point0.y;
		float dx2 = point2.x - point0.x, dy2 = point2.y - point0.y;
		return acos((dx1 * dx2 + dy1 * dy2) / sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) + 1e-10f)) * 180.0f / 3.141592653f;
	}
	Mat CropRect(const Mat& srcImg, const RotatedRect& rotatedRect)
	{   //��ͼ���вü���һ�����Σ��ɴ��Ƕȣ�
		cv::Mat srcPoints, disImg;
		boxPoints(rotatedRect, srcPoints);//�õ��þ�����ĵ�
		vector<Point2f> dis_points =
		{
			Point2f(0,rotatedRect.size.height - 1),
			Point2f(0,0),
			Point2f(rotatedRect.size.width - 1,0),
			Point2f(rotatedRect.size.width - 1,rotatedRect.size.height - 1)
		};//��ʼ��Ŀ�������ĵ㣬���Сȡ���ڳ�ʼ���󣨳����䣩
		auto M = getPerspectiveTransform(srcPoints, dis_points); //����任����
		warpPerspective(srcImg, disImg, M, rotatedRect.size); //����͸�ӱ任����ɲü�
#ifdef FIND_QRPOINT_DEBUG
		Show_Img(disImg);
#endif 
		return disImg;
	}
	float distance(const Point2f& a, const Point2f& b)
	{
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
	Point CalForthPoint(const Point& poi0, const Point& poi1, const Point& poi2)
	{
		return Point(poi2.x + poi1.x - poi0.x, poi2.y + poi1.y - poi0.y);
	}
	pair<float, float> CalExtendVec(const Point2f& poi0, const Point2f& poi1, const Point2f& poi2, float bias)
	{	//�������㣬���㳤��Ϊbias�����ƽ������
		float dis0 = distance(poi0, poi1), dis1 = distance(poi0, poi2);
		float rate = dis1 / dis0;
		float x1 = poi0.x - poi2.x, y1 = poi0.y - poi2.y;
		float x2 = (poi0.x - poi1.x) * rate, y2 = (poi0.y - poi1.y) * rate;
		float totx = x1 + x2, toty = y1 + y2, distot = sqrt(totx * totx + toty * toty);
		return { totx / distot * bias, toty / distot * bias };
	}
	Mat CropParallelRect(const Mat& srcImg, const vector<Point2f>& srcPoints, Size size = { 0,0 })
	{   //��ͼ���н�һ���ı���͸�ӱ任Ϊ����(��Ҫ�ĸ��㣩
		cv::Mat disImg;
		vector<Point2f> poi4 = srcPoints;
		//int id[4][3] = { { 0,1,2 },{1,0,3},{2,0,3},{3,1,2} };
		for (int i = 0; i < 4; ++i)
		{
#ifdef CropParallelRect_DEBUG 
			line(srcImg, srcPoints[i], poi4[i], CV_RGB(255, 0, 0), 2);
			Show_Img(srcImg);
#endif
		}
		if (size == Size(0, 0))
			size = Size(distance(srcPoints[0], srcPoints[1]), distance(srcPoints[1], srcPoints[3]));
		vector<Point2f> dis_points =
		{
			Point2f(0,0),
			Point2f(size.width - 1,0),
			Point2f(0,size.height - 1),
			Point2f(size.width - 1,size.height - 1)
		};//��ʼ��Ŀ�������ĵ㣬���Сȡ���ڳ�ʼ���󣨳����䣩
		auto M = getPerspectiveTransform(srcPoints, dis_points); //����任����
		warpPerspective(srcImg, disImg, M, size); //����͸�ӱ任����ɲü�
#ifdef CropParallelRect_DEBUG 
		Show_Img(disImg);
#endif 
		return disImg;
	}
	bool isRightlAngle(float angle)
	{
		return MinRightAngel <= angle && MaxRightAngel >= angle;
	}
	namespace QrcodeParse
	{

#ifdef FIND_QRPOINT_DEBUG
		int TestCaseNumber = 1;
#endif
		struct ParseInfo
		{
			Point2f Center;
			int size;
			RotatedRect Rect;
			ParseInfo(const vector<Point>& pointSet) :
				Center(CalRectCenter(pointSet)),
				size(pointSet.size()),
				Rect(minAreaRect(pointSet)) {}
			ParseInfo() = default;
		};
		constexpr float MaxQRBWRate = 2.25, MinQRBWRate = 0.40;//ʶ���ڰױ������ƣ�����1.0��
		constexpr int MinQRSize = 10;//��Сʶ����С��ģ���뾶��ͼ��ߴ綯̬�ж�
		constexpr float MaxQRScale = 0.25, MinQRXYRate = 5.0 / 6.0, MaxQRXYRate = 6.0 / 5.0;
		//ʶ��㳤��ռԭͼ����������ʶ���ĳ������С���ƺ��������
		double Cal3NumVariance(const int a, const int b, const int c)
		{   //�������������ķ���
			double avg = (a + b + c) / 3.0;
			return (a - avg) * (a - avg) + (b - avg) * (b - avg) + (c - avg) * (c - avg);
			//��ʵӦ�ó����������Ƕ�û����Ҳ��Ӱ��Ƚϴ�С��
		}
		bool IsQrBWRateLegal(const float rate)
		{   //�жϺڰױ����Ƿ�Ϸ�
			return rate < MaxQRBWRate&& rate > MinQRBWRate;
			// �������rate=1.0��ʵ�ʿ�����һ����Χ�ڲ�����
		}
		bool BWRatePreprocessing(Mat& image, vector<int>& vValueCount)
		{   //�ڰ�����Ԥ������
			int count = 0, nc = image.cols * image.channels(), nr = image.rows / 2;
			uchar lastColor = 0, * data = image.ptr<uchar>(nr);
			for (int i = 0; i < nc; i++)      //�������������Լ��������Ƶ�������Ŀ
			{
				uchar color = data[i];
				if (color > 0)
					color = 255;
				if (i == 0)
				{
					lastColor = color;
					count++;
				}
				else
				{
					if (lastColor != color)
					{
						vValueCount.push_back(count);
						count = 0;
					}
					count++;
					lastColor = color;
				}
			}
			if (count) vValueCount.push_back(count);
			bool ans = vValueCount.size() >= 5;
#ifdef FIND_QRPOINT_DEBUG
			printf(ans ? "Preprocess Passed!" : "Preprocess Failed!");
#endif   
			return ans; //��ά��δͨ��Ԥ�������Ʋ����ڰ׺ڰ׺ڵ�5����
		}
		bool IsQrBWRateXLabel(Mat& image)
		{
			////�����ά��ʶ����XLabel�ĺڰױ����Ƿ�����Ҫ��
#ifdef FIND_QRPOINT_DEBUG
			printf("%c Labels:", (TestCaseNumber & 1) ? ('Y') : ('X'));
#endif 
			vector<int> vValueCount;
			if (!BWRatePreprocessing(image, vValueCount)) //δͨ��Ԥ��������ʶ���
				return false;
			//����ڰױ���1:1:3:1:1
			int index = -1, maxCount = -1;
			for (int i = 0; i < vValueCount.size(); i++)
			{
				if (i == 0)
				{
					index = i;
					maxCount = vValueCount[i];
				}
				else if (vValueCount[i] > maxCount)
				{
					index = i;
					maxCount = vValueCount[i];
				}
			}
			//��� �ұ� ��������ֵ������
			if (index < 2 || (vValueCount.size() - index) < 3)
				return false;
			//�ڰױ���1:1:3:1:1����

			float rate = ((float)maxCount) / 3.00;//���м�ı���3Ϊ��׼
			bool checkTag = 1;
#ifdef FIND_QRPOINT_DEBUG
			printf("BWRate: "); //����Ӧ����1��1��3��1��1
#endif
			for (int i = -2; i < 3; ++i)
			{
				float rateNow = vValueCount[index + i] / rate;
#ifdef FIND_QRPOINT_DEBUG
				printf("%f ", rateNow);
#endif
				if (i) checkTag &= IsQrBWRateLegal(rateNow);
			}
			return checkTag;
		}
		bool IsQrBWRate(Mat& image)
		{   //�����ά��ʶ���ĺ��ݺڰױ����Ƿ�����Ҫ��
#ifdef FIND_QRPOINT_DEBUG
			printf("\t");
#endif
			//����X��ı���
			bool xTest = IsQrBWRateXLabel(image);
			if (!xTest)
			{
#ifdef FIND_QRPOINT_DEBUG
				puts("\nFailed!");
#endif
				return false;
			}
#ifdef FIND_QRPOINT_DEBUG
			++TestCaseNumber;
			printf("\n\t");
#endif
			//������ת90���Լ���Y�����
			Mat image_rotation_90 = Rotation_90(image);
			bool yTest = IsQrBWRateXLabel(image_rotation_90);
#ifdef FIND_QRPOINT_DEBUG
			puts(yTest ? "\nPass!" : "\nFailed!");
#endif
			return yTest;
		}
		bool IsQrSizeLegal(const Size2f& qrSize, const Size2f&& imgSize)
		{
			float xYScale = qrSize.height / qrSize.width;
#ifdef FIND_QRPOINT_DEBUG
			bool ans = qrSize.height >= MinQRSize && qrSize.width >= MinQRSize;
			ans &= qrSize.height / imgSize.height < MaxQRScale&& qrSize.width / imgSize.width < MaxQRScale;
			ans &= xYScale <= MaxQRXYRate && xYScale >= MinQRXYRate;
			printf("Xsize:%.0f Ysize:%.0f XScale:%.2f%% YScale:%.2f%% xYScale:%.2f%% ",
				qrSize.height, qrSize.width,
				qrSize.height / imgSize.height * 100.0,
				qrSize.width / imgSize.width * 100.0,
				xYScale * 100.0
			);
			puts(ans ? "Size test Passed!" : "Size test Failed!");
			return ans;
#else
			if (qrSize.height < MinQRSize || qrSize.width < MinQRSize) //�жϿ�Ⱥͳ����Ƿ�̫С
				return false;
			if (qrSize.height / imgSize.height >= MaxQRScale || qrSize.width / imgSize.width >= MaxQRScale)
				return false;                                          //�ж����ԭͼ��ռ�ı����Ƿ�̫��
			if (xYScale < MinQRXYRate || xYScale > MaxQRXYRate)        //�жϳ�����Ƿ�ʧ��
				return false;
			return true;
#endif
		}
		bool IsQrPoint(const vector<Point>& contour, const Mat& img)
		{   //�������ж������vector<Point>�Ƿ��Ƕ�ά��ʶ���
#ifdef FIND_QRPOINT_DEBUG
			TestCaseNumber += (TestCaseNumber & 1) ? (1) : (2); //����������
			printf("\nPOINT %d:\n\t", TestCaseNumber / 2);
#endif
			RotatedRect rotatedRect = minAreaRect(contour);
			//������С���Ǿ���
			cv::Mat cropImg = CropRect(img, rotatedRect);
			//����ά�������ͼ�Ͽٳ���
			if (!IsQrSizeLegal(rotatedRect.size, img.size())) return false;
			//�жϳߴ��Ƿ�Ϸ�
			return IsQrBWRate(cropImg);
			//�жϺڰױ����Ƿ�Ϸ�
		}
		Mat ImgPreprocessing(const Mat& srcImg, float blurRate = 0.0005)
		{   //����ͼ��Ԥ������
			Mat tmpImg;
			//��ɫͼת�Ҷ�ͼ
			//Show_Img(srcImg);
			cvtColor(srcImg, tmpImg, COLOR_BGR2GRAY);
#ifdef FIND_QRPOINT_DEBUG
			Show_Img(tmpImg);
#endif		
			//ģ��ȫͼ�����ٸ�Ƶ��Ϣ�ĸ��ţ�������Ħ���ƣ�
			//ʵ����Ħ����ȥ���ƺ����и��õİ취������ȥ��һЩ��Ƶ����Ϣ��
			float BlurSize = 1.0 + srcImg.rows * blurRate;

			blur(tmpImg, tmpImg, Size2f(BlurSize, BlurSize));
#ifdef FIND_QRPOINT_DEBUG
			Show_Img(tmpImg);
#endif		
			//��ֵ��
			threshold(tmpImg, tmpImg, 0, 255, THRESH_BINARY | THRESH_OTSU);
#ifdef FIND_QRPOINT_DEBUG
			Show_Img(tmpImg);
#endif
			return tmpImg;
		}
		bool ScreenQrPoint(const Mat& srcImg, vector<vector<Point>>& qrPoints)
		{
			//���ò�����������
			vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;
			findContours(srcImg, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE, Point(0, 0));
			//ͨ����ɫ��λ����Ϊ�����������������������ص㣬ɸѡ��������λ��

			int parentIdx = -1;
			int ic = 0;

			for (int i = 0; i < contours.size(); i++)
			{
				if (hierarchy[i][2] != -1 && ic == 0)
				{
					parentIdx = i;
					ic++;
				}
				else if (hierarchy[i][2] != -1)
				{
					ic++;
				}
				else if (hierarchy[i][2] == -1)
				{
					ic = 0;
					parentIdx = -1;
				}
				if (ic == 2)
				{
					bool isQrPoint = IsQrPoint(contours[parentIdx], srcImg);
					//�����ҵ���������ɫ��λ��
					if (isQrPoint)
						qrPoints.push_back(contours[parentIdx]);
					ic = 0;
					parentIdx = -1;
				}
			}
#ifdef FIND_QRPOINT_DEBUG
			printf("Find %d Points!", (int)qrPoints.size());
			printf(qrPoints.size() < 3 ? "Points is too less,Screen Failed!" : "\n");
#endif // FIND_QRPOINT_DEBUG
			return qrPoints.size() < 3;
		}
		bool isRightAngleExist(const Point& point0, const Point& point1, const Point& point2)
		{
#ifdef FIND_QRPOINT_DEBUG
			static int counter = 0;
			float angle0 = Cal3PointAngle(point0, point1, point2), angle1 = Cal3PointAngle(point1, point0, point2), angle2 = Cal3PointAngle(point2, point0, point1);
			bool flag2 = isRightlAngle(angle0) || isRightlAngle(angle1) || isRightlAngle(angle2);
			printf("\nDumpPoints: %d angle0: %.2f angle1: %.2f,angle2: %.2f %s\n", ++counter, angle0, angle1, angle2, flag2 ? "Passed!" : "Failed!");
#endif
			return isRightlAngle(Cal3PointAngle(point0, point1, point2)) ||
				isRightlAngle(Cal3PointAngle(point1, point0, point2)) ||
				isRightlAngle(Cal3PointAngle(point2, point0, point1));
		}
		bool DumpExcessQrPoint(vector<vector<Point>>& qrPoints)
		{	//Ŀǰ��ʵ�֣����������������ֱ�ǵķ�����ӽ���������
			//�����Ժ��и��õ�ʵ�֣���
			sort(
				qrPoints.begin(), qrPoints.end(),
				[](const vector<Point>& a, const vector<Point>& b) {return a.size() < b.size(); }
			);
			//���������
			double mindis = INFINITY;
			int pos = -1;
			Point Point0 = CalRectCenter(qrPoints[0]), Point1 = CalRectCenter(qrPoints[1]), Point2;
			for (int i = 2; i < qrPoints.size(); ++i)
			{
				bool tag = 0;
				if (!isRightAngleExist(Point2 = CalRectCenter(qrPoints[i]), Point1, Point0))
					tag = 1;
				if (!tag)
				{
					auto temp = Cal3NumVariance(qrPoints[i].size(), qrPoints[i - 1].size(), qrPoints[i - 2].size());
					if (mindis > temp)
					{
						mindis = temp;
						pos = i;
					}
				}
				Point0 = Point1;
				Point1 = Point2;
			}
			//���pos==-1���򰴴�С����󲻴��ڼн�90�����ҵ�ʶ��㡣
			if (pos == -1) return 1;
			else
			{
				vector<vector<Point>> temp =
				{
					std::move(qrPoints[pos - 2]),
					std::move(qrPoints[pos - 1]),
					std::move(qrPoints[pos])
				};
				for (int i = 0; i < pos - 2; ++i)
					temp.push_back(std::move(qrPoints[i]));
				for (int i = pos + 1; i < qrPoints.size(); ++i)
					temp.push_back(std::move(qrPoints[i]));
				std::swap(temp, qrPoints);
				return 0;
			}
			//�粻����1�����ҵ���ֱ�������������С��������
			//�������ĵ�
		}
		void AdjustPointsOrder(vector<vector<Point>>& src3Points)
		{
			vector<vector<Point>> temp;
			Point p3[3] = { CalRectCenter(src3Points[0]),CalRectCenter(src3Points[1]),CalRectCenter(src3Points[2]) };
			int index[3][3] = { { 0,1,2 },{1,0,2},{2,0,1} };
			for (int i = 0; i < 3; i++)
			{
				if (isRightlAngle(Cal3PointAngle(p3[index[i][0]], p3[index[i][1]], p3[index[i][2]])))
				{
					temp.push_back(std::move(src3Points[index[i][0]]));     //���Ͻǵĵ�λ��0�� Red
					if (IsClockWise(p3[index[i][0]], p3[index[i][1]], p3[index[i][2]]))//�ж�1�ŵ��2�ŵ��˳��ʱ���ϵ
					{
						temp.push_back(std::move(src3Points[index[i][1]]));//���Ͻǵĵ�λ��1�� Green
						temp.push_back(std::move(src3Points[index[i][2]]));//���½ǵĵ�λ��2�� Blue
					}
					else
					{
						temp.push_back(std::move(src3Points[index[i][2]]));//���Ͻǵĵ�λ��1�� Green
						temp.push_back(std::move(src3Points[index[i][1]]));//���½ǵĵ�λ��2�� Blue
					}
					for (int i = 3; i < src3Points.size(); ++i)
						temp.push_back(std::move(src3Points[i]));  //�ƶ������ĵ�
					std::swap(temp, src3Points);
					return;
				}
			}
			return;
		}
		bool Main(const Mat& srcImg, vector<vector<Point>>& qrPoints)
		{
			//����ģ��������
			vector<vector<Point>> qrPointsTemp;
			std::array<float, 5> ar = { 0.0005,0.0000,0.00025,0.001,0.0001 };
			for (auto& rate : ar)//���Բ�ͬ��ģ����
			{
				//ͼ��Ԥ����,Ȼ��ɨ�趨λ��
				if (!ScreenQrPoint(ImgPreprocessing(srcImg, rate), qrPointsTemp))
				{
					if (qrPointsTemp.size() >= 4 && !DumpExcessQrPoint(qrPointsTemp))
					{
						qrPointsTemp.swap(qrPoints);
						AdjustPointsOrder(qrPoints);
						return 0;
					}
				}
			}
			return 1;
		}
		bool Main(const Mat& srcImg, vector<ParseInfo>& Points3Info)
		{
			vector<vector<Point>> qrPoints;
			if (Main(srcImg, qrPoints)) return 1;
			for (auto& e : qrPoints)
				Points3Info.emplace_back(e);
			return 0;
		}
		vector<Point2f> Adjust3PointsToParallelogram(vector<ParseInfo> Points3Info)
		{
			float avglen = 0.0;
			vector<Point2f> ret;
			int id[4][3] = { { 0,1,2 },{1,0,3},{2,0,3},{3,1,2} };
			for (int i = 0; i < 3; ++i)
			{
				ret.push_back(Points3Info[i].Center);
				avglen += Points3Info[i].Rect.size.height;
				avglen += Points3Info[i].Rect.size.width;
			}
			avglen /= 6.0 * sqrt(2.0) * 0.8;
			ret.push_back
			(
				CalForthPoint
				(
					Points3Info[0].Center,
					Points3Info[1].Center,
					Points3Info[2].Center
				)
			);
			pair<float, float> temp[4];
			for (int i = 0; i < 4; ++i)
				temp[i] = CalExtendVec(ret[id[i][0]], ret[id[i][1]], ret[id[i][2]], avglen);
			for (int i = 0; i < 4; ++i)
			{
				ret[i].x += temp[i].first;
				ret[i].y += temp[i].second;
			}
			return ret;
		}
		bool Main(const Mat& srcImg, Mat& disImg, vector<ParseInfo>& Points3Info)
		{
			if (Main(srcImg, Points3Info)) return 1;
			vector<float> avglen;
			for (auto& e : Points3Info)
				avglen.push_back((e.Rect.size.height + e.Rect.size.width) / 2.0);
			disImg = CropParallelRect(srcImg, Adjust3PointsToParallelogram(Points3Info));
		}
		void __DisPlay(const char* ImgPath)
		{
			Mat srcImg = imread(ImgPath, 1);
			imshow("ԭʼ", srcImg);
			vector<vector<Point>> qrPoints;
			if (!Main(srcImg, qrPoints))
			{
				for (int i = 0, C = 0x00FF0000; i < qrPoints.size(); ++i, C >>= 8)
					drawContours(srcImg, vector<vector<Point>>{qrPoints[i]}, 0, CV_RGB(C >> 16, (C >> 8) & 0xFF, C & 0xFF), -1);
				//��䶨λ��
				//���Ͻǵĵ���ʾΪ��ɫ�����Ͻǵĵ���ʾΪ��ɫ�����½ǵĵ���ʾΪ��ɫ
				Point2f point[3];
				for (int i = 0; i < qrPoints.size(); i++)
					point[i] = CalRectCenter(qrPoints[i]);
				line(srcImg, point[0], point[1], Scalar(255, 255, 0), 2);
				line(srcImg, point[1], point[2], Scalar(0, 255, 255), 2);
				line(srcImg, point[0], point[2], Scalar(255, 0, 255), 2);
				//���Ӷ�λ��
				imshow("���", srcImg);
			}
			waitKey(0);
		}
		void __DisPlay2(const char* ImgPath)
		{
			Mat srcImg = imread(ImgPath, 1);
			imshow("ԭʼ", srcImg);
			vector<ParseInfo> qrPoints;
			if (!Main(srcImg, qrPoints))
			{
				line(srcImg, qrPoints[0].Center, qrPoints[1].Center, Scalar(0, 0, 255), 2);
				line(srcImg, qrPoints[1].Center, qrPoints[2].Center, Scalar(0, 255, 0), 2);
				line(srcImg, qrPoints[0].Center, qrPoints[2].Center, Scalar(255, 0, 0), 2);
				Point2f poi[4];
				for (auto& e : qrPoints)
				{
					e.Rect.points(poi);
					line(srcImg, poi[0], poi[1], Scalar(128, 128, 128), 2);
					line(srcImg, poi[1], poi[2], Scalar(128, 128, 128), 2);
					line(srcImg, poi[2], poi[3], Scalar(128, 128, 128), 2);
					line(srcImg, poi[3], poi[0], Scalar(128, 128, 128), 2);
				}
				//���Ӷ�λ��
				imshow("���", srcImg);
			}
			waitKey(0);
		}
		void __DisPlay3(const char* ImgPath)
		{
			Mat srcImg = imread(ImgPath, 1), disImg;
			vector<ParseInfo>  Points3Info;
			if (Main(srcImg, disImg, Points3Info))
			{
				puts("ERR");
				return;
			}
			imshow("ans", disImg);
			waitKey(0);
		}
	}
	bool IsQrTypeRateLegal(float rate)
	{
		return rate <= MaxQrTypeRate && rate >= minQrTypeRate;
	}
	bool isLegalDistanceRate(float rate)
	{
		return rate <= MaxDistanceRate && rate >= minDistanceRate;
	}
	bool FindForthPoint(vector<QrcodeParse::ParseInfo>& PointsInfo)
	{
		float avgSize = (PointsInfo[0].size + PointsInfo[1].size + PointsInfo[2].size) / 3.0;
		float expectDistance = distance(PointsInfo[0].Center, CalForthPoint(PointsInfo[0].Center, PointsInfo[1].Center, PointsInfo[2].Center));
		QrcodeParse::ParseInfo possiblePoints;
		bool tag = 1;
		for (int i = 3; i < PointsInfo.size(); ++i)
		{
#ifdef FIND_QRPOINT_DEBUG
#endif
			if (IsQrTypeRateLegal(avgSize / PointsInfo[i].size))//��С����
				if (isRightlAngle(Cal3PointAngle(PointsInfo[i].Center, PointsInfo[1].Center, PointsInfo[2].Center)))
					if (isLegalDistanceRate(distance(PointsInfo[i].Center, PointsInfo[0].Center) / expectDistance))
					{
						possiblePoints = std::move(PointsInfo[i]), tag = 0;
						break;
					}
		}

		if (tag) return 1;
		PointsInfo.erase(PointsInfo.begin() + 3, PointsInfo.end());
		PointsInfo.push_back(std::move(possiblePoints));
		return 0;
	}
	vector<Point2f> AdjustForthPoint(const vector<QrcodeParse::ParseInfo> PointsInfo, bool tag)
	{
		float avglen = 0.0;
		vector<Point2f> ret;
		int id[4][3] = { { 0,1,2 },{1,0,3},{2,0,3},{3,1,2} };
		for (int i = 0; i < 3; ++i)
		{
			ret.push_back(PointsInfo[i].Center);
			avglen += PointsInfo[i].Rect.size.height;
			avglen += PointsInfo[i].Rect.size.width;
		}
		ret.push_back(PointsInfo[3].Center);
		avglen += PointsInfo[3].Rect.size.height * 2.0;
		avglen += PointsInfo[3].Rect.size.width * 2.0;
		avglen /= (tag) ? 8.0 : 2.0;
		if (tag) avglen = avglen / 14.0 * 9 * sqrt(2);
		pair<float, float> temp[4];
		for (int i = 0; i < 3; ++i)
			temp[i] = CalExtendVec(ret[id[i][0]], ret[id[i][1]], ret[id[i][2]], avglen);
		float forthCornerLen = avglen * ((tag) ? (11.0 / 18.0) : ((56.0 - 3.5 * sqrt(2.0)) / 56.0));
		temp[3] = CalExtendVec(ret[id[3][0]], ret[id[3][1]], ret[id[3][2]], forthCornerLen);
		for (int i = 0; i < 4; ++i)
		{
			ret[i].x += temp[i].first;
			ret[i].y += temp[i].second;
		}
		return ret;
	}
	void GetVec(Mat& mat)
	{
		uint16_t minVec[3] = { 255,255,255 }, maxVec[3] = { 0, 0, 0 };
		Mat tempMat;
		for (int i = 10; i < 100; ++i)
		{
			for (int j = 10; j < 100; ++j)
			{
				Vec3b& temp = mat.at<Vec3b>(i, j);
				minVec[0] = min(minVec[0], (uint16_t)temp[0]);
				minVec[1] = min(minVec[1], (uint16_t)temp[1]);
				minVec[2] = min(minVec[2], (uint16_t)temp[2]);
				maxVec[0] = max(maxVec[0], (uint16_t)temp[0]);
				maxVec[1] = max(maxVec[1], (uint16_t)temp[1]);
				maxVec[2] = max(maxVec[2], (uint16_t)temp[2]);
			}
		}
		float avg = (minVec[0] + maxVec[0] + minVec[1] + maxVec[1] + minVec[2] + maxVec[2]) / 6.0;
		for (int i = 0; i < 1080; ++i)
		{
			for (int j = 0; j < 1080; ++j)
			{
				Vec3b& temp = mat.at<Vec3b>(i, j);
				float sum = (temp[0] + temp[1] + temp[2]) / 3.0;
				if (sum < avg) temp = Vec3b(0, 0, 0);
				else temp = Vec3b(255, 255, 255);
			}
		}
		return;
	}
	void dfs(int i, int j, int limi, int limj, int* dir, bool(*ispass)[16], const Mat& mat)
	{
		if ((limi - i) * dir[0] > 0 || (limj - j) * dir[1] > 0) return;
		if ((limi - i) * dir[0] <= -16 || (limj - j) * dir[1] <= -16) return;
		if (ispass[(i - limi) * dir[0]][(j - limj) * dir[1]]) return;
		auto temp = mat.at<Vec3b>(i, j);
		if (temp[0] == temp[1] && temp[1] == temp[2] && temp[2] == 255)
		{
			ispass[(i - limi) * dir[0]][(j - limj) * dir[1]] = 1;
			dfs(i + 1 * dir[0], j, limi, limj, dir, ispass, mat);
			dfs(i - 1 * dir[0], j, limi, limj, dir, ispass, mat);
			dfs(i, j - 1 * dir[0], limi, limj, dir, ispass, mat);
			dfs(i, j + 1 * dir[0], limi, limj, dir, ispass, mat);
		}
	}
	vector<Point2f> FindConner(Mat& mat)
	{
		int dis = 0;
		int dir[4][2] = { {1,1},{-1,1},{1,-1},{-1,-1} };
		int poi[4][2] = { {0,0},{1079,0},{0,1079},{1079,1079} };
		vector<Point2f> ret;
		for (int k = 0; k < 4; ++k)
		{
			bool ispass[16][16] = { 0 };
			dfs(poi[k][0] + 10 * dir[k][0], poi[k][1] + 10 * dir[k][1], poi[k][0], poi[k][1], dir[k], ispass, mat);
			for (dis = 0; dis <= 15; ++dis)
			{
				for (int i = 0; i <= dis; ++i)
				{
					int j = dis - i;
					auto temp = mat.at<Vec3b>(poi[k][0] + i * dir[k][0], poi[k][1] + j * dir[k][1]);
					if (temp[0] == temp[1] && temp[1] == temp[2] && temp[2] == 255 && ispass[i][j])
					{
						ret.emplace_back(poi[k][0] + i * dir[k][0], poi[k][1] + j * dir[k][1]);
						goto Final;
					}
				}
			}
		Final:
			if (dis == 100)
				break;
		}
		//Show_Img(mat);
		if (ret.size() != 4) return ret;
		std::swap(ret[1].x, ret[2].y);
		std::swap(ret[2].x, ret[1].y);
		return ret;
	}
	void Resize(Mat& mat)
	{
		Mat temp = Mat(108, 108, CV_8UC3);
		for (int i = 0; i < 108; ++i)
		{
			for (int j = 0; j < 108; ++j)
			{
				int counter[8] = { 0 };
				for (int k = 4; k <= 5; ++k)
				{
					for (int l = 4; l <= 5; ++l)
					{
						int id = 0;
						const auto& vec = mat.at<Vec3b>(i * 10 + k, j * 10 + l);
						if (vec[0] == 255)
							id += 4;
						if (vec[1] == 255)
							id += 2;
						if (vec[2] == 255)
							id += 1;
						++counter[id];
					}
				}
				int maxpos = 0;
				for (int i = 1; i < 8; ++i)
					if (counter[maxpos] < counter[i])
						maxpos = i;
				temp.at<Vec3b>(i, j) = Vec3b((maxpos >> 2) * 255, ((maxpos >> 1) & 1) * 255, (maxpos & 1) * 255);
			}
		}
		mat = temp;
	}
	bool Main(const Mat& srcImg, Mat& disImg)
	{
		Mat temp;

		//����Ϊ��λ����
		{
			//Show_Img(srcImg);
			vector<QrcodeParse::ParseInfo> PointsInfo;
			if (Main(srcImg, PointsInfo) || PointsInfo.size() < 4)
				return 1;

			if (FindForthPoint(PointsInfo)) return 1;
			//һ�ײü�����ɳ���ɸѡ
			temp = CropParallelRect(srcImg, AdjustForthPoint(PointsInfo, 0));
#ifdef FIND_QRPOINT_DEBUG
			Show_Img(temp);
#endif 
			disImg = CropParallelRect(srcImg, AdjustForthPoint(PointsInfo, 1));
#ifdef FIND_QRPOINT_DEBUG
			Show_Img(disImg);
#endif 
			//���ײü������ʵ��ӳ�䣬�����������
			PointsInfo.clear();
			//return 0;
			if (Main(temp, PointsInfo) || PointsInfo.size() < 4);
			else
			{
				if (FindForthPoint(PointsInfo)) return 0;
				disImg = CropParallelRect(temp, AdjustForthPoint(PointsInfo, 1));
			}
			//Show_Img(disImg);
			//������ײü�ʧ�ܸ���һ�ײü�����Ϣ����һ����֪���Ƿ�ȷ�Ľ����
			//����΢����������ս���
			disImg.copyTo(temp);
			cv::resize(temp, temp, Size(1080, 1080));
			GetVec(temp);
			auto poi4 = FindConner(temp);
			if (poi4.size() != 4) return 1;
			cv::resize(disImg, disImg, Size(1080, 1080));
			temp = CropParallelRect(disImg, poi4, Size(1080, 1080));
		}

		disImg = temp;
#ifdef FIND_QRPOINT_DEBUG
		Show_Img(disImg);
#endif 
		GetVec(disImg);
		Resize(disImg);
#ifdef FIND_QRPOINT_DEBUG
		Show_Img(disImg);
#endif 
		return 0;
	}
	void __DisPlay(const char* ImgPath)
	{
		Mat srcImg = imread(ImgPath, 1), disImg;
		if (Main(srcImg, disImg))
		{
			puts("ERR");
			return;
		}
		imshow("ans", disImg);
		waitKey(0);
	}
}