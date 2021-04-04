#ifndef  _PREHZ_H
#define  _PREHZ_H

void puthz(int x, int y, char *s, int flag, int part, int color);
int  outputLetterNum(char ch, int x, int y, int color);
int xouttextxy(int x,int y,char *s,int color);
void outputhz(int x1,int y1,int x2,int y2,char *s,int color);   //显示汉字和字符并换行  只提供16*16的汉字
int  outputLetterNum2(char ch,int x,int y,int color);
void puthzcu(int x, int y,char *s,int flag,int part,int color);   //显示汉字加粗函数
void outtime(int x1,int y1,int x2,int y2,char *s,int color);   //显示时间换行，x1x2y1y2为界定范围
#endif