/*====================================================
x,y Ϊ������ʾ���ֵ�λ��
s ��ʾ������ʾ�ĺ���
flag ��ʾ����ѡ���ֵĴ�С������flag�Ĳ�ͬ���ò�ͬ�ĺ��ֿ�
part ��ʾ���ּ�ļ��һ��Ϊ16
color ��ʾ���ֵ���ɫ
======================================================*/
#include"PREhz.h"
#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

/*int  outputLetterNum(char ch,int x,int y,int color)
{
	char a[62] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
		'r','s','t','u','v','w','x','y','z','0','1','2','3','4','5','6','7','8','9',
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
		'R','S','T','U','V','W','X','Y','Z'};
	int i;
	for (i = 0;i < 62;i++)
	{
		if (ch == a[i])break;
	}
	if (i < 62)
	{
		char temp[2] = { '\0','\0' };
		temp[0] = ch;
		setcolor(color);
		settextstyle(1,0,2);
		outtextxy(x, y-7,temp);
		return 1;
	}
	else return 0;

}*/

int  outputLetterNum(char ch,int x,int y,int color)
{
	if (31<ch&&127>ch)
	{
		char temp[2] = { '\0','\0' };
		temp[0] = ch;
		setcolor(color);
		settextjustify(LEFT_TEXT,CENTER_TEXT);
		settextstyle(1,0,2);
		outtextxy(x,y+5,temp);
		return 1;
	}
	else return 0;

}



