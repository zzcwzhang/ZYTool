#include "UICallBack.h"
#include "SConfig.h"
#include "EditUI/UI.h"
#include "GUILayer.h"
#include "Cannon.h"
#include "GameManager.h"
#include "Player.h"
using namespace cocostudio;

void UICallBack::playNextArmature(Armature *pArmature, MovementEventType movementType, const char *movementID)
{
	std::string id = movementID;
	if(movementType == LOOP_COMPLETE ||
		movementType == COMPLETE)
	{
		auto pString = (String*)pArmature->getUserData();
		pArmature->getAnimation()->play(pString->getCString());
		pArmature->getAnimation()->setMovementEventCallFunc(nullptr,nullptr);
		CC_SAFE_RELEASE(pString);
	}
	else if(movementType == START)
	{
		
	}
}

void UICallBack::setFormUnVisible()
{
	UIM->getForm(Form_danrenmoshixuanguan)->setVisible(false);
}

void UICallBack::setFormRenwutankuangClose()
{
	UIM->closeForm((short)Form_renwutankuang,true);

	auto curForm = UIM->getForm(Form_buyuchang);
	auto task = curForm->getControl(buyuchang_control18);
	task->setVisible(true);

	task->setScale(0.01f);
	auto scale1 = ScaleTo::create(0.25f,1.2f,1.2f);
	auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
	task->runAction(Sequence::createWithTwoActions(scale1,scale2));

	auto taskPrompt = curForm->getControl(buyuchang_control22);
	taskPrompt->setVisible(true);
	//task->setScale(0.01f);
	//task->runAction(Sequence::create(DelayTime::create(0.5f),ScaleTo::create(0.2f,1.2f,1.2f),ScaleTo::create(0.2,1.0f,1.0f),NULL));
}

void UICallBack::removeArmature( cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const char *movementID )
{
	if (movementType == COMPLETE)
	{
		pArmature->removeFromParent();
	}
}

void UICallBack::missilePrepareCallBack(cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const char *movementID)
{
	if (movementType == COMPLETE)
	{
		pArmature->getAnimation()->setMovementEventCallFunc(this,nullptr);
		SELF->getCannon()->bPrepareFire = false;
	}
}

void UICallBack::setMisssionAppear()
{
	SELF->getCannon()->specialArm->getAnimation()->play("dd_chuxian");
	SELF->getCannon()->specialArm->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(UICallBack::missilePrepareCallBack));
}

void UICallBack::setLaserAppear()
{
	SELF->getCannon()->specialArm->getAnimation()->play("jg_tuichu");
	SELF->getCannon()->specialArm->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(UICallBack::missilePrepareCallBack));
}

void UICallBack::setBulletLockBlast(cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const char *movementID)
{
	if (movementType==COMPLETE)
	{
		auto form = UIM->getForm(Form_jiesuopaodan);
		MListView *bulletList = (MListView *)form->getControl(jiesuopaodan_control3);
		MControl *item = bulletList->getItem(0);
		bulletList->removeItem(item);
	}
}


void UICallBack::MissileOrLaserReadyCallBack( cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const char *movementID )
{
	if (movementType == COMPLETE)
	{
		//guiGame->getCannon()->missileReady = true;
	}
}

void UICallBack::SetbigGoldArmaCallBack(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID)
{
	if (movementType == COMPLETE)
	{
		std::string nextStr = "";
		if (movementID.compare("jinbi")==0)
		{
			nextStr = "jinbi_zhuan";
		}
		armature->getAnimation()->play(nextStr);
		armature->getAnimation()->setMovementEventCallFunc(armature,movementEvent_selector(UICallBack::removeArmature));
	}

	if(movementType==START)
	{
		String *pStr = (String*)armature->getUserData();
		NumSprite* np = NumSprite::create(atoi(pStr->getCString()),GameNumberStoreLayerLevel);
		np->setPosition(Vec2(0,-65));
		np->setScale(0.85f);
		armature->addChild(np,20);
	}
}

void UICallBack::onlineRewardCallback()
{
	auto form = UIM->getForm(Form_zaixianjiangli);
	auto ctrl = form->getControl(zaixianjiangli_control14);

	ctrl->setVisible(false);
}

void UICallBack::playGradeArmature( cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const std::string& movementID )
{
	if (movementType==COMPLETE)
	{
		std::string nextStr = "";
		if(movementID.compare("dengji") == 0)
		{
			nextStr = "dengji_2";
		}
		else if(movementID.compare("taibang") == 0)
		{
			nextStr = "taibang_2";
		}
		pArmature->getAnimation()->play(nextStr);
		pArmature->getAnimation()->setMovementEventCallFunc(pArmature,movementEvent_selector(UICallBack::removeArmature));
	}
	if (movementType==START)
	{
		if (movementID.compare("dengji")==0 || movementID.compare("dengji_2")==0)
		{
			GradeInf* Inf = GData->getGradeInf(SELF->getPlayGrade());
			NumSprite* np = NumSprite::create(Inf->upReward,GameNumberStoreLayerLevel);
			np->setScale(0.75f);
			np->setPosition(Vec2(40,-25));
			pArmature->addChild(np,1000);

			if (!pRunData->bUpLevel)
			{
				char str[60];
				sprintf(str,"r_%d",SELF->getPlayRank());
				std::string L_Index = GMI->getString("UIText",str);
				auto label = Label::createWithSystemFont(L_Index.c_str(),"Aril",24);
				label->setColor(Color3B(255,255,0));
				label->setPosition(40,25);
				pArmature->addChild(label,1000);
			}
		}
		
		if (movementID.compare("taibang")==0 || movementID.compare("taibang_2")==0)
		{
			auto catchFish = Fish::createFishshadow((Fish::FishType)pRunData->catchFishType);
			catchFish->setPosition(90,80);
			catchFish->setColor(ccc3(255,255,255));
			catchFish->setOpacity(255);
			catchFish->setFlipX(true);
			catchFish->setRotation(-90);
			catchFish->setScale(0.50f);
			pArmature->addChild(catchFish,22);
		}
	}
}

void UICallBack::playGradeNextArmature( cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const char *movementID )
{
// 	if (movementType==COMPLETE)
// 	{
// 		
// 	}
}

void UICallBack::showLogin()
{
	UIM->showForm(Form_dengluchuangkou);
}

//关闭道具提示框
void UICallBack::closePropDialog()
{
	propDialogTxt = "";
	propCtrl = nullptr;
	UIM->closeForm(Form_daojutishikuang,false);

}
