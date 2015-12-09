#include"UI.h"
#include "CursorTextField.h"
#include "netHelpT.h"
#include "Player.h"
#include "GameManager.h"
#include "GameDataManager.h"
Gender curSelGender = Male;

void refreshPlayerInf()
{
	auto form = UIM->getForm(Form_fengmian);

	form->getControl(fengmian_control9)->refresh();
	form->getControl(fengmian_control10)->refresh();
	form->getControl(fengmian_control11)->refresh();
	form->getControl(fengmian_control12)->refresh();
	form->getControl(fengmian_control15)->refresh();
	form->getControl(fengmian_control16)->refresh();
}

void dengluchuangkou_register(Node* node)
{
UIForm *form = (UIForm*)node;
  form->getControl(dengluchuangkou_control3)->registerClickEvent(dengluchuangkou_control3_Click);
  form->getControl(dengluchuangkou_control4)->registerClickEvent(dengluchuangkou_control4_Click);
  form->getControl(dengluchuangkou_control7)->registerClickEvent(dengluchuangkou_control7_Click);
  form->getControl(dengluchuangkou_control8)->registerClickEvent(dengluchuangkou_control8_Click);
  form->getControl(dengluchuangkou_control9)->registerClickEvent(dengluchuangkou_control9_Click);
  form->getControl(dengluchuangkou_control11)->registerClickEvent(dengluchuangkou_control11_Click);
  form->getControl(dengluchuangkou_control13)->registerClickEvent(dengluchuangkou_control13_Click);
  form->getControl(dengluchuangkou_control14)->registerClickEvent(dengluchuangkou_control14_Click);
  form->getControl(dengluchuangkou_control20)->registerClickEvent(dengluchuangkou_control20_Click);
}

