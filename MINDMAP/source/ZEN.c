#include"MAINHEAD.h"

int zenInterface(BOX*h, long start)
{
	char *list[5] = {"ҹ��", "��ݼ�", "��ʱ��", "��ʽ", "�˳�"};//��ʼ��zen����ڵ�����
	register int i = 0;//��ʼ������ַ�i
	register int k = 0;//��ʼ������ַ�k
	int state = 0;//��ʼ��״̬���
	const Rect Table = {570, 25, 630, 210};//zen���λ��ֵ
	Menu word[5] = {{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"},
					{{0, 0, 0, 0}, "\0"}};//��ʼzen���

	BOX*pBox = NULL, *pPoint = NULL, *pPress = NULL;//һ��ָ��
	
	setviewport(0,0,639,479,1);
	setfillstyle(1, h->lastLevelFlag);
	bar(0, 0, 639, 479);//��䱳��
	
	for(k = 0; k < 5; k++)//zen���ֵ
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
	bar(Table.left+1, Table.top+1, Table.right-1, Table.bottom-1);//���Ʊ��

	if(h != NULL)//��ͼ��Ϊ��
	{
		drawAllZENBox(h);//����˼ά��ͼ
	}
	else//��ͼΪ��
	h = boxData0Generate( );//���ɵ�һ������

	for(i = 0; i < 5; i++)
	{
		puthz(word[i].pos.left, word[i].pos.top, (word+i)->title, 16, 16, 8);//��ʾzen����
	}
	if(start != 0)
	{
		time(&start);//��ȡ��ʼʱ��
	}
	
	while(1)
	{
		state = mouseZEN(h, &pBox, &pPoint, &pPress, Table, start, list);//����״̬ѡ��
		switch(state)
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
			case 40://��ת��ҹ��ģʽ
			{
				return 6;
			}
			case 41://��ת��������
			{
				return 4;
			}
		}
		if(state!=1&&state!=9)//��û���ƶ�����ѡ�е�ͼʱ
		{
			renewZENBox(h,0,0,639,479);//ˢ��˼ά��ͼ
		}
	}
}

int TableOp(Rect Table, BOX*h, BOX**ppPress, long start, char **list)
{
	int a = 0;//��������ʼ��
	int state = 0;//״̬������ʼ��
	register int i = 0;//��ǳ�ʼ��
	time_t end;//����ʱ��
	
	while(1)
	{
		
		setviewport(0, 0, 639, 479, 1);
		newmouse(&MouseX, &MouseY, &a);//�������
		
		for(i = 0; i < 5; i++)//���������Ӧ��������ʱ����������
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
			state = 2;//����ڡ���ݼ����ϴ���state = 2
		}
		
		else if(MouseX >= Table.left
		&& MouseX <= Table.right
		&& MouseY >= (Table.top+5+80)
		&& MouseY <= (Table.top+21+80))
		{
			state = 3;//����ڡ���ʱ���ϴ���state = 3
		}
		
		else if(mouse_press(Table.left, Table.top+5, Table.right, Table.top+21)==1)
		{
			state = 1;//�����ҹ�䣬���ݲ���state = 1
		}
		
		else if(mouse_press(Table.left, Table.top+5+120, Table.right, Table.top+21+120)==1)
		{
			state = 4;//�������ʽ�����ݲ���state = 4
		}
		
		else if(mouse_press(Table.left, Table.top+5+160, Table.right, Table.top+21+160)==1)
		{
			state = 5;//������˳������ݲ���state = 5
		}
		
		else if(!(MouseX <= Table.right
		&& MouseY <= Table.bottom
		&& MouseX >= Table.left
		&& MouseY >= Table.top))
		{
			state = 6;//��겻��zen���ڣ����ݲ���state = 6
		}
		
		switch(state)//�ж�state��ֵ
		{
			case 1://����ҹ��ģʽ2
			{
				clrmous(MouseX, MouseY);
				clearviewport();
				setfillstyle(1, LIGHTGRAY);
				bar(0, 0, 639, 479);
				mouseinit();
				return 40;
			}
			case 2://�鿴��ݼ�
			KeyShow(h, Table);
			break;
			case 3://�鿴zenģʽ��ʱ���¼
			TimeShow(h, start, Table);
			break;
			case 4://ѡ����ʽ
			boxType(h,*ppPress);
			break;
			case 5://����������
			{
				clrmous(MouseX, MouseY);
				clearviewport();
				setfillstyle(1, WHITE);
				bar(0, 0, 639, 479);
				return 41;
			}
			case 6://���뵼ͼ�༭ģʽ
			return ;
		}
	}
}

