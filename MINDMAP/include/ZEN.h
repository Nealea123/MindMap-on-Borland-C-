#ifndef ZEN_H_INCLUDED
#define ZEN_H_INCLUDED

#include"BOX.h"
#include"head.h"

int zenInterface(BOX*h, long start);
int TableOp(Rect Table, BOX*h, BOX**ppPress, long start, char **list);
int mouseZEN(BOX*h, BOX**ppBox, BOX**ppPoint, BOX**ppPress, Rect Table, long start, char **list);
void TimeShow(BOX*h, long start, Rect Table);
void KeyShow(BOX*h, Rect Table);
void renewZENBox(BOX*h,int x1,int y1,int x2,int y2);
void drawAllZENBox(BOX*h);
void drawtable(void);

#endif // ZEN_H_INCLUDED
