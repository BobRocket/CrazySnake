#include <graphics.h>
#include <stdio.h>
#define MAX 500

//struct
struct Snake
{
	int x[MAX],y[MAX];
	int speed,node,dir,life;
	color_t color;
}snake;
struct Bean
{
	int x,y;
	int visable;
	int num;
	color_t color;
}bean;
struct Brick
{
	int x,y;
}brick[MAX];
struct data
{
	int level;
	int score;
	color_t levelColor1,levelColor2;
	int bricknum,beannum;
	char life[20];
	char score1[20];
	char win[20];
	int barwidth;
}data;       


void drawbrick(int x,int y)
{
	setcolor(WHITE);
	line(x,y,x+9,y);
	line(x,y+9,x+8,y+1);
	line(x,y,x,y+9);
	line(x+1,y,x+1,y+8);
	setcolor(data.levelColor1);
	line(x+1,y+9,x+9,y+9);
	line(x+2,y+8,x+9,y+8);
	line(x+8,y+2,x+9,y+9);
	line(x+9,y+1,x+9,y+9);
	setfillcolor(data.levelColor2);
	bar(x+2,y+2,x+7,y+7);
}

void drawsnake()
{
	setcolor(snake.color);
	setlinestyle(0,0,3);
	for(int i=0;i<snake.node;i++)
	{
		rectangle(snake.x[i],snake.y[i],snake.x[i]+9,snake.y[i]+9);
	}
	delay(snake.speed);
	setcolor(BLACK);
	rectangle(snake.x[snake.node-1],snake.y[snake.node-1],snake.x[snake.node-1]+9,snake.y[snake.node-1]+9);
}

void setsnake()
{
	for(int i=snake.node-1;i>0;i--)
	{
		snake.x[i]=snake.x[i-1];
		snake.y[i]=snake.y[i-1];
	}
	switch(snake.dir)
	{
		case 1: snake.x[0]+=10;break;
		case 2: snake.x[0]-=10;break;
		case 3: snake.y[0]-=10;break;
		case 4: snake.y[0]+=10;break;
	}
}

void snakectrl()
{
	if(keystate(VK_RIGHT)&&snake.dir!=2)	
		snake.dir=1;
	if(keystate(VK_LEFT)&&snake.dir!=1)
		snake.dir=2;
	if(keystate(VK_UP)&&snake.dir!=4)
		snake.dir=3;
	if(keystate(VK_DOWN)&&snake.dir!=3)
		snake.dir=4;		
}

void snakeEatBean()
{
	if(snake.x[0]==bean.x&&snake.y[0]==bean.y)
	{
		snake.node++;
		bean.visable=0;
		data.score+=10;
		data.barwidth+=10;
		if(data.score==50)
		{
			snake.life++;
			data.score=0;
		}
		data.beannum++;
	}
}

void snakeEatItself()
{
	for(int i=3;i<snake.node;i++)
	{
		if(snake.x[i]==snake.x[0]&&snake.y[i]==snake.y[0]&&snake.life!=0)
		{
			snake.life-=1;
			snake.x[0]=40;
			snake.y[0]=70;
			snake.dir=1;
		}
	}
}

void crash()
{
	if(snake.x[0]<40||snake.x[0]>759||snake.y[0]<70||snake.y[0]>559)
	{
		snake.life-=1;
		snake.x[0]=40;
		snake.y[0]=70;
		snake.dir=1;
	}
	for(int i=0;i<data.bricknum;i++)
	{
		if(snake.x[0]==brick[i].x&&snake.y[0]==brick[i].y)
		{
			snake.life-=1;
			snake.x[0]=40;
			snake.y[0]=70;
			snake.dir=1;
		}
		
	}
}

void drawlife()
{
	for(int i=0;i<snake.life;i++)
	{
		setcolor(RED);
		circle(100+15*i,17,5);
	}
}

