#include"PlaneGame.h"

//Manager���µĳ�Ա����
//���캯��
Manager::Manager()
{
	//��ʼ������
	this->Asuna.score = 0;
	this->Asuna.KillEnemyNum = 0;

	//��ʼ������
	initgraph(AllWidth, AllHigh);

	//ͼƬ����
	loadimage(&img_myplane, _T("myplane.png"), MyPlaneWidth, MyPlaneLength);//�����ҷ��ɻ�ͼƬ(����ͼƬ��С)
	loadimage(&img_myplane_mask, _T("myplane_mask.png"), MyPlaneWidth, MyPlaneLength);//�����ҷ��ɻ��ڸ�ͼ(����ͼƬ��С)
	loadimage(&img_enemyplane, _T("enemyplane.png"), EnemyWidth, EnemyLength);//����з����ɻ�ͼƬ(����ͼƬ��С)
	loadimage(&img_enemyplane_mask, _T("enemyplane_mask.png"), EnemyWidth, EnemyLength);//����з����ɻ��ڸ�ͼ(����ͼƬ��С)

	//�ҷ��ɻ���ʼ��
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

	//�з��ɻ���ʼ��
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

//���ű�������
void Manager::PlayBGM()
{
	mciSendString(_T("open E:\\VSC++��Ŀ\\C++��Ŀ\\�������Ŀ\\�������Ŀ\\game_music01.mp3 alias bkmusic"), NULL, 0, NULL);//�򿪱�������
	//mciSendString(_T("open D:\\game_music.mp3 alias bkmusic"), NULL, 0, NULL);//�򿪱�������
	//mciSendString(_T("open D:\\game_music01.mp3 alias bkmusic"), NULL, 0, NULL);
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);  // ѭ������
}

//չʾ����
void Manager::ShowInterface()
{
	putimage(this->Asuna.position_x,this->Asuna.position_y, &img_myplane);//չʾ�ҷ��ɻ�
	//putimage(this->Kirito.position_x,this->Kirito.position_y, &img_enemyplane);//չʾ�з��ɻ�

	//չʾ�з��ɻ�
	for (int i = 0; i < EnemyMaxNum; i++)
	{
		putimage(this->Kirito_01[i].position_x, this->Kirito_01[i].position_y, &img_enemyplane);//չʾ�з��ɻ�
	}

	settextcolor(WHITE);
	settextstyle(15, 0, _T("Consolas"));
	TCHAR a[] = _T("����ֵ��");
	outtextxy(710, 20, a);
	TCHAR b[] = _T("����:");
	outtextxy(710, 80, b);
	TCHAR c[] = _T("����л���:");
	outtextxy(710, 140, c);

	//չʾ�ҷ��ɻ���Ϣ
	this->ShowMyPlaneHP();//��ʾ�ҷ��ɻ�Ѫ��
	this->ShowMyPlaneScore();//��ʾ�ҷ��ɻ��÷�
	this->ShowMyPlaneKill();//��ʾ�ҷ��ɻ�����л���    

	FlushBatchDraw();//ִ��������ͼ
}

//�������йصĸ���(���������ҷ��ɻ��ƶ��������ӵ�)
void Manager::UpdateWithInput()
{
	MOUSEMSG m;//��¼�����Ϣ
	static int BulletOrder = 0;//��¼���������һ���ӵ�
	while (MouseHit())
	{
		putimage(this->Asuna.position_x,this->Asuna.position_y,&img_myplane_mask);
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)//����ƶ�ʱ���ɻ�����������λ��
		{
			//��ֹ�ɻ��ɳ��߽�
			if (0 <= m.x && m.x <= Width - MyPlaneWidth
				&& 0 <= m.y && m.y <= High - MyPlaneLength)
			{
				this->Asuna.position_x = m.x;
				this->Asuna.position_y = m.y;
			}

			
		}
		//else if (m.uMsg == WM_LBUTTONDOWN)//��������������ӵ�
		//{
		//ʹ�������������ӵ��޷�ʵ���ӵ����������䣬���������Ҳ�������귢���ӵ�	
		//}
	}
	if (_kbhit())//����ո����ӵ�
	{
		char input = _getch();
		switch (input)
		{
		case ' ':
		{
			if (BulletOrder >= 50)//���ӵ��ķ���˳������
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
			TCHAR s1[] = _T("��Ϸ��ͣ");
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
			TCHAR s2[] = _T("��Ϸ��ͣ");
			outtextxy(Width / 2 - 20, High / 2, s2);
			BeginBatchDraw();
		}
		}
	}

}

