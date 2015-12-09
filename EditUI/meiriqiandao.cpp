#include"UI.h"
#include "GameSocket.h"
#include "FProtocol.h"
#include "GameManager.h"
#include "Player.h"

int qiandao_signFlag = 0;

void meiriqiandao_register(Node* node)
{
UIForm *form = (UIForm*)node;
  form->getControl(meiriqiandao_control24)->registerClickEvent(meiriqiandao_control24_Click);
  form->getControl(meiriqiandao_control25)->registerClickEvent(meiriqiandao_control25_Click);
  form->getControl(meiriqiandao_control33)->registerClickEvent(meiriqiandao_control33_Click);
  form->getControl(meiriqiandao_control37)->registerClickEvent(meiriqiandao_control37_Click);
  form->getControl(meiriqiandao_control45)->registerClickEvent(meiriqiandao_control45_Click);
}


void meiriqiandao_control12_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	//date
	LabelTTF *lb_date = LabelTTF::create(GData->getDate(),"Arial",20);
	lb_date->setPosition(size.width/2,size.height/2);
	//lb_date->setColor(Color3B(0,0,0));
	paintNode->addChild(lb_date);
}

int isLeapyear(int year)/*this function is used to calculate that if a year is a leap year*/
{
	if(year%4==0)
	{
		if(year%100!=0)
			return 1;
		else if(year%100==0&&year%400==0)
			return 1;
		else
			return 0;
	}
	else
		return 0;

}

int getDaysByMonth(int year,int month)
{
	int days = 0;
	switch(month)
	{
	case 1:
		days=31;/*how many days in this month*/
		break;
	case 2:
		days=(isLeapyear(year))? 29:28;/*this is used to calculate if there are 29 or 28 days in february*/
		break;
	case 3:
		days=31;
		break;
	case 4:
		days=30;
		break;
	case 5:
		days=31;
		break;
	case 6:
		days=30;
		break;
	case 7:
		days=31;
		break;
	case 8:
		days=31;
		break;
	case 9:
		days=30;
		break;
	case 10:
		days=31;
		break;
	case 11:
		days=30;
		break;
	case 12:
		days=31;
		break;
	default:
		days=0;
		break;
	}

	return days;
}
//??¦Ì?¨¢?D???¦Ì?¨¬¨¬¨ºy
int getContinuousSign()
{
	int days = getDaysByMonth(GData->getYear(),GData->getMonth());

	int sum = 0;
	for (int i = 0;i<days;i++)
	{
		if (GData->isSigned(i))
		{
			sum++;
		}
		else
		{
			sum = 0;
		}
		if (i == GData->getDay() - 1)
		{
			break;
		}
	}

	return sum;
}
//??¦Ì?¨¤?????¦Ì?¨¬¨¬¨ºy
int getSumSign()
{
	int days = getDaysByMonth(GData->getYear(),GData->getMonth());

	int sum = 0;
	for (int i = 0;i<days;i++)
	{
		if (GData->isSigned(i))
		{
			sum++;
		}
	}

	return sum;
}

void meiriqiandao_control22_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	//¨¢?D???¦Ì?
	//LabelTTF *lb_date = LabelTTF::create(ConvertToString(getContinuousSign()),"Arial",20);
	auto lb_date = LabelBMFont::create(ConvertToString(getContinuousSign()),"fonts/num_fenmian_dengji.fnt");
	lb_date->setPosition(size.width/2,size.height/2 + 3);
	lb_date->setScale(0.8f);
	paintNode->addChild(lb_date);
}

void meiriqiandao_control23_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	//¨¤?????¦Ì?
	//LabelTTF *lb_date = LabelTTF::create(ConvertToString(getSumSign()),"Arial",20);
	auto lb_date = LabelBMFont::create(ConvertToString(getSumSign()),"fonts/num_fenmian_dengji.fnt");
	lb_date->setPosition(size.width/2,size.height/2 + 3);
	lb_date->setScale(0.8f);
	paintNode->addChild(lb_date);
}

