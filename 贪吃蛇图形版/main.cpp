#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<ctime>
#include<graphics.h>
#include<mmsystem.h>
#include<cmath>
#include<math.h>
#include<conio.h>
#include<windows.h>
#include <iostream>
#include<thread>
#include<shellapi.h>
#include"tools.h"
#include"vector2.h"
#include"VK_.h"
#include"lianbiao.h"
#include"assert.h"
#pragma comment(lib,"winmm.lib")

//申明图片
IMAGE img_bg;
IMAGE img_shetou_up;
IMAGE img_shetou_left;
IMAGE img_shetou_right;
IMAGE img_shetou_down;
IMAGE img_shesheng;
IMAGE img_shewei_up;
IMAGE img_shewei_left;
IMAGE img_shewei_right;
IMAGE img_shewei_down;
IMAGE img_shewan_left_up;
IMAGE img_shewan_right_up;
IMAGE img_shewan_left_down;
IMAGE img_shewan_right_down;
IMAGE img_food;
IMAGE img_gameover;
IMAGE img_yinyue;
IMAGE img_pause;


//枚举类型
enum {
	empty,
	shetou,
	shesheng,
	shewei,
	shewan,
	other
};

enum {
	up,
	down,
	left,
	right,
	leftup,
	rightup,
	leftdown,
	rightdown,
	uptoleft,
	uptoright,
	downtoleft,
	downtoright,
	righttoup,
	righttodown,
	lefttoup,
	lefttodown,
	undefined
};//方向枚举

typedef struct FOODS
{
	bool isfood;
	int x;
	int y;
}foods;

foods foodinmap;

bool alive = true;//游戏是否继续

int turnaround(int direction)//转向函数
{
	switch (direction)
	{
	case up:
		return down;
	case down:
		return up;
	case left:
		return right;
	case right:
		return left;
	}
}

int arr[100] = { 0 };
list* she = lian(3, arr);//声明蛇链表
int shedirection = up;//蛇的方向
bool iseat = false;//是否吃了东西
int length = 4;//蛇的长度
int level = 1;//游戏等级
int speed = 1000;//游戏速度

void food();
void whichmod(char key);
void loadimages()//载入图片
{
	loadimage(&img_bg, "res/bg.png");
	loadimage(&img_shetou_up, "res/shetou/shetouup.png");
	loadimage(&img_shetou_left, "res/shetou/shetouleft.png");
	loadimage(&img_shetou_right, "res/shetou/shetouright.png");
	loadimage(&img_shetou_down, "res/shetou1/shetoudownc.png");
	loadimage(&img_shesheng, "res/shesheng/shesheng.png");
	loadimage(&img_shewei_right, "res/shewei/sheweileft.png");
	loadimage(&img_shewei_left, "res/shewei/sheweiright.png");
	loadimage(&img_shewei_up, "res/shewei1/sheweidownc.png");
	loadimage(&img_shewei_down, "res/shewei/sheweiup.png");
	loadimage(&img_food, "res/food/food.png");
	loadimage(&img_shewan_left_up, "res/shewan/shewanleftup.png");
	loadimage(&img_shewan_right_up, "res/shewan/shewanrightup.png");
	loadimage(&img_shewan_left_down, "res/shewan/shewanleftdown.png");
	loadimage(&img_shewan_right_down, "res/shewan/shewanrightdown.png");
	loadimage(&img_yinyue, "res/setting/yinyue.png");
	loadimage(&img_pause, "res/setting/pause.png");
}


char input();


void she_move()//蛇移动
{
	first(&she, 0);
	she->type = shetou;//新建节点为头
	she->direction = shedirection;
	switch (shedirection)
	{
	case up:
		she->x = she->next->x;
		she->y = she->next->y - 1;
		break;
	case down:
		she->x = she->next->x;
		she->y = she->next->y + 1;
		break;
	case left:
		she->x = she->next->x - 1;
		she->y = she->next->y;
		break;
	case right:
		she->x = she->next->x + 1;
		she->y = she->next->y;
		break;
	}

	she->next->type = shesheng;//原蛇头改为蛇身
	delast(&she);//删除最后一个节点
	changelasttype(&she, shewei);//修改最后一个节点为蛇尾
	//changelastdirection(&she,turnaround(getlastdirection(&she)));//转向最后一个节点的方向
}

void iflevelup()//判断是否升级
{
	if (length <= 10)
	{
		level = 1;
	}
	if (length > 10 && length <= 20)
	{
		level = 2;
	}
	if (length > 20 && length <= 30)
	{
		level = 3;
	}
	if (length > 30 && length <= 40)
	{
		level = 4;
	}
	if (length > 40 && length <= 50)
	{
		level = 5;
	}
	if (length > 50 && length <= 60)
	{
		level = 6;
	}
	if (length > 60 && length <= 70)
	{
		level = 7;
	}
	if (length > 70 && length <= 80)
	{
		level = 8;
	}

}

