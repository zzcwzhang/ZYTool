#include"UI.h"
#include "GUILayer.h"
#include "Cannon.h"
#include "GameLayer.h"
#include "Helper.h"
#include "cocos2d.h"
#include "GScene.h"
#include "GameManager.h"
#include "Player.h"
#include "Room.h"
#include "SMSInfo.h"
#include "SMSCallBack.h"
//#include "MissileTouch.h"
//int cannonExpend[24] = {1   ,5   ,10  ,20  ,50  ,100 ,200 ,300 ,
//						400 ,500 ,600 ,700 ,800 ,900 ,1000,2000 ,
//						3000,4000,5000,6000,7000,8000,9000,10000};
short buyuchang_shezhi_tabType = 0;//展开，缩进

bool chongzhiTask = false;
bool fireMisison = false;
bool fireLaser = false;
bool buyuchang_control28Lock = false;
void buyuchang_register(Node* node)
{
  UIForm *form = (UIForm*)node;
  form->getControl(buyuchang_control3)->registerClickEvent(buyuchang_control3_Click);
  form->getControl(buyuchang_control4)->registerClickEvent(buyuchang_control4_Click);
  form->getControl(buyuchang_control11)->registerClickEvent(buyuchang_control11_Click);
  form->getControl(buyuchang_control13)->registerClickEvent(buyuchang_control13_Click);
  form->getControl(buyuchang_control14)->registerClickEvent(buyuchang_control14_Click);
  form->getControl(buyuchang_control15)->registerClickEvent(buyuchang_control15_Click);
  form->getControl(buyuchang_control16)->registerClickEvent(buyuchang_control16_Click);
  form->getControl(buyuchang_control17)->registerClickEvent(buyuchang_control17_Click);
  form->getControl(buyuchang_control21)->registerClickEvent(buyuchang_control21_Click);
  form->getControl(buyuchang_control28)->registerClickEvent(buyuchang_control28_Click);
  form->getControl(buyuchang_control29)->registerClickEvent(buyuchang_control29_Click);
  form->getControl(buyuchang_control30)->registerClickEvent(buyuchang_control30_Click);
  form->getControl(buyuchang_control31)->registerClickEvent(buyuchang_control31_Click);
  form->getControl(buyuchang_control32)->registerClickEvent(buyuchang_control32_Click);
  form->getControl(buyuchang_control33)->registerClickEvent(buyuchang_control33_Click);
  form->getControl(buyuchang_control34)->registerClickEvent(buyuchang_control34_Click);
  form->getControl(buyuchang_control35)->registerClickEvent(buyuchang_control35_Click);
  form->getControl(buyuchang_control36)->registerClickEvent(buyuchang_control36_Click);
  //form->getControl(buyuchang_control40)->registerClickEvent(buyuchang_control40_Click);
  form->getControl(buyuchang_control41)->registerClickEvent(buyuchang_control41_Click);
  form->getControl(buyuchang_control43)->registerClickEvent(buyuchang_control43_Click);
}


void buyuchang_control7_Paint(Node *node)
{
	MControl *ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node *paintNode = ctrl->getPaintNode();

	if(!paintNode->getChildByTag(7))
	{
		SELF->getCannon()->setPosition(size.width/2,size.height/2);
		paintNode->addChild(SELF->getCannon(),0,7);
	}
}
void buyuchang_control7_Update(Node *node,float dt)
{
	MControl *ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node *paintNode = ctrl->getPaintNode();
	auto form = UIM->getForm(Form_buyuchang);
	if (fireMisison)
	{
		fireMisison =false;

		auto rota = RotateTo::create(0.2f,0);
		auto m_by1 = MoveBy::create(0.2f,Vec2(0,20));
		auto m_by2 = MoveBy::create(0.3f,Vec2(0,-200));

		Armature *arm = Armature::create("daoju");
		paintNode->addChild(arm);
		arm->setPosition(size.width/2,size.height/2);
		SELF->getCannon()->specialArm = arm;

		auto func = CallFunc::create(form,callfunc_selector(UICallBack::setMisssionAppear));
		SELF->getCannon()->runAction(Sequence::create(rota,m_by1,m_by2,func,nullptr));
	}

	if (fireLaser)
	{
		fireLaser = false;
		auto rota = RotateTo::create(0.2f,0);
		auto m_by1 = MoveBy::create(0.2f,Vec2(0,20));
		auto m_by2 = MoveBy::create(0.3f,Vec2(0,-200));

		SELF->getCannon()->setFireType(Cannon::Laser);
		Armature *arm = Armature::create("daoju");
		paintNode->addChild(arm);
		arm->setPosition(size.width/2,size.height/2);
		SELF->getCannon()->specialArm = arm;
		auto func = CallFunc::create(form,callfunc_selector(UICallBack::setLaserAppear));
		SELF->getCannon()->runAction(Sequence::create(rota,m_by1,m_by2,func,nullptr));
	}

	form->getControl(buyuchang_control7)->registerUpdateLogicEvent(nullptr);
}

void buyuchang_control23_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node *paintNode = ctrl->getPaintNode();

	int lv = SELF->getPlayGrade();
	GradeInf *inf = GData->getGradeInf(lv - 1);
	int score = SELF->getScore();
	int W = 159;
	int H = 19;
	float realW = score * W/inf->upScore;
	Sprite *sp = (Sprite*)paintNode->getChildByTag(10);
	if(sp)
	{
		sp->setTextureRect(Rect(0,0,realW,H));
	}
	else
	{
		sp = Sprite::create("grade_pro.png");
		paintNode->addChild(sp);
		sp->setAnchorPoint(Vec2::ZERO);
		sp->setPosition(Vec2(-6,-1));
		sp->setTag(10);
		sp->setTextureRect(Rect(0,0,realW,H));
	}
}

void buyuchang_control24_Paint(Node* node)
{
	int Level = SELF->getPlayGrade();
	MControl *ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node *paintNode = ctrl->getPaintNode();
	Label *np = (Label*)paintNode->getChildByTag(10);
	if(!np)
	{
		np = Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(Level));
		np->setPosition(size.width/2,size.height/2);
		paintNode->addChild(np);
		np->setTag(10);
	}
	else
	{
		np->setString(ConvertToString(Level));
	}
}