int show_week (int year , int month , int day)
{
	int mont[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	if(isLeapyear(year))
		mont[2]=29;
	else
		mont[2]=28;
	int days = 0,s = 0,k = 0;
	for (int i=0;i<month;i++) 
		days+=mont[i];
	days+=day;

	s=year-1+(int)((year-1)/4)-(int)((year-1)/100)+(int)((year-1)/400)+days;
	k=s%7;

	return k;
}

void meiriqiandao_control46_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;

	int day = show_week(GData->getYear(),GData->getMonth(),1);
	int year = GData->getYear();
	int month = GData->getMonth();
	int days = getDaysByMonth(GData->getYear(),month);
	int i = 0;
	int headCount = 0;
	int tailCount = 0;

	headCount = day;

	tailCount = 42 - headCount - days;

	int datas[42] = {0};
	int _year = (month - 1) < 1?year-1:year;
	int _month = (month - 1) < 1?12:month-1;
	int _days = getDaysByMonth(_year,_month);
	for (i = 0;i<headCount;i++)
	{
		datas[i] =  _days - (headCount - i - 1);
	}
	for (i=0;i<days;i++)
	{
		datas[i+headCount] = i + 1;
	}
	for (i = 0;i<tailCount;i++)
	{
		datas[i+headCount+days] = i+1;
	}

	int offsetX = 42;
	int offsetY = 20;

	for (i = 0;i<42;i++)
	{
		//¡À3?¡ã
		Sprite *sp = nullptr;
		if (i < headCount || i >= 42 - tailCount)
		{
			sp = Sprite::create("sp_sign_1.png");
		}
		else
		{
			if (datas[i] == GData->getDay())
			{
				sp = Sprite::create("sp_sign_2.png");
			}
			else
			{
				sp = Sprite::create("sp_sign_0.png");
			}
		}

		sp->setPosition((i%7)*82 + offsetX,243 - (i/7)*40 - offsetY);
		paintNode->addChild(sp);

		LabelTTF *lb_date = LabelTTF::create(ConvertToString(datas[i]),"Arial",20);
		lb_date->setPosition((i%7)*82 + offsetX,243 - (i/7)*40 - offsetY);
		lb_date->setColor(Color3B(0,0,0));
		paintNode->addChild(lb_date);

		//??1y¦Ì?¦Ì?¡À¨º??
		if (i >= headCount && i < 42 - tailCount)
		{
			if (GData->isSigned(datas[i] - 1))
			{
				auto sp = Sprite::create("signed.png");
				sp->setPosition((i%7)*82 + offsetX,243 - (i/7)*40 - offsetY);
				paintNode->addChild(sp);
			}
		}
	}
}

void meiriqiandao_control38_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	LabelTTF *lb_date = LabelTTF::create(ConvertToString(GData->getSignRewardInf(6)->goldCount),"Arial",20);
	lb_date->setPosition(size.width/2,size.height/2);
	lb_date->setColor(Color3B(0,0,0));
	paintNode->addChild(lb_date);

}

void meiriqiandao_control39_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	//¨¢?D???¦Ì??¡À¨¤?
	if (qiandao_signFlag >= SEQ2 && qiandao_signFlag <= SEQ7)
	{
		LabelTTF *lb_date = LabelTTF::create(ConvertToString(GData->getSignRewardInf(qiandao_signFlag - SEQ2)->goldCount),"Arial",20);
		lb_date->setPosition(size.width/2,size.height/2);
		lb_date->setColor(Color3B(0,0,0));
		paintNode->addChild(lb_date);
	}
	else
	{
		LabelTTF *lb_date = LabelTTF::create(ConvertToString(0),"Arial",20);
		lb_date->setPosition(size.width/2,size.height/2);
		lb_date->setColor(Color3B(0,0,0));
		paintNode->addChild(lb_date);
	}

}

void meiriqiandao_control40_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;
	//¨¤?????¦Ì??¡À¨¤?
	if (qiandao_signFlag == SEQ15 && qiandao_signFlag == SEQ25)
	{
		LabelTTF *lb_date = LabelTTF::create(ConvertToString(GData->getSignRewardInf(qiandao_signFlag==SEQ15?7:8)->goldCount),"Arial",20);
		lb_date->setPosition(size.width/2,size.height/2);
		lb_date->setColor(Color3B(0,0,0));
		paintNode->addChild(lb_date);
	}
	else
	{
		LabelTTF *lb_date = LabelTTF::create(ConvertToString(0),"Arial",20);
		lb_date->setPosition(size.width/2,size.height/2);
		lb_date->setColor(Color3B(0,0,0));
		paintNode->addChild(lb_date);
	}
}

void meiriqiandao_control14_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;

	SignReward *_reward = (SignReward*)ctrl->getUserData();
	if (_reward)
	{
		//LabelTTF *lb_date = LabelTTF::create(ConvertToString(_reward->goldCount),"Arial",20);
		auto lb_date = LabelBMFont::create(ConvertToString(_reward->goldCount),"fonts/num_fenmian_dengji.fnt");
		lb_date->setPosition(size.width/2,size.height/2 + 10);
		lb_date->setScale(0.5f);
		paintNode->addChild(lb_date);

		auto sp_gold = Sprite::create("worth.png");
		sp_gold->setAnchorPoint(Vec2(0,0.5f));
		sp_gold->setPosition(size.width/2 + lb_date->getContentSize().width/2 * 0.5f,size.height/2 + 6);
		sp_gold->setScale(0.4f);
		paintNode->addChild(sp_gold);
	}
}

void meiriqiandao_control13_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;

	auto sp_txt = Sprite::create("qiandao_txt.png");
	sp_txt->setPosition(size.width/2,size.height/2);
	paintNode->addChild(sp_txt);
}

void meiriqiandao_control47_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;

	auto sp_txt = Sprite::create("qiandao_txt1.png");
	sp_txt->setAnchorPoint(Vec2(0,0));
	sp_txt->setPosition(0,10);
	sp_txt->setScale(0.7f);
	paintNode->addChild(sp_txt);
}

