#ifndef __GUI_LAYER__
#define __GUI_LAYER__
#include "cocos2d.h"
#include "Fish.h"
class Cannon;
class GUILayer : public cocos2d::Layer
{
private:
	int GameCheck;//鹿脴驴篓
	int taskFishNum;//虏露禄帽脠脦脦帽脫茫脢媒脕驴
	Fish::FishType taskFishtype;
	int CheckGold;//鹿脴驴篓陆卤脌酶
	bool nextTime;//录脤脨酶录脝脢卤

	
public:
	Armature* gTask;//任务栏动画
	Fish* taskFish;//任务栏上鱼

	std::string cannon_name;//获取炮台名
	//Armature* shankArm;//炮弹解锁闪烁框

	void setGameCheck(int check){GameCheck = check;}

	void HandleTime(int time);
	void setNexttime(bool next){nextTime = next;}
public:
	Cannon* pCannon;
	static GUILayer* guiLayer;
	static GUILayer* getInstance();

	Cannon* getCannon(){return pCannon;}
	//static GUILayer*create();
	virtual bool init();
	void initUIM();
	void initCannon();
	void checkTask();
	void inituiArmature();
	void showTask();

	void update(float dt);
	
	void onTouchBegan(float fx,float fy);
	void onTouchMoved(float fx,float fy);
	void onTouchEnded(float fx,float fy);

	CREATE_FUNC(GUILayer);
};
#define guiGame (GUILayer::getInstance())
#endif // !1
