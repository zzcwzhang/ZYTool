#include"UI.h"
#include "Helper.h"
#include "GameInit.h"
#include "GameManager.h"
#include "Player.h"

#define VIP_FNT "fonts/num_vip_dengji.fnt"

int GOLDpice[11] = {12,2,4,6,8,10,60,100,400,600,1000};
int GOLDcount[11] = {120000,20000,40000,60000,80000,100000,600000,1000000,4000000,6000000,10000000};
int chognzhiJY[7] = {1,100,500,1000,2000,5000,10000};

float Fanli[8] = {1.0f,1.0f,1.01f,1.02f,1.04f,1.08f,1.10f,1.15f};

//int USER_VIP_LEVEL  = 0;
float USER_VIP_PROGRESS = 00.0f;
//int USER_CHONGZHI_RMB = 0;

void jingbishangcheng_register(Node* node)
{
	UIForm *form = (UIForm*)node;
	form->getControl(jingbishangcheng_control3)->registerClickEvent(jingbishangcheng_control3_Click);
	form->getControl(jingbishangcheng_control4)->registerClickEvent(jingbishangcheng_control4_Click);
	form->getControl(jingbishangcheng_control6)->registerClickEvent(jingbishangcheng_control6_Click);
	form->getControl(jingbishangcheng_control10)->registerClickEvent(jingbishangcheng_control10_Click);
	form->getControl(jingbishangcheng_control13)->registerClickEvent(jingbishangcheng_control13_Click);
	form->getControl(jingbishangcheng_control14)->registerClickEvent(jingbishangcheng_control14_Click);
	form->getControl(jingbishangcheng_control25)->registerClickEvent(jingbishangcheng_control25_Click);
}


void jingbishangcheng_control5_Paint(Node* node)
{

	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();
	paintNode->removeAllChildren();

	int USER_CHONGZHI_RMB = SELF->getTotalCharge();
	float pros1 = 0;
	float all = 0;
	int vip = SELF->getVip();
	for (int i = 6;i>=0;i--)
	{
		if (USER_CHONGZHI_RMB>=chognzhiJY[i])
		{
			SELF->setVIP(i + 1);
			pros1 = USER_CHONGZHI_RMB-chognzhiJY[i];
			if (i!=6)
			{
				all = chognzhiJY[i+1]-chognzhiJY[i];

				USER_VIP_PROGRESS = pros1/all*100;

			}
			break;
		}
	}


	//vip???¨¨¨¬?;
	Sprite *progressSprite=Sprite::create("vipbar.png");  

	ProgressTimer* vipbar = ProgressTimer::create(progressSprite);
	vipbar->setPosition(225,8);
	vipbar->setType(kCCProgressTimerTypeBar);
	vipbar->setBarChangeRate(Point(1,0));  
	vipbar->setMidpoint(Point(0,0.5)); 


	vipbar->setPercentage(USER_VIP_PROGRESS);

	paintNode->addChild(vipbar);



	int USER_VIP_LEVEL = SELF->getVip();
	if (USER_VIP_LEVEL == 7)
	{
		vipbar->setPercentage(100);

		String* numstr = String::createWithFormat("lipinshangcheng_VIP_%d.png",USER_VIP_LEVEL-1);
		Sprite* vipNum = Sprite::create(numstr->getCString());
		vipNum->setPosition(38,10);
		paintNode->addChild(vipNum);

		String* numstr2 = String::createWithFormat("lipinshangcheng_VIP_%d.png",USER_VIP_LEVEL);
		Sprite* vipNest = Sprite::create(numstr2->getCString());
		vipNest->setPosition(478,10);
		paintNode->addChild(vipNest);
	}
	else
	{
		//??¨º?vip¦Ì¨¨??¨®???¨°?¦Ì¨¨??;
		String* numstr = String::createWithFormat("lipinshangcheng_VIP_%d.png",USER_VIP_LEVEL);
		Sprite* vipNum = Sprite::create(numstr->getCString());
		vipNum->setPosition(38,10);
		paintNode->addChild(vipNum);

		String* numstr2 = String::createWithFormat("lipinshangcheng_VIP_%d.png",USER_VIP_LEVEL+1);
		Sprite* vipNest = Sprite::create(numstr2->getCString());
		vipNest->setPosition(478,10);
		paintNode->addChild(vipNest);




	}




}

