#include "GameInit.h"
#include "GScene.h"
#include "UI.h"
#include "GameManager.h"
#include "Player.h"
GameInit::GameInit()
	:count(0)
{
	
}

GameInit::~GameInit()
{

}

bool GameInit::init()
{
	if (Layer::init())
	{
		getRandom(100);
		Size visibleSize = Director::getInstance()->getVisibleSize();

		//背景
		Sprite *loadbg = Sprite::create("start.jpg");
		loadbg->setPosition(visibleSize.width/2,visibleSize.height/2);
		this->addChild(loadbg);

		GMI->loadText();

		std::string loading = GMI->getString("UIText","text9");
		auto label = Label::create(loading.c_str(),"Aril",24);
		label->setPosition(630,100);
		this->addChild(label);
		//背景气泡
// 		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/load_paopao/load_paopao.ExportJson");
// 		Armature *paopaoArm = Armature::create("load_paopao");
// 		paopaoArm->setPosition(visibleSize.width/2,visibleSize.height/2);
// 		paopaoArm->getAnimation()->play("stand");
// 		this->addChild(paopaoArm);
// 
// 		//loading...
// 		Sprite *loadingCircle = Sprite::create("loading4.png");
// 		loadingCircle->setPosition(visibleSize.width/2 - 115,100);
// 		this->addChild(loadingCircle);
// 		RotateBy *spRotate = RotateBy::create(1,180);
// 		loadingCircle->runAction(RepeatForever::create(spRotate));
// 
// 		Sprite *loadingSp = Sprite::create("loading2.png");
// 		loadingSp->setPosition(visibleSize.width/2,100);
// 		this->addChild(loadingSp);
// 
// 		int offset = 27;
// 		loadingP0 = Sprite::create("loading3.png");
// 		loadingP0->setPosition(visibleSize.width/2 + 86,95);
// 		this->addChild(loadingP0);
// 
// 		loadingP1 = Sprite::create("loading3.png");
// 		loadingP1->setPosition(visibleSize.width/2 + 86+offset,95);
// 		this->addChild(loadingP1);
// 
// 		loadingP2 = Sprite::create("loading3.png");
// 		loadingP2->setPosition(visibleSize.width/2 + 86+2*offset,95);
// 		this->addChild(loadingP2);
		return true;
	}
	return false;
}

void GameInit::update(float delta)
{
// 
// 	if (count % 20 < 5)
// 	{
// 		loadingP0->setVisible(false);
// 		loadingP1->setVisible(false);
// 		loadingP2->setVisible(false);
// 	}
// 	else if (count % 20 < 10)
// 	{
// 		loadingP0->setVisible(true);
// 		loadingP1->setVisible(false);
// 		loadingP2->setVisible(false);
// 	} 
// 	else if (count % 20 < 15)
// 	{
// 		loadingP0->setVisible(true);
// 		loadingP1->setVisible(true);
// 		loadingP2->setVisible(false);
// 	}
// 	else
// 	{
// 		loadingP0->setVisible(true);
// 		loadingP1->setVisible(true);
// 		loadingP2->setVisible(true);
// 	}
	count++;

	switch (count)
	{
	case 10:
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/CJ1/haicao.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/CJ2/CJ2.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/CJ4/CJ4.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/CJ5/CJ_5.ExportJson");
		break;
	case 20:
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/daoju/daoju.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/daoju2/daoju2.ExportJson");
		break;
	case 30:
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/fire/bdp_fire/bdp_fire.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/fire/hxj_fire/hxj_fire.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/fire/jiguangp_fire/jiguangp_fire.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/fire/ldp_fire/ldp_fire.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/fire/pao_fire/pao_fire.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/fire/shuip_fire/shuip_fire.ExportJson");
		break;
	case 35:
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/fm_logo/fm_logo.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/gold/gold.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/yin/yin.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/tsy_01/tsy_01.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/iphone/iphone.ExportJson");
		break;
	case 40:
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/gun/bdp_dh/bdp_dh.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/gun/hxj/hxj.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/gun/jiguangp/jiguangp.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/gun/ldp/ldp.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/gun/pao/pao.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/gun/paokou/paokou.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/gun/shuip/shuip.ExportJson");
		break;
	case 45:
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/guoguan_renwu/guoguan_renwu.ExportJson");//道具加载
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/icon/icon.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/icon_2/icon_2.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/icon_3/icon_3.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/icon_4/icon_4.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/icon_5/icon_5.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/icon_6/icon_6.ExportJson");
		break;
	case 50:
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/jiangquan/jiangquan.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/jiesuo/jiesuo.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/jingdiancg/jingdiancg.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/lianjiduizhan/lianjiduizhan.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/lipinshangcheng/lipinshangcheng.ExportJson");
		break;
	case 55:
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/load_paopao/load_paopao.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/new_3tu/new_3tu.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/paopao/paopao.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/lipinshangcheng/lipinshangcheng.ExportJson");
		break;
	case 60:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Num/G_Num.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Num/L_Num.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Num/V_Num.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Fish/Fish.plist");
		break;
	case 70:
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/qipao_1/qipao_1.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/qipao_2/qipao_2.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/shuibo/shuibo.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/start/start.ExportJson");
		ArmatureDataManager::getInstance()->addArmatureFileInfo("UIEffect/upgrade/upgrade.ExportJson");
		break;
	case 80:
		GMI->setMySelf(new Player());
		GData->loadGameInfo();
		break;
	case 90:
		GMI->readRecord();
		SMI->initSoundRes();
		break;
	case 101:
		GScene->setState(GST_MENU);
		break;
	default:
		break;
	}

}

void GameInit::exitLayer()
{

}