#include"PlaneGame.h"

//Manager类下的成员函数
//构造函数
Manager::Manager()
{
	//初始化分数
	this->Asuna.score = 0;
	this->Asuna.KillEnemyNum = 0;

	//初始化画布
	initgraph(AllWidth, AllHigh);

	//图片导入
	loadimage(&img_myplane, _T("myplane.png"), MyPlaneWidth, MyPlaneLength);//导入我方飞机图片(限制图片大小)
	loadimage(&img_myplane_mask, _T("myplane_mask.png"), MyPlaneWidth, MyPlaneLength);//导入我方飞机遮盖图(限制图片大小)
	loadimage(&img_enemyplane, _T("enemyplane.png"), EnemyWidth, EnemyLength);//导入敌方方飞机图片(限制图片大小)
	loadimage(&img_enemyplane_mask, _T("enemyplane_mask.png"), EnemyWidth, EnemyLength);//导入敌方方飞机遮盖图(限制图片大小)

	//我方飞机初始化
	this->Asuna.position_x = Width * 0.5;
	this->Asuna.position_y = High * 0.5;
	this->Asuna.Death01.position_x = -1;
	this->Asuna.Death01.position_y = -1;
	this->Asuna.Death01.radius = MyPlaneBulletRadius;
	this->Asuna.Death01.is_alive = false;

	this->Asuna.HP = 10;

	for (int i = 0; i < MyPlaneBulletNum; i++)
	{
		this->Asuna.Death[i].position_x = -1;
		this->Asuna.Death[i].position_y = -1;
		this->Asuna.Death[i].radius = MyPlaneBulletRadius;
		this->Asuna.Death[i].is_alive = false;
	}

	//敌方飞机初始化
	this->Kirito.position_x = rand() % Width;
	this->Kirito.position_y = 0;
	this->Kirito.EnemySpeed = 1;
	this->Kirito.Death02.position_x = -1;
	this->Kirito.Death02.position_y = -1;
	this->Kirito.Death02.radius = EnemyPlaneBulletRadius;
	this->Kirito.Death02.is_alive = false;
	for (int i = 0; i < EnemyMaxNum; i++)
	{
		this->Kirito_01[i].position_x = rand() % Width;
		this->Kirito_01[i].position_y = 0;
		this->Kirito_01[i].EnemySpeed = rand() % 3 + 1;

		this->Kirito_01[i].Death02.position_x = this->Kirito_01[i].position_x + 12.5;
		this->Kirito_01[i].Death02.position_y = this->Kirito_01[i].position_y + 25;
		
		this->Kirito_01[i].Death02.radius = EnemyPlaneBulletRadius;
		this->Kirito_01[i].Death02.is_alive = false;
	}

}

//播放背景音乐
void Manager::PlayBGM()
{
	mciSendString(_T("open E:\\VSC++项目\\C++项目\\计算机项目\\计算机项目\\game_music01.mp3 alias bkmusic"), NULL, 0, NULL);//打开背景音乐
	//mciSendString(_T("open D:\\game_music.mp3 alias bkmusic"), NULL, 0, NULL);//打开背景音乐
	//mciSendString(_T("open D:\\game_music01.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);  // 循环播放
}

//展示界面
void Manager::ShowInterface()
{
	putimage(this->Asuna.position_x,this->Asuna.position_y, &img_myplane);//展示我方飞机
	//putimage(this->Kirito.position_x,this->Kirito.position_y, &img_enemyplane);//展示敌方飞机

	//展示敌方飞机
	for (int i = 0; i < EnemyMaxNum; i++)
	{
		putimage(this->Kirito_01[i].position_x, this->Kirito_01[i].position_y, &img_enemyplane);//展示敌方飞机
	}

	settextcolor(WHITE);
	settextstyle(15, 0, _T("Consolas"));
	TCHAR a[] = _T("生命值：");
	outtextxy(710, 20, a);
	TCHAR b[] = _T("分数:");
	outtextxy(710, 80, b);
	TCHAR c[] = _T("击落敌机数:");
	outtextxy(710, 140, c);

	//展示我方飞机信息
	this->ShowMyPlaneHP();//显示我方飞机血量
	this->ShowMyPlaneScore();//显示我方飞机得分
	this->ShowMyPlaneKill();//显示我方飞机击落敌机数    

	FlushBatchDraw();//执行批量绘图
}

