#include"MAINHEAD.h"

//���ɵ�һ���ṹ������
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
//�ҵ����һ���ṹ������
BOX *findEndBox(BOX*h)
{
	BOX*p=NULL;
	p=h;
	while(p->next!=NULL)//����ѭ������������һ���ṹ��������ʼ����
	{
		p=p->next;
	}
	return p;
}
//�ҵ��������һ����
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

//�ҵ�������ڽڵ�
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
				circle(p->centerX+p->boxX+p->lineX-3,p->centerY,3);//�����ڵ�Ȧ
				x=mouseX;
				y=mouseY;
				return p;
			}
			if(mouseX!=x&&mouseY!=y&&p->pointFlag==1)			
			{
				setcolor(p->boxColor);
				circle(p->centerX+p->boxX+p->lineX-3,p->centerY,3);//�����ڵ�Ȧ
			}
		}
		p=p->next;
	}
	return p;
}
//�ҵ��ѱ�ѡ��һ����
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

//�����ѡ�е�һ���� 
void clearAllPressBox(BOX*h) 
{
	BOX*p=h;
	while(p!=NULL)
	{
		p->pressFlag=0;
		p=p->next;
	}
}
//�ƶ�һ����
void choiceDirection(BOX*h,BOX**ppPress)
{
	if(bioskey(1)==UP&&(*ppPress)!=NULL)//����
	{
		bioskey(0);
		if((*ppPress)->lastLevelFlag!=1&&((*ppPress)->lastNextBox[0])!=NULL&&((*ppPress)->lastNextBox[0])->lastNextBox[(*ppPress)->lastLevelFlag-1]!=NULL)
		{
			clearAllPressBox(h);
			(*ppPress)=((*ppPress)->lastNextBox[0])->lastNextBox[(*ppPress)->lastLevelFlag-1];
			(*ppPress)->pressFlag=1;
		}
	}
	else if(bioskey(1)==DOWN&&(*ppPress)!=NULL)//����
	{
		bioskey(0);
		if((*ppPress)->lastLevelFlag!=(*ppPress)->lastLevelSum&&((*ppPress)->lastNextBox[0])!=NULL&&((*ppPress)->lastNextBox[0])->lastNextBox[(*ppPress)->lastLevelFlag+1]!=NULL)
		{
			clearAllPressBox(h);
			(*ppPress)=((*ppPress)->lastNextBox[0])->lastNextBox[(*ppPress)->lastLevelFlag+1];
			(*ppPress)->pressFlag=1;
		}
	}
	else if(bioskey(1)==LEFT&&(*ppPress)!=NULL)//����
	{
		bioskey(0);
		if(((*ppPress)->lastNextBox[0])!=NULL)
		{
			clearAllPressBox(h);
			(*ppPress)=(*ppPress)->lastNextBox[0];
			(*ppPress)->pressFlag=1;
		}
	}
	else if(bioskey(1)==RIGHT&&(*ppPress)!=NULL)//����
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
//�շŽڵ�
void pointBack(BOX*h,BOX*p)
{
	BOX*p1=NULL,*p2=NULL,*p0=NULL;
	int flag=0;
	if(p->pointBackFlag==0)//�ջ�
	{
		p->pointBackFlag=1;
		p1=h;
		while(p1!=NULL)
		{
			p2=p1;
			while(p2!=NULL)//�ж��Ƿ�Ϊp�ĺ�
			{
				if(p2==p)
				{
					flag=1;//Ϊp�ĺ�
					break;
				}
				p2=p2->lastNextBox[0];//�Ҹ���
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
	else//�ſ�
	{
		p->pointBackFlag=0;
		p1=h;
		while(p1!=NULL)
		{
			p2=p1;
			while(p2!=NULL)//�ж��Ƿ�Ϊp�ĺ�
			{
				if(p2==p)
				{
					flag=1;//Ϊp�ĺ�
					break;
				}
				p2=p2->lastNextBox[0];//�Ҹ���
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
					p0=p0->lastNextBox[0];//�Ҹ���
				}
				
				flag=0;
			}
			p1=p1->next;
		}
		p->parentPointBackFlag=0;
	}
}
//����һ���ṹ���������
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
				p->nextLevelSum=0;//��������Ӽ������Ϊ0
				p->lastNextBox[0]=front;//������ĸ��Ӽ����ַ��[0]ָ�򸸼�
				p->lastNextBox[1]=NULL;
				
				front->nextLevelSum++;//��������Ӽ��������1
				
				a=front->nextLevelSum-p0->lastLevelFlag-1;
				b=front->nextLevelSum;
				
				for(i=0;i<a;i++)
				{
					front->lastNextBox[b-i]=front->lastNextBox[b-i-1];//�ڸ����ĸ��Ӽ��г�ȥ����
					(front->lastNextBox[b-i])->lastLevelFlag+=1;//�����б���ʱ�������Ӽ��ı���
				}
				
				front->lastNextBox[p0->lastLevelFlag+1]=p;//������ĸ��Ӽ����ַ��[]ָ���Ӽ���
				
				front->lastNextBox[front->nextLevelSum+1]=NULL;
				
				p->lastLevelFlag=p0->lastLevelFlag+1;//������ĸ�������Ӽ���ĸ���
				
				p->next=p0->next;
				p0->next=p;
				return;
			}
		}
		else if(flag==0)//�жϵ�����Ƿ�Ϊtab
		{
			if(p->nextLevelSum==25)
			{
				overflow26Warning();
				return;
			}
			front=p;//������һ����������Ϊ������
		}
		else if(flag==2&&p!=h)//CTRL_ENTER
		{
			if(p->lastNextBox[0]->nextLevelSum==25)
			{
				overflow26Warning();
				return;
			}
			front=p->lastNextBox[0];//����ͬһ����������Ϊ���������һ��
			
			newBoxData(h,&p);
			if(p==NULL)
			{
				return;
			}
			p->nextLevelSum=0;//��������Ӽ������Ϊ0
			p->lastNextBox[0]=front;//������ĸ��Ӽ����ַ��[0]ָ�򸸼�
			p->lastNextBox[1]=NULL;
			
			front->nextLevelSum++;//��������Ӽ��������1
			
			a=front->nextLevelSum-p0->lastLevelFlag;
			b=front->nextLevelSum;
			
			for(i=0;i<a;i++)
			{
				front->lastNextBox[b-i]=front->lastNextBox[b-i-1];
				(front->lastNextBox[b-i])->lastLevelFlag+=1;
			}
			
			front->lastNextBox[p0->lastLevelFlag-1]=p;//������ĸ��Ӽ����ַ��[]ָ���Ӽ���
			
			front->lastNextBox[front->nextLevelSum+1]=NULL;
			
			p->lastLevelFlag=p0->lastLevelFlag-1;//������ĸ�������Ӽ���ĸ���
			
			(p0->last)->next=p;
			p->next=p0;
			return;
		}
		else if(flag==3&&p!=h)//CTEL_F
		{
			front=p->lastNextBox[0];//����ͬһ����������Ϊ���������һ��
			
			newBoxData(h,&p);
			if(p==NULL)
			{
				return;
			}
			p->nextLevelSum=1;//��������Ӽ������Ϊ0
			p->lastNextBox[0]=front;//������ĸ��Ӽ����ַ��[0]ָ�򸸼�
			p->lastNextBox[1]=p0;
			p->lastNextBox[2]=NULL;
			
			front->lastNextBox[p0->lastLevelFlag]=p;
			p->lastLevelFlag=p0->lastLevelFlag;//������ĸ�������Ӽ���ĸ���
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
		p->nextLevelSum=0;//��������Ӽ������Ϊ0
		p->lastNextBox[0]=front;//������ĸ��Ӽ����ַ��[0]ָ�򸸼�
		p->lastNextBox[1]=NULL;
		front->nextLevelSum++;//��������Ӽ��������1
		front->lastNextBox[front->nextLevelSum]=p;//������ĸ��Ӽ����ַ��[]ָ���Ӽ���
		front->lastNextBox[front->nextLevelSum+1]=NULL;
		p->lastLevelFlag=front->nextLevelSum;//������ĸ�������Ӽ���ĸ���
	
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
		settextjustify(LEFT_TEXT,TOP_TEXT);          //�󲿶��룬��������
		settextstyle(GOTHIC_FONT,HORIZ_DIR,1);					//����ʻ������ˮƽ�����24*24����
		outtextxy(10,10,"No enough memory!Press any key to quit...");
		getch();
		exit(1);
	}
	else
	{
		free((*pp));
		(*pp)=NULL;
	}
	(*pp)=(BOX*)malloc(sizeof(BOX));//�����µ�һ������ڴ�
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

//��������һ���ṹ����������
void boxDataGenerate(BOX*h)
{
	BOX*p=NULL,*front=NULL,*p1=NULL,*p2=NULL;
	int difference,flag=0,i=0,englishSum=0;
	
	if(h->nextLevelSum!=0)//�жϵ�һ�����Ƿ����¼�����ȷ��ԲȦ������
		h->pointFlag=1;
	else
	{
		h->pointFlag=0;
	}
	
	/***************************************************************/
	p=h;
	while(p!=NULL)//��ȫ��һ�������������ɺ󣬱���ѭ����ʹÿһ�������������е����һ���ĸ���
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
			p2=p2->lastNextBox[0];//�Ҹ���
		}
		
		p1=p;
		if(((p1->lastNextBox[1]==NULL&&p1->parentPointBackFlag==0)||p1->pointBackFlag==1)&&flag==1)
		{
			p1->nextAllSum++;
			while(p1->lastNextBox[0]!=NULL)//�����һ�������и�����nextAllSum��1
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
			p->boxX=3*(p->characterSize/2)+6;//���ñ����򳤶ȵ�һ��
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
			p->boxX=((strlen(p->content)-englishSum)/2*(p->characterSize/2)+englishSum*6+6);//���ñ����򳤶ȵ�һ��
			englishSum=0;
		}
		if(p->content[0]=='\0'&&p->boldFlag==2)
		{
			p->boxX=4*(p->characterSize/2)+6;//���ñ����򳤶ȵ�һ��
		}
		
		p->lastFile=p;
		p=p->next;
	}
	/***************************************************************/
	h->boxY=h->characterSize/2+2;
	p=h->next;
	while(p!=NULL)//����ѭ������������һ���ṹ��������ʼ����
	{
		front=p->lastNextBox[0];//ָ�򸸼���ĵ�ַ
		p->boxY=p->characterSize/2+2;//���ñ�����߶ȵ�һ��
		p->lineX=7;//���ñ������븸�����X����ľ���
		p->lineY=0;
		if(p->parentPointBackFlag==0)
		{
			if(p->lastLevelFlag>1)
			{
				p->lineY=(front->lastNextBox[p->lastLevelFlag-1])->lineY+((front->lastNextBox[p->lastLevelFlag-1])->nextAllSum)*40;
			}
		}
		p->centerX=front->centerX+front->boxX+front->lineX+p->boxX+p->lineX;//�����������X����			
		p->centerY=front->centerY+p->lineY;//�����������Y����
		
		p->lastLevelSum=front->nextLevelSum;//������ĸ�������Ӽ������
		
		if(p->nextLevelSum!=0)//�жϱ�������Ӽ�������Ƿ�Ϊ0����ȷ��ԲȦ������
		{
			p->pointFlag=1;
		}	
		else
		{
			p->pointFlag=0;
		}
		if(h->next==p)//����һ������֮��Ŀ���������
		{
			p->last=h;
		}
		if(p->next!=NULL)//�������ӵ�ַ
		{
			p->next->last=p;
		}
		else if(p->next==NULL)
		{
			p1=p;//�����ĵ�ַ����p1
		}
	
		p=p->next;
	}
	/**************************�����㷨*****************************/
	p=p1;
	while(p!=NULL)//�����������з��������Y����
	{
		if(p->parentPointBackFlag==0)
		{
			if(p->lastNextBox[1]!=NULL&&p!=h)
			{
				p->centerY=((p->lastNextBox[1])->centerY+(p->lastNextBox[p->nextLevelSum])->centerY)/2;
			}
			else if(p==h)//ȡ�õ�һ������Ӧ�е�λ��
			{
				difference=h->centerY-((h->lastNextBox[1])->centerY+(h->lastNextBox[h->nextLevelSum])->centerY)/2;
			}
		}
		p=p->last;
	}
	p=h->next;
	while(p!=NULL)//�ı����һ����������е�����Y����
	{
		if(p->parentPointBackFlag==0)
		{
			p->centerY=p->centerY+difference;
		}
		p=p->next;		
	}
	p=h->next;
	while(p!=NULL)//����ÿһ�����븸�����Y����ľ���
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
//����һ��һ����
void drawOneBox(int centerX,int centerY,int boxX,int boxY,int lineX,int lineY,char*content,int pointFlag, int pointBackFlag,int lastLevelSum,int nextAllSum,int boldFlag,int boxColor,int characterColor,int characterSize)
{
	if(nextAllSum>=0)
	{
		if(content[0]=='\0'&&boldFlag==2)
		{
			puthzcu(centerX-boxX+6,centerY-boxY+2,"��������",characterSize,characterSize,characterColor);//������
		}
		else if(content[0]!='\0'&&(boldFlag==1||boldFlag==2))
		{
			puthzcu(centerX-boxX+6,centerY-boxY+2,content,characterSize,characterSize,characterColor);//������
		}
		else if(content[0]=='\0'&&boldFlag==0)
		{
			puthz(centerX-boxX+6,centerY-boxY+2,"������",characterSize,characterSize,characterColor);//������
		}
		else if(content[0]=='\0'&&boldFlag==1)
		{
			puthzcu(centerX-boxX+6,centerY-boxY+2,"������",characterSize,characterSize,characterColor);//������
		}
		else if(content[0]!='\0'&&boldFlag==0)
		{
			puthz(centerX-boxX+6,centerY-boxY+2,content,characterSize,characterSize,characterColor);//������
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
	// rectangle(centerX-boxX,centerY-boxY,centerX+boxX,centerY+boxY);//��������
	setcolor(boxColor);
	if(lastLevelSum>0)//�ж�һ�������һ�������һ����ĸ����ܺ��Ƿ����0
		line(centerX-boxX,centerY,centerX-boxX-lineX,centerY);//�����̺���
	setcolor(boxColor);	
	if(pointFlag==1)
	{
		circle(centerX+boxX+lineX-3,centerY,3);//�����ڵ�Ȧ
		line(centerX+boxX,centerY,centerX+boxX+lineX,centerY);//�����ڵ�Ȧ�Ķ̺���
	}
	if(nextAllSum>0&&boldFlag!=2)
		line(centerX-boxX-lineX,centerY,centerX-boxX-lineX,centerY-lineY);//��������
	if(pointBackFlag==1)
	{
		setcolor(4);
		line(centerX+boxX+lineX-3,centerY-3,centerX+boxX+lineX-3,centerY+3);
	}
}
//��������һ����
void drawAllBox(BOX*h) 
{
	BOX*p=h;
	while(p!=NULL)
	{
		if(p->parentPointBackFlag==0)
		{
			drawOneBox(p->centerX,p->centerY,p->boxX,p->boxY,p->lineX,p->lineY,p->content,p->pointFlag, p->pointBackFlag,p->lastLevelSum,p->nextAllSum,p->boldFlag,p->boxColor,p->characterColor,p->characterSize);//����һ��һ����
		}
		p=p->next;
	}
}
//ɾ��һ���ṹ�弰��ȫ���Ӽ�
void deleteOneBox(BOX*h,BOX*p)
{
	BOX*p1=NULL,*p2=NULL,*p3=NULL,*front=NULL;
	int flag=0,flag1=1,a,i,b;
	
	front=p->lastNextBox[0];
	front->lastNextBox[front->nextLevelSum+1]=NULL;
	front->nextLevelSum=front->nextLevelSum-1;//ʹ�������Ӽ�����һ
	
	a=front->nextLevelSum+1-p->lastLevelFlag;
	b=p->lastLevelFlag;
	if(a==0&&front->nextLevelSum==0)
	{
		front->lastNextBox[1]=NULL;
	}
	for(i=0;i<a+1;i++)
	{
		front->lastNextBox[b+i]=front->lastNextBox[b+1+i];//�ڸ����ĸ��Ӽ��г�ȥ����
		(front->lastNextBox[b+i])->lastLevelFlag-=1;//�ָ�û�б���ʱ�������Ӽ��ı���
	}
	
	p1=findEndBox(h);//������ɵĿ�
	while(p1!=NULL)//�Ӻ���ǰѰ��
	{
		flag1=1;
		p2=p1;
		while(p2!=NULL)//�ж��Ƿ�Ϊp�ĺ�
		{
			if(p2==p)
			{
				flag=1;//Ϊp�ĺ�
				flag1=0;
				break;
			}
			p2=p2->lastNextBox[0];//�Ҹ���
		}
		
		if(flag==1)//Ϊp�ĺ�
		{
			if(p1->last!=NULL&&p1->next!=NULL)//�ж���һ���Ƿ����
			{
				(p1->last)->next=p1->next;//�������г�ȥ����
			}	
			
			if(p1->next!=NULL)//�ж���һ���Ƿ����
			{
				(p1->next)->last=p1->last;//�ڵ����г�ȥ����
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
//�������һ����Ľṹ������
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
//���½���
void renewAllBox(BOX*h,int x1,int y1,int x2,int y2)
{
	int button;
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setviewport(x1,y1,x2,y2,1);
	setfillstyle(1,h->lastLevelFlag);
	bar(0,0,637,458);
	boxDataGenerate(h);//�������з������������
	drawAllBox(h);//�������еķ���
	setviewport(0,0,639,479,1);
	MouseX-=1;
	newmouse(&MouseX,&MouseY,&button);
}
//���ڵ�������һ��
void openPointAndNextBox(BOX*h,BOX*pPress)
{
	if(pPress->pointBackFlag==1)
	{
		pointBack(h,pPress);
		boxDataGenerate(h);//�������з������������
		boxDataStorage(h,pPress,0);//������һ����ʼ����
	}
	else
	{
		boxDataStorage(h,pPress,0);//������һ����ʼ����
	}
	
}
//ɾ����ѡһ����
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
//��������
void characterInput(BOX*pPress)
{
	static BOX*p0=NULL;
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
//ѡ��һ����
void pressBox(BOX*h,BOX*pBox)
{
	clearAllPressBox(h);
	pBox->pressFlag=1;
}
//�ջؽڵ������ѡ
void pointBackAndClear(BOX*h,BOX*pPoint)
{
	clearAllPressBox(h);
	pointBack(h,pPoint);
}
//�˳������沢�����ڴ�
void exitAndClear(BOX*h)
{
	clearAllBox(h);
}
//�ڴ治�㾯��
void overflowWarning()
{
	int button;
	
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setcolor(15);
	bar(120,200,520,280);
	setcolor(8);
	rectangle(120,200,520,280);
	
	
	puthz(150, 210, "�ڴ治�㣬��ɾ��һЩ��������ٽ��д���...", 16, 16, 0);
	puthz(255, 260, "����ո���˳�����", 16, 16, 0);
	puthz(287, 260, "�ո��", 16, 16, 4);
	
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
//ֱϵ��������������
void overflow26Warning()
{
	int button;
	
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setcolor(15);
	bar(120,200,520,280);
	setcolor(8);
	rectangle(120,200,520,280);
	
	
	puthz(150, 210, "һ��������ֻ����25��ֱϵ�����⣬�Ѵ����ޣ�", 16, 16, 0);
	puthz(130, 230, "��ɾ��һЩ��������ٽ��д���...", 16, 16, 0);
	puthz(255, 260, "����ո���˳�����", 16, 16, 0);
	puthz(287, 260, "�ո��", 16, 16, 4);
	
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
//����������������
void overflowCharacterWarning()
{
	int button;
	
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setcolor(15);
	bar(120,200,520,280);
	setcolor(8);
	rectangle(120,200,520,280);
	
	puthz(150, 210, "�����������������Ѵ����ޣ���ɾ��һЩ�ֺ�", 16, 16, 0);
	puthz(130, 230, "�ٽ�������...", 16, 16, 0);
	puthz(255, 260, "����ո���˳�����", 16, 16, 0);
	puthz(287, 260, "�ո��", 16, 16, 4);
	
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
//ZENģʽ�µķ������
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
//ZENģʽ�µĽڵ����
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
					circle(p->centerX+p->boxX+p->lineX-3,p->centerY,3);//�����ڵ�Ȧ
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
					circle(p->centerX+p->boxX+p->lineX-3,p->centerY,3);//�����ڵ�Ȧ
				}
				
			}
		}
		p=p->next;
	}
	return p;
}
//ZENģʽ�µĵ��ȷ������
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