void buyuchang_control6_Paint(Node* node)
{
	int rank =SELF->getPlayRank();
	//int prerank = gamelayer->getPreRank();

	MControl *ctrl = (MControl*)node;

	//if (rank>prerank)
	{
		UIM->setSkin(ctrl,rank);
		//gamelayer->setPreRank(rank);
	}
}

//NumSprite* GoldNum;
void buyuchang_control10_Paint(Node* node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	Label *GoldNum =(Label*) paintNode->getChildByTag(10);
	if(!GoldNum)
	{
		int gold = SELF->getGold();
		GoldNum = Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(gold));
		GoldNum->setPosition(size.width/2,size.height/2+5);
		paintNode->addChild(GoldNum);	
		GoldNum->setScale(0.45f);
		GoldNum->setTag(10);
	}
	else
	{
		int gold = SELF->getGold();
		GoldNum->setString(ConvertToString(gold));
	}
}

void buyuchang_control10_Update(Node*node,float dt)
{
	MControl* ctrl = (MControl*)node;
	ctrl->refresh();
}

void buyuchang_control38_Paint(Node* node)
{
	int dynameter = SELF->getCannon()->getCannonRateInf()->consume;
	int predynameter = SELF->getCannon()->getpreConsume();

	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	paintNode->removeAllChildren();

	Label* np = Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(dynameter));
	np->setPosition(size.width/2-5,size.height/2+5);
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
		np->setPosition(size.width/2-5,size.height/2-5);
	}
	SELF->getCannon()->setpreConsume(dynameter);
}


void buyuchang_control35_Paint(Node* node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	paintNode->removeAllChildren();

	auto autoCannon = Armature::create("icon_6");
	autoCannon->setPosition(size.width/2,size.height/2);
	autoCannon->getAnimation()->play("zidong");
	paintNode->addChild(autoCannon);

// 	if (!paintNode->getChildByTag(35))
// 	{
// 		auto doCannon = Armature::create("icon_6");
// 		doCannon->setPosition(size.width/2,size.height/2);
// 		doCannon->getAnimation()->play("zidong");
// 		paintNode->addChild(doCannon,0,35);
// 	}
}

void buyuchang_control36_Paint(Node * node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	paintNode->removeAllChildren();

	auto changeCannon = Armature::create("icon_6");
	changeCannon->setPosition(size.width/2,size.height/2);
	changeCannon->getAnimation()->play("huanpao");
	paintNode->addChild(changeCannon);

// 	if (!paintNode->getChildByTag(36))
// 	{
// 		auto doCannon = Armature::create("icon_6");
// 		doCannon->setPosition(size.width/2,size.height/2);
// 		doCannon->getAnimation()->play("Animation1");
// 		paintNode->addChild(doCannon,0,36);
// 	}
}

void buyuchang_control33_Paint(Node* node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	paintNode->removeAllChildren();

	auto GoldStore = Armature::create("icon_4");
	GoldStore->setPosition(size.width/2,size.height/2-25);
	GoldStore->getAnimation()->play("jinbishangcheng");
	paintNode->addChild(GoldStore);

// 	if (!paintNode->getChildByTag(33))
// 	{
// 		auto doCannon = Armature::create("icon_4");
// 		doCannon->setPosition(size.width/2,size.height/2-25);
// 		doCannon->getAnimation()->play("jinbishangcheng");
// 		paintNode->addChild(doCannon,0,33);
// 	}
}
//Label* onLineLabel_buyu;
void buyuchang_control34_Paint(Node* node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	paintNode->removeAllChildren();

	auto onLineBGView = Armature::create("icon_4");
	onLineBGView->setPosition(size.width/2,size.height/2-15);
	onLineBGView->getAnimation()->play("lihe");
	paintNode->addChild(onLineBGView);

	//在线时间
	auto str = String::createWithFormat("%02d : %02d",gamelayer->getInLineMinter(),gamelayer->getInLineSecond());
	Label* onLineLabel_buyu = Label::createWithSystemFont(str->getCString(),"fonts/arial.ttf",24);
	onLineLabel_buyu->setPosition(size.width/2,size.height/2-15);
	paintNode->addChild(onLineLabel_buyu,1);
	onLineLabel_buyu->setTag(99);

}
bool actionTri = true;
void buyuchang_control34_Update(Node* node,float dt)
{
	MControl *ctrl = (MControl*)node;
	Label* onLineLabel_buyu = (Label*)ctrl->getPaintNode()->getChildByTag(99);
	if (onLineLabel_buyu)
	{
		auto str = String::createWithFormat("%02d : %02d",gamelayer->getInLineMinter(),gamelayer->getInLineSecond());
		if (gamelayer->getInLineMinter()==0 && gamelayer->getInLineSecond()==0)
		{
			onLineLabel_buyu->setString(GMI->getString("UIText","text6"));
			if (actionTri)
			{
				ScaleTo *scaletoBig = ScaleTo::create(0.5,1.2);
				ScaleTo *scaletoSmall = ScaleTo::create(0.5,0.8);
				Sequence* sequence = Sequence::createWithTwoActions(scaletoBig,scaletoSmall);
				onLineLabel_buyu->runAction(Repeat::create(sequence,-1));
				actionTri = false;
			}
		}
		else
		{
			onLineLabel_buyu->setString(str->getCString());
			onLineLabel_buyu->stopAllActions();
			actionTri = true; 
		}
	}
}

void buyuchang_control12_Paint(Node*node)
{
	MControl* ctrl = (MControl*)node;
	
}

