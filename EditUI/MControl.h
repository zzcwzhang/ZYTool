#ifndef MControl_H_
#define MControl_H_
#include "cocos2d.h"
#include <vector>

enum ControlFlag
{
	F_Visible = 1,
	F_AcceptEvent = 1 << 1,
	F_MouseDown = 1 << 2,
	F_MouseUp = 1 << 3,
	F_MouseMove = 1 << 4,
	F_Click = 1 << 5,
	F_DoubleClick = 1 << 6,
	F_Stencil = 1 << 7,
};

typedef bool (*TouchBegan)(cocos2d::Node *control,cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
typedef bool (*TouchMove)(cocos2d::Node *node,cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
typedef void (*TouchEvent)(cocos2d::Node *node,cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
typedef void (*Initialize)(cocos2d::Node *node);
typedef void (*UpdateLogic)(cocos2d::Node *node,float dt);
typedef void (*PaintEvent)(cocos2d::Node *node);


class DataStream;
class UIForm;
class UISkin;
class UIScriptData;
class MControl : public cocos2d::LayerColor
{
public:
	static float ClickInterval;
public:
	short type;
	short id;
	cocos2d::Color4B color;
	cocos2d::Vec2 anchor;
	short ctrlFlag;
	short parentId;
	UIForm *form;
	UISkin* curSkin;
	cocos2d::Vec2 curSkinOffset;
	short curFraemIndex;
	short curDelayTime;
	bool needUpdate;
	long long m_time;//计时器
	int touchId;//事件ID

	//皮肤节点
	Node *skinNode;
	//绘制节点
	Node *paintNode;

	bool m_bClick;
	bool m_bPressed;
	bool m_bEnabled;
	bool m_bNeedRemove;

	float lockTime;

	cocos2d::Vector<MControl*> ctrlList;
	cocos2d::Vector<UIScriptData*> scripts;
	//cocos2d::CCArray *skins;
protected:
	cocos2d::Vec2 location;
	cocos2d::Size size;
	short opacity;
	cocos2d::Vec2 scale;
	short rot;
protected:
	//自定义数据
	void *userData;
	//事件
	TouchBegan touchBegan;
	TouchMove touchMove;
	TouchEvent touchEnd;
	TouchEvent clickEvent;
	TouchEvent DoubleClickEvent;
	UpdateLogic updateEvent;
	PaintEvent paintEvent;
public:
	CREATE_FUNC(MControl);
	MControl();
	~MControl();
	virtual void loadData(DataStream *dis);
	virtual void initMControl();
	virtual void copy(MControl *ctrl);
	virtual MControl* clone();
	virtual void releaseRes();

	void setUserData(void *data);
	void* getUserData();

	virtual void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
	virtual void update(float delta);
	virtual void paint();
	virtual void addControl(MControl * child);
	virtual void  setParentCtrl(MControl* parent);

	virtual void setPosition(float x, float y);
	virtual void setPosition(cocos2d::Vec2 p);

	cocos2d::Vec2 getAbsPosition();

	virtual void setSize(short width, short height);
	virtual void setSize(cocos2d::Size size);
	cocos2d::Size getSize(){return size;}

	virtual void setControlOpacity(short opacity,bool bChild = false);
	virtual short getControlOpacity();

	virtual void setControlColor(cocos2d::Color4B color);

	virtual void setControlScale(float fScaleX,float fScaleY);
	virtual void setControlScale(cocos2d::Vec2 scale);
	virtual cocos2d::Vec2 getControlScale();

	virtual void setRotation(float fRotation);
	virtual float getRotation();

	virtual void runScript();

	bool checkFlag(short flag);
	void setFlag(short flag);
	void clearFlag(short flag);

	void setEnabled(bool enabled);
	bool getEnabled();

	virtual void refresh();

	Node *getPaintNode(){return paintNode;}

	void setSkin(UISkin* skin, cocos2d::Vec2 offset);

	//事件注册
	void registerTouchDispacher();
	void registerTouchBeganEvent(TouchBegan pevent){this->touchBegan = pevent;}
	void registerTouchMoveEvent(TouchMove pevent){this->touchMove = pevent;}
	void registerTouchEndEvent(TouchEvent pevent){this->touchEnd = pevent;}
	void registerClickEvent(TouchEvent click){this->clickEvent = click;}
	inline void registerPaintEvent(PaintEvent pevent){this->paintEvent = pevent;}
	inline void registerUpdateLogicEvent(UpdateLogic pevent){this->updateEvent = pevent;}
	inline void registerDoubleClickEvent(TouchEvent click){this->DoubleClickEvent = click;}

	virtual bool pressDownEvent(cocos2d::Touch *ptouch);
	virtual void moveEvent(cocos2d::Touch *ptouch);
	virtual void pressUpEvent(cocos2d::Touch *ptouch);
private:
	void _paint();
};
#endif