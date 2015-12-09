#include"UI.h"
#include "GScene.h"
#include "GameManager.h"
#include "Fish.h"
#include "Player.h"
void danrenmoshixuanguan_register(Node* node)
{
  UIForm *form = (UIForm*)node;
  form->getControl(danrenmoshixuanguan_control1)->registerClickEvent(danrenmoshixuanguan_control1_Click);
  form->getControl(danrenmoshixuanguan_control3)->registerClickEvent(danrenmoshixuanguan_control3_Click);
  form->getControl(danrenmoshixuanguan_control7)->registerClickEvent(danrenmoshixuanguan_control7_Click);
  form->getControl(danrenmoshixuanguan_control8)->registerClickEvent(danrenmoshixuanguan_control8_Click);
}

void danrenmoshixuanguan_control6_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	auto arm = Armature::create("jingdiancg");
	arm->getAnimation()->play("jbsc_dong");
	String *pString = String::create("jbsc_dong_chixu");
	pString->retain();
	arm->setUserData(pString);
	arm->getAnimation()->setMovementEventCallFunc(arm,movementEvent_selector(UICallBack::playNextArmature));
	arm->setPosition(size.width/2,size.height/2-20);
	paintNode->addChild(arm);
}

void danrenmoshixuanguan_control4_Paint(Node*node)
{
	
// 	auto form = UIM->getForm(Form_danrenmoshixuanguan);
// 	auto ctrl = form->getControl(danrenmoshixuanguan_control4);
// 
// 	Node* paintNode = ctrl->getPaintNode(); 
// 	auto size = ctrl->getSize(); 
// 	paintNode->removeAllChildren();
// 
// 	MControl *parent = (MControl*)ctrl->getParent();
// 	auto inf = (LevelInf*)parent->getUserData();
// 	if (inf)
// 	{
// 		auto bgView = (MControl*)parent->ctrlList.at(0);
// 		if (inf->isOpen)
// 		{
// 			int index = CCRANDOM_0_1()*3+1;
// 			UIM->setSkin(ctrl,index);
// 		}
// 	}
}

void danrenmoshixuanguan_control3_Paint(Node*node)
{
	MCONTROL_INIT_REMOVEALL;
	/****************修改******************/
	auto inf = (LevelInf*)ctrl->getUserData();

	if (inf && !inf->isOpen)
	{
		auto form = UIM->getForm(Form_danrenmoshixuanguan);
		auto listView = (MListView*)form->getControl(danrenmoshixuanguan_control2);
		auto item = listView->getItem(inf->m_id-1);
		auto beforeInf = (LevelInf*)item->getUserData();

		if (beforeInf->isOpen)
		{
			UIM->setSkin(item,1);
		}
	}
	/****************修改******************/
}

void danrenmoshixuanguan_control5_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	
	/****************修改******************/
	MControl *parent = (MControl*)ctrl->getParent();
	auto inf = (LevelInf*)parent->getUserData();
	if (inf)
	{
		auto bgView = (MControl*)parent->ctrlList.at(0);
		auto lockCtrl = (MControl*)parent->ctrlList.at(2);
		if (inf->isOpen)
		{
			int index = CCRANDOM_0_1()*3+1;
			UIM->setSkin(bgView,index);

			lockCtrl->setVisible(false);
		}
	}
	/****************修改******************/
	std::string linkName = ConvertToString(inf->m_id+1)+GMI->getString("UIText","text5")+ inf->m_name;
	auto checkName = Label::create(linkName.c_str(),"Aril",24);
	checkName->setPosition(size.width/2,size.height/2-5);
	paintNode->addChild(checkName);

	
}

void danrenmoshixuanguan_initialize(Node* node)
{
	auto form = (UIForm*)node;
	form->getControl(danrenmoshixuanguan_control6)->registerPaintEvent(danrenmoshixuanguan_control6_Paint);
	form->getControl(danrenmoshixuanguan_control5)->registerPaintEvent(danrenmoshixuanguan_control5_Paint);
	form->getControl(danrenmoshixuanguan_control4)->registerPaintEvent(danrenmoshixuanguan_control4_Paint);
	form->getControl(danrenmoshixuanguan_control3)->registerPaintEvent(danrenmoshixuanguan_control3_Paint);

	auto listView = (MListView*)form->getControl(danrenmoshixuanguan_control2);
	listView->clearItems();

	int count = GData->levelInfArray.size();
	listView->setItemCount(count);

	for (int i = 0;i < count;i++)
	{
		auto item = listView->getItem(i);
		auto inf = GData->getLevelInf(i);
		item->setUserData(inf);
	}
}
//control1
void danrenmoshixuanguan_control1_Click(Node *node,Touch* ptouch, Event* event)
{
	auto curForm = UIM->getForm(Form_danrenmoshixuanguan);
	auto nextForm = UIM->getForm(Form_fengmian);
	if (!nextForm || !nextForm->isActive())
	{
		nextForm = UIM->showForm(Form_fengmian);
	}
	nextForm->setEnabled(true);
	nextForm->setPosition(SCREEN_WIDTH * 1.5f,SCREEN_HALF_HEIGHT);

	auto curMove = MoveTo::create(0.2f,Vec2(-SCREEN_WIDTH/2,SCREEN_HALF_HEIGHT));
	
	CallFunc *endCallBack = CallFunc::create(curForm,callfunc_selector(UICallBack::setFormUnVisible));
	curForm->runAction(Sequence::create(curMove,endCallBack,nullptr));

	auto nextMove = MoveTo::create(0.2f,Vec2(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT));
	
	nextForm->runAction(nextMove);
}
//control3
void danrenmoshixuanguan_control3_Click(Node *node,Touch* ptouch, Event* event)
{
	MControl *ctrl = (MControl*)node;
	LevelInf *inf = (LevelInf*)ctrl->getUserData();
	if(inf->isOpen)
	{
		UIM->closeForm(Form_danrenmoshixuanguan,false);
		UIM->closeForm(Form_duorenmoshixuanguan,false);
		UIM->closeForm(Form_fengmian,false);
		GScene->setState(GST_GAME);
		GMI->setSingleMode(true);
	}
	
}
//control7
void danrenmoshixuanguan_control7_Click(Node *node,Touch* ptouch, Event* event)
{
	auto form = UIM->showForm(Form_jiesuopaodan);
	
	auto ctrl2 = form->getControl(jiesuopaodan_control2);
	ctrl2->setScale(0.01f);
	auto scale1 = ScaleTo::create(0.2f,1.2f,1.2f);
	auto scale2 = ScaleTo::create(0.2f,1.0f,1.0f);
	ctrl2->runAction(Sequence::createWithTwoActions(scale1,scale2));
}
//control8
void danrenmoshixuanguan_control8_Click(Node *node,Touch* ptouch, Event* event)
{
	UIForm * form = UIM->getForm(Form_danrenmoshixuanguan);
	MListView *listView = (MListView*)form->getControl(danrenmoshixuanguan_control2);
	listView->setSelectIndex(SELF->getGameCheck());
}
