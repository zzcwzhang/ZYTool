#include "MButton.h"
#include "UISkin.h"
#include "UIManager.h"
#include "Tools.h"
#include "SoundManager.h"
#include "UIForm.h"
USING_NS_CC;
MButton::MButton()
{
	pressSkin = NULL;
}

MButton::~MButton()
{
	pressSkinIds.clear();
	pressSkinOffsets.clear();
}
void MButton::loadData(DataStream *dis)
{
	MLabel::loadData(dis);
	short skinId = dis->readShort();
	this->pressSkin = UIM->getSkin(skinId);
	short count = dis->readByte();
	for (int i = 0; i < count; i++)
	{
		pressSkinIds.push_back(dis->readShort());
	}
	count = dis->readByte();
	for (int i = 0; i < count; i++)
	{
		int x = dis->readShort();
		int y = dis->readShort();
		Vec2 pp = Vec2(x,y);
		pressSkinOffsets.push_back(pp);
	}
	soundName = dis->readString();
}

void MButton::copy(MControl *ctrl)
{
	MLabel::copy(ctrl);
	MButton *label = (MButton*)ctrl;
	this->pressSkin = label->pressSkin;
	int count = label->pressSkinIds.size();
	for (int i = 0; i < count; i++)
	{
		this->pressSkinIds.push_back(label->pressSkinIds[i]);
	}

	count = label->pressSkinOffsets.size();
	for (int i = 0; i < count; i++)
	{
		this->pressSkinOffsets.push_back(label->pressSkinOffsets[i]);
	}
}

MControl* MButton::clone()
{
	MButton *btn = MButton::create();
	btn->copy(this);
	return btn;
}

void MButton::initMControl()
{
	MLabel::initMControl();
}

void MButton::update(float delta)
{
	MControl::update(delta);
}

Vec2 MButton::getPressSkinOffset(UISkin* skin)
{
	if(skin == nullptr)
	{
		return Vec2::ZERO;
	}
	int skinId = skin->m_id;
	int size = pressSkinIds.size();
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		if(pressSkinIds[i] == skinId)
		{
			index = i;
			break;
		}
	}
	return pressSkinOffsets[index];
}

bool MButton::pressDownEvent(Touch *ptouch)
{
	Size size = getSize();
	if(!this->isVisible())
	{
		return false;
	}
	if(!this->checkFlag(F_AcceptEvent))
	{
		return false;
	}
	
	/*if(lockTime < ClickInterval && form->getTouchEventType() != Multi_Event)
	{
		CCLog("lockTime");
		return false;
	}*/
	
	lockTime = 0.0f;
	for (auto ctrl : ctrlList)
	{
		if (ctrl->pressDownEvent(ptouch))
		{
			return true;
		}
	}
	Vec2 pp = this->getParent()->convertToWorldSpace(this->getPosition());
	Vec2 p = ptouch->getLocation();
	Rect rect = Rect(pp.x - anchor.x * size.width,pp.y - anchor.y * size.height,this->getSize().width,size.height);
	if(rect.containsPoint(p))
	{
		if(!this->getEnabled())
		{
			form->showTipMessage(this->id);
			return false;
		}
		long long time = getCurrentTime();
		if(time - m_time <= 0)
		{
			if(this->DoubleClickEvent)
			{
				this->DoubleClickEvent(this,ptouch,NULL);
			}
		}
		m_time = time;
		m_bPressed = true;
		this->touchId = ptouch->getID();
		this->setSkin(pressSkin,getPressSkinOffset(pressSkin));
		if(this->touchBegan)
		{
			this->touchBegan(this,ptouch,nullptr);
		}
		if(soundName.compare("") != 0)
		{
			SMI->playSound(soundName.c_str(),false);
		}
		return true;
	}
	return false;
}

void MButton::pressUpEvent(Touch *ptouch)
{
	MControl::pressUpEvent(ptouch);
	this->setSkin(skin,getSkinOffset(skin));
}