#include"UI.h"
#include "GUILayer.h"
void huodehuopao_register(Node* node)
{
  UIForm *form = (UIForm*)node;
  form->getControl(huodehuopao_control3)->registerClickEvent(huodehuopao_control3_Click);
}

void huodehuopao_control2_Paint(Node*node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	auto sp = Sprite::create("hdpt.png");
	sp->setPosition(size.width/2,size.height/2);
	paintNode->addChild(sp);

	auto rotation = RotateTo::create(2.0,720);
	//auto scaleUp = ScaleTo::create(2.0f,0.5f,0.5f);
	//auto scaleDn = ScaleTo::create(2.0f,1.0f,1.0f);
	//auto sequ = Sequence::createWithTwoActions(scaleUp,scaleDn);
	sp->runAction(RepeatForever::create(rotation));
}

void huodehuopao_control4_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	auto cannonArm = Armature::create(guiGame->cannon_name.c_str()); 

	cannonArm->setPosition(size.width/2,size.height/2-60);
	if (guiGame->cannon_name.compare("hxj")==0
		||guiGame->cannon_name.compare("bdp_dh")==0)
	{
		cannonArm->setPosition(size.width/2,size.height/2-30);
	}
	else if (guiGame->cannon_name.compare("jiguangp")==0)
	{
		cannonArm->setPosition(size.width/2,size.height/2-30);
		cannonArm->setScale(0.75f);
	}
	cannonArm->getAnimation()->play("DJ_show");
	paintNode->addChild(cannonArm);
}

void huodehuopao_initialize(Node* node)
{
	UIForm *form = (UIForm*)node;
	form->getControl(huodehuopao_control2)->registerPaintEvent(huodehuopao_control2_Paint);
	form->getControl(huodehuopao_control4)->registerPaintEvent(huodehuopao_control4_Paint);
}
//control3
void huodehuopao_control3_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->closeForm((short)Form_huodehuopao,true);
}