void getbiger()//蛇是否变长，变长则加长
{
	{
		iseat = false;
		int tempdirection = getlastdirection(&she);
		int tempx = getlastx(&she);
		int tempy = getlasty(&she);
		changelasttype(&she, shesheng);
		last(&she, 0);
		changelasttype(&she, shewei);
		changelastdirection(&she, tempdirection);
		switch (tempdirection)
		{
		case up:
			changelastx(&she, tempx);
			changelasty(&she, tempy + 1);
			break;
		case down:
			changelastx(&she, tempx);
			changelasty(&she, tempy - 1);
			break;
		case left:
			changelastx(&she, tempx + 1);
			changelasty(&she, tempy);
			break;
		case right:
			changelastx(&she, tempx - 1);
			changelasty(&she, tempy);
			break;
		}
	}
}

void updatashewei(list** pp)
{
	//printf("正常1\n");
	if (*pp == NULL)
	{
		printf("链表为空，无法修改\n");
		return;
	}
	else
	{
		list* temp = *pp;
		list* temp1 = *pp;
		while (temp->next != NULL)
		{
			temp1 = temp;
			temp = temp->next;
		}
		if (temp1->type == shewan)
		{
			switch (temp1->data == uptoleft || temp1->data == uptoright || temp1->data == righttoup || temp1->data == righttodown || temp1->data == lefttoup || temp1->data == lefttodown || temp1->data == downtoleft || temp1->data == downtoright)
			{
			case uptoleft:
				temp->direction = up;
				break;
			case uptoright:
				temp->direction = up;
				break;
			case righttoup:
				temp->direction = right;
				break;
			case righttodown:
				temp->direction = right;
				break;
			case lefttoup:
				temp->direction = left;
				break;
			case lefttodown:
				temp->direction = left;
				break;
			case downtoleft:
				temp->direction = down;
				break;
			case downtoright:
				temp->direction = down;
				break;
			}
		}
		else if (temp1->type == shesheng)
		{
			temp->direction = temp1->direction;
		}


	}
}

void draw();

void up_game_data()//更新游戏数据
{
	draw();
	whichmod(input());
	iflevelup();
	shedirection = she->direction;
	static int timer = 0;//计时器
	timer += getDelay();///更新计时器
	if (timer >= speed - level * 150)//每隔1000毫秒更新一次地图
	{
		timer = 0;
		printlistall(she);
		she_move();
		//getbiger();
	}

}

int isdown(int VK_) {
	if (_kbhit()) {
		if (GetAsyncKeyState(VK_)) { // 检查高位
			return VK_;
		}
	}
	return 0;
}

char translateKey(int key) {
	// 将 VK 转换为字符，这里简单示例，仅支持数字和字母
	if (key >= VK_0 && key <= VK_9) {
		return '0' + (key - VK_0);
	}
	else if (key >= VK_A && key <= VK_Z) {
		return 'A' + (key - VK_A);
	}
	// 可以扩展更多的映射
	return 0; // 无法转换的返回0
}

char input()
{

	int VK[100] = { VK_0, VK_1, VK_2, VK_3, VK_4, VK_5, VK_6, VK_7, VK_8, VK_9,
					VK_A, VK_B, VK_C, VK_D, VK_E, VK_F, VK_G, VK_H, VK_I, VK_J,
					VK_K, VK_L, VK_M, VK_N, VK_O, VK_P, VK_Q, VK_R, VK_S, VK_T,
					VK_U, VK_V, VK_W, VK_X, VK_Y, VK_Z, VK_F1, VK_F2, VK_F3,
					VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11,
					VK_F12, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_SPACE,
					VK_RETURN, VK_BACK, VK_TAB, VK_SHIFT, VK_CONTROL,
					VK_MENU, VK_CAPITAL, VK_ESCAPE, VK_INSERT, VK_DELETE,
					VK_HOME, VK_END, VK_PRIOR, VK_NEXT, VK_DIVIDE, VK_MULTIPLY,
					VK_SUBTRACT, VK_ADD, VK_DECIMAL, VK_NUMLOCK, VK_SCROLL,
					VK_OEM_1, VK_OEM_PLUS, VK_OEM_COMMA, VK_OEM_MINUS };

	for (int j = 0; j < 100; j++)
	{
		int key = isdown(VK[j]);
		if (key != 0)
		{
			if (1)
			{
				//printf("输入的键值为%d\n", translateKey(key));
				return translateKey(key);
			}
		}
	}
	return 0;
}