void buyuchang_control28_Paint(Node*node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	paintNode->removeAllChildren();

	auto dingp = Armature::create("icon_6");
	dingp->getAnimation()->play("dingping");
	dingp->setPosition(size.width/2,size.height/2);
	paintNode->addChild(dingp);

	Sprite *sp = Sprite::create("youxiang_biaoqian.png");
	paintNode->addChild(sp);
	sp->setPosition(Vec2(size.width - 10, size.height - 15));
	
	int count = SELF->getVariable(FixedItem);
	Label *label = Label::createWithBMFont("fonts/num_prop.fnt",ConvertToString(count));
	paintNode->addChild(label);
	label->setPosition(Vec2(size.width - 10, size.height - 13));
	label->setTag(11);
}
void buyuchang_control29_Paint(Node*node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	paintNode->removeAllChildren();

	auto kuangb = Armature::create("icon_6");
	kuangb->getAnimation()->play("kuangbao");
	kuangb->setPosition(size.width/2,size.height/2);
	paintNode->addChild(kuangb);

	Sprite *sp = Sprite::create("youxiang_biaoqian.png");
	paintNode->addChild(sp);
	sp->setPosition(Vec2(size.width - 10, size.height - 15));

	int count = SELF->getVariable(RageItem);
	Label *label = Label::createWithBMFont("fonts/num_prop.fnt",ConvertToString(count));
	paintNode->addChild(label);
	label->setPosition(Vec2(size.width - 10, size.height - 13));
	label->setTag(11);

}
void buyuchang_control30_Paint(Node*node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	paintNode->removeAllChildren();

	auto daod = Armature::create("icon_6");
	daod->getAnimation()->play("daodan");
	daod->setPosition(size.width/2,size.height/2);
	paintNode->addChild(daod);

	Sprite *sp = Sprite::create("youxiang_biaoqian.png");
	paintNode->addChild(sp);
	sp->setPosition(Vec2(size.width - 10, size.height - 15));

	int count = SELF->getVariable(MissileItem);
	Label *label = Label::createWithBMFont("fonts/num_prop.fnt",ConvertToString(count));
	paintNode->addChild(label);
	label->setPosition(Vec2(size.width - 10, size.height - 13));
	label->setTag(11);
}
void buyuchang_control31_Paint(Node*node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	paintNode->removeAllChildren();

	auto jiguang = Armature::create("icon_6");
	jiguang->getAnimation()->play("jiguang");
	jiguang->setPosition(size.width/2,size.height/2);
	paintNode->addChild(jiguang);

	Sprite *sp = Sprite::create("youxiang_biaoqian.png");
	paintNode->addChild(sp);
	sp->setPosition(Vec2(size.width - 10, size.height - 15));

	int count = SELF->getVariable(LaserItem);
	Label *label = Label::createWithBMFont("fonts/num_prop.fnt",ConvertToString(count));
	paintNode->addChild(label);
	label->setPosition(Vec2(size.width - 10, size.height - 13));
	label->setTag(11);
}
void buyuchang_control32_Paint(Node*node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	paintNode->removeAllChildren();

	auto suod = Armature::create("icon_6");
	suod->getAnimation()->play("suoding");
	suod->setPosition(size.width/2,size.height/2);
	paintNode->addChild(suod);

	Sprite *sp = Sprite::create("youxiang_biaoqian.png");
	paintNode->addChild(sp);
	sp->setPosition(Vec2(size.width - 10, size.height - 15));

	int count = SELF->getVariable(LockFishItem);
	Label *label = Label::createWithBMFont("fonts/num_prop.fnt",ConvertToString(count));
	paintNode->addChild(label);
	label->setPosition(Vec2(size.width - 10, size.height - 13));
	label->setTag(11);
}

void buyuchang_control18_Paint(Node*node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	auto gTask = Armature::create("icon_2");//关卡任务cocostudio动画
	gTask->setPosition(size.width/2,size.height/2);
	gTask->getAnimation()->play("chongzhi");
	paintNode->addChild(gTask);

	ctrl->setVisible(false);
}
void buyuchang_control19_Paint(Node*node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();
	GameLayer *layer = (GameLayer*)GMI->getRoom();
	auto taskFish = Fish::createFishshadow((Fish::FishType)layer->getTaskfishType());
	taskFish->setPosition(size.width/2,size.height/2);
	taskFish->setColor(ccc3(255,255,255));
	taskFish->setOpacity(255);
	taskFish->setRotation(90);
	paintNode->addChild(taskFish,22);
}
void buyuchang_control19_Update(Node*node,float dt)
{
	//MControl* ctrl = (MControl*)node;
	//Size size = ctrl->getSize();
	//Node* paintNode = ctrl->getPaintNode();
	//GameLayer *layer = (GameLayer*)GMI->getRoom();
	//if (chongzhiTask)
	//{
	//	paintNode->removeAllChildren();

	//	auto taskFish = Fish::createFishshadow((Fish::FishType)layer->getTaskfishType());
	//	taskFish->setPosition(size.width/2,size.height/2);
	//	taskFish->setColor(ccc3(255,255,255));
	//	taskFish->setOpacity(255);
	//	taskFish->setRotation(90);
	//	paintNode->addChild(taskFish,22);

	//	chongzhiTask = false;
	//}
	//
	//int Level = SELF->getGameCheck();
	//int preLevel = gamelayer->getpreGameCheck();
	//if (Level!=preLevel)
	//{
	//	paintNode->removeAllChildren();

	//	auto taskFish = Fish::createFishshadow((Fish::FishType)layer->getTaskfishType());
	//	taskFish->setPosition(size.width/2,size.height/2);
	//	taskFish->setColor(ccc3(255,255,255));
	//	taskFish->setOpacity(255);
	//	taskFish->setRotation(90);
	//	paintNode->addChild(taskFish,22);

	//	//gamelayer->setpreGameCheck(Level);
	//}
}

