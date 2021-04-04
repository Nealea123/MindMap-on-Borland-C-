#include"MAINHEAD.h"

/*输入账户*/
void input_1(int xmin,int ymin,int xmax,int ymax,int n,char *string,int *i)
{
	char t='\0';//初始化字符，赋空
	settextstyle(1,0,2);
	settextjustify(0,2);//设置文字大小
	while(1)
	{
		if((*i)<n+1)//当字符数小于限定长度
		{
			t=bioskey(0);//获取键值
			textcolor(BLACK);//设置字体颜色
			if(t!='\n'
			&&t!='\r'
			&&t!=' '
			&&t!=033)//当按键不为回车，空格以及ESC键
			{
				if(t!='\b'
				&&((('a'<=t)&&(t<='z'))||(('A'<=t)&&(t<='Z'))||(('0'<=t)&&(t<='9'))))//当按键为数字或字母时
				{
					string[*i]=t;//第i个字符赋值
					string[(*i)+1]='\0';//第i+1个字符赋空
					outtextxy(xmin,ymin,string);//显示字符
					(*i)++;//增加长度标记
				}
				else if(t=='\b'&&i>0)//退格键
				{
					setfillstyle(1,15);
					bar(xmin,ymin,xmax,ymax);//遮盖文字
					(*i)--;//减少一个字数
					string[*i]='\0';//删除文字赋空
					string[(*i)+1]='\0';
					outtextxy(xmin,ymin,string);//显示字符
				}
			}
		}
		else//当字符数超过限定长度
		{
			string = NULL;//字符串赋空
			(*i) = 0;//字符长度标记赋空
			setfillstyle(1, WHITE);
			bar(xmin, ymin, xmax, ymax);
			outtextxy(xmin, ymin, "over text");//提示超过
			delay(500);
			setfillstyle(1, WHITE);
			bar(xmin, ymin, xmax, ymax);//清除框中内容
			break;
		}
		if(t=='\n'
		||t=='\r'
		||t==' '
		||t==033)
		break;//退出输入模式
	}
}

/*输入密码*/
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
				if(t=='\b'&&i>0)//退格键
				{
					setfillstyle(1,15);
					bar(xmin+((*i)-1)*16,ymin,xmin+(*i)*16,ymax);//遮盖文字
					(*i)--;//减少一个字数
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

/*判断登陆时是否输入完全*/
int done_user(char *account,char *password)
{
	if(*account!='\0'&&*password!='\0')
		return 1;//当账户密码都不为空时，返回1.
	else if(*account=='\0'&&*password!='\0')
		return 2;//当账户为空，密码不为空时，返回2.
	else if(*password=='\0'&&*account!='\0')
		return 3;//当密码为空，账户不为空时，返回3.
	else if(*account=='\0'&&*password=='\0')
		return 4;//当账户密码都为空时，返回4.
}

/*判断注册时是否输入完全*/
int done_register(char *account,char *password,char *comfirm)
{
	if(*account=='\0')
	{
		if(*password=='\0'&&*comfirm=='\0')
			return 1;//当账户、密码以及确认密码同时为空时，返回1.
		if(*password=='\0'&&*comfirm!='\0')
			return 2;//当账户、密码为空，确认密码不为空时，返回2.
		if(*password!='\0'&&*comfirm=='\0')
			return 3;//当账户、确认密码为空，密码不为空时，返回3.
		if(*password!='\0'&&*comfirm!='\0')
			return 4;//当账户为空，密码、确认密码不为空时，返回4.
	}
	if(*account!='\0')
	{
		if(*password=='\0'&&*comfirm=='\0')
			return 5;//当账户不为空，密码以及确认密码同时为空时，返回5.
		if(*password=='\0'&&*comfirm!='\0')
			return 6;//当账户和密码不为空，确认密码为空时，返回6.
		if(*password!='\0'&&*comfirm=='\0')
			return 7;//当账户和确认密码为空，确认密码为空时，返回7.
		if(*password!='\0'&&*comfirm!='\0')
			return 8;//所有信息都输入
	}
}


/*判断账户是否已被注册*/
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
			exit(0);//分配空间不足，退出程序
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
			if(fclose(fp) != 0)//关闭文件
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
		if(u!=NULL)//是否内存
		{
			free(u);
			u=NULL;
		}
		if(fclose(fp) != 0)//关闭文件
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
	if(fclose(fp1)!= 0)//关闭文件
	{
		printf("\nError in closing file account");
		delay(500);
		exit(0);
	}
	free(s);
	strcat(user, account);
	strcat(user,".txt");//获取文件
	if((fp2 = fopen(user,"rb+")) == NULL)
	{
		if((fp2 = fopen(user,"wb+")) == NULL)
		{
			printf("can't open the file");
			delay(1000);
			exit(0);
		}
	}
	puthz(180,370,"注册成功",32,36,5);
	delay(1000);
	setfillstyle(1,WHITE);
	bar(180,370,370,410);
	if(fclose(fp2)!= 0)//关闭文件
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
	if((fp=fopen("..\\output\\account.txt","rb+"))==NULL)//打开文件
	{
		printf("cannot open this file\n");
		delay(1000);
		exit(0);
	}
	fseek(fp,0,SEEK_END);
	num=ftell(fp)/sizeof(User);//读取已注册的组数
	for(i=0;i<num;i++)
	{
		if((u=(User*)malloc(sizeof(User)))==NULL)
		{
			printf("memory error login");
			delay(1000);
			exit(0);//分配空间不足，退出程序
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
				if(fclose(fp) != 0)//关闭文件
				{
					printf("\nError in closing file account");
					delay(1000);
					exit(0);
				}
				*pUser=u;
				return 1;//登陆成功
			}
			else
			{
				if(u!=NULL)
				{
					free(u);
					u=NULL;
				}
				if(fclose(fp) != 0)//关闭文件
				{
					printf("\nError in closing file account");
					delay(1000);
					exit(0);
				}
				return 2;//密码错误
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
		if(fclose(fp) != 0)//关闭文件
		{
			printf("\nError in closing file account");
			delay(1000);
			exit(0);
		}
		return 3;//账户错误
	}
}





