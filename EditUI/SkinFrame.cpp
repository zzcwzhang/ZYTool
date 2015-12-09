#include "SkinFrame.h"
#include "DataStream.h"
#include "cocos2d.h"
SkinFrame::SkinFrame()
{
	m_delay = 0;
	items = NULL;
}

SkinFrame::~SkinFrame()
{
	if(this->items)
	{
		for(int i = 0; i < this->itemCount; i++)
		{
			delete items[i];
			items[i] = NULL;
		}
		delete items;
		items = NULL;
	}
}

void SkinFrame::loadFrame(DataStream *dis)
{
	this->m_delay = dis->readShort();
	short itemCount = dis->readShort();
	this->itemCount = itemCount;
	this->items = new SkinItem*[itemCount];
	for(int i = 0; i < itemCount; i++)
	{
		SkinItem *item = new SkinItem();
		item->loadItem(dis);
		this->items[i] = item;
	}
}

void SkinFrame::loadRes()
{
	for(int i = 0; i < itemCount; i++)
	{
		char name[128];
		memset(name,0,sizeof(name));
		sprintf(name,"UI/Img/ui_%d.png",this->items[i]->imgId);
		cocos2d::Director::getInstance()->getTextureCache()->addImage(name);
	}
}