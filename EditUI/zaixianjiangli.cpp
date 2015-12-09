#include"UI.h"
#include "GUILayer.h"
#include "GameLayer.h"
#include "GameDataManager.h"
#include "GScene.h"
#include "GameManager.h"
#include "Player.h"
//MControl* onLineGetButton;
NumSprite* jinq[7] = {NULL};
Sprite* yubi[7] = {NULL};
void zaixianjiangli_register(Node* node)
{
  UIForm *form1 = (UIForm*)node;
  form1->getControl(zaixianjiangli_control3)->registerClickEvent(zaixianjiangli_control3_Click);
  form1->getControl(zaixianjiangli_control11)->registerClickEvent(zaixianjiangli_control11_Click);
  form1->getControl(zaixianjiangli_control17)->registerClickEvent(zaixianjiangli_control17_Click);
}

void zaixianjiangli_control12_Paint(Node* node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	Label * onLineLabel_zaixian =(Label*) paintNode->getChildByTag(10);
	auto str = String::createWithFormat("%02d : %02d",gamelayer->getInLineMinter(),gamelayer->getInLineSecond());
	if(!onLineLabel_zaixian)
	{
		onLineLabel_zaixian = Label::createWithTTF(str->getCString(),"fonts/arial.ttf",24);
		onLineLabel_zaixian->setPosition(size.width/2,size.height/2);
		paintNode->addChild(onLineLabel_zaixian);
		onLineLabel_zaixian->setTag(10);
	}
	else
	{
		onLineLabel_zaixian->setString(str->getCString());
	}
	
}

void zaixianjiangli_control12_Update(Node*node,float dt)
{
	MControl* ctrl = (MControl*)node;
	ctrl->refresh();
	UIForm *form = UIM->getForm(Form_zaixianjiangli);
	if (gamelayer->getInLineMinter()==0 && gamelayer->getInLineSecond()==0)
	{
		form->getControl(zaixianjiangli_control13)->setVisible(false);
		form->getControl(zaixianjiangli_control11)->setVisible(true);
	}
	/****************DT??******************/
	else
	{
		form->getControl(zaixianjiangli_control13)->setVisible(true);
		form->getControl(zaixianjiangli_control11)->setVisible(false);
	}
	/****************DT??******************/
}

void zaixianjiangli_control4_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* piantNode = ctrl->getPaintNode();
	piantNode->removeAllChildren();
	auto sp=Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(500));
	sp->setPosition(size.width/2-20,size.height/2-50);
	sp->setScale(0.75f);
	piantNode->addChild(sp,0,100);

	auto worth = Sprite::create("worth.png");
	worth->setPosition(size.width/2+40,size.height/2-60);
	worth->setScale(0.8f);
	piantNode->addChild(worth,0,100);
}

void zaixianjiangli_control5_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* piantNode = ctrl->getPaintNode();
	piantNode->removeAllChildren();
	auto sp=Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(800));
	sp->setPosition(size.width/2-20,size.height/2-60);
	sp->setScale(0.75f);
	piantNode->addChild(sp);

	auto worth = Sprite::create("worth.png");
	worth->setPosition(size.width/2+40,size.height/2-70);
	worth->setScale(0.8f);
	piantNode->addChild(worth);
}

void zaixianjiangli_control6_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;

	Size size = ctrl->getSize();
	Node* piantNode = ctrl->getPaintNode();
	piantNode->removeAllChildren();
	auto sp=Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(1500));
	sp->setPosition(size.width/2-10,size.height/2-60);
	sp->setScale(0.75f);
	piantNode->addChild(sp);

	auto worth = Sprite::create("worth.png");
	worth->setPosition(size.width/2+60,size.height/2-70);
	worth->setScale(0.8f);
	piantNode->addChild(worth);
}

void zaixianjiangli_control7_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;

	Size size = ctrl->getSize();
	Node* piantNode = ctrl->getPaintNode();

	piantNode->removeAllChildren();
	auto sp=Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(2500));
	sp->setPosition(size.width/2-10,size.height/2-60);
	sp->setScale(0.75f);
	piantNode->addChild(sp);

	auto worth = Sprite::create("worth.png");
	worth->setPosition(size.width/2+60,size.height/2-70);
	worth->setScale(0.8f);
	piantNode->addChild(worth);
}

void zaixianjiangli_control8_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;

	Size size = ctrl->getSize();
	Node* piantNode = ctrl->getPaintNode();

	piantNode->removeAllChildren();
	auto sp=Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(5000));
	sp->setPosition(size.width/2-10,size.height/2-60);
	sp->setScale(0.75f);
	piantNode->addChild(sp);

	auto worth = Sprite::create("worth.png");
	worth->setPosition(size.width/2+60,size.height/2-70);
	worth->setScale(0.8f);
	piantNode->addChild(worth);
}

