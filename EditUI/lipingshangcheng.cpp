#include"UI.h"
#include "GameManager.h"
#include "Player.h"




int teleChange[10] = {5,10,20,30,50,100,150,200,300,500};
int jiangjuan[10] = {5,1,2,3,5,10,15,20,30,50};

#define LpFNT "fonts/num_liping.fnt"

void lipingshangcheng_register(Node* node)
{
  UIForm *form = (UIForm*)node;
  form->getControl(lipingshangcheng_control5)->registerClickEvent(lipingshangcheng_control5_Click);
  form->getControl(lipingshangcheng_control8)->registerClickEvent(lipingshangcheng_control8_Click);
  form->getControl(lipingshangcheng_control9)->registerClickEvent(lipingshangcheng_control9_Click);
  form->getControl(lipingshangcheng_control10)->registerClickEvent(lipingshangcheng_control10_Click);
  form->getControl(lipingshangcheng_control11)->registerClickEvent(lipingshangcheng_control11_Click);
  form->getControl(lipingshangcheng_control14)->registerClickEvent(lipingshangcheng_control14_Click);
  form->getControl(lipingshangcheng_control19)->registerClickEvent(lipingshangcheng_control19_Click);
}

bool lipingshangcheng_control14_TouchBegin(cocos2d::Node *control,cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{

	UIM->showForm(Form_tongyongtishi);
	showCommonDialog(GMI->getString("TipDialog","text1"));
	return true;
}

bool lipingshangcheng_control19_TouchBegin(cocos2d::Node *control,cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
{

	UIM->showForm(Form_tongyongtishi);
	showCommonDialog(GMI->getString("TipDialog","text1"));
	return true;
}

void lipingshangcheng_control4_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	auto numSprite=Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(SELF->getGold()));
	numSprite->setAnchorPoint(Vec2(1,0.5));
	numSprite->setPosition(size.width+7,size.height/2+5);
	numSprite->setScale(0.45f);
	paintNode->addChild(numSprite);
}

void lipingshangcheng_control7_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	auto numSprite=Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(SELF->getLottery()));
	numSprite->setAnchorPoint(Vec2(1,0.5));
	numSprite->setPosition(size.width,size.height/2);
	numSprite->setScale(0.5f);
	paintNode->addChild(numSprite);
}


void lipingshangcheng_control15_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();

	auto parent = ctrl->getParent();
	String*pStr = (String*)parent->getParent()->getUserData();

	int index = atoi(pStr->getCString());
	std::string teleCost = GMI->getString("UIText","text3")+ConvertToString(teleChange[index])+GMI->getString("UIText","text4");
	Label* teleCos = Label::create(teleCost.c_str(),"Aril",24);
	teleCos->setPosition(size.width/2,size.height/2);
	paintNode->addChild(teleCos);
}

void lipingshangcheng_control16_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();

	auto parent = ctrl->getParent();
	String*pStr = (String*)parent->getParent()->getUserData();

	int index = atoi(pStr->getCString());
	std::string teleCost = ConvertToString(teleChange[index]);
	Label* teleCos = Label::create(teleCost.c_str(),"Aril",60);
	teleCos->setPosition(size.width/2,size.height/2);

	paintNode->addChild(teleCos);
}

void lipingshangcheng_control17_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();

	auto parent = ctrl->getParent();
	String*pStr = (String*)parent->getParent()->getUserData();

	int index = atoi(pStr->getCString());
	String* cost = String::createWithFormat("%d",jiangjuan[index]);
	if (index == 0)
	{
		cost = String::createWithFormat("0.%d",jiangjuan[index]);
	}
	auto teleCos = LabelBMFont::create(cost->getCString(),LpFNT);
	teleCos->setPosition(size.width/2,size.height/2+5);
	if (index == 0)
	{
		teleCos->setScale(0.8);
	}
	


	paintNode->addChild(teleCos);
}


void lipingshangcheng_control20_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();

	auto parent = ctrl->getParent();
	String*pStr = (String*)parent->getParent()->getUserData();

	int index = atoi(pStr->getCString())+5;
	std::string teleCost = GMI->getString("UIText","text3")+ConvertToString(teleChange[index])+GMI->getString("UIText","text4");
	Label* teleCos = Label::create(teleCost.c_str(),"Aril",24);
	teleCos->setPosition(size.width/2,size.height/2);
	paintNode->addChild(teleCos);
}

