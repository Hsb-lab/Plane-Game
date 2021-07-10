#pragma once
#include<iostream>
#include<ctime>
#include<cmath>
#include <conio.h>
#include<graphics.h>
#include<vector>

#pragma comment(lib,"Winmm.lib")

#define High 640//游戏界面高
#define Width 640//游戏界面宽
#define AllHigh 640//整个画布高
#define AllWidth 790//整个画布宽

#define EnemyMaxNum 12//游戏界面上最多同时存在的敌机数量 
#define MyPlaneBulletNum 50//我方飞机子弹数量

#define MyPlaneBulletRadius 1.5//我方飞机子弹半径
#define EnemyPlaneBulletRadius 1.5//敌方飞机子弹半径

#define MyPlaneWidth 25//我方飞机宽度
#define MyPlaneLength 25//我方飞机长度
#define EnemyWidth 25//敌方飞机宽度
#define EnemyLength 25//敌方飞机长度

using namespace std;


//全局变量区
extern IMAGE img_myplane;//我方飞机图片
extern IMAGE img_myplane_mask;//我方飞机遮盖图
extern IMAGE img_enemyplane;//敌方飞机图片
extern IMAGE img_enemyplane_mask;//敌方飞机遮盖图

//子弹类
class Bullet
{
public:

	//成员属性
	float position_x;//位置x
	float position_y;//位置y
	float radius;//子弹半径
	bool is_alive;//判断子弹是否有效
};

//我方飞机类
class MyPlane
{
public:

	//成员属性
	float position_x;//位置x
	float position_y;//位置y
	int HP;//血量
	Bullet Death01;
	Bullet Death[MyPlaneBulletNum];
	int score;//游戏得分
	int KillEnemyNum;//击落敌机数
};

//敌方飞机类
class EnemyPlane
{
public:

	//成员属性
	float position_x;//位置x
	float position_y;//位置y
	float EnemySpeed;//敌方飞机下落的速度
	Bullet Death02;//子弹类
};


//管理类
class Manager
{
public:
	//构造函数
	Manager();

	//展示界面
	void ShowInterface();

	//与输入无关的更新
	void UpdateWithoutInput();

	//与输入有关的更新
	void UpdateWithInput();

	//判断我方飞机子弹移动
	void MyPlaneBulletMove();

	//判断敌方飞机子弹移动
	void EnemyPlaneBulletMove();

	//判断敌方飞机下落
	void EnemyMove();

	//判断飞机碰撞
	void PlaneCollision();

	//判断我方飞机子弹是否击中敌机
	void Is_EnemyIsHit();

	//判断我方飞机是否被敌机击中
	void Is_MyPlaneIsHit();

	//显示我方飞机HP
	void ShowMyPlaneHP();

	//显示我方飞机得分
	void ShowMyPlaneScore();

	//显示我方飞机击落敌机数
	void ShowMyPlaneKill();

	//判断是否结束游戏得函数
	void Is_EndGame();

	//播放背景音乐
	void PlayBGM();

	//获取最大得分
	int GetMaxScore();

	//成员属性
	MyPlane Asuna;//我方飞机
	EnemyPlane Kirito;//敌方飞机
	EnemyPlane Kirito_01[EnemyMaxNum];//敌方飞机
	vector<int>Scores;//储存分数的容器
};