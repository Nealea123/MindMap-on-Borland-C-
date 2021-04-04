#include"MAINHEAD.h"

/*屏幕初始化*/
void initscreen()
{
    int graphdriver=DETECT;
	int graphmode;
	initgraph(&graphdriver,&graphmode,"..\\..\\BORLANDC\\BGI");//初始化VGA
	cleardevice();
	setfillstyle(1, WHITE);
	bar(0, 0, 639, 479);//填充背景
	mouseinit();//鼠标初始化
}

/*画开始界面*/
void startscreen()
{
	setfillstyle(1,WHITE);
	bar(0,0,639,479);//填充背景
	setcolor(BLACK);
	rectangle(240,96,400,198);
	rectangle(240,288,400,384);
	puthz(290,130,"登录",32,40,BLACK);
	puthz(290,320,"注册",32,40,BLACK);//绘制登录注册按钮
}

/*已注册用户的登录界面*/
void userscreen()
{
	setfillstyle(1, WHITE);
	bar(0, 0, 639, 479);
	puthzcu(170,195,"账号",16,16,BLUE);
	puthzcu(170,245,"密码",16,16,BLUE);
	setcolor(BLACK);
	rectangle(219,189,481,215);
	rectangle(219,239,481,265);
	setfillstyle(1,WHITE);
	bar(220,190,480,214);
	bar(220,240,480,264);//绘制账户、密码输入框
	setcolor(BLACK);
	rectangle(250,280,310,310);
	rectangle(390,280,450,310);
	puthzcu(265,285,"确认",16,16,BLACK);
	puthzcu(405,285,"返回",16,16,BLACK);//绘制确认和返回键
	//getch();
	//closegraph();
}

/*用户注册界面*/
void registerscreen()
{
	setfillstyle(1, WHITE);
	bar(0, 0, 639, 479);//填充背景
	puthzcu(162,155,"账号",16,16,BLACK);
	puthzcu(160,195,"密码",16,16,BLACK);
	puthzcu(142,235,"确认密码",16,16,BLACK);
	setfillstyle(1,WHITE);
	bar(220,150,480,174);
	bar(220,190,480,214);
	bar(220,230,480,254);
	setcolor(BLACK);
	rectangle(219,149,481,175);
	rectangle(219,189,481,215);
	rectangle(219,229,481,255);//绘制账号、密码、确认密码三个输入框
	setcolor(BLACK);
	rectangle(250,280,310,310);
	rectangle(390,280,450,310);
	puthzcu(265,285,"注册",16,16,BLACK);
	puthzcu(405,285,"返回",16,16,BLACK);//绘制注册和返回键
	//getch();
	//closegraph();
}

/*开始界面的操纵*/
int startoperation()
{
	int a=0;//a用来传参给鼠标
	int area=0;//area传递鼠标所在区域
	int screen=0;//screen表示所要转的界面，改变操纵方式
	MouseS=0;//鼠标成箭头
	startscreen();
	while(1)//不断循环，便于更新鼠标
	{
		newmouse(&MouseX,&MouseY,&a);//更新鼠标
    	if((MouseX>240&&MouseX<400)
			&&((MouseY>96&&MouseY<198)||(MouseY>288&&MouseY<384)))
	    	area=1;//当鼠标移到按钮时，鼠标变成手势
	    else
	    	area=0;//当鼠标在其余地方的时候，鼠标图案为箭头
        if(area==1)
        {
	        MouseS=1;//传参，使鼠标变成手势
			if (mouse_press(240,96,400,198)==1)//在登录按钮按下鼠标左键时，切换到用户界面
	        {
				screen=1;//界面换成登录界面
				cleardevice();//清屏
				clrmous(MouseX,MouseY);
				break;//跳出循环
	        }
	        if (mouse_press(240,288,400,384)==1)//在注册按钮按下鼠标左键时，切换到注册界面
    	    {
				screen=2;//界面换成注册界面
				cleardevice();//清屏
				clrmous(MouseX,MouseY);
				break;//跳出循环
	        }
        }
        if(area==0)
        {
	        MouseS=0;//鼠标成箭头
        }
	}
    if(screen==1) 
	{
		return 2;//用户界面操作
	}
	if(screen==2)
	{
		return 3;//注册界面操作
	}
}

