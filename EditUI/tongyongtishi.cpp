#include"UI.h"
void tongyongtishi_register(Node* node)
{
UIForm *form = (UIForm*)node;
  form->getControl(tongyongtishi_control4)->registerClickEvent(tongyongtishi_control4_Click);
}

void tongyongtishi_control3_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;

	auto label0 = LabelTTF::create(dialogTxt,"Arial",20,Size(400,150),cocos2d::TextHAlignment::CENTER);
	label0->setPosition(size.width/2,size.height/2+1 - 40);
	label0->setColor(Color3B(0,0,0));
	paintNode->addChild(label0);

	auto label1 = LabelTTF::create(dialogTxt,"Arial",20,Size(400,150),cocos2d::TextHAlignment::CENTER);
	label1->setPosition(size.width/2,size.height/2-1 - 40);
	label1->setColor(Color3B(0,0,0));
	paintNode->addChild(label1);

	auto label2 = LabelTTF::create(dialogTxt,"Arial",20,Size(400,150),cocos2d::TextHAlignment::CENTER);
	label2->setPosition(size.width/2-1,size.height/2 - 40);
	label2->setColor(Color3B(0,0,0));
	paintNode->addChild(label2);

	auto label3 = LabelTTF::create(dialogTxt,"Arial",20,Size(400,150),cocos2d::TextHAlignment::CENTER);
	label3->setPosition(size.width/2+1,size.height/2 - 40);
	label3->setColor(Color3B(0,0,0));
	paintNode->addChild(label3);

	auto label = LabelTTF::create(dialogTxt,"Arial",20,Size(400,150),cocos2d::TextHAlignment::CENTER);
	label->setPosition(size.width/2,size.height/2 - 40);
	paintNode->addChild(label);
}

void tongyongtishi_initialize(Node* node)
{
	auto form = UIM->getForm(Form_tongyongtishi);

	form->getControl(tongyongtishi_control3)->registerPaintEvent(tongyongtishi_control3_Paint);
}
//control2
//control4
void tongyongtishi_control4_Click(Node *node,Touch* ptouch, Event* event)
{
	dialogTxt = "";
	UIM->closeForm(Form_tongyongtishi,false);
}
