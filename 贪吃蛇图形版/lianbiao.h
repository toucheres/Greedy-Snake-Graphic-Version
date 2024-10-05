#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"tools.h"
#include"VK_.h"
#pragma comment(lib,"winmm.lib")

struct note
{
	int data;
	int type;
	int x;
	int y;
	int direction;
	struct note* next;
};//链表结构
typedef struct note list;
list* create(int x);
void printlist(list* p);
void last(list** pp, int x);
void first(list** pp, int x);
void  defirst(list** pp);
void  delast(list** pp);
list* lian(int x, int* arr);
void freelian(list** p);
int delone(int x, list** pp);
int  delall(int x, list** pp);
void addlist(list** pp, int x, int* nump);
void  changelasttype(list** pp, int tp);
void  changefirsttype(list** pp, int tp);
list* lian(int x, int* arr);
void  changelastdirection(list** pp, int di);
int getlastdirection(list** pp);
int getlasty(list** pp);
int getlastx(list** pp);
void  changelasty(list** pp, int di);
void  changelastx(list** pp, int di);
void  printlistall(list* p);//打印列表所有信息
void  changelastdata(list** pp, int di);