int changgechartodirection(char key)
{
	switch (key)
	{
	case 'W':
		//	printf("输入了w\n");
		return up;
	case 'A':
		//printf("输入了a\n");
		return left;
	case 'D':
		//printf("输入了d\n");
		return right;
	case 'S':
		//printf("输入了s\n");
		return down;
	default:
		return undefined;
	}
}

void turnuptoleft()
{
	if (shedirection == up)
	{
		printf("从向上左转\n");
		delast(&she);
		changelasttype(&she, shewei);
		first(&she, 0);
		she->direction = left;
		she->type = shetou;
		she->x = she->next->x - 1;
		she->y = she->next->y;
		she->next->type = shewan;
		she->next->data = uptoleft;
		she->next->direction = left;
		shedirection = left;
	}
}

void turnuptoright()
{
	if (shedirection == up)
	{
		printf("从向上右转\n");
		delast(&she);
		changelasttype(&she, shewei);
		first(&she, 0);
		she->direction = right;
		she->type = shetou;
		she->x = she->next->x + 1;
		she->y = she->next->y;
		she->next->type = shewan;
		she->next->data = uptoright;
		she->next->direction = right;
		shedirection = right;
	}
}

void turndowntoleft()
{
	if (shedirection == down)
	{
		printf("从向下左转\n");
		delast(&she);
		changelasttype(&she, shewei);
		first(&she, 0);
		she->direction = left;
		she->type = shetou;
		she->x = she->next->x - 1;
		she->y = she->next->y;
		she->next->type = shewan;
		she->next->data = downtoleft;
		she->next->direction = left;
		shedirection = left;
	}
}

void turndowntoright()
{
	if (shedirection == down)
	{
		printf("从向下右转\n");
		delast(&she);
		changelasttype(&she, shewei);
		first(&she, 0);
		she->direction = right;
		she->type = shetou;
		she->x = she->next->x + 1;
		she->y = she->next->y;
		she->next->type = shewan;
		she->next->data = downtoright;
		she->next->direction = right;
		shedirection = right;
	}
}

void turnlefttodown()
{
	if (shedirection == left)
	{
		printf("从向左下转\n");
		delast(&she);
		changelasttype(&she, shewei);
		first(&she, 0);
		she->direction = down;
		she->type = shetou;
		she->x = she->next->x;
		she->y = she->next->y + 1;
		she->next->type = shewan;
		she->next->data = lefttodown;
		she->next->direction = down;
		shedirection = down;
	}
}

void turnlefttoup()
{
	if (shedirection == left)
	{
		printf("从向左上转\n");
		delast(&she);
		changelasttype(&she, shewei);
		first(&she, 0);
		she->direction = up;
		she->type = shetou;
		she->x = she->next->x;
		she->y = she->next->y - 1;
		she->next->type = shewan;
		she->next->data = lefttoup;
		she->next->direction = up;
		shedirection = up;
	}
}

void turnrighttoup()
{
	if (shedirection == right)
	{
		printf("从向右上转\n");
		delast(&she);
		changelasttype(&she, shewei);
		first(&she, 0);
		she->direction = up;
		she->type = shetou;
		she->x = she->next->x;
		she->y = she->next->y - 1;
		she->next->type = shewan;
		she->next->data = righttoup;
		she->next->direction = up;
		shedirection = up;
	}
}

void turnrighttodown()
{
	if (shedirection == right)
	{
		printf("从向右下转\n");
		delast(&she);
		changelasttype(&she, shewei);
		first(&she, 0);
		she->direction = down;
		she->type = shetou;
		she->x = she->next->x;
		she->y = she->next->y + 1;
		she->next->type = shewan;
		she->next->data = righttodown;
		she->next->direction = down;
		shedirection = down;
	}
}

void ifeat()
{
	if (foodinmap.isfood)
	{
		if (she->x == foodinmap.x && she->y == foodinmap.y)
		{
			printf("吃到食物\n");
			foodinmap.isfood = false;
			foodinmap.x = 0;
			foodinmap.y = 0;
			getbiger();
			length++;
		}
	}
}

void speedup()
{
	static int timer = 0;
	timer += getDelay();
	if (speed > 100 && timer >= 1000)
	{
		speed -= 100;
		timer = 0;
	}
}
void speeddown()
{
	static int timer = 0;
	timer += getDelay();
	if (speed < 1000 && timer >= 1000)
	{
		speed += 100;
		timer = 0;
	}
}

