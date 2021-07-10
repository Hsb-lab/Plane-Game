//综合练习-游戏2-游戏的完善
//扩充下游戏1定义的飞机大战游戏的功能：
//增加多个界面，初始化界面，说明游戏功能；结束界面，提示用户的得分情况，以及是否开始一个新的游戏；
//随着积分的增加，可以考虑增加难度，加快敌机的下落速度，和出现的速度；
//功能上做更多的性能处理：例如防止玩家操控飞机飞出边界，击中 / 碰撞检测的处理
//增加按Esc键后游戏暂停的功能
//增加图形界面（easyX, Qt, MFC）以及面向对象的程序设计
//2. 要求：提交完成一定功能或性能扩充后的源代码，以及一个word文档，
//说明你做的功能完善的目标，设计以及程序实现和测试效果。

#include"PlaneGame.h"

IMAGE img_myplane;//我方飞机图片
IMAGE img_myplane_mask;//我方飞机遮盖图
IMAGE img_enemyplane;//敌方飞机图片
IMAGE img_enemyplane_mask;//敌方飞机遮盖图

void test01()
{
	Manager Hsb;//创建一个管理类对象
	//Hsb.PlayBGM();//此功能还不成熟
	BeginBatchDraw();//开始批量绘制图片
	while (1)
	{
		Hsb.ShowInterface();
		Hsb.UpdateWithInput();
		Hsb.UpdateWithoutInput();
	}
	EndBatchDraw();//结束批量绘制图片
}

void GameExplanation()
{
	cout << "游戏说明" << endl;
	cout << "1.鼠标控制我方飞机移动" << endl;
	cout << "2.按下空格键发射子弹" << endl;
	cout << "3.我方飞机与敌方飞机发生碰撞时游戏结束" << endl;
	cout << "4.我方飞机HP降至0时游戏结束" << endl;
	cout << "5.我方飞机每次被敌方飞机子弹击中后HP减1" << endl;
	cout << "6.我方飞机击中敌方飞机后分数score加1" << endl;
	cout << "7.我方飞机得分每增加20分我方飞机HP加1" << endl;
	cout << "8.按ESC键游戏暂停，再按ESC键游戏继续" << endl;
	cout << "9.游戏结束时显示此次游戏得分和游戏最高得分" << endl;
	cout << "小细节:游戏开始后请将输入法切换为英文模式" << endl;
	system("pause");
}

int main()
{
	srand((unsigned int)time(0));//随机数种子
	GameExplanation();
	test01();
	return 0;
}