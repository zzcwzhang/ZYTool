#include "MLabel.h"
#include "UISkin.h"
#include "UIManager.h"
USING_NS_CC;
MLabel::MLabel()
{
	skin = NULL;
}

MLabel::~MLabel()
{
	skinIds.clear();
	skinOffsets.clear();
}
void MLabel::loadData(DataStream *dis)
{
	MControl::loadData(dis);
	short skinId = dis->readShort();
	this->skin = UIManager::getInstance()->getSkin(skinId);
	
	short count = dis->readByte();
	for (int i = 0; i < count; i++)
	{
		skinIds.push_back(dis->readShort());
	}
	count = dis->readByte();
	for (int i = 0; i < count; i++)
	{
		int x = dis->readShort();
		int y = dis->readShort();
		Vec2 pp = Vec2(x,y);
		skinOffsets.push_back(pp);
	}

}

void MLabel::copy(MControl *ctrl)
{
	MControl::copy(ctrl);
	MLabel *label = (MLabel*)ctrl;
	this->skin = label->skin;
	int count = label->skinIds.size();
	for (int i = 0; i < count; i++)
	{
		this->skinIds.push_back(label->skinIds[i]);
	}

	count = label->skinOffsets.size();
	for (int i = 0; i < count; i++)
	{
		this->skinOffsets.push_back(label->skinOffsets[i]);
	}
}

MControl* MLabel::clone()
{
	MLabel *label = MLabel::create();
	label->copy(this);
	return label;
}

void MLabel::initMControl()
{
	MControl::initMControl();
	if(this->skin)
	{
		setSkin(this->skin,getSkinOffset(skin));
	}
}

void MLabel::update(float delta)
{
	MControl::update(delta);
}

Vec2 MLabel::getSkinOffset(UISkin* skin)
{
	if(skin == nullptr)
	{
		return Vec2::ZERO;
	}
	int skinId = skin->m_id;
	int size = skinIds.size();
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		if(skinIds[i] == skinId)
		{
			index = i;
			break;
		}
	}
	return skinOffsets[index];
}

bool MLabel::pressDownEvent(cocos2d::Touch *ptouch)
{
	return MControl::pressDownEvent(ptouch);
}