#ifndef UIScriptCDT_H_
#define UIScriptCDT_H_
#include "cocos2d.h"
#include "GameConfig.h"
class DataStream;
enum UIScriptCdtType
{
	SystemVar = 0,
};
class UIScriptCDT : public cocos2d::Ref
{
public:
	UIScriptCdtType type;
public:
	virtual void loadData(DataStream* dis);
	virtual bool checkCDT(){return false;}
};

class CDTSystemVar : public UIScriptCDT
{
public:
	short varIndex;
	short order;
	short value;
public:
	CREATE_OBJFUNC(CDTSystemVar);
	CDTSystemVar();
	~CDTSystemVar();
	virtual void loadData(DataStream *dis);
	virtual bool checkCDT();
};
#endif