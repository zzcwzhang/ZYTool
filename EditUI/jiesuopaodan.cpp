#include"UI.h"
#include "Helper.h"
#include "GameDataManager.h"
#include "GameManager.h"
#include "GameLayer.h"
#include "GUILayer.h"
#include "Player.h"
#include "GScene.h"
using namespace std;

int bulletWorth[23] = {500,1000,2000,3000,5000,10000,30000,60000,90000,150000,200000,300000,400000,500000,600000,700000,750000,800000,900000,1000000,1100000,1200000,1300000};
bool jiesuo = false;
void jiesuopaodan_register(Node* node)
{
UIForm *form = (UIForm*)node;
  form->getControl(jiesuopaodan_control4)->registerClickEvent(jiesuopaodan_control4_Click);
  form->getControl(jiesuopaodan_control12)->registerClickEvent(jiesuopaodan_control12_Click);
}

int changeStringtoInt(String* str)
{
	int index = atoi(str->getCString());

	switch(index)
	{
	case 0:
		return 5;
	case 1:
		return 10;
	case 2:
		return 20;
	case 3:
		return 50;
	case 4:
		return 100;
	case 5:
		return 200;
	case 6:
		return 300;
	case 7:
		return 400;
	case 8:
		return 500;
	case 9:
		return 600;
	case 10:
		return 700;
	case 11:
		return 800;
	case 12:
		return 900;
	case 13:
		return 1000;
	case 14:
		return 2000;
	case 15:
		return 3000;
	case 16:
		return 4000;
	case 17:
		return 5000;
	case 18:
		return 6000;
	case 19:
		return 7000;
	case 20:
		return 8000;
	case 21:
		return 9000;
	case 22:
		return 10000;
	}
	
}

void jiesuopaodan_control5_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();

	auto pao = Armature::create("pao");
	pao->setPosition(size.width/2,size.height/2-35);
	pao->setScale(0.75f);
	paintNode->addChild(pao);


	CannonRateInf *inf = (CannonRateInf *)ctrl->getParent()->getUserData();
}

void jiesuopaodan_control5_Update(Node*node,float dt)
{

}

void jiesuopaodan_control6_Paint(Node* node)
{
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();
	paintNode->removeAllChildren();
	CannonRateInf *pStr = (CannonRateInf *)ctrl->getParent()->getUserData();
	Label *worthSp = Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(pStr->rate));
	worthSp->setScale(0.4f);
	worthSp->setAnchorPoint(Vec2(1,0.5));
	worthSp->setPosition(size.width,size.height/2);
	paintNode->addChild(worthSp);
}

void jiesuopaodan_control7_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();
	paintNode->removeAllChildren();
	CannonRateInf *pStr = (CannonRateInf *)ctrl->getParent()->getUserData();
	Label *worthSp = Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(pStr->openCoin));
	worthSp->setScale(0.55f);
	worthSp->setPosition(size.width/2,size.height/2);
	paintNode->addChild(worthSp);
}

Armature* shanArm;
void jiesuopaodan_control8_Paint(Node*node)
{
	auto form = UIM->getForm(Form_jiesuopaodan);
	MListView *bulletList = (MListView *)form->getControl(jiesuopaodan_control3);

	MControl *item = bulletList->getItem(0);
	CannonRateInf *inf = (CannonRateInf *)item->getUserData();

	MControl* ctrl = (MControl*)item->ctrlList.at(3);
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	shanArm = Armature::create("jiesuo");
	shanArm->setPosition(size.width/2,size.height/2-50);
	shanArm->getAnimation()->play("hint_deblocking");
	paintNode->addChild(shanArm);
}

void jiesuopaodan_control8_Update(Node*node,float dt)
{
	MControl* ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();

	
}

void jiesuopaodan_control9_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node* paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();
	
	Label *sp = Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(SELF->getGold()));
	sp->setPosition(size.width/2,size.height/2);
	sp->setScale(0.45f);
	paintNode->addChild(sp);
}

void jiesuopaodan_initialize(Node* node)
{
	UIForm* form = (UIForm*)node;
	
	form->getControl(jiesuopaodan_control5)->registerPaintEvent(jiesuopaodan_control5_Paint);
	form->getControl(jiesuopaodan_control5)->registerUpdateLogicEvent(jiesuopaodan_control5_Update);
	form->getControl(jiesuopaodan_control6)->registerPaintEvent(jiesuopaodan_control6_Paint);
	form->getControl(jiesuopaodan_control7)->registerPaintEvent(jiesuopaodan_control7_Paint);
	form->getControl(jiesuopaodan_control8)->registerPaintEvent(jiesuopaodan_control8_Paint);
	form->getControl(jiesuopaodan_control8)->registerUpdateLogicEvent(jiesuopaodan_control8_Update);
	form->getControl(jiesuopaodan_control9)->registerPaintEvent(jiesuopaodan_control9_Paint);
	MListView *bulletList = (MListView *)form->getControl(jiesuopaodan_control3);
	bulletList->clearItems();
	int count = GData->cannonRateArray.size();
	Vector<CannonRateInf*> tempList;
	for (int i =0;i<count;i++)
	{
		CannonRateInf* inf = GData->getCannonRateInf(i);
		if(!inf->bOpen)
		{
			tempList.pushBack(inf);
		}
	}
	count = tempList.size();
	bulletList->setItemCount(count);
	for (int i =0;i<count;i++)
	{
		CannonRateInf* inf = tempList.at(i);
		MControl *item = bulletList->getItem(i);
		item->setUserData(inf);
	}
}
//control4
void jiesuopaodan_control4_Click(Node *node,Touch* ptouch, Event* event)
{
	MControl *ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node *paintNode = ctrl->getPaintNode();
	
	/*CannonRateInf *inf = (CannonRateInf *)ctrl->getUserData();*/

	auto form = UIM->getForm(Form_jiesuopaodan);
	//auto lock = form->getControl(jiesuopaodan_control8);

	MListView *bulletList = (MListView *)form->getControl(jiesuopaodan_control3);
	MControl *item = bulletList->getItem(0);

	CannonRateInf *inf = (CannonRateInf *)item->getUserData();
	if(SELF->getGold() >= inf->openCoin)
	{
		//bulletList->removeItem(item);
		inf->bOpen = true;
		SELF->addGold(-inf->openCoin);

		MControl* ctrl = item->ctrlList.at(3);
		UIM->setSkin(ctrl,-1);
		shanArm->getAnimation()->play("deblocking");
		shanArm->getAnimation()->setMovementEventCallFunc(shanArm,movementEvent_selector(UICallBack::setBulletLockBlast));
	}
}

//control12
void jiesuopaodan_control12_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->closeForm(Form_jiesuopaodan,false);

	if(GScene->getCurState() != GST_MENU)
	{
		pRoom->setClickDeblock(false) ;
	}
}