//LabelTTF* goBackLabel;
void buyuchang_control20_Paint(Node*node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();
	GameLayer *layer = (GameLayer*)GMI->getRoom();
	String* str = String::createWithFormat("%02d : %02d : %02d",layer->getGobackHor(),layer->getGobackMin(),layer->getGobackSec());
	Label* goBackLabel = Label::create(str->getCString(),"Arial",24);
	goBackLabel->setPosition(size.width/2,size.height/2);
	goBackLabel->setScale(0.75f);
	paintNode->addChild(goBackLabel);

	goBackLabel->setTag(100);
}
void buyuchang_control20_Update(Node*node,float dt)
{
	GameLayer *layer = (GameLayer*)GMI->getRoom();
	MControl* ctrl = (MControl*)node;
	Label* goBackLabel = (Label*)ctrl->getPaintNode()->getChildByTag(100);
	if (goBackLabel)
	{
		String* str = String::createWithFormat("%02d : %02d : %02d",layer->getGobackHor(),layer->getGobackMin(),layer->getGobackSec());
		goBackLabel->setString(str->getCString());
	}
}
void buyuchang_control28_Update(Node*node,float dt)
{
	MControl *ctrl = (MControl *)node;
	Node *paintNode = ctrl->getPaintNode();
	float cdtime = 6.0f;
	if (paintNode->getChildByTag(110))
	{
		ProgressTimer* cd = (ProgressTimer*)paintNode->getChildByTag(110);
		float per = cd->getPercentage();
		Label* lb = (Label*)paintNode->getChildByTag(111);
		if (lb)
		{
			if (per<=1)
			{
				lb->removeFromParentAndCleanup(true);
				cd->removeFromParentAndCleanup(true);
				ctrl->registerUpdateLogicEvent(nullptr);
				buyuchang_control28Lock= false;
				return;
			}
			lb->setString(ConvertToString((int)(cdtime*per/100.0f)+1));
		}

	}

}
void buyuchang_control29_Update(Node*node,float dt)
{
	MControl *ctrl = (MControl *)node;
	Node *paintNode = ctrl->getPaintNode();
	if (paintNode->getChildByTag(110))
	{
		ProgressTimer* cd = (ProgressTimer*)paintNode->getChildByTag(110);
		float per = cd->getPercentage();
		Label* lb = (Label*)paintNode->getChildByTag(111);
		if (lb)
		{
			if (per<=1)
			{
				lb->removeFromParentAndCleanup(true);
				cd->removeAllChildrenWithCleanup(true);
				ctrl->registerUpdateLogicEvent(nullptr);
				return;
			}
			float cdtime = 6.0f;
			String* money = String::createWithFormat("%d",(int)(cdtime*per/100.0f)+1);
			lb->setString(money->getCString());
		}

	}
	
}
void buyuchang_control32_Update(Node*node,float dt)
{
	MControl *ctrl = (MControl *)node;
	Node *paintNode = ctrl->getPaintNode();
	float cdtime = 6.0f;
	if (paintNode->getChildByTag(110))
	{
		ProgressTimer* cd = (ProgressTimer*)paintNode->getChildByTag(110);
		float per = cd->getPercentage();
		Label* lb = (Label*)paintNode->getChildByTag(111);

		if (lb)
		{
			if (per<=1)
			{
				lb->removeFromParentAndCleanup(true);
				cd->removeAllChildrenWithCleanup(true);
				ctrl->registerUpdateLogicEvent(nullptr);
				return;
			}
			String* money = String::createWithFormat("%d",(int)(cdtime*per/100.0f)+1);
			lb->setString(money->getCString());
		}
	}

}

void buyuchang_control39_Paint(Node*node)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();
	GameLayer *layer = (GameLayer*)GMI->getRoom();
	String* str = String::createWithFormat("0 / %d",layer->getTaskfishNum());
	Label* taskNumLabel = Label::create(str->getCString(),"fonts/arial.ttf",24);
	taskNumLabel->setPosition(size.width/2,size.height/2);
	taskNumLabel->setColor(ccc3(125,255,125));
	paintNode->addChild(taskNumLabel);
	taskNumLabel->setTag(99);
}
void buyuchang_control39_Update(Node*node,float dt)
{
	GameLayer *layer = (GameLayer *)pRoom;
	MControl *ctrl = (MControl*)node;
	Label* taskNumLabel = (Label*)ctrl->getPaintNode()->getChildByTag(99);
	if (taskNumLabel)
	{
		String* str = String::createWithFormat("%d / %d",layer->getKilltaskFishNum(),layer->getTaskfishNum());
		taskNumLabel->setString(str->getCString());
	}
	
}

void buyuchang_control41_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode= ctrl->getPaintNode();
	paintNode->removeAllChildren();

	auto shanArm = Armature::create("icon_2");
	shanArm->getAnimation()->play("jiesuo");
	shanArm->setPosition(size.width/2,size.height/2);
	shanArm->setScaleX(0.8f);
	shanArm->setScaleY(0.65f);
	paintNode->addChild(shanArm);

	std:string name = GMI->getString("UIText","text1");
	auto guoglabel = Label::create(name.c_str(),"Aril",20);
	guoglabel->setPosition(size.width/2,size.height/2+20);
	guoglabel->setColor(ccc3(0,0,0));
	paintNode->addChild(guoglabel,10);

	char str[65];
	sprintf(str,"X%d",gamelayer->getCheckGold());
	auto jianglLabel = Label::create(str,"Aril",20);
	jianglLabel->setPosition(size.width/2+20,size.height/2-15);
	jianglLabel->setColor(ccc3(0,0,0));
	paintNode->addChild(jianglLabel,10);
	
	auto gold = Sprite::create("gg.png");
	gold->setPosition(size.width/2-30,size.height/2-15);
	gold->setScale(0.55f);
	paintNode->addChild(gold,10);
}

void buyuchang_control42_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	auto dengjik = Armature::create("icon_2");
	dengjik->setPosition(size.width/2+10,size.height/2-40);
	dengjik->getAnimation()->play("dengji");
	paintNode->addChild(dengjik);
}

void buyuchang_control43_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	auto shanArm = Armature::create("icon_2");
	shanArm->getAnimation()->play("jiesuo");
	shanArm->setPosition(size.width/2,size.height/2);
	shanArm->setScaleX(0.8f);
	shanArm->setScaleY(0.65f);
	paintNode->addChild(shanArm);

	CannonRateInf* caI;
	for (auto crateInf : GData->cannonRateArray)
	{
		if(crateInf) caI = crateInf;
		if (!caI->bOpen)
		{
			break;
		}
	}

	std::string deblockName = GMI->getString("UIText","text7")+ConvertToString(caI->consume)+GMI->getString("UIText","text8");
	auto label = Label::createWithSystemFont(deblockName.c_str(),"Aril",20,Size(80,160),TextHAlignment::CENTER);
	label->setPosition(size.width/2,size.height/2-55);
	paintNode->addChild(label);
}

