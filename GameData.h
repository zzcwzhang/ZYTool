#ifndef _GAME_DATA_H_
#define _GAME_DATA_H_
#include "cocos2d.h"
#include "DataStream.h"
USING_NS_CC;

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

enum Outfit
{
	wu=0,
	zhuangbei,
	yizhuangbei
};

enum GameDataType
{
	Type_Weapon = 0,
	Type_Hero,
	Type_Item,
	Type_Pet,
	Type_Ride,
	Type_Exchange,
	Type_Monkey,
	Type_Achievement,
	Type_xingxing,
	Type_Length,
};

class GameData : public cocos2d::Ref
{
public:
	static int GameDataOffset;
	short m_id;
	std::string m_name;
	bool bNew;
public:
	CREATE_OBJFUNC(GameData);
	GameData():bNew(false){};
	~GameData(){};
	virtual void load(DataStream *dis){
		m_name = dis->readString();
	}
};

class LevelInf : public GameData
{
public:
	CREATE_OBJFUNC(LevelInf);
	LevelInf();
	~LevelInf();

	virtual void load(DataStream *dis);
public:
	bool isOpen; 
	int reward;
	std::vector<short> targets;
	int missionCount;
};

class FishInf : public GameData
{
public:
	CREATE_OBJFUNC(FishInf);
	FishInf();
	~FishInf();
	virtual void load(DataStream *dis);
public:
	int rate;
	int hp;
	float minSpeed;
	float maxSpeed;
	std::string fishname;
	int jiangquan;
};

class CannonRateInf : public GameData
{
public:
	CREATE_OBJFUNC(CannonRateInf);
	CannonRateInf();
	~CannonRateInf();
	virtual void load(DataStream *dis);
public:
	int rate;
	int openCoin;
	bool bOpen;
	int consume;//消耗
};

class CannonInf : public GameData
{
public:
	CREATE_OBJFUNC(CannonInf);
	CannonInf(){bOpen = false;}
	~CannonInf(){}
	virtual void load(DataStream *dis);
public:
	int price;
	float power;
	bool bOpen;
	std::string cannonName;
	float atkSpeed;
	short atkTime;
};

class GradeInf : public GameData
{
public:
	CREATE_OBJFUNC(GradeInf);
	GradeInf(){};
	~GradeInf(){};
	virtual void load(DataStream *dis);
public:
	int upReward;
	int upScore;
};

class RoomInf : public GameData
{
public:
	CREATE_OBJFUNC(RoomInf);
	RoomInf(){}
	~RoomInf(){}
	virtual void load(DataStream *dis);
public:
	int minCoin;//最低金币
	int cannonRateIndex;//需解锁的炮台倍率
	int vip;//vip条件
	float rp;
};

class SignReward : public GameData
{
public:
	CREATE_OBJFUNC(SignReward);
	SignReward(){}
	~SignReward(){}
	virtual void load(DataStream *dis);
public:
	int goldCount;
};

//////////////////////////////////////////////////////////////////////////
class FamilyName : public GameData
{
public:
	std::string txt;
public:
	CREATE_OBJFUNC(FamilyName);
	FamilyName(){}
	~FamilyName(){}
	virtual void load(DataStream *dis);
};
//////////////////////////////////////////////////////////////////////////
class OtherName : public GameData
{
public:
	std::string txt;
public:
	CREATE_OBJFUNC(OtherName);
	OtherName(){}
	~OtherName(){}
	virtual void load(DataStream *dis);
};
//////////////////////////////////////////////////////////////////////////
class CastInf : public GameData
{
public:
	CREATE_OBJFUNC(CastInf);
	CastInf(){};
	~CastInf(){};
	virtual void load(DataStream *dis);
public:
	int buygold;
	int buyworth;
	int count;
};
#endif