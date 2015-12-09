#include"UI.h"
#include "GameManager.h"
#include "Player.h"
#include "GameSocket.h"
short fengmian_tabType = 1;//展开，缩进
short fengmian_shezhi = 0;

void fengmian_register(Node* node)
{
UIForm *form = (UIForm*)node;
  form->getControl(fengmian_control3)->registerClickEvent(fengmian_control3_Click);
  form->getControl(fengmian_control4)->registerClickEvent(fengmian_control4_Click);
  form->getControl(fengmian_control5)->registerClickEvent(fengmian_control5_Click);
  form->getControl(fengmian_control6)->registerClickEvent(fengmian_control6_Click);
  form->getControl(fengmian_control7)->registerClickEvent(fengmian_control7_Click);
  form->getControl(fengmian_control11)->registerClickEvent(fengmian_control11_Click);
  form->getControl(fengmian_control17)->registerClickEvent(fengmian_control17_Click);
  form->getControl(fengmian_control18)->registerClickEvent(fengmian_control18_Click);
  form->getControl(fengmian_control19)->registerClickEvent(fengmian_control19_Click);
  form->getControl(fengmian_control20)->registerClickEvent(fengmian_control20_Click);
  form->getControl(fengmian_control21)->registerClickEvent(fengmian_control21_Click);
  form->getControl(fengmian_control22)->registerClickEvent(fengmian_control22_Click);
  form->getControl(fengmian_control23)->registerClickEvent(fengmian_control23_Click);
  form->getControl(fengmian_control24)->registerClickEvent(fengmian_control24_Click);
  form->getControl(fengmian_control26)->registerClickEvent(fengmian_control26_Click);
  form->getControl(fengmian_control27)->registerClickEvent(fengmian_control27_Click);
  form->getControl(fengmian_control28)->registerClickEvent(fengmian_control28_Click);
  form->getControl(fengmian_control29)->registerClickEvent(fengmian_control29_Click);
}

void fengmian_control20_Paint(Node *node)
{
	auto ctrl = (MControl*)node;
	auto paintNode = ctrl->getPaintNode();

	if(!paintNode->getChildByTag(10))
	{
		auto size = ctrl->getSize();
		auto arm = Armature::create("icon_5");
		arm->setPosition(size.width/2,size.height/2);
		arm->getAnimation()->play("Animation1");
		paintNode->addChild(arm,0,10);
	}
}

void fengmian_control21_Paint(Node *node)
{
	auto ctrl = (MControl*)node;
	auto paintNode = ctrl->getPaintNode();

	if(!paintNode->getChildByTag(10))
	{
		auto size = ctrl->getSize();
		auto arm = Armature::create("icon");
		arm->setPosition(size.width/2,size.height/2);
		arm->getAnimation()->play("chongzhi");
		paintNode->addChild(arm,0,10);
	}
}

void fengmian_control22_Paint(Node *node)
{
	auto ctrl = (MControl*)node;
	auto paintNode = ctrl->getPaintNode();

	if(!paintNode->getChildByTag(10))
	{
		auto size = ctrl->getSize();
		auto arm = Armature::create("icon");
		arm->setPosition(size.width/2,size.height/2);
		arm->getAnimation()->play("paihang");
		paintNode->addChild(arm,0,10);
	}
}
void fengmian_control23_Paint(Node *node)
{
	auto ctrl = (MControl*)node;
	auto paintNode = ctrl->getPaintNode();

	if(!paintNode->getChildByTag(10))
	{
		auto size = ctrl->getSize();
		auto arm = Armature::create("icon");
		arm->setPosition(size.width/2,size.height/2);
		arm->getAnimation()->play("qiandao");
		paintNode->addChild(arm,0,10);
	}
}
void fengmian_control24_Paint(Node *node)
{
	auto ctrl = (MControl*)node;
	auto paintNode = ctrl->getPaintNode();

	if(!paintNode->getChildByTag(10))
	{
		auto size = ctrl->getSize();
		auto arm = Armature::create("icon");
		arm->setPosition(size.width/2,size.height/2);
		arm->getAnimation()->play("lipin");
		paintNode->addChild(arm,0,10);
	}
}

