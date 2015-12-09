#include"UI.h"
#include "GameLayer.h"
#include "GUILayer.h"
#include "GameManager.h"
#include "Player.h"
void gameend_register(Node* node)
{
  UIForm *form = (UIForm*)node;
  form->getControl(gameend_control4)->registerClickEvent(gameend_control4_Click);
  form->getControl(gameend_control5)->registerClickEvent(gameend_control5_Click);
}

void gameend_control3_Paint(Node*node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	auto downGold = Armature::create("gold");
	downGold->setPosition(size.width/2,size.height/2);
	downGold->getAnimation()->play("big_gold");
	paintNode->addChild(downGold);

	auto goldNum = NumSprite::create(gamelayer->getCheckGold(),GameNumberStoreLayerLevel);
	goldNum->setScale(0.7f);
	goldNum->setPosition(size.width/2,-size.height/4);
	paintNode->addChild(goldNum);

}
void gameend_control1_Paint(Node*node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	auto guanm = Sprite::create("guanquan.png");
	guanm->setPosition(size.width/2,size.height/2);
	guanm->runAction(RepeatForever::create(RotateBy::create(5.0f,1000)));

	paintNode->addChild(guanm);
}

void gameend_initialize(Node* node)
{
	UIForm *form = (UIForm*)node;
	form->getControl(gameend_control3)->registerPaintEvent(gameend_control3_Paint);
	form->getControl(gameend_control1)->registerPaintEvent(gameend_control1_Paint);

	//过关音效
	SMI->playSound("guoguan.mp3",false);
}
//control4
void gameend_control4_Click(Node *node,Touch* ptouch, Event* event)//下一关
{
	SELF->addGameCheck(1);
	GameLayer *layer = (GameLayer *)pRoom;
	layer->checkTask();

	/****************修改******************/
	auto renwu = UIM->showForm(Form_renwutankuang);
	auto ctrl1 = renwu->getControl(renwutankuang_control1);
	
	renwu->setEnabled(true);
	renwu->setScale(1.0f);
	ctrl1->setOpacity(125);
	renwu->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);
	
	auto ctrl2 = renwu->getControl(renwutankuang_control2);
	ctrl2->setScale(0.01f);
	auto scale1 = ScaleTo::create(0.2f,1.2f,1.2f);
	auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
	ctrl2->runAction(Sequence::createWithTwoActions(scale1,scale2));
	/****************修改******************/
	UIM->closeForm(Form_gameend,false);
}
//control5
void gameend_control5_Click(Node *node,Touch* ptouch, Event* event)//继续游戏
{
	UIM->closeForm(Form_gameend,false);

	auto form = UIM->getForm(Form_buyuchang);
	auto ctrl = form->getControl(buyuchang_control41);
	ctrl->setVisible(true);
	auto scale1 = ScaleTo::create(0.2f,1.2f,1.2f);
	auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
	ctrl->runAction(Sequence::createWithTwoActions(scale1,scale2));

	Node*paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();
	paintNode->removeAllChildren();

	auto shanArm = Armature::create("icon_2");
	shanArm->getAnimation()->play("jiesuo");
	shanArm->setPosition(size.width/2,size.height/2);
	shanArm->setScaleX(0.8f);
	shanArm->setScaleY(0.65f);
	paintNode->addChild(shanArm);

	std:string name = GMI->getString("UIText","text2");
	auto guoglabel = LabelTTF::create(name.c_str(),"Aril",20);
	guoglabel->setPosition(size.width/2,size.height/2);
	guoglabel->setColor(Color3B(0,0,0));
	paintNode->addChild(guoglabel,10);

	gamelayer->nextCheck = true;
}
//control6
// void gameend_control6_Click(Node *node,Touch* ptouch, Event* event)
// {
// 	UIM->closeForm(Form_gameend,false);
// }
