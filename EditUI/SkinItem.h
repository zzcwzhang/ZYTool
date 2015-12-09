#ifndef SkinItem_H_
#define SkinItem_H_
#include "cocos2d.h"
#define Flip_None  0
#define Flip_X  1
#define Flip_Y  2
#define Flip_XY  3
class DataStream;
class SkinItem
{
public:
	short x;
	short y;
	short mirror;
	short rotAngle;
	short opacity;
	cocos2d::Color3B color;
	short sx;
	short sy;
	short sw;
	short sh;
	short imgId;
public:
	SkinItem();
	~SkinItem();
	void loadItem(DataStream *dis);
	//CCRect getSpriteRect(UIForm *form);
	cocos2d::Vec2 getLocation();
	short getMirror();
	short getRotAngle();
	short getOpacity();
	cocos2d::Color3B getColor();
	bool needFunc;
};
#endif