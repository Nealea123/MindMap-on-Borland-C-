#ifndef _OUTLINE_H
#define _OUTLINE_H


//大纲模式一级线基本数据
typedef struct line
{
	int parentSum;//父级数目
	int lineFlag;//本级所在行数
	int x0;//本级线的X位置
	int y0;//本级线所在的Y位置
	struct box *pBox;//本级线对应的大纲模式的一级框
	struct line *next;//本级框的链表连接指针
}LINE;

int outlineModeFace(BOX*hB);//大纲模式操作界面
void shortcutAssistantInLine(LINE*hL);//大纲模式的快捷键助手
void moveFaceInLine(LINE*hL);//移动大纲界面
void choiceLineDirection(LINE*hL,LINE*pPress);//指向大纲线上下移动
void exitLineAndClear(LINE*hL);//退出大纲模式
void pressLine(LINE*hL,LINE*pLine);//点击选中一级大纲线
LINE* traversalLineCycle(LINE*hL,int x1,int y1);//寻找鼠标所在的一级大纲线
LINE* traversalLinePointCycle(LINE*hL,int x1,int y1);//寻找所在的一级节点
LINE* traversalLinePressBox(LINE*hL);//寻找选中的一级大纲线
int mouseKeyOutlineOperate(LINE*hL,LINE**ppLine,LINE**ppPoint,LINE**ppPress);//大纲模式鼠标操作
int dropDownOutlineMenu(LINE*hL);//大纲模式下拉菜单
void reDrawLineAll(LINE*hL);//更新大纲界面
void clearAllLine(LINE*hL);//清除所有大纲数据
void drawOutlineInterface(LINE*hL);//画出大纲界面
LINE *transMindMapToOutline(BOX*hB);//转换思维导图数据为大纲模式
void lineDataGenerate(LINE*hL);//大纲模式数据生成
void drawAllLine(LINE*hL);//画出所有的大纲线
void renewXY(LINE*hL);//更新大纲的XY数据
void characterInputInLine(LINE*pLPress);
void justDrawLine(LINE*hL);//只画大纲图

#endif