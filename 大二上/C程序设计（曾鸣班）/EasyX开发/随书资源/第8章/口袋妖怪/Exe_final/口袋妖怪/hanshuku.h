							//charת��ΪTCHAR
void CharToTchar (const char * _char, TCHAR * tchar)
{
    int iLength ;
    iLength = MultiByteToWideChar (CP_ACP, 0, _char, strlen (_char) + 1, NULL, 0) ;
    MultiByteToWideChar (CP_ACP, 0, _char, strlen (_char) + 1, tchar, iLength) ;
}
							//ʮ����ص�Ч����ʾ
void lighting()
{
							IMAGE im3, im4;
							mciSendString(_T("Seek sk1 to start"), NULL, 0, NULL);
							mciSendString(_T("play sk1"), NULL, 0, NULL);
							loadimage(&im3, _T("��Դ�ļ���\\����\\����1.jpg"), 70, 200);
							loadimage(&im4, _T("��Դ�ļ���\\����\\����1bk.jpg"), 70, 200);
							putimage(450, 0, &im4, NOTSRCERASE);
							putimage(450, 0, &im3, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
							IMAGE im5, im6;
							loadimage(&im5, _T("��Դ�ļ���\\����\\����2.jpg"), 70, 200);
							loadimage(&im6, _T("��Դ�ļ���\\����\\����2bk.jpg"), 70, 200);
							putimage(450, 0, &im6, NOTSRCERASE);
							putimage(450, 0, &im5, SRCINVERT);
							FlushBatchDraw();
							Sleep(300);
							IMAGE im7, im8;
							loadimage(&im7, _T("��Դ�ļ���\\����\\����3.jpg"), 70, 220);
							loadimage(&im8, _T("��Դ�ļ���\\����\\����3bk.jpg"), 70, 220);
							putimage(450, -10, &im8, NOTSRCERASE);
							putimage(450, -10, &im7, SRCINVERT);
							FlushBatchDraw();         
							Sleep(500);
							// mciSendString(_T("close sk1"), NULL, 0, NULL);
}
								 //��м��ܵ�չʾ
void scream()
{
							IMAGE im7, im8;
							mciSendString(_T("Seek sk2 to start"), NULL, 0, NULL);
							mciSendString(_T("play sk2"), NULL, 0, NULL);
							loadimage(&im7, _T("��Դ�ļ���\\����\\���.jpg"), 70, 220);
							loadimage(&im8, _T("��Դ�ļ���\\����\\���bk.jpg"), 70, 220);
							putimage(200,130, &im8, NOTSRCERASE);
							putimage(200,130 , &im7, SRCINVERT);
							FlushBatchDraw();
							Sleep(500);
								 mciSendString(_T("close sk2"), NULL, 0, NULL);
}
                                //��Ų���չʾ
void flash()
{
	IMAGE im7, im8;
	mciSendString(_T("Seek sk3 to start"), NULL, 0, NULL);
	mciSendString(_T("play sk3"), NULL, 0, NULL);
	loadimage(&im7, _T("��Դ�ļ���\\����\\��Ų�.jpg"));
	loadimage(&im8, _T("��Դ�ļ���\\����\\��Ų�bk.jpg"));
	putimage(350, 30, &im8, NOTSRCERASE);
	putimage(350, 30, &im7, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	IMAGE im9, im10;
	loadimage(&im9, _T("��Դ�ļ���\\����\\��Ų�2.jpg"));
	loadimage(&im10, _T("��Դ�ļ���\\����\\��Ų�2bk.jpg"));
	putimage(350, 80, &im10, NOTSRCERASE);
	putimage(350, 80, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	IMAGE im11, im12;
	loadimage(&im11, _T("��Դ�ļ���\\����\\��Ų�3.jpg"));
	loadimage(&im12, _T("��Դ�ļ���\\����\\��Ų�3bk.jpg"));
	putimage(350, 105, &im12, NOTSRCERASE);
	putimage(350, 105, &im11, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	IMAGE im13, im14;
	loadimage(&im13, _T("��Դ�ļ���\\����\\��Ų�4.jpg"));
	loadimage(&im14, _T("��Դ�ļ���\\����\\��Ų�4bk.jpg"));
	putimage(350, 135, &im14, NOTSRCERASE);
	putimage(350, 135, &im13, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	IMAGE im15, im16;
	loadimage(&im15, _T("��Դ�ļ���\\����\\��Ų�5.jpg"));
	loadimage(&im16, _T("��Դ�ļ���\\����\\��Ų�5bk.jpg"));
	putimage(350, 165, &im16, NOTSRCERASE);
	putimage(350, 165, &im15, SRCINVERT);
	FlushBatchDraw();
	Sleep(500);
		//mciSendString(_T("close sk3"), NULL, 0, NULL);
}

                                //���׼��ܵ�չʾ
void thunder()
{
	IMAGE im3, im4;
	mciSendString(_T("Seek sk4 to start"), NULL, 0, NULL);
	mciSendString(_T("play sk4"), NULL, 0, NULL);
							loadimage(&im3, _T("��Դ�ļ���\\����\\����1.jpg"), 70, 200);
							loadimage(&im4, _T("��Դ�ļ���\\����\\����1bk.jpg"), 70, 200);
							putimage(450, 0, &im4, NOTSRCERASE);
							putimage(450, 0, &im3, SRCINVERT);
							FlushBatchDraw();
							Sleep(400);
							IMAGE im5, im6;
							loadimage(&im5, _T("��Դ�ļ���\\����\\����2.jpg"), 70, 200);
							loadimage(&im6, _T("��Դ�ļ���\\����\\����2bk.jpg"), 70, 200);
							putimage(400, 0, &im6, NOTSRCERASE);
							putimage(400, 0, &im5, SRCINVERT);
							FlushBatchDraw();
							Sleep(500);
						//	mciSendString(_T("close sk4"), NULL, 0, NULL);
}

                                    //��������
void catchit()
{
	IMAGE im15, im16;
	mciSendString(_T("Seek enemy_1 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_1"), NULL, 0, NULL);
	loadimage(&im15, _T("��Դ�ļ���\\����\\����.jpg"));
	loadimage(&im16, _T("��Դ�ļ���\\����\\����bk.jpg"));
	putimage(370, 80, &im16, NOTSRCERASE);
	putimage(370, 80, &im15, SRCINVERT);
	FlushBatchDraw();
	Sleep(500);
		//mciSendString(_T("close enemy_1"), NULL, 0, NULL);
}



									//��������
void fallingStar()
{
	IMAGE im11;
	int x , y ;
	mciSendString(_T("Seek enemy_2 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_2"), NULL, 0, NULL);
	for (x =240, y = 70; x >= 120 && y <= 190; x = x -1, y = y + 1)
	{
		getimage(&im11, x, y, 150, 170);
		IMAGE im9, im10;
		loadimage(&im9, _T("��Դ�ļ���\\����\\����.jpg"));
		loadimage(&im10, _T("��Դ�ļ���\\����\\����bk.jpg"));
		putimage(x, y, &im10, NOTSRCERASE);
		putimage(x, y, &im9, SRCINVERT);
		FlushBatchDraw();
		putimage(x, y, &im11);
	}
	Sleep(500);
	//mciSendString(_T("close enemy_2"), NULL, 0, NULL);
}


									//ˮ��
void waterattack()
{
	IMAGE im9, im10;
	mciSendString(_T("Seek enemy_3 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_3"), NULL, 0, NULL);
	loadimage(&im9, _T("��Դ�ļ���\\����\\ˮ��2.jpg"));
	loadimage(&im10, _T("��Դ�ļ���\\����\\ˮ��2bk.jpg"));
	putimage(100, 130, &im10, NOTSRCERASE);
	putimage(100, 130, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(200);
	IMAGE im11, im12;
	loadimage(&im11, _T("��Դ�ļ���\\����\\ˮ��3.jpg"));
	loadimage(&im12, _T("��Դ�ļ���\\����\\ˮ��3bk.jpg"));
	putimage(95, 130, &im12, NOTSRCERASE);
	putimage(95, 130, &im11, SRCINVERT);
	FlushBatchDraw();
	Sleep(500);
	//	mciSendString(_T("close enemy_3"), NULL, 0, NULL);
}


									//����
void sword()
{
	IMAGE im11;
	int x = 240, y = 90;
	mciSendString(_T("Seek enemy_4 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_4"), NULL, 0, NULL);
	for (x = 240, y = 90; x >= 140 && y <= 140; x = x - 2, y = y + 1)
	{
		getimage(&im11, x, y, 180, 99);
		IMAGE im9, im10;
		loadimage(&im9, _T("��Դ�ļ���\\����\\��.jpg"));
		loadimage(&im10, _T("��Դ�ļ���\\����\\��bk.jpg"));
		putimage(x, y, &im10, NOTSRCERASE);
		putimage(x,y, &im9, SRCINVERT);
		FlushBatchDraw();
		putimage(x, y, &im11);
	}
	Sleep(500);
	//mciSendString(_T("close enemy_4"), NULL, 0, NULL);
}



									//����
void firehigh()
{
	IMAGE im9, im10;
	mciSendString(_T("Seek enemy_5 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_5"), NULL, 0, NULL);
	loadimage(&im9, _T("��Դ�ļ���\\����\\����.jpg"));
	loadimage(&im10, _T("��Դ�ļ���\\����\\����bk.jpg"));
	putimage(70, 140, &im10, NOTSRCERASE);
	putimage(70, 140, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(500);
	putimage(70, 140, &im10, NOTSRCERASE);
	putimage(70, 140, &im9, SRCINVERT);
	FlushBatchDraw();
	putimage(70, 140, &im10, NOTSRCERASE);
	putimage(70, 140, &im9, SRCINVERT);
	Sleep(1000);
	FlushBatchDraw();
	putimage(70, 140, &im10, NOTSRCERASE);
	putimage(70, 140, &im9, SRCINVERT);
	Sleep(1000);
	FlushBatchDraw();
	Sleep(500);
	//Sleep(500);
	//mciSendString(_T("close enemy_5"), NULL, 0, NULL);
}


									//��ʯͷ
void stoneattack()
{
	IMAGE im11;
	int x = 320, y = 140;
	mciSendString(_T("Seek enemy_6 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_6"), NULL, 0, NULL);
	for (x = 320, y = 140; x >= 120 && y <= 240; x = x - 2, y = y + 1)
	{
		getimage(&im11, x, y, 50, 40);
		IMAGE im9, im10;
		loadimage(&im9, _T("��Դ�ļ���\\����\\��ʯ.jpg"));
		loadimage(&im10, _T("��Դ�ļ���\\����\\��ʯbk.jpg"));
		putimage(x, y, &im10, NOTSRCERASE);
		putimage(x, y, &im9, SRCINVERT);
		FlushBatchDraw();
		putimage(x, y, &im11);
	}
	Sleep(500);
			//mciSendString(_T("close enemy_6"), NULL, 0, NULL);
}


									//��ը
void boom()
{
	IMAGE im9, im10;
	mciSendString(_T("Seek enemy_7 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_7"), NULL, 0, NULL);
	loadimage(&im9, _T("��Դ�ļ���\\����\\��ը.jpg"));
	loadimage(&im10, _T("��Դ�ļ���\\����\\��ըbk.jpg"));
	for (int y = 0; y <= 140; y++)
	{
		putimage(30, 200, 250, y, &im10, 0, 0, NOTSRCERASE);
		putimage(30, 200, 250, y, &im9, 0, 0, SRCINVERT);
		FlushBatchDraw();
		Sleep(10);
	}
//Sleep(500);
		//mciSendString(_T("close enemy_7"), NULL, 0, NULL);
}

									//���
void enemyscream()
{
	IMAGE im9, im10;
	mciSendString(_T("Seek enemy_8 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_8"), NULL, 0, NULL);
	loadimage(&im9, _T("��Դ�ļ���\\����\\�з����.jpg"));
	loadimage(&im10, _T("��Դ�ļ���\\����\\�з����bk.jpg"));
	putimage(300, 90,&im10,NOTSRCERASE);
	putimage(300, 90, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(500);
	//mciSendString(_T("close enemy_8"), NULL, 0, NULL);
}


									//��Ҷ�쵶
void rope()
{
	IMAGE im9, im10;
	mciSendString(_T("Seek enemy_1 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_1"), NULL, 0, NULL);
	loadimage(&im9, _T("��Դ�ļ���\\����\\����.jpg"));
	loadimage(&im10, _T("��Դ�ļ���\\����\\����bk.jpg"));
	putimage(70, 230, &im10, NOTSRCERASE);
	putimage(70, 230, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(500);
	//	mciSendString(_T("close enemy_1"), NULL, 0, NULL);
}


									//˺ҧ
void eat()
{
	IMAGE im9, im10;
	mciSendString(_T("Seek enemy_7 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_7"), NULL, 0, NULL);
	loadimage(&im9, _T("��Դ�ļ���\\����\\˺ҧ.jpg"));
	loadimage(&im10, _T("��Դ�ļ���\\����\\˺ҧbk.jpg"));
	putimage(70, 170, &im10, NOTSRCERASE);
	putimage(70, 170, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(500);
		//mciSendString(_T("close enemy_7"), NULL, 0, NULL);
}


									//����
void wind()
{
	IMAGE im9, im10;
	mciSendString(_T("Seek enemy_3 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_3"), NULL, 0, NULL);
	loadimage(&im9, _T("��Դ�ļ���\\����\\����.jpg"));
	loadimage(&im10, _T("��Դ�ļ���\\����\\����bk.jpg"));
	putimage(120, 280, &im10, NOTSRCERASE);
	putimage(120, 280, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(200);
	putimage(120, 265, &im10, NOTSRCERASE);
	putimage(120, 265, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(200);
	putimage(120, 250, &im10, NOTSRCERASE);
	putimage(120, 250, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(200);
	putimage(120, 235, &im10, NOTSRCERASE);
	putimage(120, 235, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(200);
	putimage(120, 220, &im10, NOTSRCERASE);
	putimage(120, 220, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(500);
		//mciSendString(_T("close enemy_3"), NULL, 0, NULL);
}


									//����
void musicattack()
{
	IMAGE im9, im10;
	mciSendString(_T("Seek enemy_5 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_5"), NULL, 0, NULL);
	loadimage(&im9, _T("��Դ�ļ���\\����\\���ֹ���1.jpg"));
	loadimage(&im10, _T("��Դ�ļ���\\����\\���ֹ���1bk.jpg"));
	putimage(310, 80, &im10, NOTSRCERASE);
	putimage(310, 80, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(300);
	IMAGE im11, im12;
	loadimage(&im11, _T("��Դ�ļ���\\����\\���ֹ���2.jpg"));
	loadimage(&im12, _T("��Դ�ļ���\\����\\���ֹ���2bk.jpg"));
	putimage(260, 130, &im12, NOTSRCERASE);
	putimage(260, 130, &im11, SRCINVERT);
	FlushBatchDraw();
	Sleep(300);
	IMAGE im13, im14;
	loadimage(&im13, _T("��Դ�ļ���\\����\\���ֹ���3.jpg"));
	loadimage(&im14, _T("��Դ�ļ���\\����\\���ֹ���3bk.jpg"));
	putimage(180, 140, &im14, NOTSRCERASE);
	putimage(180, 140, &im13, SRCINVERT);
	FlushBatchDraw();
	Sleep(300);
	putimage(220, 160, &im10, NOTSRCERASE);
	putimage(220, 160, &im9, SRCINVERT);
	FlushBatchDraw();
	Sleep(300);
	putimage(230, 240, &im12, NOTSRCERASE);
	putimage(230, 240, &im11, SRCINVERT);
	FlushBatchDraw();
	Sleep(500);
	//	mciSendString(_T("close enemy_5"), NULL, 0, NULL);
}


									//����
void lighton()
{
	IMAGE im5, im6;
	mciSendString(_T("Seek enemy_6 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_6"), NULL, 0, NULL);
	loadimage(&im5, _T("��Դ�ļ���\\����\\����.jpg"));
	loadimage(&im6, _T("��Դ�ļ���\\����\\����bk.jpg"));
	putimage(220, 160, &im6, NOTSRCERASE);
	putimage(220, 160, &im5, SRCINVERT);
	FlushBatchDraw();
	Sleep(500);
		//mciSendString(_T("close enemy_6"), NULL, 0, NULL);
}


									//��������
void star()
{
	IMAGE im5, im6;
	mciSendString(_T("Seek enemy_1 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_1"), NULL, 0, NULL);
	loadimage(&im5, _T("��Դ�ļ���\\����\\����.jpg"));
	loadimage(&im6, _T("��Դ�ļ���\\����\\����bk.jpg"));
	putimage(90, 200, &im6, NOTSRCERASE);
	putimage(90, 200, &im5, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	putimage(90, 240, &im6, NOTSRCERASE);
	putimage(90, 240, &im5, SRCINVERT);
	FlushBatchDraw();
	Sleep(300);
	putimage(110, 205, &im6, NOTSRCERASE);
	putimage(110, 205, &im5, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	putimage(140, 200, &im6, NOTSRCERASE);
	putimage(140, 200, &im5, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	putimage(150, 230, &im6, NOTSRCERASE);
	putimage(150, 230, &im5, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	putimage(110, 230, &im6, NOTSRCERASE);
	putimage(110, 230, &im5, SRCINVERT);
	putimage(110, 250, &im6, NOTSRCERASE);
	putimage(110, 250, &im5, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	putimage(95, 255, &im6, NOTSRCERASE);
	putimage(95, 255, &im5, SRCINVERT);
	putimage(135, 260, &im6, NOTSRCERASE);
	putimage(135, 260, &im5, SRCINVERT);
	FlushBatchDraw();
	Sleep(100);
	putimage(110, 280, &im6, NOTSRCERASE);
	putimage(110, 280, &im5, SRCINVERT);
	putimage(100, 290, &im6, NOTSRCERASE);
	putimage(100, 290, &im5, SRCINVERT);
	FlushBatchDraw();
	Sleep(500);
	//	mciSendString(_T("close enemy_1"), NULL, 0, NULL);
}


									//�����
void windattack()
{
	IMAGE im11;
	int x = 320, y = 140;
	mciSendString(_T("Seek enemy_2 to start"), NULL, 0, NULL);
	mciSendString(_T("play enemy_2"), NULL, 0, NULL);
	for (x = 320, y = 140; x >= 120 && y <= 240; x = x - 2, y = y + 1)
	{
		getimage(&im11, x, y, 80, 46);
		IMAGE im9, im10;
		loadimage(&im9, _T("��Դ�ļ���\\����\\�絶.jpg"));
		loadimage(&im10, _T("��Դ�ļ���\\����\\�絶bk.jpg"));
		putimage(x, y, &im10, NOTSRCERASE);
		putimage(x, y, &im9, SRCINVERT);
		FlushBatchDraw();
		putimage(x, y, &im11);
	}
	Sleep(500);
			//mciSendString(_T("close enemy_2"), NULL, 0, NULL);
}