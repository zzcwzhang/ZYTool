#ifndef NETHELPT_H
#define	NETHELPT_H

#include "FProtocol.h"
#include "netDataDto.h"
#include "string"
#include "cocos2d.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "json/document.h"
#include "GameSocket.h"
#include "cocostudio/CocoStudio.h"
#include <vector>
#include "GameManager.h"

//排行榜 资源
//vip 字体
#define VIP_FNT "fonts/num_paihangbang_vip.fnt"
#define FONT_TEXT "fonts/ziti"
//奖杯 资源
#define JB_1 "paihangbang/jiangbei_1.png"
#define JB_2 "paihangbang/jiangbei_2.png"
#define JB_3 "paihangbang/jiangbei_3.png"



USING_NS_CC;

using namespace std;
using namespace rapidjson;
using namespace cocostudio;

#endif