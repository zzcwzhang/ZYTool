#include "UIScriptCDTh.h"
#include "DataStream.h"
#include "UIManager.h"
USING_NS_CC;
void UIScriptCDT::loadData(DataStream *dis)
{
}
//////////////////////////////////////////////////////////////////////////
CDTSystemVar::CDTSystemVar()
{
	this->type = SystemVar;
}

CDTSystemVar::~CDTSystemVar()
{
}

void CDTSystemVar::loadData(DataStream *dis)
{
	this->varIndex = dis->readShort();
	this->order = dis->readByte();
	this->value = dis->readShort();
}

bool CDTSystemVar::checkCDT()
{
	int var = UIM->getSystemVar(varIndex);
	switch(order)
	{
	case 0://����
		return var > value;
	case 1://���ڵ���
		return var >= value;
	case 2://����
		return var == value;
	case 3://����
		return var != value;
	case 4://С��
		return var < value;
	case 5://С�ڵ���
		return var <= value;
	}
	return false;
}