void dengluchuangkou_initialize(Node* node)
{
	UIForm *form = (UIForm*)node;
	//输入框
	MControl *ctrl18 = form->getControl(dengluchuangkou_control18);
	std::string tipStr = GMI->getString("UIText","InputUserNameTip");
	CursorTextField *txtField18 = CursorTextField::textFieldWithPlaceHolder(ctrl18->getPaintNode(),tipStr.c_str(), "fonts/Marker Felt.ttf",30);//,
	txtField18->setInputSize(ctrl18->getSize());
	txtField18->setPosition(Vec2(15,-2));
	txtField18->setAnchorPoint(Vec2(0,0));
	ctrl18->getPaintNode()->addChild(txtField18,1,99);
	
	

	MControl *ctrl19 = form->getControl(dengluchuangkou_control19);
	tipStr = GMI->getString("UIText","InputPswdTip");
	CursorTextField *txtField19 = CursorTextField::textFieldWithPlaceHolder(ctrl19->getPaintNode(),tipStr.c_str(), "fonts/Marker Felt.ttf",30);//,
	txtField19->setInputSize(ctrl19->getSize());
	txtField19->setPosition(Vec2(15,-2));
	txtField19->setAnchorPoint(Vec2(0,0));
	ctrl19->getPaintNode()->addChild(txtField19,1,99);



	MControl *ctrl15 = form->getControl(dengluchuangkou_control15);
	tipStr = GMI->getString("UIText","InputUserNameTip");
	CursorTextField *txtField15 = CursorTextField::textFieldWithPlaceHolder(ctrl15->getPaintNode(),tipStr.c_str(), "fonts/Marker Felt.ttf",30);//,
	txtField15->setInputSize(ctrl15->getSize());
	txtField15->setPosition(Vec2(15,-2));
	txtField15->setAnchorPoint(Vec2(0,0));
	ctrl15->getPaintNode()->addChild(txtField15,1,99);

	MControl *ctrl16 = form->getControl(dengluchuangkou_control16);
	tipStr = GMI->getString("UIText","InputPswdTip");
	CursorTextField *txtField16 = CursorTextField::textFieldWithPlaceHolder(ctrl16->getPaintNode(),tipStr.c_str(), "fonts/Marker Felt.ttf",30);//,
	txtField16->setInputSize(ctrl16->getSize());
	txtField16->setPosition(Vec2(15,-2));
	txtField16->setAnchorPoint(Vec2(0,0));
	ctrl16->getPaintNode()->addChild(txtField16,1,99);


	MControl *ctrl17 = form->getControl(dengluchuangkou_control17);
	tipStr = GMI->getString("UIText","InputPswdSureTip");
	CursorTextField *txtField17 = CursorTextField::textFieldWithPlaceHolder(ctrl17->getPaintNode(),tipStr.c_str(), "fonts/Marker Felt.ttf",30);//,
	txtField17->setInputSize(ctrl17->getSize());
	txtField17->setPosition(Vec2(15,-2));
	txtField17->setAnchorPoint(Vec2(0,0));
	ctrl17->getPaintNode()->addChild(txtField17,1,99);

	std::string ss="";
	if(SELF->nickName.compare("") == 0)
	{
		int index = getRandom(GData->familyNameArray.size());
		ss += GData->getFamilyName(index);
		index = getRandom(GData->maleNameArray.size());
		ss += GData->getMaleName(index);

		//form->getControl(denglu_control6)->setVisible(false);
	}
	else
	{
		//form->getControl(denglu_control6)->setVisible(true);
		ss = SELF->nickName;
	}

	MControl *ctrl21 = form->getControl(dengluchuangkou_control21);
	CursorTextField *txtField21 = CursorTextField::textFieldWithPlaceHolder(ctrl21->getPaintNode(),ss.c_str(), "fonts/Marker Felt.ttf",30);//,
	txtField21->setInputSize(ctrl21->getSize());
	txtField21->setPosition(Vec2(15,-2));
	txtField21->setAnchorPoint(Vec2(0,0));
	txtField21->setInpuntText((char*)ss.c_str());
	ctrl21->getPaintNode()->addChild(txtField21,1,99);

	//显示哪个窗口
	auto ctrl12 = form->getControl(dengluchuangkou_control12);
	auto ctrl2 = form->getControl(dengluchuangkou_control2);
	auto ctrl10 = form->getControl(dengluchuangkou_control10);

	//ctrl12->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);
	ctrl12->setPosition(SCREEN_HALF_WIDTH,800);
	ctrl12->stopAllActions();
	auto action1 = MoveTo::create(0.2f,Vec2(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT - 50));
	auto action2 = MoveTo::create(0.1f,Vec2(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT));
	ctrl12->runAction(Sequence::create(action1,action2,nullptr));

	ctrl2->setPosition(-500,-500);
	ctrl10->setPosition(-500,-500);

	auto maleCtrl = form->getControl(dengluchuangkou_control3);
	auto femaleCtrl = form->getControl(dengluchuangkou_control4);

	if(SELF->getSex() == 0)
	{
		UIM->setSkin(maleCtrl,0);
		UIM->setSkin(femaleCtrl,-1);
	}
	else
	{
		UIM->setSkin(maleCtrl,1);
		UIM->setSkin(femaleCtrl,0);
	}
	
	curSelGender = Male;
}
//control3
void dengluchuangkou_control3_Click(Node *node,Touch* ptouch, Event* event)
{
	auto form = UIM->getForm(Form_dengluchuangkou);
	auto maleCtrl = form->getControl(dengluchuangkou_control3);
	auto femaleCtrl = form->getControl(dengluchuangkou_control4);

	UIM->setSkin(maleCtrl,0);
	UIM->setSkin(femaleCtrl,-1);

	curSelGender = Male;
}
//control4
void dengluchuangkou_control4_Click(Node *node,Touch* ptouch, Event* event)
{
	auto form = UIM->getForm(Form_dengluchuangkou);
	auto maleCtrl = form->getControl(dengluchuangkou_control3);
	auto femaleCtrl = form->getControl(dengluchuangkou_control4);

	UIM->setSkin(maleCtrl,-1);
	UIM->setSkin(femaleCtrl,0);

	curSelGender = Female;
}
//control7
void dengluchuangkou_control7_Click(Node *node,Touch* ptouch, Event* event)
{
	std::string ss = "";
	if(curSelGender == Male)
	{
		int index = getRandom(GData->familyNameArray.size());
		ss += GData->getFamilyName(index);
		index = getRandom(GData->maleNameArray.size());
		ss += GData->getMaleName(index);
	}
	else
	{
		int index = getRandom(GData->familyNameArray.size());
		ss += GData->getFamilyName(index);
		index = getRandom(GData->femaleNameArray.size());
		ss += GData->getFemaleName(index);
	}

	UIForm *form = UIM->getForm(Form_dengluchuangkou);
	MControl *ctrl21 = form->getControl(dengluchuangkou_control21);
	CursorTextField *txtField21 = (CursorTextField*)ctrl21->getPaintNode()->getChildByTag(99);
	txtField21->setInpuntText((char*)ss.c_str());
}
//control8
void dengluchuangkou_control8_Click(Node *node,Touch* ptouch, Event* event){
	//注册
	auto form = UIM->getForm(Form_dengluchuangkou);


	auto curForm = form->getControl(dengluchuangkou_control12);
	auto nextForm = form->getControl(dengluchuangkou_control10);

	curForm->setPosition(-500,-500);
	nextForm->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);

