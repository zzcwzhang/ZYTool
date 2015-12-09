#ifndef MButton_H_
#define MButton_H_
#include "MLabel.h"
#include "DataStream.h"
class UISkin;
class MButton : public MLabel
{
public:
	CREATE_FUNC(MButton);
	MButton();
	~MButton();
	virtual void loadData(DataStream *dis);
	virtual void initMControl();
	virtual void update(float delta);
	virtual void copy(MControl *ctrl);
	virtual MControl* clone();
	virtual cocos2d::Vec2 getPressSkinOffset(UISkin* skin);

	virtual bool pressDownEvent(cocos2d::Touch *ptouch);
	virtual void pressUpEvent(cocos2d::Touch *ptouch);
public:
	UISkin* pressSkin;
	std::vector<short> pressSkinIds;
	std::vector<cocos2d::Vec2> pressSkinOffsets;
	std::string soundName;
};
#endif