#include "HelloWorldScene.h"
#include "SConfig.h"
USING_NS_CC;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::registerEventDispatcher()
{
	auto touchEvt                =   EventListenerTouchOneByOne::create();  
	touchEvt->onTouchBegan       =   CC_CALLBACK_2(HelloWorld::onTouchBegan,this);  
	touchEvt->onTouchMoved       =   CC_CALLBACK_2(HelloWorld::onTouchMoved,this);  
	touchEvt->onTouchEnded       =   CC_CALLBACK_2(HelloWorld::onTouchEnded,this);  
	touchEvt->onTouchCancelled   =   CC_CALLBACK_2(HelloWorld::onTouchCancelled,this); 

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvt,this);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    this->scheduleUpdate();
	registerEventDispatcher();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    //this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);

    /******************使用CocoStudio动画起***********************/
	//ArmatureDataManager::getInstance()->addArmatureFileInfo("Export/Defence0.png", "Export/Defence0.plist", "Export/Defence.ExportJson");
	//armature = Armature::create("Defence");
	//armature->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	//armature->getAnimation()->play("windmill");
	//armature->getAnimation()->setMovementEventCallFunc(this,SEL_MovementEventCallFunc(&HelloWorld::animationCallBack));
	////armature->getAnimation()->playWithIndex(0);
	//this->addChild(armature);
	///******************使用CocoStudio动画终***********************/
	//char str[20] = {0};
	//sprintf_s(str,"123456");

	/******************使用序列帧动画起***********************/
	/*SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Defence0.plist");
	auto sp = Sprite::createWithSpriteFrameName("car40.png");
    sp->setPosition(150,150);
  
    auto ani = Animation::create();  
    for (int i = 0;i < 4;i++)  
    {  
        std::string fileName = StringUtils::format("car4%d.png",i);  
        ani->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));  
    }  
    ani->setLoops(-1);  
    ani->setDelayPerUnit(0.05f);  
  
    Animate* animate = Animate::create(ani);  
    sp->runAction(animate);  
    this->addChild(sp); */ 
	/******************使用序列帧动画终***********************/

	////__Array* array = new __Array();
	//Vector<FiniteTimeAction*>frameArray;
	//Vector<FiniteTimeAction*>frameArray1;
	////auto frameArray = Array::create(); 
	//
	//auto sprite1 = Sprite::create("CloseNormal.png");
	//sprite->setPosition(Point(100,100));
	//this->addChild(sprite);

	//auto moveto = MoveTo::create(2.5f,Point(300,300));
	//auto moveby = MoveBy::create(1.5f,Point(500,500));

	//frameArray.pushBack(moveto);
	//frameArray.pushBack(moveby);

	//frameArray1.pushBack(frameArray);
	//sprite->runAction(Sequence::create(frameArray1));
	////sprite->runAction(Sequence::create(RotateBy::create(1.0f,360),ScaleTo::create(1.0f,1.2f),NULL)); 
	//
	//

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
//    //Director::getInstance()->end();
//	//this->removeChild(armature);
//	armature->setScaleX(-1);
//	auto move = MoveTo::create(1.5f,Point(700,290));
//	armature->runAction(move);
//	
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}

//void HelloWorld::animationCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID)
//{
//	if(movementType==COMPLETE)
//	{
//		//this->removeChild(armature);
//	}
//}

bool HelloWorld::onTouchBegan( Touch* touch,Event* evt )
{
	log("SSS");
	return true;
}

void HelloWorld::onTouchMoved( Touch* touch,Event* evt )
{

}

void HelloWorld::onTouchEnded( Touch* touch,Event* evt )
{

}

void HelloWorld::update(float dt)
{
	log("AAA");
}






