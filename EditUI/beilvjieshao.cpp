#include"UI.h"
#include "Fish.h"
int FishIndex[7][5] = {
	{0 ,1 ,2 ,3 ,4 },
	{5 ,6 ,7 ,8 ,9 },
	{10,11,12,13,14},
	{15,16,17,18,19},
	{20,21,22,23,24},
	{25,26,27,28,29},
	{30,0 ,0 ,0 ,0}	
};

int beilvIndex[7][5] = {
	{2 ,3  ,4  ,5  ,8  },
	{6 ,7  ,9  ,10 ,11 },
	{12,15 ,20 ,15 ,25 },
	{30,35 ,18 ,18 ,18 },
	{6 ,12 ,40 ,50 ,30 },
	{35,150,130,140,100},
	{160,0  ,0  ,0  ,0}
};

const char* getFishName(int x,int y)
{
	int index = FishIndex[x][y];
	FishInf* finf = GData->fishInfArray.at(index);
	return finf->fishname.c_str();

	
}
void beilvjieshao_register(Node* node)
{
  UIForm *form = (UIForm*)node;
  form->getControl(beilvjieshao_control3)->registerClickEvent(beilvjieshao_control3_Click);
}

int nameIndex = 0;
void beilvjieshao_control7_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();

	String *pStr = (String *)ctrl->getParent()->getUserData();
	log("7%s",pStr->getCString());

	char str[60];
	sprintf(str,"%s_0.png",getFishName(nameIndex,0));
	//auto sp = Sprite::createWithSpriteFrameName(str);
	auto sp= Fish::createFishshadow((Fish::FishType)FishIndex[nameIndex][0]);
	sp->doshadowFishLifeAnimation();
	sp->setOpacity(255);
	sp->setColor(ccc3(255,255,255));
	String* ls = String::createWithFormat("X %d",beilvIndex[nameIndex][0]);
	auto label = LabelTTF::create(ls->getCString(),"fonts/arial.ttf",24);

	if (strcmp(pStr->getCString(),"0")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"1")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		sp->setScale(0.5f);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"2")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		sp->setScale(0.45f);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"3")==0)
	{
		sp->setPosition(size.width/2-15,size.height/2+10);
		sp->setScale(0.35f);
		label->setPosition(size.width/2-15,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"4")==0)
	{
		sp->setPosition(size.width/2-15,size.height/2+10);
		sp->setScale(0.7f);
		label->setPosition(size.width/2-15,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"5")==0)
	{
		sp->setPosition(size.width/2-15,size.height/2+10);
		sp->setScale(0.25f);
		label->setPosition(size.width/2-15,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"6")==0)
	{
		sp->setPosition(size.width/2-15,size.height/2+10);
		sp->setScale(0.20f);
		label->setPosition(size.width/2-15,size.height/2-30);
	}
	sp->setRotation(90);
	paintNode->addChild(sp);

	paintNode->addChild(label);
}

void beilvjieshao_control8_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();

	String *pStr = (String *)ctrl->getParent()->getUserData();

	if (strcmp(pStr->getCString(),"6")==0) return ;

	char str[60];
	sprintf(str,"%s_0.png",getFishName(nameIndex,1));
	//auto sp = Sprite::createWithSpriteFrameName(str);
	auto sp= Fish::createFishshadow((Fish::FishType)FishIndex[nameIndex][1]);
	sp->doshadowFishLifeAnimation();
	sp->setOpacity(255);
	sp->setColor(ccc3(255,255,255));

	String* ls = String::createWithFormat("X %d",beilvIndex[nameIndex][1]);
	auto label = LabelTTF::create(ls->getCString(),"fonts/arial.ttf",24);

	if (strcmp(pStr->getCString(),"0")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"1")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		sp->setScale(0.75f);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"2")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		sp->setScale(0.4f);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"3")==0)
	{
		sp->setPosition(size.width/2-15,size.height/2+10);
		sp->setScale(0.45f);
		label->setPosition(size.width/2-15,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"4")==0)
	{
		sp->setPosition(size.width/2-15,size.height/2+10);
		sp->setScale(0.45f);
		label->setPosition(size.width/2-15,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"5")==0)
	{
		sp->setPosition(size.width/2-15,size.height/2+10);
		sp->setScale(0.45f);
		label->setPosition(size.width/2-15,size.height/2-30);
	}
	
	sp->setRotation(90);
	paintNode->addChild(sp);

	paintNode->addChild(label);
}

void beilvjieshao_control9_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();

	String *pStr = (String *)ctrl->getParent()->getUserData();
	//log("9%s",pStr->getCString());
	if (strcmp(pStr->getCString(),"6")==0) return ;

	char str[60];
	sprintf(str,"%s_0.png",getFishName(nameIndex,2));
	//auto sp = Sprite::createWithSpriteFrameName(str);
	auto sp= Fish::createFishshadow((Fish::FishType)FishIndex[nameIndex][2]);
	sp->doshadowFishLifeAnimation();
	sp->setOpacity(255);
	sp->setColor(ccc3(255,255,255));

	String* ls = String::createWithFormat("X %d",beilvIndex[nameIndex][2]);
	auto label = LabelTTF::create(ls->getCString(),"fonts/arial.ttf",24);

	if (strcmp(pStr->getCString(),"0")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"1")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		sp->setScale(0.75f);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"2")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		sp->setScale(0.45f);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"3")==0)
	{
		sp->setPosition(size.width/2-10,size.height/2+10);
		sp->setScale(0.45f);
		label->setPosition(size.width/2-10,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"4")==0)
	{
		sp->setPosition(size.width/2-10,size.height/2+10);
		sp->setScale(0.45f);
		label->setPosition(size.width/2-10,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"5")==0)
	{
		sp->setPosition(size.width/2-15,size.height/2+10);
		sp->setScale(0.45f);
		label->setPosition(size.width/2-15,size.height/2-30);
	}

	sp->setRotation(90);
	paintNode->addChild(sp);

	paintNode->addChild(label);
}

