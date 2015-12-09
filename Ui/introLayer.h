#ifndef __IntroLayer_H__
#define __IntroLayer_H__
#include "cocos2d.h"
#include "GameBase.h"
USING_NS_CC;

class IntroLayer : public BaseLayer
{
public:
	IntroLayer();
	~IntroLayer();
	virtual bool init();
	
	void registerEventDispatcher();
	bool onTouchBegan(Touch* touch,Event* evt);
	void onTouchMoved(Touch* touch,Event* evt);
	void onTouchEnded(Touch* touch,Event* evt);

	void startGame(Ref* sendor);
	void endGame(Ref* sendor);
	CREATE_FUNC(IntroLayer);

	virtual void update(float delta);
	virtual void exitLayer();
	
public:
	Layer *m_pWaveRipple;
	float paopaoInterval;		//???Y????
};
#endif