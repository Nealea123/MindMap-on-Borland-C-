#include"MAINHEAD.h"

//生成第一级结构体数据
BOX *boxData0Generate()
{
	static BOX head;
	BOX *h=&head;
	h->centerX=90;	
	h->centerY=230;
	h->boxX=60;
	h->boxY=20;
	h->lineX=7;
	h->lineY=0;
	h->lastLevelFlag=15;
	h->pointFlag=0;
	h->pressFlag=1;
	h->parentPointBackFlag=0;
	h->pointBackFlag=0;
	h->boldFlag=2;
	h->boxColor=8;
	h->boxNewColor=8;
	h->characterColor=0;
	h->characterNewColor=0;
	h->characterSize=24;
	h->nextLevelSum=0;
	h->lastLevelSum=0;
	h->nextAllSum=0;
	h->content[0]='\0';
	h->lastNextBox[0]=NULL;
	h->next=NULL;
	h->last=NULL;
	h->lastFile=h;
	return h;
}
//找到最后一级结构体数据
BOX *findEndBox(BOX*h)
{
	BOX*p=NULL;
	p=h;
	while(p->next!=NULL)//遍历循环，依次生成一级结构体其他初始数据
	{
		p=p->next;
	}
	return p;
}
//找到鼠标所在一级框
BOX *traversalBoxCycle(BOX*h,int x1,int y1,int color)
{
	BOX*p=h;
	int mouseX,mouseY;
	mouseX=MouseX-x1;
	mouseY=MouseY-y1;
	while(p!=NULL)
	{	
		if(p->parentPointBackFlag==0)
		{
			if(mouseX <= p->centerX + p->boxX && mouseX >= p->centerX - p->boxX && mouseY <= p->centerY + p->boxY && mouseY >= p->centerY - p->boxY)
			{
				setcolor(SFKCOLOR);
				drawSmallOutBox(p);
				return p;
			}
			else
			{
				setcolor(color);
				drawSmallOutBox(p);
			}	
		}
		p=p->next;
	}
	return p;
}

void drawSmallOutBox(BOX*p)
{
	line(p->centerX-p->boxX-1,p->centerY-p->boxY-1,p->centerX+p->boxX+1,p->centerY-p->boxY-1);
	line(p->centerX-p->boxX-1,p->centerY+p->boxY+1,p->centerX+p->boxX+1,p->centerY+p->boxY+1);
	
	line(p->centerX-p->boxX-1,p->centerY-p->boxY-1,p->centerX-p->boxX-1,p->centerY-3);
	line(p->centerX-p->boxX-1,p->centerY+3,p->centerX-p->boxX-1,p->centerY+p->boxY+1);
	
	line(p->centerX+p->boxX+1,p->centerY-p->boxY-1,p->centerX+p->boxX+1,p->centerY-3);
	line(p->centerX+p->boxX+1,p->centerY+3,p->centerX+p->boxX+1,p->centerY+p->boxY+1);
}

//找到鼠标所在节点
BOX *traversalPointCycle(BOX*h,int x1,int y1)
{
	BOX*p=h;
	int x=0,y=0,mouseX,mouseY;
	mouseX=MouseX-x1;
	mouseY=MouseY-y1;
	while(p!=NULL)
	{	
		if(p->parentPointBackFlag==0)
		{
			if(pow(mouseX-(p->centerX+p->boxX+p->lineX-3),2)+pow(mouseY-p->centerY,2)<=16&&p->pointFlag==1)
			{
				setcolor(4);
				circle(p->centerX+p->boxX+p->lineX-3,p->centerY,3);//画出节点圈
				x=mouseX;
				y=mouseY;
				return p;
			}
			if(mouseX!=x&&mouseY!=y&&p->pointFlag==1)			
			{
				setcolor(p->boxColor);
				circle(p->centerX+p->boxX+p->lineX-3,p->centerY,3);//画出节点圈
			}
		}
		p=p->next;
	}
	return p;
}
//找到已被选中一级框
BOX *traversalPressBox(BOX*h,int color)
{
	
	BOX*p=h,*p0=NULL;
	while(p!=NULL)
	{
		if(p->pressFlag==1&&p->parentPointBackFlag==0)
		{
			setcolor(SFKCOLOR);
			drawOutBox(p);	
			p0=p;
		}
		else if(p->parentPointBackFlag==0)
		{
			setcolor(color);
			drawOutBox(p);	
		}
		p=p->next;
	}
	return p0;
}

