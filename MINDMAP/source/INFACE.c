#include"MAINHEAD.h"

//ͼ�γ�ʼ��
void interfaceInit()
{
	int graphdrive,graphmode;
	graphdrive = DETECT;
	initgraph(&graphdrive,&graphmode,"..\\..\\BORLANDC\\BGI");
	cleardevice();
	setcolor(BACKGOUNDCOLOR);
	bar(0,0,639,479);
	mouseinit();
}
//��Ҫ�����л�
void interfaceSwitch()
{
	int flag=1;
	time_t start;
	BOX*h=boxData0Generate();//���ɵ�һ������;
	User*pUser=NULL;//�û��˺�ָ��
	
	while(1)
	{
		switch(flag)
		{
			case 1:
			{
				flag=startoperation();//��ʼ����
				break;
			}
			case 2:
			{
				flag=useroperation(&pUser);//�û�����
				break;
			}
			case 3:
			{
				flag=registeroperation();//�û�ע��
				break;
			}
			case 4:
			{
				flag=mainInterface(h,pUser);//����˼ά��ͼ������
				break;
			}
			case 5:
			{
				flag=zenInterface(h, start);//����ZEN��רע������
				break;
			}
			case 6:
			{
				flag=darkInterFace(h, start);//����ZENҹ��ģʽ
				break;
			}
			case 7:
			{
				flag=outlineModeFace(h);//����˼ά��ͼ���ģʽ����
				break;
			}
			default:
			{
				return;//�˳�����
			}
		}
	}	
}














