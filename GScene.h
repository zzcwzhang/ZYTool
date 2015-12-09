#ifndef _GAME_SCENE_
#define _GAME_SCENE_

#include "cocos2d.h"
#include "GameBase.h"
#include "GameConfig.h"
USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	GameScene();
	~GameScene();

	static cocos2d::Scene* createScene();
	static GameScene* getInstance();

	CREATE_FUNC(GameScene);

	virtual bool init();
	virtual void update(float delta);
	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);

	void setState(GAMESTATE state);
	GAMESTATE getCurState();
	void changeState();
private:
	static GameScene *instance;

public:
	GAMESTATE _curState,_preState;
	BaseLayer* _baseLayer;
};

#define GScene (GameScene::getInstance())
void doSms();
void doSuccess();
void doFaile();
void refreshUIForm();
#endif