//与输入有关的更新(用鼠标控制我方飞机移动及发射子弹)
void Manager::UpdateWithInput()
{
	MOUSEMSG m;//记录鼠标消息
	static int BulletOrder = 0;//记录发射的是那一颗子弹
	while (MouseHit())
	{
		putimage(this->Asuna.position_x,this->Asuna.position_y,&img_myplane_mask);
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)//鼠标移动时，飞机坐标等于鼠标位置
		{
			//防止飞机飞出边界
			if (0 <= m.x && m.x <= Width - MyPlaneWidth
				&& 0 <= m.y && m.y <= High - MyPlaneLength)
			{
				this->Asuna.position_x = m.x;
				this->Asuna.position_y = m.y;
			}

			
		}
		//else if (m.uMsg == WM_LBUTTONDOWN)//点击鼠标左键发射子弹
		//{
		//使用鼠标左键发射子弹无法实现子弹的连续发射，所以这里我不采用鼠标发射子弹	
		//}
	}
	if (_kbhit())//输入空格发射子弹
	{
		char input = _getch();
		switch (input)
		{
		case ' ':
		{
			if (BulletOrder >= 50)//将子弹的发射顺序置零
			{
				BulletOrder = 0;
			}
			this->Asuna.Death[BulletOrder].position_x = this->Asuna.position_x + 12.5;
			this->Asuna.Death[BulletOrder].position_y = this->Asuna.position_y - 1;
			solidcircle(this->Asuna.Death[BulletOrder].position_x, this->Asuna.Death[BulletOrder].position_y, this->Asuna.Death[BulletOrder].radius);
			BulletOrder++;
			break;
		}

		case 27:
		{
			EndBatchDraw();
			settextstyle(50, 0, _T("Consolas"));
			settextcolor(WHITE);
			cleardevice();
			TCHAR s1[] = _T("游戏暂停");
			outtextxy(Width / 2 - 20, High / 2, s1);
			while (true)
			{
				if (_getch() == 27)
				{
					break;
				}
			}
			settextstyle(50, 0, _T("Consolas"));
			settextcolor(BLACK);
			TCHAR s2[] = _T("游戏暂停");
			outtextxy(Width / 2 - 20, High / 2, s2);
			BeginBatchDraw();
		}
		}
	}

}

//判断我方飞机子弹移动
void Manager::MyPlaneBulletMove()
{
	for (int i = 0; i < MyPlaneBulletNum; i++)
	{
		if (this->Asuna.Death[i].position_y > -1)
		{
			clearcircle(this->Asuna.Death[i].position_x, this->Asuna.Death[i].position_y, this->Asuna.Death[i].radius);
			this->Asuna.Death[i].position_y--;
			solidcircle(this->Asuna.Death[i].position_x, this->Asuna.Death[i].position_y, this->Asuna.Death[i].radius);
		}
	}
}

//判断飞机碰撞
void Manager::PlaneCollision()
{
	for (int i = 0; i < EnemyMaxNum; i++)
	{
		if (fabs((this->Asuna.position_x + 12.5) - (this->Kirito_01[i].position_x + 12.5)) <= 20
			&& fabs((this->Asuna.position_y + 12.5) - (this->Kirito_01[i].position_y + 12.5)) <= 20)
		{
			this->Scores.push_back(this->Asuna.score);//储存此次游戏的分数
			this->Is_EndGame();
		}
	}
}

//判断我方飞机子弹是否击中敌机
void Manager::Is_EnemyIsHit()
{
	for (int j = 0; j < MyPlaneBulletNum; j++)
	{
		for (int i = 0; i < EnemyMaxNum; i++)
		{
			//判断我方飞机子弹是否击中敌机
			if (fabs(this->Asuna.Death[j].position_x - (this->Kirito_01[i].position_x + 12.5)) <= this->Asuna.Death[j].radius + 12.5
				&& fabs(this->Asuna.Death[j].position_y - (this->Kirito_01[i].position_y + 12.5)) <= this->Asuna.Death[j].radius + 12.5)
			{
				static int BloodPlus = 0;

				this->Asuna.score++;  
				this->Asuna.KillEnemyNum++;

				//根据得分增加我方飞机血量（无上限）
				BloodPlus++;
				if (BloodPlus >= 20)
				{
					this->Asuna.HP++;
					BloodPlus = 0;
				}

				//处理图像
				clearcircle(this->Asuna.Death[j].position_x, this->Asuna.Death[j].position_y, this->Asuna.Death[j].radius);//隐藏子弹
				putimage(this->Kirito_01[i].position_x, this->Kirito_01[i].position_y, &img_enemyplane_mask);//隐藏敌方飞机

				//重新初始化子弹
				this->Asuna.Death[j].position_x = -1;
				this->Asuna.Death[j].position_y = -1;

				//重新生成敌机
				this->Kirito_01[i].position_y = 0;
				this->Kirito_01[i].position_x = rand() % Width;
			}
		}
	}
}

