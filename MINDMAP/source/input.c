#include"MAINHEAD.h"

/*�����˻�*/
void input_1(int xmin,int ymin,int xmax,int ymax,int n,char *string,int *i)
{
	char t='\0';//��ʼ���ַ�������
	settextstyle(1,0,2);
	settextjustify(0,2);//�������ִ�С
	while(1)
	{
		if((*i)<n+1)//���ַ���С���޶�����
		{
			t=bioskey(0);//��ȡ��ֵ
			textcolor(BLACK);//����������ɫ
			if(t!='\n'
			&&t!='\r'
			&&t!=' '
			&&t!=033)//��������Ϊ�س����ո��Լ�ESC��
			{
				if(t!='\b'
				&&((('a'<=t)&&(t<='z'))||(('A'<=t)&&(t<='Z'))||(('0'<=t)&&(t<='9'))))//������Ϊ���ֻ���ĸʱ
				{
					string[*i]=t;//��i���ַ���ֵ
					string[(*i)+1]='\0';//��i+1���ַ�����
					outtextxy(xmin,ymin,string);//��ʾ�ַ�
					(*i)++;//���ӳ��ȱ��
				}
				else if(t=='\b'&&i>0)//�˸��
				{
					setfillstyle(1,15);
					bar(xmin,ymin,xmax,ymax);//�ڸ�����
					(*i)--;//����һ������
					string[*i]='\0';//ɾ�����ָ���
					string[(*i)+1]='\0';
					outtextxy(xmin,ymin,string);//��ʾ�ַ�
				}
			}
		}
		else//���ַ��������޶�����
		{
			string = NULL;//�ַ�������
			(*i) = 0;//�ַ����ȱ�Ǹ���
			setfillstyle(1, WHITE);
			bar(xmin, ymin, xmax, ymax);
			outtextxy(xmin, ymin, "over text");//��ʾ����
			delay(500);
			setfillstyle(1, WHITE);
			bar(xmin, ymin, xmax, ymax);//�����������
			break;
		}
		if(t=='\n'
		||t=='\r'
		||t==' '
		||t==033)
		break;//�˳�����ģʽ
	}
}

/*��������*/
void input_2(int xmin,int ymin,int xmax,int ymax,int n,char *string, int *i)
{
	char t='\0';
	// setfillstyle(1, WHITE);
	// bar(xmin, ymin, xmax, ymax);
	settextstyle(1,0,2);
	settextjustify(0,2);
	while(1)
	{
		if((*i)<n+1)
		{
			t=bioskey(0);
			textcolor(0);
			if(t!='\n'
			&&t!='\r'
			&&t!=' '
			&&t!=033)
			{
				if(t!='\b'
				&&((('a'<=t)&&(t<='z'))
				||(('A'<=t)&&(t<='Z'))
				||(('0'<=t)&&(t<='9'))))
				{
					string[*i]=t;
					string[(*i)+1]='\0';
					outtextxy(xmin+(*i)*16,ymin,"*");		    	
					(*i)++;
				}
				if(t=='\b'&&i>0)//�˸��
				{
					setfillstyle(1,15);
					bar(xmin+((*i)-1)*16,ymin,xmin+(*i)*16,ymax);//�ڸ�����
					(*i)--;//����һ������
					string[*i]='\0';
				}
			}
			if(t=='\n'
			||t=='\r'
			||t==' '
			||t==033)
			break;
		}
		else
		{
			string = NULL;
			(*i) = 0;
			setfillstyle(1, WHITE);
			bar(xmin, ymin, xmax, ymax);
			outtextxy(xmin, ymin, "over text");
			delay(500);
			setfillstyle(1, WHITE);
			bar(xmin, ymin, xmax, ymax);
			break;
		}
	}
}

/*�жϵ�½ʱ�Ƿ�������ȫ*/
int done_user(char *account,char *password)
{
	if(*account!='\0'&&*password!='\0')
		return 1;//���˻����붼��Ϊ��ʱ������1.
	else if(*account=='\0'&&*password!='\0')
		return 2;//���˻�Ϊ�գ����벻Ϊ��ʱ������2.
	else if(*password=='\0'&&*account!='\0')
		return 3;//������Ϊ�գ��˻���Ϊ��ʱ������3.
	else if(*account=='\0'&&*password=='\0')
		return 4;//���˻����붼Ϊ��ʱ������4.
}

/*�ж�ע��ʱ�Ƿ�������ȫ*/
int done_register(char *account,char *password,char *comfirm)
{
	if(*account=='\0')
	{
		if(*password=='\0'&&*comfirm=='\0')
			return 1;//���˻��������Լ�ȷ������ͬʱΪ��ʱ������1.
		if(*password=='\0'&&*comfirm!='\0')
			return 2;//���˻�������Ϊ�գ�ȷ�����벻Ϊ��ʱ������2.
		if(*password!='\0'&&*comfirm=='\0')
			return 3;//���˻���ȷ������Ϊ�գ����벻Ϊ��ʱ������3.
		if(*password!='\0'&&*comfirm!='\0')
			return 4;//���˻�Ϊ�գ����롢ȷ�����벻Ϊ��ʱ������4.
	}
	if(*account!='\0')
	{
		if(*password=='\0'&&*comfirm=='\0')
			return 5;//���˻���Ϊ�գ������Լ�ȷ������ͬʱΪ��ʱ������5.
		if(*password=='\0'&&*comfirm!='\0')
			return 6;//���˻������벻Ϊ�գ�ȷ������Ϊ��ʱ������6.
		if(*password!='\0'&&*comfirm=='\0')
			return 7;//���˻���ȷ������Ϊ�գ�ȷ������Ϊ��ʱ������7.
		if(*password!='\0'&&*comfirm!='\0')
			return 8;//������Ϣ������
	}
}


