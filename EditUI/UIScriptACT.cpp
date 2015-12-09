#include "UI.h"
#include "SoundManager.h"
void ActDelay::loadData(DataStream *dis)
{
	this->delayTime = dis->readShort();
}
void ActDelay::runScriptAct(UIForm* form)
{
	form->getCurTrailer()->setDelayTime(delayTime);
}
//////////////////////////////////////////////////////////////////////////

void ActEnableSet::loadData(DataStream *dis)
{
	this->ctrlIndex = dis->readShort();
	this->enable = dis->readByte() == 1;
}
void ActEnableSet::runScriptAct(UIForm* form)
{
	MControl *ctrl = form->getControl(ctrlIndex);
	ctrl->setEnabled(enable);
}
//////////////////////////////////////////////////////////////////////////
void ActGotoPlay::loadData(DataStream *dis)
{
	this->trailerIndex = dis->readByte();
	this->timeIndex = dis->readShort();
}
void ActGotoPlay::runScriptAct(UIForm* form)
{
	UITrailer *trailer = form->getTrailer(trailerIndex);
	form->setTrailer(trailer);
	trailer->setCurTimeIndex(timeIndex);
}
//////////////////////////////////////////////////////////////////////////
void ActPlay::runScriptAct(UIForm* form)
{
	form->getCurTrailer()->play();
}
//////////////////////////////////////////////////////////////////////////
void ActSkinSet::loadData(DataStream *dis)
{
	this->ctrlIndex = dis->readShort();
	this->skinType = dis->readByte();
	this->skinIndex = dis->readShort();
}
void ActSkinSet::runScriptAct(UIForm* form)
{
	UISkin *skin = UIM->getSkin(skinIndex);
	if(skinType == 0)
	{
		MLabel *ctrl = (MLabel*)form->getControl(ctrlIndex);
		ctrl->skin = skin;
		ctrl->setSkin(skin,ctrl->getSkinOffset(skin));
	}
	else
	{
		MButton *btn = (MButton*)form->getControl(ctrlIndex);
		btn->pressSkin = skin;
	}
}
//////////////////////////////////////////////////////////////////////////
void ActStop::runScriptAct(UIForm* form)
{
	form->getCurTrailer()->stop();
}
//////////////////////////////////////////////////////////////////////////
void ActSystemVar::loadData(DataStream *dis)
{
	this->varIndex = dis->readShort();
	this->order = dis->readByte();
	this->value = dis->readShort();
}
void ActSystemVar::runScriptAct(UIForm* form)
{
	switch(order)
	{
	case 0:
		UIM->setSystemVar(varIndex,value);
		break;
	case 1:
		{
			short v = UIM->getSystemVar(varIndex) + value;
			UIM->setSystemVar(varIndex,v);
		}
		break;
	case 2:
		{
			short v = UIM->getSystemVar(varIndex) - value;
			UIM->setSystemVar(varIndex,v);
		}
		break;
	}
	
}
//////////////////////////////////////////////////////////////////////////
void ActVisibleSet::loadData(DataStream *dis)
{
	this->ctrlIndex = dis->readShort();
	this->visible = dis->readByte() == 1;
}
void ActVisibleSet::runScriptAct(UIForm* form)
{
	MControl *ctrl = form->getControl(ctrlIndex);
	ctrl->setVisible(visible);
}
//////////////////////////////////////////////////////////////////////////
void ActSoundSet::loadData(DataStream *dis)
{
	this->soundFlag = dis->readByte();
	this->soundType = dis->readByte();
	this->soundName = dis->readString();
}
void ActSoundSet::runScriptAct(UIForm* form)
{
	if(soundFlag == 0)
	{//²¥·Å
		if(soundType == 0)
		{
			//BGM
			SMI->playSound(soundName.c_str(),true);
		}
		else
		{
			SMI->playSound(soundName.c_str(),false);
		}
	}
	else
	{
		//Í£Ö¹
		SMI->stopSound(soundName.c_str());
	}
}
//////////////////////////////////////////////////////////////////////////