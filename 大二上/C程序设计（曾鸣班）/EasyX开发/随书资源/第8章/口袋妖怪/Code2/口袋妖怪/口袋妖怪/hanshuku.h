void pokemon_fight_show(char *p, int jumpy)
{
	

	IMAGE im1, im2;
	loadimage(&im1, _T("��Դ�ļ���\\Ƥ����.jpg"));
	loadimage(&im2, _T("��Դ�ļ���\\Ƥ����2.jpg"));
	putimage(65, jumpy, &im2, NOTSRCERASE);
	putimage(65, jumpy, &im1, SRCINVERT);
	FlushBatchDraw();//������������
}
void lighting()	//���缼�ܵ�Ч����ʾ
{
							IMAGE im3, im4;   
							loadimage(&im3, _T("��Դ�ļ���\\����1.jpg"), 70, 200);
							loadimage(&im4, _T("��Դ�ļ���\\����1bk.jpg"), 70, 200);
							putimage(450, 0, &im4, NOTSRCERASE);
							putimage(450, 0, &im3, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
							IMAGE im5, im6;
							loadimage(&im5, _T("��Դ�ļ���\\����2.jpg"), 70, 200);
							loadimage(&im6, _T("��Դ�ļ���\\����2bk.jpg"), 70, 200);
							putimage(450, 0, &im6, NOTSRCERASE);
							putimage(450, 0, &im5, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
							IMAGE im7, im8;
							loadimage(&im7, _T("��Դ�ļ���\\����3.jpg"), 70, 220);
							loadimage(&im8, _T("��Դ�ļ���\\����3bk.jpg"), 70, 220);
							putimage(450, -10, &im8, NOTSRCERASE);
							putimage(450, -10, &im7, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
}

void scream()   //��м��ܵ�չʾ
{
							IMAGE im7, im8;
							loadimage(&im7, _T("��Դ�ļ���\\���.jpg"), 70, 220);
							loadimage(&im8, _T("��Դ�ļ���\\���bk.jpg"), 70, 220);
							putimage(200,130, &im8, NOTSRCERASE);
							putimage(200,130 , &im7, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
}