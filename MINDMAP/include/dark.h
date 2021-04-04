#ifndef DARK_H_INCLUDED
#define DARK_H_INCLUDED

#include"BOX.h"
#include"head.h"

int darkInterFace(BOX*h, long start);
int TableDark(Rect Table, Cir Sun, long start, char **list);
int mouseDark(BOX*h, BOX**ppBox, BOX**ppPoint, BOX**ppPress, Rect Table, Cir Sun, long start, char **list);
void TimeShow_Dark(long start, Rect Table);
void KeyShow_Dark(Rect Table);
void renewNIGHTBox(BOX*h, Cir Sun, int x1, int y1, int x2, int y2);
int shine(Cir Sun);
void drawSun(Cir Sun, int color);
void drawDARKTable(void);
void drawAllDARKBox(BOX*h);

#endif // DARK_H_INCLUDED
