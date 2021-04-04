#include"MAINHEAD.h"
#include"FILEOPER.h"
//���뱾�˺ŵ�˼ά��ͼ�ļ���Ϣ
void readMoreMindmapFile(User*pUser,MAPF**pMapFile)
{
	char address[]="..\\USERS\\";
	char hzm[]=".dat";
	char allName[50]={'\0'};
	MAPF*hM=NULL,*p=NULL,*p1=NULL;
	FILE*fp=NULL;
	
	
	memset(allName,'\0',sizeof(allName));
	strcat(allName,address);
	strcat(allName,pUser->account);
	strcat(allName,"file");
	strcat(allName,hzm);
	fp=fopen(allName,"rb");
	
	
	if(fp==NULL)
	{
		fp=fopen(allName,"w");
		fclose(fp);
	}
	else
	{
		rewind(fp);
		hM=(MAPF*)malloc(sizeof(MAPF));
		fread(hM,sizeof(MAPF),1,fp);
		hM->fileSum=0;
		p1=hM;
		p=hM;
		while(p->next!=NULL)
		{
			p=NULL;
			p=(MAPF*)malloc(sizeof(MAPF));
			fseek(fp,sizeof(MAPF),1);
			fread(p,sizeof(MAPF),1,fp);
			p1->next=p;  
			p1=p;
			hM->fileSum++;
		}
		fclose(fp);
		
		hM->usess=pUser;
		*pMapFile=hM;
		memset(allName,'\0',sizeof(allName));
		strcat(allName,address);
		strcat(allName,hM->usess->account);
		strcat(allName,"FILE");
		mkdir(allName);
		return;
		
	}
	hM=(MAPF*)malloc(sizeof(MAPF));
	*pMapFile=hM;
	hM->fileSum=0;
	hM->usess=pUser;
	hM->next=NULL;
	memset(allName,'\0',sizeof(allName));
	strcat(allName,address);
	strcat(allName,hM->usess->account);
	strcat(allName,"FILE");
	mkdir(allName);
}
//�������浯����
void drawSaveFile(char*fileName)
{
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setfillstyle(1,15);
	bar(120,180,520,300);
	setcolor(8);
	rectangle(120,180,520,300);
	
	puthz(150, 190, "�����¿������뱣����ļ����ƣ�", 16, 16, 0);
	puthz(150, 210, "(��Ӣ����ĸ������,�ҳ��Ȳ�����10λ)", 16, 16, 0);
	puthz(160, 270, "ȷ��", 16, 16, 0);
	puthz(460, 270, "ȡ��", 16, 16, 0);
	rectangle(130, 230,510,260);
	puthz(130, 240,fileName,16,16,0);
}
//����˼ά��ͼ����
void saveMindmap(BOX*h,MAPF*hM,MAPF**NM)
{
	BOX*p=h;
	FILE*fp=NULL;
	char fileName[14]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
	int flag=6;
	char address[]="..\\USERS\\";
	char hzm[]=".dat";
	char allName[50];
	char fatherName[50];
	MAPF*pM=NULL,*pM1=NULL;
	memset(allName,'\0',sizeof(allName));
	memset(fatherName,'\0',sizeof(fatherName));
	
	if(*NM!=NULL)
	{
		strcat(allName,address);
		strcat(allName,hM->usess->account);
		strcat(allName,"FILE");
		strcat(allName,"\\");
		strcat(allName,(*NM)->mindmapFileName);
		strcat(allName,hzm);
		
		fp=fopen(allName,"wb");
		rewind(fp);
		while(p!=NULL)
		{
			fwrite(p,sizeof(BOX),1,fp);
			fseek(fp,sizeof(BOX),1);
			p=p->next;
		}
		fclose(fp);
		fp=NULL;
		return;
	}
	
	
	if(hM->fileSum>=15)
	{
		most15File();
		return;
	}
	while(1)
	{
		
		flag=getInputFileName(h,fileName);
		if(flag==1)
		{
			break;
		}
		else if(flag==0)
		{
			return;
		}
	}
	strcat(allName,address);
	strcat(allName,hM->usess->account);
	strcat(allName,"FILE");
	strcat(allName,"\\");
	strcat(allName,fileName);
	strcat(allName,hzm);
	fp=fopen(allName,"rb");
	rewind(fp);
	memset(allName,'\0',sizeof(allName));
	while(fp!=NULL)
	{
		theSameName();
		
		while(1)
		{
			flag=getInputFileName(h,fileName);
			if(flag==1)
			{
				break;
			}
			else if(flag==0)
			{
				return;
			}
		}
		fclose(fp);
		fp=NULL;
		memset(allName,'\0',sizeof(allName));
		strcat(allName,address);
		strcat(allName,hM->usess->account);
		strcat(allName,"FILE");
		strcat(allName,"\\");
		strcat(allName,fileName);
		strcat(allName,hzm);
		fp=fopen(allName,"rb");
		rewind(fp);
		
	}
	
	fclose(fp);
	
	memset(allName,'\0',sizeof(allName));
	strcat(allName,address);
	strcat(allName,hM->usess->account);
	strcat(allName,"FILE");
	strcat(allName,"\\");
	strcat(allName,fileName);
	strcat(allName,hzm);
	
	fp=fopen(allName,"wb");
	rewind(fp);
	while(p!=NULL)
	{
		fwrite(p,sizeof(BOX),1,fp);
		fseek(fp,sizeof(BOX),1);
		p=p->next;
	}
	fclose(fp);
	
	
	pM=hM;
	hM->fileSum=0;
	while(pM->next!=NULL)
	{
		pM=pM->next;
		hM->fileSum++;
	}
	pM1=(MAPF*)malloc(sizeof(MAPF));
	
	pM->next=pM1;
	
	memset(allName,'\0',sizeof(allName));
	strcat(allName,fileName);
	strcat(allName,hzm);
	strcpy(pM1->mindmapFileName,allName);
	pM1->lastAddress=pM1;
	pM1->usess=hM->usess;
	pM1->next=NULL;
	*NM=pM1;
	
	strcat(fatherName,address);
	strcat(fatherName,hM->usess->account);
	strcat(fatherName,"FILE");
	strcat(fatherName,hzm);
	
	
	
	pM=hM;
	fp=fopen(fatherName,"wb+");
	rewind(fp);
	while(pM!=NULL)
	{
		fwrite(pM,sizeof(MAPF),1,fp);
		fseek(fp,sizeof(MAPF),1);
		pM=pM->next;
	}
	hM->fileSum++;
	fclose(fp);
}
//�������ļ�������
void drawOpenMap(MAPF*hM,MAPF**cM,char*flag)
{
	int i=0;
	MAPF*pM=NULL;
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setfillstyle(1,15);
	bar(120,80,520,420);
	setcolor(8);
	rectangle(120,80,520,420);
	
	puthz(150, 80, "��ѡ��򿪱��˻���˼ά��ͼ�ļ���", 16, 16, 0);
	puthz(160, 400, "ȷ��", 16, 16, 0);
	puthz(460, 400, "ȡ��", 16, 16, 0);

	
	pM=hM;
	
	for(i=0;i<hM->fileSum;i++)
	{
		pM=pM->next;
		setcolor(0);
		rectangle(130,105+20*i,140,115+20*i);
		
		puthz(150,100+20*i,pM->mindmapFileName,16,16,0);
		if(flag[i]==1)
		{
			drawGo(135,105+7+20*i,0);
			*cM=pM;
		}
	}
}
//ѡ��Ҫ�򿪵�˼ά��ͼ
int chooseOpenMap(MAPF*hM,MAPF**cM,MAPF**NM)
{
	char flag[17]={0};
	int a=0,i=0;
	drawOpenMap(hM,cM,flag);
	while(1)
	{
		newmouse(&MouseX,&MouseY,&a);
		for(i=0;i<hM->fileSum;i++)
		{
			if(mouse_press(130,105+20*i,140,115+20*i)==1)
			{
				delay(200);
				memset(flag,0,sizeof(flag));
				flag[i]=1;				
				drawOpenMap(hM,cM,flag);
			}
		}
		if(mouseIn(160, 400,200,420))
		{
			clrmous(MouseX,MouseY);
			puthz(160, 400, "ȷ��", 16, 16, THZCOLOR);
			MouseX--;MouseY--;
			newmouse(&MouseX,&MouseY,&a);
			while(mouseIn(160, 400,200,420))
			{
				newmouse(&MouseX,&MouseY,&a);
				if(press==1)
				{
					clrmous(MouseX,MouseY);
					setfillstyle(1,15);
					bar(120,80,520,420);
					for(i=0;i<hM->fileSum;i++)
					{
						if(flag[i]==1)
						{
							*NM=*cM;
						}
					}
					return 1;
				}
			}
			if(mouseIn(160, 400,200,420)==0)
			{
				clrmous(MouseX,MouseY);
				puthz(160, 400, "ȷ��", 16, 16, 0);
			}
		}
		if(mouseIn(460, 400,500,420))
		{
			clrmous(MouseX,MouseY);
			puthz(460, 400, "ȡ��", 16, 16, THZCOLOR);
			MouseX--;MouseY--;
			newmouse(&MouseX,&MouseY,&a);
			while(mouseIn(460, 400,500,420))
			{
				newmouse(&MouseX,&MouseY,&a);
				if(press==1)
				{
					clrmous(MouseX,MouseY);
					setfillstyle(1,15);
					bar(120,80,520,420);
					return 0;
				}
			}
			if(mouseIn(460, 400,500,420)==0)
			{
				clrmous(MouseX,MouseY);
				puthz(460, 400, "ȡ��", 16, 16, 0);
			}
		}
	
		
	}
	
	
}
//��˼ά��ͼ
void openMindmap(BOX*h,MAPF*hM,MAPF**NM)
{
	FILE*fp=NULL;
	BOX*p=NULL;
	BOX*p1=NULL;
	MAPF*cM=NULL,*cM1=NULL;
	int  flag=2;
	char address[]="..\\USERS\\";
	char hzm[]=".dat";
	char allName[50];
	flag=drawCloseRight();
	if(flag==1)
	{
		if(NM!=NULL)
		{
			saveMindmap(h,hM,NM);
		}
		if(hM->fileSum>=15&&NM==NULL)
		{
			most15File();
			return;
		}
	}
	flag=2;
	
	
	memset(allName,'\0',sizeof(allName));
	cM1=NM;
	flag=chooseOpenMap(hM,&cM,NM);
	if(flag==0)
	{
		return;
	}
	else if(flag==1&&*NM==NULL)
	{
		return;
	}
	clearAllBox(h);
	
	strcat(allName,address);
	strcat(allName,hM->usess->account);
	strcat(allName,"FILE");
	strcat(allName,"\\");
	strcat(allName,cM->mindmapFileName);
	strcat(allName,hzm);
	fp=fopen(allName,"rb");
	
	
	
	rewind(fp);
	fread(h,sizeof(BOX),1,fp);
	p1=h;
	p=h;
	while(p->next!=NULL)
	{
		p=NULL;
		if((p=(BOX*)malloc(sizeof(BOX)*5))==NULL)
		{
			setcolor(0);
			settextjustify(LEFT_TEXT,TOP_TEXT);          //�󲿶��룬��������
			settextstyle(GOTHIC_FONT,HORIZ_DIR,1);					//����ʻ������ˮƽ�����24*24����
			outtextxy(10,10,"No enough memory!Press any key to quit...");
			getch();
			exit(1);
		}
		else
		{
			free(p);
			p=NULL;
		}
		
		p=(BOX*)malloc(sizeof(BOX));
		p1->next=p;
		p1=p;
		fseek(fp,sizeof(BOX),1);
		fread(p,sizeof(BOX),1,fp);
	}
	fclose(fp);
	rightenNewAdress(h);
	
}
//����˼ά��ͼ��ͼ��ַ
void rightenNewAdress(BOX*h)
{
	BOX*p=NULL,*p1=NULL;
	int i=0;
	
	p=h;
	while(p!=NULL)
	{
		for(i=0;i<=p->nextLevelSum;i++)
		{
			p1=h;
			while(p1!=NULL)
			{
				if(p->lastNextBox[p->nextLevelSum-i]==p1->lastFile)
				{
					p->lastNextBox[p->nextLevelSum-i]=p1;
					break;
				}
				p1=p1->next;
			}
		}
		p=p->next;
	}
	
	p=h;
	p->last=NULL;
	while(p!=NULL)
	{
		if(p->next!=NULL)
		{
			p1=p->next;
			p1->last=p;
		}
		p=p->next;
	}
	
	p=h;
	while(p!=NULL)
	{
		p->lastFile=p;
		p=p->next;
	}
}
//�����Ƿ񱣴浱ǰ�ļ����ѿ�
int drawCloseRight()
{
	int a=0;
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setfillstyle(1,15);
	bar(240,210,400,270);
	setcolor(8);
	rectangle(240,210,400,270);
	
	puthz(260, 220, "�Ƿ񱣴浱ǰ�ļ�?", 16, 16, 0);
	puthz(260, 250, "ȷ��", 16, 16, 0);
	puthz(360, 250, "ȡ��", 16, 16, 0);
	
	while(1)
	{
		if(bioskey(1)!=0&&bioskey(1)!=SPACE&&bioskey(1)!=ESC)
		{	
			bioskey(0);
		}
		if(mouseIn(260, 240,300,260))
		{
			clrmous(MouseX,MouseY);
			puthz(260, 250, "ȷ��", 16, 16, THZCOLOR);
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
				puthz(260, 250, "ȷ��", 16, 16, 0);
			}
		}
		if(mouseIn(360, 240,400,260))
		{
			clrmous(MouseX,MouseY);
			puthz(360, 250, "ȡ��", 16, 16, THZCOLOR);
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
				puthz(360, 250, "ȡ��", 16, 16, 0);
			}
		}
		newmouse(&MouseX,&MouseY,&a);
	}
	clrmous(MouseX,MouseY);
	setfillstyle(1,15);
	bar(240,210,400,270);
}
//�ر�˼ά��ͼ�ļ�
void closeMindmap(BOX*h,MAPF*hM,MAPF**cM)
{
	int flag=2;
	if(hM->fileSum>=15)
	{
		most15File();
		return;
	}
	flag=drawCloseRight();
	if(flag==1)
	{
		if(*cM==NULL)//���ļ�
		{
			saveMindmap(h,hM,cM);
			return;
		}
		else//���ļ�
		{
			saveMindmap(h,hM,cM);
			*cM=NULL;
		}
	}
	*cM=NULL;
	clearAllBox(h);
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
	memset(h->content,'\0',100);
	h->lastNextBox[0]=NULL;
	h->next=NULL;
	h->last=NULL;
	h->lastFile=h;
}
//�����ļ�������
int getInputFileName(BOX*h,char*fileName)
{
	int a;
	int anum = 0;
	
	drawSaveFile(fileName);
	
	while(1)
	{
		newmouse(&MouseX,&MouseY,&a);	
		if(mouse_press(130, 230,510,260)==1)
		{
			clrmous(MouseX,MouseY);//������
			input_1(130+1, 230+1,510-1,260-1,10,fileName,&anum);//�����û��˺�
		}
		if(bioskey(1)!=0&&bioskey(1)!=SPACE&&bioskey(1)!=ESC)
		{	
			bioskey(0);
		}
		if(mouseIn(160, 270,200,290))
		{
			clrmous(MouseX,MouseY);
			puthz(160, 270, "ȷ��", 16, 16, THZCOLOR);
			MouseX--;MouseY--;
			newmouse(&MouseX,&MouseY,&a);
			while(mouseIn(160, 270,200,290))
			{
				newmouse(&MouseX,&MouseY,&a);
				if(press==1)
				{
					clrmous(MouseX,MouseY);
					setfillstyle(1,15);
					bar(120,180,520,300);
					return 1;
				}
			}
			if(mouseIn(160, 270,200,290)==0)
			{
				clrmous(MouseX,MouseY);
				puthz(160, 270, "ȷ��", 16, 16, 0);
			}
		}
		if(mouseIn(460, 270,500,290))
		{
			clrmous(MouseX,MouseY);
			puthz(460, 270, "ȡ��", 16, 16, THZCOLOR);
			MouseX--;MouseY--;
			newmouse(&MouseX,&MouseY,&a);
			while(mouseIn(460, 270,500,290))
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
			if(mouseIn(460, 270,500,290)==0)
			{
				clrmous(MouseX,MouseY);
				puthz(460, 270, "ȡ��", 16, 16, 0);
			}
		}
	}	
}
//����ͬ���ļ����ѵ�����
void theSameName()
{
	int button;
	
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setfillstyle(1,15);
	bar(120,200,520,280);
	setcolor(8);
	rectangle(120,200,520,280);
	
	puthz(150, 210, "�ļ�����������������", 16, 16, 0);
	puthz(255, 260, "����ո���˳�����", 16, 16, 0);
	puthz(287, 260, "�ո��", 16, 16, 4);
	
	while(bioskey(1)!=SPACE)
	{
		if(bioskey(1)!=0&&bioskey(1)!=SPACE)
		{	
			bioskey(0);
		}
		newmouse(&MouseX,&MouseY,&button);
	}
}
//˼ά��ͼ����������������
void most15File()
{
	int button;
	
	setviewport(0,0,639,479,1);
	clrmous(MouseX,MouseY);
	setfillstyle(1,15);
	bar(120,200,520,280);
	setcolor(8);
	rectangle(120,200,520,280);
	
	puthz(150, 210, "���ֻ�ܽ���15��˼ά��ͼ", 16, 16, 0);
	puthz(255, 260, "����ո���˳�����", 16, 16, 0);
	puthz(287, 260, "�ո��", 16, 16, 4);
	
	while(bioskey(1)!=SPACE)
	{
		if(bioskey(1)!=0&&bioskey(1)!=SPACE)
		{	
			bioskey(0);
		}
		newmouse(&MouseX,&MouseY,&button);
	}
}