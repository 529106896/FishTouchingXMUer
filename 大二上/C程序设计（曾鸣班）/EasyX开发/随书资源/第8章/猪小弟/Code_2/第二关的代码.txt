//level_2

IMAGE level2_bk;	//背景图
IMAGE stone_bk, stone_front;//石头的图

//第二关的变量
int pooyan_red_x, pooyan_red_y;//定义猪妈的坐标
int ball_x[WOLF_NUM_2], ball_y[WOLF_NUM_2];//气球的坐标
int wolf_x[WOLF_NUM_2], wolf_y[WOLF_NUM_2];//狼的坐标
int arrow_x[ARROW_NUM], arrow_y[ARROW_NUM];//箭的坐标
int wolf_sign[WOLF_NUM_2];//标记屏幕上的每一只狼用于判断狼是否出现，-1表示没有出现，1表示出现
int wolf_count;//用于控制屏幕上每一只狼
int ball_count;//用于控制屏幕上每一只气球
int count_shoot;//统计射了几只箭并便于后续控制
int shoot[ARROW_NUM];//判断是否射射箭的数组，-1表示没有出现，1表示出现
int rand_space;//随机出现的狼之间的间隔距离，避免重合
int string_y;//绳子纵坐标
int wolf_up_x[WOLF_NUM_2];//狼上升的位置的横坐标
int ball_up_x[WOLF_NUM_2];//气球上升时的横坐标
int ball_sign[WOLF_NUM_2];//标记每一个气球，-1表示没有出现，1表示出现
int stone_x;//石头的横纵坐标
int stone_y;
int arrow_num;//统计屏幕上箭的个数，确保屏幕上存在箭的个数固定；
int ball_interval[WOLF_NUM_2];//用来给爆炸后的气球延时处理
int wolf_interval[WOLF_NUM_2];//给死后的狼延时处理
int pooyan_red_dead_x;
int pooyan_red_dead_y;//处理猪妈死亡后的坐标
int pooyan_exit;//判断猪妈是否存活，1表示存活，2表示中弹死亡
int put_wolf=0;//推石头的狼
void main()
{
	initgraph(WIDTH, HEIGHT);//定义一张640*600的游戏画布

	srand(time(NULL));
	startup_0();
	while (act == 0)
	{
		show_0();
		update_without_input_0();
		update_with_input_0();
	}

	startup_3();
	while (act == 1)
	{
		show_3();
		update_without_input_3();
		if (pooyan_red_3_x <= 0)
			break;
	}

	startup_1();
	while (act == 1)
	{
		show_1();//画出一帧图
		update_without_input_1();//更新无关输入的变量
		update_with_input_1();//更新输入
		if (num >= 10)
			break;
	}

	startup_4();
	while (act == 1)
	{
		show_4();
		update_without_input_4();
		if (pooyan_red_4_x <= 0)
			break;
	}

	startup_2();
	while (act == 1)
	{
		show_2();//绘图
		update_without_input_2();//不需要输入的更新
		update_with_input_2();//需要输入的更新
	}
	gameover();
	getch();
	//EndBatchDraw();
	closegraph();
}
void startup_2()
{
	int i;
//	put_wolf = 0;//初始化推石头的狼为0；
	stone_x = 450;
	stone_y = 20;//石头的初始坐标
	pooyan_red_x = 500;
	pooyan_red_y = 120;//猪妈的初始坐标
	pooyan_exit = 1;//初始化猪妈存活
	for (i = 0; i < ARROW_NUM; i++)
	{
		shoot[i] = -1;//没有箭射出
		arrow_x[i] = pooyan_red_x - 25;
		arrow_y[i] = pooyan_red_y + 43;//初始化箭的坐标
	}
	count_shoot = -1;
	arrow_num = 0;//初始化屏幕上没有箭时计数为0；
	for (i = 0; i < WOLF_NUM_2; i++)//初始化狼的坐标
	{
		wolf_x[i] = 0;
		wolf_y[i] = 505;
		wolf_sign[i] = -1;//初始化将所有狼标记为-1表示没有狼出现
		wolf_up_x[i] = rand() % 250 + 90;//初始化狼和气球上升时的坐标
		wolf_interval[i] = { 0 };
	}
	wolf_count = -1;//初始化屏幕上没有狼,也没有气球；
	ball_count = -1;
	rand_space = rand() % 2500 + 1000;//控制狼与狼之间的随机间隔
	for (i = 0; i < WOLF_NUM_2; i++)//初始化气球坐标
	{
		ball_x[i] = wolf_x[i];
		ball_y[i] = wolf_y[i];//通过图层遮盖让气球和狼完美衔接
		ball_sign[i] = -1;
		ball_up_x[i] = wolf_up_x[i];
		ball_interval[i] = { 0 };
	}
	loadimage(&level2_bk, L"level2_bk.jpg");	//背景图
	loadimage(&stone_bk, L"stone_bk.jpg");
	loadimage(&stone_front, L"stone_front.jpg");//石头的图
	loadimage(&level1_pooyan_red_bk, L"level1_pooyan_red_bk.jpg");
	loadimage(&level1_pooyan_red_front, L"level1_pooyan_red_front.jpg");//猪妈的图
	loadimage(&pooyan_red_down_bk, L"pooyan_red_down_bk.jpg");
	loadimage(&pooyan_red_down_front, L"pooyan_red_down_front.jpg");
	loadimage(&pooyan_red1_down_bk, L"pooyan_red1_down_bk.jpg");
	loadimage(&pooyan_red1_down_front, L"pooyan_red1_down_front.jpg");//猪妈下坠的图
	loadimage(&arrow_bk, L"arrow_bk.jpg");
	loadimage(&arrow_front, L"arrow_front.jpg");//骨箭的图
	loadimage(&arrow_down_bk, L"arrow_down_bk.jpg");
	loadimage(&arrow_down_front, L"arrow_down_front.jpg");//骨箭下坠的图
	loadimage(&level1_ball_bk, L"level1_ball_bk.jpg");//气球的图
	loadimage(&level1_ball_front, L"level1_ball_front.jpg");
	loadimage(&ball_red_exploded_bk, L"ball_red_exploded_bk.jpg");
	loadimage(&ball_red_exploded_front, L"ball_red_exploded_front.jpg");//气球爆炸的图
	loadimage(&level_wolf_bk, L"level_wolf_bk.jpg");
	loadimage(&level_wolf_front, L"level_wolf_front.jpg");//狼的图
	loadimage(&rope_bk, L"rope_bk.jpg");
	loadimage(&rope_front, L"rope_front.jpg");//绳子的图
	loadimage(&wolf1_bk_right, L"wolf1_bk_right.jpg");
	loadimage(&wolf1_right, L"wolf1_right.jpg");
	loadimage(&wolf2_bk_right, L"wolf2_bk_right.jpg");
	loadimage(&wolf2_right, L"wolf2_right.jpg");//狼向右行走的图
	loadimage(&wolf_stop_bk1, L"wolf_stop_bk1.jpg");
	loadimage(&wolf_stop_front1, L"wolf_stop_front1.jpg");
	loadimage(&wolf_stop_bk2, L"wolf_stop_bk2.jpg");
	loadimage(&wolf_stop_front2, L"wolf_stop_front2.jpg");//狼被击中的图
	loadimage(&wolf_dead_bk1, L"wolf_dead_bk1.jpg");
	loadimage(&wolf_dead_front1, L"wolf_dead_front1.jpg");
	loadimage(&wolf_dead_bk2, L"wolf_dead_bk2.jpg");
	loadimage(&wolf_dead_front2, L"wolf_dead_front2.jpg");//狼下坠的图
	loadimage(&bullet_bk, L"bullet_bk.jpg");
	loadimage(&bullet_front, L"bullet_front.jpg");//子弹的图
	loadimage(&rope_bk, L"rope_bk.jpg");
	loadimage(&rope_front, L"rope_front.jpg");//绳子的图
	loadimage(&bone_bk, L"level1_bone_bk.jpg");
	loadimage(&bone_front, L"level1_bone_front.jpg");//肉骨棒的图
	HWND hWnd = GetHWnd();
	mciSendString(L"close bkmusic", NULL, 0, NULL);

	SetWindowText(hWnd, _T("猪小弟"));//获得窗口句柄

	mciSendString(L"open bk1.mp3 alias bkm", NULL, 0, NULL);
	mciSendString(L"play bkm repeat", NULL, 0, NULL);
	BeginBatchDraw();
}

