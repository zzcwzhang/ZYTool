#ifndef MLable_H_
#define MLable_H_
#include <vector>
#include "cocos2d.h"
#include "MControl.h"
#include "DataStream.h"
class UISkin;
class MLabel : public MControl
{
public:
	UISkin* skin;
	std::vector<short> skinIds;
	std::vector<cocos2d::Vec2> skinOffsets;
public:
	CREATE_FUNC(MLabel);
	MLabel();
	~MLabel();
	virtual void update(float delta);
	virtual void loadData(DataStream *dis);
	virtual void initMControl();
	virtual void copy(MControl *ctrl);
	virtual MControl* clone();
	virtual cocos2d::Vec2 getSkinOffset(UISkin* skin);

	virtual bool pressDownEvent(cocos2d::Touch *ptouch);
};
#endif