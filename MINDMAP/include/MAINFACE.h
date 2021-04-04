#ifndef _MAINFACE_H
#define _MAINFACE_H

#include"FILEOPER.h"

int mainInterface(BOX*h,User*pUser);//主界面操作执行
void drawMainInterface(void);//画主界面
int mouseKeyMainOperate(BOX*h,BOX**ppBox,BOX**ppPoint,BOX**ppPress,MAPF*cM);//主界面操作识别
int dropDownMainMenu(BOX*h);//主界面下拉式菜单

void moveFace(BOX*h);//移动思维导图界面
void shortcutAssistant(BOX*h);//快捷键助手弹出
void reDrawAll(BOX*h);//更新思维导图主界面
void boxType(BOX*h,BOX*pPress);//方框样式更改
void drawGo(int x,int y,int color);//画一个选择勾
void drawNewBoxTypeMenu(int*flag);//画出样式更改弹出框
void newGuidance(BOX*h,BOX*pPress);//新手指导弹出框引导
void drawNewGuidance(int a);//画出新手指导弹出框
int mouseIn(int x1,int y1,int x2,int y2);//鼠标所在函数
void Character8Warning();//字符已达上限提醒
int exitYesOrNo();//是否退出程序弹出框


#endif