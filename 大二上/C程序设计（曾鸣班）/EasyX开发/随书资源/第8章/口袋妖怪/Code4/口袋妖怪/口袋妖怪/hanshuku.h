							//char转化为TCHAR
void CharToTchar (const char * _char, TCHAR * tchar)
{
    int iLength ;
    iLength = MultiByteToWideChar (CP_ACP, 0, _char, strlen (_char) + 1, NULL, 0) ;
    MultiByteToWideChar (CP_ACP, 0, _char, strlen (_char) + 1, tchar, iLength) ;
}
							//十万伏特的效果演示
void lighting()
{
							IMAGE im3, im4;
							loadimage(&im3, _T("资源文件夹\\技能\\闪电1.jpg"), 70, 200);
							loadimage(&im4, _T("资源文件夹\\技能\\闪电1bk.jpg"), 70, 200);
							putimage(450, 0, &im4, NOTSRCERASE);
							putimage(450, 0, &im3, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
							IMAGE im5, im6;
							loadimage(&im5, _T("资源文件夹\\技能\\闪电2.jpg"), 70, 200);
							loadimage(&im6, _T("资源文件夹\\技能\\闪电2bk.jpg"), 70, 200);
							putimage(450, 0, &im6, NOTSRCERASE);
							putimage(450, 0, &im5, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
							IMAGE im7, im8;
							loadimage(&im7, _T("资源文件夹\\技能\\闪电3.jpg"), 70, 220);
							loadimage(&im8, _T("资源文件夹\\技能\\闪电3bk.jpg"), 70, 220);
							putimage(450, -10, &im8, NOTSRCERASE);
							putimage(450, -10, &im7, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
}
								 //尖叫技能的展示
void scream()
{
							IMAGE im7, im8;
							loadimage(&im7, _T("资源文件夹\\技能\\尖叫.jpg"), 70, 220);
							loadimage(&im8, _T("资源文件夹\\技能\\尖叫bk.jpg"), 70, 220);
							putimage(200,130, &im8, NOTSRCERASE);
							putimage(200,130 , &im7, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
}
                                //电磁波的展示
void flash()
{
	IMAGE im7, im8;
	loadimage(&im7, _T("资源文件夹\\技能\\电磁波.jpg"));
	loadimage(&im8, _T("资源文件夹\\技能\\电磁波bk.jpg"));
	putimage(350, 30, &im8, NOTSRCERASE);
	putimage(350, 30, &im7, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	IMAGE im9, im10;
	loadimage(&im9, _T("资源文件夹\\技能\\电磁波2.jpg"));
	loadimage(&im10, _T("资源文件夹\\技能\\电磁波2bk.jpg"));
	putimage(350, 80, &im10, NOTSRCERASE);
	putimage(350, 80, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	IMAGE im11, im12;
	loadimage(&im11, _T("资源文件夹\\技能\\电磁波3.jpg"));
	loadimage(&im12, _T("资源文件夹\\技能\\电磁波3bk.jpg"));
	putimage(350, 105, &im12, NOTSRCERASE);
	putimage(350, 105, &im11, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	IMAGE im13, im14;
	loadimage(&im13, _T("资源文件夹\\技能\\电磁波4.jpg"));
	loadimage(&im14, _T("资源文件夹\\技能\\电磁波4bk.jpg"));
	putimage(350, 135, &im14, NOTSRCERASE);
	putimage(350, 135, &im13, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	IMAGE im15, im16;
	loadimage(&im15, _T("资源文件夹\\技能\\电磁波5.jpg"));
	loadimage(&im16, _T("资源文件夹\\技能\\电磁波5bk.jpg"));
	putimage(350, 165, &im16, NOTSRCERASE);
	putimage(350, 165, &im15, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
}

                                //打雷技能的展示
void thunder()
{
	IMAGE im3, im4;
							loadimage(&im3, _T("资源文件夹\\技能\\打雷1.jpg"), 70, 200);
							loadimage(&im4, _T("资源文件夹\\技能\\打雷1bk.jpg"), 70, 200);
							putimage(450, 0, &im4, NOTSRCERASE);
							putimage(450, 0, &im3, SRCINVERT);
							FlushBatchDraw();
							Sleep(400);
							IMAGE im5, im6;
							loadimage(&im5, _T("资源文件夹\\技能\\打雷2.jpg"), 70, 200);
							loadimage(&im6, _T("资源文件夹\\技能\\打雷2bk.jpg"), 70, 200);
							putimage(400, 0, &im6, NOTSRCERASE);
							putimage(400, 0, &im5, SRCINVERT);
							FlushBatchDraw();
							Sleep(400);
}
