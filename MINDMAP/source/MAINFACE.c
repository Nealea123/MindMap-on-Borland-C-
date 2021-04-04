#include"MAINHEAD.h"

//主界面操作执行
int mainInterface(BOX*h,User*pUser)
{
	int flag=0;//操作识别符
	BOX*pBox=NULL,*pPoint=NULL,*pPress=NULL;//一级指针
	MAPF*hM=NULL;
	static MAPF*cM=NULL;
	
	setviewport(0,0,639,479,1);
	setfillstyle(1,XLCDBACKGOUNDCOLOR);
	bar(0,0,639,479);
	setfillstyle(1,h->lastLevelFlag);
	bar(1,20,638,478);
	MouseS=4;
	
	
	readMoreMindmapFile(pUser,&hM);

	drawMainInterface();//画主界面
	renewAllBox(h,1,20,638,478);
	
	while(1)
	{
		flag=mouseKeyMainOperate(h,&pBox,&pPoint,&pPress,cM);//获得操作指令
		switch(flag)//执行操作
		{
			case 1://选中一级
			{
				pressBox(h,pBox);break;
			}
			case 2://选中节点
			{
				pointBackAndClear(h,pPoint);break;
			}
			case 3:case 7:case 31://开节点并生成下一级
			{
				openPointAndNextBox(h,pPress);break;
			}
			case 4:case 32://生成同一级
			{
				boxDataStorage(h,pPress,1);break;
			}
			case 5:case 21://删除一级
			{
				deleteBox(h,&pPress);break;
			}
			case 6://汉字输入
			{
				characterInput(pPress);break;
			}	
			case 8:case 14://退出
			{
				exitAndClear(h);return 8;
			}
			case 9://移动
			{
				choiceDirection(h,&pPress);break;
			}
			case 11://新建
			{
				closeMindmap(h,hM,&cM);break;
			}
			case 12://打开
			{
				openMindmap(h,hM,&cM);break;
			}
			case 13://保存
			{
				saveMindmap(h,hM,&cM);break;
			}
			case 10://移动界面
			{
				moveFace(h);break;
			}
			case 33://生成上一级
			{
				boxDataStorage(h,pPress,2);break;
			}
			case 34://生成父级
			{
				boxDataStorage(h,pPress,3);break;
			}
			case 52://快捷键助手
			{
				shortcutAssistant(h);break;
			}
			case 22://样式
			{
				boxType(h,pPress);break;
			}
			case 51://新手指导
			{
				newGuidance(h,pPress);break;
			}
			case 42://进入大纲模式
			{
				clrmous(MouseX,MouseY);
				return 7;
			}
			case 43://进入ZEN模式
			{
				clrmous(MouseX,MouseY);
				return 5;
				
			}
		}
		if(flag!=1&&flag!=9)
		{
			renewAllBox(h,1,20,638,478);//互动后更新界面
		}
	}	
}
//主界面功能选择
int mouseKeyMainOperate(BOX*h,BOX**ppBox,BOX**ppPoint,BOX**ppPress,MAPF*cM)
{
	int button=0,onePress=0,menuFlag=0,flag=0;
	MAPF*cM1=NULL;
	while(1)
	{
		setviewport(0,0,639,479,1);
		if(cM1!=cM||cM==NULL)
		{
			setfillstyle(1,15);
			bar(237,1,400,18);
		}
		if(cM!=NULL)
		{
			line(237,1,237,17);
			puthz(240,1,cM->mindmapFileName,16,16,0);
			cM1=cM;
		}
		if(MouseX<=638&&MouseY>=20)
		{
			setviewport(1,20,638,478,1);
			drawAllBox(h);
			while(MouseX<=638&&MouseY>=20)
			{	
				setviewport(0,0,639,479,1);
				newmouse(&MouseX,&MouseY,&button);
				if(cM1!=cM&&cM==NULL)
				{
					bar(237,1,400,18);
				}
				if(cM!=NULL)
				{
					line(237,1,237,17);
					puthz(240,1,cM->mindmapFileName,16,16,0);
					cM1=cM;
				}
				
				setviewport(1,20,638,478,1);
				*ppBox=traversalBoxCycle(h,1,20,h->lastLevelFlag);
				*ppPress=traversalPressBox(h,h->lastLevelFlag);
				*ppPoint=traversalPointCycle(h,1,20);
				
				setviewport(0,0,639,479,1);
				if(press==1&&(*ppBox!=NULL||*ppPoint!=NULL))//鼠标点击操作
				{
					delay(300);
					onePress=1;
				}
				if(onePress==1)
				{
					onePress=0;
					if(*ppBox!=NULL)
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
						if(flag==1)
						{
							return 8;
						}
						else 
						{
							setviewport(1,20,638,478,1);
							drawAllBox(h);
							continue;
						}
					}
					else if(bioskey(1)==TAB&&(*ppPress)!=NULL&&(*ppPress)->pointBackFlag==0)
					{
						bioskey(0);					
						return 3;
					}
					else if(bioskey(1)==ENTER&&(*ppPress)!=NULL)
					{
						bioskey(0);
						return 4;
					}
					else if(bioskey(1)==DELETE&&(*ppPress)!=NULL&&(*ppPress)!=h)
					{
						bioskey(0);
						return 5;
					}
					else if(bioskey(1)==TAB&&(*ppPress)!=NULL&&(*ppPress)->pointBackFlag==1)
					{
						bioskey(0);
						return 7;
					}
					else if(bioskey(1)==CTRL_LEFT||bioskey(1)==CTRL_RIGHT||bioskey(1)==CTRL_DOWN||bioskey(1)==CTRL_UP||bioskey(1)==CTRL_O)
					{
						return 10;	
					}
					else if(bioskey(1)==CTRL_ENTER)
					{
						bioskey(0);
						return 33;
					}
					else if(bioskey(1)==CTRL_F&&(*ppPress)!=NULL&&(*ppPress)!=h)
					{
						bioskey(0);
						return 34;
					}
					else if(bioskey(1)==CTRL_N)
					{
						bioskey(0);
						return 11;
					}
					else if(bioskey(1)==CTRL_U)
					{
						bioskey(0);
						return 12;
					}
					else if(bioskey(1)==CTRL_S)
					{
						bioskey(0);
						return 13;
					}
					else if(bioskey(1)==CTRL_M)
					{
						bioskey(0);
						return 41;
					}
					else if(bioskey(1)==CTRL_B)
					{
						bioskey(0);
						return 42;
					}
					else if(bioskey(1)==CTRL_Z)
					{
						bioskey(0);
						return 43;
					}
					else if(bioskey(1)==CTRL_H)
					{
						bioskey(0);
						return 51;
					}
					else if(bioskey(1)==CTRL_A)
					{
						bioskey(0);
						return 52;
					}
					else if(bioskey(1)==CTRL_T)
					{
						bioskey(0);
						return 22;
					}
					else if((bioskey(1)==UP||bioskey(1)==LEFT||bioskey(1)==DOWN||bioskey(1)==RIGHT)&&(*ppPress)!=NULL)
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
				*ppPress=traversalPressBox(h,h->lastLevelFlag);
				
				setviewport(0,0,639,479,1);
				newmouse(&MouseX,&MouseY,&button);
				
				
				menuFlag=dropDownMainMenu(h);
				if(mouse_press(420,1,484,17)==1)
				{
					return 41;
				}
				if(mouse_press(500,1,532,17)==1)
				{
					return 42;
				}
				if(mouse_press(548,6,568,17)==1)
				{
					return 43;
				}
				setviewport(0,0,639,479,1);
				puthz(420,1,"思维导图",16,16,3);
				puthz(500,1,"大纲",16,16,HZCOLOR);
				settextstyle(1,0,1);
				settextjustify(LEFT_TEXT,CENTER_TEXT);
				setcolor(HZCOLOR);
				outtextxy(548,6,"ZEN");
				
				if(menuFlag>=11)
				{
					return menuFlag;
				}
			} 
			clrmous(MouseX,MouseY);
		}	
	}
}
//主界面下拉菜单
int dropDownMainMenu(BOX*h)
{
	char *s[]={"文件","编辑","插入","查看","帮助"};
	int b[]={4,2,4,3,2,0,0};
	int c[]={0,4,6,10,13,15,0};
	char *z[]={"新建","打开","保存","退出","删除","样式","子主题","主题之后","主题之前","父主题","思维导图","大纲","ZEN模式","入门指导","快捷键助手",};
	int i=0,j=0,flag=0,flag0=10,a=0,menuXFlag=0,menuYFlag=0;
	for(i=0;i<5;i++)
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
							setfillstyle(1,h->lastLevelFlag);
							bar(3,19,275,138);
							reDrawAll(h);
							clrmous(MouseX,MouseY);
							setcolor(15);
							line(3,18,275,18);
							if(menuXFlag*10+menuYFlag==14)
							{
								flag0=exitYesOrNo();
								if(flag0==0)
								{
									setviewport(1,20,638,478,1);
									drawAllBox(h);
									return 1;
								}
							}
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
				setfillstyle(1,h->lastLevelFlag);
				bar(3,19,275,138);
				reDrawAll(h);
				clrmous(MouseX,MouseY);
				setcolor(15);
				line(3,18,275,18);
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
				return 41;
			}
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
				return 42;
			}
		}
		if(mouseIn(500,1,532,17)==0)
		{
			clrmous(MouseX,MouseY);
			puthz(500,1,"大纲",16,16,HZCOLOR);
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
				return 43;
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
}//dropDownMainMenu
//画出主界面
void drawMainInterface()
{
	int i;
	char *s[]={"文件","编辑","插入","查看","帮助"};
	
	setviewport(0,0,639,479,1);
	setcolor(DFKCOLOR);
	rectangle(0,19,639,479);
	for(i=0;i<5;i++)
	{
		puthz(5+48*i, 1, s[i], 16, 16,HZCOLOR);
	}	
	puthz(420,1,"思维导图",16,16,3);
	puthz(500,1,"大纲",16,16,HZCOLOR);
	settextstyle(1,0,1);
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	setcolor(HZCOLOR);
	outtextxy(548,6,"ZEN");
}
//移动思维导图界面
void moveFace(BOX*h)
{
	//ctrl+[=6683 1a1b   ctrl+]=6941 1b1d
	//ctrl+\= 2b1c   ctrl+-=3103 0c1f
	if(bioskey(1)==CTRL_LEFT)//向左移
	{
		bioskey(0);
		h->centerX=h->centerX-10;
	}
	else if(bioskey(1)==CTRL_RIGHT)//向右移
	{
		bioskey(0);
		h->centerX=h->centerX+10;
	}
	else if(bioskey(1)==CTRL_UP)//向上移
	{
		bioskey(0);
		h->centerY=h->centerY-10;
	}
	else if(bioskey(1)==CTRL_DOWN)//向下移
	{
		bioskey(0);
		h->centerY=h->centerY+10;
	}
	else if(bioskey(1)==CTRL_O)//归位
	{
		bioskey(0);
		h->centerX=70;
		h->centerY=230;
	}
}
//快捷键助手弹出
void shortcutAssistant(BOX*h)
{
	int button,i=0,j=0;
	char *z[]={"新建文件","打开文件","最近打开","保存","关闭","退出","删除","插入子主题","插入主题之后","插入主题之前","插入父主题","思维导图模式","大纲模式","真模式","入门指导","快捷键助手","左移导图","右移导图","上移导图","下移导图","导图归位"};
	char *e[]={"Ctrl+N","Ctrl+U","Ctrl+R","Ctrl+S","Ctrl+C","Esc","Delete","Tab","Enter","Ctrl+Enter","Ctrl+F","Ctrl+M","Ctrl+B","Ctrl+Z","Ctrl+H","Ctrl+A","Ctrl+[","Ctrl+]","Ctrl+-","Ctrl+\\","Ctrl+O"};
	
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setfillstyle(1,XLCDBACKGOUNDCOLOR);
	bar(220,20,420,470);
	setcolor(8);
	rectangle(220,20,420,470);
	for(i=0;i<21;i++)
	{
		if(i==6||i==7||i==11||i==14||i==16)
		{
			j++;
		}
		puthz(225, 25+i*18+8*j, z[i], 16, 16, j);
		setcolor(j);
		settextjustify(LEFT_TEXT,TOP_TEXT);
		settextstyle(0,0,1);
		outtextxy(330, 30+i*18+8*j, e[i]);
	}
	puthz(225, 450, "点击空格键退出快捷键助手", 16, 16, 0);
	puthz(257, 450, "空格键", 16, 16, 4);
	
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
	reDrawAll(h);
}
//更新思维导图主界面
void reDrawAll(BOX*h)
{
	int button;
	drawMainInterface();
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setviewport(1,20,638,478,1);
	boxDataGenerate(h);//生成所有方框的所有数据
	drawAllBox(h);//画出所有的方框
	setviewport(0,0,639,479,1);
	MouseX-=1;
	newmouse(&MouseX,&MouseY,&button);
}
//画出新手指导弹出框
void drawNewGuidance(int a)
{
	int i=0;
	char *s[]={"欢迎使用M indM ap。根据我的指引 ","，你可以通过键盘 3 步实现一张思维导","图。如果你想稍后再尝试，你可以在“ 帮","助 ”中找到它。","那么，第一步我们选择了一个主题，然后尝","试点击Tab。"," ",//7
	"做的不错。现在你添加了一个子主题。","然后点击Enter。"," ",//3
	"很好。你现在添加了一个同级主题。","最后一步，输入拼音，在这个主题上输入你","的想法。"," ",//4
	"很好，你做到了，你现在可以随意创建自己","的思维导图了。"};//2
	
	settextjustify(LEFT_TEXT,TOP_TEXT);
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setfillstyle(1,XLCDBACKGOUNDCOLOR);
	bar(320,130,639,479);
	setcolor(8);
	rectangle(320,130,639,479);
	
	for(i=0;i<a;i++)
	{
		puthz(330, 140+20*i, s[i], 16, 16, 0);
	}
	if(a==7)
	{
		puthz(394, 140, "M indM ap", 16, 16, 4);
		puthz(474, 160, "3", 16, 16, 4);
		puthz(378, 240, "Tab", 16, 16, 4);
	}
	if(a==10)
	{
		puthz(394, 300, "Enter", 16, 16, 4);
	}
	if(a==13)
	{
		puthz(442, 360, "拼音", 16, 16, 4);
	}
}
//新手指导弹出框引导
void newGuidance(BOX*h,BOX*pPress)
{
	int button;
	int flag[4]={0,0,0,0};
	
	if(pPress==NULL)
	{
		setviewport(0,0,639,479,1);
		clrmous(MouseX,MouseY);
		setcolor(15);
		bar(120,200,520,280);
		setcolor(8);
		rectangle(120,200,520,280);
		
		
		puthz(130, 210, "未选中子主题，请选中子主题后，再开启入门指导...", 16, 16, 0);
		puthz(255, 260, "点击空格键退出提醒", 16, 16, 0);
		puthz(287, 260, "空格键", 16, 16, 4);
		
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
	drawNewGuidance(7);
	while(bioskey(1)!=SPACE)
	{
		if(bioskey(1)==TAB&&pPress!=NULL&&pPress->pointBackFlag==0&&flag[0]==0)
		{
			bioskey(0);
			openPointAndNextBox(h,pPress);
			pressBox(h,pPress->next);
			pPress=pPress->next;
			renewAllBox(h,1,20,638,478);
			setviewport(1,20,638,478,1);
			traversalPressBox(h,h->lastLevelFlag);
			setviewport(0,0,639,479,1);
			drawNewGuidance(10);
			flag[0]=1;
		}
		else if(bioskey(1)==ENTER&&pPress!=NULL&&flag[0]==1&&flag[1]==0)
		{
			bioskey(0);
			boxDataStorage(h,pPress,1);
			pressBox(h,pPress->next);
			pPress=pPress->next;
			renewAllBox(h,1,20,638,478);
			setviewport(1,20,638,478,1);
			traversalPressBox(h,h->lastLevelFlag);
			setviewport(0,0,639,479,1);
			drawNewGuidance(13);
			flag[1]=1;
		}
		else if(bioskey(1)!=0&&pPress!=NULL&&flag[1]==1&&flag[2]==0)
		{
			characterInput(pPress);
			renewAllBox(h,1,20,638,478);
			setviewport(1,20,638,478,1);
			traversalPressBox(h,h->lastLevelFlag);
			setviewport(0,0,639,479,1);
			drawNewGuidance(16);
			flag[2]=1;
			
			puthz(370, 460, "点击空格键退出快捷键助手", 16, 16, 0);
			puthz(402, 460, "空格键", 16, 16, 4);
		}
		else if(bioskey(1)==ESC)
		{
			return;
		}
		else if(bioskey(1)!=0)
		{
			bioskey(0);
		}
		newmouse(&MouseX,&MouseY,&button);
	}
}
//方框样式更改
void boxType(BOX*h,BOX*pPress)
{
	int button,i=0,j=0;
	int flag[6]={0,0,0,0,0,0};
	BOX*p=h,*p0=NULL;
	if(pPress!=NULL)
	{
		if(pPress->boldFlag==0)
		{
			flag[2]=1;
		}
		flag[1]=pPress->characterSize/8-2;
		flag[3]=pPress->characterColor;
		flag[4]=pPress->boxColor;
		flag[5]=h->lastLevelFlag;
	}
	else
	{
		flag[0]=1;
		flag[1]=0;
		flag[2]=0;
		flag[3]=0;
		flag[4]=8;
		flag[5]=15;
	}
	
	settextjustify(LEFT_TEXT,TOP_TEXT);
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	
	drawNewBoxTypeMenu(flag);
	while(bioskey(1)!=SPACE)
	{
		for(i=0;i<2;i++)
		{
			if(mouse_press(160+140*i, 133,170+140*i, 143)==1)
			{
				delay(200);
				flag[0]=i;
				if(pPress==NULL)
					flag[0]=1;
				else
					drawNewBoxTypeMenu(flag);
			}
			if(mouse_press(160+140*i, 173,170+140*i, 183)==1)
			{
				delay(200);
				flag[1]=i;
				drawNewBoxTypeMenu(flag);
			}
			if(mouse_press(160+140*i, 213,170+140*i, 223)==1)
			{
				delay(200);
				flag[2]=i;
				drawNewBoxTypeMenu(flag);
			}
		}
		if(mouse_press(440, 133,450, 143)==1)
		{
			delay(200);
			flag[0]=2;
			if(pPress==NULL)
				flag[0]=1;
			else
				drawNewBoxTypeMenu(flag);
		}
		for(i=0;i<3;i++)
		{  
			for(j=0;j<16;j++)
			{
				if(mouse_press(160+20*j-1,250+i*40-1,170+20*j+1,260+i*40+1)==1)
				{
					delay(200);
					if(i==0)
					{
						flag[3]=j;
						drawNewBoxTypeMenu(flag);
					}
					else if (i==1)
					{
						flag[4]=j;
						drawNewBoxTypeMenu(flag);
					}
					else if (i==2)
					{
						flag[5]=j;
						drawNewBoxTypeMenu(flag);
					}
				}
			}
		}
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
	if(flag[0]==0)
	{
		if(pPress!=NULL)
		{
			if(pPress!=h)
			{
				if(flag[2]==0)
				{
					pPress->boldFlag=1;
				}
				else if(flag[2]==1)
				{
					pPress->boldFlag=0;
				}
					
			}
			pPress->characterSize=(flag[1]+2)*8;
			pPress->characterColor=flag[3];
			pPress->boxColor=flag[4];
		}
	}
	else if(flag[0]==1)
	{
		while(p!=NULL)
		{
			if(p!=h)
			{
				if(flag[2]==0)
				{
					p->boldFlag=1;
				}
				else if(flag[2]==1)
				{
					p->boldFlag=0;
				}
			}
			p->characterSize=(flag[1]+2)*8;
			p->characterColor=flag[3];
			p->boxColor=flag[4];
			p=p->next;
		}
		h->characterNewColor=flag[3];
		h->boxNewColor=flag[4];
	}
	else if(flag[0]==2)
	{
		while(p!=NULL)
		{
			p0=p;
			while(p0!=NULL)
			{
				if(p0==pPress)
				{
					if(p!=h)
					{
						if(flag[2]==0)
						{
							p->boldFlag=1;
						}
						else if(flag[2]==1)
						{
							p->boldFlag=0;
						}
					}
					p->characterSize=(flag[1]+2)*8;
					p->characterColor=flag[3];
					p->boxColor=flag[4];
				}
				p0=p0->lastNextBox[0];
			}
			p=p->next;
		}
	}
	h->lastLevelFlag=flag[5];
}
//画出样式更改弹出框
void drawNewBoxTypeMenu(int*flag)
{
	int i=0,j=0;
	char *z[]={"样式更改范围","字体大小","字体是否加粗","字体颜色","方框及子级线颜色","背景颜色"};
	char *s[]={"当前选中","16*16","是","完成","取消"};
	char *d[]={"所有一级","24*24","否"};
	settextjustify(LEFT_TEXT,TOP_TEXT);
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setfillstyle(1,XLCDBACKGOUNDCOLOR);
	bar(150,100,540,380);
	setcolor(8);
	rectangle(150,100,540,380);
	
	for(i=0;i<6;i++)
	{
		puthz(160, 110+i*40, z[i], 16, 16, 0);
	}
	for(i=0;i<3;i++)
	{
		setcolor(8);
		rectangle(160, 133+i*40,170, 143+i*40);
		puthz(175, 130+i*40, s[i], 16, 16, 8);
		
		setcolor(8);
		rectangle(300, 133+i*40,310, 143+i*40);
		puthz(315, 130+i*40, d[i], 16, 16, 8);
		
	}
	setcolor(8);
	rectangle(440, 133,450, 143);
	puthz(455, 130, "之后子级", 16, 16, 8);
	for(i=0;i<3;i++)
	{  
		for(j=0;j<16;j++)
		{
			setfillstyle(1,j);
			bar(160+20*j,250+i*40,170+20*j,260+i*40);
			setcolor(8);
			rectangle(160+20*j-1,250+i*40-1,170+20*j+1,260+i*40+1);
		}
	}
	puthz(240, 360, "点击空格键完成样式编辑", 16, 16, 0);
	puthz(272, 360, "空格键", 16, 16, 4);
	
	if(flag[0]==0)
	{
		drawGo(165,140,0);
	}
	else if(flag[0]==1)
	{
		drawGo(305,140,0);
	}
	else if(flag[0]==2)
	{
		drawGo(445,140,0);
	}
	if(flag[1]==0)
	{
		drawGo(165,180,0);
	}
	else
	{
		drawGo(305,180,0);
	}
	if(flag[2]==0)
	{
		drawGo(165,220,0);
	}
	else
	{
		drawGo(305,220,0);
	}
	if(flag[3]==0)
	{
		drawGo(165+20*flag[3],257,1);
	}
	else
	{
		drawGo(165+20*flag[3],257,0);
	}
	if(flag[4]==0)
	{
		drawGo(165+20*flag[4],297,1);
	}
	else
	{
		drawGo(165+20*flag[4],297,0);
	}
	if(flag[5]==0)
	{
		drawGo(165+20*flag[5],337,1);
	}
	else
	{
		drawGo(165+20*flag[5],337,0);
	}		
}
//画一个选择勾
void drawGo(int x,int y,int color)
{
	setcolor(color);
	line(x,y,x-5,y-5);
	line(x,y,x+10,y-10);
}
//鼠标所在函数
int mouseIn(int x1,int y1,int x2,int y2)
{
	if(MouseX >= x1 
	&&MouseY >=y1
	&&MouseX <=x2 
	&&MouseY <=y2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//字符已达上限提醒
void Character8Warning()
{
	int button;
	
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setfillstyle(1,15);
	bar(120,200,520,280);
	setcolor(8);
	rectangle(120,200,520,280);
	
	puthz(150, 210, "字符已达上限，请删除一些字符", 16, 16, 0);
	puthz(255, 260, "点击空格键退出提醒", 16, 16, 0);
	puthz(287, 260, "空格键", 16, 16, 4);
	
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
//是否退出程序弹出框
int exitYesOrNo()
{
	int a=0;
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setfillstyle(1,15);
	bar(240,210,400,270);
	setcolor(8);
	rectangle(240,210,400,270);
	
	puthz(260, 220, "确定退出程序?", 16, 16, 0);
	puthz(260, 250, "确定", 16, 16, 0);
	puthz(360, 250, "取消", 16, 16, 0);
	
	while(bioskey(1)!=SPACE)
	{
		if(bioskey(1)!=0&&bioskey(1)!=SPACE&&bioskey(1)!=ESC)
		{	
			bioskey(0);
		}
		if(mouseIn(260, 240,300,260))
		{
			clrmous(MouseX,MouseY);
			puthz(260, 250, "确定", 16, 16, THZCOLOR);
			MouseX--;MouseY--;
			newmouse(&MouseX,&MouseY,&a);
			while(mouseIn(260, 240,300,260))
			{
				newmouse(&MouseX,&MouseY,&a);
				if(press==1)
				{
					clrmous(MouseX,MouseY);
					setfillstyle(1,15);
					bar(240,210,400,270);
					return 1;
				}
			}
			if(mouseIn(260, 240,300,260)==0)
			{
				clrmous(MouseX,MouseY);
				puthz(260, 250, "确定", 16, 16, 0);
			}
		}
		if(mouseIn(360, 240,400,260))
		{
			clrmous(MouseX,MouseY);
			puthz(360, 250, "取消", 16, 16, THZCOLOR);
			MouseX--;MouseY--;
			newmouse(&MouseX,&MouseY,&a);
			while(mouseIn(360, 240,400,260))
			{
				newmouse(&MouseX,&MouseY,&a);
				if(press==1)
				{
					clrmous(MouseX,MouseY);
					setfillstyle(1,15);
					bar(240,210,400,270);
					return 0;
				}
			}
			if(mouseIn(360, 240,400,260)==0)
			{
				clrmous(MouseX,MouseY);
				puthz(360, 250, "取消", 16, 16, 0);
			}
		}
		newmouse(&MouseX,&MouseY,&a);
	}
	clrmous(MouseX,MouseY);
	setfillstyle(1,15);
	bar(240,210,400,270);
}
















