#include"UI.h"
#include "GameManager.h"
#include "Player.h"
#include "Room.h"
#include "Cannon.h"
void duorenbuyuchang_register(Node* node)
{
UIForm *form = (UIForm*)node;
form->getControl(duorenbuyuchang_control7)->registerClickEvent(duorenbuyuchang_control7_Click);
form->getControl(duorenbuyuchang_control8)->registerClickEvent(duorenbuyuchang_control8_Click);
form->getControl(duorenbuyuchang_control9)->registerClickEvent(duorenbuyuchang_control9_Click);
form->getControl(duorenbuyuchang_control10)->registerClickEvent(duorenbuyuchang_control10_Click);
form->getControl(duorenbuyuchang_control12)->registerClickEvent(duorenbuyuchang_control12_Click);
form->getControl(duorenbuyuchang_control16)->registerClickEvent(duorenbuyuchang_control16_Click);
form->getControl(duorenbuyuchang_control17)->registerClickEvent(duorenbuyuchang_control17_Click);
form->getControl(duorenbuyuchang_control26)->registerClickEvent(duorenbuyuchang_control26_Click);
form->getControl(duorenbuyuchang_control42)->registerClickEvent(duorenbuyuchang_control42_Click);
form->getControl(duorenbuyuchang_control43)->registerClickEvent(duorenbuyuchang_control43_Click);
form->getControl(duorenbuyuchang_control44)->registerClickEvent(duorenbuyuchang_control44_Click);
form->getControl(duorenbuyuchang_control50)->registerClickEvent(duorenbuyuchang_control50_Click);
form->getControl(duorenbuyuchang_control51)->registerClickEvent(duorenbuyuchang_control51_Click);
form->getControl(duorenbuyuchang_control55)->registerClickEvent(duorenbuyuchang_control55_Click);
form->getControl(duorenbuyuchang_control60)->registerClickEvent(duorenbuyuchang_control60_Click);
form->getControl(duorenbuyuchang_control61)->registerClickEvent(duorenbuyuchang_control61_Click);
form->getControl(duorenbuyuchang_control62)->registerClickEvent(duorenbuyuchang_control62_Click);
form->getControl(duorenbuyuchang_control65)->registerClickEvent(duorenbuyuchang_control65_Click);
form->getControl(duorenbuyuchang_control66)->registerClickEvent(duorenbuyuchang_control66_Click);
}

void aiCoin_Paint(Node *node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	Player *player = (Player*)ctrl->getParent()->getUserData();
	if(!player)
	{
		paintNode->removeAllChildren();
		return;
	}
	Label *GoldNum =(Label*) paintNode->getChildByTag(10);
	if(!GoldNum)
	{
		int gold = player->getGold();
		GoldNum = Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(gold));
		GoldNum->setPosition(size.width/2,size.height/2 + 5);
		paintNode->addChild(GoldNum);	
		GoldNum->setScale(0.45f);
		GoldNum->setTag(10);
	}
	else
	{
		int gold = player->getGold();
		GoldNum->setString(ConvertToString(gold));
	}
}

void playerCoin_Paint(Node *node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	Label *GoldNum =(Label*) paintNode->getChildByTag(10);
	Player *player = SELF;
	if(!GoldNum)
	{
		int gold = player->getGold();
		GoldNum = Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(gold));
		GoldNum->setPosition(size.width/2,size.height/2 + 5);
		paintNode->addChild(GoldNum);	
		GoldNum->setScale(0.45f);
		GoldNum->setTag(10);
	}
	else
	{
		int gold = player->getGold();
		GoldNum->setString(ConvertToString(gold));
	}
}