void drawOutBox(BOX*p)
{
	line(p->centerX-p->boxX-2,p->centerY-p->boxY-2,p->centerX+p->boxX+2,p->centerY-p->boxY-2);
	line(p->centerX-p->boxX-2,p->centerY+p->boxY+2,p->centerX+p->boxX+2,p->centerY+p->boxY+2);
	
	line(p->centerX-p->boxX-2,p->centerY-p->boxY-2,p->centerX-p->boxX-2,p->centerY-5);
	line(p->centerX-p->boxX-2,p->centerY+5,p->centerX-p->boxX-2,p->centerY+p->boxY+2);
	
	line(p->centerX+p->boxX+2,p->centerY-p->boxY-2,p->centerX+p->boxX+2,p->centerY-5);
	line(p->centerX+p->boxX+2,p->centerY+5,p->centerX+p->boxX+2,p->centerY+p->boxY+2);
	
	line(p->centerX-p->boxX-3,p->centerY-p->boxY-3,p->centerX+p->boxX+3,p->centerY-p->boxY-3);
	line(p->centerX-p->boxX-3,p->centerY+p->boxY+3,p->centerX+p->boxX+3,p->centerY+p->boxY+3);
	
	line(p->centerX-p->boxX-3,p->centerY-p->boxY-3,p->centerX-p->boxX-3,p->centerY-5);
	line(p->centerX-p->boxX-3,p->centerY+5,p->centerX-p->boxX-3,p->centerY+p->boxY+3);
	
	line(p->centerX+p->boxX+3,p->centerY-p->boxY-3,p->centerX+p->boxX+3,p->centerY-5);
	line(p->centerX+p->boxX+3,p->centerY+5,p->centerX+p->boxX+3,p->centerY+p->boxY+3);
}

