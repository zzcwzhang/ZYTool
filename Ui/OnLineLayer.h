#ifndef OnLineLayer_H_
#define OnLineLayer_H_
#include "Room.h"
class OnLineLayer : public Room
{
public:
	OnLineLayer();
	~OnLineLayer();
	static OnLineLayer* create(int index);
	virtual bool initWithRoomIndex(int index);
	virtual void exitLayer();

	virtual void update(float dt);

	void randomPlayer(float dt);

	void checkFish();
private:
	void sitdown(Player *player);
	void standUp(Player *player);
private:
	short seats[4];
	float  addPlayerTime;
};
#endif