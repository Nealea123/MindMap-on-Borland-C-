#include"MAINHEAD.h"
//���ģʽ��������
int outlineModeFace(BOX*hB)
{
	int flag=0;//����ʶ���
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
		flag=mouseKeyOutlineOperate(hL,&pLine,&pPoint,&pPress);//��ò���ָ��
		switch(flag)//ִ�в���
		{
			case 1://ѡ��һ��
			{
				pressLine(hL,pLine);
				break;
			}
			case 2://ѡ�нڵ�
			{
				pointBackAndClear(hL->pBox,pPoint->pBox);
				break;
			}
			case 6://��������
			{
				characterInputInLine(pPress);
				break;
			}	
			case 8://�˳�
			{
				exitLineAndClear(hL);
				return 8;
			}
			case 9://�ƶ�
			{
				choiceLineDirection(hL,pPress);
				break;
			}
			case 10://�ƶ�����
			{
				moveFaceInLine(hL);
				break;
			}
			case 31://��ݼ�����
			{
				shortcutAssistantInLine(hL);
				break;
			}
			case 11://��ʽ
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
			reDrawLineAll(hL);//��������½���
		}
	}	
}
//���ģʽ������
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
				if(press==1&&(*ppLine!=NULL||*ppPoint!=NULL))//���������
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
				if(bioskey(1)!=0)//���̼������
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
//���ģʽ�����˵�
int dropDownOutlineMenu(LINE*hL)
{
	char *s[]={"�༭","�鿴","����"};
	int b[]={1,3,1,0};
	int c[]={0,1,4,5,0};
	char *z[]={
	"��ʽ",
	"˼ά��ͼ","���","��ģʽ",
	"��ݼ�����",};
	int i=0,j=0,flag=0,a=0,flag0=0,menuXFlag=0,menuYFlag=0;
	for(i=0;i<3;i++)
	{
		if(mouseIn(5+48*i,1,5+48*i+32,19))//һ���˵���(5+28*i,1)-(5+48*i+32,19)
		{
			clrmous(MouseX,MouseY);
			puthz(5+48*i, 1, s[i], 16, 16, THZCOLOR);
			setfillstyle(1,XLCDBACKGOUNDCOLOR);
			bar(5+48*i-2,18,5+48*i-2+80,18+b[i]*20);
			//���(5+48*i-2,18)-(5+48*i+80,18+b[i]*20)
			setcolor(SFKCOLOR);
			rectangle(5+48*i-2,18,5+48*i-2+80,18+b[i]*20);//����(5+48*i-2,18)-(5+48*i+80,18+b[i]*20)
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
		if(!mouseIn(5+48*i,1,5+48*i+32,19))//�˵����ڷ�Χ(5+48*i,1)-(5+48*i+32,19)
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
	
	if(mouseIn(420,1,484,17))//һ���˵���(5+28*i,1)-(5+48*i+32,19)
	{
		clrmous(MouseX,MouseY);
		puthz(420,1,"˼ά��ͼ",16,16,THZCOLOR);
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
			puthz(420,1,"˼ά��ͼ",16,16,HZCOLOR);
		}
	}
	
	if(mouseIn(500,1,532,17))
	{
		clrmous(MouseX,MouseY);
		puthz(500,1,"���",16,16,THZCOLOR);
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
//���ģʽ�Ŀ�ݼ�����
void shortcutAssistantInLine(LINE*hL)
{
	int button,i=0,j=0;
	char *z[]={"��ʽ",
	"˼ά��ͼģʽ","���ģʽ","��ģʽ",
	"��ݼ�����",
	"���ƴ��","���ƴ��","���ƴ��","���ƴ��","��ٹ�λ"};
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
	puthz(225, 350, "����ո���˳���ݼ�����", 16, 16, 0);
	puthz(257, 350, "�ո��", 16, 16, 4);
	
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
//�ƶ���ٽ���
void moveFaceInLine(LINE*hL)
{
	if(bioskey(1)==CTRL_LEFT)//������
	{
		bioskey(0);
		hL->x0=hL->x0-10;
	}
	else if(bioskey(1)==CTRL_RIGHT)//������
	{
		bioskey(0);
		hL->x0=hL->x0+10;
	}
	else if(bioskey(1)==CTRL_UP)//������
	{
		bioskey(0);
		hL->y0=hL->y0-10;
	}
	else if(bioskey(1)==CTRL_DOWN)//������
	{
		bioskey(0);
		hL->y0=hL->y0+10;
	}
	else if(bioskey(1)==CTRL_O)//��λ
	{
		bioskey(0);
		hL->x0=30;
		hL->y0=30;
	}
	renewXY(hL);
}
//ָ�����������ƶ�
void choiceLineDirection(LINE*hL,LINE*pPress)
{
	LINE*pL=NULL;
	if(bioskey(1)==UP&&pPress!=NULL)//����
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
	else if(bioskey(1)==DOWN&&pPress!=NULL)//����
	{
		bioskey(0);
		if(pPress->next!=NULL)
		{
			pressLine(hL,pPress->next);
		}
	}
}
//�˳����ģʽ
void exitLineAndClear(LINE*hL)
{
	clearAllBox(hL->pBox);
	clearAllLine(hL);
}
//���ѡ��һ�������
void pressLine(LINE*hL,LINE*pPress)
{
	clearAllPressBox(hL->pBox);
	pPress->pBox->pressFlag=1;
}
//Ѱ��������ڵ�һ�������
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
//Ѱ��ѡ�е�һ�������
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
//Ѱ�����ڵ�һ���ڵ�
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
//���´�ٽ���
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
//ֻ�����ͼ
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
//������д������
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
//������ٽ���
void drawOutlineInterface(LINE*hL)
{
	int i;
	char *s[]={"�༭","�鿴","����"};
	
	setviewport(0,0,639,479,1);
	setcolor(DFKCOLOR);
	rectangle(0,19,639,479);
	for(i=0;i<3;i++)
	{
		puthz(5+48*i, 1, s[i], 16, 16,HZCOLOR);
	}	
	puthz(420,1,"˼ά��ͼ",16,16,HZCOLOR);
	puthz(500,1,"���",16,16,3);
	settextstyle(1,0,1);
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	setcolor(HZCOLOR);
	outtextxy(548,6,"ZEN");
}
//ת��˼ά��ͼ����Ϊ���ģʽ
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
//���ģʽ��������
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
//�������еĴ����
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
				puthzcu(pL->x0,pL->y0,"��������",16,16,pB->characterColor);//������
			}
			else if(pB->content[0]!='\0'&&(pB->boldFlag==1||pB->boldFlag==2))
			{
				puthzcu(pL->x0,pL->y0,pB->content,16,16,pB->characterColor);//������
			}
			else if(pB->content[0]=='\0'&&pB->boldFlag==0)
			{
				puthz(pL->x0,pL->y0,"������",16,16,pB->characterColor);//������
			}
			else if(pB->content[0]=='\0'&&pB->boldFlag==1)
			{
				puthzcu(pL->x0,pL->y0,"������",16,16,pB->characterColor);//������
			}
			else if(pB->content[0]!='\0'&&pB->boldFlag==0)
			{
				puthz(pL->x0,pL->y0,pB->content,16,16,pB->characterColor);//������
			}
			
			setcolor(pL->pBox->boxColor);	
			if(pL->pBox->pointFlag==1)
			{
				circle(pL->x0-10-3,pL->y0+8,3);;//�����ڵ�Ȧ
				line(pL->x0-10-3-3,pL->y0+8,pL->x0-10,pL->y0+8);//�����ڵ�Ȧ�Ķ̺���
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
//���´�ٵ�XY����
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
//��ٽ���ĺ�������
void characterInputInLine(LINE*pLPress)
{
	static BOX*p0=NULL;
	BOX*pPress=pLPress->pBox;
	int a=0,keyValue=0;
	char content0[14]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};//һ������װ�� 
	static char content1[200];
	char py[14]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};//ƴ���ַ���(�����ַ���)
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














