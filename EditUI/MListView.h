#ifndef MListView_H_
#define MListView_H_
#include "MLabel.h"
#include "DataStream.h"

typedef void (*ItemSelectChange)(Node *curItem, Node *preItem,Touch* pTouch);
class MListView : public MLabel
{
public:
	CREATE_FUNC(MListView);
	MListView();
	~MListView();
	virtual void update(float delta);
	virtual void paint();
	virtual void visit(Renderer *renderer, const Mat4& transform, uint32_t flags);
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
	virtual void loadData(DataStream *dis);
	virtual void initMControl();
	virtual void releaseRes();
	virtual void refresh();

	virtual bool pressDownEvent(cocos2d::Touch *ptouch);
	virtual void moveEvent(cocos2d::Touch *ptouch);
	virtual void pressUpEvent(cocos2d::Touch *ptouch);

	void registerItemSelectChangedEvent(ItemSelectChange func){itemSelectChanged = func;}
	ItemSelectChange getItemSelectChanged(){return itemSelectChanged;}

	int getItemCount(){return itemCount;}
	void addItemCount(short num);
	void setItemCount(short count);
	void removeItem(int index);
	void removeItem(MControl *item);
	void addItem(MControl *ctrl);
	void insertItem(MControl *item, int index);
	void clearItems();
	MControl *getItem(int index);
	short getItemIndexof(MControl *item);
	void setInertiaSpeed(float speed,float acc);
	void setSelectIndex(int index,bool bsmooth = false);
	
	/**
     * clip this view so that outside of the visible bounds can be hidden.
     */
    void beforeDraw();
    void onBeforeDraw();
    /**
     * retract what's done in beforeDraw so that there's no side effect to
     * other nodes.
     */
    void afterDraw();
    void onAfterDraw();
private:
	void updateItemsPos(float dx, float dy);
	void updateInertia(float dt);
	bool checkItemPostion(float dt);
	void correctItems(float dt);
public:	
	short itemCtrlId;
	short direction;//0为水平，1为垂直
	MControl *curItem;
	MControl *preItem;
	std::string soundName;
private:
	ItemSelectChange itemSelectChanged;
	short itemCount;
	cocos2d::Vector<MControl*> items;
	Vec2 startPoint;
	float inertiaSpeed;//惯性速度
	float acceleration;//加速度
	bool isDragging;
	bool isCorrect;
	CustomCommand _beforeDrawCommand;
	CustomCommand _afterDrawCommand;
};
#endif