void fengmian_control15_Paint(Node *node)
{
	//金币数量
	MCONTROL_INIT_REMOVEALL;

	auto numSprite=Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(SELF->getLottery()));
	numSprite->setAnchorPoint(Vec2(1.0f,0));
	numSprite->setPosition(size.width,17);
	numSprite->setScale(0.5f);
	paintNode->addChild(numSprite);
}

void fengmian_control16_Paint(Node *node)
{
	//金币数量
	MCONTROL_INIT_REMOVEALL;

	auto numSprite=Label::createWithBMFont("fonts/num_shunji_shuzi.fnt",ConvertToString(SELF->getGold()));
	numSprite->setAnchorPoint(Vec2(1.0f,0));
	numSprite->setPosition(size.width,17);
	numSprite->setScale(0.5f);
	paintNode->addChild(numSprite);
}

void fengmian_control11_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	char tempFile[64];
	memset(tempFile,0,sizeof(tempFile));
	sprintf(tempFile,"touxiang_%d.png",GData->iconIndex + 1);
	auto headIcon = Sprite::create(tempFile);
	headIcon->setPosition(size.width/2,size.height/2);
	paintNode->addChild(headIcon);
}

void fengmian_control10_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;

	auto numSprite = LabelBMFont::create(ConvertToString(SELF->getPlayGrade()),"fonts/num_shunji_shuzi.fnt");
	numSprite->setAnchorPoint(Vec2(1.0f,0));
	numSprite->setPosition(size.width,17);
	numSprite->setScale(0.5f);
	paintNode->addChild(numSprite);
}

void fengmian_control1_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	
	auto bgLogo = Armature::create("fm_logo");
	bgLogo->setPosition(size.width/2,size.height/2+100);
	bgLogo->getAnimation()->play("Animation1");
	paintNode->addChild(bgLogo);
}

void fengmian_control2_Paint(Node*node)
{
// 	if (fengmian_tabType==0)
// 	{
// 		auto form = UIM->getForm(Form_fengmian);
// 		auto ctrl = form->getControl(fengmian_control2);
// 		ctrl->setScale(0.1f);
// 
// 		fengmian_tabType = 1;
// 	}
// 	

}

void fengmian_control25_Paint(Node*node)
{
	if (fengmian_shezhi==0)
	{
		auto form = UIM->getForm(Form_fengmian);
		auto ctrl = form->getControl(fengmian_control25);
		ctrl->setScale(0.1f);

		fengmian_shezhi = 1;
	}
}

void fengmian_control9_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	//昵称
	auto nickNameLabel = LabelTTF::create(SELF->nickName,"Arial",20);
	nickNameLabel->setPosition(size.width/2,size.height/2);
	paintNode->addChild(nickNameLabel);
}

void fengmian_control12_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	//经验条
	auto sp = Sprite::create("grade_pro.png");
	sp->setAnchorPoint(Vec2(0,0));
	sp->setPosition(-12,-2);
	int curScore = SELF->getScore();
	int needScore = GData->getGradeInf(SELF->getPlayGrade() - 1)->upScore;
	float rate = curScore * 1.0f / needScore;
	sp->setTextureRect(Rect(0,0,sp->getContentSize().width * rate,sp->getContentSize().height));

	paintNode->addChild(sp);
}