// 	if(curForm->isVisible()){
// 		curForm->setVisible(false);
// 		curForm->setEnabled(false);
// 	}
// 	nextForm->setVisible(true);
// 	nextForm->setEnabled(true);

	
	//nextForm->setPosition(-SCREEN_WIDTH/2,SCREEN_HALF_HEIGHT);

	/*auto curMove = MoveTo::create(0.2f,Vec2(SCREEN_WIDTH * 1.5f,SCREEN_HALF_HEIGHT));
	curForm->stopAllActions();
	curForm->runAction(curMove);

	auto nextMove = MoveTo::create(0.2f,Vec2(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT));
	nextForm->stopAllActions();
	nextForm->runAction(nextMove);*/

}
//control9
void dengluchuangkou_control9_Click(Node *node,Touch* ptouch, Event* event)
{
	auto form = UIM->getForm(Form_dengluchuangkou);

	auto ctrl21 = form->getControl(dengluchuangkou_control21);
	CursorTextField *txtField21 = (CursorTextField*)(ctrl21->getPaintNode()->getChildByTag(99));
	std::string  nickName = txtField21->getInputTextStringUTF();

	//检查昵称
	if (nickName.compare("")==0)
	{
		std::string tempStr = GMI->getString("UIText","NickNameNotNull");
		showCommonDialog(tempStr);
		return;
	}

	SELF->nickName = nickName;
	//GData->setNickName(nickName);
	SELF->setSex(curSelGender);
	GData->setGender(curSelGender);

	UIM->closeForm(Form_dengluchuangkou,true);

	refreshPlayerInf();
}



void registerCB(std::string str)
{
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();
		if(result ==  1){
			//注册成功
			auto form = UIM->getForm(Form_dengluchuangkou);


			auto curForm = form->getControl(dengluchuangkou_control10);
			auto nextForm = form->getControl(dengluchuangkou_control12);
			curForm->setPosition(-500,-500);
			nextForm->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);
// 			if(curForm->isVisible()){
// 				curForm->setVisible(false);
// 				curForm->setEnabled(false);
// 			}
// 			nextForm->setVisible(true);
// 			nextForm->setEnabled(true);


			return;
		}
	}
}
//control11
void dengluchuangkou_control11_Click(Node *node,Touch* ptouch, Event* event){
	//立即注册
	auto form = UIM->getForm(Form_dengluchuangkou);
	MControl *ctrl15 = form->getControl(dengluchuangkou_control15);
	MControl *ctrl16 = form->getControl(dengluchuangkou_control16);
	MControl *ctrl17 = form->getControl(dengluchuangkou_control17);

	CursorTextField *txtField15 = (CursorTextField*)(ctrl15->getPaintNode()->getChildByTag(99));
	CursorTextField *txtField16 = (CursorTextField*)(ctrl16->getPaintNode()->getChildByTag(99));
	CursorTextField *txtField17 = (CursorTextField*)(ctrl17->getPaintNode()->getChildByTag(99));
	std::string  username = txtField15->getInputTextStringUTF();
	std::string  password = txtField16->getInputTextStringUTF();
	std::string  password_c = txtField17->getInputTextStringUTF();

	if(username == ""){
		//用户名为空
		log("%s","username is null");
		return;
	}

	if (password == "")
	{
		//密码为空
		log("%s","password is null");
		return;
	}
	if (password_c == "")
	{
		//确认密码为空
		log("%s","password_c is null");
		return;
	}

	if (password != password_c)
	{
		//两次密码不一致
		log("%s","two password is error");
		return;
	}

	if (password == password_c)
	{
		//正常注册
		log("%s","success");
		GSocket->openConnect();
		GSocket->ToRegister(username,password,registerCB);
		return;
	}


}

