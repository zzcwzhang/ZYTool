#ifndef UIForm_H_
#define UIForm_H_
#include "cocos2d.h"
#include "MControl.h"
enum EVENTTYPE
{
	Single_Event = 0,
	Multi_Event,
	NO_Event,
};

typedef void (*Register)(cocos2d::Node *node);
class UITrailer;
class UIScriptData;
class UIForm : public cocos2d::Node
{
public:
	cocos2d::Vector<MControl*> ctrlList;
	cocos2d::Vector<UIScriptData*> scriptList;
	cocos2d::Vector<UITrailer*> trailerList;
	UITrailer *curTrailer;
	Node *_paintNode;
	short formId;
	bool m_bEnabled;
	bool m_bNeedClose;
	bool m_bNeedRelease;
	Initialize initFunc;
	UpdateLogic updateEvent;
	short childOpacity;

	bool bTipMessageLock;
	short m_eventType;
	bool m_eventLock;//事件锁
	bool m_bActive;
	bool m_bUpdate;//防止连续点击，之后在update之后才接受触摸事件
	Register registerFunc;
public:
	CREATE_OBJFUNC(UIForm);
	UIForm();
	~UIForm();
	virtual void update(float delta);
	virtual void paint();
	virtual void onEnter();
	virtual void onExit();
	virtual void visit(Renderer *renderer, const Mat4& transform, uint32_t flags);
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
	void loadForm(DataStream * dis);
	void initForm();
	void releaseRes();
	void loadRes();

	void setTrailer(UITrailer *trailer);
	void setTrailer(short trailerId);
	UITrailer* getCurTrailer(){return curTrailer;}
	UITrailer* getTrailer(short trailerId);

	void setInitFunc(Initialize initfunc);
	Initialize getInitFunc();
	void setUpdateEvent(UpdateLogic pevent);
	UpdateLogic getUpdateEvent();

	void setEnabled(bool enabled);
	bool getEnabled();

	void setTouchEventType(short eventType);
	short getTouchEventType();
	void setEventLock(bool flag);
	bool isEventLock();

	void setActive(bool flag);
	bool isActive();

	Node* getPaintNode();

	void showTipMessage(short ctrlId);
	void refresh();
	void tipMessageEnd(Node *node);

	void addControl(MControl *ctrl);
	MControl *getControl(short ctrlId);
	UIScriptData *getScriptData(short scriptId);

	void registerTouchListenner();
	virtual void addChild(Node* child, int zOrder, int tag);
	virtual void addChild(Node *child);
	virtual void addChild(Node *child,int zOrder);

	bool touchBegan(Touch* ptouch, Event* event);
	void touchMoved(Touch *pTouch, Event *pEvent);
	void touchEnded(Touch *pTouch, Event *pEvent);

	void setRegisterFunc(Register initfunc);
	Register getRegisterFunc();
};
#endif