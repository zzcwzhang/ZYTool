#ifndef zj_H_
#define zj_H_

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;
//#include "SimpleAudioEngine.h"
//#include <map>
//#include <iostream>
//#include <sstream>
#include <string.h>
#include <vector>
using namespace std;
USING_NS_CC;
//using namespace CocosDenshion;
//using namespace cocos2d::extension;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
//#include "vld.h"  
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台 
//#include "../Game_Analytics_SDK_Cocos_3/include/TalkingData.h"
//#include "platform/android/jni/JniHelper.h"
#endif
#include "GameConfig.h"
#include "DataStream.h"
#include "Tools.h"
//#include "SMSInfo.h"

#define Game_Test //测试宏
#endif