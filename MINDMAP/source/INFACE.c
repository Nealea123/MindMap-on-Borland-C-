#include"MAINHEAD.h"

//图形初始化
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
//主要界面切换
void interfaceSwitch()
{
	int flag=1;
	time_t start;
	BOX*h=boxData0Generate();//生成第一级数据;
	User*pUser=NULL;//用户账号指向
	
	while(1)
	{
		switch(flag)
		{
			case 1:
			{
				flag=startoperation();//开始界面
				break;
			}
			case 2:
			{
				flag=useroperation(&pUser);//用户登入
				break;
			}
			case 3:
			{
				flag=registeroperation();//用户注册
				break;
			}
			case 4:
			{
				flag=mainInterface(h,pUser);//进入思维导图主界面
				break;
			}
			case 5:
			{
				flag=zenInterface(h, start);//进入ZEN（专注）界面
				break;
			}
			case 6:
			{
				flag=darkInterFace(h, start);//进入ZEN夜间模式
				break;
			}
			case 7:
			{
				flag=outlineModeFace(h);//进入思维导图大纲模式界面
				break;
			}
			default:
			{
				return;//退出程序
			}
		}
	}	
}














