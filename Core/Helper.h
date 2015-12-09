#ifndef __fish_HELPER__
#define __fish_HELPER__
#include "cocos2d.h"
#include <iostream>

enum NumberType{
	GameNumberGameLayerGold = 1,
	GameNumberStoreLayerLevel,
	GameNumberStoreSubLayerGold,
	GameNumberGameLayerTime,
	GameNumberSotreUp,
	GameNumberYingxin
};

class NumSprite : public cocos2d::Sprite
{
public:
	//NumberType type;
	static NumSprite*create(int num, NumberType pType);
	//void initSprite(int num);
};
#endif