//�ۺ���ϰ-��Ϸ2-��Ϸ������
//��������Ϸ1����ķɻ���ս��Ϸ�Ĺ��ܣ�
//���Ӷ�����棬��ʼ�����棬˵����Ϸ���ܣ��������棬��ʾ�û��ĵ÷�������Լ��Ƿ�ʼһ���µ���Ϸ��
//���Ż��ֵ����ӣ����Կ��������Ѷȣ��ӿ�л��������ٶȣ��ͳ��ֵ��ٶȣ�
//����������������ܴ��������ֹ��Ҳٿطɻ��ɳ��߽磬���� / ��ײ���Ĵ���
//���Ӱ�Esc������Ϸ��ͣ�Ĺ���
//����ͼ�ν��棨easyX, Qt, MFC���Լ��������ĳ������
//2. Ҫ���ύ���һ�����ܻ�����������Դ���룬�Լ�һ��word�ĵ���
//˵�������Ĺ������Ƶ�Ŀ�꣬����Լ�����ʵ�ֺͲ���Ч����

#include"PlaneGame.h"

IMAGE img_myplane;//�ҷ��ɻ�ͼƬ
IMAGE img_myplane_mask;//�ҷ��ɻ��ڸ�ͼ
IMAGE img_enemyplane;//�з��ɻ�ͼƬ
IMAGE img_enemyplane_mask;//�з��ɻ��ڸ�ͼ

void test01()
{
	Manager Hsb;//����һ�����������
	//Hsb.PlayBGM();//�˹��ܻ�������
	BeginBatchDraw();//��ʼ��������ͼƬ
	while (1)
	{
		Hsb.ShowInterface();
		Hsb.UpdateWithInput();
		Hsb.UpdateWithoutInput();
	}
	EndBatchDraw();//������������ͼƬ
}

void GameExplanation()
{
	cout << "��Ϸ˵��" << endl;
	cout << "1.�������ҷ��ɻ��ƶ�" << endl;
	cout << "2.���¿ո�������ӵ�" << endl;
	cout << "3.�ҷ��ɻ���з��ɻ�������ײʱ��Ϸ����" << endl;
	cout << "4.�ҷ��ɻ�HP����0ʱ��Ϸ����" << endl;
	cout << "5.�ҷ��ɻ�ÿ�α��з��ɻ��ӵ����к�HP��1" << endl;
	cout << "6.�ҷ��ɻ����ез��ɻ������score��1" << endl;
	cout << "7.�ҷ��ɻ��÷�ÿ����20���ҷ��ɻ�HP��1" << endl;
	cout << "8.��ESC����Ϸ��ͣ���ٰ�ESC����Ϸ����" << endl;
	cout << "9.��Ϸ����ʱ��ʾ�˴���Ϸ�÷ֺ���Ϸ��ߵ÷�" << endl;
	cout << "Сϸ��:��Ϸ��ʼ���뽫���뷨�л�ΪӢ��ģʽ" << endl;
	system("pause");
}

int main()
{
	srand((unsigned int)time(0));//���������
	GameExplanation();
	test01();
	return 0;
}