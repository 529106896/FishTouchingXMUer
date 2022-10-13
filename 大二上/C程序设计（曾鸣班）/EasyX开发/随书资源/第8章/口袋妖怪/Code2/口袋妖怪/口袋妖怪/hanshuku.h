void pokemon_fight_show(char *p, int jumpy)
{
	

	IMAGE im1, im2;
	loadimage(&im1, _T("资源文件夹\\皮卡丘.jpg"));
	loadimage(&im2, _T("资源文件夹\\皮卡丘2.jpg"));
	putimage(65, jumpy, &im2, NOTSRCERASE);
	putimage(65, jumpy, &im1, SRCINVERT);
	FlushBatchDraw();//结束批量绘制
}
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