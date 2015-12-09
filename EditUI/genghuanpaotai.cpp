#include"UI.h"
#include "GameLayer.h"
#include "Helper.h"
#include "GUILayer.h"
#include "GameData.h"
#include "GameManager.h"
#include "GameDataManager.h"
#include "Player.h"
int pCannonWorth[6] = {1000,2000,3000,4000,5000,6000};
//bool Refresh = false;
void genghuanpaotai_register(Node* node)
{
   UIForm *form = (UIForm*)node;
   form->getControl(genghuanpaotai_control4)->registerClickEvent(genghuanpaotai_control4_Click);
   form->getControl(genghuanpaotai_control7)->registerClickEvent(genghuanpaotai_control7_Click);
   form->getControl(genghuanpaotai_control10)->registerClickEvent(genghuanpaotai_control10_Click);

}

String* getStingForIndex(int dex)
{
	String* str;
	switch(dex)
	{
	case 3:
		str = String::create("bdp_dh");
		break;
	case 4:
		str = String::create("hxj");
		break;
	case 5:
		str = String::create("jiguangp");
		break;
	case 2:
		str = String::create("ldp");
		break;
	case 0:
		str = String::create("pao");
		break;
	case 1:
		str = String::create("shuip");
		break;
	}
	return str;
}

int pIndex = 0;
void genghuanpaotai_control5_Paint(Node* node)//显示炮台
{
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();

	CannonInf *pStr = (CannonInf *)ctrl->getParent()->getUserData();
	auto pao = Armature::create(pStr->cannonName);

	if (pStr->cannonName.compare("pao")==0)
	{
		pao->setPosition(size.width/2,size.height/2-35);
		pao->setScale(0.65f);
	}
	else if (pStr->cannonName.compare("shuip")==0)
	{
		pao->setPosition(size.width/2,size.height/2-40);
		pao->setScale(0.65f);
	}
	else if (pStr->cannonName.compare("ldp")==0)
	{
		pao->setPosition(size.width/2,size.height/2-35);
		pao->setScale(0.65f);
	}
	else if (pStr->cannonName.compare("bdp_dh")==0)
	{
		pao->setPosition(size.width/2,size.height/2-5);
		pao->setScale(0.75f);
	}
	else if (pStr->cannonName.compare("hxj")==0)
	{
		pao->setPosition(size.width/2,size.height/2-10);
		pao->setScale(0.55f);
	}
	else if (pStr->cannonName.compare("jiguangp")==0)
	{
		pao->setPosition(size.width/2,size.height/2-15);
		pao->setScale(0.55f);
	}
		
	pao->getAnimation()->play("DJ_show");

	paintNode->addChild(pao);

	
}

void genghuanpaotai_control6_Paint(Node* node)//炮台标签
{
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();

	CannonInf *pStr = (CannonInf *)ctrl->getParent()->getUserData();

	char str[64];
	sprintf(str,"%s.png",pStr->cannonName.c_str());
	auto sp = Sprite::create(str);
	sp->setPosition(size.width/2,size.height/2);
	paintNode->addChild(sp);

}

int getNumSpriteIndex(std::string str)
{
	if (str.compare("pao")==0)//ldp  bdp_dh  hxj  jiguangp
	{
		return 0;
	}
	else if (str.compare("shuip")==0)
	{
		return 1;
	}
	else if (str.compare("ldp")==0)
	{
		return 2;
	}
	else if (str.compare("bdp_dh")==0)
	{
		return 3;
	}
	else if (str.compare("hxj")==0)
	{
		return 4;
	}
	else if (str.compare("jiguangp")==0)
	{
		return 5;
	}
	return 0;
}

Sprite* sp[6] = {NULL};
NumSprite* np[6] = {NULL};
void genghuanpaotai_control7_Paint(Node *node)//炮台价格
{
	MControl *ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node *paintNode = ctrl->getPaintNode();
	CannonInf *pStr = (CannonInf *)ctrl->getParent()->getUserData();

	if (!pStr->bOpen)
	{
		sp[getNumSpriteIndex(pStr->cannonName)] = Sprite::create("RMB.png");
		sp[getNumSpriteIndex(pStr->cannonName)]->setPosition(size.width/2-60,size.height/2);
		paintNode->addChild(sp[getNumSpriteIndex(pStr->cannonName)]);

		np[getNumSpriteIndex(pStr->cannonName)] = NumSprite::create(pStr->price,GameNumberStoreLayerLevel);
		//np[getNumSpriteIndex(pStr->cannonName)]->setAnchorPoint(Vec2(1,0.5));
		np[getNumSpriteIndex(pStr->cannonName)]->setPosition(size.width/2+20,size.height/2);
		paintNode->addChild(np[getNumSpriteIndex(pStr->cannonName)]);

		np[getNumSpriteIndex(pStr->cannonName)]->setScale(0.5f);
	}
	else
	{
		if (pStr->m_id==SELF->curCannonIndex)
		{
			sp[getNumSpriteIndex(pStr->cannonName)] = Sprite::create("yzb.png");
			sp[getNumSpriteIndex(pStr->cannonName)]->setPosition(size.width/2,size.height/2);
			paintNode->addChild(sp[getNumSpriteIndex(pStr->cannonName)]);
		}
		else
		{
			sp[getNumSpriteIndex(pStr->cannonName)] = Sprite::create("zb.png");
			sp[getNumSpriteIndex(pStr->cannonName)]->setPosition(size.width/2,size.height/2);
			paintNode->addChild(sp[getNumSpriteIndex(pStr->cannonName)]);
		}
	}
}