void fengmian_initialize(Node* node)
{
	auto form = UIM->getForm(Form_fengmian);
	form->getControl(fengmian_control21)->registerPaintEvent(fengmian_control21_Paint);
	form->getControl(fengmian_control22)->registerPaintEvent(fengmian_control22_Paint);
	form->getControl(fengmian_control23)->registerPaintEvent(fengmian_control23_Paint);
	form->getControl(fengmian_control24)->registerPaintEvent(fengmian_control24_Paint);
	form->getControl(fengmian_control20)->registerPaintEvent(fengmian_control20_Paint);
	form->getControl(fengmian_control16)->registerPaintEvent(fengmian_control16_Paint);
	form->getControl(fengmian_control15)->registerPaintEvent(fengmian_control15_Paint);
	form->getControl(fengmian_control9)->registerPaintEvent(fengmian_control9_Paint);
	form->getControl(fengmian_control10)->registerPaintEvent(fengmian_control10_Paint);
	form->getControl(fengmian_control11)->registerPaintEvent(fengmian_control11_Paint);
	form->getControl(fengmian_control12)->registerPaintEvent(fengmian_control12_Paint);
	form->getControl(fengmian_control1)->registerPaintEvent(fengmian_control1_Paint);
	form->getControl(fengmian_control2)->registerPaintEvent(fengmian_control2_Paint);
	form->getControl(fengmian_control25)->registerPaintEvent(fengmian_control25_Paint);

	auto ctrl = form->getControl(fengmian_control2);
	ctrl->setScale(0.1f);

	//判断显示登陆
	//UIM->showForm(Form_dengluchuangkou);
	if (!GData->isLogin())
	{
		auto action1 = DelayTime::create(0.2f);
		auto action2 = CallFunc::create(form,callfunc_selector(UICallBack::showLogin));

		form->runAction(Sequence::create(action1,action2,nullptr));
	}
	
}
//control3
void fengmian_control3_Click(Node *node,Touch* ptouch, Event* event){}
//control4
void fengmian_control4_Click(Node *node,Touch* ptouch, Event* event){}
//control5
void fengmian_control5_Click(Node *node,Touch* ptouch, Event* event){}
//control6
void fengmian_control6_Click(Node *node,Touch* ptouch, Event* event){}
//control7
void fengmian_control7_Click(Node *node,Touch* ptouch, Event* event)
{
	auto form = UIM->getForm(Form_fengmian);

	auto ctrl = form->getControl(fengmian_control2);
	auto curCtrl = (MControl*)node;
	ctrl->stopAllActions();
	if (fengmian_tabType == 0)
	{
		//缩进
		auto scaleTo = ScaleTo::create(0.15f,0.1f);
		ctrl->runAction(scaleTo);
		fengmian_tabType = 1;

		curCtrl->setRotation(0);
	}
	else
	{
		//展开
		auto action1 = ScaleTo::create(0.1f,1.2f);
		auto action2 = ScaleTo::create(0.1f,0.9f);
		auto action3 = ScaleTo::create(0.1f,1.0f);
		ctrl->runAction(Sequence::create(action1,action2,action3,nullptr));
		fengmian_tabType = 0;
		curCtrl->setRotation(180);
	}

	curCtrl->stopAllActions();
	curCtrl->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	curCtrl->runAction(Sequence::create(cAction1,cAction2,nullptr));
}
//control11
void fengmian_control11_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->showForm(Form_gerenxinxi);
}
//control17
void fengmian_control17_Click(Node *node,Touch* ptouch, Event* event){}
//control18
void fengmian_control18_Click(Node *node,Touch* ptouch, Event* event)
{
	SELF->addGold(1000);
	UIM->getForm(Form_fengmian)->getControl(fengmian_control16)->refresh();
}
//control19
void fengmian_control19_Click(Node *node,Touch* ptouch, Event* event)
{
	//单人模式
	auto curForm = UIM->getForm(Form_fengmian);
	auto nextForm = UIM->getForm(Form_danrenmoshixuanguan);
	if (!nextForm || !nextForm->isActive())
	{
		nextForm = UIM->showForm(Form_danrenmoshixuanguan);
	}
	nextForm->setVisible(true);
	nextForm->setEnabled(true);
	nextForm->setPosition(-SCREEN_WIDTH/2,SCREEN_HALF_HEIGHT);

	auto curMove = MoveTo::create(0.2f,Vec2(SCREEN_WIDTH * 1.5f,SCREEN_HALF_HEIGHT));
	curForm->stopAllActions();
	curForm->runAction(curMove);

	auto nextMove = MoveTo::create(0.2f,Vec2(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT));
	nextForm->stopAllActions();
	nextForm->runAction(nextMove);

// 	GSocket->openConnect();
// 	GSocket->SaveData(GData->getUserID(),10,1,10000,0,0,0,1,1,nullptr);
}
//control20
void fengmian_control20_Click(Node *node,Touch* ptouch, Event* event)
{
	//联网点击

	if (!GData->isLogin())
	{
		std::string tempStr = GMI->getString("UIText","LoginFirst");
		showCommonDialog(tempStr);
		return;
	}

	auto curForm = UIM->getForm(Form_fengmian);
	auto nextForm = UIM->getForm(Form_duorenmoshixuanguan);
	if (!nextForm || !nextForm->isActive())
	{
		nextForm = UIM->showForm(Form_duorenmoshixuanguan);
	}
	nextForm->setEnabled(true);
	nextForm->setPosition(SCREEN_WIDTH * 1.5f,SCREEN_HALF_HEIGHT);

	auto curMove = MoveTo::create(0.2f,Vec2(-SCREEN_WIDTH/2,SCREEN_HALF_HEIGHT));
	
	curForm->runAction(curMove);

	auto nextMove = MoveTo::create(0.2f,Vec2(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT));
	
	nextForm->runAction(nextMove);
}
//control21
void fengmian_control21_Click(Node *node,Touch* ptouch, Event* event)
{
	//充值
 	auto ctrl = (MControl*)node;
 	ctrl->stopAllActions();
 	ctrl->setScale(1.0f);
 	auto cAction1 = ScaleTo::create(0.1f,1.1f);
 	auto cAction2 = ScaleTo::create(0.1f,1.0f);
 	ctrl->runAction(Sequence::create(cAction1,cAction2,nullptr));
 
 	UIM->showForm(Form_jingbishangcheng);
}