void jingbishangcheng_control6_Paint(Node* node)
{

	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();

	//String *pStr = (String *)ctrl->getUserData();
	// 	char str[60];
	// 	sprintf(str,"%s.png",pStr->getCString());
	// 	
	// 	auto gold = Sprite::create(str);
	// 	gold->setPosition(size.width/2,size.height/2);
	// 	paintNode->addChild(gold);

	int* goldn = (int *)ctrl->getUserData();
	int gn = *goldn;
	delete goldn;
	int PngNum = 0;
	if (gn==0)
	{
		PngNum = 16;
	}
	else if(gn<3)
	{
		PngNum = 14;
	}
	else if(gn<=5)
	{
		PngNum = 15;
	}
	else if(gn<=7)
	{
		PngNum = 16;
	}
	else if(gn<=9)
	{
		PngNum = 17;
	}
	else
	{
		PngNum = 18;
	}

	String* goldname = String::createWithFormat("jinbishangcheng_%d.png",PngNum);
	auto gold = Sprite::create(goldname->getCString());
	gold->setPosition(size.width/2,size.height/2);
	paintNode->addChild(gold);
	node->setTag(300+gn);

}

void jingbishangcheng_control7_Paint(Node* node)
{

	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();
	paintNode->removeAllChildren();
	//String *pStr = (String *)ctrl->getUserData();

	//?¨¢¨¨?2?¨ºy;
	int num = node->getParent()->getTag()-300;
	CastInf* caI = GData->castArray.at(num);
	int worth = caI->buyworth;
	int coin = caI->buygold;

	NumSprite* sp = NumSprite::create(worth,GameNumberStoreLayerLevel);
	sp->setScale(0.85f);
	//sp->setAnchorPoint(Vec2(1,0.5));
	sp->setPosition(size.width/2-10,size.height/2);
	paintNode->addChild(sp);

	NumSprite* goldsp = NumSprite::create(coin,GameNumberStoreLayerLevel);

	goldsp->setScale(0.75f);

	goldsp->setAnchorPoint(Vec2(0,0.5));
	goldsp->setPosition(45,30);



	Sprite* yubi = Sprite::create("worth.png");
	yubi->setPosition(-11,237);
	paintNode->addChild(yubi);

	yubi->addChild(goldsp);

	yubi->setScale((1.0-num/100.0*2.0));



}

void jingbishangcheng_control1_Paint(Node* node)
{

	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();
	paintNode->removeAllChildren();

	auto arm = Armature::create("new_3tu");
	arm->setPosition(size.width/2,size.height/2);
	arm->getAnimation()->play("jbsc_dong");
	String *pString = String::create("jbsc_dong_chixu");
	pString->retain();
	arm->setUserData(pString);
	arm->getAnimation()->setMovementEventCallFunc(arm,movementEvent_selector(UICallBack::playNextArmature));
	paintNode->addChild(arm);
}

void jingbishangcheng_control12_Paint(Node* node)
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
void jingbishangcheng_control21_Paint(Node* node)
{
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	int User_vip_level = SELF->getVip();
	int User_havepay = 0;

	UIForm* form = (UIForm*) UIM->getForm(Form_jingbishangcheng);

	auto ct22 = form->getControl(jingbishangcheng_control22);
	auto ct24 = form->getControl(jingbishangcheng_control24);
	ct22->refresh();
	ct24->refresh();

}

