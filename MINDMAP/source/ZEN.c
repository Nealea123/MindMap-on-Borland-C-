#include"MAINHEAD.h"

int zenInterface(BOX*h, long start)
{
	char *list[5] = {"夜间", "快捷键", "计时表", "样式", "退出"};//初始化zen表格内的文字
	register int i = 0;//初始化标记字符i
	register int k = 0;//初始化标记字符k
	int state = 0;//初始化状态标记
	const Rect Table = {570, 25, 630, 210};//zen表格定位赋值
	Menu word[5] = {{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"}};//初始zen表格

	BOX*pBox = NULL, *pPoint = NULL, *pPress = NULL;//一级指针
	
	setviewport(0,0,639,479,1);
	setfillstyle(1, h->lastLevelFlag);
	bar(0, 0, 639, 479);//填充背景
	
	for(k = 0; k < 5; k++)//zen表格赋值
	{
		word[k].pos.left = Table.left+5; 
		word[k].pos.top = Table.top+5+40*k;
		word[k].pos.right = Table.right;
		word[k].pos.bottom = Table.bottom;
		word[k].title = list[k];
	}

	setcolor(LIGHTGRAY);
	rectangle(Table.left, Table.top, Table.right, Table.bottom);
	setfillstyle(1, WHITE);
	bar(Table.left+1, Table.top+1, Table.right-1, Table.bottom-1);//绘制表格

	if(h != NULL)//导图不为空
	{
		drawAllZENBox(h);//绘制思维导图
	}
	else//导图为空
	h = boxData0Generate( );//生成第一级数据

	for(i = 0; i < 5; i++)
	{
		puthz(word[i].pos.left, word[i].pos.top, (word+i)->title, 16, 16, 8);//显示zen表汉字
	}
	if(start != 0)
	{
		time(&start);//获取开始时间
	}
	
	while(1)
	{
		state = mouseZEN(h, &pBox, &pPoint, &pPress, Table, start, list);//进入状态选择
		switch(state)
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
			case 40://跳转到夜间模式
			{
				return 6;
			}
			case 41://跳转到主界面
			{
				return 4;
			}
		}
		if(state!=1&&state!=9)//当没有移动或者选中导图时
		{
			renewZENBox(h,0,0,639,479);//刷新思维导图
		}
	}
}

int TableOp(Rect Table, BOX*h, BOX**ppPress, long start, char **list)
{
	int a = 0;//鼠标参数初始化
	int state = 0;//状态参数初始化
	register int i = 0;//标记初始化
	time_t end;//结束时间
	
	while(1)
	{
		
		setviewport(0, 0, 639, 479, 1);
		newmouse(&MouseX, &MouseY, &a);//更新鼠标
		
		for(i = 0; i < 5; i++)//当鼠标在相应的文字上时，文字现亮
		{
			if((MouseX >= Table.left 
			&& MouseX <= Table.right 
			&& MouseY >= (Table.top+5+i*40) 
			&& MouseY <= (Table.top+21+i*40))
			&& (i == 1 || i == 2)) 
			{
				setviewport(0, 0, 639, 479, 1);
				clrmous(MouseX, MouseY);
				puthz(Table.left+5, Table.top+5+40*i, list[i], 16, 16, BLUE);
				setviewport(0, 0, 639, 479, 1);
				newmouse(&MouseX, &MouseY, &a);
			}
			else if((MouseX >= Table.left 
			&& MouseX <= Table.right 
			&& MouseY >= (Table.top+5+i*40) 
			&& MouseY <= (Table.top+21+i*40))
			&& (i == 0 || i == 3 || i == 4)) 
			{
				puthz(Table.left+5, Table.top+5+40*i, list[i], 16, 16, BLUE);
			}
			else if(!(MouseX >= Table.left 
			&& MouseX <= Table.right 
			&& MouseY >= (Table.top+5+i*40) 
			&& MouseY <= (Table.top+21+i*40)))
			{
				puthz(Table.left+5, Table.top+5+40*i, list[i], 16, 16, DARKGRAY);
			}
		}
		
		if(MouseX >= Table.left
		&& MouseX <= Table.right
		&& MouseY >= (Table.top+5+40)
		&& MouseY <= (Table.top+21+40))
		{
			state = 2;//鼠标在”快捷键“上传递state = 2
		}
		
		else if(MouseX >= Table.left
		&& MouseX <= Table.right
		&& MouseY >= (Table.top+5+80)
		&& MouseY <= (Table.top+21+80))
		{
			state = 3;//鼠标在”计时表“上传递state = 3
		}
		
		else if(mouse_press(Table.left, Table.top+5, Table.right, Table.top+21)==1)
		{
			state = 1;//鼠标点击夜间，传递参数state = 1
		}
		
		else if(mouse_press(Table.left, Table.top+5+120, Table.right, Table.top+21+120)==1)
		{
			state = 4;//鼠标点击样式，传递参数state = 4
		}
		
		else if(mouse_press(Table.left, Table.top+5+160, Table.right, Table.top+21+160)==1)
		{
			state = 5;//鼠标点击退出，传递参数state = 5
		}
		
		else if(!(MouseX <= Table.right
		&& MouseY <= Table.bottom
		&& MouseX >= Table.left
		&& MouseY >= Table.top))
		{
			state = 6;//鼠标不在zen表内，传递参数state = 6
		}
		
		switch(state)//判断state的值
		{
			case 1://进入夜间模式2
			{
				clrmous(MouseX, MouseY);
				clearviewport();
				setfillstyle(1, LIGHTGRAY);
				bar(0, 0, 639, 479);
				mouseinit();
				return 40;
			}
			case 2://查看快捷键
			KeyShow(h, Table);
			break;
			case 3://查看zen模式下时间记录
			TimeShow(h, start, Table);
			break;
			case 4://选择样式
			boxType(h,*ppPress);
			break;
			case 5://返回主界面
			{
				clrmous(MouseX, MouseY);
				clearviewport();
				setfillstyle(1, WHITE);
				bar(0, 0, 639, 479);
				return 41;
			}
			case 6://进入导图编辑模式
			return ;
		}
	}
}

int mouseZEN(BOX*h, BOX**ppBox, BOX**ppPoint, BOX**ppPress, Rect Table, long start, char **list)
{
	int a = 0;//鼠标参数初始化
	int onePress = 0;//鼠标按键初始化
	int flag = 0;//标记初始化
	
	while(1)
	{
		if(!(MouseX >= Table.left
		&& MouseX <= Table.right
		&& MouseY >= Table.top
		&& MouseY <= Table.bottom))//鼠标不在zen表内
		{
			setviewport(0, 0, 639, 479, 1);
			drawAllZENBox(h);//更新导图
			while(!(MouseX >= Table.left
			&& MouseX <= Table.right
			&& MouseY >= Table.top
			&& MouseY <= Table.bottom))
			{
				setviewport(0, 0, 639, 479, 1);
				newmouse(&MouseX, &MouseY,&a);//刷新鼠标
				
				setviewport(0, 0, 639, 479, 1);
				*ppBox = traversalBoxCycleInZen(h, 0, 0, h->lastLevelFlag);
				*ppPress = traversalPressBoxInZen(h,h->lastLevelFlag);
				*ppPoint = traversalPointCycleInZen(h, 0, 0);//更新思维导图数据
				
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
						return 1;//选中一级
					}
					else if(*ppPoint != NULL)
					{
						return 2;//选中节点
					}
				}
				
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
						return 10;//移动界面
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
					else if(bioskey(1) == 0x320d
					|| bioskey(1) == 0x011b)//按下Ctrl和M键或者esc键
					{
						bioskey(0);
						return 41;//返回主界面
					}
					else if(bioskey(1) == 0x1e01)//按下Ctrl和A键
					{
						bioskey(0);
						KeyShow(h, Table);
					}
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
						return 9;//移动
					}
					else if(bioskey(1) != 0)
					{
						bioskey(0);//清空缓存区
					}
				}
			}
		}
	
		if(MouseX >= Table.left
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
				
				setviewport(0, 0, 639, 479, 0);
				*ppPress = traversalPressBoxInZen(h,h->lastLevelFlag);
				
				setviewport(0, 0, 639, 479, 1);
				newmouse(&MouseX, &MouseY, &a);//刷新鼠标
				flag = TableOp(Table, h, ppPress, start, list);//进入zen表模式
				
				return flag;//放回界面参数
			}
			clrmous(MouseX, MouseY);//擦除鼠标
		}
	}
}