/*用户界面操作*/
int useroperation(User**pUser)
{
	int a=0;//a为鼠标函数一个参数
	int area=0;//area传递鼠标所在区域
	int anum = 0;//标记账户目前输入的长度
	int pnum = 0;//标记密码目前输入的长度
	char account[10+1] = {'\0'};
	char password[10+1] = {'\0'};//账户与密码
	
	
	userscreen();//绘制用户界面
	while(1)//不断循环，便于更新鼠标
	{
		newmouse(&MouseX,&MouseY,&a);//更新鼠标
		if((MouseY>=280&&MouseY<=310)
			&&((MouseX>=250&&MouseX<=310)||(MouseX>=390&&MouseX<=450)))
			area=1;//当鼠标移到按钮时，鼠标变成手势
		else if((MouseX>=220&&MouseX<=480)
			&&((MouseY>=190&&MouseY<=214)||(MouseY>=240&&MouseY<=264)))
			area=2;//当鼠标移到输入框时，鼠标变成光标
		else area=0;//当鼠标在其余地方的时候，鼠标图案为箭头
		newmouse(&MouseX,&MouseY,&a);//刷新鼠标
		switch(area)//判断area的值，从而判断鼠标的位置，进而改变MouseS，改变鼠标的形状
		{
			case 0://鼠标图案为箭头
			MouseS=0;
			break;
			case 1://鼠标变成手势
			MouseS=1;
			break;
			case 2://鼠标变成光标
			MouseS=2;
			break;
		}
		if(bioskey(1)!=0)
		{
			bioskey(0);//清除缓存区
		}
		
		if(mouse_press(220,190,480,214)==1)//点击账户输入框，输入用户账号
		{
			clrmous(MouseX,MouseY);//清除鼠标
			input_1(220,190,480,214,10,account,&anum);//输入账户
		}
		if(mouse_press(220,240,480,264)==1)//点击密码输入框，输入用户密码
		{
			clrmous(MouseX,MouseY);//清除鼠标
			input_2(220,240,480,264,10,password,&pnum);//输入密码
		}
		
		if(mouse_press(250,280,310,310)==1)//点击登录按钮
		{
			switch(done_user(account,password))//判断账户密码是否都输入完全
			{
				case 1://当账户密码都不为空
				{
					switch(login(account,password,pUser))//判断是否登录成功
					{
						case 1://登陆成功
						{
							return 4;//见参数传递到inface，将界面转换到主界面
						}
						case 2://密码错误
						{
							puthz(180,370,"密码错误",32,36,BLACK);//提示“密码错误”
							delay(2000);//延时后清除提示
							/*绘制矩形，清除原有提示*/
							setfillstyle(1,WHITE);
							bar(180,370,330,410);
							/*清理密码框内的内容*/
							setfillstyle(1,WHITE);
							bar(220,240,480,264);
							/*清除原先的密码字符串的内容*/
							*password=NULL;
							pnum=0;
						}
						break;
						case 3://账号错误
						{
							puthz(180,370,"无此账户",32,36,BLACK);//提示“无此账户”
							delay(2000);//延时后清除提示
							/*绘制矩形，清除原有提示*/
							setfillstyle(1,WHITE);
							bar(180,370,330,410);
							/*清理框内的内容*/
							setfillstyle(1,WHITE);
							bar(220,190,480,214);
							bar(220,240,480,264);
							/*清空原先的账户密码字符串的内容*/
							*account=NULL;
							*password=NULL;
							anum = 0;
							pnum = 0;
						}
						break;
					}
				}
				case 2://当账户为空，密码不为空
				{
					puthz(180,370,"请输入账户",32,36,BLACK);//提示“请输入账户”
					delay(2000);//延时后清除提示
					/*绘制矩形，清除原有提示*/
					setfillstyle(1,WHITE);
					bar(180,370,370,410);
					/*清理框内的内容*/
					setcolor(WHITE);
					setfillstyle(1,WHITE);
					bar(220,190,480,214);
					bar(220,240,480,264);
					/*清除字符串的内容*/
					*account=NULL;
					*password=NULL;
					anum = 0;
					pnum = 0;
				}
				break;
				case 3://当密码为空，账户不为空
				{
					puthz(180,370,"请输入密码",32,36,BLACK);//提示“请输入密码”
					delay(2000);//延时后清除提示
					/*绘制矩形，清除原有提示*/
					setcolor(WHITE);
					setfillstyle(1,WHITE);
					bar(180,370,370,410);
					/*清理框内的内容*/
					setcolor(WHITE);
					setfillstyle(1,WHITE);
					bar(220,240,480,264);
				}
				case 4://当密码和账户都没有输入时
				{
					puthz(180,370,"请输入信息",32,36,BLACK);//提示“请输入信息”
					delay(2000);//延时后清除提示
					/*绘制矩形，清除原有提示*/
					setcolor(WHITE);
					setfillstyle(1,WHITE);
					bar(180,370,370,410);
				}
			}
		}
				
		if(mouse_press(390,280,450,310)==1)//当鼠标按下返回键时，返回开始界面。
		{
			*account = NULL;
			*password = NULL;
			anum = 0;
			pnum = 0;//账户、密码以及确认密码内容赋空
			clrmous(MouseX,MouseY);//擦除鼠标
			cleardevice();//清屏
			startscreen();//绘制开始界面
			return 1;//开始界面的操纵
		}
	}
}