void meiriqiandao_initialize(Node* node)
{
	UIForm *form = (UIForm*)node;
// 	MListView *listView = (MListView*)form->getControl(meiriqiandao_control3);
// 	listView->setItemCount(5);

	form->getControl(meiriqiandao_control12)->registerPaintEvent(meiriqiandao_control12_Paint);
	form->getControl(meiriqiandao_control13)->registerPaintEvent(meiriqiandao_control13_Paint);
	form->getControl(meiriqiandao_control22)->registerPaintEvent(meiriqiandao_control22_Paint);
	form->getControl(meiriqiandao_control23)->registerPaintEvent(meiriqiandao_control23_Paint);
	form->getControl(meiriqiandao_control46)->registerPaintEvent(meiriqiandao_control46_Paint);

	form->getControl(meiriqiandao_control38)->registerPaintEvent(meiriqiandao_control38_Paint);
	form->getControl(meiriqiandao_control39)->registerPaintEvent(meiriqiandao_control39_Paint);
	form->getControl(meiriqiandao_control40)->registerPaintEvent(meiriqiandao_control40_Paint);
	form->getControl(meiriqiandao_control47)->registerPaintEvent(meiriqiandao_control47_Paint);

	form->getControl(meiriqiandao_control34)->setPosition(-500,-500);
	form->getControl(meiriqiandao_control44)->setPosition(-500,-500);

	for(int i = 0;i<8;i++)
	{
		form->getControl(meiriqiandao_control14 + i)->registerPaintEvent(meiriqiandao_control14_Paint);
	}

	form->getControl(meiriqiandao_control14)->setUserData(GData->getSignRewardInf(0));
	form->getControl(meiriqiandao_control15)->setUserData(GData->getSignRewardInf(1));
	form->getControl(meiriqiandao_control16)->setUserData(GData->getSignRewardInf(2));
	form->getControl(meiriqiandao_control17)->setUserData(GData->getSignRewardInf(3));
	form->getControl(meiriqiandao_control18)->setUserData(GData->getSignRewardInf(4));
	form->getControl(meiriqiandao_control19)->setUserData(GData->getSignRewardInf(5));
	form->getControl(meiriqiandao_control20)->setUserData(GData->getSignRewardInf(7));
	form->getControl(meiriqiandao_control21)->setUserData(GData->getSignRewardInf(8));
}
//control24

void getSignReward(int flag)
{
	SignReward *_reward = nullptr;
	int _addGold = 0;
	if (flag >= SEQ2 && flag <= SEQ7)
	{
		_reward = GData->getSignRewardInf(flag - SEQ2);
		_addGold = _reward->goldCount + GData->getSignRewardInf(6)->goldCount;
		SELF->addGold(_addGold);
	}
	else if (flag == SEQ15 || flag == SEQ25)
	{
		_reward = GData->getSignRewardInf(flag);
		_addGold = _reward->goldCount + GData->getSignRewardInf(6)->goldCount;
		SELF->addGold(_addGold);
	}
	else if (flag == NORMAL)
	{
		_addGold = GData->getSignRewardInf(6)->goldCount;
		SELF->addGold(_addGold);
	}

}

void signCBK(std::string str)
{
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();
		if(result ==  1){
			auto form = UIM->getForm(Form_meiriqiandao);

			int signFlag = p["sign"].GetInt();
			switch (signFlag)
			{
			case SIGNED:
				//¨°??-??¦Ì?1y¨¢?
				form->getControl(meiriqiandao_control44)->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);
				break;
			case FAILED:
				//??¦Ì?¨º¡ì¡ã¨¹

				break;
			default:
				//Ç©µ½³É¹¦
				SMI->playSound("qiandaojinbi.mp3",false);
				qiandao_signFlag = signFlag;
				form->getControl(meiriqiandao_control34)->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);
				getSignReward(qiandao_signFlag);
				int _data = GData->getSignData();
				GData->setSignData( _data + (1 << (GData->getDay() - 1)) );

				form->refresh();
				break;
			}

			return;
		}
	}
}

void meiriqiandao_control24_Click(Node *node,Touch* ptouch, Event* event)
{
	//??¦Ì?
	GSocket->openConnect();
	GSocket->ToSign(GData->getUserID(),signCBK);
}
//control25
void meiriqiandao_control25_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->closeForm(Form_meiriqiandao,false);
}
//control33
void meiriqiandao_control33_Click(Node *node,Touch* ptouch, Event* event){}
//control37
void meiriqiandao_control37_Click(Node *node,Touch* ptouch, Event* event)
{
	auto form = UIM->getForm(Form_meiriqiandao);
	form->getControl(meiriqiandao_control34)->setPosition(-500,-500);
}
//control45
void meiriqiandao_control45_Click(Node *node,Touch* ptouch, Event* event)
{
	auto form = UIM->getForm(Form_meiriqiandao);
	form->getControl(meiriqiandao_control44)->setPosition(-500,-500);
}