void puthz(int x, int y,char *s,int flag,int part,int color)
{
	FILE *hzk_p;                                       //���庺�ֿ��ļ�ָ��
	unsigned char quma,weima;                 //���庺�ֵ������λ��
	unsigned long offset;                          //���庺�����ֿ��е�ƫ����
	unsigned char mask[] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};  //�������飬������ʾ���ֵ����е�����
	int i,j,pos;


	switch(flag)    //��ͬ��flag��Ӧ��ͬ�ĺ��ֿ⣬ʵ���˺��ֵĴ�С�ɸ�����Ҫ�ı�
	{
		case 16 :
				  {
					 char mat[32];   //16*16�ĺ�����Ҫ32���ֽڵ��������洢
					int y0=y;
					int x0=x;
					// hzk_p = fopen("c:\\myCCD\\SOURSE\\hz\\hzk16","rb");            //ʹ�����·��
					hzk_p = fopen("..\\hz\\HZK16", "rb");
					//hzk_p = fopen("C:\\test\\hz\\HZK16", "rb");
					 if(hzk_p==NULL)
					 {
						settextjustify(LEFT_TEXT,TOP_TEXT);          //�󲿶��룬��������
						settextstyle(GOTHIC_FONT,HORIZ_DIR,1);					//����ʻ������ˮƽ�����24*24����
						outtextxy(10,10,"Can't open hzk16 file!Press any key to quit...");
						getch();
						exit(1);

					}
					while(*s!=NULL)
					{

						while (*s!=NULL)
						{

							/*ʶ��ո񲢴�ӡ�ո�*/
							if (*s == ' ')
							{
								x = x + part;
								s += 1;
								continue;  //��ֹ����ո�ͬʱ����
							}

							/*ʶ���з�������*/
							if (*s == '\n')
							{
								x = x0;
								y0 += flag + 5;
								s += 1;
								continue;   //��ֹ�������ͬʱ����
							}
							if (outputLetterNum(*s, x, y0,color) == 1)
							{
								x = x + part-4;
								s += 1;
								continue;  //��ֹ������ֺ���ĸͬʱ����
							}
		
							y=y0;
							quma=s[0]-0xa0;                      //�������
							weima=s[1]-0xa0;                     //���λ��
							offset=(94*(quma-1)+(weima-1))*32L;   //���Ҫ��ʾ�ĺ������ֿ��ļ��е�ƫ��
							fseek(hzk_p,offset,SEEK_SET);         //�ض�λ�ļ�ָ��
							fread (mat,32,1,hzk_p);            //�����ú��ֵľ����������,1ΪҪ���������

							for(i=0;i<16;i++)
							{
								pos=2*i;       //16*16��������ÿһ���������ֽ�
								for(j=0;j<16;j++)    //һ��һ�е�ɨ�裬��λ��Ϊ��1�ĵ���ʾ����
								{
									if((mask[j%8]&mat[pos+j/8])!=NULL)   //j%8ֻ����0��8֮��ѭ����j/8��0��1֮��ѭ��
									{
										putpixel(x+j,y,color);

									}

								}
								y++;


							}
							/*====================================================
								������һ��������ʾ��
							====================================================*/
							x+=part;        //��x һ��ƫ����part
							s+=2;           //�������ŵ������룬2���ֽڣ�����Ҫ��2

						}
						x=x0;y0+=flag+5; //һ�к�����ʾ���,���´���࿪ʼ������֣���yһ��ƫ����
					}

					break;

				 }


		case 24 :
				  {
					char mat[72];   //24*24����Ҫ72���ֽ����洢
					 int y0=y;
					 int x0=x;
					//hzk_p = fopen("c:\\myCCD\\SOURSE\\hz\\hzk24s","rb");
					 hzk_p = fopen("..\\hz\\HZK24k", "rb");
					if (hzk_p==NULL)
					{
						settextjustify(LEFT_TEXT,TOP_TEXT);          //�󲿶��룬��������
						settextstyle(GOTHIC_FONT,HORIZ_DIR,3);					//����ʻ������ˮƽ�����24*24����
						outtextxy(10,10,"Can't open hzk24 file!Press any key to quit...");
						getch();
						exit(1);

					}
					while(*s!=NULL)
					{
						while( *s!=NULL)
						{
							/*ʶ���з�������*/
							if (*s == '\n')
							{
								x = x0;
								y0 += flag + 12;
								s += 1;
							}
							if (outputLetterNum(*s, x, y0,color) == 1)
							{
								x = x + part-12;
								s += 1;
								continue;  //��ֹ������ֺ���ĸͬʱ����
							}

							y=y0;
							quma=s[0]-0xa0;                      //�������
							weima=s[1]-0xa0;                     //���λ��
							offset=(94*(quma-1)+(weima-1))*72L;
							fseek(hzk_p,offset,SEEK_SET);
							fread (mat,72,1,hzk_p);
							for (i=0;i<24;i++)
							{
								pos=3*i;   //������ÿһ���������ֽ�
								for (j=0;j<24;j++)   // ÿһ����24λ
								{
									if ((mask[j%8]&mat[pos+j/8])!=NULL)
										putpixel(x+j,y,color);

								}
								y++;

							}
							x+=part;
							s+=2;
						}
						x=x0;y0+=flag+12;
					}
						break;
				}

		case 32 :
				  {
					 char mat[128];   //32*32�ĺ�����Ҫ128���ֽڵ��������洢
					int y0=y;
					int x0=x;
					// hzk_p = fopen("c:\\myCCD\\SOURSE\\hz\\hzk32s","rb");
					hzk_p = fopen("..\\hz\\hzk32s", "rb");
					 if(hzk_p==NULL)
					 {
						settextjustify(LEFT_TEXT,TOP_TEXT);          //�󲿶��룬��������
						settextstyle(GOTHIC_FONT,HORIZ_DIR,3);					//����ʻ������ˮƽ�����24*24����						
						outtextxy(10,10,"Can't open hzk32 file!Press any key to quit...");
						 getch();
						 exit(1);

					}
					while(*s!=NULL)
					{
						while(*s!=NULL)
						{
							/*ʶ���з�������*/
							if (*s == '\n')
							{
								x = x0;
								y0 += flag + 16;
								s += 1;
							}
							if (outputLetterNum(*s, x, y0,color) == 1)
							{
								x = x + part-20;
								s += 1;
								continue;  //��ֹ������ֺ���ĸͬʱ����
							}

							y=y0;
							quma=s[0]-0xa0;                      //�������
							weima=s[1]-0xa0;                     //���λ��
							offset=(94*(quma-1)+(weima-1))*128L;
							fseek(hzk_p,offset,SEEK_SET);
							fread (mat,128,1,hzk_p);
							for(i=0;i<32;i++)
							{
								pos=4*i;       //32*32��������ÿһ���������ֽ�
								for(j=0;j<32;j++)
								{
									if((mask[j%8]&mat[pos+j/8])!=NULL)
									{
										putpixel(x+j,y,color);

									}

								}
								y++;


							}
								//������һ��������ʾ��
							x+=part;    //��x һ��ƫ����part
							s+=2;          //�������ŵ������룬2���ֽڣ�����Ҫ��2

						}
						x=x0;y0+=flag+16;   //һ�к�����ʾ��󣬸�yһ��ƫ����
					}
						break;

				 }


		case 48:
				  {
					char mat[288];   //48*48�ĺ�����Ҫ288���ֽڵ��������洢
					int y0=y;
					int x0=x;
					// hzk_p = fopen("c:\\myCCD\\SOURSE\\hz\\hzk48s","rb");
					hzk_p = fopen("..\\hz\\hzk48s", "rb");
					 if(hzk_p==NULL)
					 {
						settextjustify(LEFT_TEXT,TOP_TEXT);          //�󲿶��룬��������
						settextstyle(GOTHIC_FONT,HORIZ_DIR,3);					//����ʻ������ˮƽ�����24*24����
						outtextxy(10,10,"Can't open hzk48 file!Press any key to quit...");
						getch();
						exit(1);

					}
					while(*s!=NULL)
					{
						while (*s!=NULL)
						{
							/*ʶ���з�������*/
							if (*s == '\n')
							{
								x = x0;
								y0 += flag + 24;
								s += 1;
							}

							y=y0;
							quma=s[0]-0xa0;                      //�������
							weima=s[1]-0xa0;                     //���λ��
							offset=(94*(quma-1)+(weima-1))*288L;   //���Ҫ��ʾ�ĺ������ֿ��ļ��е�ƫ��
							fseek(hzk_p,offset,SEEK_SET);         //�ض�λ�ļ�ָ��
							fread (mat,288,1,hzk_p);            //�����ú��ֵľ����������,1ΪҪ���������

							for(i=0;i<48;i++)
							{
								pos=6*i;
								for(j=0;j<48;j++)    //һ��һ�е�ɨ�裬��λ��Ϊ��1�ĵ���ʾ����
								{
									if((mask[j%8]&mat[pos+j/8])!=NULL)   //j%8ֻ����0��8֮��ѭ����j/8��0��1֮��ѭ��
									{
										putpixel(x+j,y,color);

									}

								}
								y++;
							}
								//������һ��������ʾ��
							x+=part;    //��x һ��ƫ����part
							s+=2;          //�������ŵ������룬2���ֽڣ�����Ҫ��2

						}
						x=x0;y0+=flag+24;   //һ�к�����ʾ��󣬸�yһ��ƫ����
					}
						break;

				}

		default:
				  break;

	}

	fclose(hzk_p);
}
/*�������뺯��*/ //8x16�����ֿ� 
int xouttextxy(int x,int y,char *s,int color)
{
	FILE *asc=NULL;
	int i,j,k;
	char *mat,*temp;
	int len;
	long offset;
	int mask;
	
	len=strlen(s);
	if(!len) return 0;//���ַ�����ִ�в��� 
	if((asc=fopen("..\\hz\\ASC16","rb"))==NULL)
	{
		printf("outtextxy can't open asc16!");
		getch();
		exit(1); 
	}
	
	if((mat=(char *)malloc(16*sizeof(char)*len))==NULL)//��ŵ��� 
	{
		printf("Failed!");
		fclose(asc);
		getch();
		exit(1);
	}
	temp=mat;
	for(i=0;i<len;i++)
	{
		offset=(long)16*s[i];//�����ַ����ļ�ƫ�� 
		fseek(asc,offset,SEEK_SET);
		fread(temp,sizeof(char),16,asc);//�������ַ��������mat 
		temp+=16;
	}
	fclose(asc);
	for(i=0;i<len;i++)//ͨ���ŵ���ʾ�ַ� 
	{
		for(j=0;j<16;j++)
		{
			mask=0x80;
			for(k=0;k<8;k++)
			{
				if(mat[i*16+j]&mask)
				putpixel(x+8*i+k,y+j,color);
				mask>>=1;
			}
		}
	}
	free(mat);
	return len;
}


 //��ʾ���ֺ��ַ�������  ֻ�ṩ16*16�ĺ���
