#include"UI.h"
#include "GUILayer.h"
#include "Fish.h"
#include "Helper.h"
#include "GameLayer.h"
#include "GameManager.h"
void renwutankuang_register(Node* node)
{
  UIForm *form = (UIForm*)node;
  form->getControl(renwutankuang_control5)->registerClickEvent(renwutankuang_control5_Click);
}


void renwutankuang_control3_Paint(Node * node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	paintNode->removeAllChildren();

	GameLayer *layer = (GameLayer*)GMI->getRoom();
	Fish* taskFish = Fish::createFishshadow((Fish::FishType)layer->getTaskfishType());
	taskFish->setPosition(Vec2(260,95));
	taskFish->setColor(Color3B(255,255,255));
	taskFish->setOpacity(255);
	taskFish->setRotation(90);
	paintNode->addChild(taskFish);

	String* str = String::createWithFormat("X %d",layer->getTaskfishNum());
	Label* lt = Label::createWithSystemFont("X","fonts/arial.ttf",24);
	lt->setPosition(Vec2(360,95));
	lt->setColor(Color3B(125,255,125));
	paintNode->addChild(lt);
	int taskFishNum = layer->getTaskfishNum();
	NumSprite* np = NumSprite::create(taskFishNum,GameNumberStoreLayerLevel);
	np->setPosition(Vec2(400,95));
	np->setScale(0.55f);
	paintNode->addChild(np);

}

void renwutankuang_control4_Paint(Node* node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	paintNode->removeAllChildren();
	GameLayer *layer = (GameLayer*)GMI->getRoom();

	NumSprite* np = NumSprite::create(layer->getCheckGold(),GameNumberGameLayerGold);
	np->setPosition(size.width/2,size.height/2);
	np->setScale(0.55f);
	paintNode->addChild(np);
}

void renwutankuang_initialize(Node* node)
{
	UIForm *form = (UIForm*)node;
	form->getControl(renwutankuang_control3)->registerPaintEvent(renwutankuang_control3_Paint);
	form->getControl(renwutankuang_control4)->registerPaintEvent(renwutankuang_control4_Paint);
}

//control5
void renwutankuang_control5_Click(Node *node,Touch* ptouch, Event* event)
{
	GameLayer *layer = (GameLayer*)pRoom;
	layer->removeTaskScene();
}
