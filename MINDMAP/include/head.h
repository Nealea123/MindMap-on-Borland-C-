#ifndef	HEAD_H
#define	HEAD_H

typedef struct user
{
	char account[10];
	char password[10];
}User;

typedef struct
{
	int left;
	int top;
	int right;
	int bottom;
}Rect;

typedef struct
{
	Rect pos;
	char *title;
}Menu;

typedef struct
{
	int centreX;
	int centreY;
	int radius;
}Cir;

#endif
