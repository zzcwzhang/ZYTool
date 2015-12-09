#ifndef UIScriptData_H_
#define UIScriptData_H_
#include "cocos2d.h"
//规则
#define Rule_BeClick 0
#define Rule_Any 1
//条件类
#define CDT_SystemVar 0
//指令类型
enum ScriptActionType
{
	Act_Stop = 0,
	Act_Play,
	Act_GotoPlay,
	Act_Delay,
	Act_SystemVar,
	Act_SkinSet,
	Act_VisibleSet,
	Act_SkinStop,//皮肤停止
	Act_EnableSet,//有效性设置
};
class MControl;
class UIForm;
class UIScriptCDT;
class UIScriptACT;
class UIScriptData : public cocos2d::Ref
{
public:
	CREATE_OBJFUNC(UIScriptData);
	UIScriptData();
	~UIScriptData();
	void loadData(DataStream *dis);
	//检测规则
	bool checkRule(MControl *ctrl);
	//检测条件
	bool checkCdts();
	//执行指令
	void runActs(UIForm *form);
private:
	short rule;//规则
	cocos2d::Vector<UIScriptCDT*> cdts;
	cocos2d::Vector<UIScriptACT*> acts;
};
#endif