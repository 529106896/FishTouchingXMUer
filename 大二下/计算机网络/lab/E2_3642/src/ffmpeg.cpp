#include "ffmpeg.h"

namespace FFMPEG
{
	constexpr int MAXBUFLEN = 256;
	const char ffmpegPath[] = "ffmpeg\\bin\\";
	const char tmpPath[] = "tmpdir";
	int ImagetoVideo(const char* imagePath,
		const char* imageFormat,
		const char* videoPath,
		unsigned rawFrameRates,
		unsigned outputFrameRates,
		unsigned kbps)
	{
		char BUF[MAXBUFLEN];
		if (kbps)
			snprintf(BUF, MAXBUFLEN,
				"\"%s\"ffmpeg.exe -r %u  -f image2 -i %s\\%%05d.%s -b:v %uK -vcodec libx264  -r %u %s",
				ffmpegPath, rawFrameRates, imagePath, imageFormat, kbps, outputFrameRates, videoPath);
		else
			snprintf(BUF, MAXBUFLEN,
				"\"%s\"ffmpeg.exe -r %u -f image2 -i %s\\%%05d.%s  -vcodec libx264 -r %u %s",
				ffmpegPath, rawFrameRates, imagePath, imageFormat, outputFrameRates, videoPath);
		return system(BUF);
	}
	int VideotoImage(const char* videoPath,
		const char* imagePath,
		const char* imageFormat)
	{
		char BUF[MAXBUFLEN];
		snprintf(BUF, MAXBUFLEN, "md %s", imagePath); //生成文件目录
		system(BUF);
		snprintf(BUF, MAXBUFLEN,
			"\"%s\"ffmpeg.exe -i %s -q:v 2 -f image2  %s\\%%05d.%s",
			ffmpegPath, videoPath, imagePath, imageFormat);
		return system(BUF);
	}
	int test(void)
	{
		bool tag = VideotoImage("test.mp4", tmpPath, "png");
		if (tag)
			return tag;
		tag = ImagetoVideo(tmpPath, "png", "out.mp4", 30, 30);
		return tag;
	}
} // namespace ffmpeg