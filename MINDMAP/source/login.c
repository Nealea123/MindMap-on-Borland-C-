#include"MAINHEAD.h"

/*��Ļ��ʼ��*/
void initscreen()
{
    int graphdriver=DETECT;
	int graphmode;
	initgraph(&graphdriver,&graphmode,"..\\..\\BORLANDC\\BGI");//��ʼ��VGA
	cleardevice();
	setfillstyle(1, WHITE);
	bar(0, 0, 639, 479);//��䱳��
	mouseinit();//����ʼ��
}

/*����ʼ����*/
void startscreen()
{
	setfillstyle(1,WHITE);
	bar(0,0,639,479);//��䱳��
	setcolor(BLACK);
	rectangle(240,96,400,198);
	rectangle(240,288,400,384);
	puthz(290,130,"��¼",32,40,BLACK);
	puthz(290,320,"ע��",32,40,BLACK);//���Ƶ�¼ע�ᰴť
}

/*��ע���û��ĵ�¼����*/
void userscreen()
{
	setfillstyle(1, WHITE);
	bar(0, 0, 639, 479);
	puthzcu(170,195,"�˺�",16,16,BLUE);
	puthzcu(170,245,"����",16,16,BLUE);
	setcolor(BLACK);
	rectangle(219,189,481,215);
	rectangle(219,239,481,265);
	setfillstyle(1,WHITE);
	bar(220,190,480,214);
	bar(220,240,480,264);//�����˻������������
	setcolor(BLACK);
	rectangle(250,280,310,310);
	rectangle(390,280,450,310);
	puthzcu(265,285,"ȷ��",16,16,BLACK);
	puthzcu(405,285,"����",16,16,BLACK);//����ȷ�Ϻͷ��ؼ�
	//getch();
	//closegraph();
}

/*�û�ע�����*/
void registerscreen()
{
	setfillstyle(1, WHITE);
	bar(0, 0, 639, 479);//��䱳��
	puthzcu(162,155,"�˺�",16,16,BLACK);
	puthzcu(160,195,"����",16,16,BLACK);
	puthzcu(142,235,"ȷ������",16,16,BLACK);
	setfillstyle(1,WHITE);
	bar(220,150,480,174);
	bar(220,190,480,214);
	bar(220,230,480,254);
	setcolor(BLACK);
	rectangle(219,149,481,175);
	rectangle(219,189,481,215);
	rectangle(219,229,481,255);//�����˺š����롢ȷ���������������
	setcolor(BLACK);
	rectangle(250,280,310,310);
	rectangle(390,280,450,310);
	puthzcu(265,285,"ע��",16,16,BLACK);
	puthzcu(405,285,"����",16,16,BLACK);//����ע��ͷ��ؼ�
	//getch();
	//closegraph();
}

/*��ʼ����Ĳ���*/
int startoperation()
{
	int a=0;//a�������θ����
	int area=0;//area���������������
	int screen=0;//screen��ʾ��Ҫת�Ľ��棬�ı���ݷ�ʽ
	MouseS=0;//���ɼ�ͷ
	startscreen();
	while(1)//����ѭ�������ڸ������
	{
		newmouse(&MouseX,&MouseY,&a);//�������
    	if((MouseX>240&&MouseX<400)
			&&((MouseY>96&&MouseY<198)||(MouseY>288&&MouseY<384)))
	    	area=1;//������Ƶ���ťʱ�����������
	    else
	    	area=0;//�����������ط���ʱ�����ͼ��Ϊ��ͷ
        if(area==1)
        {
	        MouseS=1;//���Σ�ʹ���������
			if (mouse_press(240,96,400,198)==1)//�ڵ�¼��ť����������ʱ���л����û�����
	        {
				screen=1;//���滻�ɵ�¼����
				cleardevice();//����
				clrmous(MouseX,MouseY);
				break;//����ѭ��
	        }
	        if (mouse_press(240,288,400,384)==1)//��ע�ᰴť����������ʱ���л���ע�����
    	    {
				screen=2;//���滻��ע�����
				cleardevice();//����
				clrmous(MouseX,MouseY);
				break;//����ѭ��
	        }
        }
        if(area==0)
        {
	        MouseS=0;//���ɼ�ͷ
        }
	}
    if(screen==1) 
	{
		return 2;//�û��������
	}
	if(screen==2)
	{
		return 3;//ע��������
	}
}