void playerCannon_Paint(Node *node)
{
	auto ctrl = (MControl*)node; 
	auto paintNode = ctrl->getPaintNode(); 
	auto size = ctrl->getSize(); 
	paintNode->removeAllChildren();

	Player *player = SELF;
	paintNode->addChild(player->getCannon());
	player->getCannon()->setPosition(Vec2(size.width/2,size.height/2));
	/*if(ctrl->id == duorenbuyuchang_control58 || ctrl->id == duorenbuyuchang_control52)
	{
		player->getCannon()->setRotation(180);
	}
	else
	{
		player->getCannon()->setRotation(0);
	}*/
}

void aiCannon_Paint(Node *node)
{
	auto ctrl = (MControl*)node; 
	auto paintNode = ctrl->getPaintNode(); 
	auto size = ctrl->getSize(); 
	paintNode->removeAllChildren();
	Player *player = (Player*)ctrl->getParent()->getUserData();
	if(!player)
	{
		return;
	}

	paintNode->addChild(player->getCannon());
	player->getCannon()->setPosition(Vec2(size.width/2,size.height/2));
	/*if(ctrl->id == duorenbuyuchang_control21 || ctrl->id == duorenbuyuchang_control20)
	{
		player->getCannon()->setRotation(180);
	}
	else
	{
		player->getCannon()->setRotation(0);
	}*/
}

void aiCannonRate_Paint(Node *node)
{
	auto ctrl = (MControl*)node; 
	auto paintNode = ctrl->getPaintNode(); 
	auto size = ctrl->getSize(); 
	paintNode->removeAllChildren();

	Player *player = (Player*)ctrl->getParent()->getUserData();
	if(!player)
	{
		return;
	}

	int dynameter = player->getCannon()->getCannonRateInf()->consume;
	Label* np = Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(dynameter));
	np->setPosition(size.width/2-5,size.height/2-5);
	paintNode->addChild(np);
	if (dynameter<100)
	{
		np->setScale(0.8f);
	}
	else if (dynameter<1000)
	{
		np->setScale(0.6f);
	}
	else if (dynameter<10000)
	{
		np->setScale(0.4f);
	}
	else
	{
		np->setScale(0.4f);
	}
}

void playerCannonRate_Paint(Node *node)
{
	auto ctrl = (MControl*)node; 
	auto paintNode = ctrl->getPaintNode(); 
	auto size = ctrl->getSize(); 
	paintNode->removeAllChildren();

	int dynameter = SELF->getCannon()->getCannonRateInf()->consume;
	Label* np = Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(dynameter));
	np->setPosition(size.width/2-5,size.height/2-5);
	paintNode->addChild(np);
	if (dynameter<100)
	{
		np->setScale(0.8f);
	}
	else if (dynameter<1000)
	{
		np->setScale(0.6f);
	}
	else if (dynameter<10000)
	{
		np->setScale(0.4f);
	}
	else
	{
		np->setScale(0.4f);
	}
}

void duorenbuyuchang_control65_Paint(Node *node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	paintNode->removeAllChildren();

	auto autoCannon = Armature::create("icon_6");
	autoCannon->setPosition(size.width/2,size.height/2);
	autoCannon->getAnimation()->play("zidong");
	paintNode->addChild(autoCannon);
}

void duorenbuyuchang_control66_Paint(Node *node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	auto changeCannon = Armature::create("icon_6");
	changeCannon->setPosition(size.width/2,size.height/2);
	changeCannon->getAnimation()->play("huanpao");
	paintNode->addChild(changeCannon);
}

void duorenbuyuchang_control29_Paint(Node *node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	int num = SELF->getPlayGrade();
	Label *label = (Label*)paintNode->getChildByTag(10);
	if(label)
	{
		label->setString(ConvertToString(num));
	}
	else
	{
		label = Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(num));
		paintNode->addChild(label);
		label->setPosition(Vec2(-25,size.height/2 + 7));
		label->setTag(10);
		label->setScale(0.6f);
	}

	UIM->setSkin(ctrl,SELF->getPlayRank());
}