void show_2()
{
	int i;
	putimage(0, 0, &level2_bk);//背景图
							   //箭的模块
	for (i = 0; i < ARROW_NUM; i++)
	{
		if (shoot[i] == 1)
		{
			putimage(arrow_x[i], arrow_y[i], &arrow_bk, NOTSRCERASE);
			putimage(arrow_x[i], arrow_y[i], &arrow_front, SRCINVERT);//箭的图
		}
		if (shoot[i] == 2)
		{
			putimage(arrow_x[i], arrow_y[i], &arrow_down_bk, NOTSRCERASE);
			putimage(arrow_x[i], arrow_y[i], &arrow_down_front, SRCINVERT);//骨箭下坠的图
		}
	}
	putimage(stone_x, stone_y, &stone_bk, NOTSRCERASE);
	putimage(stone_x, stone_y, &stone_front, SRCINVERT);//石头的图
	if (pooyan_exit == 1)
	{
		putimage(pooyan_red_x, pooyan_red_y, &level1_pooyan_red_bk, NOTSRCERASE);
		putimage(pooyan_red_x, pooyan_red_y, &level1_pooyan_red_front, SRCINVERT);//猪妈的图
	}
	if (pooyan_exit == 2)
	{
		putimage(pooyan_red_dead_x, pooyan_red_dead_y + 30, &pooyan_red1_down_bk, NOTSRCERASE);
		putimage(pooyan_red_dead_x, pooyan_red_dead_y + 30, &pooyan_red1_down_front, SRCINVERT);
		putimage(pooyan_red_x, pooyan_red_y, &pooyan_red_down_bk, NOTSRCERASE);
		putimage(pooyan_red_x, pooyan_red_y, &pooyan_red_down_front, SRCINVERT);//猪妈下坠的图
	}
	putimage(530, 113, 20, pooyan_red_y - 110, &rope_bk, 530, 120, NOTSRCERASE);
	putimage(530, 113, 20, pooyan_red_y - 110, &rope_front, 530, 120, SRCINVERT);//绳子的图
																				 //狼的模块
	for (i = 0; i < WOLF_NUM_2; i++)
	{
		if (wolf_sign[i] == 1)
		{
			//实现狼向右移动的动画
			if (wolf_x[i] < wolf_up_x[i])
			{
				if (wolf_x[i] % 10 >= 5)//这里没有采用%2的奇偶数切换，那样会让狼跑的太快。
				{
					putimage(wolf_x[i], wolf_y[i], &wolf1_bk_right, NOTSRCERASE);
					putimage(wolf_x[i], wolf_y[i], &wolf1_right, SRCINVERT);//狼向右移动的图1
				}
				else if (wolf_x[i] % 10 < 5)
				{
					putimage(wolf_x[i], wolf_y[i], &wolf2_bk_right, NOTSRCERASE);
					putimage(wolf_x[i], wolf_y[i], &wolf2_right, SRCINVERT);//狼向右移动的图2
				}
			}
			//狼开始上升
			else if (wolf_x[i] >= wolf_up_x[i])
			{
				putimage(wolf_x[i], wolf_y[i], &level_wolf_bk, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i], &level_wolf_front, SRCINVERT);//狼的图
			}
		}
		if (wolf_sign[i] == 2)//如果狼被击中,先进行延时
		{
			if (wolf_interval[i] % 20 <= 10)
			{
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_stop_bk1, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_stop_front1, SRCINVERT);
			}
			else if (wolf_interval[i] % 20 > 10)
			{
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_stop_bk2, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_stop_front2, SRCINVERT);
			}
		}
		if (wolf_sign[i] == 3)//延时后进入快速下落状态
		{
			if (wolf_y[i] % 80 <= 40)
			{
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_dead_bk1, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_dead_front1, SRCINVERT);
			}
			else if (wolf_y[i] % 80 > 40)
			{
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_dead_bk2, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i] + 50, &wolf_dead_front2, SRCINVERT);
			}
		}
		if (wolf_sign[i] == 4)
		{
			if (wolf_x[i] % 10 <= 5)
			{
				putimage(wolf_x[i], wolf_y[i] + 20, &wolf1_bk_right, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i] + 20, &wolf1_right, SRCINVERT);
			}
			else if (wolf_x[i] % 10 > 5)
			{
				putimage(wolf_x[i], wolf_y[i] + 20, &wolf2_bk_right, NOTSRCERASE);
				putimage(wolf_x[i], wolf_y[i] + 20, &wolf2_right, SRCINVERT);
			}
		}
	}
	//气球的模块
	for (i = 0; i < WOLF_NUM_2; i++)
	{
		if ((ball_sign[i] == 1) && (wolf_x[i] >= wolf_up_x[i]))//狼到达指定位置气球也可以登场了
		{
			putimage(ball_x[i], ball_y[i], &level1_ball_bk, NOTSRCERASE);
			putimage(ball_x[i], ball_y[i], &level1_ball_front, SRCINVERT);//气球的图
		}
		if (ball_sign[i] == 2)
		{
			putimage(ball_x[i], ball_y[i], &ball_red_exploded_bk, NOTSRCERASE);
			putimage(ball_x[i], ball_y[i], &ball_red_exploded_front, SRCINVERT);//气球爆炸的图
		}
	}
	//用来记录分数
	TCHAR s[80];
	_stprintf_s(s, _T("%06d"), score);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(2, 5, _T("分数:"));
	outtextxy(55, 5, s);
	FlushBatchDraw();
}

