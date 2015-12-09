#include "Helper.h"
USING_NS_CC;

NumSprite* NumSprite::create( int num, NumberType pType )
{
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Num/Num.plist");
	char str[10] = {0};
	char name[10];
	NumSprite* n = new NumSprite;
	n->init();
	//n->type = pType;
	sprintf(str,"%d",num);

	float width = 0;
	float height = 0;

	for (int i=0;i<sizeof(str);i++)
	{
		if (str[i]=='\0')
		{
			break;
		}

		if (pType==GameNumberGameLayerGold)
		{
			sprintf(name,"g%c.png",str[i]);
		}
		else if (pType==GameNumberStoreLayerLevel)
		{
			sprintf(name,"l%c.png",str[i]);
		}
		auto sp = Sprite::createWithSpriteFrameName(name);

		n->addChild(sp);
		sp->setAnchorPoint(Vec2::ZERO);
		//p->setPosition(Vec2(p->getContentSize().width*i,0));//GameNumberGameLayerTime  
		sp->setPosition(Vec2(sp->getContentSize().width*i,0));
		height = sp->getContentSize().height;
		width = sp->getContentSize().width*(i+1);
	}
	n->setContentSize(Size(width,height));
	return n;
}

// void NumSprite::initSprite( int num )
// {
// 
// 	char str[10] = {0};
// 	char name[10];
// 
// 	sprintf(str,"%d",num);
// 
// 	float width = 0;
//	float height = 0;
// 
// 	for (int i=0;i<sizeof(str);i++)
// 	{
// 		if (str[i]=='\0')
// 		{
// 			break;
// 		}
// 
// 		if (type==GameNumberGameLayerGold)
// 		{
// 			sprintf(name,"g%c.png",str[i]);
// 		}
// 		else if (type==GameNumberStoreLayerLevel)
// 		{
// 			sprintf(name,"l%c.png",str[i]);
// 		}
// 		auto sp = Sprite::createWithSpriteFrameName(name);
// 
// 		this->addChild(sp);
//		sp->setAnchorPoint(Vec2::ZERO);
		
//		sp->setPosition(Vec2(sp->getContentSize().width*i,0));
//		height = sp->getContentSize().height;
//		width = sp->getContentSize().width*(i+1);
// 	}
// 	this->setContentSize(Size(width,height));
// }