void outputhz(int x1,int y1,int x2,int y2,char *s,int color)  
{
	FILE *hzk_p;                                       //���庺�ֿ��ļ�ָ��
	unsigned char quma,weima;                 //���庺�ֵ������λ��
	unsigned long offset;                          //���庺�����ֿ��е�ƫ����
	unsigned char mask[] = {0x180,0x140,0x120,0x110,0x108,0x104,0x102,0x101};  //�������飬������ʾ���ֵ����е�����
	int i,j,pos;			 
	char mat[32];   //16*16�ĺ�����Ҫ32���ֽڵ��������洢
	int y0=y1;
	int x0=x1;
	
	           
	hzk_p = fopen("..\\hz\\HZK16", "rb");               //ʹ�����·��
	//hzk_p = fopen("C:\\test\\hz\\HZK16", "rb");
	 if(hzk_p==NULL)
	 {
		settextjustify(LEFT_TEXT,TOP_TEXT);          //�󲿶��룬��������
		settextstyle(GOTHIC_FONT,HORIZ_DIR,1);					//����ʻ������ˮƽ�����24*24����
		outtextxy(10,10,"Can't open hzk16 file!Press any1 key1 to quit...");
		getch();
		exit(1);

	}
	while(*s!=NULL)
	{

		while (x1<x2 && y1<y2 && (*s!=NULL))   //�綨��Χ
		{

			/*ʶ��ո񲢴�ӡ�ո�*/
			if (*s == ' ')
			{
				x1 = x1 + 10;
				s += 1;
				continue;  //��ֹ����ո�ͬʱ����
			}

			/*ʶ���з�������*/
			if (*s == '\n')
			{
				x1 = x0;
				y0 += 10 + 5;
				s += 1;
				continue;   //��ֹ�������ͬʱ����
			}
			if (*s == '	')
			{
				x1 = x0;
				y0 += 10 + 5;
				s += 1;
				continue;   //��ֹ�������ͬʱ����
			}
			if (outputLetterNum2(*s, x1, y0,color) == 1)
			{
				x1 = x1 + 10;
				s += 1;
				continue;  //��ֹ������ֺ���ĸͬʱ����
			}

			y1=y0;
			quma=s[0]-0x1a0;                      //�������
			weima=s[1]-0x1a0;                     //���λ��
			offset=(94*(quma-1)+(weima-1))*32L;   //���Ҫ��ʾ�ĺ������ֿ��ļ��е�ƫ��
			fseek(hzk_p,offset,SEEK_SET);         //�ض�λ�ļ�ָ��
			fread (mat,32,1,hzk_p);            //�����ú��ֵľ����������,1ΪҪ���������

			for(i=0;i<16;i++)
			{
				pos=2*i;       //16*16��������ÿһ���������ֽ�
				for(j=0;j<16;j++)    //һ��һ�е�ɨ�裬��λ��Ϊ��1�ĵ���ʾ����
				{
					if((mask[j%8]&mat[pos+j/8])!=NULL)   //j%8ֻ����0��8֮��ѭ����j/8��0��1֮��ѭ��
					{
						putpixel(x1+j,y1,color);

					}

				}
				y1++;


			}
			/*====================================================
				������һ��������ʾ��
			====================================================*/
			x1+=16;        //��x1 һ��ƫ����part
			s+=2;           //�������ŵ������룬2���ֽڣ�����Ҫ��2

		}
		x1=x0;y0+=16+5; //һ�к�����ʾ���,���´���࿪ʼ������֣���y1һ��ƫ����
	}

	fclose(hzk_p);
}