void update_without_input_2()
{
	//箭移动的模块,箭移动的模块要放在狼的模块上面，不然会出现最后一只狼的气球射不死的bug。。。不知道什么鬼
	if (count_shoot >= 0)
	{
		shoot[count_shoot] = 1;
	}
	static int arrow_speed = 0;//定义静态变量控制定义箭的速度
	if (arrow_speed < ARROW_SPEED)
	{
		arrow_speed++;
	}
	if (arrow_speed == ARROW_SPEED)
	{
		for (int i = 0; i < ARROW_NUM; i++)
		{
			if (shoot[i] == 1)//箭的左移
			{
				if (arrow_x[i] > -50)
				{
					arrow_x[i] = arrow_x[i] - 1;//箭自动左移
				}
				else if (arrow_x[i] <= -50)//箭飞出屏幕后显示关闭，这一步必须要关闭，否则后面还会计数，导致猪妈只能发出3只箭的bug，难道飞出屏幕还算在屏幕里么？
				{
					shoot[i] = -1;
				}
			}
			if (shoot[i] == 2)//箭的下落
			{
				if (arrow_y[i] <= HEIGHT + 50)
				{
					arrow_y[i]++;
				}
				if (arrow_y[i] > HEIGHT + 50)
				{
					shoot[i] = -1;
				}
			}
		}
		arrow_speed = 0;
	}
	arrow_num = 0;
	for (int i = 0; i < ARROW_NUM; i++)
	{
		if ((shoot[i] == 1)||(shoot[i]==2))
		{
			arrow_num++;//给屏幕上的箭计数
		}
	}
	//狼的自主移动的模块
	static int sj = 0;//用于狼的延迟出现
	if (sj < rand_space)
	{
		sj++;
	}
	if ((sj == rand_space) && (wolf_count < WOLF_NUM_2 - 1))
	{
		rand_space = rand() % 2500 + 1800;//rand()%m+n  m为随机变化幅度   n为固定变化幅度；
										  //在这里比初始化加大了间隔，为了更好地防止出现狼和气球图片重合；
		sj = 0;
		wolf_count++;
		ball_count++;
		if (wolf_count >= 0)//两个赋值也得放在里面，不然还是会在结尾出现bug
		{
			wolf_sign[wolf_count] = 1;//给每一只狼依次赋值为1，让它出现；
		}
		if (ball_count >= 0)
		{
			ball_sign[ball_count] = 1;//给每一只气球依次赋值为1，让它出现；
		}
	}
	for (int i = 0; i < WOLF_NUM_2; i++)
	{
		if (wolf_y[i] == 8 && wolf_sign[i] == 1)
		{
			wolf_sign[i] = 4;
		}
	}
	static int wolf_speed = 0;//定义静态变量控制狼的速度
	if (wolf_speed < WOLF_SPEED_2)
	{
		wolf_speed++;
	}
	if (wolf_speed == WOLF_SPEED_2)
	{
		int i;
		for (i = 0; i < WOLF_NUM_2; i++)
		{
			if ((wolf_x[i] < wolf_up_x[i]) && (wolf_sign[i] == 1))
			{
				wolf_x[i]++;//狼向右移动
				ball_x[i] = wolf_x[i];
			}
			if ((wolf_y[i] > 8) && (wolf_sign[i] == 1) && (wolf_x[i] >= wolf_up_x[i]))//狼自动上移
			{
				wolf_y[i]--;
			}
			if (wolf_sign[i] == 3)//被击中后快速下落
			{
				wolf_y[i] = wolf_y[i] + 5;
			}
			//狼向石头行走
			if ((wolf_sign[i] == 4) && (wolf_x[i] < stone_x - 35))
			{
				wolf_x[i]++;
			}
			else if ((wolf_sign[i] == 4) && (wolf_x[i] >= stone_x - 35))
			{
				wolf_x[i]--;
			}
		}
		//气球的移动模块；由于气球和狼是一起的，所以原理差不多;
		for (int i = 0; i < WOLF_NUM_2; i++)
		{
			if (/*ball_y[i] > 8 &&*/ (ball_sign[i] == 1) && (wolf_x[i] >= wolf_up_x[i]))//气球自动上移
			{
				ball_y[i]--;
			}
		}
		wolf_speed = 0;
	}
	string_y = pooyan_red_y;//控制绳子跟着猪妈移动增长缩短；
							//Sleep(5);//延时，用sleep的延时会让画面变卡,影响画面的所有内容；这个问题通过静态变量控制速度解决；
							//得分的判定
	int i, j;
	for (i = 0; i < ARROW_NUM; i++)
	{
		for (j = 0; j < WOLF_NUM; j++)
		{
			//箭射中气球的判定
			if ((arrow_x[i] >= ball_up_x[j] - 8) && (arrow_x[i] <= ball_up_x[j] + 40) && (arrow_y[i] >= ball_y[j] - 3) && (arrow_y[i] <= ball_y[j] + 30))
			{
				ball_sign[j] = 2;//气球爆炸
				wolf_sign[j] = 2;//狼死前挣扎
				arrow_x[i] = -50;//箭消失，刷新下一支
				score += 200;
			}
			//箭射中狼的判定
			if ((arrow_x[i] >= wolf_up_x[j] - 8) && (arrow_x[i] <= wolf_up_x[j] + 40) && (arrow_y[i] > ball_y[j] + 30) && (arrow_y[i] <= ball_y[j] + 65))
			{
				if (wolf_sign[j] == 1)
				{
					shoot[i] = 2;//骨箭射中狼，骨箭下坠
				}
			}
		}
	}
	//对爆炸后的气球进行处理
	for (j = 0; j < WOLF_NUM; j++)
	{
		if (ball_sign[j] == 2)
		{
			ball_interval[j]++;
		}
		if (ball_interval[j] == 100)
		{
			ball_y[j] = -1;
			ball_up_x[j] = -1;
			ball_sign[j] = -1;
			ball_interval[j] = 0;
		}
	}
	//对死后的狼的处理
	for (j = 0; j < WOLF_NUM; j++)
	{
		if (wolf_sign[j] == 2)
			wolf_interval[j]++;
		if (wolf_interval[j] == 500)
		{
			wolf_up_x[j] =-1;
			wolf_sign[j] = 3;
			wolf_interval[j] = 0;
			num_2++;
		}
	}
	//到达山崖上的狼推石头
	put_wolf = 0;
	for (i = 0; i < WOLF_NUM_2; i++)
	{
		if ((wolf_sign[i] == 4) && (wolf_x[i] == stone_x - 35))
		{
			put_wolf=put_wolf+1;
		}
		if (put_wolf >= 3)
		{
			stone_x = pooyan_red_x;
			stone_y++;
		}
	}
		//猪妈被石头砸中
	if ((stone_y >= pooyan_red_y) && (stone_y >= pooyan_red_y - 5) && (stone_y <= pooyan_red_y + 45))
	{
		pooyan_red_dead_x = pooyan_red_x;
		pooyan_red_dead_y = pooyan_red_y;
		pooyan_exit = 2;
	}
	
	//对死后的猪妈的处理
	static int pooyan_red_speeed = 0;
	if (pooyan_red_speeed < 2)
		pooyan_red_speeed++;
	if (pooyan_red_speeed == 2)
	{
		if (pooyan_exit == 2)
			pooyan_red_dead_y++;
		pooyan_red_speeed = 0;
	}
	//猪妈死亡，游戏结束
	if (pooyan_red_dead_y >= HEIGHT)
		act = 3;
	//过关与失败的判定
	if (num_2 >= 15)
	{
		act = 0;
	}
}

