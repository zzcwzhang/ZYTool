#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__
#include "Room.h"
class Fish;
class Player;
class GameLayer : public Room
{
public:
	GameLayer();
	~GameLayer();
	static GameLayer* create(int index);
	virtual bool initWithRoomIndex(int index);
	virtual void exitLayer();

	void pauseObjAction(float time= -1.0f);
	void resumeObjAction();
	bool isPause();
	ActionManager* getObjActionManager(){return objActionManger;}

	int getKilltaskFishNum();
	void clearKilltaskFishNum();
	int getTaskfishNum();
	int getTaskfishType();
	int getCheckGold();
	void checkTask();
	void bubbleAnimationCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID);
	virtual bool catchFish(Fish *pFish, Bullet *pBullet);
	void removeTaskScene();//移除任务提示

	void loadResource();
	void setInLineTime(int index);
	int getInLineMinter();
	int getInLineSecond();
	int getGobackSec();
	int getGobackMin();
	int getGobackHor();

	int onlineRewardIndex;
	int onlineCoin;
	bool nextCheck;
private:
	ActionManager *objActionManger;
	bool bPause;
	float pauseTime;
	int killTaskFishNum;
	bool isPromote;
	Player *_player;
	int taskFishNum;//
	int taskFishtype;
	int CheckGold;//

	bool onlineLock;
	float onlineTime;
	float backTaskTime;
private:
	void update(float delta);
};
#endif