#include<stdio.h>
#include<stdlib.h>
#include<lianbiao.h>


//typedef struct note
//{
//	int data;
//	struct note* next;
//}list;//链表结构

list* create(int x)
{
	list* p = (list*)malloc(sizeof(list));
	if (p == NULL)
	{
		printf("创建失败\n");
		return NULL;
	}
	p->data = x;
	p->next = NULL;
	return p;
}//创建节点

void printlist(list* p)
{

	if (p == 0)
	{
		printf("无内容\n");
		return;
	}
	else
	{
		printf("%d->", p->data);
	}
	if ((p != 0) && (p->next) != NULL)
	{
		printlist(p->next);
	}
	else
	{
		printf("打印完成\n");
	}

}//打印链表


 void  printlistall(list* p)//打印列表所有信息
{
	if (p == 0)
	{
		printf("无内容\n");
		return;
	}
	else
	{
		printf("data:%d,direction:%d,x:%d,y:%d\n", p->data, p->direction, p->x, p->y);
	}
	if ((p != 0) && (p->next) != NULL)
	{
		printlistall(p->next);
	}
	else
	{
		printf("打印完成\n");
	}

}

void last(list** pp, int x)//(&p,x)
{
	list* temp = *pp;
start:
	if ((temp)->next != NULL)
	{
		temp = (temp)->next;
		goto start;
	}

	(temp)->next = create(x);
}//在最后插入节点

void first(list** pp, int x)//(&p,x)
{
	list* newhead = create(x);
	if (*pp == NULL)
	{

		*pp = newhead;
	}
	else
	{
		newhead->next = *pp;
		*pp = newhead;
	}
}//在最前插入节点

void  changefirsttype(list** pp, int tp)//(&p,x)
{
	if (*pp == NULL)
	{
		printf("链表为空，无法修改\n");
		return;
	}
	else
	{
		(*pp)->type = tp;		
	}

}//修改第一个节点

void  defirst(list** pp)//(&p,x)
{
	if (*pp == NULL)
	{
		printf("链表为空，无法删除\n");
		return;
	}
	else
	{
		list* temp = *pp;
		*pp = (*pp)->next;
		free(temp);
	}

}//删除第一个节点

void  delast(list** pp)
{
	if (*pp == NULL)
	{
		printf("链表为空，无法删除\n");
		return;
	}

	list* current = *pp;
	list* previous = NULL;

	// 找到倒数第二个节点
	while (current->next != NULL)
	{
		previous = current;
		current = current->next;
	}

	// 如果链表只有一个节点
	if (previous == NULL)
	{
		free(*pp);
		*pp = NULL;
	}
	else
	{
		free(current);
		previous->next = NULL;
	}
}//删除最后一个节点

void  changelasttype(list** pp, int tp)
{
	if (*pp == NULL)
	{
		printf("链表为空，无法修改\n");
		return;
	}
	else
	{
		list* temp = *pp;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->type = tp;
	}

}//修改最后一个节点类型

void  changelastdirection(list** pp, int di)
{
	if (*pp == NULL)
	{
		printf("链表为空，无法修改\n");
		return;
	}
	else
	{
		list* temp = *pp;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->direction = di;
	}
}

void  changelastx(list** pp, int di)
{
	if (*pp == NULL)
	{
		printf("链表为空，无法修改\n");
		return;
	}
	else
	{
		list* temp = *pp;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->x = di;
	}
}

void  changelastdata(list** pp, int di)
{
	if (*pp == NULL)
	{
		printf("链表为空，无法修改\n");
		return;
	}
	else
	{
		list* temp = *pp;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->data = di;
	}
}

void  changelasty(list** pp, int di)
{
	if (*pp == NULL)
	{
		printf("链表为空，无法修改\n");
		return;
	}
	else
	{
		list* temp = *pp;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->y = di;
	}
}

int getlastdirection(list** pp)
{
	if (*pp == NULL)
	{
		printf("链表为空，无法修改\n");
		return 0;
	}
	else
	{
		list* temp = *pp;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		return temp->direction;
	}
}


int getlastx(list** pp)
{
	if (*pp == NULL)
	{
		printf("链表为空，无法修改\n");
		return 0;
	}
	else
	{
		list* temp = *pp;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		return temp->x;
	}
}

int getlasty(list** pp)
{
	if (*pp == NULL)
	{
		printf("链表为空，无法修改\n");
		return 0;
	}
	else
	{
		list* temp = *pp;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		return temp->y;
	}
}

list* lian(int x, int* arr)
{

	if (x <= 0)
	{
		printf("无节点，返回为空\n");
		return NULL;
	}
	else
	{
		list* start = create(arr[0]);
		list* temp = start;
		int i = 1;
		for (i; i < x; i++)
		{
			start->next = create(0);
			start = start->next;
			start->data = arr[i];

		}
		return temp;
	}
}//创建链表

void freelian(list** p)//(&li)
{
	list* li = *p;
	if (*p == NULL)
		return;
	if (li->next != NULL)
	{
		freelian(&(li->next));
	}
	if (li->next == NULL)
	{
		free(li);
		li = NULL;
	}
	free(li);
	*p = NULL;
}//释放链表

int delone(int x, list** pp)
{


	list* f = *pp;
	list* b = NULL;
	if (f->data == x)
	{
		defirst(pp);
		return 1;
	}
	else
	{
		while (f->next != NULL)
		{
			if (f->data == x)
			{
				b->next = f->next;
				free(f);
				return 1;
			}
			b = f;
			f = f->next;
		}
		//printf("未找到%d\n", x);
		return 0;
	}
}//删除首个指定节点

int  delall(int x, list** pp)
{
	int flag = 0;
start:
	if (delone(x, pp))
	{
		flag++;
		goto start;
	}
	return flag;
}//删除所有指定节点

void addlist(list** pp, int x, int* nump)
{
	if (pp == NULL)
	{
		*pp = lian(x, nump);
		printf("链表为空，已创建\n");
		return;
	}
	list* temp = *pp;
	if (temp == NULL)
	{
		*pp = lian(x, nump);
		printf("链表为空，已创建\n");
		return;
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = lian(x, nump);
	printf("已添加\n");
	return;
}//尾部添加链表
//
//int main()
//{
//
//	int arr2[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	list* lianbiao = NULL;
//	printlist(lianbiao);
//	addlist(&lianbiao, 6, arr2);
//	printlist(lianbiao);
//	defirst(&lianbiao);
//	printlist(lianbiao);
//	delast(&lianbiao);
//	printlist(lianbiao);
//	delall(3, &lianbiao);
//	printlist(lianbiao);
//	freelian(&lianbiao);
//	printlist(lianbiao);
//
//
//	return 0;
//}