//清除被选中的一级框 
void clearAllPressBox(BOX*h) 
{
	BOX*p=h;
	while(p!=NULL)
	{
		p->pressFlag=0;
		p=p->next;
	}
}
//移动一级框
void choiceDirection(BOX*h,BOX**ppPress)
{
	if(bioskey(1)==UP&&(*ppPress)!=NULL)//向上
	{
		bioskey(0);
		if((*ppPress)->lastLevelFlag!=1&&((*ppPress)->lastNextBox[0])!=NULL&&((*ppPress)->lastNextBox[0])->lastNextBox[(*ppPress)->lastLevelFlag-1]!=NULL)
		{
			clearAllPressBox(h);
			(*ppPress)=((*ppPress)->lastNextBox[0])->lastNextBox[(*ppPress)->lastLevelFlag-1];
			(*ppPress)->pressFlag=1;
		}
	}
	else if(bioskey(1)==DOWN&&(*ppPress)!=NULL)//向下
	{
		bioskey(0);
		if((*ppPress)->lastLevelFlag!=(*ppPress)->lastLevelSum&&((*ppPress)->lastNextBox[0])!=NULL&&((*ppPress)->lastNextBox[0])->lastNextBox[(*ppPress)->lastLevelFlag+1]!=NULL)
		{
			clearAllPressBox(h);
			(*ppPress)=((*ppPress)->lastNextBox[0])->lastNextBox[(*ppPress)->lastLevelFlag+1];
			(*ppPress)->pressFlag=1;
		}
	}
	else if(bioskey(1)==LEFT&&(*ppPress)!=NULL)//向左
	{
		bioskey(0);
		if(((*ppPress)->lastNextBox[0])!=NULL)
		{
			clearAllPressBox(h);
			(*ppPress)=(*ppPress)->lastNextBox[0];
			(*ppPress)->pressFlag=1;
		}
	}
	else if(bioskey(1)==RIGHT&&(*ppPress)!=NULL)//向右
	{
		bioskey(0);
		if(((*ppPress)->lastNextBox[1])!=NULL)
		{
			clearAllPressBox(h);
			(*ppPress)=(*ppPress)->lastNextBox[1];
			(*ppPress)->pressFlag=1;
		}
	}
}
//收放节点
void pointBack(BOX*h,BOX*p)
{
	BOX*p1=NULL,*p2=NULL,*p0=NULL;
	int flag=0;
	if(p->pointBackFlag==0)//收回
	{
		p->pointBackFlag=1;
		p1=h;
		while(p1!=NULL)
		{
			p2=p1;
			while(p2!=NULL)//判断是否为p的后级
			{
				if(p2==p)
				{
					flag=1;//为p的后级
					break;
				}
				p2=p2->lastNextBox[0];//找父级
			}
			
			if(flag==1)
			{
				p1->parentPointBackFlag=1;
				flag=0;
			}
			p1=p1->next;
		}
		p->parentPointBackFlag=0;
	}
	else//放开
	{
		p->pointBackFlag=0;
		p1=h;
		while(p1!=NULL)
		{
			p2=p1;
			while(p2!=NULL)//判断是否为p的后级
			{
				if(p2==p)
				{
					flag=1;//为p的后级
					break;
				}
				p2=p2->lastNextBox[0];//找父级
			}
			
			if(flag==1)
			{
				p1->parentPointBackFlag=0;
				
				p0=p1->lastNextBox[0];
				while(p0!=NULL)
				{
					if(p0->pointBackFlag==1)
					{   
						p1->parentPointBackFlag=1;
					}
					p0=p0->lastNextBox[0];//找父级
				}
				
				flag=0;
			}
			p1=p1->next;
		}
		p->parentPointBackFlag=0;
	}
}
//储存一级结构体基本数据
void boxDataStorage(BOX*h,BOX*p,int flag)
{	
	BOX *front=NULL,*p0=p;
	int a,b,i;
	if(flag==0||flag==1||flag==2||flag==3)
	{
		if(flag==1&&p!=h)//enter
		{
			if(p->lastNextBox[0]->nextLevelSum==25)
			{
				overflow26Warning();
				return;
			}
			front=p->lastNextBox[0];
			
			if(p0->lastLevelFlag<front->nextLevelSum)
			{
				newBoxData(h,&p);
				if(p==NULL)
				{
					return;
				}
				p->nextLevelSum=0;//本级框的子级框个数为0
				p->lastNextBox[0]=front;//本级框的父子级框地址的[0]指向父级
				p->lastNextBox[1]=NULL;
				
				front->nextLevelSum++;//父级框的子级框个数加1
				
				a=front->nextLevelSum-p0->lastLevelFlag-1;
				b=front->nextLevelSum;
				
				for(i=0;i<a;i++)
				{
					front->lastNextBox[b-i]=front->lastNextBox[b-i-1];//在父级的父子级中除去本级
					(front->lastNextBox[b-i])->lastLevelFlag+=1;//增加有本级时的其他子级的标序
				}
				
				front->lastNextBox[p0->lastLevelFlag+1]=p;//父级框的父子级框地址的[]指向子级框
				
				front->lastNextBox[front->nextLevelSum+1]=NULL;
				
				p->lastLevelFlag=p0->lastLevelFlag+1;//本级框的父级框的子级框的个数
				
				p->next=p0->next;
				p0->next=p;
				return;
			}
		}
		else if(flag==0)//判断点击的是否为tab
		{
			if(p->nextLevelSum==25)
			{
				overflow26Warning();
				return;
			}
			front=p;//增加下一级，父级框为本级框
		}
		else if(flag==2&&p!=h)//CTRL_ENTER
		{
			if(p->lastNextBox[0]->nextLevelSum==25)
			{
				overflow26Warning();
				return;
			}
			front=p->lastNextBox[0];//增加同一级，父级框为本级框的上一级
			
			newBoxData(h,&p);
			if(p==NULL)
			{
				return;
			}
			p->nextLevelSum=0;//本级框的子级框个数为0
			p->lastNextBox[0]=front;//本级框的父子级框地址的[0]指向父级
			p->lastNextBox[1]=NULL;
			
			front->nextLevelSum++;//父级框的子级框个数加1
			
			a=front->nextLevelSum-p0->lastLevelFlag;
			b=front->nextLevelSum;
			
			for(i=0;i<a;i++)
			{
				front->lastNextBox[b-i]=front->lastNextBox[b-i-1];
				(front->lastNextBox[b-i])->lastLevelFlag+=1;
			}
			
			front->lastNextBox[p0->lastLevelFlag-1]=p;//父级框的父子级框地址的[]指向子级框
			
			front->lastNextBox[front->nextLevelSum+1]=NULL;
			
			p->lastLevelFlag=p0->lastLevelFlag-1;//本级框的父级框的子级框的个数
			
			(p0->last)->next=p;
			p->next=p0;
			return;
		}
		else if(flag==3&&p!=h)//CTEL_F
		{
			front=p->lastNextBox[0];//增加同一级，父级框为本级框的上一级
			
			newBoxData(h,&p);
			if(p==NULL)
			{
				return;
			}
			p->nextLevelSum=1;//本级框的子级框个数为0
			p->lastNextBox[0]=front;//本级框的父子级框地址的[0]指向父级
			p->lastNextBox[1]=p0;
			p->lastNextBox[2]=NULL;
			
			front->lastNextBox[p0->lastLevelFlag]=p;
			p->lastLevelFlag=p0->lastLevelFlag;//本级框的父级框的子级框的个数
			p0->lastLevelFlag=1;
			p0->lastNextBox[0]=p;
			
			(p0->last)->next=p;
			p->next=p0;
			
			return;
		}
		
		else
		{
			return;
		}
		newBoxData(h,&p);
		if(p==NULL)
		{
			return;
		}
		p->nextLevelSum=0;//本级框的子级框个数为0
		p->lastNextBox[0]=front;//本级框的父子级框地址的[0]指向父级
		p->lastNextBox[1]=NULL;
		front->nextLevelSum++;//父级框的子级框个数加1
		front->lastNextBox[front->nextLevelSum]=p;//父级框的父子级框地址的[]指向子级框
		front->lastNextBox[front->nextLevelSum+1]=NULL;
		p->lastLevelFlag=front->nextLevelSum;//本级框的父级框的子级框的个数
	
		if(front->nextLevelSum!=1)
		{
			p0=front->lastNextBox[front->nextLevelSum-1];
			while(p0->nextLevelSum!=0)
			{
				p0=p0->lastNextBox[p0->nextLevelSum];
			}
			if(p0->next!=NULL)
			{
				p->next=p0->next;
			}
			else
			{
				p->next=NULL;
			}
			p0->next=p;
		}
		else
		{
			if(front!=h)
			{
				p0=front;
				p->next=p0->next;
				p0->next=p;
			}
			else
			{
				p->next=NULL;
				h->next=p;
			}
		}
	}
}

