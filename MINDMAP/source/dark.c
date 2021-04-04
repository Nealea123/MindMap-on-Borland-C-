#include"MAINHEAD.h"

int darkInterFace(BOX*h, long start)
{
	char *list[3] = {"��ݼ�", "��ʱ��", "�˳�"};//zen���ַ���ʼ��
	register int i = 0;//��ʼ�� i
	register int k = 0;//��ʼ�� k
	int state = 0;//��ʼ�� state
	BOX*pBox = NULL;//��ʼѡ�еĿ�ͼ��ָ��
	BOX*pPoint = NULL;//��ʼ��ѡ�нڵ��ָ��
	BOX*pPress = NULL;//��ʼ������ָ��
	const Cir Sun = {600, 140, 10};//��ʼ��̫�������ݣ�����Բ�ĺ����꣬�����꣬�뾶
	const Rect Table = {570, 40, 630, 110};//��ʼ��zen�������
	Menu word[3] = {{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"}};//��ʼ��������������
	/******�����ݵ��뵽Menu�ṹ����*******/
	for(k = 0; k < 3; k++)
	{
		word[k].pos.left = Table.left+5; 
		word[k].pos.top = Table.top+5+20*k;
		word[k].pos.right = Table.right;
		word[k].pos.bottom = Table.bottom;
		word[k].title = list[k];
	}
	/***********��ȡ��ʼ����ҹ��ģʽ��ʱ��****************/
	if(start != 0)
	{
		time(&start);
	}
	/***********��䱳��************/
	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, 639, 479);
	/*����zen��*/
	setcolor(DARKGRAY);
	rectangle(Table.left, Table.top, Table.right, Table.bottom);
	for(i = 0; i < 3; i++)
	{
		puthz(word[i].pos.left, word[i].pos.top, (word+i)->title, 16, 16, 8);
	}
	drawSun(Sun, DARKGRAY);//����̫����ť
	/*********ˢ��˼ά��ͼ*******/
	if(h != NULL)//��h��Ϊ��
	{
		drawAllDARKBox(h);//��ʾh������Ϣ
	}
	else//��hΪ��
	h = boxData0Generate( );//���ɵ�һ������
	
	while(1)//����ѭ��
	{
		state = mouseDark(h, &pBox, &pPoint, &pPress, Table, Sun, start, list);//��ȡ״̬
		switch(state)//�ж�״̬����
		{
			case 1://ѡ��һ��
			{
				pressBox(h, pBox);
				break;
			}
			case 2://ѡ�нڵ�
			{
				pointBackAndClear(h,pPoint);
				break;
			}
			case 3:case 7:case 31://���ڵ㲢������һ��
			{
				openPointAndNextBox(h,pPress);
				break;
			}
			case 4:case 32://����ͬһ��
			{
				boxDataStorage(h,pPress,1);
				break;
			}
			case 5:case 21://ɾ��һ��
			{
				deleteBox(h,&pPress);
				break;
			}
			case 6://��������
			{
				characterInput(pPress);
				break;
			}	
			case 9://�ƶ�
			{
				choiceDirection(h,&pPress);
				break;
			}
			case 10://�ƶ�����
			{
				moveFace(h);
				break;
			}
			case 33://������һ��
			{
				boxDataStorage(h,pPress,2);
				break;
			}
			case 34://���ɸ���
			{
				boxDataStorage(h,pPress,3);
				break;
			}
			case 40://��ת��������
			{
				return 4;
			}
			case 41://��ת��zen����
			{
				return 5;
			}
		}
		if(state!=1 
		&& state!=9
		&& !(MouseX >= Table.left
		&& MouseX <= Table.right
		&& MouseY >= Table.top
		&& MouseY <= Table.bottom))//����ͼ���ƶ��ҵ�ͼ��ѡ�нڵ�
		{
			renewNIGHTBox(h, Sun, 0, 0, 639, 479);//ˢ�µ�ͼ
		}
		
	}
}

int TableDark(Rect Table, Cir Sun, long start, char **list)
{
	int a = 0;//��ʼ��������
	int state = 0;//��ʼ��״̬����
	int face = 0;
	register int i = 0;//��ʼ������ڲ˵����е�λ�ò���
	
	while(1)
	{
		setviewport(0, 0, 639, 479, 1);
		newmouse(&MouseX, &MouseY, &a);//ˢ�����
		
		for(i = 0; i < 3; i++)
		{
			/********�ж�������ں��ֲ���������*********/
			if((MouseX >= Table.left 
			&& MouseX <= Table.right 
			&& MouseY >= (Table.top+5+i*20) 
			&& MouseY <= (Table.top+21+i*20))
			&& (i == 0 || i == 1))
			{
				setviewport(0, 0, 639, 479, 1);
				clrmous(MouseX, MouseY);//������
				puthz(Table.left+5, Table.top+5+20*i, list[i], 16, 16, WHITE);//��������
				setviewport(0, 0, 639, 479, 1);
				newmouse(&MouseX, &MouseY, &a);//ˢ�����
			}
			else if((MouseX >= Table.left 
			&& MouseX <= Table.right 
			&& MouseY >= (Table.top+5+i*20) 
			&& MouseY <= (Table.top+21+i*20))
			&& i == 2)
			{
				puthz(Table.left+5, Table.top+5+20*i, list[i], 16, 16, WHITE);//��������
			}
			if(!(MouseX >= Table.left 
			&& MouseX <= Table.right 
			&& MouseY >= (Table.top+5+i*20) 
			&& MouseY <= (Table.top+21+i*20)))
			{
				puthz(Table.left+5, Table.top+5+20*i, list[i], 16, 16, DARKGRAY);//��������
			}
		}
	/****************�ж�����ڲ˵��е�״̬��������״ֵ̬******************/
		if(MouseX >= Table.left
		&& MouseX <= Table.right
		&& MouseY >= (Table.top+5)
		&& MouseY <= (Table.top+21))
		{
			state = 1;//���λ�ڿ�ݼ�
		}
		else if(MouseX >= Table.left
		&& MouseX <= Table.right
		&& MouseY >= (Table.top+5+20)
		&& MouseY <= (Table.top+21+20))
		{
			state = 2;//���λ�ڼ�ʱ��
		}
		else if(MouseX >= Sun.centreX-13
		&& MouseX <= Sun.centreX+13
		&& MouseY >= Sun.centreY-13
		&& MouseY <= Sun.centreY+13)
		{
			state = 4;//��갴��̫����ť
		}
		else if(mouse_press(Table.left, Table.top+5+40, Table.right, Table.top+21+40)==1)
		{
			state = 3;//��갴���˳�
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
			state = 5;//���λ�ڱ����
		}
		/**************�ж�״̬����**************/
		switch(state)
		{
			case 1:
				KeyShow_Dark(Table);//��ʾ��ݼ��˵�
			break;
			case 2:
				TimeShow_Dark(start, Table);//��ʾ��ʱ��
			break;
			case 3:
			{
				clrmous(MouseX, MouseY);
				clearviewport();
				setfillstyle(1, WHITE);
				bar(0, 0, 639, 479);
				return 40;//��ת��������
			}
			case 4:
			{
				face = shine(Sun);
				if(face == 41)//�ж��Ƿ���̫��
				{
					return face;//����zen����
				}
			}
			break;
			case 5://���뵼ͼ�༭ģʽ
			return;
		}
	}
}

int mouseDark(BOX*h, BOX**ppBox, BOX**ppPoint, BOX**ppPress, Rect Table, Cir Sun, long start, char **list)
{
	int a = 0;//��ʼ��������
	int onePress = 0;//��ʼ����������
	int flag = 0;//��ʼ����ǲ���
	
	while(1)
	{	/**********�����λ��̫��**************/
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
					bioskey(0);//��ջ�����
				}
				/************����ָ�븳ֵ************/
				setviewport(0, 0, 639, 479, 0);
				*ppPress = traversalPressBoxInZen(h,7);
				/************�ж��Ƿ���̫��**************/
				setviewport(0, 0, 639, 479, 1);
				newmouse(&MouseX, &MouseY, &a);
				flag = shine(Sun);
				return flag;	
			}
		}
		/*************���λ�ڵ�ͼ����************/
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
				newmouse(&MouseX, &MouseY, &a);//ˢ�����
				/**************��ͼ����ָ�븳ֵ*******************/
				setviewport(0, 0, 639, 479, 1);
				*ppBox = traversalBoxCycleInZen(h, 0, 0,7);
				*ppPress = traversalPressBoxInZen(h,7);
				*ppPoint = traversalPointCycleInZen(h, 0, 0);
				/*************�ж��Ƿ���������*************/
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
						return 1;//ѡ�п�ͼ
					}
					else if(*ppPoint != NULL)
					{
						return 2;//ѡ�нڵ�
					}
				}
				/**********��ȡ��ֵ�����жϣ�����״̬����***************/
				setviewport(0, 0, 639, 479, 1);
				if(bioskey(1) != 0)//���̼������
				{
					if(bioskey(1) == 0x0f09//����Tab��
					&& (*ppPress) != NULL
					&& (*ppPress)->pointBackFlag == 0)
					{
						bioskey(0);					
						return 3;//���ڵ㲢������һ��
					}
					else if(bioskey(1) == 0x1c0d//����Enter��
					&& (*ppPress) != NULL)
					{
						bioskey(0);
						return 4;//����ͬһ��
					}
					else if(bioskey(1) == 0x5300//����Delete��
					&& (*ppPress) != NULL && (*ppPress) != h)
					{
						bioskey(0);
						return 5;//ɾ��һ��
					}
					else if(bioskey(1) == 0x0f09//����Shift+Tab��
					&& (*ppPress) != NULL
					&& (*ppPress)->pointBackFlag == 1)
					{
						bioskey(0);
						return 7;//���ڵ㲢������һ��
					}
					else if(bioskey(1) == 0x1a1b//����Ctrl��[��
					|| bioskey(1) == 0x1b1d//����Ctrl��]��
					|| bioskey(1) == 0x2b1c//����Ctrl��-��
					|| bioskey(1) == 0x0c1f//����Ctrl��\��
					|| bioskey(1) == 0x180f)//����Ctrl��O��
					{
						return 10;//�ƶ�˼ά��ͼ
					}
					else if(bioskey(1) == 0x1C0A)//����Ctrl��Enter��
					{
						bioskey(0);
						return 33;//������һ��
					}
					else if(bioskey(1) == 0x2106)//����Ctrl��F��
					{
						bioskey(0);
						return 34;//���ɸ���
					}
					else if(bioskey(1) == 0x320d)//����Ctrl��M��
					{
						bioskey(0);
						return 40;//����������
					}
					else if(bioskey(1) == 0x2c1a)//����Ctrl��Z��
					{
						bioskey(0);
						return 41;//����zen����
					}
					// else if(bioskey(1) == 0x1e01)//����Ctrl��A��
					// {
						// bioskey(0);
						// KeyShow_Dark(Table);
					// }
					/*��û�а��¿�ݼ�*/
					else if(bioskey(1)!=SPACE&&bioskey(1)!=DELETE&&bioskey(1)!=ENTER&&bioskey(1)!=TAB&&bioskey(1)!=CTRL_ENTER&&(*ppPress)!=NULL)
					{
						return 6;//��������
					}
					/*���·������ѡ����ı�*/
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
						bioskey(0);//��ջ�����
					}
				}
			}
		}
		/*************���λ�ڲ˵���***************/		
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
					bioskey(0);//��ջ�����
				}
				setviewport(0, 0, 639, 479, 1);
				newmouse(&MouseX, &MouseY, &a);//ˢ�����
				setviewport(0, 0, 639, 479, 0);
				*ppPress = traversalPressBoxInZen(h,7);
				flag = TableDark(Table, Sun, start, list);
				return flag;	//���ؽ������
			}
		}
	}
}

