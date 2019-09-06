#include<stdio.h>
#include<string.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
/****************************************************************/
#define Height 59  //迷宫的高度，必须为奇数
#define Width 59  //迷宫的宽度，必须为奇数
#define Road 0
#define Wall 1
#define Start 2
#define End 3
#define Up 1
#define Down 2
#define Left 3
#define Right 4
#define Esc 5
int M_Map[Height+2][Width+2];
/****************************************************************/
#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'
char click = 1;
int score=0;   //记录分数 
/****************************************************************/
#define MOD 28
#define R_X 19
#define R_Y 12
int x,y;
int R_score,mark,next,R_Map[R_X][R_Y],R_GameSpeed=300;
/****************************************************************/
#define	SWN		3	// 课程数
#define NAMELEN		20	// 姓名最大字符数
#define CODELEN		10	// 学号最大字符数
#define FNAMELEN	80	// 文件名最大字符数
#define BUFLEN		80	// 缓冲区最大字符数
/****************************************************************/
void gotoxy(int x,int y)  //移动坐标
{
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}
void hidden()  //隐藏光标
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut,&cci);
    cci.bVisible=0;  //赋1为显示，赋0为隐藏
    SetConsoleCursorInfo(hOut,&cci);
}
/****************************************************************/
int  P_Map[5][16][16] =   //地图 
{
	{0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,
	 0,1,1,1,0,5,1,0,0,0,0,0,0,0,0,0,
	 0,1,0,0,4,0,1,0,0,0,0,0,0,0,0,0,
	 1,1,0,1,0,1,1,1,0,0,0,0,0,0,0,0,
	 1,0,0,1,0,1,3,1,0,0,0,0,0,0,0,0,
	 1,0,1,0,0,4,3,1,0,0,0,0,0,0,0,0,
	 1,0,4,0,0,0,3,1,0,0,0,0,0,0,0,0,
	 1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	 
	{0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,
	 0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,0,
	 1,1,3,0,4,1,1,0,1,1,0,0,0,0,0,0,
	 1,3,3,4,0,4,0,0,5,1,0,0,0,0,0,0,
	 1,3,3,0,4,0,4,0,1,1,0,0,0,0,0,0,
	 1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,
	 0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	 
	{0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,
	 0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,
	 0,0,0,0,0,1,0,0,4,4,0,1,0,0,0,0,
	 1,1,1,1,1,1,0,4,1,0,0,1,0,0,0,0,
	 1,3,3,3,1,1,1,0,1,0,0,1,0,0,0,0,
	 1,3,0,0,1,0,0,4,0,1,0,1,1,0,0,0,
	 1,3,0,0,0,0,4,0,4,0,4,0,1,0,0,0,
	 1,3,0,0,1,0,0,4,0,1,0,0,1,0,0,0,
	 1,3,3,3,1,1,1,0,1,0,0,0,1,0,0,0,
	 1,1,1,1,1,1,0,4,0,0,0,1,1,0,0,0,
	 0,0,0,0,0,1,0,5,1,0,0,1,0,0,0,0,
	 0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	 
	{0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,
	 0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,
	 0,1,1,1,1,0,0,4,4,1,1,1,1,1,0,0, 
	 0,1,0,0,0,1,0,0,0,0,0,0,0,1,0,0, 
	 0,1,0,4,0,0,0,4,0,0,0,4,0,1,0,0, 
	 0,1,0,0,0,1,1,0,1,1,1,1,1,1,0,0, 
	 1,1,1,1,4,1,1,0,0,0,0,0,0,1,0,0, 
	 1,0,0,0,4,0,1,0,0,0,5,0,0,1,0,0, 
	 1,0,4,0,4,0,1,0,1,1,1,1,1,1,0,0, 
	 1,1,0,0,4,0,1,0,1,3,3,3,1,0,0,0,
	 0,1,0,1,0,0,0,0,0,3,3,3,1,0,0,0,
	 0,1,0,0,0,0,1,1,3,3,3,3,1,0,0,0, 
	 0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	 
	{1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,
	 1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,
	 1,0,4,3,0,1,1,0,1,1,0,3,4,0,1,0,
	 1,1,0,4,3,0,1,1,1,0,3,4,0,1,1,0,
	 0,1,1,0,4,3,0,5,0,3,4,0,1,1,0,0,
	 0,0,1,1,0,4,3,0,3,4,0,1,1,0,0,0,
	 0,0,0,1,1,4,3,1,3,4,1,1,0,0,0,0,
	 0,0,1,1,0,4,3,1,3,4,0,1,1,0,0,0,
	 0,1,1,0,4,3,0,1,0,1,4,0,1,1,0,0,
	 1,1,0,4,3,0,1,1,1,0,3,4,0,1,1,0,
	 1,0,4,3,0,1,1,0,1,1,0,3,4,0,1,1,
	 1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1,
	 1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};
/****************************************************************/
int R_Shape[28][6]=
{  //存储方块的所有排列 
    {0,-1,0,-2,1,0}, {0,1,1,0,2,0}, {-1,0,0,1,0,2}, {0,-1,-1,0,-2,0},
    {0,-1,0,1,-1,0}, {0,1,1,0,-1,0}, {1,0,0,-1,0,1}, {1,0,-1,0,0,-1},
    {-1,1,0,1,1,0}, {0,-1,1,0,1,1}, {-1,0,0,-1,1,-1}, {-1,-1,-1,0,0,1},
    {-1,0,0,1,1,1}, {0,1,1,-1,1,0}, {-1,0,0,1,1,1}, {0,1,1,-1,1,0},
    {-1,0,0,-1,0,-2}, {-1,0,-2,0,0,1}, {0,1,0,2,1,0}, {0,-1,1,0,2,0},
    {0,1,1,0,1,1}, {0,-1,1,0,1,-1}, {-1,0,0,-1,-1,-1}, {-1,0,-1,1,0,1},
    {0,1,0,2,0,3}, {1,0,2,0,3,0}, {0,-1,0,-2,0,-3}, {-1,0,-2,0,-3,0}
};
/****************************************************************/
int cas = 0;	//表示第一关
int P_Box[2] = {3,4};
void P_Paint()
{
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 16; j++){
			if (j == 0) printf("\t\t");
			switch (P_Map[cas][i][j])
			{
			case 0:
				printf("  ");  //路 
				break;
			case 1:
				printf("■");  //墙 
				break;
			case 3:
				printf("☆");  //底座  
				break;
			case 4:
				printf("★");  //箱子 
				break;
			case 5:
			case 8:
				printf("●");  //人 
				break;
			case 7:
				printf("※");  //箱子与底座重合 
				break;
			}
		}
		printf("\n");
	}
}
/****************************************************************/
void P_Game()
{
	int i, j;
	for (i = 0; i < 16; i++){
		for (j = 0; j < 16; j++){
			if (P_Map[cas][i][j] == 5 || P_Map[cas][i][j] == 8) break;
		}
		if (P_Map[cas][i][j] == 5 || P_Map[cas][i][j] == 8)	break;
	}
	char k = getch();
	switch (k)
	{
	case 'w':
	case 'W':
	case 72:
		if (P_Map[cas][i - 1][j]   == 0 || P_Map[cas][i - 1][j] == 3){   //3+5=8 ：表示目的和人在一起	
			P_Map[cas][i - 1][j] += 5;  //目标位置(map[i-1][j])人（5）来了	
			P_Map[cas][i][j] -= 5;     //现在位置(map[i][j])人（5）走了
		}
		else if (P_Map[cas][i - 1][j] == 4 || P_Map[cas][i - 1][j] == 7){
			if (P_Map[cas][i - 2][j] == 0 || P_Map[cas][i - 2][j] == 3){
				P_Map[cas][i - 2][j] += 4;	
				P_Map[cas][i - 1][j] += 1;  //箱子位置：箱子（-4）走了，人来（+5）				
				P_Map[cas][i][j] -= 5;  //现在位置人走了
			}
		} 
	break;
	case 's':
	case 'S':
	case 80:
		if (P_Map[cas][i + 1][j] == 0 || P_Map[cas][i + 1][j] == 3){
			P_Map[cas][i + 1][j] += 5;
			P_Map[cas][i][j] -= 5;
		}
		else if (P_Map[cas][i + 1][j] == 4 || P_Map[cas][i + 1][j] == 7){
			if (P_Map[cas][i + 2][j] == 0 || P_Map[cas][i + 2][j] == 3){
				P_Map[cas][i + 2][j] += 4;
				P_Map[cas][i + 1][j] += 1;
				P_Map[cas][i][j] -= 5;
			}
		}
	break;
	case 'a':
	case 'A':
	case 75:
		if (P_Map[cas][i][j - 1] == 0 || P_Map[cas][i][j - 1] == 3){
			P_Map[cas][i][j - 1] = P_Map[cas][i][j - 1] + 5;
			P_Map[cas][i][j] = P_Map[cas][i][j] - 5; 
		}
		else if (P_Map[cas][i][j - 1] == 4 || P_Map[cas][i][j - 1] == 7){
			if (P_Map[cas][i][j - 2] == 0 || P_Map[cas][i][j - 2] == 3){
				P_Map[cas][i][j - 2] += 4;
				P_Map[cas][i][j - 1] += 1;
				P_Map[cas][i][j] -= 5;
			}
		}
	break;
	case 'D':
	case 'd':
	case 77:
		if (P_Map[cas][i][j + 1] == 0 || P_Map[cas][i][j + 1] == 3){
			P_Map[cas][i][j + 1] += 5;
			P_Map[cas][i][j] -= 5;
		}
		else if (P_Map[cas][i][j + 1] == 4 || P_Map[cas][i][j + 1] == 7){
			if (P_Map[cas][i][j + 2] == 0 || P_Map[cas][i][j + 2] == 3){
				P_Map[cas][i][j + 2] += 4;
				P_Map[cas][i][j + 1] += 1;
				P_Map[cas][i][j] -= 5;
			}
		}
	break;
	}
}/****************************************************************/
int P_GameOver()  //结束判断
{
	int count = 0;	
	for (int i = 0; i < 16; i++){  //遍历地图	
		for (int j = 0; j < 16; j++){
			if (P_Map[cas][i][j] == 7)
				count++;
		}
	}
	return count;
}
int P_gameOver2()  //没箱子时结束游戏 
{
	int count = 3;
	
	for (int i = 0; i < 16; i++){  //遍历地图 
		for (int j = 0; j < 16; j++){		
			if (P_Map[cas][i][j] == 3)
				count--;
		}
	}
	return count;
}
/****************************************************************/
void M_Create(int x,int y)  //建立随机迷宫 
{
	int c[4][2]={1,0,0,-1,-1,0,0,1};  //建立坐标系 
	int i,j,t;
	for(i=0;i<4;i++){
		j=rand()%4;
		t=c[i][0];c[i][0]=c[j][0];c[j][0]=t;
		t=c[i][1];c[i][1]=c[j][1];c[j][1]=t;
	}   //打乱方向 
	M_Map[x][y]=Road;  
	for(i=0;i<4;i++){
		if(M_Map[x+2*c[i][0]][y+2*c[i][1]] == Wall){
			M_Map[x+c[i][0]][y+c[i][1]]=Road;
			M_Create(x+2*c[i][0],y+2*c[i][1]);
		}
	}
}
void M_Paint(int x,int y)  //画出迷宫 
{
	gotoxy(2*y-2,x-1);
	switch(M_Map[x][y])
	{
		case Start:
			printf("◆");break;  //入口
		case End:
			printf("★");break;  //出口
		case Road:
			printf("  ");break;  //通道
		case Wall:
			printf("▉");break;  //墙壁	 
	}
} 
/****************************************************************/
int M_Key()  //接收按键 
{
	char k;
	while(k=getch()){
		if(k == 27) return Esc;   //Esc
		if(k==87||k==72||k==119) return Up;   //上
		if(k==83||k==80||k==115) return Down;   //下 
		if(k==65||k==75||k==97) return Left;   //左 
		if(k==68||k==77||k==100) return Right;   //右 
	}
}
/****************************************************************/
void M_Game()
{
	int x=2,y=1;   //玩家出生点 
	int k;   //接受按键 
	while(1){
		gotoxy(2*y-2,x-1);
		printf("●");
		 if(M_Map[x][y]==End){    //判断是否到达出口 
		 	printf("恭喜您通关啦！");
		 	getch();
		 	break;
		}
		k=M_Key();
		if(k==Esc){
		 	break;
		}
		switch(k)   //玩家行动 
		{
			case Up:
				if(M_Map[x-1][y] != Wall){
					M_Paint(x,y);
					x--;
				} 
			break;
			case Down:
				if(M_Map[x+1][y] != Wall){
					M_Paint(x,y);
					x++;
				}
			break;
			case Left:
				if(M_Map[x][y-1] != Wall){
					M_Paint(x,y);
					y--;
				}
			break;
			case Right:
				if(M_Map[x][y+1] != Wall){
					M_Paint(x,y);
					y++; 
				}
			break; 
		} 
	}
}
/****************************************************************/
void M_Zero()    //初始化 
{
	int i,j;
	srand((unsigned)time(NULL));   //初始化随机种子 
	hidden();
	for(i=0;i<Height+1;i++){
		for(j=0;j<Width+1;j++){    //初始化迷宫 
			if(i==0||i==Height+1||j==0||j==Width+1)  M_Map[i][j]=Road;
			else  M_Map[i][j]=Wall;
	   	}
	}
	M_Create(2*(rand()%(Height/2)+1),2*(rand()%(Width/2)+1));   //确定边界 
	M_Map[2][1]=Start;  //确定入口 
    M_Map[Height-1][Width]=End;   //确定出口 
    for(i=1;i<=Height;i++){
    	for(j=1;j<=Width;j++){
    		M_Paint(i,j);   //画出迷宫 
    	}
    }
}
/****************************************************************/
typedef struct Snakes
{
	int x;
	int y;
	struct Snakes *next;    
}snake;
snake *head,*tail;
struct Food
{
	int x;
	int y;
}food;
/****************************************************************/
void S_Wall(int x, int y)
{
	gotoxy(x, y);
	printf("■");
}
void S_Body(int x, int y)
{
	gotoxy(x, y);
	printf("●");
}
void S_Space(int x, int y)
{
	gotoxy(x, y);
	printf("  ");
}
/****************************************************************/
void S_Create()             
{
	gotoxy(64,8);
	printf("得分：%d  ",score);
	int i;   //建立围墙 
	for (i = 0; i<58; i += 2){	
		S_Wall(i, 0);
		S_Wall(i, 26);
	}
	for (i = 1; i < 26; i++){
		S_Wall(0, i);
		S_Wall(56, i);
	}
	head = (snake*)malloc(sizeof(snake));    //创造蛇 
	head->x = 16;
	head->y = 15;
	tail = (snake*)malloc(sizeof(snake));
	snake *p = (snake*)malloc(sizeof(snake));
	snake *q = (snake*)malloc(sizeof(snake));
	p->x = 16;
	p->y = 16;
	q->x = 16;
	q->y = 17;
	head->next = p;
	p->next = q;
	q->next = tail;
	tail->next = NULL;
	tail->x = 4;
	tail->y = 2;	
}
/****************************************************************/
void S_Apple()  //创造食物 
{
	srand((int)time(NULL));
	Createfood:
	food.y = rand() % (25) + 1;
	food.x = rand() % (54) + 2;
	if (food.x % 2 != 0){
		food.x = food.x+1;
	}
	snake *judge = head;
	while (1){     //遍历排除蛇身重复
		if (judge->next == NULL) break;
		if (food.x == judge->x&&food.y == judge->y){
			goto Createfood;
		}
		judge = judge->next;
	}
	gotoxy(food.x, food.y);
	printf("★");
}
/****************************************************************/
int S_Judge()  //判断死亡条件 
{
	if (head->x == 0|| head->x == 56 || head->y == 0 || head->y == 26)	return 0;
	snake *p = head->next;
	while (1){
		if (p->next == NULL) break;
		if (head->x == p->x&&head->y == p->y){
			return 0;
		}
		p = p->next;
	}
	return 1;
}
/****************************************************************/
void S_ChangeBody(int a,int b)
{
	snake *p = head->next;
	int mid1, mid2,mid_1,mid_2;
	mid1 = p->x;
	mid2 = p->y;
	while (1){
		if (p->next->next == NULL) break;
		mid_1 = p->next->x;
		mid_2 = p->next->y;
		p->next->x = mid1;
		p->next->y = mid2;
		mid1 = mid_1;
		mid2 = mid_2; 
		p = p->next;
	}
	p = head->next;
	if (p->next!= NULL){
		p->x = a;
		p->y = b;
	}
}
void S_MovingBody()
{
	int count = 0;
	int speed;
	int k;
	int a = head->x, b = head->y;
	snake *p = head;
	while (1){
		if (p->next == NULL) break;
		S_Space(p->x, p->y);
		count++;
		p = p->next;
	}	
	switch (click)
	{
		case up:
			head->y -= 1;
			S_ChangeBody(a,b);
			break;
		case down:
			head->y += 1;
			S_ChangeBody(a,b);
			break;
		case left:
			head->x -= 2;
			S_ChangeBody(a,b);
			break;
		case right:
			head->x += 2;
			S_ChangeBody(a,b);
			break;
	}
	p = head;
	while (1){
		if (p->next == NULL) break;
		S_Body(p->x, p->y);
		p = p->next;
	}
	p = head;
	gotoxy(0, 28);
	if (count <= 10) speed = 200;    //调节速度 
	else if (count > 10 && count <= 20) speed = 150;
	else if (count > 20 && count <= 40) speed = 100;
	else speed = 50;
	Sleep(speed);
}
/****************************************************************/
void S_Eating()
{
	if (head->x == food.x&&head->y == food.y){
		S_Apple();
		snake *_new = (snake*)malloc(sizeof(snake));
		snake *p;
		p = head;
		score++;
		gotoxy(64,8);
	printf("得分：%d  ",score);
		while (1){
			if (p->next->next == NULL) break;
			p = p->next;
		}
		p->next = _new;
		_new->next = tail;
	}
}
/****************************************************************/
int S_ClickControl()
{
	char c;
	while (1){
		if (S_Judge()==0) return 0;
		if (_kbhit()){  //接收按键 
			click = _getch();
		}
		S_MovingBody();
		S_Eating();
	}
	return 1;
}
/****************************************************************/
void R_Gameover()  //死亡判断 
{
    int i,j,flag=0;
    for(j=1;j<R_Y-1;j++){
        if(R_Map[1][j]!=0){
            flag=1;break;
        }
    }
    if(flag==1){
        for(i=1;i<R_X-1;i++){
            gotoxy(2,i+1);
            for(j=1;j<R_Y-1;j++){
                printf("□");
            }
			puts("");
        }
        gotoxy(7,9);
        printf("GAME OVER!");
        gotoxy(1,R_X+1);
        exit(0);
    }
}
/****************************************************************/
void R_Paint(int id)  //画出地图 
{
    int i,j;
    gotoxy(1,1);
    if(id!=-1){
    for(i=0;i<R_X;i++){
       for(j=0;j<R_Y;j++){
            if(i==0&&j==0 || i==0&&j==R_Y-1 || j==0&&i==R_X-1 || j==R_Y-1&&i==R_X-1) printf("●");
            else if(i==0 || i==R_X-1) printf("●");  //画墙 
            else if(j==0 || j==R_Y-1) printf("●");
            else if(R_Map[i][j]==2) printf("■");   
            else if(i==x+R_Shape[id][0] && j==y+R_Shape[id][1] ||
                    i==x+R_Shape[id][2] && j==y+R_Shape[id][3] ||
                    i==x+R_Shape[id][4] && j==y+R_Shape[id][5] ||
                    i==x && j==y)
            	printf("■");  //画方块
            else if(R_Map[i][j]==0) printf("  ");        
        	}
        if(i==1) printf("   下一个 :");
        if(i==11) printf("   等分 :   %d",R_score);
        puts("");
    	}
    }
    else {
        mark=1;
        for(i=0;i<R_X;i++){
            for(j=0;j<R_Y;j++){
            	if(i==0&&j==0 || i==0&&j==R_Y-1 || j==0&&i==R_X-1 || j==R_Y-1&&i==R_X-1) printf("●");
            	else if(i==0 || i==R_X-1) printf("●");
            	else if(j==0 || j==R_Y-1) printf("●");
            	else if(R_Map[i][j]==2) printf("■");
            	else if(R_Map[i][j]==0) printf("  ");      
            }
            if(i==11)printf("   score :   %d",R_score);
            puts("");
    }
}  
    gotoxy(30,6);
    printf("  ");
    for(i=0;i<6;i=i+2){
        gotoxy(30+2*R_Shape[id][i+1],6+R_Shape[id][i]); 
		printf("  ");
    }
    gotoxy(30,6); 
	printf("■");
    for(i=0;i<6;i=i+2){
        gotoxy(30+2*R_Shape[next][i+1],6+R_Shape[next][i]); 
		printf("■");
        }
    Sleep(R_GameSpeed);
}
/****************************************************************/
void R_Clear(int id){   //消除方块
    int i,j;
    memset(R_Map,0,sizeof(R_Map));
    for(i=0;i<R_X;i++){
    	for(j=0;j<R_Y;j++){
        	if(i==R_X-1 || j==0 || j==R_Y-1) R_Map[i][j]=-1;
        }
	}
    x=0;y=5;
    R_Paint(id);
}
/****************************************************************/ 
int R_Judge(int x,int y,int id){
    int i;
    if(R_Map[x][y]!=0)return 0;
    for(i=0;i<6;i=i+2){
        if(R_Map[ x+R_Shape[id][i] ][ y+R_Shape[id][i+1] ]!=0) return 0;
    }
	return 1;
}
/****************************************************************/
void R_Score(){  //记录分数 
    int i,j,ii,jj;
    for(i=1;i<R_X-1;i++){
        int flag=0;
        for(j=1;j<R_Y-1;j++){
            if(R_Map[i][j]!=2){ 
				flag=1;
				break; 
			}
        }
        if(flag==0){
            int k=3;
            while(k--){
                gotoxy(2,i+1);
                for(ii=1;ii<R_Y-1;ii++){
                    if(R_Map[i][ii]==2){
                    	if(k%2==1) printf("  ");
                    	else printf("■");
                    }
                }
				Sleep(100);
            }
            for(ii=i;ii>1;ii--){
            	for(jj=1;jj<R_Y-1;jj++) 
				R_Map[ii][jj]=R_Map[ii-1][jj];
            }
            R_Paint(-1);
            R_score++;
            if(R_score%100==0 && R_score!=0)R_GameSpeed-=50;  //控制速度 
        }
    }
}
/****************************************************************/
char X_schoolwork[SWN][NAMELEN+1] = {"语文","数学","英语"};// 课程名称表 
struct record
{
	char	name[NAMELEN+1];	// 姓名 
	char 	code[CODELEN+1];	// 学号 
	int 	marks[SWN];		// 各课程成绩 
	int total;			// 总分 
}stu;
struct node
{
	char	name[NAMELEN+1];	// 姓名 
	char 	code[CODELEN+1];	// 学号 
	int 	marks[SWN];		// 各课程成绩 
	int 	total;			// 总分 
	struct	node *next;	
}*X_head;
/****************************************************************/	
int X_Total[SWN];		// 各课程总分 
FILE *stfpt;		// 文件指针 
char stuf[FNAMELEN];	// 文件名 
int X_ReadRecord(FILE *fpt,struct record *rpt)// 从指定文件读入一个记录 
{
	char buf[BUFLEN];
	int i;
	if(fscanf(fpt,"%s",buf)!=1)
		return 0;	// 文件结束 
	strncpy(rpt->name,buf,NAMELEN);
	fscanf(fpt,"%s",buf);
	strncpy(rpt->code,buf,CODELEN);
	for(i=0;i<SWN;i++)
		fscanf(fpt,"%d",&rpt->marks[i]);
	for(rpt->total=0,i=0;i<SWN;i++)
		rpt->total+=rpt->marks[i];
	return 1;
}
/****************************************************************/
void X_WriteRecord(FILE *fpt,struct record *rpt)// 对指定文件写入记录 
{
	int i;
	fprintf(fpt,"%s\n",rpt->name);
	fprintf(fpt,"%s\n",rpt->code);
	for(i=0;i<SWN;i++)
		fprintf(fpt,"%d\n",rpt->marks[i]);

}
/****************************************************************/
void X_Displaystu(struct record *rpt)// 显示学生记录 
{
	int i;
	printf("\n姓名   : %s\n",rpt->name);
	printf("学号   : %s\n",rpt->code);
	printf("标记  :\n");
	for(i=0;i<SWN;i++)
		printf("       %-15s : %4d\n",X_schoolwork[i],rpt->marks[i]);
	printf("总分  : %4d\n",rpt->total);
}
int X_TotalMark(char *fname)// 计算各单科总分
{
	FILE *fp;
	struct record s;
	int count,i;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("无法打开文件 %s.\n",fname);
		return 0;
	}
	for(i=0;i<SWN;i++)
		X_Total[i]=0;
	count=0;
	while(X_ReadRecord(fp,&s)!=0)
	{
		for(i=0;i<SWN;i++)
			X_Total[i]+=s.marks[i];
		count++;
	}
	fclose(fp);
	return count;	// 返回记录数 
}
void X_Liststu(char *fname)// 列表显示学生信息 
{
	FILE *fp;
	struct record s;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("无法打开文件 %s.\n",fname);
		return ;
	}
	while(X_ReadRecord(fp,&s)!=0)
	{
		X_Displaystu(&s);
		printf("\n      请按回车键继续…\n");
		while(getchar()!='\n');
	}
	fclose(fp);
	return;
}
/****************************************************************/
struct node *makelist(char *fname)// 构造链表 
{
	FILE *fp;
	struct record s;
	struct node *p,*u,*v,*h;
	int i;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("无法打开文件 %s.\n",fname);
		return NULL;
	}
	h=NULL;
	p=(struct node *)malloc(sizeof(struct node));
	while(X_ReadRecord(fp,(struct record *)p)!=0)
	{
		v=h;
		while(v&&p->total<=v->total)
		{
			u=v;
			v=v->next;
		}
		if(v==h)
			h=p;
		else
			u->next=p;
		p->next=v;
		p=(struct node *)malloc(sizeof(struct node));
	}
	free(p);
	fclose(fp);
	return h;
}
void X_DisplayList(struct node *h)// 顺序显示链表
{
	while(h!=NULL)
	{
		X_Displaystu((struct record *)h);
		printf("\n      请按回车键继续…\n");
		while(getchar()!='\n');
		h=h->next;
	}
	return;
}
/****************************************************************/
int X_Retrievebyn(char *fname, char *key)// 按学生姓名查找学生记录 
{
	FILE *fp;
	int c;
	struct record s;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("无法打开文件 %s.\n",fname);
		return 0;
	}
	c=0;
	while(X_ReadRecord(fp,&s)!=0)
	{
		if(strcmp(s.name,key)==0)
		{
			X_Displaystu(&s);
			c++;
		}
	}
	fclose(fp);
	if(c==0)
		printf("该学生 %s 不在文件内 %s.\n",key,fname);
	return 1;
}
int X_Retrievebyc(char *fname, char *key)// 按学生学号查找学生记录 
{
	FILE *fp;
	int c;
	struct record s;
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("无法打开文件 %s.\n",fname);
		return 0;
	}
	c=0;
	while(X_ReadRecord(fp,&s)!=0)
	{
		if(strcmp(s.code,key)==0)
		{
			X_Displaystu(&s);
			c++;
			break;
		}
	}
	fclose(fp);
	if(c==0)
		printf("该学生 %s 不在文件内 %s.\n",key,fname);
	return 1;
}
/****************************************************************/
void TuiXiangZi()
{
	while (1){
		printf("\n\n\t\t   第【%d】关\n",cas+1);
		P_Paint();
		if (P_GameOver() == P_Box[cas])
		{
			system("pause");
			cas++;
			if (cas == 5) break;
		}
		P_Game();
		system("cls");
	}
	printf("恭喜您通关了！");
}
/****************************************************************/
void MiGong()
{
	while(1){
    M_Zero();
    M_Game();
    int k=M_Key();
	if(k==Esc){
		break;
	}
	system("cls");
	}
}
/****************************************************************/
void TanChiShe()
{
	S_Create();
	S_Apple();
	if (S_ClickControl() == 0){ 
		printf("很遗憾您死了！");
	}
}
/****************************************************************/
void FangKuai(){
    int i,id,set=1;    
    srand(time(NULL));
    id=rand()%MOD; 
	id=(id+MOD)%MOD;
    next=rand()%MOD; 
	next=(next+MOD)%MOD;      
    R_Clear(id);        
    while(1){
		Here:mark=0;
        if(set==0){
            id=next;
            next=rand()%MOD; 
			next=(next+MOD)%MOD;
            x=0;y=5;
            set=1;
        }              
        while(!kbhit()){
            R_Gameover();
            if(R_Judge(x+1,y,id)==1) x++;
            else {
                R_Map[x][y]=2;
                for(i=0;i<6;i=i+2)
                    R_Map[x+R_Shape[id][i]][y+R_Shape[id][i+1]]=2;
                    R_Score();
                    set=0;
            }
            if(mark!=1) R_Paint(id);
            goto Here;
        }             
    char key;
    key=getch();                 
    if(key==72){
        int tmp=id;
        id++;
        if( id%4==0 && id!=0 )id=id-4;
        if(R_Judge(x,y,id)!=1)id=tmp;
    }
        else if(key==80 && R_Judge(x+1,y,id)==1) x++;
        else if(key==75 && R_Judge(x,y-1,id)==1) y--;
        else if(key==77 && R_Judge(x,+1,id)==1) y++;
        else if(key==27){
			gotoxy(1,R_X+1);
			exit(0);
		}
    }
    getch();
}
/****************************************************************/
void XiTong()
{
	int i,j,n;
	char c;
	char buf[BUFLEN];
	FILE *fp;
	struct record s;
	system("cls");
	printf("请输入学生分数记录档案名称: ");
	scanf("%s",stuf);
	if((fp=fopen(stuf,"r"))==NULL)
	{
		printf("文件 %s 不存在，要创建它吗? (Y/N) ",stuf);
		getchar();
		c=getchar();
		if(c=='Y'||c=='y')
		{
			fp=fopen(stuf,"w");
			printf("请输入您想储存的学生数量: ");
			scanf("%d",&n);
			for(i=0;i<n;i++)
			{
				printf("输入学生姓名: ");
				scanf("%s",&s.name);
				printf("输入学生学号： ");
				scanf("%s",&s.code);
				for(j=0;j<SWN;j++)
				{
					printf("输入%s成绩: ",X_schoolwork[j]);
					scanf("%d",&s.marks[j]);
				}
				X_WriteRecord(fp,&s);
			}
			fclose(fp);
		}
	}
	fclose(fp);
	getchar();
	/*clrscr();*/
	puts("现在您可以输入一个命令来管理这些记录。");
	puts("m : 平均分数");
	puts("t : 总分");
	puts("n : 按学生姓名搜索记录");
	puts("c : 根据学生学号搜索记录");
	puts("l : 按学号排列显示");
	puts("s : 按总分从高到低排列显示。");
	puts("q : 使用完毕");
	while(1)
	{
		puts("请输入命令:");
		scanf(" %c",&c);		//输入选择命令 
		if(c=='q'||c=='Q')
		{
			puts("\n 谢谢您的使用！");
			break;		// q，结束程序运行 
		}
		switch(c)
		{
			case 'm': // 计算平均分 
			case 'M':
				if((n=X_TotalMark(stuf))==0)
				{
					puts("错误！");
					break;
				}
				printf("\n");
				for(i=0;i<SWN;i++)
					printf("%s平均分: %.2f.\n",X_schoolwork[i],(float)X_Total[i]/n);
				break;
			case 't': // 计算总分 
			case 'T':
				if((n=X_TotalMark(stuf))==0)
				{
					puts("错误！");
					break;
				}
				printf("\n");
				for(i=0;i<SWN;i++)
					printf("%s总分: %d.\n",X_schoolwork[i],X_Total[i]);
				break;
			case 'n': // 按学生的姓名寻找记录 
			case 'N':
				printf("请输入您想查询的学生姓名: ");	
				scanf("%s",buf);
				X_Retrievebyn(stuf,buf);
				break;
			case 'c': // 按学生的学号寻找记录 
			case 'C':
				printf("请输入您想查询的学生学号: ");	
				scanf("%s",buf);
				X_Retrievebyc(stuf,buf);
				break;
			case 'l': // 列出所有学生记录 
			case 'L':
				X_Liststu(stuf);
				break;
			case 's': // 按总分从高到低排列显示 
			case 'S':
				if((X_head=makelist(stuf))!=NULL)
					X_DisplayList(X_head);
				break;
			default: break;
		}
	}
}
/****************************************************************/
int main()
{
	char s;
	system("color 0D");
	gotoxy(32,8);
		printf("期 末 作 业");
	gotoxy(32,32);	
	system("pause");
	system("cls");
	
	gotoxy(32,4);
		printf("游戏目录"); 
	gotoxy(32,8);
		printf("A.迷宫"); 
	gotoxy(32,10);
		printf("B.贪吃蛇");
	gotoxy(32,12);
		printf("C.推箱子");
	gotoxy(32,14);
		printf("D.俄罗斯方块");
	gotoxy(32,16);
		printf("E.学籍管理系统");
	gotoxy(32,20);
		printf("G.休息一下"); 
	while(1){
		gotoxy(32,28);
		printf("请选择您想玩的游戏：");	
		scanf(" %c",&s);
		system("cls");
		if(s=='a'||s=='A'){
			MiGong();
		}
		if(s=='b'||s=='B'){
			TanChiShe();
		}
		if(s=='c'||s=='C'){
			TuiXiangZi();
		}
		if(s=='d'||s=='D'){
			FangKuai();
		}
		if(s=='e'||s=='E'){
			XiTong();
		}
		if(s=='g'||s=='G'){
			gotoxy(32,8);
			printf("感谢您的游玩！");
			gotoxy(32,32);	
			system("pause");
			break;
			return 0; 
		} 
	}
}
