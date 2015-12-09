#ifndef UITrailer_H_
#define UITrailer_H_
#include "cocos2d.h"
#include "DataStream.h"
#include "MControl.h"
#include <vector>
class UITimeLine;
class UITrailer;
class UIForm;
class UIScriptData;
class UITrailerFrame : public cocos2d::Ref
{
public:
	CREATE_OBJFUNC(UITrailerFrame);
	UITrailerFrame();
	~UITrailerFrame();
	void loadData(DataStream *dis);
public:
	UITimeLine *line;
	short timeIndex;
	cocos2d::Vec2 location;
	cocos2d::Size size;
	short opacity;
	short rot;
	short skinIndex;
	cocos2d::Vec2 scale;
	short frontTo;
	short backTo;
	cocos2d::Color4B bkColor;
};
//////////////////////////////////////////////////////////////////////////
class UITimeLine : public cocos2d::Ref
{
public:
	CREATE_OBJFUNC(UITimeLine);
	UITimeLine();
	~UITimeLine();
	void loadData(DataStream *dis);
	void updateObjNode(short timeIndex);
	void runScript(short timeIndex);
private:
	UITrailerFrame *getFrame(int index);
	UIScriptData *getScriptData(int timeIndex);
public:
	MControl *ctrl;
	UITrailer *trailer;
	cocos2d::Vector<UITrailerFrame*> frames;
	std::vector<int> scriptIds;
};
//////////////////////////////////////////////////////////////////////////
class UITrailer : public cocos2d::Ref
{
public:
	CREATE_OBJFUNC(UITrailer);
	UITrailer();
	~UITrailer();
	void loadData(DataStream *dis);
	void updateLogic(float dt);
	void setDelayTime(short delayTime){this->delayTime = delayTime;}
	void setCurTimeIndex(short timeIndex){this->curTimeIndex = timeIndex;m_time = 0;}
	short getCurTimeIndex(){return this->curTimeIndex;}
	bool checkTimeIndex(short timeIndex);
	UIForm* getForm(){return form;}
	void setForm(UIForm* form){this->form = form;}
	void stop();
	void play();
	bool isStop(){return bStop;}
	void setSpeed(short speed);
private:
	UIForm *form;
	cocos2d::Vector<UITimeLine*> timeLines;
	short speed;
	short m_time;
	short curTimeIndex;
	short delayTime;
	bool bStop;
};
#endif