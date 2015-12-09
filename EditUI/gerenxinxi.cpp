#include"UI.h"
#include "Player.h"
#include "GameManager.h"
#include "CursorTextField.h"

Gender gerenxinxi_selGender = Male;
int    gerenxinxi_headIcon = 0;

void gerenxinxi_register(Node* node)
{
UIForm *form = (UIForm*)node;
  form->getControl(gerenxinxi_control3)->registerClickEvent(gerenxinxi_control3_Click);
  form->getControl(gerenxinxi_control4)->registerClickEvent(gerenxinxi_control4_Click);
  form->getControl(gerenxinxi_control5)->registerClickEvent(gerenxinxi_control5_Click);
  form->getControl(gerenxinxi_control6)->registerClickEvent(gerenxinxi_control6_Click);
  form->getControl(gerenxinxi_control7)->registerClickEvent(gerenxinxi_control7_Click);
  form->getControl(gerenxinxi_control13)->registerClickEvent(gerenxinxi_control13_Click);
  form->getControl(gerenxinxi_control14)->registerClickEvent(gerenxinxi_control13_Click);
  form->getControl(gerenxinxi_control15)->registerClickEvent(gerenxinxi_control13_Click);
  form->getControl(gerenxinxi_control16)->registerClickEvent(gerenxinxi_control13_Click);
  form->getControl(gerenxinxi_control17)->registerClickEvent(gerenxinxi_control13_Click);
  form->getControl(gerenxinxi_control18)->registerClickEvent(gerenxinxi_control13_Click);
}

void gerenxinxi_control8_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	//¦Ì¨¨??
	auto numSprite = LabelBMFont::create(ConvertToString(SELF->getPlayGrade()),"fonts/num_shunji_shuzi.fnt");
	//numSprite->setAnchorPoint(Vec2(1.0f,0));
	numSprite->setPosition(size.width/2,size.height/2);
	numSprite->setScale(0.5f);
	paintNode->addChild(numSprite);
}

void gerenxinxi_control9_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	//3?o?
}

void gerenxinxi_control10_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;

	auto sp_progress = Sprite::create("gerenxinxi_jingyan.png");
	sp_progress->setAnchorPoint(Vec2(0,0));
	sp_progress->setPosition(0,4);

	int curScore = SELF->getScore();
	int needScore = GData->getGradeInf(SELF->getPlayGrade() - 1)->upScore;
	float rate = curScore * 1.0f / needScore;
	sp_progress->setTextureRect(Rect(0,0,sp_progress->getContentSize().width * rate,sp_progress->getContentSize().height));

	paintNode->addChild(sp_progress);
}

void gerenxinxi_control11_Paint(Node *node)
{
	//MCONTROL_INIT_REMOVEALL;
}

void gerenxinxi_control12_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;

	char tempFile[64];
	memset(tempFile,0,sizeof(tempFile));
	sprintf(tempFile,"touxiang_%d.png",gerenxinxi_headIcon + 1);
	auto headIcon = Sprite::create(tempFile);
	headIcon->setPosition(size.width/2,size.height/2);
	paintNode->addChild(headIcon);
}

void gerenxinxi_control13_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	
	int index = ctrl->id - gerenxinxi_control13;

	char tempFile[64];
	memset(tempFile,0,sizeof(tempFile));
	sprintf(tempFile,"touxiang_%d.png",index + 1);
	auto headIcon = Sprite::create(tempFile);
	headIcon->setPosition(size.width/2,size.height/2);
	paintNode->addChild(headIcon);
}