int mouseZEN(BOX*h, BOX**ppBox, BOX**ppPoint, BOX**ppPress, Rect Table, long start, char **list)
{
	int a = 0;//��������ʼ��
	int onePress = 0;//��갴����ʼ��
	int flag = 0;//��ǳ�ʼ��
	
	while(1)
	{
		if(!(MouseX >= Table.left
		&& MouseX <= Table.right
		&& MouseY >= Table.top
		&& MouseY <= Table.bottom))//��겻��zen����
		{
			setviewport(0, 0, 639, 479, 1);
			drawAllZENBox(h);//���µ�ͼ
			while(!(MouseX >= Table.left
			&& MouseX <= Table.right
			&& MouseY >= Table.top
			&& MouseY <= Table.bottom))
			{
				setviewport(0, 0, 639, 479, 1);
				newmouse(&MouseX, &MouseY,&a);//ˢ�����
				
				setviewport(0, 0, 639, 479, 1);
				*ppBox = traversalBoxCycleInZen(h, 0, 0, h->lastLevelFlag);
				*ppPress = traversalPressBoxInZen(h,h->lastLevelFlag);
				*ppPoint = traversalPointCycleInZen(h, 0, 0);//����˼ά��ͼ����
				
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
						return 1;//ѡ��һ��
					}
					else if(*ppPoint != NULL)
					{
						return 2;//ѡ�нڵ�
					}
				}
				
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
						return 10;//�ƶ�����
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
					else if(bioskey(1) == 0x320d
					|| bioskey(1) == 0x011b)//����Ctrl��M������esc��
					{
						bioskey(0);
						return 41;//����������
					}
					else if(bioskey(1) == 0x1e01)//����Ctrl��A��
					{
						bioskey(0);
						KeyShow(h, Table);
					}
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
						return 9;//�ƶ�
					}
					else if(bioskey(1) != 0)
					{
						bioskey(0);//��ջ�����
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
					bioskey(0);//��ջ�����
				}
				
				setviewport(0, 0, 639, 479, 0);
				*ppPress = traversalPressBoxInZen(h,h->lastLevelFlag);
				
				setviewport(0, 0, 639, 479, 1);
				newmouse(&MouseX, &MouseY, &a);//ˢ�����
				flag = TableOp(Table, h, ppPress, start, list);//����zen��ģʽ
				
				return flag;//�Żؽ������
			}
			clrmous(MouseX, MouseY);//�������
		}
	}
}

void TimeShow(BOX*h, long start, Rect Table)
{
	char *TM[3] = {"00", "00", "00"};//��ʼ���ַ��͵�ʱ����
	char *unit[3] = {"ʱ", "��", "��"};
	int tm[3] = {0, 0, 0};//��ʼ��int�͵�ʱ����
	int a = 0;//����������
	register int i = 0;//���ݱ�Ƿ�
	int t = 0;//ʱ���¼
	time_t end;//����ʱ��
	const Rect timeshow = {457, 106, 569, 148};//�����ʱ��λ��
	
	while(bioskey(1)!=SPACE)//�����¿ո��
	{
		time(&end);//��ȡ����ʱ��
		/*��ʾ��ʱ���ϵĺ���*/
		setcolor(DARKGRAY);
		rectangle(timeshow.left, timeshow.top, timeshow.right, timeshow.bottom);
		setfillstyle(1, 15);
		bar(timeshow.left+1, timeshow.top+1, timeshow.right-1, timeshow.bottom-1);
		setcolor(DARKGRAY);
		puthz(timeshow.left+2, timeshow.top+2, "רעʱ��", 16, 16, DARKGRAY);
		/*����ʱ����*/
		t = (long)difftime(end, start);
		tm[0] = t/3600;
		tm[1] = (t-tm[0]*3600)/60;
		tm[2] = t-tm[0]*3600-tm[1]*60;
		/*��ʾʱ��*/
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
			return;//�˳�����
		}
		newmouse(&MouseX,&MouseY,&a);//ˢ�����
	}
	
}

