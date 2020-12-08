#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char MM[14] = "123456";
struct Teacher                                                 //教师信息
{
	char number[20];                                           //教师号
	char name[48];                                             //姓名
	char gender[10];                                           //性别
	int age;                                                   //年龄
	char work[128];                                            //职称
	char money[14];                                            //工资
	char place[128];                                           //单位
};
struct Node                                                    //节点
{
	struct Teacher date;
	struct Node* next;
};
struct VIP                                                     //登录信息
{
	char mun[14];
	char YHname[128];
}vip[10];
struct Node* createList()                                      //创建头节点
{
	struct Node* HeadNode = (struct Node*)malloc(sizeof(struct Node));
	HeadNode->next = NULL;
	return HeadNode;
}
struct Node* createNode(struct Teacher date)                    //创建节点
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->date = date;
	newNode->next = NULL;
	return newNode;
}
struct Node* list;                                                   //创建链表
int DL();                                                            //登录系统   
int Registeruser(int j);                                             //创建账户（10个）
void systemMenu();                                                   //菜单
void keyDown(struct Node* HeadNode);                                 //交互界面
void Help();                                                         //系统帮助
void InputMessage(struct Node* HeadNode, Teacher date);              //录入信息
void ShowMessage(struct Node* HeadNode);                             //浏览信息
struct Node* FindMessageNumber(struct Node* HeadNode, char* date);    //查找信息（编号）
void ShowNowMessage(struct Node* nowNode);                           //打印当前节点
void DeleteMessageNumber(struct Node* HeadNode, char* date);         //删除信息（编号）
void DeleteMessageName(struct Node* HeadNode, char* message);        //删除信息（姓名）
void ChangeYHMessageame(const char* tempname);                       //改变用户信息
void WriteFile(struct Node* HeadNode, const char* fileName);         //保存文件
void ReadFile(struct Node* HeadNode, const char* fileName);           //读取文件
int main()
{
	list = createList();
	ReadFile(list, "教师信息档案.txt");
	int t = 1, flag = 0, key;
	printf("/**********欢迎使用教师信息管理系统**********/\n");
	printf("/******************0.登录系统******************/\n");
	printf("/******************1.注册系统******************/\n");
	printf("/******************2.系统帮助******************/\n");
	printf("/******************3.退出系统******************/\n");
	printf("/********************************************/\n");
	printf("请输入0~3：\n");
	printf("提示：机会只有一次！\n");
	scanf("%d", &key);
	switch (key)
	{
	case 0:
		printf("0.登录系统\n");
		if (DL() == 1)
		{
			flag = 1;
		}
		break;
	case 1:
		printf("1.注册系统\n");
		int j;
		char MY[14];
		printf("请输入密钥：\n");
		scanf("%s", MY);
		if (strcmp(MM, MY) == 0
			)
		{
			printf("请输入1~10中的一个数字作为编号:\n");
			scanf("%d", &j);
			if (Registeruser(j) == 1)
			{
				flag = 1;
			}
		}
		else
		{
			printf("密钥错误，退出系统！\n");
			exit(0);
		}
		break;
	case 2:
		printf("2.系统帮助\n");
		Help();
		system("pause");
		break;
	case 3:
		printf("3.退出系统\n");
		exit(0);
		system("pause");
		break;
	}
	system("cls");
	while (flag == 1)
	{
		systemMenu();
		keyDown(list);
		system("pause");
		system("cls");
	}
	return 0;
}
int DL()
{
	char Mname[100], mm[12];
	int i = 0, flag = 0;
	printf("请输入用户名：\n");
	scanf("%s", Mname);
	printf("请输入密码：\n");
	scanf("%s", mm);
	FILE* fp;
	fp = fopen("账号信息档案.txt", "r");
	while (!feof(fp))
	{
		fscanf(fp, "%s %sn", &vip[i].YHname, &vip[i].mun);
		if ((strcmp(vip[i].YHname, Mname) == 0) && (strcmp(vip[i].mun, mm) == 0))
		{
			flag = 1;
			fclose(fp);
			break;
		}
		i++;
	}
	if (flag == 1)
	{
		printf("登陆成功！\n");
		system("pause");
		return 1;
	}
	else
	{
		printf("用户名错误或密码错误！\n");
		return 0;
	}
}
int Registeruser(int j)
{
	char YHname[128];
	char pw[14], pd[14];
	printf("【注册帐号】\n");
	FILE* fp = fopen("账号信息档案.txt", "ab");
	printf("提示：账号、密码可以为数字,中文字母,英文字母,符号.\n");
	printf("请你输入账号：\n");
	scanf("%s", YHname);
	strcpy(vip[j].YHname, YHname);
	printf("请你输入密码：\n");
	scanf("%s", pw);
	strcpy(vip[j].mun, pw);
	printf("再次确认密码：\n");
	scanf("%s", pd);
	if (strcmp(vip[j].mun, pd) != 0)
	{
		printf("注册失败!!!\n");
		return 0;
	}
	else
	{
		fprintf(fp, "账号\t密码\n");
		fprintf(fp, "%s\t%s\n", vip[j].YHname, vip[j].mun);
		printf("\n注册成功!!!\n");
		fclose(fp);
		return 1;
		system("pause");
		system("cls");
	}
}
void systemMenu()
{
	printf("-------------------【教师信息管理系统】----------------\n");
	printf("\t\t0.录入信息\n");	
		printf("\t\t1.浏览信息\n");
		printf("\t\t2.查找信息\n");
		printf("\t\t3.修改信息\n");
		printf("\t\t4.删除信息\n");
		printf("\t\t5.修改用户信息\n");
		printf("\t\t6.教师信息统计\n");
		printf("\t\t7.退出系统\n");
	printf("-------------------------------------------------------\n");
	printf("请输入(0~7)\n");
}
void keyDown(struct Node* HeadNode)
{
	int usekey, t = 0, y = 0, p = 0, q[3] = { 0 };
	struct Teacher tempDate;
	struct Node* pMove = HeadNode->next;
	scanf("%d", &usekey);
	switch (usekey)
	{
	case 0:
		printf("\t\t0.录入信息\n");
		printf("请输入教师的教师号\n");
		scanf("%s", tempDate.number);
		while (pMove != NULL)
		{
			if (strcmp(pMove->date.number, tempDate.number) == 0)
			{
				printf("教师号重复！");
				t = 1;
			}
			pMove = pMove->next;
		}
		if (t == 1)
		{
			break;
		}
		printf("请输入教师的姓名\n");
		scanf("%s", tempDate.name);
		printf("请输入教师的性别\n");
		scanf("%s", tempDate.gender);
		printf("请输入教师的年龄\n");
		scanf("%d", &tempDate.age);
		printf("请输入教师的职称\n");
		scanf("%s", tempDate.work);
		printf("请输入教师的工资\n");
		scanf("%s", tempDate.money);
		printf("请输入教师的单位\n");
		scanf("%s", tempDate.place);
		InputMessage(list, tempDate);
		break;
	case 1:
		printf("\t\t1.浏览信息\n");
		ShowMessage(list);
		break;
	case 2:
		int way;
		printf("\t\t0.查找信息\n");
		printf("0.按教师号查找\t1.按姓名查找\t2.按职称查找\t3.按单位查找\n");
		scanf("%d", &way);
		switch (way)
		{
		case 0:
			printf("请输入要查找教师的教师号:");
			scanf("%s", tempDate.number);
			if (FindMessageNumber(list, tempDate.number) == NULL)
			{
				printf("查无此人\n");
				break;
			}
			else
			{
				ShowNowMessage(FindMessageNumber(list, tempDate.number));
			}
			break;
		case 1:
			printf("请输入要查找教师的姓名:");
			scanf("%s", tempDate.name);
			if (pMove == NULL)
			{
				printf("无此人\n");
				break;
			}
			else
			{
				while (pMove != NULL)
				{
					if (strcmp(pMove->date.name, tempDate.name) == 0)
					{
						ShowNowMessage(pMove);
					}
					pMove = pMove->next;
				}
			}
			break;
		case 2:
			printf("请输入要查找教师的职称:");
			scanf("%s", tempDate.work);
			if (pMove == NULL)
			{
				printf("无此人\n");
				break;
			}
			else
			{
				while (pMove != NULL)
				{
					if (strcmp(pMove->date.work, tempDate.work) == 0)
					{
						ShowNowMessage(pMove);
					}
					pMove = pMove->next;
				}
			}
			break;
		case 3:
			printf("请输入要查找教师的单位:");
			scanf("%s", tempDate.place);
			if (pMove == NULL)
			{
				printf("无此人\n");
				break;
			}
			else
			{
				while (pMove != NULL)
				{
					if (strcmp(pMove->date.place, tempDate.place) == 0)
					{
						ShowNowMessage(pMove);
					}
					pMove = pMove->next;
				}
			}
			break;
		default:
			printf("输入错误！请重新输入......");
			break;
		}
		break;
	case 3:
		printf("\t\t3.修改信息\n");
		char MY[14];
		printf("请输入密钥：\n");
		scanf("%s", MY);
		if (strcmp(MM, MY) == 0)
		{
			printf("请输入要修改教师的教师号:");
			scanf("%s", tempDate.number);
			if (FindMessageNumber(list, tempDate.number) == NULL)
			{
				printf("查无此人\n");
				break;
			}
			else
			{
				struct Node* nowNode = FindMessageNumber(list, tempDate.number);
				ShowNowMessage(nowNode);
				printf("请输入教师的教师号\n");
				scanf("%s", tempDate.number);
				strcpy(nowNode->date.number, tempDate.number);
				printf("请输入教师的姓名\n");
				scanf("%s", tempDate.name);
				strcpy(nowNode->date.name, tempDate.name);
				printf("请输入教师的性别\n");
				scanf("%s", tempDate.gender);
				strcpy(nowNode->date.gender, tempDate.gender);
				printf("请输入教师的年龄\n");
				scanf("%d", &tempDate.age);
				nowNode->date.age = tempDate.age;
				printf("请输入教师的职称\n");
				scanf("%s", tempDate.work);
				strcpy(nowNode->date.work, tempDate.work);
				printf("请输入教师的工资\n");
				scanf("%s", tempDate.money);
				strcpy(nowNode->date.money, tempDate.money);
				printf("请输入教师的单位\n");
				scanf("%s", tempDate.place);
				strcpy(nowNode->date.place, tempDate.place);
				ShowNowMessage(FindMessageNumber(list, tempDate.number));
			}
		}
		else
		{
			printf("密钥错误！\n");
			break;
		}
		break;
	case 4:
		int xg;
		printf("\t\t4.删除信息\n");
		char MK[14];
		printf("请输入密钥：\n");
		scanf("%s", MK);
		if (strcmp(MM, MK) == 0)
		{
			printf("请选择删除方式 1.教师号 2.姓名\n");
			scanf("%d", &xg);
			switch (xg)
			{
			case 1:
				printf("请输入要删除教师的教师号:");
				scanf("%s", tempDate.number);
				DeleteMessageNumber(list, tempDate.number);
				break;
			case 2:
				printf("请输入要删除教师的姓名:");
				scanf("%s", tempDate.name);
				DeleteMessageName(list, tempDate.name);
				break;
			default:
				printf("输入错误");
				break;
			}
		}
		else
		{
			printf("密钥错误！\n");
			break;
		}
		break;
	case 5:
		printf("\t\t5.修改用户信息\n");
		char tempname[128];
		printf("请输入您现在的用户名：\n");
		scanf("%s", tempname);
		ChangeYHMessageame(tempname);
		break;
	case 6:
		printf("\t\t6.教师信息统计\n");
		int r;
		printf("请输入统计标准：1.性别 2.年龄 3.单位\n");
		scanf("%d", &r);
		switch (r)
		{
		case 1:
			char gen[20];
			printf("请输入要统计的性别（男/女）：");
			scanf("%s", gen);
			while (pMove != NULL)
			{
				if (strcmp(pMove->date.gender, gen) == 0)
				{
					ShowNowMessage(pMove);
					y++;
				}
				pMove = pMove->next;
			}
			printf("%s人共%d人.\n", gen, y);
			break;
		case 2:
			int a;
			printf("请输入统计的年龄段：1.20~30 2.30~40 3.40~50 4.50~60\n");
			scanf("%d", &a);
			switch (a)
			{
			case 1:
				while (pMove != NULL)
				{
					if (20 <= pMove->date.age && pMove->date.age < 30)
					{
						ShowNowMessage(pMove);
						q[0]++;
					}
					pMove = pMove->next;
				}
				printf("年龄在20~30的人共%d人.\n", q[0]);
				break;
			case 2:
				while (pMove != NULL)
				{
					if (30 <= pMove->date.age && pMove->date.age < 40)
					{
						ShowNowMessage(pMove);
						q[1]++;
					}
					pMove = pMove->next;
				}
				printf("年龄在30~40的人共%d人.\n", q[1]);
				break;
			case 3:
				while (pMove != NULL)
				{
					if (40 <= pMove->date.age && pMove->date.age < 50)
					{
						ShowNowMessage(pMove);
						q[2]++;
					}
					pMove = pMove->next;
				}
				printf("年龄在40~50的人共%d人.\n", q[2]);
				break;
			case 4:
				while (pMove != NULL)
				{
					if (50 <= pMove->date.age && pMove->date.age <= 60)
					{
						ShowNowMessage(pMove);
						q[3]++;
					}
					pMove = pMove->next;
				}
				printf("年龄在50~60的人共%d人.\n", q[3]);
				break;
			default:
				printf("输入错误");
				break;
			}
			break;
		case 3:
			char Y[1280];
			printf("请输入要统计的单位：");
			scanf("%s", Y);
			while (pMove != NULL)
			{
				if (strcmp(pMove->date.place, Y) == 0)
				{
					ShowNowMessage(pMove);
					p++;
				}
				pMove = pMove->next;
			}
			printf("%s的人共%d人.\n", Y, p);
			break;
		default:
			printf("输入错误");
			break;
		}
		break;
	case 7:
		printf("\t\t7.退出系统\n");
		system("pause");
		exit(0);
		break;
	default:
		printf("输入错误，请重新输入：");
		break;
	}
	WriteFile(list, "教师信息档案.txt");
}
void Help()
{
	printf("\n\t\t\t0.欢迎使用系统帮助！\n");
	printf("\n\t\t\t1.初次进入系统后,请先创建账号，密码。\n");
	printf("\n\t\t\t2.按照菜单提示键入数字代号;\n");
	printf("\n\t\t\t3.增加学生信息后会自动保存;\n");
	printf("\n\t\t\t4.谢谢您的使用！\n");
}
void InputMessage(struct Node* HeadNode, Teacher date)
{
	struct Node* newNode = createNode(date);
	newNode->next = HeadNode->next;
	HeadNode->next = newNode;
}
void ShowMessage(struct Node* HeadNode)
{
	struct Node* pMove = HeadNode->next;
	printf("教师号\t姓名\t性别\t年龄\t职称\t\t工资\t单位\n");
	while (pMove)
	{
		printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\n", pMove->date.number, pMove->date.name, pMove->date.gender, pMove->date.age, pMove->date.work, pMove->date.money, pMove->date.place);
		pMove = pMove->next;
	}
	printf("\n");
}
struct Node* FindMessageNumber(struct Node* HeadNode, char* date)
{
	struct Node* pMove = HeadNode->next;
	if (pMove == NULL)
		return pMove;
	else
	{
		while (strcmp(pMove->date.number, date))
		{
			pMove = pMove->next;
			if (pMove == NULL)
				break;
		}
		return pMove;
	}
}
void ShowNowMessage(struct Node* nowNode)
{
	printf("教师号\t姓名\t性别\t年龄\t职称\t\t工资\t单位\n");
	printf("%s\t%s\t%s\t%d\t%s\t%s\t%s\n", nowNode->date.number, nowNode->date.name, nowNode->date.gender, nowNode->date.age, nowNode->date.work, nowNode->date.money, nowNode->date.place);
}
void DeleteMessageNumber(struct Node* HeadNode, char* date)
{
	struct Node* posfrontNode = HeadNode;
	struct Node* posNode = HeadNode->next;
	if (posNode == NULL)
	{
		printf("无相关内容\n");
		return;
	}
	else
	{
		while (strcmp(posNode->date.number, date))
		{
			posfrontNode = posNode;
			posNode = posfrontNode->next;
			if (posNode == NULL)
			{
				printf("无相关内容\n");
				return;
			}
		}
		posfrontNode->next = posNode->next;
		free(posNode);
	}
}
void DeleteMessageName(struct Node* HeadNode, char* message)
{
	struct Node* posfrontNode = HeadNode;
	struct Node* posNode = HeadNode->next;
	if (posNode == NULL)
	{
		printf("无相关内容\n");
		return;
	}
	else
	{
		while (strcmp(posNode->date.name, message))
		{
			posfrontNode = posNode;
			posNode = posfrontNode->next;
			if (posNode == NULL)
			{
				printf("无相关内容\n");
				return;
			}
		}
		posfrontNode->next = posNode->next;
		free(posNode);
	}
}
void ChangeYHMessageame(const char* tempname)
{
	int j = 0, flag = 0;
	char name[128], nnu[14];
	FILE* fp;
	fp = fopen("账号信息档案.txt", "r");
	while (!feof(fp))
	{
		fscanf(fp, "%s", &vip[j].YHname);
		if (strcmp(vip[j].YHname, tempname) == 0)
		{
			flag = 1;
			fclose(fp);
			break;
		}
		j++;
	}
	if (flag == 1)
	{
		printf("请输入新的用户名：\n");
		scanf("%s", name);
		printf("请输入新的密码：\n");
		scanf("%s", nnu);
		strcpy(vip[j].YHname, name);
		strcpy(vip[j].mun, nnu);
		fp = fopen("账号信息档案.txt", "w");
		fprintf(fp, "账号\t密码\n");
		fprintf(fp, "%s\t%s\n", vip[j].YHname, vip[j].mun);
		fclose(fp);
	}
	if (flag == 0)
	{
		printf("用户名错误！\n");
	}
}
void WriteFile(struct Node* HeadNode, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "w");
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
	}
	struct Node* pMove = HeadNode->next;
	while (pMove)
	{
		fprintf(fp, "%s\t%s\t%s\t%d\t%s\t%s\t%s\n", pMove->date.number, pMove->date.name, pMove->date.gender, pMove->date.age, pMove->date.work, pMove->date.money, pMove->date.place);
		pMove = pMove->next;
	}
	fclose(fp);
}
void ReadFile(struct Node* HeadNode, const char* fileName)
{
	FILE* fp;
	struct Teacher date;
	fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		fp = fopen(fileName, "w+");
	}
	while (fscanf(fp, "%s\t%s\t%s\t%d\t%s\t%s\t%s\n", date.number, date.name, date.gender, &date.age, date.work, date.money, date.place) != EOF)
	{
		struct Node* newNode = createNode(date);
		newNode->next = HeadNode->next;
		HeadNode->next = newNode;
	}
	fclose(fp);
}