int  outputLetterNum2(char ch,int x,int y,int color)
{
	if (31<ch&&127>ch)
	{
		char temp[2] = { '\0','\0' };
		temp[0] = ch;
		xouttextxy(x,y,temp,color);
		return 1;
	}
	else return 0;

}	 
//��ʾ���ּӴֺ���
void puthzcu(int x, int y,char *s,int flag,int part,int color)   
 {
    puthz(x,y,s,flag,part,color);
    puthz(x+1,y,s,flag,part,color);     
 }
//��ʾʱ�任�У�x1x2y1y2Ϊ�綨��Χ
void outtime(int x1,int y1,int x2,int y2,char *s,int color)   
{
	int y0=y1;
	int x0=x1;  //��¼ԭxֵyֵ
 
    while(*s!=NULL)
	{
		while (x1<x2 && y1<y2 && (*s!=NULL))   //�綨��Χ
		{

			/*ʶ��ո񲢴�ӡ�ո�*/
			if (*s == ' ')
			{
				x1 = x1 + 10;
				s += 1;
				continue;  //��ֹ����ո�ͬʱ����
			}

			/*ʶ���з�������*/
			if (*s == '\n')
			{
				x1 = x0;
				y0 += 10 + 5;
				s += 1;
				continue;   //��ֹ�������ͬʱ����
			}
			if (outputLetterNum2(*s, x1, y0,color) == 1)
			{
				x1 = x1 + 10;
				s += 1;
				continue;  //��ֹ������ֺ���ĸͬʱ����
			}
		}
	    y0 += 10 + 6;
        x1 = x0;		
	}	
}
