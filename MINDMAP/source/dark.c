#include"MAINHEAD.h"

int darkInterFace(BOX*h, long start)
{
	char *list[3] = {"快捷键", "计时表", "退出"};//zen表字符初始化
	register int i = 0;//初始化 i
	register int k = 0;//初始化 k
	int state = 0;//初始化 state
	BOX*pBox = NULL;//初始选中的框图的指针
	BOX*pPoint = NULL;//初始化选中节点的指针
	BOX*pPress = NULL;//初始化按键指针
	const Cir Sun = {600, 140, 10};//初始化太阳的数据，包括圆心横坐标，纵坐标，半径
	const Rect Table = {570, 40, 630, 110};//初始化zen表的数据
	Menu word[3] = {{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"}};//初始化弹出窗的数据
	/******将数据导入到Menu结构体中*******/
	for(k = 0; k < 3; k++)
	{
		word[k].pos.left = Table.left+5; 
		word[k].pos.top = Table.top+5+20*k;
		word[k].pos.right = Table.right;
		word[k].pos.bottom = Table.bottom;
		word[k].title = list[k];
	}
	/***********获取开始进入夜间模式的时间****************/
	if(start != 0)
	{
		time(&start);
	}
	/***********填充背景************/
	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, 639, 479);
	/*绘制zen表*/
	setcolor(DARKGRAY);
	rectangle(Table.left, Table.top, Table.right, Table.bottom);
	for(i = 0; i < 3; i++)
	{
		puthz(word[i].pos.left, word[i].pos.top, (word+i)->title, 16, 16, 8);
	}
	drawSun(Sun, DARKGRAY);//绘制太阳按钮
	/*********刷新思维导图*******/
	if(h != NULL)//若h不为空
	{
		drawAllDARKBox(h);//显示h所有信息
	}
	else//若h为空
	h = boxData0Generate( );//生成第一级数据
	
	while(1)//进入循环
	{
		state = mouseDark(h, &pBox, &pPoint, &pPress, Table, Sun, start, list);//获取状态
		switch(state)//判断状态参数
		{
			case 1://选中一级
			{
				pressBox(h, pBox);
				break;
			}
			case 2://选中节点
			{
				pointBackAndClear(h,pPoint);
				break;
			}
			case 3:case 7:case 31://开节点并生成下一级
			{
				openPointAndNextBox(h,pPress);
				break;
			}
			case 4:case 32://生成同一级
			{
				boxDataStorage(h,pPress,1);
				break;
			}
			case 5:case 21://删除一级
			{
				deleteBox(h,&pPress);
				break;
			}
			case 6://汉字输入
			{
				characterInput(pPress);
				break;
			}	
			case 9://移动
			{
				choiceDirection(h,&pPress);
				break;
			}
			case 10://移动界面
			{
				moveFace(h);
				break;
			}
			case 33://生成上一级
			{
				boxDataStorage(h,pPress,2);
				break;
			}
			case 34://生成父级
			{
				boxDataStorage(h,pPress,3);
				break;
			}
			case 40://跳转到主界面
			{
				return 4;
			}
			case 41://跳转到zen界面
			{
				return 5;
			}
		}
		if(state!=1 
		&& state!=9
		&& !(MouseX >= Table.left
		&& MouseX <= Table.right
		&& MouseY >= Table.top
		&& MouseY <= Table.bottom))//当导图不移动且导图不选中节点
		{
			renewNIGHTBox(h, Sun, 0, 0, 639, 479);//刷新导图
		}
		
	}
}

int TableDark(Rect Table, Cir Sun, long start, char **list)
{
	int a = 0;//初始化鼠标参数
	int state = 0;//初始化状态参数
	int face = 0;
	register int i = 0;//初始化鼠标在菜单栏中的位置参数
	
	while(1)
	{
		setviewport(0, 0, 639, 479, 1);
		newmouse(&MouseX, &MouseY, &a);//刷新鼠标
		
		for(i = 0; i < 3; i++)
		{
			/********判断鼠标所在汉字并将其现亮*********/
			if((MouseX >= Table.left 
			&& MouseX <= Table.right 
			&& MouseY >= (Table.top+5+i*20) 
			&& MouseY <= (Table.top+21+i*20))
			&& (i == 0 || i == 1))
			{
				setviewport(0, 0, 639, 479, 1);
				clrmous(MouseX, MouseY);//清除鼠标
				puthz(Table.left+5, Table.top+5+20*i, list[i], 16, 16, WHITE);//汉字显亮
				setviewport(0, 0, 639, 479, 1);
				newmouse(&MouseX, &MouseY, &a);//刷新鼠标
			}
			else if((MouseX >= Table.left 
			&& MouseX <= Table.right 
			&& MouseY >= (Table.top+5+i*20) 
			&& MouseY <= (Table.top+21+i*20))
			&& i == 2)
			{
				puthz(Table.left+5, Table.top+5+20*i, list[i], 16, 16, WHITE);//汉字显亮
			}
			if(!(MouseX >= Table.left 
			&& MouseX <= Table.right 
			&& MouseY >= (Table.top+5+i*20) 
			&& MouseY <= (Table.top+21+i*20)))
			{
				puthz(Table.left+5, Table.top+5+20*i, list[i], 16, 16, DARKGRAY);//汉字显亮
			}
		}
	/****************判断鼠标在菜单中的状态，并传递状态值******************/
		if(MouseX >= Table.left
		&& MouseX <= Table.right
		&& MouseY >= (Table.top+5)
		&& MouseY <= (Table.top+21))
		{
			state = 1;//鼠标位于快捷键
		}
		else if(MouseX >= Table.left
		&& MouseX <= Table.right
		&& MouseY >= (Table.top+5+20)
		&& MouseY <= (Table.top+21+20))
		{
			state = 2;//鼠标位于计时表
		}
		else if(MouseX >= Sun.centreX-13
		&& MouseX <= Sun.centreX+13
		&& MouseY >= Sun.centreY-13
		&& MouseY <= Sun.centreY+13)
		{
			state = 4;//鼠标按下太阳按钮
		}
		else if(mouse_press(Table.left, Table.top+5+40, Table.right, Table.top+21+40)==1)
		{
			state = 3;//鼠标按下退出
		}
		else if(!(MouseX <= Table.right
		&& MouseY <= Table.bottom
		&& MouseX >= Table.left
		&& MouseY >= Table.top)
		|| !(MouseX >= Sun.centreX-13
		&& MouseX <= Sun.centreX+13
		&& MouseY >= Sun.centreY-13
		&& MouseY <= Sun.centreY+13))
		{
			state = 5;//鼠标位于表格外
		}
		/**************判断状态参数**************/
		switch(state)
		{
			case 1:
				KeyShow_Dark(Table);//显示快捷键菜单
			break;
			case 2:
				TimeShow_Dark(start, Table);//显示计时表
			break;
			case 3:
			{
				clrmous(MouseX, MouseY);
				clearviewport();
				setfillstyle(1, WHITE);
				bar(0, 0, 639, 479);
				return 40;//跳转到主界面
			}
			case 4:
			{
				face = shine(Sun);
				if(face == 41)//判断是否按下太阳
				{
					return face;//返回zen界面
				}
			}
			break;
			case 5://进入导图编辑模式
			return;
		}
	}
}

int mouseDark(BOX*h, BOX**ppBox, BOX**ppPoint, BOX**ppPress, Rect Table, Cir Sun, long start, char **list)
{
	int a = 0;//初始化鼠标参数
	int onePress = 0;//初始化按键参数
	int flag = 0;//初始化标记参数
	
	while(1)
	{	/**********当鼠标位于太阳**************/
		if(MouseX >= Sun.centreX-13
		&& MouseX <= Sun.centreX+13
		&& MouseY >= Sun.centreY-13
		&& MouseY <= Sun.centreY+13)
		{
			while(MouseX >= Sun.centreX-13
			&& MouseX <= Sun.centreX+13
			&& MouseY >= Sun.centreY-13
			&& MouseY <= Sun.centreY+13)
			{
				if(bioskey(1) != 0)
				{
					bioskey(0);//清空缓存区
				}
				/************按键指针赋值************/
				setviewport(0, 0, 639, 479, 0);
				*ppPress = traversalPressBoxInZen(h,7);
				/************判断是否按下太阳**************/
				setviewport(0, 0, 639, 479, 1);
				newmouse(&MouseX, &MouseY, &a);
				flag = shine(Sun);
				return flag;	
			}
		}
		/*************鼠标位于导图区域************/
		else if(!((MouseX >= Table.left
		&& MouseX <= Table.right
		&& MouseY >= Table.top
		&& MouseY <= Table.bottom)
		|| (MouseX >= Sun.centreX-13
		&& MouseX <= Sun.centreX+13
		&& MouseY >= Sun.centreY-13
		&& MouseY <= Sun.centreY+13)))
		{
			setviewport(0, 0, 639, 479, 1);
			drawAllBox(h);
			while(!((MouseX >= Table.left
			&& MouseX <= Table.right
			&& MouseY >= Table.top
			&& MouseY <= Table.bottom)
			|| (MouseX >= Sun.centreX-13
			&& MouseX <= Sun.centreX+13
			&& MouseY >= Sun.centreY-13
			&& MouseY <= Sun.centreY+13)))
			{
				setviewport(0, 0, 639, 479, 1);
				newmouse(&MouseX, &MouseY, &a);//刷新鼠标
				/**************导图内容指针赋值*******************/
				setviewport(0, 0, 639, 479, 1);
				*ppBox = traversalBoxCycleInZen(h, 0, 0,7);
				*ppPress = traversalPressBoxInZen(h,7);
				*ppPoint = traversalPointCycleInZen(h, 0, 0);
				/*************判断是否按下鼠标左键*************/
				setviewport(0, 0, 639, 479, 1);
				if(press == 1 
				&& (*ppBox != NULL || *ppPoint != NULL))
				{
					delay(300);
					onePress = 1;
				}
				if(onePress == 1)
				{
					onePress = 0;
					if(*ppBox != NULL)
					{
						return 1;//选中框图
					}
					else if(*ppPoint != NULL)
					{
						return 2;//选中节点
					}
				}
				/**********读取键值做出判断，返回状态参数***************/
				setviewport(0, 0, 639, 479, 1);
				if(bioskey(1) != 0)//键盘键入操作
				{
					if(bioskey(1) == 0x0f09//按下Tab键
					&& (*ppPress) != NULL
					&& (*ppPress)->pointBackFlag == 0)
					{
						bioskey(0);					
						return 3;//开节点并生成下一级
					}
					else if(bioskey(1) == 0x1c0d//按下Enter键
					&& (*ppPress) != NULL)
					{
						bioskey(0);
						return 4;//生成同一级
					}
					else if(bioskey(1) == 0x5300//按下Delete键
					&& (*ppPress) != NULL && (*ppPress) != h)
					{
						bioskey(0);
						return 5;//删除一级
					}
					else if(bioskey(1) == 0x0f09//按下Shift+Tab键
					&& (*ppPress) != NULL
					&& (*ppPress)->pointBackFlag == 1)
					{
						bioskey(0);
						return 7;//开节点并生成下一级
					}
					else if(bioskey(1) == 0x1a1b//按下Ctrl和[键
					|| bioskey(1) == 0x1b1d//按下Ctrl和]键
					|| bioskey(1) == 0x2b1c//按下Ctrl和-键
					|| bioskey(1) == 0x0c1f//按下Ctrl和\键
					|| bioskey(1) == 0x180f)//按下Ctrl和O键
					{
						return 10;//移动思维导图
					}
					else if(bioskey(1) == 0x1C0A)//按下Ctrl和Enter键
					{
						bioskey(0);
						return 33;//生成上一级
					}
					else if(bioskey(1) == 0x2106)//按下Ctrl和F键
					{
						bioskey(0);
						return 34;//生成父级
					}
					else if(bioskey(1) == 0x320d)//按下Ctrl和M键
					{
						bioskey(0);
						return 40;//返回主界面
					}
					else if(bioskey(1) == 0x2c1a)//按下Ctrl和Z键
					{
						bioskey(0);
						return 41;//返回zen界面
					}
					// else if(bioskey(1) == 0x1e01)//按下Ctrl和A键
					// {
						// bioskey(0);
						// KeyShow_Dark(Table);
					// }
					/*当没有按下快捷键*/
					else if(bioskey(1)!=SPACE&&bioskey(1)!=DELETE&&bioskey(1)!=ENTER&&bioskey(1)!=TAB&&bioskey(1)!=CTRL_ENTER&&(*ppPress)!=NULL)
					{
						return 6;//汉字输入
					}
					/*按下方向键，选定框改变*/
					else if((bioskey(1) == 0x4800
					|| bioskey(1) == 0x4b00
					|| bioskey(1) == 0x5000
					|| bioskey(1) == 0x4d00)
					&&(*ppPress) != NULL)
					{
						return 9;
					}
					else if(bioskey(1) != 0)
					{
						bioskey(0);//清空缓存区
					}
				}
			}
		}
		/*************鼠标位于菜单栏***************/		
		else if(MouseX >= Table.left
		&& MouseX <= Table.right
		&& MouseY >= Table.top
		&& MouseY <= Table.bottom)
		{
			while(MouseX >= Table.left
				&& MouseX <= Table.right
				&& MouseY >= Table.top
				&& MouseY <= Table.bottom)
			{
				if(bioskey(1) != 0)
				{
					bioskey(0);//清空缓存区
				}
				setviewport(0, 0, 639, 479, 1);
				newmouse(&MouseX, &MouseY, &a);//刷新鼠标
				setviewport(0, 0, 639, 479, 0);
				*ppPress = traversalPressBoxInZen(h,7);
				flag = TableDark(Table, Sun, start, list);
				return flag;	//返回界面参数
			}
		}
	}
}

void TimeShow_Dark(long start, Rect Table)
{
	/*********初始化计时器参数***********/
	char *TM[3] = {"00", "00", "00"};//初始化char型时分秒
	char *unit[3] = {"时", "分", "秒"};//时间记录单位
	int tm[3] = {0, 0, 0};//初始化int型时分秒
	int a = 0;//初始化鼠标参数
	register int i = 0;//初始化标记参数
	int t = 0;//初始化时间
	time_t end;//结束时间
	const Rect timeshow = {457, 46, 569, 88};//时间表定位
	
	while(bioskey(1)!=SPACE)
	{
		time(&end);//获取结束时间
		/************绘制菜单栏***********/
		setcolor(DARKGRAY);
		rectangle(timeshow.left, timeshow.top, timeshow.right, timeshow.bottom);
		setfillstyle(1, LIGHTGRAY);
		bar(timeshow.left+1, timeshow.top+1, timeshow.right-1, timeshow.bottom-1);
		setcolor(DARKGRAY);
		puthz(timeshow.left+2, timeshow.top+2, "夜间时间", 16, 16, DARKGRAY);
		/************计算获取夜间模式使用时间**************/
		t = (long)difftime(end, start);
		tm[0] = t/3600;
		tm[1] = (t-tm[0]*3600)/60;
		tm[2] = t-tm[0]*3600-tm[1]*60;
		/****************显示时间***************/
		for(i=0; i<3; i++)
		{
			itoa(tm[i], TM[i], 10);
			puthz(timeshow.left+22+i*35, timeshow.top+23, unit[i], 16, 16, DARKGRAY);
			settextstyle(0, 0, 1);
			outtextxy(timeshow.left+4+35*i, timeshow.top+29, TM[i]);
		}
		delay(100);
		
		
		if(bioskey(1)!=0&&bioskey(1)!=SPACE&&bioskey(1)!=ESC)
		{	
			bioskey(0);//清空缓存区
		}
		else if(bioskey(1)==ESC)
		{
			return;//关闭计时表
		}
		newmouse(&MouseX,&MouseY,&a);
	}
	
}

void KeyShow_Dark(Rect Table)
{
	/**************快捷键信息初始化********************/
	char *key1[] = {"退出","删除","插入子主题","插入主题之后","插入主题之前","插入父主题","思维导图模式","左移导图","右移导图","上移导图","下移导图","导图归位"};
	char *key2[] = {"Esc","Delete","Tab","Enter","Ctrl+Enter","Ctrl+F","Ctrl+M","Ctrl+[","Ctrl+]","Ctrl+-","Ctrl+\\","Ctrl+O"};
	register int i = 0;//标记初始化
	register int j = 0;
	int a = 0;//鼠标参数初始化
	/**********************快捷键初始化并赋值***********************/
	Rect keytable = {360, 40, 570, 270};
	Menu Func[12] = {{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}};
	Menu Bios[12] = {{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}};			
	for(i = 0; i < 12; i++)
	{
		Func[i].pos.left = keytable.left+8;
		Func[i].pos.top = keytable.top+8+i*18;
		Func[i].pos.right = keytable.right;
		Func[i].pos.bottom = keytable.bottom;
		Func[i].title = key1[i];
		Bios[i].pos.left = keytable.left+130;
		Bios[i].pos.top = keytable.top+8+i*18;
		Bios[i].pos.right = keytable.right;
		Bios[i].pos.bottom = keytable.bottom;
		Bios[i].title = key2[i];
	}
	/****************绘制快捷键一览表********************/
	setfillstyle(1, LIGHTGRAY);
	bar(keytable.left, keytable.top, keytable.right, keytable.bottom);
	
	setcolor(DARKGRAY);
	rectangle(keytable.left, keytable.top, keytable.right, keytable.bottom);
	/*******************显示快捷键信息***********************/
	for(j = 0; j < 12; j++)
	{
		puthz(Func[j].pos.left, Func[j].pos.top, Func[j].title, 16, 16, 8);
		xouttextxy(Bios[j].pos.left, Bios[j].pos.top, Bios[j].title, 8);
	}
	
	while(bioskey(1)!=SPACE)
	{
		if(bioskey(1)!=0&&bioskey(1)!=SPACE&&bioskey(1)!=ESC)
		{	
			bioskey(0);//清空缓存区
		}
		else if(bioskey(1)==ESC)
		{
			return;//关闭快捷键一览表
		}
		newmouse(&MouseX,&MouseY,&a);//刷新鼠标
	}
}

void drawAllDARKBox(BOX*h) 
{
	BOX*p=h;
	while(p!=NULL)//判断导图指针h是否为空
	{
		/***************绘制导图*****************/
		if(p->parentPointBackFlag==0)
		{
			drawOneBox(p->centerX,p->centerY,p->boxX,p->boxY,p->lineX,p->lineY,p->content,p->pointFlag, p->pointBackFlag,p->lastLevelSum,p->nextAllSum,p->boldFlag,p->boxColor,p->characterColor,p->characterSize);//画出一个一级框
		}
		p=p->next;
		drawDARKTable();
	}
}

void renewNIGHTBox(BOX*h, Cir Sun, int x1,int y1,int x2,int y2)
{
	int button;//初始化鼠标参数
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);//清除鼠标
	setviewport(x1,y1,x2,y2,1);
	setfillstyle(1,LIGHTGRAY);
	bar(x1,y1,x2,y2);//填充背景
	boxDataGenerate(h);//生成所有方框的所有数据
	drawAllDARKBox(h);//画出所有的方框
	drawDARKTable();
	setviewport(0,0,639,479,1);
	MouseX-=1;
	setviewport(0, 0, 639, 479, 1);
	newmouse(&MouseX,&MouseY,&button);
}

