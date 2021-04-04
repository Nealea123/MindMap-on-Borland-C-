#ifndef LOGINFACE_H_INCLUDED
#define LOGINFACE_H_INCLUDED

void initscreen(void);//界面初始化
void startscreen(void);//开始界面绘制
void userscreen(void);//用户界面绘制
void registerscreen(void);//注册界面绘制
int startoperation(void);//开始界面鼠标操纵
int useroperation(User**pUser);//用户登录界面的操作
int registeroperation(void);//用户注册界面的操作

#endif // LOGINFACE_H_INCLUDED
