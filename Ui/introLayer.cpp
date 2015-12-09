#include "introLayer.h"
#include "cocostudio/CocoStudio.h"
#include "GScene.h"
#include "EditUI/UI.h"
using namespace cocostudio;

IntroLayer::IntroLayer()
{
	/*for (int i=1;i<7;i++)
	{
		char str[30];
		memset(str,'0',sizeof(str));
		sprintf(str,"Fish/Fish%d.plist",i);
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(str);
	}*/
}

IntroLayer::~IntroLayer()
{

}


bool IntroLayer::init()
{
	if(!Layer::init()) return false;
	//registerEventDispatcher();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bgView = Sprite::create("start.jpg");
	bgView->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(bgView);

	//Ìí¼Ó±³¾°¶¯»­
	auto bgArm = Armature::create("start");
	bgArm->setPosition(visibleSize.width/2,visibleSize.height/2);
	bgArm->getAnimation()->play("stand");
	this->addChild(bgArm);

	auto curForm = UIM->showForm(Form_fengmian);
	curForm->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);

	//±³¾°ÒôÀÖ
	SMI->playSound("fengmian_bgm.mp3",true);

	paopaoInterval = 0;

	return true;
}

void IntroLayer::registerEventDispatcher()
{
	auto touchEvt                =   EventListenerTouchOneByOne::create();  
	touchEvt->onTouchBegan       =   CC_CALLBACK_2(IntroLayer::onTouchBegan,this);  
	touchEvt->onTouchMoved       =   CC_CALLBACK_2(IntroLayer::onTouchMoved,this);  
	touchEvt->onTouchEnded       =   CC_CALLBACK_2(IntroLayer::onTouchEnded,this);  
	//touchEvt->onTouchCancelled   =   CC_CALLBACK_2(IntroLayer::onTouchCancelled,this); 

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvt,this);
}

bool IntroLayer::onTouchBegan( Touch* touch,Event* evt )
{
	log("QQQ");
	return true;
}

void IntroLayer::onTouchMoved( Touch* touch,Event* evt )
{
	
}

void IntroLayer::onTouchEnded( Touch* touch,Event* evt )
{
	auto point = touch->getLocation();
	log("po.x:%f,po.y:%f",point.x,point.y);
	//startGame();
}

void IntroLayer::startGame(Ref* sendor)
{
	//Sound::Instance()->pauseMusic();
	//Director::getInstance()->pushScene(TransitionFade::create(1.0f,GameLayer::createScene()));
	GScene->setState(GST_GAME);
}

void IntroLayer::endGame( Ref* sendor )
{
	Director::getInstance()->end();
}

void IntroLayer::update(float delta)
{
	paopaoInterval += delta;

	if (paopaoInterval > 5.0f)
	{
		paopaoInterval = 0;
		SMI->playSound("fengmian_paopao.mp3",false);
	}
}

void IntroLayer::exitLayer()
{

}