void zaixianjiangli_control9_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;

	Size size = ctrl->getSize();
	Node* piantNode = ctrl->getPaintNode();

	piantNode->removeAllChildren();
	auto sp=Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(10000));
	sp->setPosition(size.width/2-20,size.height/2-60);
	sp->setScale(0.75f);
	piantNode->addChild(sp);

	auto worth = Sprite::create("worth.png");
	worth->setPosition(size.width/2+60,size.height/2-70);
	worth->setScale(0.8f);
	piantNode->addChild(worth);
}

void zaixianjiangli_control10_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;

	Size size = ctrl->getSize();
	Node* piantNode = ctrl->getPaintNode();

	piantNode->removeAllChildren();
	auto sp=Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(20000));
	sp->setPosition(size.width/2-20,size.height/2-70);
	sp->setScale(0.75f);
	piantNode->addChild(sp);

	auto worth = Sprite::create("worth.png");
	worth->setPosition(size.width/2+60,size.height/2-80);
	worth->setScale(0.8f);
	piantNode->addChild(worth);
}

void zaixianjiangli_control16_Paint()
{
	UIForm *form = UIM->getForm(Form_zaixianjiangli);
	MControl *ctrl = form->getControl(zaixianjiangli_control16);
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	auto sp=Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(gamelayer->onlineCoin));
	sp->setPosition(size.width/2,size.height/2+10);
	sp->setScale(0.65f);
	paintNode->addChild(sp);
}

void zaixianjiangli_initialize(Node* node)
{
	UIForm *form = (UIForm*)node;
	form->getControl(zaixianjiangli_control12)->registerPaintEvent(zaixianjiangli_control12_Paint);//
	form->getControl(zaixianjiangli_control12)->registerUpdateLogicEvent(zaixianjiangli_control12_Update);

	form->getControl(zaixianjiangli_control4)->registerPaintEvent(zaixianjiangli_control4_Paint);
	form->getControl(zaixianjiangli_control5)->registerPaintEvent(zaixianjiangli_control5_Paint);
	form->getControl(zaixianjiangli_control6)->registerPaintEvent(zaixianjiangli_control6_Paint);
	form->getControl(zaixianjiangli_control7)->registerPaintEvent(zaixianjiangli_control7_Paint);
	form->getControl(zaixianjiangli_control8)->registerPaintEvent(zaixianjiangli_control8_Paint);
	form->getControl(zaixianjiangli_control9)->registerPaintEvent(zaixianjiangli_control9_Paint);
	form->getControl(zaixianjiangli_control10)->registerPaintEvent(zaixianjiangli_control10_Paint);

	for (int i = 0; i < 7; i++)
	{
		MControl *ctrl = form->getControl(zaixianjiangli_control4 + i);
		if(i < gamelayer->onlineRewardIndex)
		{
			UIM->setSkin(ctrl,1);
		}
		else
		{
			UIM->setSkin(ctrl,0);
		}
	}
}
//control3
void zaixianjiangli_control3_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->closeForm((short)Form_zaixianjiangli,true);
}
//control11
void zaixianjiangli_control11_Click(Node *node,Touch* ptouch, Event* event)
{
	MControl* onLineGetButton = (MControl*)node;
	UIForm *form = UIM->getForm(Form_zaixianjiangli);
	MControl* onLineGetButtonban = form->getControl(zaixianjiangli_control13);

	auto ctrl = form->getControl(zaixianjiangli_control14);
	
	ctrl->setVisible(true);
	ctrl->setScale(0.01f);
	ctrl->setPosition(370,200); /*DT??*/
	ctrl->runAction(ScaleTo::create(0.35f,1.0,1.0f));

	zaixianjiangli_control16_Paint();

	SELF->addGold(gamelayer->onlineCoin);

	auto downGold = Armature::create("gold");
	downGold->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);
	downGold->getAnimation()->play("big_gold");
	downGold->getAnimation()->setMovementEventCallFunc(downGold,movementEvent_selector(UICallBack::removeArmature));
	GScene->addChild(downGold,10000);

	UIM->setSkin(form->getControl(zaixianjiangli_control4 + gamelayer->onlineRewardIndex),1);
	gamelayer->setInLineTime(gamelayer->onlineRewardIndex + 1);
	if(gamelayer->onlineRewardIndex < 7)
	{
		form->getControl(zaixianjiangli_control13)->setVisible(true);
		form->getControl(zaixianjiangli_control11)->setVisible(false);
	}
	else
	{
		form->getControl(zaixianjiangli_control13)->setVisible(false);
		form->getControl(zaixianjiangli_control11)->setVisible(false);

		UIForm *form = UIM->getForm(Form_buyuchang);
		form->getControl(buyuchang_control34)->setVisible(false);
	}
}

//control17
void zaixianjiangli_control17_Click(Node *node,Touch* ptouch, Event* event)
{
	auto form = UIM->getForm(Form_zaixianjiangli);
	auto ctrl = form->getControl(zaixianjiangli_control14);
	
	//ctrl->setPosition(410,-310);
	auto scale = ScaleTo::create(0.35f,0.01f,0.01f);
	auto callfunc = CallFunc::create(ctrl,callfunc_selector(UICallBack::onlineRewardCallback));
	ctrl->runAction(Sequence::createWithTwoActions(scale,callfunc));
}