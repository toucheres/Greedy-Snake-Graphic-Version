#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include"VK_.h"
#include<conio.h>
#include<winuser.h>
#include<stdio.h>


int VK[100] = { VK_0,VK_1,VK_2,VK_3,VK_4,VK_5,VK_6,VK_7,VK_8,VK_9,VK_A,VK_B,VK_C,VK_D,VK_E,VK_F,VK_G,VK_H,VK_I,VK_J,VK_K,VK_L,VK_M,VK_N,VK_O,VK_P,VK_Q,VK_R,VK_S,VK_T,VK_U,VK_V,VK_W,VK_X,VK_Y,VK_Z,VK_F1,VK_F2,VK_F3,VK_F4,VK_F5,VK_F6,VK_F7,VK_F8,VK_F9,VK_F10,VK_F11,VK_F12,VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,VK_SPACE,VK_RETURN,VK_BACK,VK_TAB,VK_SHIFT,VK_CONTROL,VK_MENU,VK_CAPITAL,VK_ESCAPE,VK_INSERT,VK_DELETE,VK_HOME,VK_END,VK_PRIOR,VK_NEXT,VK_DIVIDE,VK_MULTIPLY,VK_SUBTRACT,VK_ADD,VK_DECIMAL,VK_NUMLOCK,VK_SCROLL,VK_OEM_1,VK_OEM_PLUS,VK_OEM_COMMA,VK_OEM_MINUS, };

int isdown(int VK_)
{
	if (_kbhit())
	{
		if (GetAsyncKeyState(VK_))
		{
			return VK_;
		}
		else
		{
			return 0;
		}
	}
}

void input(int input[])
{
	int j = 0;
	int i = 0;
	for (j = 0; j < 100; j++)
	{
		int key = isdown(VK[j]);
		if (key)
		{
			input[i] = key;
			i++;
		}
	}
}

//int main()
//{
//	while (1)
//	{
//		int inputpool[100] = { 0 };
//		input(inputpool);
//		for (int i = 0; i < 100; i++)
//		{
//			if (inputpool[i])
//			{
//				printf("%d ", inputpool[i]);
//			}
//		}
//		Sleep(100);
//	}
//	return 0;
//}

