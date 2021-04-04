#ifndef _MAINHEAD_H
#define _MAINHEAD_H

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<graphics.h>
#include<time.h>
#include<dos.h>
#include<bios.h>
#include<conio.h>
#include<math.h>
#include<dir.h>
#include"PREhz.h"
#include"PREinput.h"
#include"PREmouse.h"

#include"head.h"
#include"input.h"
#include"login.h"
#include"dark.h"
#include"ZEN.h"

#include"BOX.h"
#include"INFACE.h"
#include"MAINFACE.h"
#include"OUTLINE.h"
#include"FILEOPER.h"

#define CTRL_N 0x310e
#define CTRL_U 0x1615
#define CTRL_R 0x1312
#define CTRL_S 0x1f13
#define CTRL_C 0x2e03
#define ESC 0x011b

#define DELETE 0x5300
#define CTRL_T 0x1414

#define TAB 0x0f09
#define ENTER 0x1c0d
#define CTRL_ENTER 0x1C0A
#define CTRL_F 0x2106

#define CTRL_M 0x320d
#define CTRL_B 0x3002
#define CTRL_Z 0x2c1a

#define CTRL_H 0x2308
#define CTRL_A 0x1e01

#define CTRL_UP 0x0c1f//CTRL_-
#define CTRL_DOWN 0x2b1c//CTRL_|
#define CTRL_LEFT 0x1a1b//CTRL_[
#define CTRL_RIGHT 0x1b1d//CTRL_]
#define CTRL_O 0x180f

#define UP 0x4800
#define DOWN 0x5000
#define LEFT 0x4b00
#define RIGHT 0x4d00

#define BACKSPACE 0x0e08
#define SPACE 0x3920

#define BACKGOUNDCOLOR 15//背景颜色
#define XBACKGOUNDCOLOR 11//小背景颜色
#define XLCDBACKGOUNDCOLOR 15//下拉菜单方框填充颜色

#define MCHZCOLOR 0//软件名称汉字颜色
#define HZCOLOR 0//菜单汉字颜色
#define THZCOLOR 3//鼠标指向汉字颜色
#define XLCDHZCOLOR 0//下拉菜单汉字颜色
#define ZMCOLOR 0//字母颜色

#define DFKCOLOR 7//全局方框线条颜色
#define SFKCOLOR 8//下拉菜单方框线条颜色
#define FKCOLOR 7//方框线条颜色

#define RADIUS 5

#endif