#include "GameLayer.h"
#include "Fish.h"
#include "FishGroup.h"
#include "FishMatrix.h"
#include "GUILayer.h"
#include "Cannon.h"
#include "Bullet.h"
#include "UIManager.h"
#include "UIConfig.h"
#include "GScene.h"
#include "GameInit.h"
#include "SConfig.h"
#include "GameDataManager.h"
#include "UI.h"
#include "GameManager.h"
#include "Player.h"
int onLineTime[7] = {1,2,5,10,15,30,60};//测试在线时间
int onLineAward[7] = {500,800,1500,2500,5000,10000,20000};//奖励金币
GameLayer::GameLayer() 
{
	bPause = false;
	killTaskFishNum = 0;
	isPromote = false;
	nextCheck = false;
	objActionManger = new ActionManager();
	onlineRewardIndex = 0;
	loadResource();
}

GameLayer::~GameLayer()
{
	
	objActionManger->removeAllActions();
	objActionManger->release();
	
}

GameLayer* GameLayer::create(int index)
{
	GameLayer *pret = new GameLayer();
	if(pret && pret->initWithRoomIndex(index))
	{
		pret->autorelease();
		return pret;
	}
	else
	{
		delete pret;
		return nullptr;
	}
}
void GameLayer::loadResource()
{

}

bool GameLayer::initWithRoomIndex(int index)
{
	if(!Room::initWithRoomIndex(index)) return false;
	GMI->setRoom(this);
	auto catchfishScene = UIM->showForm(Form_buyuchang);/*修改*/
	_player = SELF;
	_player->initCannon();
	_player->setSeat(0);
	addPlayer(_player);
	checkTask();

	/****************修改******************/
	auto renwu = UIM->showForm(Form_renwutankuang);
	auto ctrl1 = renwu->getControl(renwutankuang_control1);
	ctrl1->setOpacity(125);

	renwu->setEnabled(true);
	renwu->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);

	auto ctrl2 = renwu->getControl(renwutankuang_control2);
	ctrl2->setScale(0.01f);
	auto scale1 = ScaleTo::create(0.25f,1.2f,1.2f);
	auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
	ctrl2->runAction(Sequence::createWithTwoActions(scale1,scale2));
	
	catchfishScene->getControl(buyuchang_control25)->setVisible(false);
	/****************修改******************/
	return true;
}

void GameLayer::pauseObjAction(float time)
{
	bPause = true;
	pauseTime = time;
}
void GameLayer::resumeObjAction()
{
	bPause = false;
}

bool GameLayer::isPause()
{
	return bPause;
}

void GameLayer::checkTask()
{
	int curLevel = _player->getGameCheck()-1;
	LevelInf *inf = GData->getLevelInf(curLevel);
	taskFishtype = (Fish::FishType)getRandom(inf->targets.size() - 1);
	taskFishNum = inf->missionCount;
	CheckGold = inf->reward;
	backTaskTime = 10 * 60.0f;
	setInLineTime(0);
}

int GameLayer::getKilltaskFishNum()
{
	return killTaskFishNum;
}
void GameLayer::clearKilltaskFishNum()
{
	killTaskFishNum = 0;
}
int GameLayer::getTaskfishNum()
{
	return taskFishNum;
}
int GameLayer::getTaskfishType()
{
	return taskFishtype;
}
int GameLayer::getCheckGold()
{
	return CheckGold;
}

void GameLayer::setInLineTime(int index)
{
	onlineRewardIndex = index;
	if(index >=7)
	{
		onlineLock = true;
		return;
	}
	onlineCoin = onLineAward[index];
	onlineTime = onLineTime[index] * 6.0f;
	onlineLock = false;
}

int GameLayer::getInLineMinter()
{
	int ms = ((int)onlineTime)%3600;
	return ms/60;
}
int GameLayer::getInLineSecond()
{
	return((int)onlineTime)%60; /*修改*/
}

int GameLayer::getGobackSec()
{
	return((int)backTaskTime)%60;
}
int GameLayer::getGobackMin()
{
	int ms = ((int)backTaskTime)%3600;
	return ms/60;
}
int GameLayer::getGobackHor()
{
	return ((int)backTaskTime)/3600;
}

void GameLayer::update( float delta )
{
	backTaskTime -= delta;
// 	
// 	static int fico = 0;
// 	if (getFishes().size()!=fico)
// 	{
// 		fico =getFishes().size();
// 		log("fihes count %d",getFishes().size());
// 	}
	

	//在线奖励
	if(!onlineLock)
	{
		onlineTime -= delta;
		if(onlineTime <= 0)
		{
			onlineLock = true;
		}
	}
	
	if(killTaskFishNum==taskFishNum)
	{
		killTaskFishNum = 0;
		taskFishtype = Fish::FishType(-1);
		//UIM->showForm(Form_gameend);

 		auto form = UIM->getForm(Form_buyuchang);
 		auto ctrl1 = form->getControl(buyuchang_control18);
 		auto ctrl2 = form->getControl(buyuchang_control22);
 		auto ctrl3 = form->getControl(buyuchang_control41);
		
 		ctrl1->setVisible(false);
 		ctrl2->setVisible(false);
 		ctrl3->setVisible(true);
 
 		ctrl3->setScale(0.01f);
 		auto scale1 = ScaleTo::create(0.25f,1.20f,1.20f);
 		auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
 		ctrl3->runAction(Sequence::createWithTwoActions(scale1,scale2));
	}

	if(FishTag >= FISHTAGPOOR) FishTag = 0;

	_player->getCannon()->update(delta);
	//guiGame->update(delta);

	//自定义管理Action
	if(!bPause)
	{
		objActionManger->update(delta);
	}
	else
	{
		if(pauseTime > 0.0f)
		{
			pauseTime -= delta;
			if(pauseTime <= 0.0f)
			{
				bPause = false;
			}
		}
	}
	updateYuchaoTime(delta);
	this->checkBullets();
	this->updateFishShadow(delta);
	this->checkDeblock();
}

bool GameLayer::catchFish(Fish *pFish, Bullet *pBullet)
{
	if(Room::catchFish(pFish,pBullet))
	{
		if (pFish->getFishType()==taskFishtype)
		{
			if(killTaskFishNum!=taskFishNum)
			{
				killTaskFishNum++;
			}
		}
		return true;
	}
	return false;
}

void GameLayer::removeTaskScene()
{
	/****************修改******************/
	auto form = UIM->showForm(Form_renwutankuang);
	auto ctrl = form->getControl(renwutankuang_control1);
	ctrl->setOpacity(0);

	auto ctrl2 = form->getControl(renwutankuang_control2);
	auto scale2 = ScaleTo::create(0.25f,0.01f,0.01f);
	auto scale1 = ScaleTo::create(0.2f,1.2f,1.2f);
	
	CallFunc *endCallBack = CallFunc::create(form,callfunc_selector(UICallBack::setFormRenwutankuangClose));

	ctrl2->runAction(Sequence::create(scale1,scale2,endCallBack,nullptr));
	
	this->schedule(schedule_selector(Room::updateFish),0.5f);
	/****************修改******************/
}



void GameLayer::bubbleAnimationCallBack( Armature *armature, MovementEventType movementType, const std::string& movementID )
{
	if(movementType==COMPLETE)
	{
		this->removeChild(armature);
		//switchBGView(0);
	}
}

void GameLayer::exitLayer()
{
	Room::exitLayer();
	
}