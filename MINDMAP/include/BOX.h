#ifndef _BOX_H
#define _BOX_H
//˼ά��ͼ��ͼ��һ����Ļ�������
typedef struct box
{
	int centerX;//����������x����	
	int centerY;//����������y����
	int boxX;//������x�����ϵĳ��ȵ�һ��
	int boxY;//������y�����ϵĳ��ȵ�һ��
	int lineX;//������x�����ϵ�������
	int lineY;//������y�����ϵ�������
	
	char pointFlag;//�������Ƿ��п��սڵ��жϱ�־��1Ϊ�У�0Ϊ��
	char pointBackFlag;//�������Ƿ��ջ��Լ��Ľڵ�
	char parentPointBackFlag;//�������Ƿ��и����ջؽڵ�
	char pressFlag;//�������Ƿ�ѡ��
	char boldFlag;//�����������Ƿ�Ӵ�
	char boxColor;//�����򷽿���ɫ
	char characterColor;//������������ɫ
	char boxNewColor;//�½��Ŀ�ķ�����ɫ
	char characterNewColor;//�½��Ŀ��������ɫ
	char characterSize;//������������С
	
	char lastLevelSum;//������ĸ�������Ӽ���ĸ���
	char nextLevelSum;//��������ӵ�е��Ӽ���ĸ���
	char lastLevelFlag;//���������ڸ�����ĵڼ���
	int nextAllSum;//��������ӵ�е����һ����ĸ���
	
	char content[95];//���������������
	
	struct box *lastNextBox[27];//�������д���ĸ������Ӽ���Ľṹ���ַ��[0]Ϊ�����ĵ�ַ��[1]~[]Ϊ�Ӽ��ĵ�ַ
	struct box *next;//����İ����˳�������Ѱַ��ַ
	struct box *last;//����İ����˳��ĵ��������Ѱַ��ַ
	struct box *lastFile;
}BOX;

//�����Զ����ݲ���
BOX *boxData0Generate(void);//���ɵ�һ���ṹ������
BOX *findEndBox(BOX*h);//�ҵ����һ���ṹ������
void boxDataStorage(BOX*h,BOX*p,int flag);//����һ���ṹ���������
void boxDataGenerate(BOX*h);//��������һ���ṹ����������
void openPointAndNextBox(BOX*h,BOX*pPress);//���ڵ�������һ��
void newBoxData(BOX*h,BOX**p);//���ɳ�ʼ����
void deleteOneBox(BOX*h,BOX*p);//ɾ��һ���ṹ�弰��ȫ���Ӽ�
void clearAllBox(BOX*h);//�������һ����Ľṹ������
void deleteBox(BOX*h,BOX**ppPress);//ɾ����ѡһ����
void exitAndClear(BOX*h);//�˳������沢�����ڴ�

//�������û���������
void pressBox(BOX*h,BOX*pBox);//ѡ��һ����
BOX *traversalBoxCycle(BOX*h,int x1,int y1,int color);//�ҵ��������һ����
BOX *traversalPointCycle(BOX*h,int x1,int y1);//�ҵ�������ڽڵ�
BOX *traversalPressBox(BOX*h,int color);//�ҵ��ѱ�ѡ��һ����
void clearAllPressBox(BOX*h);//�����ѡ�е�һ���� 
void drawSmallOutBox(BOX*p);//�����������
void drawOutBox(BOX*p);//�������ѡ��
void choiceDirection(BOX*h,BOX**ppPress);//�ƶ�һ����
void pointBack(BOX*h,BOX*p);//�շŽڵ�
void characterInput(BOX*pPress);//��������

//���򱻶�����
void drawAllBox(BOX*h);//��������һ���� 
void drawOneBox(int centerX,int centerY,int boxX,int boxY,int lineX,int lineY,char*content,int pointFlag, int pointBackFlag,int lastLevelSum,int nextAllSum,int boldFlag,int boxColor,int characterColor,int characterSize);//����һ��һ����
void renewAllBox(BOX*h,int x1,int y1,int x2,int y2);//���½���
void pointBackAndClear(BOX*h,BOX*pPoint);//�ջؽڵ������ѡ

//�ڴ治������
void overflowWarning(void);//�ڴ治������
void overflow26Warning(void);//ֱϵ�Ӽ�����������
void overflowCharacterWarning(void);//��������������

//ZENģʽ�µ�Ѱ�ұ���
BOX *traversalBoxCycleInZen(BOX*h,int x1,int y1,int color);//�ҵ��������һ����
BOX *traversalPointCycleInZen(BOX*h,int x1,int y1);//�ҵ�������ڽڵ�
BOX *traversalPressBoxInZen(BOX*h,int color);//�ҵ��ѱ�ѡ��һ����

#endif

