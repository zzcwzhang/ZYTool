#include"UI.h"

void setPropDialog()
{
	auto ctrl = (MControl*)propCtrl;
	Vec2 startV,endV;
	startV = ctrl->getAbsPosition();
	startV.x += ctrl->getSize().width/2;
	startV.y += ctrl->getSize().height/2;

	if (startV.x < SCREEN_HALF_WIDTH)
	{
		endV.x = startV.x + 50;
	}
	else
	{
		endV.x = startV.x - 50;
	}

	if (startV.y < SCREEN_HALF_HEIGHT)
	{
		endV.y = startV.y + 100;
	}
	else
	{
		endV.y = startV.y - 100;
	}

	Vec2 offset = startV - endV;
	//3¡è?¨¨
	float len = ccpDistance(startV,endV);
	//???¨¨
	float degrees = -1 * CC_RADIANS_TO_DEGREES(ccpToAngle(offset));
	degrees += 180;

	auto form = UIM->getForm(Form_daojutishikuang);
	auto paintNode = form->getControl(daojutishikuang_control4)->getPaintNode();
	paintNode->removeAllChildren();
	
	//¦Ì?
	auto sp_point = Sprite::create("proptip.png");
	sp_point->setPosition(startV);
	paintNode->addChild(sp_point);

	//??1
	auto sp_line = Sprite::create("proptip_line.png");
	sp_line->setTextureRect(Rect(0,0,len,sp_line->getContentSize().height));
	sp_line->setAnchorPoint(Vec2(0,0.5f));
	sp_line->setPosition(startV);
	sp_line->setRotation(degrees);
	paintNode->addChild(sp_line);

	//??2
	auto sp_line1 = Sprite::create("proptip_line.png");
	sp_line1->setTextureRect(Rect(0,0,sp_line->getContentSize().width/2,sp_line->getContentSize().height));
	sp_line1->setAnchorPoint(Vec2(0,0.5f));
	paintNode->addChild(sp_line1);
	if (startV.x >= SCREEN_HALF_WIDTH)
	{
		sp_line1->setAnchorPoint(Vec2(1,0.5f));

		sp_line1->setPosition(Vec2(endV.x + 2,endV.y));
	}
	else
	{
		sp_line1->setPosition(Vec2(endV.x - 2,endV.y));
	}

	//?¨°
	auto ctrl2 = form->getControl(daojutishikuang_control2);
	int x = 0;
	if (startV.x < SCREEN_HALF_WIDTH)
	{
		x = endV.x + sp_line->getContentSize().width/2 + ctrl2->getSize().width/2;
	}
	else
	{
		x = endV.x - sp_line->getContentSize().width/2 - ctrl2->getSize().width/2;
	}
	ctrl2->setPosition(Vec2(x,endV.y));
	ctrl2->stopAllActions();
	ctrl2->setScale(1.0f,0);
	auto action1 = ScaleTo::create(0.1f,1.0f,1.0f);
	ctrl2->runAction(action1);
}

void daojutishikuang_register(Node* node)
{
UIForm *form = (UIForm*)node;
}

void daojutishikuang_control3_Paint(Node *node)
{
	MCONTROL_INIT_REMOVEALL;

	auto label0 = LabelTTF::create(propDialogTxt,"Arial",20,Size(400,150),cocos2d::TextHAlignment::CENTER);
	label0->setPosition(size.width/2,size.height/2+1 - 40);
	label0->setColor(Color3B(0,0,0));
	paintNode->addChild(label0);

	auto label1 = LabelTTF::create(propDialogTxt,"Arial",20,Size(400,150),cocos2d::TextHAlignment::CENTER);
	label1->setPosition(size.width/2,size.height/2-1 - 40);
	label1->setColor(Color3B(0,0,0));
	paintNode->addChild(label1);

	auto label2 = LabelTTF::create(propDialogTxt,"Arial",20,Size(400,150),cocos2d::TextHAlignment::CENTER);
	label2->setPosition(size.width/2-1,size.height/2 - 40);
	label2->setColor(Color3B(0,0,0));
	paintNode->addChild(label2);

	auto label3 = LabelTTF::create(propDialogTxt,"Arial",20,Size(400,150),cocos2d::TextHAlignment::CENTER);
	label3->setPosition(size.width/2+1,size.height/2 - 40);
	label3->setColor(Color3B(0,0,0));
	paintNode->addChild(label3);

	auto label = LabelTTF::create(propDialogTxt,"Arial",20,Size(400,150),cocos2d::TextHAlignment::CENTER);
	label->setPosition(size.width/2,size.height/2 - 40);
	paintNode->addChild(label);
}

void daojutishikuang_initialize(Node* node)
{
	auto form = (UIForm*)node;

	form->getControl(daojutishikuang_control3)->registerPaintEvent(daojutishikuang_control3_Paint);

	auto action1 = DelayTime::create(1.5f);
	auto action2 = CallFunc::create(form,callfunc_selector(UICallBack::closePropDialog));
	form->runAction(Sequence::create(action1,action2,nullptr));

	if (propCtrl)
	{
		setPropDialog();
	}
}
