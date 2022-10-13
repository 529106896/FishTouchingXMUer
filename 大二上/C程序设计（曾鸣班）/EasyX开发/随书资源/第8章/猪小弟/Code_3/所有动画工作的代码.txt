			  //level_0相关数据初始化
IMAGE level0_bk;	//背景图
IMAGE pooyan_blue_0, pooyan_blue_0_bk, pooyan_blue_1, pooyan_blue_1_bk;
IMAGE pooyan_pink_0, pooyan_pink_0_bk, pooyan_pink_1, pooyan_pink_1_bk;
IMAGE pooyan_red_0, pooyan_red_0_bk, pooyan_red_1, pooyan_red_1_bk;
IMAGE ball_0, ball_0_bk, ball_1, ball_1_bk;
IMAGE wolf_0, wolf_0_bk, wolf_1, wolf_1_bk;
int pooyan_blue_0_x = 640, pooyan_blue_0_y = 425;
int pooyan_pink_0_x = 640, pooyan_pink_0_y = 425;
int pooyan_red_0_x = 640, pooyan_red_0_y = 425;
int ball_0_x = 640, ball_0_y = 400;
int wolf_0_x = 640, wolf_0_y = 425;
int score = 0;	//分数

//动画1相关数据初始化
IMAGE bk;
IMAGE pooyan_pink_3_bk_next, pooyan_pink_3_next, pooyan_pink_4_bk_next, pooyan_pink_4_next;
IMAGE wolf_3_bk_right, wolf_3_right, wolf_4_bk_right, wolf_4_right;
IMAGE pooyan_pink_3, pooyan_pink_3_bk, pooyan_pink_4, pooyan_pink_4_bk;
IMAGE pooyan_red_3, pooyan_red_3_bk, pooyan_red_4, pooyan_red_4_bk;
IMAGE wolf_3, wolf_3_bk, wolf_4, wolf_4_bk;
int pooyan_pink_3_x = 640, pooyan_pink_3_y = 425;
int pooyan_red_3_x = 640, pooyan_red_3_y = 425;
int pooyan_pink_3_next_x = 240, pooyan_pink_3_next_y = 425;
int wolf_1_right_x = 0, wolf_1_right_y = 425;
int wolf_1_left_x = 325, wolf_1_left_y = 425;
//动画2相关数据初始化
IMAGE pooyan_blue_5, pooyan_blue_5_bk, pooyan_blue_6, pooyan_blue_6_bk;
IMAGE pooyan_pink_5, pooyan_pink_5_bk, pooyan_pink_6, pooyan_pink_6_bk;
IMAGE pooyan_red_5, pooyan_red_5_bk, pooyan_red_6, pooyan_red_6_bk;
IMAGE ball_5, ball_5_bk, ball_6, ball_6_bk;
IMAGE wolf_5, wolf_5_bk, wolf_6, wolf_6_bk;
int pooyan_blue_4_x = 640, pooyan_blue_4_y = 425;
int pooyan_pink_4_x = 640, pooyan_pink_4_y = 425;
int pooyan_red_4_x = 640, pooyan_red_4_y = 425;
int ball_4_x = 640, ball_4_y = 400;
int wolf_4_x = 640, wolf_4_y = 425;
void startup_0();
void show_0();
void update_without_input_0();
void update_with_input_0();

void startup_3();
void show_3();
void update_without_input_3();