//UIForm *form;
void buyuchang_initialize(Node* node)
{
	UIForm *form = (UIForm*)node;
	form->getControl(buyuchang_control7)->registerPaintEvent(buyuchang_control7_Paint);//炮台位置
	
	form->getControl(buyuchang_control23)->registerPaintEvent(buyuchang_control23_Paint);
	form->getControl(buyuchang_control24)->registerPaintEvent(buyuchang_control24_Paint); //等级位置
	form->getControl(buyuchang_control6)->registerPaintEvent(buyuchang_control6_Paint); //职衔位置

	form->getControl(buyuchang_control10)->registerPaintEvent(buyuchang_control10_Paint); //金币数字位置
	form->getControl(buyuchang_control10)->registerUpdateLogicEvent(buyuchang_control10_Update); 
	form->getControl(buyuchang_control38)->registerPaintEvent(buyuchang_control38_Paint); //倍率位置

	form->getControl(buyuchang_control35)->registerPaintEvent(buyuchang_control35_Paint); //自动发炮
	form->getControl(buyuchang_control36)->registerPaintEvent(buyuchang_control36_Paint); //换炮

	form->getControl(buyuchang_control33)->registerPaintEvent(buyuchang_control33_Paint); //金币商城
	form->getControl(buyuchang_control34)->registerPaintEvent(buyuchang_control34_Paint); //在线礼包
	form->getControl(buyuchang_control34)->registerUpdateLogicEvent(buyuchang_control34_Update);

	//form->getControl(buyuchang_control12)->registerPaintEvent(buyuchang_control12_Paint);//缩放按钮设置菜单

	form->getControl(buyuchang_control28)->registerPaintEvent(buyuchang_control28_Paint);//各种道具
	form->getControl(buyuchang_control29)->registerPaintEvent(buyuchang_control29_Paint);
	form->getControl(buyuchang_control30)->registerPaintEvent(buyuchang_control30_Paint);
	form->getControl(buyuchang_control31)->registerPaintEvent(buyuchang_control31_Paint);
	form->getControl(buyuchang_control32)->registerPaintEvent(buyuchang_control32_Paint);

	//重置任务
	form->getControl(buyuchang_control18)->registerPaintEvent(buyuchang_control18_Paint);
	form->getControl(buyuchang_control19)->registerPaintEvent(buyuchang_control19_Paint);
	//form->getControl(buyuchang_control19)->registerUpdateLogicEvent(buyuchang_control19_Update);
	form->getControl(buyuchang_control20)->registerPaintEvent(buyuchang_control20_Paint);
	form->getControl(buyuchang_control20)->registerUpdateLogicEvent(buyuchang_control20_Update);
	form->getControl(buyuchang_control39)->registerPaintEvent(buyuchang_control39_Paint);
	form->getControl(buyuchang_control39)->registerUpdateLogicEvent(buyuchang_control39_Update);
	////任务完成
	form->getControl(buyuchang_control41)->registerPaintEvent(buyuchang_control41_Paint);
	form->getControl(buyuchang_control42)->registerPaintEvent(buyuchang_control42_Paint);
	form->getControl(buyuchang_control43)->registerPaintEvent(buyuchang_control43_Paint);

	form->getControl(buyuchang_control12)->setScale(0.1f);
	buyuchang_shezhi_tabType = 1;

	actionTri = true;
	buyuchang_control28Lock = false;
}
//control3
void buyuchang_control3_Click(Node *node,Touch* ptouch, Event* event)//倍率减
{
	if(SELF->curRateInfIndex==0) return ;
	SELF->curRateInfIndex--;
	CannonRateInf *inf = GData->getCannonRateInf(SELF->curRateInfIndex);
	SELF->getCannon()->setCannonRateInf(inf);
	SELF->getCannon()->setLevelEffect();
	UIM->getForm(Form_buyuchang)->getControl(buyuchang_control38)->refresh();
}
//control4
void buyuchang_control4_Click(Node *node,Touch* ptouch, Event* event)//倍率加
{
	if(SELF->curRateInfIndex==23) return ;
	//
	CannonRateInf *inf = GData->getCannonRateInf(SELF->curRateInfIndex+1);
	
	if (inf->bOpen)
	{
		SELF->curRateInfIndex++;
		SELF->getCannon()->setCannonRateInf(inf);
		SELF->getCannon()->setLevelEffect();
		UIM->getForm(Form_buyuchang)->getControl(buyuchang_control38)->refresh();
	}


}
//control11
void buyuchang_control11_Click(Node *node,Touch* ptouch, Event* event)
{
	SELF->addGold(1000);
}

