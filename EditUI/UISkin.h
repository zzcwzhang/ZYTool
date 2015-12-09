#ifndef UISkin_H_
#define UISkin_H_
#include "cocos2d.h"
#include "GameConfig.h"
class SkinFrame;
class DataStream;
class UISkin : public cocos2d::Ref
{
public:
	short frameCount;
	cocos2d::Size size;
	SkinFrame **frames;
	short m_id;
	bool bCyclePlay;
public:
	CREATE_OBJFUNC(UISkin);
	UISkin()
	{ 
		frames = nullptr; 
		frameCount = 0;
		this->size = cocos2d::Size(0, 0);
	}
	~UISkin();
	void loadSkin(DataStream *dis);
	void loadRes();
};
#endif