#ifndef _GAME_INIT_H_
#define _GAME_INIT_H_

#include "GameBase.h"

class GameInit : public BaseLayer
{
public:
	GameInit();
	~GameInit();

	CREATE_FUNC(GameInit);

	virtual bool init();
	virtual void update(float delta);
	virtual void exitLayer();

public:
	int count;
	//Sprite *loadingP0;
	//Sprite *loadingP1;
	//Sprite *loadingP2;
};

#endif