void buyuchang_control13_Click(Node *node,Touch* ptouch, Event* event)//设置按钮
{
	log("shezhi");
	auto form = UIM->getForm(Form_buyuchang);

	auto ctrl = form->getControl(buyuchang_control12);
	ctrl->stopAllActions();
	if (buyuchang_shezhi_tabType == 0)
	{
		//缩进
		auto scaleTo = ScaleTo::create(0.15f,0.1f);
		ctrl->runAction(scaleTo);
		buyuchang_shezhi_tabType = 1;
	}
	else
	{
		//展开
		auto action1 = ScaleTo::create(0.1f,1.2f);
		auto action2 = ScaleTo::create(0.1f,0.9f);
		auto action3 = ScaleTo::create(0.1f,1.0f);
		ctrl->runAction(Sequence::create(action1,action2,action3,nullptr));
		buyuchang_shezhi_tabType = 0;
	}

	auto curCtrl = (MControl*)node;
	curCtrl->stopAllActions();
	curCtrl->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	curCtrl->runAction(Sequence::create(cAction1,cAction2,nullptr));
}
//control14
void buyuchang_control14_Click(Node *node,Touch* ptouch, Event* event)
{
	log("paodanjiesuo");
	auto jiesuobullet = UIM->showForm(Form_jiesuopaodan);
	auto ctrl2 = jiesuobullet->getControl(jiesuopaodan_control2);
	ctrl2->setScale(0.01f);
	auto scale1 = ScaleTo::create(0.25f,1.2f,1.2f);
	auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
	ctrl2->runAction(Sequence::createWithTwoActions(scale1,scale2));

	/*****************修改*********************/
	auto form = UIM->getForm(Form_buyuchang);
	form->getControl(buyuchang_control43)->setVisible(false);
	pRoom->setClickDeblock(true);
	/*****************修改*********************/
}
//control15
void buyuchang_control15_Click(Node *node,Touch* ptouch, Event* event)
{
	log("yuanniu");
	auto fish = UIM->showForm(Form_beilvjieshao);
	auto ctrl2 = fish->getControl(beilvjieshao_control2);/*修改*/
	ctrl2->setScale(0.01f);  /*修改*/
	auto scale1 = ScaleTo::create(0.25f,1.2f,1.2f);
	auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
	ctrl2->runAction(Sequence::createWithTwoActions(scale1,scale2));  /*修改*/
}
//control16
void buyuchang_control16_Click(Node *node,Touch* ptouch, Event* event)
{
	log("yinyueanniu");
}
//control17
void buyuchang_control17_Click(Node *node,Touch* ptouch, Event* event)
{
	auto exitGame = UIM->showForm(Form_canrentuichu);
	auto ctrl2 = exitGame->getControl(canrentuichu_control2);

	ctrl2->setScale(0.01f);
	auto scale1 = ScaleTo::create(0.25f,1.2f,1.2f);
	auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
	ctrl2->runAction(Sequence::createWithTwoActions(scale1,scale2));

}
//control21
void buyuchang_control21_Click(Node *node,Touch* ptouch, Event* event)//重置任务
{
	MControl *ctrl = (MControl*)node;
	chongzhiTask = true;
	GameLayer *layer = (GameLayer *)pRoom;
	layer->checkTask();
	layer->clearKilltaskFishNum();
	chongzhiTask = true;
	ctrl->form->getControl(buyuchang_control19)->refresh();
	ctrl->refresh();
// 	auto curForm = UIM->getForm(Form_buyuchang);
// 	auto task = curForm->getControl(buyuchang_control18);
// 	task->setVisible(false);
// 
// 	auto renwu = UIM->showForm(Form_renwutankuang);
// 	renwu->setEnabled(true);
// 	renwu->setScale(1.0f);
// 	renwu->setPosition(SCREEN_WIDTH * 1.5f,SCREEN_HALF_HEIGHT);
// 	renwu->runAction(Sequence::createWithTwoActions(DelayTime::create(1.0f),MoveTo::create(0.2f,Vec2(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT))));
}

/*修改*/ //添加
void setCDBar(float cdtime)
{
	do 
	{
		
	} while (0);

	do 
	{
		auto form = UIM->getForm(Form_buyuchang);
		auto missile = form->getControl(buyuchang_control30);
		Node* missileNode = missile->getPaintNode();

		Sprite* barsp = Sprite::create("bar.png");
		ProgressTimer* cd = ProgressTimer::create(barsp);
		cd->setType(kCCProgressTimerTypeRadial);
		cd->setScaleX(-1);
		cd->setPercentage(100);
		cd->setTag(110);
		cd->setPosition(missileNode->getContentSize().width/2,missileNode->getContentSize().height/2);
		missile->addChild(cd,10);
		cd->runAction(Sequence::createWithTwoActions(ProgressTo::create(cdtime,0.0),RemoveSelf::create()));

	} while (0);

	do 
	{
		auto form = UIM->getForm(Form_buyuchang);
		auto laser = form->getControl(buyuchang_control31);
		Node* laserNode = laser->getPaintNode();

		Sprite* barsp = Sprite::create("bar.png");
		ProgressTimer* cd = ProgressTimer::create(barsp);
		cd->setType(kCCProgressTimerTypeRadial);
		cd->setScaleX(-1);
		cd->setPercentage(100);
		cd->setTag(110);
		cd->setPosition(laserNode->getContentSize().width/2,laserNode->getContentSize().height/2);
		laser->addChild(cd,10);
		cd->runAction(Sequence::createWithTwoActions(ProgressTo::create(cdtime,0.0),RemoveSelf::create()));
;
	} while (0);
}

void buyFixedItem(int payId,bool flag)
{
	if(flag)
	{
		buyItems(payId);

		UIForm *form = UIM->getForm(Form_buyuchang);
		form->getControl(buyuchang_control28)->refresh();
	}
}
//control28
void buyuchang_control28_Click(Node *node,Touch* ptouch, Event* event)
{
	if(buyuchang_control28Lock)
	{
		return;
	}
	auto ctrl = (MControl*)node;
	ctrl->stopAllActions();
	ctrl->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	ctrl->runAction(Sequence::create(cAction1,cAction2,nullptr));
	if(SELF->getVariable(FixedItem) <= 0)
	{
		pSMSInfo->sendMessage(SMS_BUY_FixedScreen,buyFixedItem);
		return;
	}
	GameLayer *layer = (GameLayer*)pRoom;
	layer->pauseObjAction(10.0f);//
	Armature *arm = Armature::create("daoju2");
	arm->getAnimation()->playWithIndex(1);
	arm->getAnimation()->setMovementEventCallFunc(arm,movementEvent_selector(UICallBack::removeArmature));
	pRoom->addChild(arm);
	arm->setZOrder(BULLETLOCALZORDER);
	arm->setPosition(Vec2(S_WIDTH/2,S_HEIGHT/2));


	Node *paintNode = ctrl->getPaintNode();
	Sprite* barsp = Sprite::create("bar.png");
	ProgressTimer* cd = ProgressTimer::create(barsp);
	cd->setType(kCCProgressTimerTypeRadial);
	cd->setScaleX(-1);
	cd->setPercentage(100);
	cd->setPosition(node->getContentSize().width/2,node->getContentSize().height/2);
	paintNode->addChild(cd,1,110);
	cd->runAction(ProgressTo::create(10.0f,0.0));

	String* money = String::createWithFormat("%d",60);
	Label* lb = Label::create(money->getCString(),"fonts/arial.ttf",40);
	lb->setColor(Color3B(0,255,0));
	lb->setPosition(cd->getPosition());
	lb->setTag(111);
	paintNode->addChild(lb,1999,111);
	ctrl->registerUpdateLogicEvent(buyuchang_control28_Update);
	buyuchang_control28Lock = true;

	SELF->addVariable(FixedItem,-1);
	Label *label = (Label*)ctrl->getPaintNode()->getChildByTag(11);
	label->setString(ConvertToString(SELF->getVariable(FixedItem)));
}