void duorenbuyuchang_control30_Paint(Node *node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	int lv = SELF->getPlayGrade();
	GradeInf *inf = GData->getGradeInf(lv - 1);
	int score = SELF->getScore();
	int W = 101;
	int H = 12;
	float realW = score * W/inf->upScore;
	Sprite *sp = (Sprite*)paintNode->getChildByTag(10);
	if(sp)
	{
		sp->setTextureRect(Rect(0,0,realW,H));
	}
	else
	{
		sp = Sprite::create("grade_pro1.png");
		paintNode->addChild(sp);
		sp->setAnchorPoint(Vec2::ZERO);
		sp->setPosition(Vec2(0,3));
		sp->setTag(10);
		sp->setTextureRect(Rect(0,0,realW,H));
	}
}

void duorenbuyuchang_control30_Update(Node *node, float dt)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	ctrl->refresh();
}

void duorenbuyuchang_control31_Paint(Node *node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	int num = SELF->getLottery();
	Label *label = (Label*)paintNode->getChildByTag(10);
	if(label)
	{
		label->setString(ConvertToString(num));
	}
	else
	{
		label = Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(num));
		paintNode->addChild(label);
		label->setPosition(Vec2(size.width/2,size.height/2));
		label->setTag(10);
		label->setScale(0.6f);
	}
}

void Icon_Paint(Node *node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();
	Player *player = (Player*)ctrl->getParent()->getUserData();
	if(!player)
	{
		return;
	}
	char name[64];
	memset(name,0,sizeof(name));
	sprintf(name,"touxiang_%d.png",player->iconId);
	Sprite *sp = Sprite::create(name);
	paintNode->addChild(sp);
	sp->setPosition(Vec2(size.width/2,size.height/2));
}

void duorenbuyuchang_update(Node *node,float dt)
{
	UIForm *form = (UIForm*)node;
	form->getControl(duorenbuyuchang_control45)->refresh();
	form->getControl(duorenbuyuchang_control11)->refresh();
	form->getControl(duorenbuyuchang_control63)->refresh();
	form->getControl(duorenbuyuchang_control54)->refresh();

	form->getControl(duorenbuyuchang_control13)->refresh();
	form->getControl(duorenbuyuchang_control37)->refresh();
	form->getControl(duorenbuyuchang_control14)->refresh();
	form->getControl(duorenbuyuchang_control15)->refresh();
}

void refreshPlayerRate()
{
	UIForm *form = UIM->getForm(Form_duorenbuyuchang);
	form->getControl(duorenbuyuchang_control46)->refresh();
	form->getControl(duorenbuyuchang_control22)->refresh();
	form->getControl(duorenbuyuchang_control59)->refresh();
	form->getControl(duorenbuyuchang_control53)->refresh();
}

