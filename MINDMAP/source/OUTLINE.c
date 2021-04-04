#include"MAINHEAD.h"
//大纲模式操作界面
int outlineModeFace(BOX*hB)
{
	int flag=0;//操作识别符
	LINE*hL=NULL;
	LINE*pLine=NULL,*pPoint=NULL,*pPress=NULL;
	clrmous(MouseX,MouseY);
	MouseS=4;
	setviewport(0,0,639,479,1);
	setfillstyle(1,XLCDBACKGOUNDCOLOR);
	bar(0,0,639,479);
	setfillstyle(1,hB->lastLevelFlag);
	bar(1,20,638,478);
	setviewport(1,20,638,478,1);
	hL=transMindMapToOutline(hB);
	setviewport(0,0,639,479,1);
	drawOutlineInterface(hL);
	setviewport(1,20,638,478,1);
	lineDataGenerate(hL);
	hL->x0=30;
	hL->y0=30;
	drawAllLine(hL);
	
	while(1)
	{
		flag=mouseKeyOutlineOperate(hL,&pLine,&pPoint,&pPress);//获得操作指令
		switch(flag)//执行操作
		{
			case 1://选中一级
			{
				pressLine(hL,pLine);
				break;
			}
			case 2://选中节点
			{
				pointBackAndClear(hL->pBox,pPoint->pBox);
				break;
			}
			case 6://汉字输入
			{
				characterInputInLine(pPress);
				break;
			}	
			case 8://退出
			{
				exitLineAndClear(hL);
				return 8;
			}
			case 9://移动
			{
				choiceLineDirection(hL,pPress);
				break;
			}
			case 10://移动界面
			{
				moveFaceInLine(hL);
				break;
			}
			case 31://快捷键助手
			{
				shortcutAssistantInLine(hL);
				break;
			}
			case 11://样式
			{
				boxType(hL->pBox,pPress->pBox);
				break;
			}
			case 21:
			{
				clearAllLine(hL);
				return 4;
			}
			case 23:
			{
				clearAllLine(hL);
				return 5;
			}
		}
		if(flag!=1&&flag!=9)
		{
			reDrawLineAll(hL);//互动后更新界面
		}
	}	
}
//大纲模式鼠标操作
int mouseKeyOutlineOperate(LINE*hL,LINE**ppLine,LINE**ppPoint,LINE**ppPress)
{
	int button=0,onePress=0,menuFlag=0,flag=0;
	while(1)
	{
		if(MouseX<=638&&MouseY>=20)
		{
			setviewport(1,20,638,478,1);
			drawAllLine(hL);
			while(MouseX<=638&&MouseY>=20)
			{	
				setviewport(0,0,639,479,1);
				newmouse(&MouseX,&MouseY,&button);
				
				setviewport(1,20,638,478,1);
				*ppLine=traversalLineCycle(hL,1,20);
				*ppPress=traversalLinePressBox(hL);
				*ppPoint=traversalLinePointCycle(hL,1,20);
				
				setviewport(0,0,639,479,1);
				if(press==1&&(*ppLine!=NULL||*ppPoint!=NULL))//鼠标点击操作
				{
					delay(300);
					onePress=1;
				}
				if(onePress==1)
				{
					onePress=0;
					if(*ppLine!=NULL)
					{
						return 1;
					}
					else if(*ppPoint!=NULL)
					{
						return 2;
					}
				}
				
				setviewport(1,20,638,478,1);
				if(bioskey(1)!=0)//键盘键入操作
				{	
					if(bioskey(1)==ESC)
					{
						bioskey(0);
						flag=exitYesOrNo();
						if(flag==0)
						{
							return 8;
						}
						else 
						{
							setviewport(1,20,638,478,1);
							drawAllLine(hL);
							continue;
						}
					}
					else if(bioskey(1)==CTRL_LEFT||bioskey(1)==CTRL_RIGHT||bioskey(1)==CTRL_DOWN||bioskey(1)==CTRL_UP||bioskey(1)==CTRL_O)
					{
						return 10;	
					}
					else if(bioskey(1)==CTRL_M)
					{
						bioskey(0);
						return 21;
					}
					else if(bioskey(1)==CTRL_B)
					{
						bioskey(0);
						return 22;
					}
					else if(bioskey(1)==CTRL_Z)
					{
						bioskey(0);
						return 23;
					}
					else if(bioskey(1)==CTRL_A)
					{
						bioskey(0);
						return 31;
					}
					else if(bioskey(1)==CTRL_T)
					{
						bioskey(0);
						return 11;
					}
					else if((bioskey(1)==UP||bioskey(1)==DOWN)&&(*ppPress)!=NULL)
					{
						return 9;
					}
					else if(bioskey(1)!=SPACE&&bioskey(1)!=DELETE&&bioskey(1)!=ENTER&&bioskey(1)!=TAB&&bioskey(1)!=CTRL_ENTER&&(*ppPress)!=NULL)
					{
						return 6;
					}
					else if(bioskey(1)!=0)
					{
						bioskey(0);
					}
				}				
			}
			setviewport(0,0,639,479,1);
			clrmous(MouseX,MouseY);
		}
		if(MouseY<=19)
		{ 
			while(MouseY<=19)
			{
				if(bioskey(1)!=0)
				{
					bioskey(0);
				}
				setviewport(1,20,638,478,1);
				*ppPress=traversalLinePressBox(hL);
				
				setviewport(0,0,639,479,1);
				newmouse(&MouseX,&MouseY,&button);
				menuFlag=dropDownOutlineMenu(hL);
				
				if(menuFlag>=11)
				{
					return menuFlag;
				}
			} 
			clrmous(MouseX,MouseY);
		}	
	}
}
//大纲模式下拉菜单
int dropDownOutlineMenu(LINE*hL)
{
	char *s[]={"编辑","查看","帮助"};
	int b[]={1,3,1,0};
	int c[]={0,1,4,5,0};
	char *z[]={
	"样式",
	"思维导图","大纲","真模式",
	"快捷键助手",};
	int i=0,j=0,flag=0,a=0,flag0=0,menuXFlag=0,menuYFlag=0;
	for(i=0;i<3;i++)
	{
		if(mouseIn(5+48*i,1,5+48*i+32,19))//一级菜单栏(5+28*i,1)-(5+48*i+32,19)
		{
			clrmous(MouseX,MouseY);
			puthz(5+48*i, 1, s[i], 16, 16, THZCOLOR);
			setfillstyle(1,XLCDBACKGOUNDCOLOR);
			bar(5+48*i-2,18,5+48*i-2+80,18+b[i]*20);
			//清白(5+48*i-2,18)-(5+48*i+80,18+b[i]*20)
			setcolor(SFKCOLOR);
			rectangle(5+48*i-2,18,5+48*i-2+80,18+b[i]*20);//画框(5+48*i-2,18)-(5+48*i+80,18+b[i]*20)
			for(j=0;j<b[i];j++)
			{
				puthz(5+48*(i), 20+j*20, z[c[i]+j], 16, 16, XLCDHZCOLOR);
			}
			flag=1;
			
			while(mouseIn(5+48*i-2,18,5+48*i+80,19+b[i]*20)||mouseIn(5+48*i,1,5+48*i+32,19))//(5+48*i-2,1)-(5+48*i-2+80,20+b[i]*20)
			{
				newmouse(&MouseX,&MouseY,&a);
				for(j=0;j<b[i];j++)
				{
					if(MouseY>=20+j*20&&MouseY<=20+j*20+20)  
					{
						puthz(5+48*(i),  20+j*20, z[c[i]+j], 16, 16, THZCOLOR);
						if(press==1)
						{
							menuXFlag=i+1;
							menuYFlag=j+1;
							puthz(5+48*(i), 1, s[i], 16, 16, XLCDHZCOLOR);
							clrmous(MouseX,MouseY);
							setfillstyle(1,hL->pBox->lastLevelFlag);
							bar(3,19,200,90);
							justDrawLine(hL);
							clrmous(MouseX,MouseY);
							setcolor(15);
							line(3,18,200,18);
							return (menuXFlag*10+menuYFlag);
						}
					}
					if(	!(MouseY>=20+j*20&&MouseY<=20+j*20+20))
					{
						puthz(5+48*(i), 20+j*20, z[c[i]+j], 16, 16, XLCDHZCOLOR);
					}
				}
			}
			clrmous(MouseX,MouseY);
		}
		if(!mouseIn(5+48*i,1,5+48*i+32,19))//菜单存在范围(5+48*i,1)-(5+48*i+32,19)
		{
			puthz(5+48*(i), 1, s[i], 16, 16, XLCDHZCOLOR);
			while(flag==1)
			{
				clrmous(MouseX,MouseY);
				setfillstyle(1,hL->pBox->lastLevelFlag);
				bar(3,19,200,90);
				justDrawLine(hL);
				clrmous(MouseX,MouseY);
				setcolor(15);
				line(3,18,200,18);
				flag=0;
			}
		}
	}
	
	if(mouseIn(420,1,484,17))//一级菜单栏(5+28*i,1)-(5+48*i+32,19)
	{
		clrmous(MouseX,MouseY);
		puthz(420,1,"思维导图",16,16,THZCOLOR);
		MouseX--;MouseY--;
		newmouse(&MouseX,&MouseY,&a);
		while(mouseIn(420,1,484,17))//(5+48*i-2,1)-(5+48*i-2+80,20+b[i]*20)
		{
			newmouse(&MouseX,&MouseY,&a);
			if(press==1)
			{
				delay(200);
				return 21;
			}
		}
		if(mouseIn(420,1,484,17)==0)
		{
			clrmous(MouseX,MouseY);
			puthz(420,1,"思维导图",16,16,HZCOLOR);
		}
	}
	
	if(mouseIn(500,1,532,17))
	{
		clrmous(MouseX,MouseY);
		puthz(500,1,"大纲",16,16,THZCOLOR);
		MouseX--;MouseY--;
		newmouse(&MouseX,&MouseY,&a);
		while(mouseIn(500,1,532,17))//(5+48*i-2,1)-(5+48*i-2+80,20+b[i]*20)
		{
			newmouse(&MouseX,&MouseY,&a);
			if(press==1)
			{
				delay(200);
				return 22;
			}
		}
	}
	
	if(mouseIn(548,6,578,17))
	{
		clrmous(MouseX,MouseY);
		settextstyle(1,0,1);
		settextjustify(LEFT_TEXT,CENTER_TEXT);
		setcolor(THZCOLOR);
		outtextxy(548,6,"ZEN");
		MouseX--;MouseY--;
		newmouse(&MouseX,&MouseY,&a);
		while(mouseIn(548,6,578,17))//(5+48*i-2,1)-(5+48*i-2+80,20+b[i]*20)
		{
			newmouse(&MouseX,&MouseY,&a);
			if(press==1)
			{
				delay(200);
				return 23;
			}
		}
		if(mouseIn(548,6,578,17)==0)
		{
			clrmous(MouseX,MouseY);
			settextstyle(1,0,1);
			settextjustify(LEFT_TEXT,CENTER_TEXT);
			setcolor(HZCOLOR);
			outtextxy(548,6,"ZEN");
		}
	}
	return 0;
}
//大纲模式的快捷键助手
void shortcutAssistantInLine(LINE*hL)
{
	int button,i=0,j=0;
	char *z[]={"样式",
	"思维导图模式","大纲模式","真模式",
	"快捷键助手",
	"左移大纲","右移大纲","上移大纲","下移大纲","大纲归位"};
	char *e[]={"Ctrl+T","Ctrl+M","Ctrl+B","Ctrl+Z","Ctrl+A","Ctrl+[","Ctrl+]","Ctrl+-","Ctrl+\\","Ctrl+O"};
	
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setfillstyle(1,XLCDBACKGOUNDCOLOR);
	bar(220,120,420,370);
	setcolor(8);
	rectangle(220,120,420,370);
	for(i=0;i<10;i++)
	{
		if(i==1||i==4||i==5||i==10)
		{
			j++;
		}
		puthz(225, 125+i*18+8*j, z[i], 16, 16, j);
		setcolor(j);
		settextjustify(LEFT_TEXT,TOP_TEXT);
		settextstyle(0,0,1);
		outtextxy(330, 130+i*18+8*j, e[i]);
	}
	puthz(225, 350, "点击空格键退出快捷键助手", 16, 16, 0);
	puthz(257, 350, "空格键", 16, 16, 4);
	
	while(bioskey(1)!=SPACE)
	{
		if(bioskey(1)!=0&&bioskey(1)!=SPACE&&bioskey(1)!=ESC)
		{	
			bioskey(0);
		}
		else if(bioskey(1)==ESC)
		{
			return;
		}
		newmouse(&MouseX,&MouseY,&button);
	}
}
//移动大纲界面
void moveFaceInLine(LINE*hL)
{
	if(bioskey(1)==CTRL_LEFT)//向左移
	{
		bioskey(0);
		hL->x0=hL->x0-10;
	}
	else if(bioskey(1)==CTRL_RIGHT)//向右移
	{
		bioskey(0);
		hL->x0=hL->x0+10;
	}
	else if(bioskey(1)==CTRL_UP)//向上移
	{
		bioskey(0);
		hL->y0=hL->y0-10;
	}
	else if(bioskey(1)==CTRL_DOWN)//向下移
	{
		bioskey(0);
		hL->y0=hL->y0+10;
	}
	else if(bioskey(1)==CTRL_O)//归位
	{
		bioskey(0);
		hL->x0=30;
		hL->y0=30;
	}
	renewXY(hL);
}
//指向大纲线上下移动
void choiceLineDirection(LINE*hL,LINE*pPress)
{
	LINE*pL=NULL;
	if(bioskey(1)==UP&&pPress!=NULL)//向上
	{
		bioskey(0);
		if(pPress!=hL)
		{
			pL=hL;
			while(pL!=NULL)
			{
				if(pL->next==pPress)
				{
					break;
				}
				pL=pL->next;
			}
			pressLine(hL,pL);
		}
	}
	else if(bioskey(1)==DOWN&&pPress!=NULL)//向下
	{
		bioskey(0);
		if(pPress->next!=NULL)
		{
			pressLine(hL,pPress->next);
		}
	}
}
//退出大纲模式
void exitLineAndClear(LINE*hL)
{
	clearAllBox(hL->pBox);
	clearAllLine(hL);
}
//点击选中一级大纲线
void pressLine(LINE*hL,LINE*pPress)
{
	clearAllPressBox(hL->pBox);
	pPress->pBox->pressFlag=1;
}
//寻找鼠标所在的一级大纲线
LINE* traversalLineCycle(LINE*hL,int x1,int y1)
{
	LINE*pL=hL;
	int mouseX,mouseY;
	int L=0,englishSum=0,i=0;
	mouseX=MouseX-x1;
	mouseY=MouseY-y1;
	while(pL!=NULL)
	{	
		if(pL->pBox->parentPointBackFlag==0)
		{
			for(i=0;i<strlen(pL->pBox->content);i++)
			{
				if(pL->pBox->content[i]<127&&pL->pBox->content[i]>31)
				{
					englishSum++;
				}
			}
			if(strlen(pL->pBox->content)==0&&pL==hL)
			{
				L=8;
			}
			else if(strlen(pL->pBox->content)==0)
			{
				L=6;
			}
			else
			{
				L=0;
			}
			if(mouseX>=pL->x0 &&mouseY <= pL->y0+20-4  && mouseY >= pL->y0)
			{
				setcolor(SFKCOLOR);
				line(pL->x0,pL->y0+20-4,pL->x0+((strlen(pL->pBox->content)-englishSum+L)/2*8+englishSum*6)*2,pL->y0+20-4);
				englishSum=0;
				return pL;
			}
			else
			{
				setcolor(hL->pBox->lastLevelFlag);
				line(pL->x0,pL->y0+20-4,pL->x0+((strlen(pL->pBox->content)-englishSum+L)/2*8+englishSum*6)*2,pL->y0+20-4);
				englishSum=0;
			}	
		}
		pL=pL->next;
	}
	return pL;
}
//寻找选中的一级大纲线
LINE *traversalLinePressBox(LINE*hL)
{
	LINE*pL=hL,*p0=NULL;
	int L=0,englishSum=0,i=0;
	
	while(pL!=NULL)
	{
		if(pL->pBox->parentPointBackFlag==0)
		{
			for(i=0;i<strlen(pL->pBox->content);i++)
			{
				if(pL->pBox->content[i]<127&&pL->pBox->content[i]>31)
				{
					englishSum++;
				}
			}
			if(strlen(pL->pBox->content)==0&&pL==hL)
			{
				L=8;
			}
			else if(strlen(pL->pBox->content)==0)
			{
				L=6;
			}
			else
			{
				L=0;
			}
			if(pL->pBox->pressFlag==1&&pL->pBox->parentPointBackFlag==0)
			{
				setcolor(SFKCOLOR);
				line(pL->x0,pL->y0+20-3,pL->x0+((strlen(pL->pBox->content)-englishSum+L)/2*8+englishSum*6)*2,pL->y0+20-3);
				line(pL->x0,pL->y0+20-2,pL->x0+((strlen(pL->pBox->content)-englishSum+L)/2*8+englishSum*6)*2,pL->y0+20-2);
				englishSum=0;
				p0=pL;
			}
			else if(pL->pBox->parentPointBackFlag==0)
			{
				setcolor(hL->pBox->lastLevelFlag);
				line(pL->x0,pL->y0+20-3,pL->x0+((strlen(pL->pBox->content)-englishSum+L)/2*8+englishSum*6)*2,pL->y0+20-3);
				line(pL->x0,pL->y0+20-2,pL->x0+((strlen(pL->pBox->content)-englishSum+L)/2*8+englishSum*6)*2,pL->y0+20-2);
				englishSum=0;
			}
		}
		pL=pL->next;
	}
	return p0;
}
//寻找所在的一级节点
LINE* traversalLinePointCycle(LINE*hL,int x1,int y1)
{
	LINE*pL=hL;
	int x=0,y=0,mouseX,mouseY;
	mouseX=MouseX-x1;
	mouseY=MouseY-y1;
	while(pL!=NULL)
	{	
		if(pL->pBox->parentPointBackFlag==0)
		{
			if(pow(mouseX-(pL->x0-10-3),2)+pow(mouseY-(pL->y0+8),2)<=16&&pL->pBox->pointFlag==1)
			{
				setcolor(4);
				circle(pL->x0-10-3,pL->y0+8,3);
				x=mouseX;
				y=mouseY;
				return pL;
			}
			if(mouseX!=x&&mouseY!=y&&pL->pBox->pointFlag==1)			
			{
				setcolor(pL->pBox->boxColor);
				circle(pL->x0-10-3,pL->y0+8,3);
			}
		}
		pL=pL->next;
	}
	return pL;
}
//更新大纲界面
void reDrawLineAll(LINE*hL)
{
	int button;
	drawOutlineInterface(hL);
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setviewport(1,20,638,478,1);
	setfillstyle(1,hL->pBox->lastLevelFlag);
	bar(0,0,637,458);
	drawAllLine(hL);
	setviewport(0,0,639,479,1);
	MouseX-=1;
	newmouse(&MouseX,&MouseY,&button);
}
//只画大纲图
void justDrawLine(LINE*hL)
{
	int button;
	drawOutlineInterface(hL);
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setviewport(1,20,638,478,1);
	drawAllLine(hL);
	setviewport(0,0,639,479,1);
	MouseX-=1;
	newmouse(&MouseX,&MouseY,&button);
}
//清除所有大纲数据
void clearAllLine(LINE*hL)
{
	LINE*pL=hL,*pL0=NULL;
	while(pL!=NULL)
	{
		pL0=pL->next;
		free(pL);
		pL=pL0;
	}
}
//画出大纲界面
void drawOutlineInterface(LINE*hL)
{
	int i;
	char *s[]={"编辑","查看","帮助"};
	
	setviewport(0,0,639,479,1);
	setcolor(DFKCOLOR);
	rectangle(0,19,639,479);
	for(i=0;i<3;i++)
	{
		puthz(5+48*i, 1, s[i], 16, 16,HZCOLOR);
	}	
	puthz(420,1,"思维导图",16,16,HZCOLOR);
	puthz(500,1,"大纲",16,16,3);
	settextstyle(1,0,1);
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	setcolor(HZCOLOR);
	outtextxy(548,6,"ZEN");
}
//转换思维导图数据为大纲模式
LINE *transMindMapToOutline(BOX*hB)
{
	LINE *pL=NULL,*hL=NULL,*last=NULL;
	BOX *pB=findEndBox(hB);
	
	while(pB!=NULL)
	{
		if((pL=(LINE*)malloc(sizeof(LINE)*5))==NULL)
		{
			setcolor(0);
			settextjustify(LEFT_TEXT,TOP_TEXT);  
			settextstyle(GOTHIC_FONT,HORIZ_DIR,1);	
			outtextxy(10,10,"No enough memory!Press any key to quit...");
			getch();
			exit(1);
		}
		else
		{
			free(pL);
			pL=NULL;
		}
		
		pL=(LINE*)malloc(sizeof(LINE));
		pL->next=last;
		pL->pBox=pB;
		
		last=pL;
		if(pB==hB)
		{
			hL=pL;
		}
		
		pB=pB->last;
	}
	return hL;
}
//大纲模式数据生成
void lineDataGenerate(LINE*hL)
{
	LINE*pL=hL;
	BOX*pB=NULL;
	int flag=0;
	while(pL!=NULL)
	{
		pB=pL->pBox;
		while(pB!=NULL)
		{
			flag++;
			pB=pB->lastNextBox[0];
		}
		pL->parentSum=flag;
		flag=0;
		pL=pL->next;
	}

	flag=0;
	pL=hL;
	while(pL!=NULL)
	{
		flag++;
		pL->lineFlag=flag;
		pL=pL->next;
	}
}
//画出所有的大纲线
void drawAllLine(LINE*hL)
{
	LINE*pL=hL;
	BOX*pB=NULL;
	renewXY(hL);
	while(pL!=NULL)
	{	
		if(pL->pBox->parentPointBackFlag==0)
		{
			pB=pL->pBox;
			if(pB->content[0]=='\0'&&pB->boldFlag==2)
			{
				puthzcu(pL->x0,pL->y0,"中心主题",16,16,pB->characterColor);//画出字
			}
			else if(pB->content[0]!='\0'&&(pB->boldFlag==1||pB->boldFlag==2))
			{
				puthzcu(pL->x0,pL->y0,pB->content,16,16,pB->characterColor);//画出字
			}
			else if(pB->content[0]=='\0'&&pB->boldFlag==0)
			{
				puthz(pL->x0,pL->y0,"子主题",16,16,pB->characterColor);//画出字
			}
			else if(pB->content[0]=='\0'&&pB->boldFlag==1)
			{
				puthzcu(pL->x0,pL->y0,"子主题",16,16,pB->characterColor);//画出字
			}
			else if(pB->content[0]!='\0'&&pB->boldFlag==0)
			{
				puthz(pL->x0,pL->y0,pB->content,16,16,pB->characterColor);//画出字
			}
			
			setcolor(pL->pBox->boxColor);	
			if(pL->pBox->pointFlag==1)
			{
				circle(pL->x0-10-3,pL->y0+8,3);;//画出节点圈
				line(pL->x0-10-3-3,pL->y0+8,pL->x0-10,pL->y0+8);//画出节点圈的短横线
			}
			if(pL->pBox->pointBackFlag==1)
			{
				setcolor(4);
				line(pL->x0-10-3,pL->y0+8-3,pL->x0-10-3,pL->y0+8+3);
			}
		}
		pL=pL->next;
	}
}
//更新大纲的XY数据
void renewXY(LINE*hL)
{
	LINE*pL=hL->next;
	int lineSum=0;
	while(pL!=NULL)
	{	
		if(pL->pBox->parentPointBackFlag==0)
		{
			lineSum++;
		}
		pL->x0=hL->x0+20*pL->parentSum;
		pL->y0=hL->y0+20*lineSum;
		
		pL=pL->next;
	}
}
//大纲界面的汉字输入
void characterInputInLine(LINE*pLPress)
{
	static BOX*p0=NULL;
	BOX*pPress=pLPress->pBox;
	int a=0,keyValue=0;
	char content0[14]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};//一个汉字装入 
	static char content1[200];
	char py[14]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};//拼音字符串(西文字符串)
	if(strlen(pPress->content)>=80&&bioskey(1)!=BACKSPACE)
	{
		bioskey(0);
		overflowCharacterWarning();
		return;
	}
	if(pPress->content[0]=='\0')
	{
		memset(content1,'\0',sizeof(content1));
	}
	if(bioskey(1)==BACKSPACE&&pPress->content[0]!='\0')
	{
		bioskey(0);
		if(pPress->content[strlen(pPress->content)-1]<127&&pPress->content[strlen(pPress->content)-1]>31)
		{
			pPress->content[strlen(pPress->content)-1]='\0';
		}
		else 
		{
			pPress->content[strlen(pPress->content)-1]='\0';
			pPress->content[strlen(pPress->content)-1]='\0';
		}
		return;
	}
	else if(bioskey(1)==BACKSPACE&&pPress->content[0]=='\0')
	{
		bioskey(0);
		return;
	}
	if(p0!=pPress)
	{
		memset(content1,'\0',sizeof(content1));
		memset(py,'\0',12);
	}
	if(pPress->content[0]!='\0')
	{
		strcpy(content1,pPress->content);
	}
	if(pLPress->x0>640||pLPress->y0>470)
	{
		a=input_method(320-30,240+10,content0,keyValue,py);
	}
	else
	{
		a=input_method(pLPress->x0,pLPress->y0+20,content0,keyValue,py);
	}
	if(a!=3&&a!=0)
	{
		strcat(content1,content0);
		strcpy(pPress->content,content1);
	}
	p0=pPress;
}