//control22
void fengmian_control22_Click(Node *node,Touch* ptouch, Event* event)
{
	//排行榜
 	auto ctrl = (MControl*)node;
 	ctrl->stopAllActions();
 	ctrl->setScale(1.0f);
 	auto cAction1 = ScaleTo::create(0.1f,1.1f);
 	auto cAction2 = ScaleTo::create(0.1f,1.0f);
 	ctrl->runAction(Sequence::create(cAction1,cAction2,nullptr));
 
 	UIM->showForm(Form_paihangbang);
}
//control23
void fengmian_control23_Click(Node *node,Touch* ptouch, Event* event)
{
	//每日签到
	auto ctrl = (MControl*)node;
	ctrl->stopAllActions();
	ctrl->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	ctrl->runAction(Sequence::create(cAction1,cAction2,nullptr));

	//判断能不能签到
	if (GData->isLogin())
	{
		UIM->showForm(Form_meiriqiandao);
	}
	else
	{
		std::string tempStr = GMI->getString("UIText","LoginFirst");
		showCommonDialog(tempStr);
	}
	
}
//control24
void fengmian_control24_Click(Node *node,Touch* ptouch, Event* event)
{
	//礼品商城
 	auto ctrl = (MControl*)node;
 	ctrl->stopAllActions();
 	ctrl->setScale(1.0f);
 	auto cAction1 = ScaleTo::create(0.1f,1.1f);
 	auto cAction2 = ScaleTo::create(0.1f,1.0f);
 	ctrl->runAction(Sequence::create(cAction1,cAction2,nullptr));

	UIM->showForm(Form_lipingshangcheng);
}

//control26
void fengmian_control26_Click(Node *node,Touch* ptouch, Event* event){}
//control27
void fengmian_control27_Click(Node *node,Touch* ptouch, Event* event){}
//control28
void fengmian_control28_Click(Node *node,Touch* ptouch, Event* event){}
//control29
void fengmian_control29_Click(Node *node,Touch* ptouch, Event* event)
{
	auto form = UIM->getForm(Form_fengmian);

	auto ctrl = form->getControl(fengmian_control25);
	ctrl->stopAllActions();
	if (fengmian_shezhi == 0)
	{
		//缩进
		auto scaleTo = ScaleTo::create(0.15f,0.1f);
		ctrl->runAction(scaleTo);
		fengmian_shezhi = 1;
	}
	else
	{
		//展开
		auto action1 = ScaleTo::create(0.1f,1.2f);
		auto action2 = ScaleTo::create(0.1f,0.9f);
		auto action3 = ScaleTo::create(0.1f,1.0f);
		ctrl->runAction(Sequence::create(action1,action2,action3,nullptr));
		fengmian_shezhi = 0;
	}

	auto curCtrl = (MControl*)node;
	curCtrl->stopAllActions();
	curCtrl->setScale(1.0f);
	auto cAction1 = ScaleTo::create(0.1f,1.1f);
	auto cAction2 = ScaleTo::create(0.1f,1.0f);
	curCtrl->runAction(Sequence::create(cAction1,cAction2,nullptr));
}