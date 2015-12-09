#ifndef UIScriptACT_H_
#define UIScriptACT_H_
#include "cocos2d.h"
#include "DataStream.h"
#include "GameConfig.h"
class UIForm;
enum UIScriptActionType
{
	Stop = 0,
	Play,
	GotoPlay,
	Delay,//�ӳ�
	Type_SystemVarAct,
	SkinSet,//Ƥ������
	VisibleSet,//�ɼ�����
	SkinStop,//Ƥ��ֹͣ
	EnableSet,//�ؼ���Ч
	SoundSet,
};

class UIScriptACT : public cocos2d::Ref
{
public:
	UIScriptActionType type;
public:
	virtual void loadData(DataStream *dis){}
	virtual void runScriptAct(UIForm* form){}
};

class ActDelay : public UIScriptACT
{
public:
	short delayTime;
public:
	CREATE_OBJFUNC(ActDelay);
	ActDelay(){this->type = Delay;}
	~ActDelay(){}
	virtual void loadData(DataStream *dis);
	virtual void runScriptAct(UIForm* form);
};

class ActEnableSet : public UIScriptACT
{
public:
	short ctrlIndex;
	bool enable;
public:
	CREATE_OBJFUNC(ActEnableSet);
	ActEnableSet(){this->type = EnableSet;}
	~ActEnableSet(){}
	virtual void loadData(DataStream *dis);
	virtual void runScriptAct(UIForm* form);
};

class ActGotoPlay : public UIScriptACT
{
public:
	short trailerIndex;
	short timeIndex;
public:
	CREATE_OBJFUNC(ActGotoPlay);
	ActGotoPlay(){this->type = GotoPlay;}
	~ActGotoPlay(){}
	virtual void loadData(DataStream *dis);
	virtual void runScriptAct(UIForm* form);
};
class ActPlay : public UIScriptACT
{
public:
	CREATE_OBJFUNC(ActPlay);
	ActPlay(){this->type = Play;}
	~ActPlay(){}
	virtual void runScriptAct(UIForm* form);
};
class ActSkinSet : public UIScriptACT
{
public:
	short ctrlIndex;
	short skinType;
	short skinIndex;
public:
	CREATE_OBJFUNC(ActSkinSet);
	ActSkinSet(){this->type = SkinSet;}
	~ActSkinSet(){}
	virtual void loadData(DataStream *dis);
	virtual void runScriptAct(UIForm* form);
};

class ActStop : public UIScriptACT
{
public:
	CREATE_OBJFUNC(ActStop);
	ActStop(){this->type = Stop;}
	~ActStop(){}
	virtual void runScriptAct(UIForm* form);
};

class ActSystemVar : public UIScriptACT
{
public:
	short varIndex;
	short order;//0Ϊ���ڣ�1Ϊ���ϣ�2Ϊ��ȥ
	short value;
public:
	CREATE_OBJFUNC(ActSystemVar);
	ActSystemVar(){this->type = Type_SystemVarAct;}
	~ActSystemVar(){}
	virtual void loadData(DataStream *dis);
	virtual void runScriptAct(UIForm* form);
};

class ActVisibleSet : public UIScriptACT
{
public:
	short ctrlIndex;
	bool visible;
public:
	CREATE_OBJFUNC(ActVisibleSet);
	ActVisibleSet(){this->type = VisibleSet;}
	~ActVisibleSet(){};
	virtual void loadData(DataStream *dis);
	virtual void runScriptAct(UIForm* form);
};

class ActSoundSet : public UIScriptACT
{
public:
	short soundFlag;
	short soundType;
	std::string soundName;
public:
	CREATE_OBJFUNC(ActSoundSet);
	ActSoundSet(){this->type = SoundSet;}
	~ActSoundSet(){};
	virtual void loadData(DataStream *dis);
	virtual void runScriptAct(UIForm* form);
};
#endif