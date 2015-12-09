#ifndef ZCONFIG___
#define ZCONFIG___

#include "cocos2d.h"
#include<iostream>
#include <ctime>
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
//#include "vld.h"  
#endif
#include "Helper.h"
#include "GameDataManager.h"
#include "SoundManager.h"

#include<algorithm>
#include <string>
#include  <map>
#include <vector>
#define array1(type) vector<type>
#define array2(type) vector<array1(type)>
#define array3(type) vector<array2(type)>
#define array4(type) vector<array3(type)>
#define ArrayList(type) vector<type>
#define ArrayList2(type) vector<ArrayList(type)>
#define ArrayList3(type) vector<ArrayList2(type)>
#define ArrayList4(type) vector<ArrayList3(type)>
#define	FPS_RATE			50				//设定游戏帧率

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_HALF_WIDTH = 640;
const int SCREEN_HALF_HEIGHT = 360;
const int ZJ_UI_ZODER = 2000;
const int PACKS_ZORDER = ZJ_UI_ZODER+4;
#define NAMESPACE_SG_BEGIN namespace cocoedemo{
#define NAMESPACE_SG_END }
#define USING_SG_GAME using namespace cocoedemo
USING_NS_CC;
// typedef signed char cbyte; 
// typedef unsigned char unbyte;
using std::vector;
using std::string;
using std::map;
using std::stringstream;

#define MCONTROL_INIT_REMOVEALL \
	auto ctrl = (MControl*)node; \
	auto paintNode = ctrl->getPaintNode(); \
	auto size = ctrl->getSize(); \
	paintNode->removeAllChildren();


#endif