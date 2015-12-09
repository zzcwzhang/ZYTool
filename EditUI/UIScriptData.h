#ifndef UIScriptData_H_
#define UIScriptData_H_
#include "cocos2d.h"
//����
#define Rule_BeClick 0
#define Rule_Any 1
//������
#define CDT_SystemVar 0
//ָ������
enum ScriptActionType
{
	Act_Stop = 0,
	Act_Play,
	Act_GotoPlay,
	Act_Delay,
	Act_SystemVar,
	Act_SkinSet,
	Act_VisibleSet,
	Act_SkinStop,//Ƥ��ֹͣ
	Act_EnableSet,//��Ч������
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
	//������
	bool checkRule(MControl *ctrl);
	//�������
	bool checkCdts();
	//ִ��ָ��
	void runActs(UIForm *form);
private:
	short rule;//����
	cocos2d::Vector<UIScriptCDT*> cdts;
	cocos2d::Vector<UIScriptACT*> acts;
};
#endif