#include "UI.h"
UIScriptData::UIScriptData()
{

}
UIScriptData::~UIScriptData()
{
	cdts.clear();
	acts.clear();
}

void UIScriptData::loadData(DataStream *dis)
{
	this->rule = dis->readByte();
	int count = dis->readByte();
	//条件集
	if(count > 0)
	{
		for(int i = 0; i < count; i++)
		{
			int type = dis->readByte();
			UIScriptCDT *cdt = NULL;
			switch(type)
			{
			case SystemVar:
				cdt = CDTSystemVar::create();
				break;
			}
			cdt->loadData(dis);
			cdts.pushBack(cdt);
		}
	}
	else
	{
		//this->cdts = nullptr;
	}
	//指令集
	count = dis->readByte();
	if(count > 0)
	{
		for(int i = 0; i < count; i++)
		{
			int type = dis->readByte();
			UIScriptACT *act = NULL;
			switch(type)
			{
			case Stop:
				act = ActStop::create();
				break;
			case Delay:
				act = ActDelay::create();
				break;
			case Play:
				act = ActPlay::create();
				break;
			case GotoPlay:
				act = ActGotoPlay::create();
				break;
			case Type_SystemVarAct:
				act = ActSystemVar::create();
				break;
			case SkinSet:
				act = ActSkinSet::create();
				break;
			case VisibleSet:
				act = ActVisibleSet::create();
				break;
			case EnableSet:
				act = ActEnableSet::create();
				break;
			case SoundSet:
				act = ActSoundSet::create();
				break;
			}
			act->loadData(dis);
			acts.pushBack(act);
		}
	}
	else
	{
		//this->acts = nullptr;
	}
}

bool UIScriptData::checkRule(MControl *ctrl)
{
	if(this->rule == 1)
	{
		return true;
	}
	
	if(ctrl->m_bClick)
	{
		return true;
	}
	return false;
}

bool UIScriptData::checkCdts()
{
	if(cdts.size() <= 0)
	{
		return true;
	}
	for (auto cdt : cdts)
	{
		if(!cdt->checkCDT())
		{
			return false;
		}
	}
	return true;
}

void UIScriptData::runActs(UIForm *form)
{
	for (auto act : acts)
	{
		act->runScriptAct(form);
	}
}