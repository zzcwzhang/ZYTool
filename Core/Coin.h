#ifndef __fish_Coin__
#define __fish_Coin__
#include "cocos2d.h"
#include<iostream>
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace cocostudio;
class Coin : public cocos2d::Node
{
public:
	enum CoinType{
		COIN_TYPE_GOLDSMALL,
		COIN_TYPE_GOLDBIG
	};
	static Coin* create(CoinType type);
	Coin(CoinType type);
	~Coin();
	void addLineCoinPath(float duration, cocos2d::Vec2 p);
	void goCoin();
	void addCoinDead();
	void animationCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID);
	Vector<FiniteTimeAction*>m_coinPath;
	Armature*coinArma;
protected:
	CoinType m_coinType;
	void generateAnimation();
};
#endif