void TimeShow_Dark(long start, Rect Table)
{
	/*********��ʼ����ʱ������***********/
	char *TM[3] = {"00", "00", "00"};//��ʼ��char��ʱ����
	char *unit[3] = {"ʱ", "��", "��"};//ʱ���¼��λ
	int tm[3] = {0, 0, 0};//��ʼ��int��ʱ����
	int a = 0;//��ʼ��������
	register int i = 0;//��ʼ����ǲ���
	int t = 0;//��ʼ��ʱ��
	time_t end;//����ʱ��
	const Rect timeshow = {457, 46, 569, 88};//ʱ���λ
	
	while(bioskey(1)!=SPACE)
	{
		time(&end);//��ȡ����ʱ��
		/************���Ʋ˵���***********/
		setcolor(DARKGRAY);
		rectangle(timeshow.left, timeshow.top, timeshow.right, timeshow.bottom);
		setfillstyle(1, LIGHTGRAY);
		bar(timeshow.left+1, timeshow.top+1, timeshow.right-1, timeshow.bottom-1);
		setcolor(DARKGRAY);
		puthz(timeshow.left+2, timeshow.top+2, "ҹ��ʱ��", 16, 16, DARKGRAY);
		/************�����ȡҹ��ģʽʹ��ʱ��**************/
		t = (long)difftime(end, start);
		tm[0] = t/3600;
		tm[1] = (t-tm[0]*3600)/60;
		tm[2] = t-tm[0]*3600-tm[1]*60;
		/****************��ʾʱ��***************/
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
			bioskey(0);//��ջ�����
		}
		else if(bioskey(1)==ESC)
		{
			return;//�رռ�ʱ��
		}
		newmouse(&MouseX,&MouseY,&a);
	}
	
}

