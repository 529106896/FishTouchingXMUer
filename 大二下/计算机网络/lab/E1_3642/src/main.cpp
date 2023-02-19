#define _CRT_SECURE_NO_WARNINGS
//������
#include"pic.h"
#include"code.h"
#include"ffmpeg.h"
#include"ImgDecode.h"

using namespace std;

#define Show_Img(src) do\
{\
	cv::imshow("DEBUG", src);\
	cv::waitKey();\
}while (0);
//ͼƬת��Ƶ
int FileToVideo(const char* filePath, const char* videoPath, int timLim = INT_MAX, int fps = 10)
{
	FILE* fp = fopen(filePath, "rb");
	if (fp == nullptr) return 1;
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	rewind(fp);
	char* temp = (char*)malloc(sizeof(char) * size);
	if (temp == nullptr) return 1;
	fread(temp, 1, size, fp);
	fclose(fp);
	system("md outputImg");
	Code::Main(temp, size, "outputImg", "png", 1LL * fps * timLim / 1000);
	FFMPEG::ImagetoVideo("outputImg", "png", videoPath, fps, 10, 100000);
	system("rd /s /q outputImg");
	free(temp);
	return 0;
}

//��ƵתͼƬ
int VideoToFile(const char* videoPath, const char* filePath)
{
	//cv::Mat srcImg = cv::imread("1.jpg", 1);
	//Show_Img(srcImg);
	char imgName[256];
	system("rd /s /q inputImg");
	system("md inputImg");
	bool isThreadOver = false;
	std::thread th([&] {FFMPEG::VideotoImage(videoPath, "inputImg", "jpg"); isThreadOver = true; });
	int precode = -1;
	std::vector<unsigned char> outputFile;
	bool hasStarted = 0;
	bool ret = 0;
	for (int i = 1;; ++i, system((std::string("del ") + imgName).c_str()))
	{
		printf("Reading Image %05d.jpg\n", i);
		snprintf(imgName, 256, "inputImg\\%05d.jpg", i);
		FILE* fp;
		do
		{
			fp = fopen(imgName, "rb");
		} while (fp == nullptr && !isThreadOver);

		if (fp == nullptr)
		{
			puts("failed to open the video, is the video Incomplete?");
			ret = 1;
			break;
		}
		cv::Mat srcImg = cv::imread(imgName, 1), disImg;
		//Show_Img(srcImg);
		fclose(fp);

		if (ImgParse::Main(srcImg, disImg))
		{
			continue;
		}
		//Show_Img(disImg);
		ImageDecode::ImageInfo imageInfo;
		bool ans = ImageDecode::Main(disImg, imageInfo);
		if (ans)
		{
			continue;
		}
		if (!hasStarted)
		{
			if (imageInfo.IsStart)
				hasStarted = 1;
			else continue;
		}
		if (precode == imageInfo.FrameBase)
			continue;
		if (((precode + 1) & UINT16_MAX) != imageInfo.FrameBase)
		{
			puts("error, there is a skipped frame,there are some images parsed failed.");
			ret = 1;
			break;
		}
		printf("Frame %d is parsed!\n", imageInfo.FrameBase);

		precode = (precode + 1) & UINT16_MAX;
		for (auto& e : imageInfo.Info)
			outputFile.push_back(e);

		if (imageInfo.IsEnd)
			break;
	}
	if (ret == 0)
	{
		th.join();
		printf("\nVideo Parse is success.\nFile Size:%lldB\nTotal Frame:%d\n", outputFile.size(), precode);
		FILE* fp = fopen(filePath, "wb");
		if (fp == nullptr) return 1;
		outputFile.push_back('\0');
		fwrite(outputFile.data(), sizeof(unsigned char), outputFile.size() - 1, fp);
		fclose(fp);
		return ret;
	}
	exit(1);
}
int main(int argc, char* argv[])
{
	constexpr bool type = false;
	//type==true ���ļ�����Ϊ��Ƶ  �����в��� �� �����ļ�·�� �����Ƶ·�� ���Ƶʱ��
	//type==false ����Ƶ����Ϊ�ļ� �����в��� �� ������Ƶ·�� ���ͼƬ·��
	if constexpr (type)
	{
		if (argc == 4)
			return FileToVideo(argv[1], argv[2], std::stoi(argv[3]));
		else if (argc == 5)
			return FileToVideo(argv[1], argv[2], std::stoi(argv[3]), std::stoi(argv[4]));
	}
	else
	{
		if (argc == 3)
			return VideoToFile(argv[1], argv[2]);
	}
	puts("argument error,please check your argument");
	return 1;
}