void lipingshangcheng_control21_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();

	auto parent = ctrl->getParent();
	String*pStr = (String*)parent->getParent()->getUserData();

	int index = atoi(pStr->getCString())+5;
	std::string teleCost = ConvertToString(teleChange[index]);
	Label* teleCos = Label::create(teleCost.c_str(),"Aril",60);
	teleCos->setPosition(size.width/2,size.height/2);
	paintNode->addChild(teleCos);
}

void lipingshangcheng_control22_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();

	auto parent = ctrl->getParent();
	String*pStr = (String*)parent->getParent()->getUserData();


	int index = atoi(pStr->getCString())+5;
	String* cost = String::createWithFormat("%d",jiangjuan[index]);
	auto teleCos = LabelBMFont::create(cost->getCString(),LpFNT);
	teleCos->setPosition(size.width/2,size.height/2+5);
	if (jiangjuan[index] == 100)
	{
		teleCos->setScale(0.78);
	}


	paintNode->addChild(teleCos);
}

void lipingshangcheng_control27_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();

	LabelTTF* chongzhilb = LabelTTF::create(GMI->getString("UIText","duihuanjilu"),"fonts/Marker Felt.ttf",30);
	chongzhilb->setPosition(477,-171);
	ctrl->addChild(chongzhilb);


}
void lipingshangcheng_control29_Paint(Node*node)
{
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();

}
void lipingshangcheng_initialize(Node* node)
{
	auto form = UIM->getForm(Form_lipingshangcheng);

	form->getControl(lipingshangcheng_control4)->registerPaintEvent(lipingshangcheng_control4_Paint);
	form->getControl(lipingshangcheng_control7)->registerPaintEvent(lipingshangcheng_control7_Paint);

	form->getControl(lipingshangcheng_control15)->registerPaintEvent(lipingshangcheng_control15_Paint);
	form->getControl(lipingshangcheng_control16)->registerPaintEvent(lipingshangcheng_control16_Paint);
	form->getControl(lipingshangcheng_control17)->registerPaintEvent(lipingshangcheng_control17_Paint);

	form->getControl(lipingshangcheng_control20)->registerPaintEvent(lipingshangcheng_control20_Paint);
	form->getControl(lipingshangcheng_control21)->registerPaintEvent(lipingshangcheng_control21_Paint);
	form->getControl(lipingshangcheng_control22)->registerPaintEvent(lipingshangcheng_control22_Paint);

	form->getControl(lipingshangcheng_control27)->registerPaintEvent(lipingshangcheng_control27_Paint);
	form->getControl(lipingshangcheng_control29)->registerPaintEvent(lipingshangcheng_control29_Paint);



	auto ctrl = form->getControl(lipingshangcheng_control10);
	UIM->setSkin(ctrl,1);

	MListView* exchange = (MListView*)form->getControl(lipingshangcheng_control12);
	exchange->clearItems();
	exchange->setItemCount(5);

	for (int i=0;i<5;i++)
	{
		MControl*item = exchange->getItem(i);
		String* pStr = String::createWithFormat("%d",i);
		pStr->retain();

		item->setUserData(pStr);

		//×¢²á14
		MControl *_item = (MControl *)item->ctrlList.at(0);
		MControl *item14 = (MControl *)_item->ctrlList.at(0);
		item14->registerTouchBeganEvent(lipingshangcheng_control14_TouchBegin);
		

		//×¢²á19
		MControl *_item1 = (MControl *)item->ctrlList.at(1);
		MControl *item19 = (MControl *)_item1->ctrlList.at(0);
		item19->registerTouchBeganEvent(lipingshangcheng_control19_TouchBegin);
	}

	int jilu_Count = 50;

	MListView *chongzhi = (MListView *)form->getControl(lipingshangcheng_control28);
	chongzhi->clearItems();
	chongzhi->setItemCount(jilu_Count);
	for (int i=0;i<jilu_Count;i++)
	{
		MControl*item = chongzhi->getItem(i);

		int *num = new int(i);
		item->setUserData(num);
	}

	//(*TouchBegan)(cocos2d::Node *control,cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
	form->getControl(lipingshangcheng_control26)->setVisible(false);

	//ÖØÖÃÑ¡Ïî¿¨;
	auto form12 =form->getControl(lipingshangcheng_control12);
	form12->setVisible(true);
	form12->setPosition(0,0);

	auto form26 =form->getControl(lipingshangcheng_control26);
	form26->setVisible(false);

	MControl* aa = form->getControl(lipingshangcheng_control10);
	UIM->setSkin(aa,1);
	MControl* bb = form->getControl(lipingshangcheng_control11);
	UIM->setSkin(bb,0);	

}
//control5
void lipingshangcheng_control5_Click(Node *node,Touch* ptouch, Event* event)
{
// 	SELF->addGold(1000);
// 
// 	auto fengmian = UIM->getForm(Form_fengmian);
// 	if(fengmian) 
// 		fengmian->getControl(fengmian_control16)->refresh();
// 
// 	auto lipinstroe = UIM->getForm(Form_lipingshangcheng);
// 	if(lipinstroe)
// 		lipinstroe->getControl(lipingshangcheng_control4)->refresh();

	UIM->closeForm((short)Form_lipingshangcheng,true);
	UIM->showForm(Form_jingbishangcheng);

	//¡Áa¦Ì??e¡À¨°¨¦¨¬3?;

}
//control8
void lipingshangcheng_control8_Click(Node *node,Touch* ptouch, Event* event)
{

}
//control9
void lipingshangcheng_control9_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->closeForm((short)Form_lipingshangcheng,true);
}
//control10
void lipingshangcheng_control10_Click(Node *node,Touch* ptouch, Event* event)
{

	auto form = UIM->getForm(Form_lipingshangcheng);
	auto form2 =form->getControl(lipingshangcheng_control12);
	form2->setVisible(true);
	form2->setPosition(0,0);

	auto form3 =form->getControl(lipingshangcheng_control26);
	form3->setVisible(false);

	MControl* aa = form->getControl(lipingshangcheng_control10);
	UIM->setSkin(aa,1);
	MControl* bb = form->getControl(lipingshangcheng_control11);
	UIM->setSkin(bb,0);	
}
//control11
void lipingshangcheng_control11_Click(Node *node,Touch* ptouch, Event* event)
{

	auto form = UIM->getForm(Form_lipingshangcheng);

	auto form2 =form->getControl(lipingshangcheng_control12);
	form2->setVisible(false);

	auto form3 =form->getControl(lipingshangcheng_control26);
	form3->setVisible(true);
	form2->setPosition(0,0);

	MControl* aa = form->getControl(lipingshangcheng_control11);
	UIM->setSkin(aa,1);
	MControl* bb = form->getControl(lipingshangcheng_control10);
	UIM->setSkin(bb,0);	
}
//control14
void lipingshangcheng_control14_Click(Node *node,Touch* ptouch, Event* event)
{
	// up exchange
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();


	UIM->showForm(Form_tongyongtishi);

// 	auto parent = ctrl->getParent();
// 	String*pStr = (String*)parent->getParent()->getUserData();
// 
// 	int index = atoi(pStr->getCString());
// 
// 	SELF->addGold(teleChange[index]);
// 
// 	auto fengmian = UIM->getForm(Form_fengmian);
// 	if(fengmian) 
// 		fengmian->getControl(fengmian_control16)->refresh();
// 
// 	auto lipinstroe = UIM->getForm(Form_lipingshangcheng);
// 	if(lipinstroe)
// 		lipinstroe->getControl(lipingshangcheng_control4)->refresh();


}
//control19
void lipingshangcheng_control19_Click(Node *node,Touch* ptouch, Event* event)
{

	// down exchange
	MControl*ctrl = (MControl*)node;
	Size size = ctrl->getSize();
	Node*paintNode = ctrl->getPaintNode();

	UIM->showForm(Form_tongyongtishi);

// 	auto parent = ctrl->getParent();
// 	String*pStr = (String*)parent->getParent()->getUserData();
// 
// 	int index = atoi(pStr->getCString())+5;
// 
// 	SELF->addGold(teleChange[index]);
// 
// 	auto fengmian = UIM->getForm(Form_fengmian);
// 	if(fengmian) 
// 		fengmian->getControl(fengmian_control16)->refresh();
// 
// 	auto lipinstroe = UIM->getForm(Form_lipingshangcheng);
// 	if(lipinstroe)
// 		lipinstroe->getControl(lipingshangcheng_control4)->refresh();
}

