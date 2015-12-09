#ifndef __CANNON_H__
#define __CANNON_H__
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
USING_NS_CC;
using namespace cocostudio;

class Room;
class CannonRateInf;
class CannonInf;
class Fish;
class Player;
enum CannonType{
	Cannon1 = 0,
	Cannon2,
	Cannon3,
	Cannon4,
	Cannon5,
	Cannon6,

	MissileCannon,//导弹
	LaserCannon,
};

enum IsOutfit
{
	none=0,
	outfit,
	outfited
};
class Cannon : public cocos2d::Node
{
public:
	~Cannon();
	void setpreConsume(int Hart){prevConsume = Hart;}
	int getpreConsume(){return prevConsume;}

	bool getAutoFire(){return autoFire;}
	void setAutoFire(bool fire){autoFire = fire;}

	bool getBanClick(){return banClick;}
	void setBanClick(bool click){banClick = click;}

	void update(float dt);
	void updateFire(float dt);
	cocos2d::Vec2 getCannonHolePos();
	void doFire();
	void rotationAndFire(cocos2d::Vec2 pTo);
	void cannonFireEffect();
	cocos2d::Vec2 bulletFlyendPos(cocos2d::Vec2 bulletStart);

	void onTouchBegan(float fx,float fy);
	void onTouchMoved(float fx,float fy);
	void onTouchEnded(float fx,float fy);

	void setClick(Vec2 v2);
	Armature* getCannonArm(){return this->armature;}
	void animationCallBack_1(Armature *armature, MovementEventType movementType, const std::string& movementID);
	void setLevelEffect();

	void setCannonRateInf(CannonRateInf* inf){rateInf = inf;}
	CannonRateInf* getCannonRateInf(){return rateInf;}

	void setCannonInf(CannonInf* inf){cannonInf = inf;}
	CannonInf* getCannonInf(){return cannonInf;}

	static Cannon*createWithtype(CannonType type=Cannon1);
	bool initWithCannonType(CannonType type);
	void dostudioAniamtion();

	void setFireType(int index)
	{
		fireType = (FireType)index;
	}
	/*LockFish*/
	Armature* lockArm; 
	void addLockToFish( Fish* fish );
	/*LockFish*/

	void setPlayer(Player *player);
	Player* getPlayer();

	void setCilckOnceWithMissionAndLaser(){clickOnce = true;}
private:
	void doRageFire();
	void doMissileFire();
	void doLaserFire();
	void fasheMissileCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID);
	void fasheLaserCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID);
	//void clearLaserCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID);
	
public:
	Fish *targeFish;
	enum FireType{
		Common = 0,//普通
		Rage,//狂暴
		Missile,//导弹
		Laser,//激光
	};
	float RageTime;//狂暴时间
	float LockTime;//锁定时间
	bool bLockFish;
	bool bPress;
	bool bPrepareFire;
	FireType fireType;
	int ownCannon[6];
	Armature* specialArm;
	/****激光数据****/
	cocos2d::Vec2 laserS;
	cocos2d::Vec2 laserE;
	int  laserCosume;
	bool isHartLaser;
	bool clickOnce;
private:
	Player* _owner;
	cocos2d::Vec2 m_pDirection;
	char * cannonName;
	Armature* armature;
	Cannon();
	
	
	cocos2d::Vector<Armature*>fireArma;
	float befRotation;
	float clickX;
	float clickY;
	bool autoFire;
	float fireInterval;
	bool banClick;
	bool beginClick;
	int prevConsume;
	CannonRateInf* rateInf;
	CannonInf *cannonInf;
	//int Consume;//消耗
	//float attack;//攻击力

};
#endif