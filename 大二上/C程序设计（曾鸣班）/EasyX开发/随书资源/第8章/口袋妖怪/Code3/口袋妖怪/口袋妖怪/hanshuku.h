void lighting()	//闪电技能的效果演示
{
							IMAGE im3, im4;   
							loadimage(&im3, _T("资源文件夹\\闪电1.jpg"), 70, 200);
							loadimage(&im4, _T("资源文件夹\\闪电1bk.jpg"), 70, 200);
							putimage(450, 0, &im4, NOTSRCERASE);
							putimage(450, 0, &im3, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
							IMAGE im5, im6;
							loadimage(&im5, _T("资源文件夹\\闪电2.jpg"), 70, 200);
							loadimage(&im6, _T("资源文件夹\\闪电2bk.jpg"), 70, 200);
							putimage(450, 0, &im6, NOTSRCERASE);
							putimage(450, 0, &im5, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
							IMAGE im7, im8;
							loadimage(&im7, _T("资源文件夹\\闪电3.jpg"), 70, 220);
							loadimage(&im8, _T("资源文件夹\\闪电3bk.jpg"), 70, 220);
							putimage(450, -10, &im8, NOTSRCERASE);
							putimage(450, -10, &im7, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
}

void scream()   //尖叫技能的展示
{
							IMAGE im7, im8;
							loadimage(&im7, _T("资源文件夹\\尖叫.jpg"), 70, 220);
							loadimage(&im8, _T("资源文件夹\\尖叫bk.jpg"), 70, 220);
							putimage(200,130, &im8, NOTSRCERASE);
							putimage(200,130 , &im7, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
}

void flash()
{
	IMAGE im7, im8;
	loadimage(&im7, _T("资源文件夹\\技能3.jpg"));
	loadimage(&im8, _T("资源文件夹\\技能3bk.jpg"));
	putimage(350, 30, &im8, NOTSRCERASE);
	putimage(350, 30, &im7, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	IMAGE im9, im10;
	loadimage(&im9, _T("资源文件夹\\技能3-2.jpg"));
	loadimage(&im10, _T("资源文件夹\\技能3-2bk.jpg"));
	putimage(350, 80, &im10, NOTSRCERASE);
	putimage(350, 80, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	IMAGE im11, im12;
	loadimage(&im11, _T("资源文件夹\\技能3-3.jpg"));
	loadimage(&im12, _T("资源文件夹\\技能3-3bk.jpg"));
	putimage(350, 105, &im12, NOTSRCERASE);
	putimage(350, 105, &im11, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	IMAGE im13, im14;
	loadimage(&im13, _T("资源文件夹\\技能3-4.jpg"));
	loadimage(&im14, _T("资源文件夹\\技能3-4bk.jpg"));
	putimage(350, 135, &im14, NOTSRCERASE);
	putimage(350, 135, &im13, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	IMAGE im15, im16;
	loadimage(&im15, _T("资源文件夹\\技能3-5.jpg"));
	loadimage(&im16, _T("资源文件夹\\技能3-5bk.jpg"));
	putimage(350, 165, &im16, NOTSRCERASE);
	putimage(350, 165, &im15, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
}