//�ж��ҷ��ɻ��ӵ��ƶ�
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

//�жϷɻ���ײ
void Manager::PlaneCollision()
{
	for (int i = 0; i < EnemyMaxNum; i++)
	{
		if (fabs((this->Asuna.position_x + 12.5) - (this->Kirito_01[i].position_x + 12.5)) <= 20
			&& fabs((this->Asuna.position_y + 12.5) - (this->Kirito_01[i].position_y + 12.5)) <= 20)
		{
			this->Scores.push_back(this->Asuna.score);//����˴���Ϸ�ķ���
			this->Is_EndGame();
		}
	}
}

//�ж��ҷ��ɻ��ӵ��Ƿ���ел�
void Manager::Is_EnemyIsHit()
{
	for (int j = 0; j < MyPlaneBulletNum; j++)
	{
		for (int i = 0; i < EnemyMaxNum; i++)
		{
			//�ж��ҷ��ɻ��ӵ��Ƿ���ел�
			if (fabs(this->Asuna.Death[j].position_x - (this->Kirito_01[i].position_x + 12.5)) <= this->Asuna.Death[j].radius + 12.5
				&& fabs(this->Asuna.Death[j].position_y - (this->Kirito_01[i].position_y + 12.5)) <= this->Asuna.Death[j].radius + 12.5)
			{
				static int BloodPlus = 0;

				this->Asuna.score++;  
				this->Asuna.KillEnemyNum++;

				//���ݵ÷������ҷ��ɻ�Ѫ���������ޣ�
				BloodPlus++;
				if (BloodPlus >= 20)
				{
					this->Asuna.HP++;
					BloodPlus = 0;
				}

				//����ͼ��
				clearcircle(this->Asuna.Death[j].position_x, this->Asuna.Death[j].position_y, this->Asuna.Death[j].radius);//�����ӵ�
				putimage(this->Kirito_01[i].position_x, this->Kirito_01[i].position_y, &img_enemyplane_mask);//���صз��ɻ�

				//���³�ʼ���ӵ�
				this->Asuna.Death[j].position_x = -1;
				this->Asuna.Death[j].position_y = -1;

				//�������ɵл�
				this->Kirito_01[i].position_y = 0;
				this->Kirito_01[i].position_x = rand() % Width;
			}
		}
	}
}

//�ж��ҷ��ɻ��Ƿ񱻵л�����
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
				clearcircle(this->Kirito_01[i].Death02.position_x, this->Kirito_01[i].Death02.position_y, this->Kirito_01[i].Death02.radius);//���صл��ӵ�

				//���³�ʼ���ӵ�
				this->Kirito_01[i].Death02.position_x = this->Kirito_01[i].position_x + 12.5;
				this->Kirito_01[i].Death02.position_y = this->Kirito_01[i].position_y + 25;
			
			}
		}
	}
}

