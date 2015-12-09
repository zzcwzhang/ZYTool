#include "Coin.h"
#include "GameLayer.h"

Coin::Coin( CoinType type )
{
	m_coinType = type;
}

Coin::~Coin()
{
	m_coinPath.clear();
}

Coin* Coin::create( CoinType type )
{
	Coin *cn = new Coin(type);
	cn->init();
	cn->autorelease();
	cn->generateAnimation();
	return cn;
}

void Coin::generateAnimation()
{
	std::string name = "gold";
	if(m_coinType == COIN_TYPE_GOLDSMALL)
	{
		name = "yin";
	}
	coinArma = Armature::create(name);
	coinArma->setPosition(Vec2::ZERO);
	this->addChild(coinArma);
	this->setContentSize(Size(130,105));
	Size size = this->getContentSize();
	coinArma->getAnimation()->playWithIndex(0);
}

void Coin::goCoin()
{
	CallFunc* callfunc = CallFunc::create(this,callfunc_selector(Coin::addCoinDead));
	m_coinPath.pushBack(/*RemoveSelf::create(true)*/callfunc);

	this->runAction(Sequence::create(m_coinPath));
}

void Coin::addLineCoinPath( float duration, cocos2d::Vec2 p )
{
	MoveTo* mto = MoveTo::create(duration,p);
	m_coinPath.pushBack(mto);
}

void Coin::addCoinDead()
{
	coinArma->stopAllActions();
	coinArma->getAnimation()->playWithIndex(1);
	coinArma->getAnimation()->setMovementEventCallFunc(this,SEL_MovementEventCallFunc(&Coin::animationCallBack));
}

void Coin::animationCallBack( Armature *armature, MovementEventType movementType, const std::string& movementID )
{
	if(movementType==COMPLETE)
	{
		this->removeFromParent();
	}
}


