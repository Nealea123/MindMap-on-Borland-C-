#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include"BOX.h"

void input_1(int xmin,int ymin,int xmax,int ymax,int n,char *string,int *i);
void input_2(int xmin,int ymin,int xmax,int ymax,int n,char *string,int *i);
int done_user(char *account,char *password);
int done_register(char *account,char *password,char *comfirm);
int judge_account(char *string);
void account_create(char *account,char *password);
int login(char *account,char *password,User**pUser);
// void creatfile(BOX*h, char *account, char *fname);
// void openfile(BOX*h, char *account, char *fname);
// void filesort(char *account, char *fname, int seq, int num);
// void recentfile(BOX*h, char *account);

#endif // INPUT_H_INCLUDED