void gerenxinxi_initialize(Node* node)
{
	auto form = UIM->getForm(Form_gerenxinxi);

	form->getControl(gerenxinxi_control8)->registerPaintEvent(gerenxinxi_control8_Paint);
	form->getControl(gerenxinxi_control9)->registerPaintEvent(gerenxinxi_control9_Paint);
	form->getControl(gerenxinxi_control10)->registerPaintEvent(gerenxinxi_control10_Paint);
	form->getControl(gerenxinxi_control12)->registerPaintEvent(gerenxinxi_control12_Paint);

	for (int i = 0;i<6;i++)
	{
		form->getControl(gerenxinxi_control13 + i)->registerPaintEvent(gerenxinxi_control13_Paint);
	}

	//¨º?¨¨??¨°
	MControl *ctrl11 = form->getControl(gerenxinxi_control11);
	CursorTextField *txtField11 = CursorTextField::textFieldWithPlaceHolder(ctrl11->getPaintNode(),"", "fonts/Marker Felt.ttf",30);//,
	txtField11->setInputSize(ctrl11->getSize());
	txtField11->setPosition(Vec2(15,-2));
	txtField11->setAnchorPoint(Vec2(0,0));
	ctrl11->getPaintNode()->addChild(txtField11,1,99);

	txtField11->setInpuntText((char*)SELF->nickName.c_str());


	auto maleCtrl = form->getControl(gerenxinxi_control3);
	auto femaleCtrl = form->getControl(gerenxinxi_control4);

	UIM->setSkin(maleCtrl,0);
	UIM->setSkin(femaleCtrl,-1);

	gerenxinxi_selGender = Male;

	gerenxinxi_headIcon = GData->iconIndex;
}
//control3
void gerenxinxi_control3_Click(Node *node,Touch* ptouch, Event* event)
{
	auto form = UIM->getForm(Form_gerenxinxi);
	auto maleCtrl = form->getControl(gerenxinxi_control3);
	auto femaleCtrl = form->getControl(gerenxinxi_control4);

	UIM->setSkin(maleCtrl,0);
	UIM->setSkin(femaleCtrl,-1);

	gerenxinxi_selGender = Male;
}
//control4
void gerenxinxi_control4_Click(Node *node,Touch* ptouch, Event* event)
{
	auto form = UIM->getForm(Form_gerenxinxi);
	auto maleCtrl = form->getControl(gerenxinxi_control3);
	auto femaleCtrl = form->getControl(gerenxinxi_control4);

	UIM->setSkin(maleCtrl,-1);
	UIM->setSkin(femaleCtrl,0);

	gerenxinxi_selGender = Female;
}
//control5
void gerenxinxi_control5_Click(Node *node,Touch* ptouch, Event* event)
{
	auto form = UIM->getForm(Form_gerenxinxi);

	GData->setGender(gerenxinxi_selGender);
	GData->iconIndex = gerenxinxi_headIcon;

	auto nameField = (CursorTextField*)form->getControl(gerenxinxi_control11)->getPaintNode()->getChildByTag(99);
	SELF->nickName = nameField->getInputTextStringUTF();

	UIM->closeForm(Form_gerenxinxi,true);

	UIM->getForm(Form_fengmian)->getControl(fengmian_control9)->refresh();
	UIM->getForm(Form_fengmian)->getControl(fengmian_control11)->refresh();
}
//control6
void gerenxinxi_control6_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->closeForm(Form_gerenxinxi,false);
}
//control7
void gerenxinxi_control7_Click(Node *node,Touch* ptouch, Event* event){}
//control13
void gerenxinxi_control13_Click(Node *node,Touch* ptouch, Event* event)
{
	auto form = UIM->getForm(Form_gerenxinxi);
	auto ctrl = (MControl*)node;
	auto action1 = ScaleTo::create(0.1f,1.1f);
	auto action2 = ScaleTo::create(0.1f,1.0f);
	ctrl->stopAllActions();
	ctrl->runAction(Sequence::create(action1,action2,nullptr));

	int index = ctrl->id - gerenxinxi_control13;

	gerenxinxi_headIcon = index;
	form->getControl(gerenxinxi_control12)->refresh();
}
//control14
void gerenxinxi_control14_Click(Node *node,Touch* ptouch, Event* event){}
//control15
void gerenxinxi_control15_Click(Node *node,Touch* ptouch, Event* event){}
//control16
void gerenxinxi_control16_Click(Node *node,Touch* ptouch, Event* event){}
//control17
void gerenxinxi_control17_Click(Node *node,Touch* ptouch, Event* event){}
//control18
void gerenxinxi_control18_Click(Node *node,Touch* ptouch, Event* event){}
