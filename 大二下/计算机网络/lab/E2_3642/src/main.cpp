#define _CRT_SECURE_NO_WARNINGS
//主函数
#include"pic.h"
#include"code.h"
#include"ffmpeg.h"
#include"ImgDecode.h"
#include <cstring>

using namespace std;

#define Show_Img(src) do\
{\
	cv::imshow("DEBUG", src);\
	cv::waitKey();\
}while (0);
//图片转视频
int FileToVideo(const char* filePath, int FrameLimit, const char* videoPath, int timLim = INT_MAX, int fps = 10)
{
	const char* fatherpath = filePath;
	string filename = "1.txt";
	char filepath[256];
	memset(filepath, '\0', sizeof(filepath));
	char temp1[256];

	for (int i = 0; i < 4; i++)
	{
		snprintf(temp1, 255, "%s\\%s+", fatherpath, filename.c_str());
		strcat(filepath, temp1);
		filename[0]++;
	}
	filepath[strlen(filepath) - 1] = '\0';

	snprintf(temp1, 255, "copy /b %s %s\\%s", filepath, fatherpath, "des.txt");
	system(temp1);

	snprintf(temp1, 255, "%s\\des.txt", filePath);

	FILE* fp = fopen(temp1, "rb");
	if (fp == nullptr) return 1;
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	rewind(fp);
	char* temp = (char*)malloc(sizeof(char) * size);
	if (temp == nullptr) return 1;
	fread(temp, 1, size, fp);
	fclose(fp);
	system("md outputImg");
	Code::Main(temp, size, "outputImg", "png", FrameLimit);
	FFMPEG::ImagetoVideo("outputImg", "png", videoPath, fps, 10, 100000);
	system("rd /s /q outputImg");
	free(temp);
	return 0;
}

//视频转图片
int VideoToFile(const char* videoPath, const char* filePath)
{
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
		char temp[256];
		snprintf(temp, 255, "md %s", filePath);
		system(temp);
		snprintf(temp, 255, "%s\\%s", filePath, "testout.txt");
		FILE* fp = fopen(temp, "wb");
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
	//type==true 将文件编码为视频  命令行参数 ： 输入文件目录 最大传输单元 输出视频路径 最长视频时长
	//type==false 将视频编码为文件 命令行参数 ： 输入视频路径 输出图片路径
	if constexpr (type)
	{
		if (argc == 5)
			return FileToVideo(argv[1], std::stoi(argv[2]), argv[3], std::stoi(argv[4]));
		else if (argc == 6)
			return FileToVideo(argv[1], std::stoi(argv[2]), argv[3], std::stoi(argv[4]), std::stoi(argv[5]));
	}
	else
	{
		if (argc == 3)
			return VideoToFile(argv[1], argv[2]);
	}
	puts("argument error,please check your argument");
	return 1;
}