void KeyShow_Dark(Rect Table)
{
	/**************��ݼ���Ϣ��ʼ��********************/
	char *key1[] = {"�˳�","ɾ��","����������","��������֮��","��������֮ǰ","���븸����","˼ά��ͼģʽ","���Ƶ�ͼ","���Ƶ�ͼ","���Ƶ�ͼ","���Ƶ�ͼ","��ͼ��λ"};
	char *key2[] = {"Esc","Delete","Tab","Enter","Ctrl+Enter","Ctrl+F","Ctrl+M","Ctrl+[","Ctrl+]","Ctrl+-","Ctrl+\\","Ctrl+O"};
	register int i = 0;//��ǳ�ʼ��
	register int j = 0;
	int a = 0;//��������ʼ��
	/**********************��ݼ���ʼ������ֵ***********************/
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
	/****************���ƿ�ݼ�һ����********************/
	setfillstyle(1, LIGHTGRAY);
	bar(keytable.left, keytable.top, keytable.right, keytable.bottom);
	
	setcolor(DARKGRAY);
	rectangle(keytable.left, keytable.top, keytable.right, keytable.bottom);
	/*******************��ʾ��ݼ���Ϣ***********************/
	for(j = 0; j < 12; j++)
	{
		puthz(Func[j].pos.left, Func[j].pos.top, Func[j].title, 16, 16, 8);
		xouttextxy(Bios[j].pos.left, Bios[j].pos.top, Bios[j].title, 8);
	}
	
	while(bioskey(1)!=SPACE)
	{
		if(bioskey(1)!=0&&bioskey(1)!=SPACE&&bioskey(1)!=ESC)
		{	
			bioskey(0);//��ջ�����
		}
		else if(bioskey(1)==ESC)
		{
			return;//�رտ�ݼ�һ����
		}
		newmouse(&MouseX,&MouseY,&a);//ˢ�����
	}
}