void beilvjieshao_control10_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();

	String *pStr = (String *)ctrl->getParent()->getUserData();
	//log("10%s",pStr->getCString());
	if (strcmp(pStr->getCString(),"6")==0) return ;

	char str[60];
	sprintf(str,"%s_0.png",getFishName(nameIndex,3));
	//auto sp = Sprite::createWithSpriteFrameName(str);
	auto sp= Fish::createFishshadow((Fish::FishType)FishIndex[nameIndex][3]);
	sp->doshadowFishLifeAnimation();
	sp->setOpacity(255);
	sp->setColor(ccc3(255,255,255));

	String* ls = String::createWithFormat("X %d",beilvIndex[nameIndex][3]);
	auto label = LabelTTF::create(ls->getCString(),"fonts/arial.ttf",24);

	if (strcmp(pStr->getCString(),"0")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"1")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		sp->setScale(0.75f);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"2")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		sp->setScale(0.45f);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"3")==0)
	{
		sp->setPosition(size.width/2-10,size.height/2+10);
		sp->setScale(0.55f);
		label->setPosition(size.width/2-10,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"4")==0)
	{
		sp->setPosition(size.width/2-10,size.height/2+10);
		sp->setScale(0.25f);
		label->setPosition(size.width/2-10,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"5")==0)
	{
		sp->setPosition(size.width/2-15,size.height/2+10);
		sp->setScale(0.25f);
		label->setPosition(size.width/2-15,size.height/2-30);
	}

	sp->setRotation(90);
	paintNode->addChild(sp);

	paintNode->addChild(label);
}

void beilvjieshao_control11_Paint(Node*node)
{
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	Size size = ctrl->getSize();

	String *pStr = (String *)ctrl->getParent()->getUserData();
	//log("11%s",pStr->getCString());
	if (strcmp(pStr->getCString(),"6")==0) return ;

	char str[60];
	sprintf(str,"%s_0.png",getFishName(nameIndex,4));
	//auto sp = Sprite::createWithSpriteFrameName(str);
	auto sp= Fish::createFishshadow((Fish::FishType)FishIndex[nameIndex][4]);
	sp->doshadowFishLifeAnimation();
	sp->setOpacity(255);
	sp->setColor(ccc3(255,255,255));

	String* ls = String::createWithFormat("X %d",beilvIndex[nameIndex][4]);
	auto label = LabelTTF::create(ls->getCString(),"fonts/arial.ttf",24);
	
	if (strcmp(pStr->getCString(),"0")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"1")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		sp->setScale(0.75f);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"2")==0)
	{
		sp->setPosition(size.width/2,size.height/2+10);
		sp->setScale(0.35f);
		label->setPosition(size.width/2,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"3")==0)
	{
		sp->setPosition(size.width/2-10,size.height/2+10);
		sp->setScale(0.25f);
		label->setPosition(size.width/2-10,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"4")==0)
	{
		sp->setPosition(size.width/2-10,size.height/2+10);
		sp->setScale(0.45f);
		label->setPosition(size.width/2-10,size.height/2-30);
	}
	else if (strcmp(pStr->getCString(),"5")==0)
	{
		sp->setPosition(size.width/2-15,size.height/2+10);
		sp->setScale(0.25f);
		label->setPosition(size.width/2-15,size.height/2-30);
	}

	sp->setRotation(90);
	paintNode->addChild(sp);

	paintNode->addChild(label);

	nameIndex++;
}

void beilvjieshao_initialize(Node* node)
{
	UIForm* form = (UIForm*)node;
	form->getControl(beilvjieshao_control7)->registerPaintEvent(beilvjieshao_control7_Paint);
	form->getControl(beilvjieshao_control8)->registerPaintEvent(beilvjieshao_control8_Paint);
	form->getControl(beilvjieshao_control9)->registerPaintEvent(beilvjieshao_control9_Paint);
	form->getControl(beilvjieshao_control10)->registerPaintEvent(beilvjieshao_control10_Paint);
	form->getControl(beilvjieshao_control11)->registerPaintEvent(beilvjieshao_control11_Paint);

	MListView *beilvList = (MListView *)form->getControl(beilvjieshao_control4);
	beilvList->clearItems();
	beilvList->setItemCount(7);

	for (int i = 0;i < 7;++i)
	{
		MControl *item = beilvList->getItem(i);
		String *pStr = String::createWithFormat("%d",i);
		pStr->retain();

		item->setUserData(pStr);
	}
}
//control3
void beilvjieshao_control3_Click(Node *node,Touch* ptouch, Event* event){

	nameIndex = 0;
	UIM->closeForm(Form_beilvjieshao,false);
}
