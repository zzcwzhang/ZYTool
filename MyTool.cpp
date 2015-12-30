#include "MyTool.h"

#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#define KEY_DOWN(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 1 : 0)
#define KEY_UP(vk_code) (GetAsyncKeyState(vk_code) & 0x8000 ? 0 : 1)
#endif

#define KEYLOG(a) 	\
if(KEY_DOWN(a))\
{\
		ILOG(a)\
}\

#define PRESSCONTROL_KEYBOOLD_ONCE(vk_code) \
	static int T_##vk_code = 0;\
if (KEY_UP(vk_code))\
{\
	T_##vk_code = 0;\
}\
if(KEY_DOWN(vk_code)) \
{\
	if (T_##vk_code==0)\
	{
#define PRESSCONTROL_KEYBOOLD_PRESSING(vk_code)	\
	}\
	if (T_##vk_code>=30)\
	{
#define PRESSCONTROL_KEYBOOLD_END(vk_code) }\
	T_##vk_code ++;\
}



int MyTool::funcount = 0;
int MyTool::count = 0;
MyTool* MyTool::instance;


MyTool* MyTool::getInstance()
{
	if (!instance)
	{

		instance = MyTool::create();
		Director::getInstance()->getRunningScene()->addChild(instance);

	}

	return instance;
}

MyTool::MyTool(void)
{
	instance = NULL;
}


MyTool::~MyTool(void)
{
}

void MyTool::update( float dt )
{
// 	 	PRESSCONTROL_KEYBOOLD_ONCE(VK_BACK)  /*按下时执行一次;*/
// 	 		log("once");
// 	 	PRESSCONTROL_KEYBOOLD_PRESSING(VK_BACK)  /*持续按一秒以上后开始连续执行（不需要也要加上）;*/
// 	 		log("pressing");
// 	 	PRESSCONTROL_KEYBOOLD_END(VK_BACK)  /*结束;*/


#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)



	//----------------------位置控制;

	//上;
	PRESSCONTROL_KEYBOOLD_ONCE(VK_UP) 
	 	controlNode->setPositionY(controlNode->getPositionY()+1);
	PRESSCONTROL_KEYBOOLD_PRESSING(VK_UP) 
	 	controlNode->setPositionY(controlNode->getPositionY()+1);
	PRESSCONTROL_KEYBOOLD_END(VK_UP);
	//下;
	PRESSCONTROL_KEYBOOLD_ONCE(VK_DOWN) 
		controlNode->setPositionY(controlNode->getPositionY()-1);
	PRESSCONTROL_KEYBOOLD_PRESSING(VK_DOWN) 
		controlNode->setPositionY(controlNode->getPositionY()-1);
	PRESSCONTROL_KEYBOOLD_END(VK_DOWN);
	//→;
	PRESSCONTROL_KEYBOOLD_ONCE(VK_RIGHT) 
		controlNode->setPositionX(controlNode->getPositionX()+1);
	PRESSCONTROL_KEYBOOLD_PRESSING(VK_RIGHT) 
		controlNode->setPositionX(controlNode->getPositionX()+1);
	PRESSCONTROL_KEYBOOLD_END(VK_RIGHT);
	//←;
	PRESSCONTROL_KEYBOOLD_ONCE(VK_LEFT) 
		controlNode->setPositionX(controlNode->getPositionX()-1);
	PRESSCONTROL_KEYBOOLD_PRESSING(VK_LEFT) 
		controlNode->setPositionX(controlNode->getPositionX()-1);
	PRESSCONTROL_KEYBOOLD_END(VK_LEFT);

	


	//----------------------大小控制;

	//缩小;
	PRESSCONTROL_KEYBOOLD_ONCE(VK_PRIOR) 
		controlNode->setScale(controlNode->getScale()-0.02);
	PRESSCONTROL_KEYBOOLD_PRESSING(VK_PRIOR) 
		controlNode->setScale(controlNode->getScale()-0.02);
	PRESSCONTROL_KEYBOOLD_END(VK_PRIOR);

	//放大;
	PRESSCONTROL_KEYBOOLD_ONCE(VK_NEXT) 
		controlNode->setScale(controlNode->getScale()+0.02);
	PRESSCONTROL_KEYBOOLD_PRESSING(VK_NEXT) 
		controlNode->setScale(controlNode->getScale()+0.02);
	PRESSCONTROL_KEYBOOLD_END(VK_NEXT);


	//----------------------颜色控制;

	static GLubyte colorR = 255;
	static GLubyte colorG = 255;
	static GLubyte colorB = 255;

	//数字键盘7 变红;
	PRESSCONTROL_KEYBOOLD_ONCE(0x67) 
		controlNode->setColor(ccc3(colorR,--colorG,--colorB));
	PRESSCONTROL_KEYBOOLD_PRESSING(0x67) 
		controlNode->setColor(ccc3(colorR,--colorG,--colorB));
	PRESSCONTROL_KEYBOOLD_END(0x67);

	//数字键盘1 反变红;
	PRESSCONTROL_KEYBOOLD_ONCE(0x61) 
		controlNode->setColor(ccc3(colorR,++colorG,++colorB));
	PRESSCONTROL_KEYBOOLD_PRESSING(0x61) 
		controlNode->setColor(ccc3(colorR,++colorG,++colorB));
	PRESSCONTROL_KEYBOOLD_END(0x61);

	//绿;
	PRESSCONTROL_KEYBOOLD_ONCE(0x68) 
		controlNode->setColor(ccc3(--colorR,colorG,--colorB));
	PRESSCONTROL_KEYBOOLD_PRESSING(0x68) 
		controlNode->setColor(ccc3(--colorR,colorG,--colorB));
	PRESSCONTROL_KEYBOOLD_END(0x68);

	PRESSCONTROL_KEYBOOLD_ONCE(0x62) 
		controlNode->setColor(ccc3(++colorR,colorG,++colorB));
	PRESSCONTROL_KEYBOOLD_PRESSING(0x62) 
		controlNode->setColor(ccc3(++colorR,colorG,++colorB));
	PRESSCONTROL_KEYBOOLD_END(0x62);

	//蓝;
	PRESSCONTROL_KEYBOOLD_ONCE(0x69) 
		controlNode->setColor(ccc3(--colorR,--colorG,colorB));
	PRESSCONTROL_KEYBOOLD_PRESSING(0x69) 
		controlNode->setColor(ccc3(--colorR,--colorG,colorB));
	PRESSCONTROL_KEYBOOLD_END(0x69);

	PRESSCONTROL_KEYBOOLD_ONCE(0x63) 
		controlNode->setColor(ccc3(++colorR,++colorG,colorB));
	PRESSCONTROL_KEYBOOLD_PRESSING(0x63) 
		controlNode->setColor(ccc3(++colorR,++colorG,colorB));
	PRESSCONTROL_KEYBOOLD_END(0x63);

	//恢复原来颜色;
	
	PRESSCONTROL_KEYBOOLD_ONCE(0x60) 
		colorR = 255;
		colorG = 255;
		colorB = 255;
		controlNode->setColor(ccc3(colorR,colorG,colorB));
	PRESSCONTROL_KEYBOOLD_PRESSING(0x60) 
	PRESSCONTROL_KEYBOOLD_END(0x60);

	//------------------------------方向控制;
	PRESSCONTROL_KEYBOOLD_ONCE(0x64) 
		controlNode->setRotation(controlNode->getRotation()+1);
	PRESSCONTROL_KEYBOOLD_PRESSING(0x64) 
		controlNode->setRotation(controlNode->getRotation()+1);
	PRESSCONTROL_KEYBOOLD_END(0x64);

	PRESSCONTROL_KEYBOOLD_ONCE(0x66) 
		controlNode->setRotation(controlNode->getRotation()-1);
	PRESSCONTROL_KEYBOOLD_PRESSING(0x66) 
		controlNode->setRotation(controlNode->getRotation()-1);
	PRESSCONTROL_KEYBOOLD_END(0x66);



	//------------------------------输出到控制台;

	//空格;
	
	PRESSCONTROL_KEYBOOLD_ONCE(VK_SPACE)
	SLOG("----------------------------RESULT------------------------------");
	CCPoint ppt = controlNode->getPosition();
	log("Cur Point(%f,%f)",ppt.x,ppt.y);
	float ppx = ppt.x-tcx;
	float ppy = ppt.y-tcy;
	log("Changed Vec2(%f,%f)",ppx,ppy);
	float scale = controlNode->getScale();
	FLOG(scale);
	log("Color(%d,%d,%d)",colorR,colorG,colorB);
	log("Rotation : %f",controlNode->getRotation());
	SLOG("------------------------------END--------------------------------");
	PRESSCONTROL_KEYBOOLD_PRESSING(VK_SPACE)
		log("pressing");
	PRESSCONTROL_KEYBOOLD_END(VK_SPACE);
	

#endif
}

bool MyTool::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->scheduleUpdate();


	return true;
}

void MyTool::setControlNode( Node *nd )
{
	controlNode = nd;
	tcx = nd->getPositionX();
	tcy = nd->getPositionY();

}


