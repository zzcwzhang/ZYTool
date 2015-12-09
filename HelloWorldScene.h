#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
//using namespace cocostudio;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void update(float dt);

	void registerEventDispatcher();
	bool onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* evt);
	void onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* evt);
	void onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* evt);
	
  //  Armature *armature;
	//void animationCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