void newBoxData(BOX*h,BOX**pp)
{
	(*pp)=NULL;
	if(((*pp)=(BOX*)malloc(sizeof(BOX)*50))==NULL)
	{
		overflowWarning();
		return;
		setcolor(0);
		settextjustify(LEFT_TEXT,TOP_TEXT);          //左部对齐，顶部对齐
		settextstyle(GOTHIC_FONT,HORIZ_DIR,1);					//黑体笔划输出，水平输出，24*24点阵
		outtextxy(10,10,"No enough memory!Press any key to quit...");
		getch();
		exit(1);
	}
	else
	{
		free((*pp));
		(*pp)=NULL;
	}
	(*pp)=(BOX*)malloc(sizeof(BOX));//开辟新的一级框的内存
	(*pp)->pointFlag=0;
	(*pp)->parentPointBackFlag=0;
	(*pp)->pointBackFlag=0;
	(*pp)->pressFlag=0;
	memset((*pp)->content,'\0',100);
	
	(*pp)->boldFlag=0;
	(*pp)->boxColor=h->boxNewColor;
	(*pp)->characterColor=h->characterNewColor;
	(*pp)->characterSize=16;
	
	clearAllPressBox(h);
	(*pp)->pressFlag=1;
}

//生成所有一级结构体其他数据
void boxDataGenerate(BOX*h)
{
	BOX*p=NULL,*front=NULL,*p1=NULL,*p2=NULL;
	int difference,flag=0,i=0,englishSum=0;
	
	if(h->nextLevelSum!=0)//判断第一级框是否有下级，以确定圆圈的留存
		h->pointFlag=1;
	else
	{
		h->pointFlag=0;
	}
	
	/***************************************************************/
	p=h;
	while(p!=NULL)//在全部一级基本数据生成后，遍历循环，使每一级储存它后方所有的最后一级的个数
	{
		flag=1;
		p->nextAllSum=0;
		
		p2=p->lastNextBox[0];
		while(p2!=NULL)
		{
			if(p2->pointBackFlag==1)
			{   
				flag=0;
			}
			p2=p2->lastNextBox[0];//找父级
		}
		
		p1=p;
		if(((p1->lastNextBox[1]==NULL&&p1->parentPointBackFlag==0)||p1->pointBackFlag==1)&&flag==1)
		{
			p1->nextAllSum++;
			while(p1->lastNextBox[0]!=NULL)//给最后一级的所有父级的nextAllSum加1
			{
				p1=p1->lastNextBox[0];
				p1->nextAllSum++;	
			}
		}
		p=p->next;
	}
	/***************************************************************/
	p=h;
	while(p!=NULL)
	{
		if(p->content[0]=='\0')
		{
			p->boxX=3*(p->characterSize/2)+6;//设置本级框长度的一半
		}
		else
		{
			for(i=0;i<strlen(p->content);i++)
			{
				if(p->content[i]<127&&p->content[i]>31)
				{
					englishSum++;
				}
			}
			p->boxX=((strlen(p->content)-englishSum)/2*(p->characterSize/2)+englishSum*6+6);//设置本级框长度的一半
			englishSum=0;
		}
		if(p->content[0]=='\0'&&p->boldFlag==2)
		{
			p->boxX=4*(p->characterSize/2)+6;//设置本级框长度的一半
		}
		
		p->lastFile=p;
		p=p->next;
	}
	/***************************************************************/
	h->boxY=h->characterSize/2+2;
	p=h->next;
	while(p!=NULL)//遍历循环，依次生成一级结构体其他初始数据
	{
		front=p->lastNextBox[0];//指向父级框的地址
		p->boxY=p->characterSize/2+2;//设置本级框高度的一半
		p->lineX=7;//设置本级框与父级框的X方向的距离
		p->lineY=0;
		if(p->parentPointBackFlag==0)
		{
			if(p->lastLevelFlag>1)
			{
				p->lineY=(front->lastNextBox[p->lastLevelFlag-1])->lineY+((front->lastNextBox[p->lastLevelFlag-1])->nextAllSum)*40;
			}
		}
		p->centerX=front->centerX+front->boxX+front->lineX+p->boxX+p->lineX;//本级框的中心X坐标			
		p->centerY=front->centerY+p->lineY;//本级框的中心Y坐标
		
		p->lastLevelSum=front->nextLevelSum;//本级框的父级框的子级框个数
		
		if(p->nextLevelSum!=0)//判断本级框的子级框个数是否为0，以确定圆圈的留存
		{
			p->pointFlag=1;
		}	
		else
		{
			p->pointFlag=0;
		}
		if(h->next==p)//将第一级框与之后的框连接起来
		{
			p->last=h;
		}
		if(p->next!=NULL)//倒序链接地址
		{
			p->next->last=p;
		}
		else if(p->next==NULL)
		{
			p1=p;//将最后的地址赋给p1
		}
	
		p=p->next;
	}
	/**************************修正算法*****************************/
	p=p1;
	while(p!=NULL)//重新生成所有方框的中心Y坐标
	{
		if(p->parentPointBackFlag==0)
		{
			if(p->lastNextBox[1]!=NULL&&p!=h)
			{
				p->centerY=((p->lastNextBox[1])->centerY+(p->lastNextBox[p->nextLevelSum])->centerY)/2;
			}
			else if(p==h)//取得第一级方框应有的位移
			{
				difference=h->centerY-((h->lastNextBox[1])->centerY+(h->lastNextBox[h->nextLevelSum])->centerY)/2;
			}
		}
		p=p->last;
	}
	p=h->next;
	while(p!=NULL)//改变除第一级以外的所有的中心Y坐标
	{
		if(p->parentPointBackFlag==0)
		{
			p->centerY=p->centerY+difference;
		}
		p=p->next;		
	}
	p=h->next;
	while(p!=NULL)//生成每一级框与父级框的Y方向的距离
	{
		if(p->parentPointBackFlag==0)
		{
			front=p->lastNextBox[0];
			p->lineY=p->centerY-front->centerY;
		}
		p=p->next;
	}
	/***************************************************************/
}
//画出一个一级框
void drawOneBox(int centerX,int centerY,int boxX,int boxY,int lineX,int lineY,char*content,int pointFlag, int pointBackFlag,int lastLevelSum,int nextAllSum,int boldFlag,int boxColor,int characterColor,int characterSize)
{
	if(nextAllSum>=0)
	{
		if(content[0]=='\0'&&boldFlag==2)
		{
			puthzcu(centerX-boxX+6,centerY-boxY+2,"中心主题",characterSize,characterSize,characterColor);//画出字
		}
		else if(content[0]!='\0'&&(boldFlag==1||boldFlag==2))
		{
			puthzcu(centerX-boxX+6,centerY-boxY+2,content,characterSize,characterSize,characterColor);//画出字
		}
		else if(content[0]=='\0'&&boldFlag==0)
		{
			puthz(centerX-boxX+6,centerY-boxY+2,"子主题",characterSize,characterSize,characterColor);//画出字
		}
		else if(content[0]=='\0'&&boldFlag==1)
		{
			puthzcu(centerX-boxX+6,centerY-boxY+2,"子主题",characterSize,characterSize,characterColor);//画出字
		}
		else if(content[0]!='\0'&&boldFlag==0)
		{
			puthz(centerX-boxX+6,centerY-boxY+2,content,characterSize,characterSize,characterColor);//画出字
		}
	}
	setcolor(boxColor);
	line(centerX-boxX+RADIUS,centerY-boxY,centerX+boxX-RADIUS,centerY-boxY);
	line(centerX-boxX+RADIUS,centerY+boxY,centerX+boxX-RADIUS,centerY+boxY);
	line(centerX-boxX,centerY-boxY+RADIUS,centerX-boxX,centerY+boxY-RADIUS);
	line(centerX+boxX,centerY-boxY+RADIUS,centerX+boxX,centerY+boxY-RADIUS);
	arc(centerX-boxX+RADIUS,centerY-boxY+RADIUS,90,180,RADIUS);
	arc(centerX+boxX-RADIUS,centerY-boxY+RADIUS,0,90,RADIUS);
	arc(centerX-boxX+RADIUS,centerY+boxY-RADIUS,180,270,RADIUS);
	arc(centerX+boxX-RADIUS,centerY+boxY-RADIUS,270,360,RADIUS);
	// rectangle(centerX-boxX,centerY-boxY,centerX+boxX,centerY+boxY);//画出方框
	setcolor(boxColor);
	if(lastLevelSum>0)//判断一级框的上一级框的下一级框的个数总和是否大于0
		line(centerX-boxX,centerY,centerX-boxX-lineX,centerY);//画出短横线
	setcolor(boxColor);	
	if(pointFlag==1)
	{
		circle(centerX+boxX+lineX-3,centerY,3);//画出节点圈
		line(centerX+boxX,centerY,centerX+boxX+lineX,centerY);//画出节点圈的短横线
	}
	if(nextAllSum>0&&boldFlag!=2)
		line(centerX-boxX-lineX,centerY,centerX-boxX-lineX,centerY-lineY);//画长竖线
	if(pointBackFlag==1)
	{
		setcolor(4);
		line(centerX+boxX+lineX-3,centerY-3,centerX+boxX+lineX-3,centerY+3);
	}
}
//画出所有一级框
void drawAllBox(BOX*h) 
{
	BOX*p=h;
	while(p!=NULL)
	{
		if(p->parentPointBackFlag==0)
		{
			drawOneBox(p->centerX,p->centerY,p->boxX,p->boxY,p->lineX,p->lineY,p->content,p->pointFlag, p->pointBackFlag,p->lastLevelSum,p->nextAllSum,p->boldFlag,p->boxColor,p->characterColor,p->characterSize);//画出一个一级框
		}
		p=p->next;
	}
}
//删除一级结构体及其全部子级
void deleteOneBox(BOX*h,BOX*p)
{
	BOX*p1=NULL,*p2=NULL,*p3=NULL,*front=NULL;
	int flag=0,flag1=1,a,i,b;
	
	front=p->lastNextBox[0];
	front->lastNextBox[front->nextLevelSum+1]=NULL;
	front->nextLevelSum=front->nextLevelSum-1;//使父级的子级数减一
	
	a=front->nextLevelSum+1-p->lastLevelFlag;
	b=p->lastLevelFlag;
	if(a==0&&front->nextLevelSum==0)
	{
		front->lastNextBox[1]=NULL;
	}
	for(i=0;i<a+1;i++)
	{
		front->lastNextBox[b+i]=front->lastNextBox[b+1+i];//在父级的父子级中除去本级
		(front->lastNextBox[b+i])->lastLevelFlag-=1;//恢复没有本级时的其他子级的标序
	}
	
	p1=findEndBox(h);//最后生成的框
	while(p1!=NULL)//从后往前寻找
	{
		flag1=1;
		p2=p1;
		while(p2!=NULL)//判断是否为p的后级
		{
			if(p2==p)
			{
				flag=1;//为p的后级
				flag1=0;
				break;
			}
			p2=p2->lastNextBox[0];//找父级
		}
		
		if(flag==1)//为p的后级
		{
			if(p1->last!=NULL&&p1->next!=NULL)//判断上一级是否存在
			{
				(p1->last)->next=p1->next;//在正序中除去本级
			}	
			
			if(p1->next!=NULL)//判断下一级是否存在
			{
				(p1->next)->last=p1->last;//在倒序中除去本级
			}
			if(p1->next==NULL)
			{
				(p1->last)->next=NULL;
			}
			p3=p1->last;
			free(p1);
			p1=p3;
			flag=0;
		}
		if(flag1==1)
		{
			p1=p1->last;
		}
	}
}
//清除所有一级框的结构体数据
void clearAllBox(BOX*h)
{
	BOX*p=h->next,*next;
	while(p!=NULL)
	{
		next=p->next;
		free(p);
		p=next;
	}
}
//更新界面
void renewAllBox(BOX*h,int x1,int y1,int x2,int y2)
{
	int button;
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setviewport(x1,y1,x2,y2,1);
	setfillstyle(1,h->lastLevelFlag);
	bar(0,0,637,458);
	boxDataGenerate(h);//生成所有方框的所有数据
	drawAllBox(h);//画出所有的方框
	setviewport(0,0,639,479,1);
	MouseX-=1;
	newmouse(&MouseX,&MouseY,&button);
}
//开节点生成下一级
void openPointAndNextBox(BOX*h,BOX*pPress)
{
	if(pPress->pointBackFlag==1)
	{
		pointBack(h,pPress);
		boxDataGenerate(h);//生成所有方框的所有数据
		boxDataStorage(h,pPress,0);//生成下一级初始数据
	}
	else
	{
		boxDataStorage(h,pPress,0);//生成下一级初始数据
	}
	
}
//删除被选一级框
void deleteBox(BOX*h,BOX**ppPress)
{
	BOX*p1=NULL;
	if((*ppPress)!=h)
	{
		((*ppPress)->last)->pressFlag=1;
		p1=(*ppPress)->last;
		deleteOneBox(h,*ppPress);
		*ppPress=p1;
	}
}
//汉字输入
void characterInput(BOX*pPress)
{
	static BOX*p0=NULL;
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
	if(pPress->centerX>640||pPress->centerY>470)
	{
		a=input_method(320-30,240+10,content0,keyValue,py);
	}
	else
	{
		a=input_method(pPress->centerX-30,pPress->centerY+10,content0,keyValue,py);
	}
	
	if(a!=3&&a!=0)
	{
		strcat(content1,content0);
		strcpy(pPress->content,content1);
	}
	p0=pPress;
}
//选中一级框
void pressBox(BOX*h,BOX*pBox)
{
	clearAllPressBox(h);
	pBox->pressFlag=1;
}
//收回节点清除被选
void pointBackAndClear(BOX*h,BOX*pPoint)
{
	clearAllPressBox(h);
	pointBack(h,pPoint);
}
//退出主界面并清理内存
void exitAndClear(BOX*h)
{
	clearAllBox(h);
}
//内存不足警告
void overflowWarning()
{
	int button;
	
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setcolor(15);
	bar(120,200,520,280);
	setcolor(8);
	rectangle(120,200,520,280);
	
	
	puthz(150, 210, "内存不足，请删除一些子主题后，再进行创建...", 16, 16, 0);
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
//直系子主题已满警告
void overflow26Warning()
{
	int button;
	
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setcolor(15);
	bar(120,200,520,280);
	setcolor(8);
	rectangle(120,200,520,280);
	
	
	puthz(150, 210, "一个主题下只能有25个直系子主题，已达上限，", 16, 16, 0);
	puthz(130, 230, "请删除一些子主题后，再进行创建...", 16, 16, 0);
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
//汉字输入已满警告
void overflowCharacterWarning()
{
	int button;
	
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setcolor(15);
	bar(120,200,520,280);
	setcolor(8);
	rectangle(120,200,520,280);
	
	puthz(150, 210, "主题文字内容字数已达上限，请删除一些字后，", 16, 16, 0);
	puthz(130, 230, "再进行输入...", 16, 16, 0);
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
//ZEN模式下的方框遍历
BOX *traversalBoxCycleInZen(BOX*h,int x1,int y1,int color)
{
	BOX*p=h;
	int mouseX,mouseY;
	mouseX=MouseX-x1;
	mouseY=MouseY-y1;
	while(p!=NULL)
	{	
		if(p->parentPointBackFlag==0)
		{
			if(mouseX <= p->centerX + p->boxX && mouseX >= p->centerX - p->boxX && mouseY <= p->centerY + p->boxY && mouseY >= p->centerY - p->boxY)
			{
				if(!(p->centerX+p->boxX>570&&p->centerX-p->boxX<630&&p->centerY+p->boxY<210&&p->centerY-p->boxY>25))
				{
					setcolor(SFKCOLOR);
					drawSmallOutBox(p);
				}
				return p;
			}
			else
			{
				if(!(p->centerX+p->boxX>570&&p->centerX-p->boxX<630&&p->centerY+p->boxY<210&&p->centerY-p->boxY>25))
				{
					setcolor(color);
					drawSmallOutBox(p);
				}
				
			}	
		}
		p=p->next;
	}
	return p;
}
//ZEN模式下的节点遍历
BOX *traversalPointCycleInZen(BOX*h,int x1,int y1)
{
	//570, 25, 630, 210
	BOX*p=h;
	int x=0,y=0,mouseX,mouseY;
	mouseX=MouseX-x1;
	mouseY=MouseY-y1;
	while(p!=NULL)
	{	
		if(p->parentPointBackFlag==0)
		{
			if(pow(mouseX-(p->centerX+p->boxX+p->lineX-3),2)+pow(mouseY-p->centerY,2)<=16&&p->pointFlag==1)
			{
				if(!(p->centerX+p->boxX>570&&p->centerX-p->boxX<630&&p->centerY+p->boxY<210&&p->centerY-p->boxY>25))
				{
					setcolor(4);
					circle(p->centerX+p->boxX+p->lineX-3,p->centerY,3);//画出节点圈
				}
				x=mouseX;
				y=mouseY;
				return p;
			}
			if(mouseX!=x&&mouseY!=y&&p->pointFlag==1)			
			{
				if(!(p->centerX+p->boxX>570&&p->centerX-p->boxX<630&&p->centerY+p->boxY<210&&p->centerY-p->boxY>25))
				{
					setcolor(p->boxColor);
					circle(p->centerX+p->boxX+p->lineX-3,p->centerY,3);//画出节点圈
				}
				
			}
		}
		p=p->next;
	}
	return p;
}
//ZEN模式下的点击确定遍历
BOX *traversalPressBoxInZen(BOX*h,int color)
{
	BOX*p=h,*p0=NULL;
	while(p!=NULL)
	{
		
		if(p->pressFlag==1&&p->parentPointBackFlag==0)
		{
			if(!(p->centerX+p->boxX>570&&p->centerX-p->boxX<630&&p->centerY+p->boxY<210&&p->centerY-p->boxY>25))
			{
				setcolor(SFKCOLOR);
				drawOutBox(p);	
			}
			p0=p;
		}
		else if(p->parentPointBackFlag==0&&(!(p->centerX+p->boxX>570&&p->centerX-p->boxX<630&&p->centerY+p->boxY<210&&p->centerY-p->boxY>25)))
		{
			setcolor(color);
			drawOutBox(p);	
		}
		p=p->next;
			
		
	}
	return p0;
}