void TimeShow(BOX*h, long start, Rect Table)
{
	char *TM[3] = {"00", "00", "00"};//初始化字符型的时分秒
	char *unit[3] = {"时", "分", "秒"};
	int tm[3] = {0, 0, 0};//初始化int型的时分秒
	int a = 0;//传递鼠标参数
	register int i = 0;//传递标记符
	int t = 0;//时间记录
	time_t end;//结束时间
	const Rect timeshow = {457, 106, 569, 148};//定义计时器位置
	
	while(bioskey(1)!=SPACE)//不按下空格键
	{
		time(&end);//获取结束时间
		/*显示计时器上的汉字*/
		setcolor(DARKGRAY);
		rectangle(timeshow.left, timeshow.top, timeshow.right, timeshow.bottom);
		setfillstyle(1, 15);
		bar(timeshow.left+1, timeshow.top+1, timeshow.right-1, timeshow.bottom-1);
		setcolor(DARKGRAY);
		puthz(timeshow.left+2, timeshow.top+2, "专注时间", 16, 16, DARKGRAY);
		/*计算时分秒*/
		t = (long)difftime(end, start);
		tm[0] = t/3600;
		tm[1] = (t-tm[0]*3600)/60;
		tm[2] = t-tm[0]*3600-tm[1]*60;
		/*显示时间*/
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
			bioskey(0);//清空缓冲区
		}
		else if(bioskey(1)==ESC)
		{
			return;//退出界面
		}
		newmouse(&MouseX,&MouseY,&a);//刷新鼠标
	}
	
}