/*�û��������*/
int useroperation(User**pUser)
{
	int a=0;//aΪ��꺯��һ������
	int area=0;//area���������������
	int anum = 0;//����˻�Ŀǰ����ĳ���
	int pnum = 0;//�������Ŀǰ����ĳ���
	char account[10+1] = {'\0'};
	char password[10+1] = {'\0'};//�˻�������
	
	
	userscreen();//�����û�����
	while(1)//����ѭ�������ڸ������
	{
		newmouse(&MouseX,&MouseY,&a);//�������
		if((MouseY>=280&&MouseY<=310)
			&&((MouseX>=250&&MouseX<=310)||(MouseX>=390&&MouseX<=450)))
			area=1;//������Ƶ���ťʱ�����������
		else if((MouseX>=220&&MouseX<=480)
			&&((MouseY>=190&&MouseY<=214)||(MouseY>=240&&MouseY<=264)))
			area=2;//������Ƶ������ʱ������ɹ��
		else area=0;//�����������ط���ʱ�����ͼ��Ϊ��ͷ
		newmouse(&MouseX,&MouseY,&a);//ˢ�����
		switch(area)//�ж�area��ֵ���Ӷ��ж�����λ�ã������ı�MouseS���ı�������״
		{
			case 0://���ͼ��Ϊ��ͷ
			MouseS=0;
			break;
			case 1://���������
			MouseS=1;
			break;
			case 2://����ɹ��
			MouseS=2;
			break;
		}
		if(bioskey(1)!=0)
		{
			bioskey(0);//���������
		}
		
		if(mouse_press(220,190,480,214)==1)//����˻�����������û��˺�
		{
			clrmous(MouseX,MouseY);//������
			input_1(220,190,480,214,10,account,&anum);//�����˻�
		}
		if(mouse_press(220,240,480,264)==1)//�����������������û�����
		{
			clrmous(MouseX,MouseY);//������
			input_2(220,240,480,264,10,password,&pnum);//��������
		}
		
		if(mouse_press(250,280,310,310)==1)//�����¼��ť
		{
			switch(done_user(account,password))//�ж��˻������Ƿ�������ȫ
			{
				case 1://���˻����붼��Ϊ��
				{
					switch(login(account,password,pUser))//�ж��Ƿ��¼�ɹ�
					{
						case 1://��½�ɹ�
						{
							return 4;//���������ݵ�inface��������ת����������
						}
						case 2://�������
						{
							puthz(180,370,"�������",32,36,BLACK);//��ʾ���������
							delay(2000);//��ʱ�������ʾ
							/*���ƾ��Σ����ԭ����ʾ*/
							setfillstyle(1,WHITE);
							bar(180,370,330,410);
							/*����������ڵ�����*/
							setfillstyle(1,WHITE);
							bar(220,240,480,264);
							/*���ԭ�ȵ������ַ���������*/
							*password=NULL;
							pnum=0;
						}
						break;
						case 3://�˺Ŵ���
						{
							puthz(180,370,"�޴��˻�",32,36,BLACK);//��ʾ���޴��˻���
							delay(2000);//��ʱ�������ʾ
							/*���ƾ��Σ����ԭ����ʾ*/
							setfillstyle(1,WHITE);
							bar(180,370,330,410);
							/*������ڵ�����*/
							setfillstyle(1,WHITE);
							bar(220,190,480,214);
							bar(220,240,480,264);
							/*���ԭ�ȵ��˻������ַ���������*/
							*account=NULL;
							*password=NULL;
							anum = 0;
							pnum = 0;
						}
						break;
					}
				}
				case 2://���˻�Ϊ�գ����벻Ϊ��
				{
					puthz(180,370,"�������˻�",32,36,BLACK);//��ʾ���������˻���
					delay(2000);//��ʱ�������ʾ
					/*���ƾ��Σ����ԭ����ʾ*/
					setfillstyle(1,WHITE);
					bar(180,370,370,410);
					/*������ڵ�����*/
					setcolor(WHITE);
					setfillstyle(1,WHITE);
					bar(220,190,480,214);
					bar(220,240,480,264);
					/*����ַ���������*/
					*account=NULL;
					*password=NULL;
					anum = 0;
					pnum = 0;
				}
				break;
				case 3://������Ϊ�գ��˻���Ϊ��
				{
					puthz(180,370,"����������",32,36,BLACK);//��ʾ�����������롱
					delay(2000);//��ʱ�������ʾ
					/*���ƾ��Σ����ԭ����ʾ*/
					setcolor(WHITE);
					setfillstyle(1,WHITE);
					bar(180,370,370,410);
					/*������ڵ�����*/
					setcolor(WHITE);
					setfillstyle(1,WHITE);
					bar(220,240,480,264);
				}
				case 4://��������˻���û������ʱ
				{
					puthz(180,370,"��������Ϣ",32,36,BLACK);//��ʾ����������Ϣ��
					delay(2000);//��ʱ�������ʾ
					/*���ƾ��Σ����ԭ����ʾ*/
					setcolor(WHITE);
					setfillstyle(1,WHITE);
					bar(180,370,370,410);
				}
			}
		}
				
		if(mouse_press(390,280,450,310)==1)//����갴�·��ؼ�ʱ�����ؿ�ʼ���档
		{
			*account = NULL;
			*password = NULL;
			anum = 0;
			pnum = 0;//�˻��������Լ�ȷ���������ݸ���
			clrmous(MouseX,MouseY);//�������
			cleardevice();//����
			startscreen();//���ƿ�ʼ����
			return 1;//��ʼ����Ĳ���
		}
	}
}