//判断我方飞机是否被敌机击中
void Manager::Is_MyPlaneIsHit()
{
	if (this->Asuna.HP <= 0)
	{
		this->Is_EndGame();
	}
	else
	{
		for (int i = 0; i < EnemyMaxNum; i++)
		{
			if (fabs(this->Kirito_01[i].Death02.position_x - (this->Asuna.position_x + 12.5)) <= this->Kirito_01[i].Death02.radius + 12.5
				&& fabs(this->Kirito_01[i].Death02.position_y - (this->Asuna.position_y + 12.5)) <= this->Kirito_01[i].Death02.radius + 12.5)
			{
				this->Asuna.HP -= 1;
				clearcircle(this->Kirito_01[i].Death02.position_x, this->Kirito_01[i].Death02.position_y, this->Kirito_01[i].Death02.radius);//隐藏敌机子弹

				//重新初始化子弹
				this->Kirito_01[i].Death02.position_x = this->Kirito_01[i].position_x + 12.5;
				this->Kirito_01[i].Death02.position_y = this->Kirito_01[i].position_y + 25;
			
			}
		}
	}
}

//判断是否结束游戏的函数
void Manager::Is_EndGame()
{
	cleardevice();
	TCHAR s[] = _T("Game Over");
	TCHAR s1[] = _T("按Q键重新开始游戏");
	TCHAR s2[] = _T("按E键退出游戏程序");

	settextcolor(RED);
	settextstyle(90, 0, s);
	outtextxy(Width*0.3, High * 0.3, s);

	settextcolor(WHITE);
	settextstyle(15, 0, s1);
	outtextxy(Width * 0.3, High * 0.3 + 80 + 15 , s1);
	settextstyle(15, 0, s2);
	outtextxy(Width * 0.3, High * 0.3 + 80 + 30 , s2);

	TCHAR sco[5];
	_stprintf_s(sco, _T("%d"), this->Asuna.score);
	outtextxy(AllWidth * 0.3, 350, _T("本次游戏得分: "));
	outtextxy(AllWidth * 0.3 + 100, 350, sco);

	_stprintf_s(sco, _T("%d"), this->GetMaxScore());
	outtextxy(AllWidth * 0.3, 350 + 30, _T("历史最高得分: "));
	outtextxy(AllWidth * 0.3 + 100, 350 + 30, sco);


	FlushBatchDraw();//执行批量绘图

	

	char input = '0';
	while (1)
	{
		input = _getch();
		if (input == 'Q' || input == 'q')
		{
			cleardevice();

			//初始化分数
			this->Asuna.score = 0;
			this->Asuna.KillEnemyNum = 0;

			//我方飞机初始化
			this->Asuna.position_x = Width * 0.5;
			this->Asuna.position_y = High * 0.5;
			this->Asuna.Death01.position_x = -1;
			this->Asuna.Death01.position_y = -1;
			this->Asuna.Death01.radius = MyPlaneBulletRadius;
			this->Asuna.Death01.is_alive = false;
			this->Asuna.HP = 10;
			for (int i = 0; i < MyPlaneBulletNum; i++)
			{
				this->Asuna.Death[i].position_x = -1;
				this->Asuna.Death[i].position_y = -1;
				this->Asuna.Death[i].radius = MyPlaneBulletRadius;
				this->Asuna.Death[i].is_alive = false;
			}

			//敌方飞机初始化
			this->Kirito.position_x = rand() % Width;
			this->Kirito.position_y = 0;
			this->Kirito.EnemySpeed = 1;
			this->Kirito.Death02.position_x = -1;
			this->Kirito.Death02.position_y = -1;
			this->Kirito.Death02.radius = EnemyPlaneBulletRadius;
			this->Kirito.Death02.is_alive = false;
			for (int i = 0; i < EnemyMaxNum; i++)
			{
				this->Kirito_01[i].position_x = rand() % Width;
				this->Kirito_01[i].position_y = 0;
				this->Kirito_01[i].EnemySpeed = rand() % 3 + 1;

				this->Kirito_01[i].Death02.position_x = this->Kirito_01[i].position_x + 12.5;
				this->Kirito_01[i].Death02.position_y = this->Kirito_01[i].position_y + 25;

				this->Kirito_01[i].Death02.radius = EnemyPlaneBulletRadius;
				this->Kirito_01[i].Death02.is_alive = false;
			}
			break;
		}
		else if (input == 'E' || input == 'e')
		{
			exit(0);
		}
	}
}