void KeyShow(BOX*h, Rect Table)
{
	/*��ʼ����ʾ���ַ�*/
	char *key1[] = {"�˳�","ɾ��","����������","��������֮��","��������֮ǰ","���븸����","˼ά��ͼģʽ","���Ƶ�ͼ","���Ƶ�ͼ","���Ƶ�ͼ","���Ƶ�ͼ","��ͼ��λ"};
	char *key2[] = {"Esc","Delete","Tab","Enter","Ctrl+Enter","Ctrl+F","Ctrl+M","Ctrl+[","Ctrl+]","Ctrl+-","Ctrl+\\","Ctrl+O"};
	/*��ʼ����Ƿ�*/
	register int i = 0;
	register int j = 0;
	int a = 0;//��������ʼ��
	/*��ʼ����ݼ���Ϣ*/
	Rect keytable = {360, 20, 570, 250};
	Menu Func[12] = {{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}};
	Menu Bios[12] = {{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, 
					{{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}, {{0, 0, 0, 0}, "\0"}};
	/*��ݼ���Ϣ��ֵ*/				
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
	/*���ƿ�ݼ����*/
	setfillstyle(1, WHITE);
	bar(keytable.left, keytable.top, keytable.right, keytable.bottom);
	setcolor(LIGHTGRAY);
	rectangle(keytable.left, keytable.top, keytable.right, keytable.bottom);
	/*��ʾ��ݼ���Ϣ*/
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
			return;//�رտ�ݼ�
		}
		newmouse(&MouseX,&MouseY,&a);//ˢ�����
	}
	renewZENBox(h,0,0,639,479);//ˢ�µ�ͼ
}


void renewZENBox(BOX*h,int x1,int y1,int x2,int y2)
{
	int button = 0;//��������ʼ��
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);//������
	setviewport(x1,y1,x2,y2,1);
	setfillstyle(1,h->lastLevelFlag);
	bar(x1,y1,x2,y2);//��䱳��
	boxDataGenerate(h);//�������з������������
	drawAllZENBox(h);//�������еķ���
	drawtable();//����zen��
	setviewport(0,0,639,479,1);//���ˢ��
	MouseX-=1;
	newmouse(&MouseX,&MouseY,&button);
}

void drawAllZENBox(BOX*h) //����zenģʽ�µ�˼ά��ͼ
{
	BOX*p=h;	
	while(p!=NULL)
	{
		if(p->parentPointBackFlag==0)
		{
			drawOneBox(p->centerX,p->centerY,p->boxX,p->boxY,p->lineX,p->lineY,p->content,p->pointFlag, p->pointBackFlag,p->lastLevelSum,p->nextAllSum,p->boldFlag,p->boxColor,p->characterColor,p->characterSize);//����һ��һ����
		}
		p=p->next;
		drawtable();
	}
}

void drawtable()
{
	/*********************zen���ʼ��**************************/
	char *list[5] = {"ҹ��", "��ݼ�", "��ʱ��", "��ʽ", "�˳�"};
	static Rect Table = {570, 25, 630, 210};
	register int i = 0;
	register int k = 0;
	Menu word[5] = {{{0, 0, 0, 0}, "\0"},
				{{0, 0, 0, 0}, "\0"},
				{{0, 0, 0, 0}, "\0"},
				{{0, 0, 0, 0}, "\0"},
				{{0, 0, 0, 0}, "\0"}};
	/************************zen��ֵ***************************/			
	for(k = 0; k < 5; k++)
	{
		word[k].pos.left = Table.left+5; 
		word[k].pos.top = Table.top+5+40*k;
		word[k].pos.right = Table.right;
		word[k].pos.bottom = Table.bottom+21;
		word[k].title = list[k];
	}	
    /**************************����zen��**************************/
	setcolor(LIGHTGRAY);
	rectangle(Table.left, Table.top, Table.right, Table.bottom);
	setfillstyle(1, WHITE);
	bar(Table.left+1, Table.top+1, Table.right-1, Table.bottom-1);
	for(i = 0; i < 5; i++)
	{
		puthz(word[i].pos.left, word[i].pos.top, (word+i)->title, 16, 16, 8);
	}	
}