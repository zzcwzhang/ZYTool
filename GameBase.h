#ifndef _GAME_BASE_
#define _GAME_BASE_

#include "cocos2d.h"

USING_NS_CC;

class BaseLayer : public Layer
{
public:

	virtual void update(float delta){}
	virtual void exitLayer(){}
};

#endif