void startup_4();
void show_4();
void update_without_input_4();
void startup_0()
{
	HWND hWnd = GetHWnd();
	SetWindowText(hWnd, _T("猪小弟"));//获得窗口句柄
	loadimage(&level0_bk, L"pooyan.jpg");	//背景图
	loadimage(&pooyan_blue_0, L"pooyan_blue0.jpg");
	loadimage(&pooyan_blue_0_bk, L"pooyan_blue0_bk.jpg");
	loadimage(&pooyan_blue_1, L"pooyan_blue1.jpg");
	loadimage(&pooyan_blue_1_bk, L"pooyan_blue1_bk.jpg");
	loadimage(&pooyan_pink_0, L"pooyan_pink0.jpg");
	loadimage(&pooyan_pink_0_bk, L"pooyan_pink0_bk.jpg");
	loadimage(&pooyan_pink_1, L"pooyan_pink1.jpg");
	loadimage(&pooyan_pink_1_bk, L"pooyan_pink1_bk.jpg");
	loadimage(&pooyan_red_0, L"pooyan_red0.jpg");
	loadimage(&pooyan_red_0_bk, L"pooyan_red0_bk.jpg");
	loadimage(&pooyan_red_1, L"pooyan_red1.jpg");
	loadimage(&pooyan_red_1_bk, L"pooyan_red1_bk.jpg");
	loadimage(&ball_0, L"ball0.jpg");
	loadimage(&ball_0_bk, L"ball0_bk.jpg");
	loadimage(&ball_1, L"ball1.jpg");
	loadimage(&ball_1_bk, L"ball1_bk.jpg");
	loadimage(&wolf_0, L"wolf0.jpg");
	loadimage(&wolf_0_bk, L"wolf0_bk.jpg");
	loadimage(&wolf_1, L"wolf1.jpg");
	loadimage(&wolf_1_bk, L"wolf1_bk.jpg");

	mciSendString(_T("open bk0.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
	BeginBatchDraw();
}

void show_0()
{
	putimage(0, 0, &level0_bk);  //背景
	int i, j;
	for (j = 0; j < HEIGHT; j++)
	{
		for (i = 0; i < WIDTH; i++)
		{
			if (i == wolf_0_x && j == wolf_0_y && wolf_0_x > 0)
			{
				Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(wolf_0_x, wolf_0_y, &wolf_0_bk, NOTSRCERASE);
					putimage(wolf_0_x, wolf_0_y, &wolf_0, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(wolf_0_x, wolf_0_y, &wolf_1_bk, NOTSRCERASE);
					putimage(wolf_0_x, wolf_0_y, &wolf_1, SRCINVERT);
				}
			}
			if (i == pooyan_blue_0_x && j == pooyan_blue_0_y && pooyan_blue_0_x > 0)
			{
				if (wolf_0_x == 0)
					Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(pooyan_blue_0_x, pooyan_blue_0_y, &pooyan_blue_0_bk, NOTSRCERASE);
					putimage(pooyan_blue_0_x, pooyan_blue_0_y, &pooyan_blue_0, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(pooyan_blue_0_x, pooyan_blue_0_y, &pooyan_blue_1_bk, NOTSRCERASE);
					putimage(pooyan_blue_0_x, pooyan_blue_0_y, &pooyan_blue_1, SRCINVERT);
				}
			}
			if (i == pooyan_pink_0_x && j == pooyan_pink_0_y && pooyan_pink_0_x > 0)
			{
				if (pooyan_blue_0_x == 0)
					Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(pooyan_pink_0_x, pooyan_pink_0_y, &pooyan_pink_0_bk, NOTSRCERASE);
					putimage(pooyan_pink_0_x, pooyan_blue_0_y, &pooyan_pink_0, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(pooyan_pink_0_x, pooyan_pink_0_y, &pooyan_pink_1_bk, NOTSRCERASE);
					putimage(pooyan_pink_0_x, pooyan_blue_0_y, &pooyan_pink_1, SRCINVERT);
				}
			}
			if (i == ball_0_x && j == ball_0_y && wolf_0_x <= 428)
			{
				if (ball_0_y > 380)
				{
					if (i / 10 % 2 == 0)
					{
						putimage(ball_0_x, ball_0_y, &ball_0_bk, NOTSRCERASE);
						putimage(ball_0_x, ball_0_y, &ball_0, SRCINVERT);
					}
					if (i / 10 % 2 == 1)
					{
						putimage(ball_0_x, ball_0_y, &ball_1_bk, NOTSRCERASE);
						putimage(ball_0_x, ball_0_y, &ball_1, SRCINVERT);
					}
				}
				if (ball_0_y <= 380)
				{
					if (j / 10 % 2 == 0)
					{
						putimage(ball_0_x, ball_0_y, &ball_0_bk, NOTSRCERASE);
						putimage(ball_0_x, ball_0_y, &ball_0, SRCINVERT);
					}
					if (j / 10 % 2 == 1)
					{
						putimage(ball_0_x, ball_0_y, &ball_1_bk, NOTSRCERASE);
						putimage(ball_0_x, ball_0_y, &ball_1, SRCINVERT);
					}
				}
			}
			if (i == pooyan_red_0_x && j == pooyan_red_0_y && pooyan_red_0_x > 0)
			{
				if (pooyan_pink_0_x == 0)
					Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(pooyan_red_0_x, pooyan_red_0_y, &pooyan_red_0_bk, NOTSRCERASE);
					putimage(pooyan_red_0_x, pooyan_red_0_y, &pooyan_red_0, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(pooyan_red_0_x, pooyan_red_0_y, &pooyan_red_1_bk, NOTSRCERASE);
					putimage(pooyan_red_0_x, pooyan_red_0_y, &pooyan_red_1, SRCINVERT);
				}
			}
		}
		
	}
	FlushBatchDraw();
}

void update_without_input_0()
{

	if (wolf_0_x > 0)
		wolf_0_x = wolf_0_x - 10;
	if (wolf_0_x <= 540 && pooyan_blue_0_x > 0)
		pooyan_blue_0_x = pooyan_blue_0_x - 10;
	if (wolf_0_x <= 440 && pooyan_pink_0_x > 0)
		pooyan_pink_0_x = pooyan_pink_0_x - 10;
	if (wolf_0_x <= 428)
	{
		if (ball_0_x > 175)
			ball_0_x = ball_0_x - 10;
		else if (ball_0_y > 280 && pooyan_red_0_x > 130)
			ball_0_y = ball_0_y - 10;
	}
	if (wolf_0_x <= 340 && pooyan_red_0_x > 0)
		pooyan_red_0_x = pooyan_red_0_x - 10;
}

void update_with_input_0()
{
	char input;
	if (kbhit())
	{
		input = getch();
		if (input == 's' && ball_0_y == 280)
			ball_0_y = 340;
		if (input == 'w' && ball_0_y == 340)
			ball_0_y = 280;
		if (input == 13 && ball_0_y == 280)
			act = 1;
	}
}

void startup_3()
{
	loadimage(&bk, L"bk.jpg");
	loadimage(&pooyan_pink_3, L"pooyan_pink0.jpg");
	loadimage(&pooyan_pink_3_bk, L"pooyan_pink0_bk.jpg");
	loadimage(&pooyan_pink_4, L"pooyan_pink1.jpg");
	loadimage(&pooyan_pink_4_bk, L"pooyan_pink1_bk.jpg");
	loadimage(&pooyan_red_3, L"pooyan_red0.jpg");
	loadimage(&pooyan_red_3_bk, L"pooyan_red0_bk.jpg");
	loadimage(&pooyan_red_4, L"pooyan_red1.jpg");
	loadimage(&pooyan_red_4_bk, L"pooyan_red1_bk.jpg");
	loadimage(&wolf_3, L"wolf0.jpg");
	loadimage(&wolf_3_bk, L"wolf0_bk.jpg");
	loadimage(&wolf_4, L"wolf1.jpg");
	loadimage(&wolf_4_bk, L"wolf1_bk.jpg");
	loadimage(&pooyan_pink_3_bk_next, L"pooyan_pink0_bk_next.jpg");
	loadimage(&pooyan_pink_3_next, L"pooyan_pink0_next.jpg");
	loadimage(&pooyan_pink_4_bk_next, L"pooyan_pink1_bk_next.jpg");
	loadimage(&pooyan_pink_4_next, L"pooyan_pink1_next.jpg");
	loadimage(&wolf_3_bk_right, L"wolf1_bk_right.jpg");
	loadimage(&wolf_3_right, L"wolf1_right.jpg");
	loadimage(&wolf_4_bk_right, L"wolf2_bk_right.jpg");
	loadimage(&wolf_4_right, L"wolf2_right.jpg");

	BeginBatchDraw();
}

void show_3()
{
	putimage(0, 0, &bk);
	int j;
	for (j = 0; j < WIDTH; j++)
	{
		if (j == pooyan_pink_0_x && pooyan_pink_0_x >= 240)
		{
			Sleep(100);
			if (j / 10 % 2 == 0)
			{
				putimage(pooyan_pink_3_x, pooyan_pink_3_y, &pooyan_pink_3_bk, NOTSRCERASE);
				putimage(pooyan_pink_3_x, pooyan_pink_3_y, &pooyan_pink_3, SRCINVERT);
			}
			if (j / 10 % 2 == 1)
			{
				putimage(pooyan_pink_3_x, pooyan_pink_3_y, &pooyan_pink_4_bk, NOTSRCERASE);
				putimage(pooyan_pink_3_x, pooyan_pink_3_y, &pooyan_pink_4, SRCINVERT);
			}
		}
		if (j == pooyan_pink_3_next_x && pooyan_pink_3_x <= 230 && pooyan_pink_3_next_x - wolf_1_right_x > 5)
		{
			if (wolf_1_right_x <= 0)
				Sleep(100);
			if (j / 10 % 2 == 0)
			{
				putimage(pooyan_pink_3_next_x, pooyan_pink_3_next_y, &pooyan_pink_3_bk_next, NOTSRCERASE);
				putimage(pooyan_pink_3_next_x, pooyan_pink_3_next_y, &pooyan_pink_3_next, SRCINVERT);
			}
			if (j / 10 % 2 == 1)
			{
				putimage(pooyan_pink_3_next_x, pooyan_pink_3_next_y, &pooyan_pink_4_bk_next, NOTSRCERASE);
				putimage(pooyan_pink_3_next_x, pooyan_pink_3_next_y, &pooyan_pink_4_next, SRCINVERT);
			}
		}
		if (j == wolf_1_right_x && pooyan_pink_3_x <= 230 && pooyan_pink_3_next_x - wolf_1_right_x > 5)
		{
			Sleep(100);
			if (j / 10 % 2 == 0)
			{
				putimage(wolf_1_right_x, wolf_1_right_y, &wolf_3_bk_right, NOTSRCERASE);
				putimage(wolf_1_right_x, wolf_1_right_y, &wolf_3_right, SRCINVERT);
			}
			if (j / 10 % 2 == 1)
			{
				putimage(wolf_1_right_x, wolf_1_right_y, &wolf_4_bk_right, NOTSRCERASE);
				putimage(wolf_1_right_x, wolf_1_right_y, &wolf_4_right, SRCINVERT);
			}
		}
		if (j == wolf_1_left_x && pooyan_pink_3_next_x - wolf_1_right_x < 5)
		{
			Sleep(100);
			if (j / 10 % 2 == 0)
			{
				putimage(wolf_1_left_x, wolf_1_left_y, &pooyan_pink_4_bk, NOTSRCERASE);
				putimage(wolf_1_left_x, wolf_1_left_y, &pooyan_pink_4, SRCINVERT);
				putimage(wolf_1_left_x, wolf_1_left_y, &wolf_4_bk, NOTSRCERASE);
				putimage(wolf_1_left_x, wolf_1_left_y, &wolf_4, SRCINVERT);
			}
			if (j / 10 % 2 == 1)
			{
				putimage(wolf_1_left_x, wolf_1_left_y, &pooyan_pink_4_bk, NOTSRCERASE);
				putimage(wolf_1_left_x, wolf_1_left_y, &pooyan_pink_4, SRCINVERT);
				putimage(wolf_1_left_x, wolf_1_left_y, &wolf_3_bk, NOTSRCERASE);
				putimage(wolf_1_left_x, wolf_1_left_y, &wolf_3, SRCINVERT);
			}
		}
		if (j == pooyan_red_3_x && wolf_1_left_x <= 320)
		{
			if (wolf_1_left_x < 0)
				Sleep(100);
			if (j / 10 % 2 == 0)
			{
				putimage(pooyan_red_3_x, pooyan_red_3_y, &pooyan_red_3_bk, NOTSRCERASE);
				putimage(pooyan_red_3_x, pooyan_red_3_y, &pooyan_red_3, SRCINVERT);
			}
			if (j / 10 % 2 == 1)
			{
				putimage(pooyan_red_3_x, pooyan_red_3_y, &pooyan_red_4_bk, NOTSRCERASE);
				putimage(pooyan_red_3_x, pooyan_red_3_y, &pooyan_red_4, SRCINVERT);
			}
		}
	}
	FlushBatchDraw();
}

void update_without_input_3()
{
	if (pooyan_pink_3_x >= 240 && wolf_1_right_x < pooyan_pink_3_next_x)
		pooyan_pink_3_x = pooyan_pink_3_x - 10;
	if (pooyan_pink_3_x <= 240 && pooyan_pink_3_next_x - wolf_1_right_x > 5)
		pooyan_pink_3_next_x = pooyan_pink_3_next_x + 10;
	if (pooyan_pink_3_x <= 240 && pooyan_pink_3_next_x - wolf_1_right_x > 5)
		wolf_1_right_x = wolf_1_right_x + 30;
	if (wolf_1_left_x >= 0 && pooyan_pink_3_next_x - wolf_1_right_x < 5)
		wolf_1_left_x = wolf_1_left_x - 30;
	if (pooyan_red_3_x >= 0 && wolf_1_left_x <= 320)
		pooyan_red_3_x = pooyan_red_3_x - 30;
}

void startup_4()
{
	loadimage(&bk, L"bk.jpg");
	loadimage(&pooyan_blue_5, L"pooyan_blue0.jpg");
	loadimage(&pooyan_blue_5_bk, L"pooyan_blue0_bk.jpg");
	loadimage(&pooyan_blue_6, L"pooyan_blue1.jpg");
	loadimage(&pooyan_blue_6_bk, L"pooyan_blue1_bk.jpg");
	loadimage(&pooyan_pink_5, L"pooyan_pink0.jpg");
	loadimage(&pooyan_pink_5_bk, L"pooyan_pink0_bk.jpg");
	loadimage(&pooyan_pink_6, L"pooyan_pink1.jpg");
	loadimage(&pooyan_pink_6_bk, L"pooyan_pink1_bk.jpg");
	loadimage(&pooyan_red_5, L"pooyan_red0.jpg");
	loadimage(&pooyan_red_5_bk, L"pooyan_red0_bk.jpg");
	loadimage(&pooyan_red_6, L"pooyan_red1.jpg");
	loadimage(&pooyan_red_6_bk, L"pooyan_red1_bk.jpg");
	loadimage(&wolf_5, L"wolf0.jpg");
	loadimage(&wolf_5_bk, L"wolf0_bk.jpg");
	loadimage(&wolf_6, L"wolf1.jpg");
	loadimage(&wolf_6_bk, L"wolf1_bk.jpg");

	BeginBatchDraw();
}

void show_4()
{
	putimage(0, 0, &bk);  //背景
	int i, j;
	for (j = 0; j < HEIGHT; j++)
	{
		for (i = 0; i < WIDTH; i++)
		{
			if (i == wolf_4_x && j == wolf_4_y && wolf_4_x > 0)
			{
				Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(wolf_4_x, wolf_4_y, &wolf_5_bk, NOTSRCERASE);
					putimage(wolf_4_x, wolf_4_y, &wolf_5, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(wolf_4_x, wolf_4_y, &wolf_6_bk, NOTSRCERASE);
					putimage(wolf_4_x, wolf_4_y, &wolf_6, SRCINVERT);
				}
			}
			if (i == pooyan_blue_4_x && j == pooyan_blue_4_y && pooyan_blue_4_x > 0)
			{
				if (wolf_4_x == 0)
					Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(pooyan_blue_4_x, pooyan_blue_4_y, &pooyan_blue_5_bk, NOTSRCERASE);
					putimage(pooyan_blue_4_x, pooyan_blue_4_y, &pooyan_blue_5, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(pooyan_blue_4_x, pooyan_blue_4_y, &pooyan_blue_6_bk, NOTSRCERASE);
					putimage(pooyan_blue_4_x, pooyan_blue_4_y, &pooyan_blue_6, SRCINVERT);
				}
			}
			if (i == pooyan_pink_4_x && j == pooyan_pink_4_y && pooyan_pink_4_x > 0)
			{
				if (pooyan_blue_4_x == 0)
					Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(pooyan_pink_4_x, pooyan_pink_4_y, &pooyan_pink_5_bk, NOTSRCERASE);
					putimage(pooyan_pink_4_x, pooyan_blue_4_y, &pooyan_pink_5, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(pooyan_pink_4_x, pooyan_pink_4_y, &pooyan_pink_6_bk, NOTSRCERASE);
					putimage(pooyan_pink_4_x, pooyan_blue_4_y, &pooyan_pink_6, SRCINVERT);
				}
			}
			if (i == pooyan_red_4_x && j == pooyan_red_4_y && pooyan_red_4_x > 0)
			{
				if (pooyan_pink_4_x == 0)
					Sleep(100);
				if (i / 10 % 2 == 0)
				{
					putimage(pooyan_red_4_x, pooyan_red_4_y, &pooyan_red_5_bk, NOTSRCERASE);
					putimage(pooyan_red_4_x, pooyan_red_4_y, &pooyan_red_5, SRCINVERT);
				}
				if (i / 10 % 2 == 1)
				{
					putimage(pooyan_red_4_x, pooyan_red_4_y, &pooyan_red_6_bk, NOTSRCERASE);
					putimage(pooyan_red_4_x, pooyan_red_4_y, &pooyan_red_6, SRCINVERT);
				}
			}
		}
	}
	FlushBatchDraw();
}

void update_without_input_4()
{
	if (wolf_4_x > 0)
		wolf_4_x = wolf_4_x - 10;
	if (wolf_4_x <= 540 && pooyan_blue_4_x > 0)
		pooyan_blue_4_x = pooyan_blue_4_x - 10;
	if (wolf_4_x <= 440 && pooyan_pink_4_x > 0)
		pooyan_pink_4_x = pooyan_pink_4_x - 10;
	if (wolf_4_x <= 340 && pooyan_red_4_x > 0)
		pooyan_red_4_x = pooyan_red_4_x - 10;
}