void whichmod(char key)
{
	//printf("输入的键值为%c\n", key);
	switch (key)
	{
	case 'W':
		turnrighttoup();
		turnlefttoup();
		break;
	case 'A':
		turnuptoleft();
		turndowntoleft();
		break;
	case 'D':
		turnuptoright();
		turndowntoright();
		break;
	case 'S':
		turnrighttodown();
		turnlefttodown();
		break;
	case 'Q':
		speedup();
		break;
	case 'E':
		speeddown();
		break;

	}
}

void ifdead()
{
	if (she->x < 1 || she->x > 10 || she->y < 1 || she->y > 21)
	{
		printf("撞墙死了\n");
		alive = false;
	}
	list* temp = she->next;
	while (temp->next != NULL)
	{
		if (she->x == temp->x && she->y == temp->y)
		{
			alive = false;
			printf("撞自己死了\n");
			break;
		}
		temp = temp->next;
	}
	if (alive == false)
	{
		exit(0);
	}
}

void logic()//游戏逻辑
{
	//turn(input());
	printf("%c", input());
	updatashewei(&she);
	static int timer = 0;
	timer += getDelay();
	up_game_data();
	food();
	ifeat();
	ifdead();


}

void create_she()//创建蛇
{
	she = lian(4, arr);//创建蛇链表

	she->type = shetou;
	she->direction = right;
	she->x = 6;
	she->y = 11;

	she->next->type = shesheng;
	she->next->direction = right;
	she->next->x = 5;
	she->next->y = 11;

	she->next->next->type = shesheng;
	she->next->next->direction = right;
	she->next->next->x = 4;
	she->next->next->y = 11;

	she->next->next->next->type = shewei;
	she->next->next->next->direction = right;
	she->next->next->next->x = 3;
	she->next->next->next->y = 11;
}

void draw_she()//绘制蛇
{

	int i = 0;
	list* temp = she;
	while (she != NULL)
	{
		switch (she->type)
		{
		case shetou:
			switch (she->direction)
			{
			case up:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shetou_up);
				break;
			case down:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shetou_down);
				break;
			case left:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shetou_left);
				break;
			case right:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shetou_right);
				break;
			}
			break;
		case shesheng:
			putimagePNG(37 + she->x * 57, she->y * 57, &img_shesheng);
			break;
		case shewan:
			switch (she->data)
			{
			case uptoleft:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shewan_left_down);
				break;
			case uptoright:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shewan_right_down);
				break;
			case downtoleft:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shewan_left_up);
				break;
			case downtoright:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shewan_right_up);
				break;
			case righttodown:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shewan_left_down);
				break;
			case righttoup:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shewan_left_up);
				break;
			case lefttodown:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shewan_right_down);
				break;
			case lefttoup:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shewan_right_up);
				break;
			}
			break;
		case shewei:

			switch (she->direction)
			{
			case up:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shewei_up);
				break;
			case down:
				//putimagePNG(37 + she->x * 57, she->y * 57, &img_shesheng);
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shewei_down);
				break;
			case left:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shewei_left);
				break;
			case right:
				putimagePNG(37 + she->x * 57, she->y * 57, &img_shewei_right);
				break;
			}
			break;
		}
		she = she->next;
	}
	she = temp;
}

void draw_ui()//绘制UI
{
	putimagePNG(0, 0, &img_bg);
}

void draw_food()//绘制食物
{
	if (foodinmap.isfood)
	{
		putimagePNG(37 + foodinmap.x * 57, foodinmap.y * 57, &img_food);
	}
}

void draw()//绘制
{
	BeginBatchDraw();
	draw_ui();
	draw_she();
	draw_food();
	EndBatchDraw();
}



void initgame()//初始化游戏
{
	initgraph(700, 1200, 1);//设置窗口大小
	
	loadimages();//载入图片
	create_she();
}

void food()//生成食物
{
	if (foodinmap.isfood == false)//如果食物不在地图中
	{
		srand(time(NULL));
		foodinmap.x = rand() % 9 + 2;
		foodinmap.y = rand() % 16 + 2;
		foodinmap.isfood = true;
	}
}

void menu()//菜单
{
	putimagePNG(0,0,&img_bg);
	putimagePNG(140,442, &img_yinyue);
	putimagePNG(440, 442, &img_pause);
	int c = _getch();
	mciSendString("open new Type mp3 alias bgm repeat", NULL, 0, NULL);
}

void loadmusic()//载入音乐
{
	mciSendString("open res/bgmusic.mp3 alias bgmusic", NULL, 0, NULL);
	mciSendString("play bgmusic", NULL, 0, NULL);
}

int main()
{
	std::thread newThread1(loadmusic);
	newThread1.detach();
	initgame();
	menu();
	int i = 1;
	while (1)
	{
		logic();
	}
	return 0;
}