void KeyShow(BOX*h, Rect Table)
{
	/*初始化显示的字符*/
	char *key1[] = {"退出","删除","插入子主题","插入主题之后","插入主题之前","插入父主题","思维导图模式","左移导图","右移导图","上移导图","下移导图","导图归位"};
	char *key2[] = {"Esc","Delete","Tab","Enter","Ctrl+Enter","Ctrl+F","Ctrl+M","Ctrl+[","Ctrl+]","Ctrl+-","Ctrl+\\","Ctrl+O"};
	/*初始化标记符*/
	register int i = 0;
	register int j = 0;
	int a = 0;//鼠标参数初始化
	/*初始化快捷键信息*/
	Rect keytable = {360, 20, 570, 250};
	Menu Func[12] = {{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}};
	Menu Bios[12] = {{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}};
	/*快捷键信息赋值*/				
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
	/*绘制快捷键表格*/
	setfillstyle(1, WHITE);
	bar(keytable.left, keytable.top, keytable.right, keytable.bottom);
	setcolor(LIGHTGRAY);
	rectangle(keytable.left, keytable.top, keytable.right, keytable.bottom);
	/*显示快捷键信息*/
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
			return;//关闭快捷键
		}
		newmouse(&MouseX,&MouseY,&a);//刷新鼠标
	}
	renewZENBox(h,0,0,639,479);//刷新导图
}


void renewZENBox(BOX*h,int x1,int y1,int x2,int y2)
{
	int button = 0;//鼠标参数初始化
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);//清除鼠标
	setviewport(x1,y1,x2,y2,1);
	setfillstyle(1,h->lastLevelFlag);
	bar(x1,y1,x2,y2);//填充背景
	boxDataGenerate(h);//生成所有方框的所有数据
	drawAllZENBox(h);//画出所有的方框
	drawtable();//绘制zen表
	setviewport(0,0,639,479,1);//鼠标刷新
	MouseX-=1;
	newmouse(&MouseX,&MouseY,&button);
}

void drawAllZENBox(BOX*h) //绘制zen模式下的思维导图
{
	BOX*p=h;	
	while(p!=NULL)
	{
		if(p->parentPointBackFlag==0)
		{
			drawOneBox(p->centerX,p->centerY,p->boxX,p->boxY,p->lineX,p->lineY,p->content,p->pointFlag, p->pointBackFlag,p->lastLevelSum,p->nextAllSum,p->boldFlag,p->boxColor,p->characterColor,p->characterSize);//画出一个一级框
		}
		p=p->next;
		drawtable();
	}
}

void drawtable()
{
	/*********************zen表初始化**************************/
	char *list[5] = {"夜间", "快捷键", "计时表", "样式", "退出"};
	static Rect Table = {570, 25, 630, 210};
	register int i = 0;
	register int k = 0;
	Menu word[5] = {{{0, 0, 0, 0}, "\0"},
				{{0, 0, 0, 0}, "\0"},
				{{0, 0, 0, 0}, "\0"},
				{{0, 0, 0, 0}, "\0"},
				{{0, 0, 0, 0}, "\0"}};
	/************************zen表赋值***************************/			
	for(k = 0; k < 5; k++)
	{
		word[k].pos.left = Table.left+5; 
		word[k].pos.top = Table.top+5+40*k;
		word[k].pos.right = Table.right;
		word[k].pos.bottom = Table.bottom+21;
		word[k].title = list[k];
	}	
    /**************************绘制zen表**************************/
	setcolor(LIGHTGRAY);
	rectangle(Table.left, Table.top, Table.right, Table.bottom);
	setfillstyle(1, WHITE);
	bar(Table.left+1, Table.top+1, Table.right-1, Table.bottom-1);
	for(i = 0; i < 5; i++)
	{
		puthz(word[i].pos.left, word[i].pos.top, (word+i)->title, 16, 16, 8);
	}	
}