void drawbean()
{
	if(bean.visable==1)
	{
		setcolor(bean.color);
		setlinewidth(3);
		rectangle(bean.x,bean.y,bean.x+9,bean.y+9);
		setcolor(BLACK);
		rectangle(bean.x,bean.y,bean.x+2,bean.y+2);
		rectangle(bean.x+7,bean.y,bean.x+9,bean.y+2);
		rectangle(bean.x+7,bean.y+7,bean.x+9,bean.y+9);
		rectangle(bean.x,bean.y+7,bean.x+2,bean.y+9);	
	}	
}
void drawgame()
{
	setcolor(YELLOW);
	setfillcolor(RED);
	setfont(20,10,"Small Fonts");
	sprintf(data.life,"LIFE:%d",snake.life);
	sprintf(data.score1,"SCORE:%d",data.score);
	xyprintf(30,5,data.life);
	xyprintf(400,5,data.score1);
	rectangle(600,10,750,20);
	bar(602,12,600+data.score*3,18);
	setcolor(LIGHTBLUE);
	setfillcolor(GREEN);
	rectangle(600,30,750,40);
	bar(602,32,600+data.beannum*30,38);
}
void drawlevel()
{
	for(int i=30;i<770;i+=10)
	{
		drawbrick(i,60);
		drawbrick(i,560);
	}
	for(int i=70;i<560;i+=10)
	{
		drawbrick(30,i);
		drawbrick(770,i);
	}
		switch(data.level)
	{
		case 1:
			data.levelColor1=RED;
			data.levelColor2=0xff8989;
			for(int i=0;i<56;i++)
			{
				brick[i].x=i*10+120;
				brick[i].y=300;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=56;i<112;i++)
			{
				brick[i].x=i*10+120-560;
				brick[i].y=310;
				drawbrick(brick[i].x,brick[i].y);
			}
			data.bricknum=112;
			break;
			
		case 2: 
			data.levelColor1=0xff8900;
			data.levelColor2=0Xf0c189;
			for(int i=0;i<56;i++)
			{
				brick[i].x=i*10+120;
				brick[i].y=220;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=56;i<112;i++)
			{
				brick[i].x=i*10+120-560;
				brick[i].y=400;
				drawbrick(brick[i].x,brick[i].y);
			}
			data.bricknum=112;
			break;
			
		case 3:
			data.levelColor1=GREEN;
			data.levelColor2=0X9dff9d;
			for(int i=0;i<30;i++)
			{
				brick[i].x=190;
				brick[i].y=i*10+160;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=30;i<60;i++)
			{
				brick[i].x=400;
				brick[i].y=i*10+160-300;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=60;i<90;i++)
			{
				brick[i].x=600;
				brick[i].y=i*10+160-600;
				drawbrick(brick[i].x,brick[i].y);
			}
			data.bricknum=90;
			break;
			
		case 4: 
			data.levelColor1=BLUE;
			data.levelColor2=LIGHTBLUE;
			for(int i=0;i<48;i++)
			{
				brick[i].x=i*10+160;
				brick[i].y=200;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=48;i<96;i++)
			{
				brick[i].x=i*10+160-480;
				brick[i].y=420;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=96;i<115;i++)
			{
				brick[i].x=120;
				brick[i].y=i*10+220-960;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=115;i<134;i++)
			{
				brick[i].x=670;
				brick[i].y=i*10+220-1150;
				drawbrick(brick[i].x,brick[i].y);
			}
			data.bricknum=134;
			break;
			
		case 5: 
			data.levelColor1=RED;
			data.levelColor2=YELLOW;
			for(int i=0;i<48;i++)
			{
				brick[i].x=i*10+160;
				brick[i].y=200;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=48;i<96;i++)
			{
				brick[i].x=i*10+160-480;
				brick[i].y=310;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=96;i<144;i++)
			{
				brick[i].x=i*10+160-960;
				brick[i].y=420;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=144;i<163;i++)
			{
				brick[i].x=120;
				brick[i].y=i*10+220-1440;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=163;i<182;i++)
			{
				brick[i].x=670;
				brick[i].y=i*10+220-1630;
				drawbrick(brick[i].x,brick[i].y);
			}
			data.bricknum=182;
			break;
			
		case 6: 
			data.levelColor1=MAGENTA;
			data.levelColor2=LIGHTMAGENTA;
			for(int i=0;i<48;i++)
			{
				brick[i].x=i*10+160;
				brick[i].y=200;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=48;i<96;i++)
			{
				brick[i].x=i*10+160-480;
				brick[i].y=270;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=96;i<144;i++)
			{
				brick[i].x=i*10+160-960;
				brick[i].y=350;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=144;i<192;i++)
			{
				brick[i].x=i*10+160-1440;
				brick[i].y=420;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=192;i<211;i++)
			{
				brick[i].x=120;
				brick[i].y=i*10+220-1920;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=211;i<230;i++)
			{
				brick[i].x=670;
				brick[i].y=i*10+220-2110;
				drawbrick(brick[i].x,brick[i].y);
			}
			data.bricknum=230;
			break;
			
		case 7: 
			data.levelColor1=CYAN;
			data.levelColor2=LIGHTCYAN;
			for(int i=0;i<56;i++)
			{
				brick[i].x=i*10+120;
				brick[i].y=300;
				drawbrick(brick[i].x,brick[i].y);
			}
			for(int i=56;i<96;i++)
			{
				brick[i].x=400;
				brick[i].y=i*10+120-560;
				drawbrick(brick[i].x,brick[i].y);
			}
			data.bricknum=96;
			break;
		
	}
}
void setnewbean()
{
	int ok=1;
	if(bean.visable==0)
	{
		bean.x=random(55)*10+40;
		bean.y=random(37)*10+70;
		for(int i=0;i<data.bricknum;i++)
		{
			if(bean.x==brick[i].x&&bean.y==brick[i].y)
				ok=0;
		}
		if(ok==1)
			bean.visable=1;
	}		
}

void setfirstbean()
{
	int ok=1;
	while(ok==1)
	{
		bean.x=random(55)*10+40;
		bean.y=random(37)*10+70;
		for(int i=0;i<data.bricknum;i++)
		{
			if(bean.x==brick[i].x&&bean.y==brick[i].y)
				ok=0;
		}
		if(ok==1)
		{
			bean.visable=1;	
			break;
		}	
	}		
}


void initgame()
{
	data.score=0;
	data.level=1;
	data.barwidth=0;
	snake.node=5;
	snake.speed=20;
	snake.dir=1;
	snake.x[0]=40;
	snake.y[0]=70;
	snake.life=5;
	snake.color=GREEN;
	bean.color=YELLOW;
	bean.visable=0;
	setnewbean();
}

void mainLoop()
{
	initgame();
	for(;is_run();delay_fps(60))
	{
		
		cleardevice();
		
		drawsnake();
		drawlife();
		drawlevel();
		drawbean();
		drawgame();
		
		setsnake();
		setnewbean();
		snakeEatBean();
		snakeEatItself();
		snakectrl();
		crash();
		if(data.beannum==5)
		{
			data.level++;
			snake.dir=1;
			snake.x[0]=40;
			snake.y[0]=70;
			data.beannum=0;
		}
		if(data.level==8)
		{
			data.level=1;
			snake.speed-=10;
		}
		if(snake.life<0)break;
	}
}
//main
int main()
{
	setinitmode(INIT_ANIMATION);
	initgraph(800,600);
	randomize();
	mainLoop();
	closegraph();
	return 0;
}
