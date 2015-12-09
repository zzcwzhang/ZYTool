#include"UI.h"
#include "GScene.h"
#include "GameManager.h"
void duorenmoshixuanguan_register(Node* node)
{
UIForm *form = (UIForm*)node;
  form->getControl(duorenmoshixuanguan_control2)->registerClickEvent(duorenmoshixuanguan_control2_Click);
  form->getControl(duorenmoshixuanguan_control4)->registerClickEvent(duorenmoshixuanguan_control4_Click);
  form->getControl(duorenmoshixuanguan_control5)->registerClickEvent(duorenmoshixuanguan_control5_Click);
  form->getControl(duorenmoshixuanguan_control15)->registerClickEvent(duorenmoshixuanguan_control15_Click);
}

void duorenmoshixuanguan_control1_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	auto arm = Armature::create("lianjiduizhan");
	arm->getAnimation()->play("jbsc_dong");
	String *pString = String::create("jbsc_dong_chixu");
	pString->retain();
	arm->setUserData(pString);
	arm->getAnimation()->setMovementEventCallFunc(arm,movementEvent_selector(UICallBack::playNextArmature));
	arm->setPosition(size.width/2,size.height/2-20);
	paintNode->addChild(arm);
}

void duorenmoshixuanguan_control2_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	auto fishSprite = Sprite::create("online_fish0.png");
	fishSprite->setPosition(size.width/2,size.height/2 + 20);
	paintNode->addChild(fishSprite);
}

void duorenmoshixuanguan_control3_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	auto fishSprite = Sprite::create("online_fish1.png");
	fishSprite->setPosition(size.width/2,size.height/2 + 20);
	paintNode->addChild(fishSprite);
}

void duorenmoshixuanguan_control4_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	auto fishSprite = Sprite::create("online_fish2.png");
	fishSprite->setPosition(size.width/2,size.height/2 + 20);
	paintNode->addChild(fishSprite);
}

void duorenmoshixuanguan_control5_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	auto fishSprite = Sprite::create("online_fish3.png");
	fishSprite->setPosition(size.width/2,size.height/2 + 20);
	paintNode->addChild(fishSprite);
}

void duorenmoshixuanguan_initialize(Node* node)
{
	auto form = (UIForm*)node;
	form->getControl(duorenmoshixuanguan_control1)->registerPaintEvent(duorenmoshixuanguan_control1_Paint);
	form->getControl(duorenmoshixuanguan_control2)->registerPaintEvent(duorenmoshixuanguan_control2_Paint);
	form->getControl(duorenmoshixuanguan_control3)->registerPaintEvent(duorenmoshixuanguan_control3_Paint);
	form->getControl(duorenmoshixuanguan_control4)->registerPaintEvent(duorenmoshixuanguan_control4_Paint);
	form->getControl(duorenmoshixuanguan_control5)->registerPaintEvent(duorenmoshixuanguan_control5_Paint);
}
//control2
void duorenmoshixuanguan_control2_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->closeForm(Form_duorenmoshixuanguan,false);
	UIM->closeForm(Form_fengmian,false);
	pRunData->curRoomIndex = 1;
	GScene->setState(GST_OnLineGame);
	GMI->setSingleMode(false);
}
//control4
void duorenmoshixuanguan_control4_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->closeForm(Form_duorenmoshixuanguan,false);
	UIM->closeForm(Form_fengmian,false);
	pRunData->curRoomIndex = 2;
	GScene->setState(GST_OnLineGame);
	GMI->setSingleMode(false);
}
//control5
void duorenmoshixuanguan_control5_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->closeForm(Form_duorenmoshixuanguan,false);
	UIM->closeForm(Form_fengmian,false);
	pRunData->curRoomIndex = 3;
	GScene->setState(GST_OnLineGame);
	GMI->setSingleMode(false);
}

//control15
void duorenmoshixuanguan_control15_Click(Node *node,Touch* ptouch, Event* event)
{
	auto curForm = UIM->getForm(Form_duorenmoshixuanguan);
	auto nextForm = UIM->getForm(Form_fengmian);
	if (!nextForm || !nextForm->isActive())
	{
		nextForm = UIM->showForm(Form_fengmian);
	}
	nextForm->setEnabled(true);
	nextForm->setPosition(-SCREEN_WIDTH/2,SCREEN_HALF_HEIGHT);

	auto curMove = MoveTo::create(0.2f,Vec2(SCREEN_WIDTH * 1.5f,SCREEN_HALF_HEIGHT));
	
	curForm->runAction(curMove);

	auto nextMove = MoveTo::create(0.2f,Vec2(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT));
	
	nextForm->runAction(nextMove);
}