void update_with_input_2()
{
	//用input=getch()会产生严重的键位冲突；影响可玩性；
	//所以改用GetAsyncKeyState函数来解决键位冲突
	static int pooyan_red_speed = 0;//静态变量控制猪妈的速度，增加流畅性
	if (GetAsyncKeyState(0x57) & 0x8000 && (pooyan_red_y >= 120))//用w键控制猪妈上移
	{
		if (pooyan_red_speed < POOYAN_SPEED_2)
		{
			pooyan_red_speed++;
		}
		else if (pooyan_red_speed == POOYAN_SPEED_2)
		{
			pooyan_red_y = pooyan_red_y--;
			pooyan_red_speed = 0;
		}
	}
	if (GetAsyncKeyState(0x53) & 0x8000 && pooyan_red_y <= 350)//用s键控制猪妈向下移动
	{
		if (pooyan_red_speed < POOYAN_SPEED_2)
		{
			pooyan_red_speed++;
		}
		else if (pooyan_red_speed == POOYAN_SPEED_2)
		{
			pooyan_red_y = pooyan_red_y++;
			pooyan_red_speed = 0;
		}
	}
	char input;
	int judge = 0;//用来解决GetAsyncKeyState过于灵敏的问题，如果不加，就会出现按一次‘j’出现很多只箭；
	if (kbhit())
	{
		input = getch();
		if (input = 'j')
		{
			judge = 1;
		}
	}
	if (GetAsyncKeyState(0x4A) && 0x8000 && (arrow_num < 3))//按j键放箭同时控制屏幕上只能存在3只箭
	{
		if (judge == 1)
		{
			count_shoot++;//每加一次，数组中的箭就释放一次；
			arrow_y[count_shoot] = pooyan_red_y + 43;//让每一只箭发出后都待在正确位置 ，而不是跟着猪妈漂移；
			mciSendString(L"close shot", NULL, 0, NULL);
			mciSendString(L"open shot.mp3 alias shot", NULL, 0, NULL);
			mciSendString(L"play shot", NULL, 0, NULL);

		}
	}
}

void gameover()
{
	if (act == 3)
	{
		Sleep(1000);
		getch();
		exit(0);
	}
}