void drawAllDARKBox(BOX*h) 
{
	BOX*p=h;
	while(p!=NULL)//�жϵ�ͼָ��h�Ƿ�Ϊ��
	{
		/***************���Ƶ�ͼ*****************/
		if(p->parentPointBackFlag==0)
		{
			drawOneBox(p->centerX,p->centerY,p->boxX,p->boxY,p->lineX,p->lineY,p->content,p->pointFlag, p->pointBackFlag,p->lastLevelSum,p->nextAllSum,p->boldFlag,p->boxColor,p->characterColor,p->characterSize);//����һ��һ����
		}
		p=p->next;
		drawDARKTable();
	}
}

void renewNIGHTBox(BOX*h, Cir Sun, int x1,int y1,int x2,int y2)
{
	int button;//��ʼ��������
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);//������
	setviewport(x1,y1,x2,y2,1);
	setfillstyle(1,LIGHTGRAY);
	bar(x1,y1,x2,y2);//��䱳��
	boxDataGenerate(h);//�������з������������
	drawAllDARKBox(h);//�������еķ���
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
		/************��괦��̫����ť*************/
		if(MouseX >= Sun.centreX-13
		&& MouseX <= Sun.centreX+13
		&& MouseY >= Sun.centreY-13
		&& MouseY <= Sun.centreY+13)
		{
			drawSun(Sun, YELLOW);//̫������
			if(press == 1)//�ж��Ƿ���̫��
			{
				/**********����̫������ת��zen����******/
				setfillstyle(1,WHITE);
				bar(0, 0, 639, 479);
				clrmous(MouseX, MouseY);
				return 41;
			}
		}
		/************����ƿ�̫����ť*************/
		else
		{
			drawSun(Sun, DARKGRAY);
			setviewport(0, 0, 639, 479, 1);
			clrmous(MouseX, MouseY);
			return;
		}
	}
}
/**************����̫����ť************/
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
	char *list[3] = {"��ݼ�", "��ʱ��", "�˳�"};//��ʼ���˵���Ϣ
	register int i = 0;
	register int k = 0;//��ʼ����Ƿ�
	static Rect Table = {570, 40, 630, 110};//��λ�˵���
	const Cir Sun = {600, 140, 10};//��λ̫��
	/****************��ʼ����Ϣ*****************/
	Menu word[3] = {{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"}};
	/*************��Ϣ��ֵ**********************/
	for(k = 0; k < 3; k++)
	{
		word[k].pos.left = Table.left+5; 
		word[k].pos.top = Table.top+5+20*k;
		word[k].pos.right = Table.right;
		word[k].pos.bottom = Table.bottom;
		word[k].title = list[k];
	}
	/************���Ʋ˵�***********/
	setfillstyle(1, LIGHTGRAY);
	bar(Table.left, Table.top, Table.right, Table.bottom);
	setcolor(DARKGRAY);
	rectangle(Table.left, Table.top, Table.right, Table.bottom);
	/**********��ʾ�˵���Ϣ*********/
	for(i=0; i<3; i++)
	{
		puthz(word[i].pos.left, word[i].pos.top, (word+i)->title, 16, 16, 8);
	}
	
	drawSun(Sun, DARKGRAY);//����̫��
}