void jingbishangcheng_control22_Paint(Node* node)
{
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();
	int USER_VIP_LEVEL = SELF->getVip();
	String* textuiNum = String::createWithFormat("vipsign_%d",USER_VIP_LEVEL);
	LabelTTF* signlb = LabelTTF::create(GMI->getString("UIText",textuiNum->getCString()),"fonts/Marker Felt.ttf",30);
	signlb->setPosition(270,165);
	paintNode->addChild(signlb);

	String* textuiNum2 = String::createWithFormat("vipfanli_%d",USER_VIP_LEVEL);
	LabelTTF* chongzhilb = LabelTTF::create(GMI->getString("UIText",textuiNum2->getCString()),"fonts/Marker Felt.ttf",30);
	chongzhilb->setPosition(270,85);
	paintNode->addChild(chongzhilb);

	String* vipNum = String::createWithFormat("%d",USER_VIP_LEVEL);
	auto label_vip = LabelBMFont::create(vipNum->getCString(),VIP_FNT);
	label_vip->setPosition(345,265);
	paintNode->addChild(label_vip);

	if (USER_VIP_LEVEL==7)
	{
		ctrl->setPosition(425,130);

	}
}

void jingbishangcheng_control24_Paint(Node* node)
{
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	int USER_VIP_LEVEL = SELF->getVip();
	if (USER_VIP_LEVEL<7)
	{
		ctrl->setVisible(true);

		String* textuiNum = String::createWithFormat("vipsign_%d",USER_VIP_LEVEL+1);
		LabelTTF* signlb = LabelTTF::create(GMI->getString("UIText",textuiNum->getCString()),"fonts/Marker Felt.ttf",30);
		signlb->setPosition(270,165);
		paintNode->addChild(signlb);

		String* textuiNum2 = String::createWithFormat("vipfanli_%d",USER_VIP_LEVEL+1);
		LabelTTF* chongzhilb = LabelTTF::create(GMI->getString("UIText",textuiNum2->getCString()),"fonts/Marker Felt.ttf",30);
		chongzhilb->setPosition(270,85);
		paintNode->addChild(chongzhilb);

		String* vipNum2 = String::createWithFormat("%d",USER_VIP_LEVEL+1);
		auto label_vip2 = LabelBMFont::create(vipNum2->getCString(),VIP_FNT);
		label_vip2->setPosition(345,265);
		paintNode->addChild(label_vip2);

		String *leijichongzhi = String::createWithFormat(GMI->getString("UIText","leijichongzhi").c_str(),chognzhiJY[USER_VIP_LEVEL]);
		LabelTTF* ljlb = LabelTTF::create(leijichongzhi->getCString(),
			"fonts/Marker Felt.ttf",
			30);
		ljlb->setPosition(-125,205);
		ljlb->setColor(Color3B(254,255,0));
		paintNode->addChild(ljlb);


	}
	else
	{
		UIForm* form = (UIForm*) UIM->getForm(Form_jingbishangcheng);
		ctrl->setVisible(false);
		form->getControl(jingbishangcheng_control23)->setVisible(false);

	}
}