void duorenbuyuchang_initialize(Node* node)
{
	UIForm *form = (UIForm*)node;
	int playerIds[4] = {duorenbuyuchang_control41,duorenbuyuchang_control2,duorenbuyuchang_control49,duorenbuyuchang_control57};
	int aiIds[4] = {duorenbuyuchang_control3,duorenbuyuchang_control36,duorenbuyuchang_control5,duorenbuyuchang_control4};
	
	for (int i = 0; i <4 ;i++)
	{
		form->getControl(aiIds[i])->setVisible(false);
		form->getControl(playerIds[i])->setVisible(false);
	}
	form->setUpdateEvent(duorenbuyuchang_update);

	form->getControl(duorenbuyuchang_control65)->registerPaintEvent(duorenbuyuchang_control65_Paint);
	form->getControl(duorenbuyuchang_control66)->registerPaintEvent(duorenbuyuchang_control66_Paint);
	form->getControl(duorenbuyuchang_control29)->registerPaintEvent(duorenbuyuchang_control29_Paint);
	form->getControl(duorenbuyuchang_control30)->registerPaintEvent(duorenbuyuchang_control30_Paint);
	form->getControl(duorenbuyuchang_control30)->registerUpdateLogicEvent(duorenbuyuchang_control30_Update);
	form->getControl(duorenbuyuchang_control31)->registerPaintEvent(duorenbuyuchang_control31_Paint);

	form->getControl(duorenbuyuchang_control47)->registerPaintEvent(playerCannon_Paint);
	form->getControl(duorenbuyuchang_control18)->registerPaintEvent(playerCannon_Paint);
	form->getControl(duorenbuyuchang_control58)->registerPaintEvent(playerCannon_Paint);
	form->getControl(duorenbuyuchang_control52)->registerPaintEvent(playerCannon_Paint);

	form->getControl(duorenbuyuchang_control46)->registerPaintEvent(playerCannonRate_Paint);
	form->getControl(duorenbuyuchang_control22)->registerPaintEvent(playerCannonRate_Paint);
	form->getControl(duorenbuyuchang_control59)->registerPaintEvent(playerCannonRate_Paint);
	form->getControl(duorenbuyuchang_control53)->registerPaintEvent(playerCannonRate_Paint);

	form->getControl(duorenbuyuchang_control23)->registerPaintEvent(aiCannonRate_Paint);
	form->getControl(duorenbuyuchang_control38)->registerPaintEvent(aiCannonRate_Paint);
	form->getControl(duorenbuyuchang_control25)->registerPaintEvent(aiCannonRate_Paint);
	form->getControl(duorenbuyuchang_control24)->registerPaintEvent(aiCannonRate_Paint);

	form->getControl(duorenbuyuchang_control21)->registerPaintEvent(aiCannon_Paint);
	form->getControl(duorenbuyuchang_control20)->registerPaintEvent(aiCannon_Paint);
	form->getControl(duorenbuyuchang_control19)->registerPaintEvent(aiCannon_Paint);
	form->getControl(duorenbuyuchang_control39)->registerPaintEvent(aiCannon_Paint);

	form->getControl(duorenbuyuchang_control45)->registerPaintEvent(playerCoin_Paint);
	form->getControl(duorenbuyuchang_control11)->registerPaintEvent(playerCoin_Paint);
	form->getControl(duorenbuyuchang_control63)->registerPaintEvent(playerCoin_Paint);
	form->getControl(duorenbuyuchang_control54)->registerPaintEvent(playerCoin_Paint);

	form->getControl(duorenbuyuchang_control13)->registerPaintEvent(aiCoin_Paint);
	form->getControl(duorenbuyuchang_control37)->registerPaintEvent(aiCoin_Paint);
	form->getControl(duorenbuyuchang_control14)->registerPaintEvent(aiCoin_Paint);
	form->getControl(duorenbuyuchang_control15)->registerPaintEvent(aiCoin_Paint);

	form->getControl(duorenbuyuchang_control48)->registerPaintEvent(Icon_Paint);
	form->getControl(duorenbuyuchang_control32)->registerPaintEvent(Icon_Paint);
	form->getControl(duorenbuyuchang_control56)->registerPaintEvent(Icon_Paint);
	form->getControl(duorenbuyuchang_control64)->registerPaintEvent(Icon_Paint);
	form->getControl(duorenbuyuchang_control33)->registerPaintEvent(Icon_Paint);
	form->getControl(duorenbuyuchang_control40)->registerPaintEvent(Icon_Paint);
	form->getControl(duorenbuyuchang_control34)->registerPaintEvent(Icon_Paint);
	form->getControl(duorenbuyuchang_control35)->registerPaintEvent(Icon_Paint);
}
//control7
void duorenbuyuchang_control7_Click(Node *node,Touch* ptouch, Event* event){}
//control8
void duorenbuyuchang_control8_Click(Node *node,Touch* ptouch, Event* event){}
//control9
void duorenbuyuchang_control9_Click(Node *node,Touch* ptouch, Event* event){}
//control10
void duorenbuyuchang_control10_Click(Node *node,Touch* ptouch, Event* event){}
//control12
void duorenbuyuchang_control12_Click(Node *node,Touch* ptouch, Event* event){}
//control16
void duorenbuyuchang_control16_Click(Node *node,Touch* ptouch, Event* event)
{
	duorenbuyuchang_control42_Click(node,ptouch,event);
}
//control17
void duorenbuyuchang_control17_Click(Node *node,Touch* ptouch, Event* event)
{
	duorenbuyuchang_control43_Click(node,ptouch,event);
}
//control26
void duorenbuyuchang_control26_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->showForm(Form_canrentuichu);
}
//control42
void duorenbuyuchang_control42_Click(Node *node,Touch* ptouch, Event* event)
{
	if(SELF->curRateInfIndex==0) return ;
	SELF->curRateInfIndex--;
	CannonRateInf *inf = GData->getCannonRateInf(SELF->curRateInfIndex);
	SELF->getCannon()->setCannonRateInf(inf);
	SELF->getCannon()->setLevelEffect();
	refreshPlayerRate();
}
//control43
void duorenbuyuchang_control43_Click(Node *node,Touch* ptouch, Event* event)
{
	if(SELF->curRateInfIndex==23) return ;
	SELF->curRateInfIndex++;
	CannonRateInf *inf = GData->getCannonRateInf(SELF->curRateInfIndex);
	SELF->getCannon()->setCannonRateInf(inf);
	SELF->getCannon()->setLevelEffect();
	refreshPlayerRate();
}
//control44
void duorenbuyuchang_control44_Click(Node *node,Touch* ptouch, Event* event)
{

}
//control50
void duorenbuyuchang_control50_Click(Node *node,Touch* ptouch, Event* event)
{
	duorenbuyuchang_control42_Click(node,ptouch,event);
}
//control51
void duorenbuyuchang_control51_Click(Node *node,Touch* ptouch, Event* event)
{
	duorenbuyuchang_control43_Click(node,ptouch,event);
}
//control55
void duorenbuyuchang_control55_Click(Node *node,Touch* ptouch, Event* event)
{

}
//control60
void duorenbuyuchang_control60_Click(Node *node,Touch* ptouch, Event* event)
{
	duorenbuyuchang_control42_Click(node,ptouch,event);
}
//control61
void duorenbuyuchang_control61_Click(Node *node,Touch* ptouch, Event* event)
{
	duorenbuyuchang_control43_Click(node,ptouch,event);
}