//�ж��Ƿ������Ϸ�ĺ���
void Manager::Is_EndGame()
{
	cleardevice();
	TCHAR s[] = _T("Game Over");
	TCHAR s1[] = _T("��Q�����¿�ʼ��Ϸ");
	TCHAR s2[] = _T("��E���˳���Ϸ����");

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
	outtextxy(AllWidth * 0.3, 350, _T("������Ϸ�÷�: "));
	outtextxy(AllWidth * 0.3 + 100, 350, sco);

	_stprintf_s(sco, _T("%d"), this->GetMaxScore());
	outtextxy(AllWidth * 0.3, 350 + 30, _T("��ʷ��ߵ÷�: "));
	outtextxy(AllWidth * 0.3 + 100, 350 + 30, sco);


	FlushBatchDraw();//ִ��������ͼ

	

	char input = '0';
	while (1)
	{
		input = _getch();
		if (input == 'Q' || input == 'q')
		{
			cleardevice();

			//��ʼ������
			this->Asuna.score = 0;
			this->Asuna.KillEnemyNum = 0;

			//�ҷ��ɻ���ʼ��
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

			//�з��ɻ���ʼ��
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

//�жϵз��ɻ��ӵ��ƶ�
void Manager::EnemyPlaneBulletMove()
{

	for (int i = 0; i < EnemyMaxNum; i++)
	{
		if (this->Kirito_01[i].Death02.position_y < High)
		{
			clearcircle(this->Kirito_01[i].Death02.position_x, this->Kirito_01[i].Death02.position_y, this->Kirito_01[i].Death02.radius);//���صз��ɻ��ӵ�
			this->Kirito_01[i].Death02.position_y += 1.5 * this->Kirito_01[i].EnemySpeed / 10;
			solidcircle(this->Kirito_01[i].Death02.position_x, this->Kirito_01[i].Death02.position_y, this->Kirito_01[i].Death02.radius);//չʾ�з��ɻ��ӵ�
		}
		else
		{
			//�ӵ���ʼ��
			this->Kirito_01[i].Death02.position_x = this->Kirito_01[i].position_x + 12.5;
			this->Kirito_01[i].Death02.position_y = this->Kirito_01[i].position_y + 25;
		}
	}
}

//�жϵз��ɻ�����
void Manager::EnemyMove()
{
	//if (this->Kirito.position_y < High)
	//{
	//	putimage(this->Kirito.position_x, this->Kirito.position_y, &img_enemyplane_mask);//���صз��ɻ�
	//	this->Kirito.position_y += 0.1;
	//	putimage(this->Kirito.position_x, this->Kirito.position_y, &img_enemyplane);//չʾ�з��ɻ�
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
			putimage(this->Kirito_01[i].position_x,this->Kirito_01[i].position_y, &img_enemyplane_mask);//���صз��ɻ�
			this->Kirito_01[i].position_y += this->Kirito_01[i].EnemySpeed /10;
			putimage(this->Kirito_01[i].position_x,this->Kirito_01[i].position_y, &img_enemyplane);//չʾ�з��ɻ�
		}
		else
		{
			this->Kirito_01[i].position_y = 0;
			this->Kirito_01[i].position_x = rand() % Width;
			this->Kirito_01[i].EnemySpeed = rand() % 3 + 1;
		}
	}

}

//��ʾ�ҷ��ɻ�HP
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

//��ʾ�ҷ��ɻ��÷�
void Manager::ShowMyPlaneScore()
{
	settextstyle(15, 0, _T("Consolas"));
	settextcolor(WHITE);
	TCHAR sco[5];
	_stprintf_s(sco, _T("%d"), this->Asuna.score);
	outtextxy(710, 100, _T("    "));
	outtextxy(710, 100, sco);
}

//��ʾ�ҷ��ɻ�����л���
void Manager::ShowMyPlaneKill()
{
	settextstyle(15, 0, _T("Consolas"));
	settextcolor(WHITE);
	TCHAR T[5];
	_stprintf_s(T, _T("%d"), this->Asuna.KillEnemyNum);
	outtextxy(710, 160, _T("    "));
	outtextxy(710, 160, T);
}

//�������޹صĸ���
void Manager::UpdateWithoutInput()
{
	//�ҷ��ɻ��ӵ��ƶ�
	this->MyPlaneBulletMove();

	//�жϵз��ɻ��ӵ��ƶ�
	this->EnemyPlaneBulletMove();

	//�ж��ҷŷɻ��ӵ��Ƿ���ел�
	this->Is_EnemyIsHit();

	//�ж��ҷ��ɻ��Ƿ񱻵л�����
	this->Is_MyPlaneIsHit();

	//�ж��ҷ��ɻ��Ƿ���з��ɻ���ײ
	this->PlaneCollision();

	//�з��ɻ�����
	this->EnemyMove();
}     

//��ȡ���÷�
int Manager::GetMaxScore()
{
	int MaxScore = 0;
	for (vector<int>::iterator it = this->Scores.begin(); it != this->Scores.end(); it++)
	{
		if (MaxScore < *it)//����������
		{
			MaxScore = *it;
		}
	}
	return MaxScore;
}