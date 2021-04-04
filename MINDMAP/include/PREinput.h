#ifndef __PREINPUT_H__
#define __PREINPUT_H__
#include "PREmouse.h"
#define BACK_SPACE 0x0e08
#define DELETE 0x5300
#define SPACE 0x3920
#define ENTER 0x1c0d
#define LASTLINE 0x1a5b
#define NEXTLINE 0x1b5d
#define LEFT 0x4b00
#define RIGHT 0x4d00
#define FIRST 0x0231
#define SECOND 0x0332
#define THIRD 0x0433
#define FOURTH 0x0534

#define MAXPY 12      //最大拼音（西文）数量 

#define FAIL 0
#define SUCCESS 1

int hz_input(int x1,int y1,int x2,int y2,char *s,int len);/*返回本次键入字符串长度*/ 
int input_method(int x,int y,char *str,int value,char *py);/*汉字输入法调入函数*/
char *itostr(int a,char *s);/*数字标号输出*/ 
void pyFrm(int x1,int y1,int x2,int y2);/*输入法小框*/ 

#endif