void buyRageItem(int payId,bool flag)
{
	if(flag)
	{
		buyItems(payId);

		UIForm *form = UIM->getForm(Form_buyuchang);
		form->getControl(buyuchang_control29)->refresh();
	}
}
//control29
void buyuchang_control29_Click(Node *node,Touch* ptouch, Event* event)
{
	if (SELF->getCannon()->fireType!=Cannon::Common)
	{
		return ;
	}
	auto ctrl = (MControl*)node;
	ctrl->stopAllActions();
	ctrl->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	ctrl->runAction(Sequence::create(cAction1,cAction2,nullptr));
	if(SELF->getVariable(RageItem) <= 0)
	{
		pSMSInfo->sendMessage(SMS_BUY_Rage,buyRageItem);
		return;
	}
	SELF->getCannon()->RageTime = 10.0f;
	SELF->getCannon()->setFireType(Cannon::Rage);
	Armature *arm = Armature::create("daoju2");
	arm->getAnimation()->playWithIndex(0);
	//arm->getAnimation()->setMovementEventCallFunc(arm,movementEvent_selector(UICallBack::fixedFishArmature));
	pRoom->addChild(arm);
	arm->setTag(-22);
	arm->setZOrder(BULLETLOCALZORDER);
	arm->setPosition(Vec2(S_WIDTH/2,S_HEIGHT/2));

	auto form = UIM->getForm(Form_buyuchang);
	Node* kuangbNode = ctrl->getPaintNode();
	float cdtime = 6.0f;
	Sprite* barsp = Sprite::create("bar.png");
	ProgressTimer* cd = ProgressTimer::create(barsp);
	cd->setType(kCCProgressTimerTypeRadial);
	cd->setScaleX(-1);
	cd->setPercentage(100);
	cd->setTag(110);
	cd->setPosition(kuangbNode->getContentSize().width/2,kuangbNode->getContentSize().height/2);
	kuangbNode->addChild(cd,1,110);
	cd->runAction(Sequence::createWithTwoActions(ProgressTo::create(cdtime,0.0),RemoveSelf::create()));

	log("create lb kuangbao");
	String* money = String::createWithFormat("%.1f",cdtime);
	Label* lb = Label::create(money->getCString(),"fonts/arial.ttf",40);
	lb->setPosition(cd->getPosition());
	lb->setColor(Color3B(0,255,0));
	lb->setTag(111);
	kuangbNode->addChild(lb,1,111);
	ctrl->registerUpdateLogicEvent(buyuchang_control29_Update);
	SELF->addVariable(RageItem,-1);
	Label *label = (Label*)ctrl->getPaintNode()->getChildByTag(11);
	label->setString(ConvertToString(SELF->getVariable(RageItem)));
}
void buyMissileItem(int payId,bool flag)
{
	if(flag)
	{
		buyItems(payId);

		UIForm *form = UIM->getForm(Form_buyuchang);
		form->getControl(buyuchang_control30)->refresh();
	}
}
//control30
void buyuchang_control30_Click(Node *node,Touch* ptouch, Event* event)
{
	if (SELF->getCannon()->fireType!=Cannon::Common )
	{
		return ;
	}
	auto ctrl = (MControl*)node;
	ctrl->stopAllActions();
	ctrl->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	ctrl->runAction(Sequence::create(cAction1,cAction2,nullptr));
	if(SELF->getVariable(MissileItem) <= 0)
	{
		pSMSInfo->sendMessage(SMS_BUY_Missile,buyMissileItem);
		return;
	}
	SELF->getCannon()->setCilckOnceWithMissionAndLaser();
	SELF->getCannon()->setFireType(Cannon::Missile);
	fireMisison = true;
	SELF->getCannon()->bPrepareFire = true;

	SELF->addVariable(MissileItem,-1);
	Label *label = (Label*)ctrl->getPaintNode()->getChildByTag(11);
	label->setString(ConvertToString(SELF->getVariable(MissileItem)));
	UIM->getForm(Form_buyuchang)->getControl(buyuchang_control7)->registerUpdateLogicEvent(buyuchang_control7_Update);
}
void buyLaserItem(int payId,bool flag)
{
	if(flag)
	{
		buyItems(payId);

		UIForm *form = UIM->getForm(Form_buyuchang);
		form->getControl(buyuchang_control31)->refresh();
	}
}
//control31
void buyuchang_control31_Click(Node *node,Touch* ptouch, Event* event)
{
	if (SELF->getCannon()->fireType!=Cannon::Common)
	{
		return ;
	}
	auto ctrl = (MControl*)node;
	ctrl->stopAllActions();
	ctrl->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	ctrl->runAction(Sequence::create(cAction1,cAction2,nullptr));
	if(SELF->getVariable(LaserItem) <= 0)
	{
		pSMSInfo->sendMessage(SMS_BUY_Laser,buyLaserItem);
		return;
	}
	SELF->addVariable(LaserItem,-1);
	Label *label = (Label*)ctrl->getPaintNode()->getChildByTag(11);
	label->setString(ConvertToString(SELF->getVariable(LaserItem)));

	fireLaser = true;
	SELF->getCannon()->bPrepareFire = true;
	SELF->getCannon()->setFireType(Cannon::Laser);
	SELF->getCannon()->setCilckOnceWithMissionAndLaser();
	UIM->getForm(Form_buyuchang)->getControl(buyuchang_control7)->registerUpdateLogicEvent(buyuchang_control7_Update);
}
void buyLockFishItem(int payId,bool flag)
{
	if(flag)
	{
		buyItems(payId);

		UIForm *form = UIM->getForm(Form_buyuchang);
		form->getControl(buyuchang_control32)->refresh();
	}
}
//control32
void buyuchang_control32_Click(Node *node,Touch* ptouch, Event* event)
{
	auto ctrl = (MControl*)node;
	ctrl->stopAllActions();
	ctrl->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	ctrl->runAction(Sequence::create(cAction1,cAction2,nullptr));

	if(SELF->getVariable(LockFishItem) <= 0)
	{
		pSMSInfo->sendMessage(SMS_BUY_LockFish,buyLockFishItem);
		return;
	}
	SELF->addVariable(LockFishItem,-1);
	SELF->getCannon()->LockTime = 10.0f;
	SELF->getCannon()->bLockFish = true;

	auto form = UIM->getForm(Form_buyuchang);
	Node* lokcNode = ctrl->getPaintNode();
	float cdtime = 6.0f;
	Sprite* barsp = Sprite::create("bar.png");
	ProgressTimer* cd = ProgressTimer::create(barsp);
	cd->setType(kCCProgressTimerTypeRadial);
	cd->setScaleX(-1);
	cd->setPercentage(100);
	cd->setTag(110);
	cd->setPosition(lokcNode->getContentSize().width/2,lokcNode->getContentSize().height/2);
	lokcNode->addChild(cd,1,110);
	cd->runAction(Sequence::createWithTwoActions(ProgressTo::create(cdtime,0.0),RemoveSelf::create()));


	String* money = String::createWithFormat("%.1f",cdtime);
	Label* lb = Label::create(money->getCString(),"fonts/Marker Felt.ttf",40);
	lb->setPosition(cd->getPosition());
	lb->setColor(Color3B(0,255,0));
	lb->setTag(111);
	lokcNode->addChild(lb,1,111);

	Label *label = (Label*)lokcNode->getChildByTag(11);
	label->setString(ConvertToString(SELF->getVariable(LockFishItem)));

	ctrl->registerUpdateLogicEvent(buyuchang_control32_Update);
}

