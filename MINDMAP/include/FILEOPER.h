#ifndef _FILEOPER_H
#define _FILEOPER_H

#include"FILEOPER.h"
//思维导图文件操作的一个文件的基本数据
typedef struct mapf
{
	char mindmapFileName[15];//思维导图文件名
	int fileSum;//总的文件数目
	
	struct mapf *next;//思维导图文件的链表连接指针
	struct mapf *lastAddress;//思维导图文件的上次文件地址
	User *usess;//本级思维导图文件名所属用户
}MAPF;



void readMoreMindmapFile(User*pUser,MAPF**pMapFile);//读入本账号的思维导图文件信息
void saveMindmap(BOX*h,MAPF*hM,MAPF**NM);//保存思维导图操作
void openMindmap(BOX*h,MAPF*hM,MAPF**NM);//打开思维导图
int getInputFileName(BOX*h,char*fileName);//保存文件名输入
void drawSaveFile(char*fileName);//画出保存弹出框
int chooseOpenMap(MAPF*hM,MAPF**cM,MAPF**NM);
void drawOpenMap(MAPF*hM,MAPF**cM,char*flag);
void rightenNewAdress(BOX*h);//更新思维导图框图地址
void closeMindmap(BOX*h,MAPF*hM,MAPF**cM);//关闭思维导图文件
void saveFile(BOX*h);
int drawCloseRight();////画出是否保存当前文件提醒框
void theSameName();//保存同名文件提醒弹出框
void most15File();//思维导图创建已满弹出提醒

#endif