#include "UISkin.h"
#include "SkinFrame.h"
#include "DataStream.h"
UISkin::~UISkin()
{
	if(this->frames)
	{
		for (int i = 0; i < frameCount; i++)
		{
			delete frames[i];
		}
		delete frames;
		frames = NULL;
	}
}

void UISkin::loadRes()
{
	for(int i = 0; i < this->frameCount; i++)
	{
		this->frames[i]->loadRes();
	}
}

void UISkin::loadSkin(DataStream *dis)
{
	int width = dis->readShort();
	int height = dis->readShort();
	int centerX = dis->readShort();
	int centerY = dis->readShort();
	this->bCyclePlay = dis->readByte() == 1;
	this->size = cocos2d::Size(width,height);
	//this->m_center = Vec2(centerX,centerY);
	this->frameCount = dis->readShort();
	this->frames = new SkinFrame*[this->frameCount];
	for(int i = 0; i < this->frameCount; i++)
	{
		SkinFrame *frame = new SkinFrame();
		frame->loadFrame(dis);
		this->frames[i] = frame;
	}
}