//control33

void buyuchang_control33_Click(Node *node,Touch* ptouch, Event* event)//金币商城
{
	auto goldStoreBt = (MControl*)node;
	goldStoreBt->stopAllActions();
	goldStoreBt->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	goldStoreBt->runAction(Sequence::create(cAction1,cAction2,nullptr));

	auto goldStore = UIM->showForm(Form_jingbishangcheng);

	goldStore->setScale(0.01f);
	auto scale1 = ScaleTo::create(0.25f,1.2f,1.2f);
	auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
	goldStore->runAction(Sequence::createWithTwoActions(scale1,scale2));
}
//control34
void buyuchang_control34_Click(Node *node,Touch* ptouch, Event* event)//在线奖励
{
	auto onlineGoldBt = (MControl*)node;
	onlineGoldBt->stopAllActions();
	onlineGoldBt->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	onlineGoldBt->runAction(Sequence::create(cAction1,cAction2,nullptr));

	auto onLine = UIM->showForm(Form_zaixianjiangli);
	auto ctrl2 = onLine->getControl(zaixianjiangli_control2);
	ctrl2->setScale(0.01f);
	auto scale1 = ScaleTo::create(0.25f,1.2f,1.2f);
	auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
	ctrl2->runAction(Sequence::createWithTwoActions(scale1,scale2));
}
//control35
void buyuchang_control35_Click(Node *node,Touch* ptouch, Event* event)//自动发炮
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
//control36
void buyuchang_control36_Click(Node *node,Touch* ptouch, Event* event)//换炮
{
	log("huanpao");
	auto changeCtrl = (MControl*)node;
	changeCtrl->stopAllActions();
	changeCtrl->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	changeCtrl->runAction(Sequence::create(cAction1,cAction2,nullptr));

	auto chang = UIM->showForm(Form_genghuanpaotai);
	auto ctrl2 = chang->getControl(genghuanpaotai_control2);
	ctrl2->setScale(0.01f);
	auto scale1 = ScaleTo::create(0.25f,1.2f,1.2f);
	auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
	ctrl2->runAction(Sequence::createWithTwoActions(scale1,scale2));
}
//control41
void buyuchang_control41_Click(Node *node,Touch* ptouch, Event* event)
{
	if (!gamelayer->nextCheck)
	{
		auto gameEnd = UIM->showForm(Form_gameend);
		auto ctrl3 = gameEnd->getControl(gameend_control3);/*修改*/
		ctrl3->setScale(0.01f); /*修改*/
		auto scale1 = ScaleTo::create(0.2f,1.2f,1.2f);
		auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
		ctrl3->runAction(Sequence::createWithTwoActions(scale1,scale2));/*修改*/

		auto ctrl = (MControl*)node;
		ctrl->setVisible(false);

		SELF->addGold(gamelayer->getCheckGold());

		LevelInf* Inf = GData->levelInfArray.at(SELF->getGameCheck());
		
		if (!Inf->isOpen)
		{
			Inf->isOpen = true;
		}
		
	}
	else
	{
		log("jinru");
		SELF->addGameCheck(1);
		GameLayer *layer = (GameLayer *)pRoom;
		layer->checkTask();
		//guiGame->checkTask();

		auto renwu = UIM->showForm(Form_renwutankuang);
		auto renwuCtrl = renwu->getControl(renwutankuang_control1);

		renwu->setEnabled(true);
		renwu->setScale(1.0f);
		renwuCtrl->setOpacity(125);
		renwu->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);

		auto ctrl2 = renwu->getControl(renwutankuang_control2);/*修改*/
		ctrl2->setScale(0.01f);   /*修改*/
		auto scale1 = ScaleTo::create(0.2f,1.2f,1.2f);
		auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
		ctrl2->runAction(Sequence::createWithTwoActions(scale1,scale2));/*修改*/

		auto ctrl = (MControl*)node;
		ctrl->setVisible(false);

		gamelayer->nextCheck = false;
	}
}


void buyuchang_control40_Click(Node *node,Touch* ptouch, Event* event)
{

}

void buyuchang_control43_Click(Node *node,Touch* ptouch, Event* event)
{
	MControl*ctrl = (MControl*)node;
	ctrl->setVisible(false);

	pRoom->setClickDeblock(true);/*修改*/

	auto jiesuobullet = UIM->showForm(Form_jiesuopaodan);
	auto ctrl2 = jiesuobullet->getControl(jiesuopaodan_control2);
	ctrl2->setScale(0.01f);
	auto scale1 = ScaleTo::create(0.25f,1.2f,1.2f);
	auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
	ctrl2->runAction(Sequence::createWithTwoActions(scale1,scale2));

}