/*ע��������*/
int registeroperation()
{
	int a=0;//aΪ��꺯��һ������
	int anum = 0;//����˻�Ŀǰ����ĳ���
	int pnum = 0;//�������Ŀǰ����ĳ���
	int cnum = 0;//���ȷ������Ŀǰ����ĳ���
	char account[10+1] = {'\0'};
	char password[10+1] = {'\0'};
	char comfirm[10+1] = {'\0'};//�ֱ�Ϊ�˻������룬ȷ�����룬���г�ʼ��
	
	registerscreen();//����ע�����
	while(1)//����ѭ�������ڸ������
	{
		newmouse(&MouseX,&MouseY,&a);//�������
		if((MouseY>=280&&MouseY<=310)
			&&((MouseX>=250&&MouseX<=310)||(MouseX>=390&&MouseX<=450)))
			MouseS=1;//���������
		else if((MouseX>=220&&MouseX<=480)
			&&((MouseY>=150&&MouseY<=174)||(MouseY>=190&&MouseY<=214)||(MouseY>=230&&MouseY<=254)))
			MouseS=2;//����ɹ��
		else 
			MouseS=0;//���ͼ��Ϊ��ͷ
		newmouse(&MouseX,&MouseY,&a);//�������
		
		if(mouse_press(220,150,480,174)==1)//����û������
		{
			clrmous(MouseX,MouseY);//������
			input_1(220,150,480,174,10,account,&anum);//�����û��˺�
		}
		else if(mouse_press(220,190,480,214)==1)//����û������
		{
			clrmous(MouseX,MouseY);//������
			input_2(220,190,480,214,10,password,&pnum);//��������
		}
		else if(mouse_press(220,230,480,254)==1)//�������ȷ�Ͽ�
		{
			clrmous(MouseX,MouseY);//������
			input_2(220,230,480,254,10,comfirm,&cnum);//����ȷ������
		}
		/*���ע���*/
		if(mouse_press(250,280,310,310)==1)
		{
			switch(done_register(account,password,comfirm))//�ж���Ϣ�Ƿ�������ȫ
			{
				case 1://��Ϣ��û������
				{
					puthz(180,370,"��������Ϣ",32,36,BLACK);//��ʾ����������Ϣ��
					delay(2000);//��ʱ�������ʾ
					/*���ƾ��Σ����ԭ����ʾ*/
					setfillstyle(1,WHITE);
					bar(180,370,340,410);
				}
				break;
				case 2://�˻�������û�����룬ֻ����ȷ������
				{
					puthz(180,370,"�������˻�������",32,36,BLACK);//��ʾ���������˻������롱
					delay(2000);//��ʱ�������ʾ
					/*���ƾ��Σ����ԭ����ʾ*/
					setfillstyle(1,WHITE);
					bar(180,370,470,410);
					/*���ȷ�������ַ���*/
					setfillstyle(1,WHITE);
					bar(220,230,480,254);
					*comfirm = NULL;
					cnum = 0;
				}
				break;
				case 3://�˻�������û�����룬ֻ��������
				{
					puthz(180,370,"�������˻���ȷ������",32,36,BLACK);//��ʾ���������˻���ȷ�����롱
					delay(2000);//��ʱ�������ʾ
					/*���ƾ��Σ����ԭ����ʾ*/
					setfillstyle(1,WHITE);
					bar(180,370,560,410);
					/*��������ַ���*/
					setfillstyle(1,WHITE);
					bar(220,190,480,214);
					*password = NULL;
					pnum = 0;
				}
				break;
				case 4://�˻�û�����룬ֻ���������ȷ������
				{
					puthz(180,370,"�������˻�",32,36,BLACK);//��ʾ���������˻���
					delay(2000);//��ʱ�������ʾ
					/*���ƾ��Σ����ԭ����ʾ*/
					setfillstyle(1,WHITE);
					bar(180,370,370,410);
					setfillstyle(1,WHITE);
					bar(220,190,480,214);
					bar(220,230,480,254);
					/*���ԭ�ȵ������Լ�ȷ�������ַ���������*/
					*password = NULL;
					*comfirm = NULL;
					pnum = 0;
					cnum = 0;
				}
				break;
				case 5://ֻ�����˻���û�����������ȷ������
				{
					puthz(180,370,"�����������ȷ������",32,36,BLACK);//��ʾ"�����������ȷ������"
					delay(2000);//��ʱ�������ʾ
					/*���ƾ��Σ����ԭ����ʾ*/
					setfillstyle(1,WHITE);
					bar(180,370,560,410);
				}
				break;
				case 6://�Ѿ������˻���ȷ�����룬û����������
				{
					puthz(180,370,"����������",32,36,BLACK);//��ʾ�����������롱
					delay(2000);
					setfillstyle(1,WHITE);
					bar(180,370,560,410);//������ʾ
					/*ȷ�����븳��*/
					setfillstyle(1,WHITE);
					bar(220,190,480,214);
					*comfirm = NULL;
					cnum = 0;
				}
				break;
				case 7://�Ѿ������˻������룬û������ȷ������
				{
					puthz(180,370,"������ȷ������",32,36,BLACK);//��ʾ"����������"
					delay(2000);//��ʱ�������ʾ
					/*���ƾ��Σ����ԭ����ʾ*/
					setfillstyle(1,WHITE);
					bar(180,370,560,410);
					setfillstyle(1,WHITE);
					/*�����Լ�ȷ�����븳��*/
					bar(220,190,480,214);
					bar(220,230,480,254);
					*password = NULL;
					*comfirm = NULL;
					pnum = 0;
					cnum = 0;
				}
				break;
				case 8://��Ϣȫ������
				{
					switch(judge_account(account))//�ж��Ƿ��û��ѱ�ע��
					{
						case 1://�û��ѱ�ע��
						{
							puthz(180,370,"�û��ѱ�ע��",32,36,BLACK);//��ʾ���û��ѱ�ע�ᡰ
							delay(2000);//��ʱ�������ʾ
							/*���ƾ��Σ����ԭ����ʾ*/
							setcolor(WHITE);
							setfillstyle(1,WHITE);
							bar(180,370,440,410);
							/*������ڵ�����*/
							setfillstyle(1,WHITE);
							bar(220,150,480,174);
							bar(220,190,480,214);
							bar(220,230,480,254);
							*account = NULL;
							*password = NULL;
							*comfirm = NULL;
							anum = 0;
							pnum = 0;
							cnum = 0;
						}
						break;
						case 2://�û�δ��ע��
						switch(strcmp(password,comfirm))//�ж��������������Ƿ����Ǻ�
						{
							case 0:
							{
								account_create(account,password);//�����û�
								clrscr();
								return 2;
							}
							default:
							{
								puthz(180,370,"������ȷ������",32,36,BLACK);//��ʾ"������ȷ������"
								delay(2000);//��ʱ�������ʾ
								/*���ƾ��Σ����ԭ����ʾ*/
								setfillstyle(1,WHITE);
								bar(180,370,440,410);
								/*����������ڵ����ݣ�ͬʱ�����ȷ�����븳��*/
								setfillstyle(1,WHITE);
								bar(220,190,480,214);
								bar(220,230,480,254);
								*password = NULL;
								*comfirm = NULL;
								pnum = 0;
								cnum = 0;
							}
							break;
						}
						break;
					}
				}
				break;
			}
		}
		if (mouse_press(390,280,450,310)==1)//���ؿ�ʼ����
		{
			*account = NULL;
			*password = NULL;
			*comfirm = NULL;
			anum = 0;
			pnum = 0;
			cnum = 0;//�˻��������Լ�ȷ���������ݸ���
			clrmous(MouseX,MouseY);//�������
			cleardevice();//����
			startscreen();//���ƿ�ʼ����
			return 1;//��ʼ����Ĳ���
		}
	}
}