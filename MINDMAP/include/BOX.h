#ifndef _BOX_H
#define _BOX_H
//思维导图框图的一级框的基本数据
typedef struct box
{
	int centerX;//本级框中心x坐标	
	int centerY;//本级框中心y坐标
	int boxX;//本级框x方向上的长度的一半
	int boxY;//本级框y方向上的长度的一半
	int lineX;//本级框x方向上的延伸线
	int lineY;//本级框y方向上的延伸线
	
	char pointFlag;//本级框是否有可收节点判断标志，1为有，0为无
	char pointBackFlag;//本级框是否收回自己的节点
	char parentPointBackFlag;//本级框是否有父级收回节点
	char pressFlag;//本级框是否被选中
	char boldFlag;//本级框字体是否加粗
	char boxColor;//本级框方框颜色
	char characterColor;//本级框字体颜色
	char boxNewColor;//新建的框的方框颜色
	char characterNewColor;//新建的框的字体颜色
	char characterSize;//本级框的字体大小
	
	char lastLevelSum;//本级框的父级框的子级框的个数
	char nextLevelSum;//本级框所拥有的子级框的个数
	char lastLevelFlag;//本级框属于父级框的第几个
	int nextAllSum;//本级框所拥有的最后一级框的个数
	
	char content[95];//本级框的文字内容
	
	struct box *lastNextBox[27];//本级框中储存的父级与子级框的结构体地址，[0]为父级的地址，[1]~[]为子级的地址
	struct box *next;//链表的按添加顺序的链表寻址地址
	struct box *last;//链表的按添加顺序的倒序的链表寻址地址
	struct box *lastFile;
}BOX;

//程序自动数据操作
BOX *boxData0Generate(void);//生成第一级结构体数据
BOX *findEndBox(BOX*h);//找到最后一级结构体数据
void boxDataStorage(BOX*h,BOX*p,int flag);//储存一级结构体基本数据
void boxDataGenerate(BOX*h);//生成所有一级结构体其他数据
void openPointAndNextBox(BOX*h,BOX*pPress);//开节点生成下一级
void newBoxData(BOX*h,BOX**p);//生成初始数据
void deleteOneBox(BOX*h,BOX*p);//删除一级结构体及其全部子级
void clearAllBox(BOX*h);//清除所有一级框的结构体数据
void deleteBox(BOX*h,BOX**ppPress);//删除被选一级框
void exitAndClear(BOX*h);//退出主界面并清理内存

//程序与用户互动操作
void pressBox(BOX*h,BOX*pBox);//选中一级框
BOX *traversalBoxCycle(BOX*h,int x1,int y1,int color);//找到鼠标所在一级框
BOX *traversalPointCycle(BOX*h,int x1,int y1);//找到鼠标所在节点
BOX *traversalPressBox(BOX*h,int color);//找到已被选中一级框
void clearAllPressBox(BOX*h);//清除被选中的一级框 
void drawSmallOutBox(BOX*p);//画出鼠标所在
void drawOutBox(BOX*p);//画出鼠标选中
void choiceDirection(BOX*h,BOX**ppPress);//移动一级框
void pointBack(BOX*h,BOX*p);//收放节点
void characterInput(BOX*pPress);//汉字输入

//程序被动绘制
void drawAllBox(BOX*h);//画出所有一级框 
void drawOneBox(int centerX,int centerY,int boxX,int boxY,int lineX,int lineY,char*content,int pointFlag, int pointBackFlag,int lastLevelSum,int nextAllSum,int boldFlag,int boxColor,int characterColor,int characterSize);//画出一个一级框
void renewAllBox(BOX*h,int x1,int y1,int x2,int y2);//更新界面
void pointBackAndClear(BOX*h,BOX*pPoint);//收回节点清除被选

//内存不足提醒
void overflowWarning(void);//内存不足提醒
void overflow26Warning(void);//直系子级框已满提醒
void overflowCharacterWarning(void);//汉字数已满提醒

//ZEN模式下的寻找遍历
BOX *traversalBoxCycleInZen(BOX*h,int x1,int y1,int color);//找到鼠标所在一级框
BOX *traversalPointCycleInZen(BOX*h,int x1,int y1);//找到鼠标所在节点
BOX *traversalPressBoxInZen(BOX*h,int color);//找到已被选中一级框

#endif