//判断敌方飞机子弹移动
void Manager::EnemyPlaneBulletMove()
{

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		if (this->Kirito_01[i].Death02.position_y < High)
		{
			clearcircle(this->Kirito_01[i].Death02.position_x, this->Kirito_01[i].Death02.position_y, this->Kirito_01[i].Death02.radius);//隐藏敌方飞机子弹
			this->Kirito_01[i].Death02.position_y += 1.5 * this->Kirito_01[i].EnemySpeed / 10;
			solidcircle(this->Kirito_01[i].Death02.position_x, this->Kirito_01[i].Death02.position_y, this->Kirito_01[i].Death02.radius);//展示敌方飞机子弹
		}
		else
		{
			//子弹初始化
			this->Kirito_01[i].Death02.position_x = this->Kirito_01[i].position_x + 12.5;
			this->Kirito_01[i].Death02.position_y = this->Kirito_01[i].position_y + 25;
		}
	}
}

//判断敌方飞机下落
void Manager::EnemyMove()
{
	//if (this->Kirito.position_y < High)
	//{
	//	putimage(this->Kirito.position_x, this->Kirito.position_y, &img_enemyplane_mask);//隐藏敌方飞机
	//	this->Kirito.position_y += 0.1;
	//	putimage(this->Kirito.position_x, this->Kirito.position_y, &img_enemyplane);//展示敌方飞机
	//}
	//else
	//{
	//	this->Kirito.position_y = 0;
	//	this->Kirito.position_x = rand() % Width;
	//}

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		if (this->Kirito_01[i].position_y < High)
		{
			putimage(this->Kirito_01[i].position_x,this->Kirito_01[i].position_y, &img_enemyplane_mask);//隐藏敌方飞机
			this->Kirito_01[i].position_y += this->Kirito_01[i].EnemySpeed /10;
			putimage(this->Kirito_01[i].position_x,this->Kirito_01[i].position_y, &img_enemyplane);//展示敌方飞机
		}
		else
		{
			this->Kirito_01[i].position_y = 0;
			this->Kirito_01[i].position_x = rand() % Width;
			this->Kirito_01[i].EnemySpeed = rand() % 3 + 1;
		}
	}

}

//显示我方飞机HP
void Manager::ShowMyPlaneHP()
{
	settextstyle(15, 0, _T("Consolas"));
	settextcolor(WHITE);
	TCHAR num[3];
	int hp = this->Asuna.HP;
	_stprintf_s(num, _T("%d"), hp);
	outtextxy(710, 50, _T("   "));
	outtextxy(710, 50, num);
}

//显示我方飞机得分
void Manager::ShowMyPlaneScore()
{
	settextstyle(15, 0, _T("Consolas"));
	settextcolor(WHITE);
	TCHAR sco[5];
	_stprintf_s(sco, _T("%d"), this->Asuna.score);
	outtextxy(710, 100, _T("    "));
	outtextxy(710, 100, sco);
}

//显示我方飞机击落敌机数
void Manager::ShowMyPlaneKill()
{
	settextstyle(15, 0, _T("Consolas"));
	settextcolor(WHITE);
	TCHAR T[5];
	_stprintf_s(T, _T("%d"), this->Asuna.KillEnemyNum);
	outtextxy(710, 160, _T("    "));
	outtextxy(710, 160, T);
}

//与输入无关的更新
void Manager::UpdateWithoutInput()
{
	//我方飞机子弹移动
	this->MyPlaneBulletMove();

	//判断敌方飞机子弹移动
	this->EnemyPlaneBulletMove();

	//判断我放飞机子弹是否击中敌机
	this->Is_EnemyIsHit();

	//判断我方飞机是否被敌机击中
	this->Is_MyPlaneIsHit();

	//判断我方飞机是否与敌方飞机相撞
	this->PlaneCollision();

	//敌方飞机下落
	this->EnemyMove();
}     

//获取最大得分
int Manager::GetMaxScore()
{
	int MaxScore = 0;
	for (vector<int>::iterator it = this->Scores.begin(); it != this->Scores.end(); it++)
	{
		if (MaxScore < *it)//更新最大分数
		{
			MaxScore = *it;
		}
	}
	return MaxScore;
}