/*注册界面操作*/
int registeroperation()
{
	int a=0;//a为鼠标函数一个参数
	int anum = 0;//标记账户目前输入的长度
	int pnum = 0;//标记密码目前输入的长度
	int cnum = 0;//标记确认密码目前输入的长度
	char account[10+1] = {'\0'};
	char password[10+1] = {'\0'};
	char comfirm[10+1] = {'\0'};//分别为账户，密码，确认密码，进行初始化
	
	registerscreen();//绘制注册界面
	while(1)//不断循环，便于更新鼠标
	{
		newmouse(&MouseX,&MouseY,&a);//更新鼠标
		if((MouseY>=280&&MouseY<=310)
			&&((MouseX>=250&&MouseX<=310)||(MouseX>=390&&MouseX<=450)))
			MouseS=1;//鼠标变成手势
		else if((MouseX>=220&&MouseX<=480)
			&&((MouseY>=150&&MouseY<=174)||(MouseY>=190&&MouseY<=214)||(MouseY>=230&&MouseY<=254)))
			MouseS=2;//鼠标变成光标
		else 
			MouseS=0;//鼠标图案为箭头
		newmouse(&MouseX,&MouseY,&a);//更新鼠标
		
		if(mouse_press(220,150,480,174)==1)//点击用户输入框
		{
			clrmous(MouseX,MouseY);//清除鼠标
			input_1(220,150,480,174,10,account,&anum);//输入用户账号
		}
		else if(mouse_press(220,190,480,214)==1)//点击用户输入框
		{
			clrmous(MouseX,MouseY);//清除鼠标
			input_2(220,190,480,214,10,password,&pnum);//输入密码
		}
		else if(mouse_press(220,230,480,254)==1)//点击密码确认框
		{
			clrmous(MouseX,MouseY);//清除鼠标
			input_2(220,230,480,254,10,comfirm,&cnum);//输入确认密码
		}
		/*点击注册键*/
		if(mouse_press(250,280,310,310)==1)
		{
			switch(done_register(account,password,comfirm))//判断信息是否都输入完全
			{
				case 1://信息都没有输入
				{
					puthz(180,370,"请输入信息",32,36,BLACK);//提示“请输入信息”
					delay(2000);//延时后清除提示
					/*绘制矩形，清除原有提示*/
					setfillstyle(1,WHITE);
					bar(180,370,340,410);
				}
				break;
				case 2://账户和密码没有输入，只输入确认密码
				{
					puthz(180,370,"请输入账户和密码",32,36,BLACK);//提示“请输入账户和密码”
					delay(2000);//延时后清除提示
					/*绘制矩形，清除原有提示*/
					setfillstyle(1,WHITE);
					bar(180,370,470,410);
					/*清空确认密码字符串*/
					setfillstyle(1,WHITE);
					bar(220,230,480,254);
					*comfirm = NULL;
					cnum = 0;
				}
				break;
				case 3://账户和密码没有输入，只输入密码
				{
					puthz(180,370,"请输入账户和确认密码",32,36,BLACK);//提示“请输入账户和确认密码”
					delay(2000);//延时后清除提示
					/*绘制矩形，清除原有提示*/
					setfillstyle(1,WHITE);
					bar(180,370,560,410);
					/*清空密码字符串*/
					setfillstyle(1,WHITE);
					bar(220,190,480,214);
					*password = NULL;
					pnum = 0;
				}
				break;
				case 4://账户没有输入，只输入密码和确认密码
				{
					puthz(180,370,"请输入账户",32,36,BLACK);//提示“请输入账户“
					delay(2000);//延时后清除提示
					/*绘制矩形，清除原有提示*/
					setfillstyle(1,WHITE);
					bar(180,370,370,410);
					setfillstyle(1,WHITE);
					bar(220,190,480,214);
					bar(220,230,480,254);
					/*清空原先的密码以及确认密码字符串的内容*/
					*password = NULL;
					*comfirm = NULL;
					pnum = 0;
					cnum = 0;
				}
				break;
				case 5://只输入账户，没有输入密码和确认密码
				{
					puthz(180,370,"请输入密码和确认密码",32,36,BLACK);//提示"请输入密码和确认密码"
					delay(2000);//延时后清除提示
					/*绘制矩形，清除原有提示*/
					setfillstyle(1,WHITE);
					bar(180,370,560,410);
				}
				break;
				case 6://已经输入账户和确认密码，没有输入密码
				{
					puthz(180,370,"请输入密码",32,36,BLACK);//提示“请输入密码”
					delay(2000);
					setfillstyle(1,WHITE);
					bar(180,370,560,410);//擦除提示
					/*确认密码赋空*/
					setfillstyle(1,WHITE);
					bar(220,190,480,214);
					*comfirm = NULL;
					cnum = 0;
				}
				break;
				case 7://已经输入账户和密码，没有输入确认密码
				{
					puthz(180,370,"请输入确认密码",32,36,BLACK);//提示"请输入密码"
					delay(2000);//延时后清除提示
					/*绘制矩形，清除原有提示*/
					setfillstyle(1,WHITE);
					bar(180,370,560,410);
					setfillstyle(1,WHITE);
					/*密码以及确认密码赋空*/
					bar(220,190,480,214);
					bar(220,230,480,254);
					*password = NULL;
					*comfirm = NULL;
					pnum = 0;
					cnum = 0;
				}
				break;
				case 8://信息全部输入
				{
					switch(judge_account(account))//判断是否用户已被注册
					{
						case 1://用户已被注册
						{
							puthz(180,370,"用户已被注册",32,36,BLACK);//提示”用户已被注册“
							delay(2000);//延时后清除提示
							/*绘制矩形，清除原有提示*/
							setcolor(WHITE);
							setfillstyle(1,WHITE);
							bar(180,370,440,410);
							/*清理框内的内容*/
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
						case 2://用户未被注册
						switch(strcmp(password,comfirm))//判断两次输入密码是否相吻合
						{
							case 0:
							{
								account_create(account,password);//创建用户
								clrscr();
								return 2;
							}
							default:
							{
								puthz(180,370,"请重新确认密码",32,36,BLACK);//提示"请重新确认密码"
								delay(2000);//延时后清除提示
								/*绘制矩形，清除原有提示*/
								setfillstyle(1,WHITE);
								bar(180,370,440,410);
								/*清理密码框内的内容，同时密码和确认密码赋空*/
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
		if (mouse_press(390,280,450,310)==1)//返回开始界面
		{
			*account = NULL;
			*password = NULL;
			*comfirm = NULL;
			anum = 0;
			pnum = 0;
			cnum = 0;//账户、密码以及确认密码内容赋空
			clrmous(MouseX,MouseY);//擦除鼠标
			cleardevice();//清屏
			startscreen();//绘制开始界面
			return 1;//开始界面的操纵
		}
	}
}