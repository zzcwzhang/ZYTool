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

//状态集
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
	Type_Common = 0,//普通对象
	Type_Level,//关卡对象
	Type_Script,//脚本对象
	Type_Camera,//镜头对象
	Type_Field,//区域对象
	Type_Effect,//特效对象
	Type_Map,//地图节点
};

#define S_HEIGHT 720
#define S_WIDTH	1280
#define  One_Meter 32
#define USE_TALKINGDATA 1

#define DESIGN_FPS 40

#endif