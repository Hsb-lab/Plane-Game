#pragma once
#include<iostream>
#include<ctime>
#include<cmath>
#include <conio.h>
#include<graphics.h>
#include<vector>

#pragma comment(lib,"Winmm.lib")

#define High 640//��Ϸ�����
#define Width 640//��Ϸ�����
#define AllHigh 640//����������
#define AllWidth 790//����������

#define EnemyMaxNum 12//��Ϸ���������ͬʱ���ڵĵл����� 
#define MyPlaneBulletNum 50//�ҷ��ɻ��ӵ�����

#define MyPlaneBulletRadius 1.5//�ҷ��ɻ��ӵ��뾶
#define EnemyPlaneBulletRadius 1.5//�з��ɻ��ӵ��뾶

#define MyPlaneWidth 25//�ҷ��ɻ����
#define MyPlaneLength 25//�ҷ��ɻ�����
#define EnemyWidth 25//�з��ɻ����
#define EnemyLength 25//�з��ɻ�����

using namespace std;


//ȫ�ֱ�����
extern IMAGE img_myplane;//�ҷ��ɻ�ͼƬ
extern IMAGE img_myplane_mask;//�ҷ��ɻ��ڸ�ͼ
extern IMAGE img_enemyplane;//�з��ɻ�ͼƬ
extern IMAGE img_enemyplane_mask;//�з��ɻ��ڸ�ͼ

//�ӵ���
class Bullet
{
public:

	//��Ա����
	float position_x;//λ��x
	float position_y;//λ��y
	float radius;//�ӵ��뾶
	bool is_alive;//�ж��ӵ��Ƿ���Ч
};

//�ҷ��ɻ���
class MyPlane
{
public:

	//��Ա����
	float position_x;//λ��x
	float position_y;//λ��y
	int HP;//Ѫ��
	Bullet Death01;
	Bullet Death[MyPlaneBulletNum];
	int score;//��Ϸ�÷�
	int KillEnemyNum;//����л���
};

//�з��ɻ���
class EnemyPlane
{
public:

	//��Ա����
	float position_x;//λ��x
	float position_y;//λ��y
	float EnemySpeed;//�з��ɻ�������ٶ�
	Bullet Death02;//�ӵ���
};


//������
class Manager
{
public:
	//���캯��
	Manager();

	//չʾ����
	void ShowInterface();

	//�������޹صĸ���
	void UpdateWithoutInput();

	//�������йصĸ���
	void UpdateWithInput();

	//�ж��ҷ��ɻ��ӵ��ƶ�
	void MyPlaneBulletMove();

	//�жϵз��ɻ��ӵ��ƶ�
	void EnemyPlaneBulletMove();

	//�жϵз��ɻ�����
	void EnemyMove();

	//�жϷɻ���ײ
	void PlaneCollision();

	//�ж��ҷ��ɻ��ӵ��Ƿ���ел�
	void Is_EnemyIsHit();

	//�ж��ҷ��ɻ��Ƿ񱻵л�����
	void Is_MyPlaneIsHit();

	//��ʾ�ҷ��ɻ�HP
	void ShowMyPlaneHP();

	//��ʾ�ҷ��ɻ��÷�
	void ShowMyPlaneScore();

	//��ʾ�ҷ��ɻ�����л���
	void ShowMyPlaneKill();

	//�ж��Ƿ������Ϸ�ú���
	void Is_EndGame();

	//���ű�������
	void PlayBGM();

	//��ȡ���÷�
	int GetMaxScore();

	//��Ա����
	MyPlane Asuna;//�ҷ��ɻ�
	EnemyPlane Kirito;//�з��ɻ�
	EnemyPlane Kirito_01[EnemyMaxNum];//�з��ɻ�
	vector<int>Scores;//�������������
};