void genghuanpaotai_control7_update(Node*node,float dt)//###
{
	MControl *ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node *paintNode = ctrl->getPaintNode();
	CannonInf *pStr = (CannonInf *)ctrl->getParent()->getUserData();
	
	if (pStr->bOpen)
	{
		if (SELF->curCannonIndex != pStr->m_id)
		{
			if(sp[getNumSpriteIndex(pStr->cannonName)]) sp[getNumSpriteIndex(pStr->cannonName)]->initWithFile("zb.png");
		}
		else
		{
			if(sp[getNumSpriteIndex(pStr->cannonName)]) sp[getNumSpriteIndex(pStr->cannonName)]->initWithFile("yzb.png");
		}
	}
}
void genghuanpaotai_initialize(Node* node)
{
	UIForm* form = (UIForm*)node;
	form->getControl(genghuanpaotai_control5)->registerPaintEvent(genghuanpaotai_control5_Paint);
	form->getControl(genghuanpaotai_control6)->registerPaintEvent(genghuanpaotai_control6_Paint);
	form->getControl(genghuanpaotai_control7)->registerPaintEvent(genghuanpaotai_control7_Paint);
	form->getControl(genghuanpaotai_control7)->registerUpdateLogicEvent(genghuanpaotai_control7_update);
	MListView *cannonList = (MListView *)form->getControl(genghuanpaotai_control3);

	cannonList->clearItems();
	int count = GData->cannonArray.size();
	cannonList->setItemCount(count);

	for (int i = 0;i < count;++i)
	{
		MControl *item = cannonList->getItem(i);
		item->setUserData(GData->getCannonInf(i));
	}	
}



//control4
void genghuanpaotai_control4_Click(Node *node,Touch* ptouch, Event* event)
{
	log("ctrl4");
	auto form = UIM->getForm(Form_genghuanpaotai);
	auto ctrl = form->getControl(genghuanpaotai_control7);
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();

	MControl*ctrl1 = (MControl*)node;
	CannonInf *pStr = (CannonInf *)ctrl1->getUserData();

	if (!pStr->bOpen)
	{
		if (SELF->getGold()>pStr->price)
		{
			pStr->bOpen = true;
			SELF->addGold(-pStr->price);
			//GMI->curCannonInfIndex = pStr->m_id;
			//guiGame->getCannon()->initWithCannonType((CannonType)GMI->curCannonInfIndex);

			np[getNumSpriteIndex(pStr->cannonName)]->setVisible(false);
			sp[getNumSpriteIndex(pStr->cannonName)]->initWithFile("zb.png");
			sp[getNumSpriteIndex(pStr->cannonName)]->setPosition(size.width/2,size.height/2);

			auto ownCannon = UIM->showForm(Form_huodehuopao);
			auto ctrl2 = ownCannon->getControl(huodehuopao_control2);
			ctrl2->setScale(0.01f);
			auto scale1 = ScaleTo::create(0.2f,1.2f,1.2f);
			auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
			ctrl2->runAction(Sequence::createWithTwoActions(scale1,scale2));

			guiGame->cannon_name = pStr->cannonName;
		}
	}
	else
	{
		if (SELF->curCannonIndex != pStr->m_id)
		{
			SELF->curCannonIndex = pStr->m_id;

			SELF->getCannon()->initWithCannonType((CannonType)SELF->curCannonIndex);
			CannonRateInf *ratInf = GData->getCannonRateInf(SELF->curRateInfIndex);
			CannonInf *inf = GData->getCannonInf(SELF->curCannonIndex);
			SELF->getCannon()->setCannonRateInf(ratInf);
			SELF->getCannon()->setCannonInf(inf);
			SELF->getCannon()->cannonFireEffect();
			SELF->getCannon()->setLevelEffect();
			//sp[getNumSpriteIndex(pStr->cannonName)]->initWithFile("yzb.png");
		}
	}	
}

//control7
void genghuanpaotai_control7_Click(Node *node,Touch* ptouch, Event* event)//
{
	MControl *ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	String *pStr = (String *)ctrl->getParent()->getUserData();

	
// 	auto form = UIM->getForm(Form_huodehuopao);
// 	form->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT*1.5);
// 	auto nextMove = MoveTo::create(0.2f,Vec2(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT));
// 	form->runAction(nextMove);
}

//control10
void genghuanpaotai_control10_Click(Node *node,Touch* ptouch, Event* event)
{
	pIndex = 0;
	for (int i=0;i<5;i++)
	{
		sp[i]= NULL;
		np[i]=NULL;
	}
	UIM->closeForm(Form_genghuanpaotai,false);
	
}