void jingbishangcheng_initialize(Node* node)
{

	UIForm* form = (UIForm*)node;
	form->getControl(jingbishangcheng_control5)->registerPaintEvent(jingbishangcheng_control5_Paint);
	form->getControl(jingbishangcheng_control6)->registerPaintEvent(jingbishangcheng_control6_Paint);
	form->getControl(jingbishangcheng_control7)->registerPaintEvent(jingbishangcheng_control7_Paint);
	form->getControl(jingbishangcheng_control1)->registerPaintEvent(jingbishangcheng_control1_Paint);
	form->getControl(jingbishangcheng_control21)->registerPaintEvent(jingbishangcheng_control21_Paint);
	form->getControl(jingbishangcheng_control12)->registerPaintEvent(jingbishangcheng_control12_Paint);
	form->getControl(jingbishangcheng_control22)->registerPaintEvent(jingbishangcheng_control22_Paint);
	form->getControl(jingbishangcheng_control24)->registerPaintEvent(jingbishangcheng_control24_Paint);
	MListView *chongzhi = (MListView *)form->getControl(jingbishangcheng_control2);
	chongzhi->clearItems();

	//zhangyuan ;
	int ItemCount = 11;
	chongzhi->setItemCount(ItemCount);
	for (int i = 0;i < ItemCount;++i)
	{
		MControl *item = chongzhi->getItem(i);
		int* goldNum = new int(i);
		item->setUserData(goldNum);

	}


	//ÖØÖÃÑ¡Ïî¿¨;
	auto form2 =form->getControl(jingbishangcheng_control2);
	form2->setVisible(true);
	auto form21 =form->getControl(jingbishangcheng_control21);
	form21->setVisible(false);

	MControl* aa = form->getControl(jingbishangcheng_control3);
	UIM->setSkin(aa,1);
	MControl* bb = form->getControl(jingbishangcheng_control4);
	UIM->setSkin(bb,0);	
}
//control3
void jingbishangcheng_control3_Click(Node *node,Touch* ptouch, Event* event)
{

	//¨®??¡¤3??¦Ì;GMI
	auto form = UIM->getForm(Form_jingbishangcheng);
	auto form2 =form->getControl(jingbishangcheng_control2);
	form2->setVisible(true);
	auto form3 =form->getControl(jingbishangcheng_control21);
	form3->setVisible(false);

	MControl* aa = form->getControl(jingbishangcheng_control3);
	UIM->setSkin(aa,1);
	MControl* bb = form->getControl(jingbishangcheng_control4);
	UIM->setSkin(bb,0);	


}
//control4
void jingbishangcheng_control4_Click(Node *node,Touch* ptouch, Event* event)
{

	//VIP
	auto form = UIM->getForm(Form_jingbishangcheng);
	auto form2 =form->getControl(jingbishangcheng_control2);
	form2->setVisible(false);
	auto form3 =form->getControl(jingbishangcheng_control21);
	form3->refresh();
	form3->setVisible(true);

	MControl* aa = form->getControl(jingbishangcheng_control4);
	UIM->setSkin(aa,1);
	MControl* bb = form->getControl(jingbishangcheng_control3);
	UIM->setSkin(bb,0);	
}
//control6
void jingbishangcheng_control6_Click(Node *node,Touch* ptouch, Event* event)
{
	/*DT??*/
	int num = node->getTag()-300;

	CastInf* caI = GData->castArray.at(num);

	int coin = caI->buygold;
	int vip = SELF->getVip();
	//log("vip %d",vip);
	float vipfanli = Fanli[vip];
	int vipCoin = coin*(vipfanli);
	//log("vipCoin %d",vipCoin);
	SELF->addGold(vipCoin);
	SELF->addTotalCharge(caI->buyworth);
	UIM->getForm(Form_jingbishangcheng)->getControl(jingbishangcheng_control5)->refresh();

	UIM->showForm(Form_tongyongtishi)->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT-50);

	showCommonDialog(GMI->getString("UIText","chongzhichenggong"));

	auto fengmian = UIM->getForm(Form_fengmian);
	if(fengmian) 
		fengmian->getControl(fengmian_control16)->refresh();
	auto jinbistroe = UIM->getForm(Form_jingbishangcheng);
	if(jinbistroe)
		jinbistroe->getControl(lipingshangcheng_control12)->refresh();
}
//control10
void jingbishangcheng_control10_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->closeForm((short)Form_jingbishangcheng,true);
	UIM->showForm(Form_lipingshangcheng);
}
//control13
void jingbishangcheng_control13_Click(Node *node,Touch* ptouch, Event* event){}
//control14
void jingbishangcheng_control14_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->closeForm((short)Form_jingbishangcheng,true);
}

void jingbishangcheng_control25_Click(Node *node,Touch* ptouch, Event* event)
{

	//¨®??¡¤3??¦Ì;GMI
	auto form = UIM->getForm(Form_jingbishangcheng);
	auto form2 =form->getControl(jingbishangcheng_control2);
	form2->setVisible(true);
	auto form3 =form->getControl(jingbishangcheng_control21);
	form3->setVisible(false);

	MControl* aa = form->getControl(jingbishangcheng_control3);
	UIM->setSkin(aa,1);
	MControl* bb = form->getControl(jingbishangcheng_control4);
	UIM->setSkin(bb,0);	
}