int shine(Cir Sun)
{
	int a = 0;
	while(1)
	{
		setviewport(0, 0, 639, 479, 1);
		newmouse(&MouseX, &MouseY, &a);
		/************鼠标处在太阳按钮*************/
		if(MouseX >= Sun.centreX-13
		&& MouseX <= Sun.centreX+13
		&& MouseY >= Sun.centreY-13
		&& MouseY <= Sun.centreY+13)
		{
			drawSun(Sun, YELLOW);//太阳显亮
			if(press == 1)//判断是否按下太阳
			{
				/**********按下太阳，跳转到zen界面******/
				setfillstyle(1,WHITE);
				bar(0, 0, 639, 479);
				clrmous(MouseX, MouseY);
				return 41;
			}
		}
		/************鼠标移开太阳按钮*************/
		else
		{
			drawSun(Sun, DARKGRAY);
			setviewport(0, 0, 639, 479, 1);
			clrmous(MouseX, MouseY);
			return;
		}
	}
}
/**************绘制太阳按钮************/
void drawSun(Cir Sun, int color)
{
	setcolor(color);
	circle(Sun.centreX, Sun.centreY, Sun.radius);
	setfillstyle(1, color);
	floodfill(Sun.centreX, Sun.centreY, color);
	setlinestyle(0, 0, 1);
	line(Sun.centreX-10, Sun.centreY, Sun.centreX-17, Sun.centreY);
	line(Sun.centreX+10, Sun.centreY, Sun.centreX+17, Sun.centreY);
	line(Sun.centreX, Sun.centreY-10, Sun.centreX, Sun.centreY-17);
	line(Sun.centreX, Sun.centreY+10, Sun.centreX, Sun.centreY+17);
	line(Sun.centreX-8, Sun.centreY-8, Sun.centreX-12, Sun.centreY-12);
	line(Sun.centreX+8, Sun.centreY+8, Sun.centreX+12, Sun.centreY+12);
	line(Sun.centreX-8, Sun.centreY+8, Sun.centreX-12, Sun.centreY+12);
	line(Sun.centreX+8, Sun.centreY-8, Sun.centreX+12, Sun.centreY-12);
}

void drawDARKTable()
{
	char *list[3] = {"快捷键", "计时表", "退出"};//初始化菜单信息
	register int i = 0;
	register int k = 0;//初始化标记符
	static Rect Table = {570, 40, 630, 110};//定位菜单栏
	const Cir Sun = {600, 140, 10};//定位太阳
	/****************初始化信息*****************/
	Menu word[3] = {{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"}};
	/*************信息赋值**********************/
	for(k = 0; k < 3; k++)
	{
		word[k].pos.left = Table.left+5; 
		word[k].pos.top = Table.top+5+20*k;
		word[k].pos.right = Table.right;
		word[k].pos.bottom = Table.bottom;
		word[k].title = list[k];
	}
	/************绘制菜单***********/
	setfillstyle(1, LIGHTGRAY);
	bar(Table.left, Table.top, Table.right, Table.bottom);
	setcolor(DARKGRAY);
	rectangle(Table.left, Table.top, Table.right, Table.bottom);
	/**********显示菜单信息*********/
	for(i=0; i<3; i++)
	{
		puthz(word[i].pos.left, word[i].pos.top, (word+i)->title, 16, 16, 8);
	}
	
	drawSun(Sun, DARKGRAY);//绘制太阳
}