void loginCB(std::string str)
{
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();
		if(result ==  1){
			//登录成功
			if (SELF->nickName.compare("") == 0)
			{
				auto form = UIM->getForm(Form_dengluchuangkou);
				auto curForm = form->getControl(dengluchuangkou_control12);
				auto nextForm = form->getControl(dengluchuangkou_control2);
				curForm->setPosition(-500,-500);
				nextForm->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);
			}
			else
			{
				UIM->closeForm(Form_dengluchuangkou,true);
			}

			/*******用户数据**********/
			SELF->setGold(p["coin"].GetInt());	//金币
			SELF->setLottery(p["ticket"].GetInt());	//奖券
			SELF->setScore(p["fishScore"].GetInt());		//分数？
			SELF->setLvl(p["level"].GetInt());		//关卡
			SELF->setPlayGrade(1);	//玩家等级
			/************************/

			//获得日期
			std::string _date = p["Date"].GetString();
			GData->setDate(_date);
			//获得用户ID
			int _id = p["userId"].GetInt();
			GData->setUserID(_id);
			//签到数据
			int _signData = p["signData"].GetInt();
			GData->setSignData(_signData);
			//登陆成功
			GData->setLogin(true);
			return;
		}
		else
		{
			std::string tempStr = GMI->getString("UIText","LoginFaild");
			showCommonDialog(tempStr);
		}

	}
}

//control13
void dengluchuangkou_control13_Click(Node *node,Touch* ptouch, Event* event){
	//账号登录
	auto form = UIM->getForm(Form_dengluchuangkou);
	MControl *ctrl18 = form->getControl(dengluchuangkou_control18);
	MControl *ctrl19 = form->getControl(dengluchuangkou_control19);
	//ctrl18->setVisible(false);
	CursorTextField *txtField18 = (CursorTextField*)(ctrl18->getPaintNode()->getChildByTag(99));
	CursorTextField *txtField19 = (CursorTextField*)(ctrl19->getPaintNode()->getChildByTag(99));
	std::string  username = txtField18->getInputTextStringUTF();
	std::string  password = txtField19->getInputTextStringUTF();


	if (username == "")
	{
		//用户名为空
		log("%s","username is null");
		std::string tempStr = GMI->getString("UIText","UserNameNotNull");
		showCommonDialog(tempStr);
		return;
	}

	if(password == ""){
		//密码为空
		log("%s","password is null");
		std::string tempStr = GMI->getString("UIText","PswdNotNull");
		showCommonDialog(tempStr);
		return;
	}

	log("username =%s",username.c_str());
	log("password =%s",password.c_str());

	//监测登陆合法性

	GSocket->openConnect();
	GSocket->ToLogin(username,password,loginCB);
	
}


//control14
void dengluchuangkou_control14_Click(Node *node,Touch* ptouch, Event* event){
	//游客登录

	//设置游客属性
	auto form = UIM->getForm(Form_dengluchuangkou);
	auto curForm = form->getControl(dengluchuangkou_control12);
	auto nextForm = form->getControl(dengluchuangkou_control2);
	curForm->setPosition(-500,-500);
	nextForm->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);
    
	//UIM->closeForm(Form_dengluchuangkou,false);
	/*******用户数据**********/
	SELF->setGold(1000);	//金币
	SELF->setLottery(0);	//奖券
	SELF->setScore(0);		//分数？
	SELF->setLvl(1);		//关卡
	SELF->setPlayGrade(1);	//玩家等级
	/************************/
}

void dengluchuangkou_control20_Click(Node *node,Touch* ptouch, Event* event){
	//注册返回

	auto form = UIM->getForm(Form_dengluchuangkou);


	auto curForm = form->getControl(dengluchuangkou_control10);
	auto nextForm = form->getControl(dengluchuangkou_control12);
	curForm->setPosition(-500,-500);
	nextForm->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);
// 	if(curForm->isVisible()){
// 		curForm->setVisible(false);
// 		curForm->setEnabled(false);
// 	}
// 	nextForm->setVisible(true);
// 	nextForm->setEnabled(true);
}