//control62
void duorenbuyuchang_control62_Click(Node *node,Touch* ptouch, Event* event){}

//control65
void duorenbuyuchang_control65_Click(Node *node,Touch* ptouch, Event* event)
{
	log("fapao");
	bool isAuto = SELF->getCannon()->getAutoFire();
	if (isAuto)
	{
		SELF->getCannon()->setAutoFire(false);
		SELF->getCannon()->setBanClick(false);
	}
	else
	{
		SELF->getCannon()->setAutoFire(true);
		SELF->getCannon()->setBanClick(true);
	}

	auto fireCtrl = (MControl*)node;
	fireCtrl->stopAllActions();
	fireCtrl->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	fireCtrl->runAction(Sequence::create(cAction1,cAction2,nullptr));
}
//control66
void duorenbuyuchang_control66_Click(Node *node,Touch* ptouch, Event* event)
{
	log("huanpao");
	auto changeCtrl = (MControl*)node;
	changeCtrl->stopAllActions();
	changeCtrl->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	changeCtrl->runAction(Sequence::create(cAction1,cAction2,nullptr));

	auto chang = UIM->showForm(Form_genghuanpaotai);
	chang->setScale(0.01f);
	auto scale1 = ScaleTo::create(0.25f,1.2f,1.2f);
	auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
	chang->runAction(Sequence::createWithTwoActions(scale1,scale2));
}