/*�ж��˻��Ƿ��ѱ�ע��*/
int judge_account(char *account)
{
	User *u=NULL;
	int num=0;
	register int i=0;
	FILE *fp;
	if((fp=fopen("..\\output\\account.txt","rb"))==NULL)
	{
		printf("cannot open this file\n");
		delay(1000);
		exit(0);
	}
	fseek(fp,0L,SEEK_END);
	num=ftell(fp)/sizeof(User);
	rewind(fp);
	for(i=0;i<num;i++)
	{
		if((u=(User*)malloc(sizeof(User)))==NULL)
		{
			printf("memory error register_account");
			delay(1000);
			exit(0);//����ռ䲻�㣬�˳�����
		}
		fseek(fp,i*sizeof(User),SEEK_SET);
		fread(u,sizeof(User),1,fp);
		if(strcmp(u->account,account)==0)
		{
			if(u!=NULL)
			{
				free(u);
				u=NULL;
			}
			if(fclose(fp) != 0)//�ر��ļ�
			{
				printf("\nError in closing file account");
				delay(1000);
				exit(0);
			}
			return 1;
		}
	}
	
	if(i==num)
	{
		if(u!=NULL)//�Ƿ��ڴ�
		{
			free(u);
			u=NULL;
		}
		if(fclose(fp) != 0)//�ر��ļ�
		{
			printf("\nError in closing file account");
			delay(1000);
			exit(0);
		}
		return 2;
	}
}

void account_create(char *account,char *password)
{
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	char *user="..\\output\\";
	User *s=NULL;
	s=(User*)malloc(sizeof(User));
	strcpy(s->account,account);
	strcpy(s->password,password);
	if((fp1=fopen("..\\output\\account.txt","r+"))==NULL)
	{
		printf("cannot open account.txt.\n");
		delay(500);
		exit(0);
	}
	fseek(fp1,0L,SEEK_END);
	fwrite(&s->account,10,1,fp1);
	fwrite(&s->password,10,1,fp1);
	if(fclose(fp1)!= 0)//�ر��ļ�
	{
		printf("\nError in closing file account");
		delay(500);
		exit(0);
	}
	free(s);
	strcat(user, account);
	strcat(user,".txt");//��ȡ�ļ�
	if((fp2 = fopen(user,"rb+")) == NULL)
	{
		if((fp2 = fopen(user,"wb+")) == NULL)
		{
			printf("can't open the file");
			delay(1000);
			exit(0);
		}
	}
	puthz(180,370,"ע��ɹ�",32,36,5);
	delay(1000);
	setfillstyle(1,WHITE);
	bar(180,370,370,410);
	if(fclose(fp2)!= 0)//�ر��ļ�
	{
		printf("\nError in closing file account");
		delay(500);
		exit(0);
	}
}

int login(char *account,char *password,User**pUser)
{
	int num=0;
	register int i=0;
	User *u=NULL;
	FILE *fp;
	if((fp=fopen("..\\output\\account.txt","rb+"))==NULL)//���ļ�
	{
		printf("cannot open this file\n");
		delay(1000);
		exit(0);
	}
	fseek(fp,0,SEEK_END);
	num=ftell(fp)/sizeof(User);//��ȡ��ע�������
	for(i=0;i<num;i++)
	{
		if((u=(User*)malloc(sizeof(User)))==NULL)
		{
			printf("memory error login");
			delay(1000);
			exit(0);//����ռ䲻�㣬�˳�����
		}
		fseek(fp,i*sizeof(User),SEEK_SET);
		fread(u,sizeof(User),1,fp);
		if(strcmp(u->account,account)==0)
		{
			if(strcmp(u->password,password)==0)
			{
				if(u!=NULL)
				{
					// free(u);
					// u=NULL;
				}
				if(fclose(fp) != 0)//�ر��ļ�
				{
					printf("\nError in closing file account");
					delay(1000);
					exit(0);
				}
				*pUser=u;
				return 1;//��½�ɹ�
			}
			else
			{
				if(u!=NULL)
				{
					free(u);
					u=NULL;
				}
				if(fclose(fp) != 0)//�ر��ļ�
				{
					printf("\nError in closing file account");
					delay(1000);
					exit(0);
				}
				return 2;//�������
			}
		}
	}
	if(i==num)
	{
		if(u!=NULL)
		{
			free(u);
			u=NULL;
		}
		if(fclose(fp) != 0)//�ر��ļ�
		{
			printf("\nError in closing file account");
			delay(1000);
			exit(0);
		}
		return 3;//�˻�����
	}
}





