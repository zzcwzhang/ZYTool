#ifndef GameConfig_H_
#define GameConfig_H_

typedef unsigned char cbyte;

#define CREATE_OBJFUNC(__TYPE__) \
	static __TYPE__* create() \
{ \
	__TYPE__ *pRet = new __TYPE__(); \
	if (pRet) \
{ \
	pRet->autorelease(); \
	return pRet; \
} \
	else \
{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
} \
}

//״̬��
#define    GST_COUNT	24
enum GAMESTATE
{
	GST_NONE = -1,
	GST_INIT,
	GST_MENU,
	GST_GAME,
	GST_OnLineGame,
};

enum ObjNodeType
{
	Type_Common = 0,//��ͨ����
	Type_Level,//�ؿ�����
	Type_Script,//�ű�����
	Type_Camera,//��ͷ����
	Type_Field,//�������
	Type_Effect,//��Ч����
	Type_Map,//��ͼ�ڵ�
};

#define S_HEIGHT 720
#define S_WIDTH	1280
#define  One_Meter 32
#define USE_TALKINGDATA 1

#define DESIGN_FPS 40

#endif