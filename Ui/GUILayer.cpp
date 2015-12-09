#include "GUILayer.h"
#include "UIManager.h"
//#include "UIConfig.h"
#include "GameLayer.h"
#include"UI.h"
#include "Cannon.h"
#include "GameDataManager.h"
#include "cocostudio/CocoStudio.h"
#include "GameManager.h"
#include "Tools.h"
#include "Player.h"
using namespace cocostudio;
USING_NS_CC;

int FishNum[101] = {0 ,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	20,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,
	30,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
	15,15,15,15,15,15,15,15,15,15,15,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,2 ,
	2};

int CheckGoldNum[101] = {0   ,550 ,650 ,750 ,850 ,950 ,1050 ,1150 ,1250 ,1350 ,
					1450,1550,1650,1750,1850,1950,2050 ,2150 ,2250 ,2350 ,
					2450,2550,2650,2750,2850,2950,3050 ,3150 ,3250 ,3350 ,
					3450,3550,3650,3750,3850,3950,4050 ,4150 ,4250 ,4350 ,
					4450,4550,4650,4750,4850,4950,5050 ,5150 ,5250 ,5350 ,
					5450,5550,5650,5750,5850,5950,6050 ,6150 ,6250 ,6350 ,
					6450,6550,6650,6750,6850,6950,7050 ,7150 ,7250 ,7350 ,
					7450,7550,7650,7750,7850,7950,8050 ,8150 ,8250 ,8350 ,
					8450,8550,8650,8750,8850,8950,9050 ,9150 ,9250 ,9350 ,
					9450,9550,9650,9750,9850,9950,10050,10150,10250,10350,10450};


int GetBeiLv1[10] = {2,3,4,5,6,7,8,9,10,11};					
int GetBeiLv2[3] = {12,15,18};
int GetBeiLv3[6] = {20,25,30,35,40,50};
int GetBeiLv4[5] = {120,130,140,150,160};

//int onLineTime[7] = {60,120,300,600,900,1800,3600};//在线时间


 GUILayer*GUILayer::guiLayer = nullptr;
 GUILayer* GUILayer::getInstance()
 {
 	if (guiLayer==nullptr)
 	{
		guiLayer = new GUILayer();
 	}
 	return guiLayer;
 }
bool GUILayer::init()
{
	if(!Layer::init()) return false;

	gTask = NULL;
	taskFish = NULL;


	

	initUIM();
	initCannon();

	
	nextTime = false;
	//HandleTime(onLineTime[inLinetime]);
	//inLinetime = onLineTime[inLineAwardNum];
	//onLineAwardGold = onLineAward[inLinetime];
	inituiArmature();
	return true;
}

void GUILayer::update( float dt )
{
	pCannon->update(dt);
	/*static int num = 0;
	if(inLineMinter==0 && inLineSecond==0) 
	{
		if(nextTime) 
		{
			nextTime = false;
			HandleTime(onLineTime[inLinetime]);
			onLineAwardGold = onLineAward[inLinetime];
		}
		return ;
	}
		
	if (inLineSecond>=0)
	{
		if (inLineMinter>0 && inLineSecond==0)
		{
			inLineMinter--;
			inLineSecond = 59;
		}

		num++;

		if (num%60==0)
		{
			inLineSecond--;
			num = 0;
		}

	}*/
}

void GUILayer::onTouchBegan( float fx,float fy )
{
	pCannon->onTouchBegan(fx,fy);
}

void GUILayer::onTouchMoved( float fx,float fy )
{
	pCannon->onTouchMoved(fx,fy);
}

void GUILayer::onTouchEnded( float fx,float fy )
{
	pCannon->onTouchEnded(fx,fy);
}

void GUILayer::initUIM()
{
	UIM->showForm(Form_buyuchang);
}

void GUILayer::initCannon()
{

}

void GUILayer::inituiArmature()
{
	auto gLevel = Armature::create("icon_2");//等级cocostudio动画
	gLevel->setPosition(Vec2(160,620));
	gLevel->getAnimation()->play("dengji");
	this->addChild(gLevel,1);
}

void GUILayer::checkTask()
{
	int curLevel = SELF->getGameCheck();
	LevelInf *inf = GData->getLevelInf(curLevel);
	taskFishtype = (Fish::FishType)getRandom(inf->targets.size() - 1);
	taskFishNum = inf->missionCount;
	CheckGold = inf->reward;
}

void GUILayer::showTask()
{
	if(gTask) gTask->removeFromParent();
	if(taskFish) taskFish->removeFromParent();

	gTask = Armature::create("icon_2");//关卡任务cocostudio动画
	gTask->setPosition(Vec2(105,450));
	gTask->getAnimation()->play("chongzhi");
	this->addChild(gTask,1);

	taskFish = Fish::createFishshadow(taskFishtype);
	taskFish->setPosition(Vec2(60,480));
	taskFish->setColor(Color3B(255,255,255));
	taskFish->setOpacity(255);
	taskFish->setRotation(90);
	this->addChild(taskFish,22);

	String* str = String::createWithFormat("0 / %d",taskFishNum);
	Label* taskNumLabel = Label::create(str->getCString(),"fonts/arial.ttf",24);
	taskNumLabel->setPosition(Vec2(160,480));
	taskNumLabel->setColor(Color3B(125,255,125));
	this->addChild(taskNumLabel,22);
}

void GUILayer::HandleTime( int time )
{
	
}



