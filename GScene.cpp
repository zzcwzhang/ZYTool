#include "GScene.h"
#include "UIManager.h"
#include "GameInit.h"
#include "GameManager.h"
#include "introLayer.h"
#include "GameLayer.h"
#include "OnLineLayer.h"
#include "SMSInfo.h"
GameScene* GameScene::instance = nullptr;

GameScene::GameScene()
	:_baseLayer(nullptr)
{
	_curState = GST_NONE;
	_preState = GST_NONE;
}

GameScene::~GameScene()
{

}

Scene* GameScene::createScene()
{
	Scene * scene = Scene::create();

	auto *layer = GScene;
	GScene->init();

	scene->addChild(layer);

	return scene;
}

GameScene* GameScene::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameScene();
	}
	return instance;
}

bool GameScene::init()
{
	if (Layer::init())
	{
		UIM->init();
		this->addChild(UIM->getLayer(),3);

		setState(GST_INIT);
		scheduleUpdate();
		return true;
	}

	return false;
}

void GameScene::update(float delta)
{
	if (_baseLayer)
	{
		_baseLayer->update(delta);
	}
	UIM->updateLogic(delta);

	if(pSMSInfo->bSmsCharge)
	{
		pSMSInfo->bSmsCharge = false;
		doSms();

		pSMSInfo->smsChargeId = -1;
		pSMSInfo->smsChargeResult = 0;
	}
}

void GameScene::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	Layer::draw(renderer,transform,flags);

	UIM->drawUI();
}

GAMESTATE GameScene::getCurState()
{
	return _curState;
}

void GameScene::setState(GAMESTATE state)
{
	if (_curState != state)
	{
		if (_preState != GST_NONE && _baseLayer)
		{
			_baseLayer->exitLayer();
			_baseLayer->removeFromParent();
			_baseLayer = nullptr;
		}

		_preState = _curState;
		_curState = state;

		switch (state)
		{
		case GST_NONE:
			break;
		case GST_INIT:
			_baseLayer = GameInit::create();
			this->addChild(_baseLayer,0,0);
			break;
		case GST_MENU:
			_baseLayer = IntroLayer::create();
			this->addChild(_baseLayer,0,0);
			break;
		case GST_GAME:
			//_baseLayer = GameLayer::create();
			_baseLayer = GameLayer::create(0);
			this->addChild(_baseLayer,0,0);
			break;
		case GST_OnLineGame:
			_baseLayer = OnLineLayer::create(pRunData->curRoomIndex);
			this->addChild(_baseLayer,0,0);
			break;
		default:
			break;
		}
	}
}

void doSms()
{
	if(pSMSInfo->smsChargeResult == 1)
	{
		doSuccess();
	}
	else
	{
		doFaile();
	}
}
void doSuccess()
{
	if(pSMSInfo->smsChargeCallBack)
	{
		pSMSInfo->smsChargeCallBack(pSMSInfo->smsChargeId,true);
	}
	refreshUIForm();
	GMI->saveRecord();
}
void doFaile()
{
	if(pSMSInfo->smsChargeCallBack)
	{
		pSMSInfo->smsChargeCallBack(pSMSInfo->smsChargeId,false);
	}
}
void refreshUIForm()
{

}