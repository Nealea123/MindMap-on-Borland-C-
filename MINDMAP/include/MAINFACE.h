#ifndef _MAINFACE_H
#define _MAINFACE_H

#include"FILEOPER.h"

int mainInterface(BOX*h,User*pUser);//���������ִ��
void drawMainInterface(void);//��������
int mouseKeyMainOperate(BOX*h,BOX**ppBox,BOX**ppPoint,BOX**ppPress,MAPF*cM);//���������ʶ��
int dropDownMainMenu(BOX*h);//����������ʽ�˵�

void moveFace(BOX*h);//�ƶ�˼ά��ͼ����
void shortcutAssistant(BOX*h);//��ݼ����ֵ���
void reDrawAll(BOX*h);//����˼ά��ͼ������
void boxType(BOX*h,BOX*pPress);//������ʽ����
void drawGo(int x,int y,int color);//��һ��ѡ��
void drawNewBoxTypeMenu(int*flag);//������ʽ���ĵ�����
void newGuidance(BOX*h,BOX*pPress);//����ָ������������
void drawNewGuidance(int a);//��������ָ��������
int mouseIn(int x1,int y1,int x2,int y2);//������ں���
void Character8Warning();//�ַ��Ѵ���������
int exitYesOrNo();//�Ƿ��˳����򵯳���


#endif