#ifndef __fish__FishPath__
#define __fish__FishPath__
#include <iostream>
#include "cocos2d.h"
#include "Fish.h"
USING_NS_CC;

class FishBezierTo : public BezierTo
{
public:
	virtual void update(float time);

	static FishBezierTo* create(float t, const ccBezierConfig& c);

	bool initWithDuration(float t, const ccBezierConfig &c);

	virtual BezierTo* clone();
	//virtual CCObject* copyWithZone(CCZone* pZone);
};

class FishCardinalSplineTo : public CardinalSplineTo
{
public:
	virtual void update(float time);

	static FishCardinalSplineTo* create(float duration, PointArray* points, float tension);

	bool initWithDuration(float duration, PointArray* points, float tension);
	//virtual CCCardinalSplineTo* copyWithZone(cocos2d::CCZone *pZone);
};

class FishLineTo : public MoveTo
{
public:
	virtual void update(float time);

	static FishLineTo* create(float duration, const Point& position);

	bool initWithDuration(float duration, const Point& position);

	//virtual CCObject* copyWithZone(cocos2d::CCZone* pZone);
};

class FishSinTo : public ActionInterval
{
public:
	virtual void update(float time);

	static FishSinTo* create(float duration, const Vec2& startPosition,const Vec2& endPosition);

	bool initWithDuration(float duration, const Vec2& startPosition,const Vec2& endPosition);

public:
	float _angle;
	Point _origin;
	Point _endPosition;
	Point _startPosition;
};

class Fish;
class FishPathFactory
{
public:
	enum FishPathType
	{
		FISH_PATHTYPE_A = 0,
		FISH_PATHTYPE_B,
		FISH_PATHTYPE_C,
		FISH_PATHTYPE_D,
		FISH_PATHTYPE_E,
		FISH_PATHTYPE_F, //sin
		FISH_PATHTYPE_G, //circle out
		FISH_PATHTYPE_B_LINE,
		FISH_PATHTYPE_STATIC
	};

	static void generateBezierFishPath(Fish * target);
	static void generateStaticFishPath(Fish * target);
	static void generateMultiBezierFishPath(Fish *target,Vec2 start,Vec2 end, int num);
	static void generateMultiBezierFishPathWithMD(Fish *target,Vec2 start,Vec2 end, int num,Vec2 md);
	static void createFishPath(Fish* target);

	//for requirement
	static void generateFishPathA(Fish *target,Vec2 start=Vec2(0,0),Vec2 end=Vec2(0,0),bool direction=true);
	static void generateFishPathB(Fish *target,int type=-1,Vec2 start=Vec2(0,0),Vec2 end=Vec2(0,0));
	static void generateFishPathB_line(Fish *target,int type=-1,Vec2 start=Vec2(0,0),Vec2 end=Vec2(0,0),Vec2 md=Vec2(0,0));
	static void generateFishPathC(Fish *target);
	static void generateFishPathD(Fish *target);//Ö±ÏßÂ·¾¶
	static void generateFishPathE(Fish *target);
	static void generateFishPathF(Fish *target);//sin
	static void generateFishPathG(Fish *target);//circle out

	//for groups
	static void generateFishesPath(Vector<Fish*>pfishes);
	static void generateFishesPathA(Vector<Fish*>pfishes);
	static void generateFishesPathB(Vector<Fish*>pfishes);
	static void generateFishesPathB_line(Vector<Fish*>pfishes);
	static void generateFishesPathC(Vector<Fish*>pfishes);
	static void generateFishesPathD(Vector<Fish*>pfishes);
	static void generateFishesPathE(Vector<Fish*>pfishes);
	static void generateFishesPathF(Vector<Fish*>pfishes);
	static void generateFishesPathG(Vector<Fish*> pfishes);
	static void generateFishesPathStatic(Vector<Fish*> pfishes);

	static FishPathType getFishPathType(Fish::FishType type);
};

#endif