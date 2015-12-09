#ifndef __BULLET_CANNON__
#define __BULLET_CANNON__
#include "cocos2d.h"
#include "Cannon.h"
class GameLayer;
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;
enum BulletStatus{
	Bullet_Fly = 0,
	Bullet_Hit,
	Bullet_Net,
	Bullet_End
};
class Player;
class Bullet : public cocos2d::Node
{
public:
	int m_speed;
	cocos2d::Vec2 ptLastStart;
	BulletStatus m_status;
	int bullet_score;//�̳д�������
	float hit_score;//�̳д��ڹ�����
	CannonType bulletType;
	cocos2d::Vec2 laserEnd;  //�����յ�
	cocos2d::Vec2 laserStart;//�������
	Cannon* pCannon;
	bool bInvalid;
	bool bCanAttack;
	short atkTime;
	CustomCommand _customCommand;
public:
	Bullet();
	~Bullet();
	

	static Bullet*createWithBulletType(CannonType cannontype,int pScore,float hScore,cocos2d::Vec2 sPos,float f_rotation);
	bool initWithBulletType(CannonType cannontype,int pScore,float hScore,cocos2d::Vec2 sPos,float f_rotation);
	void shootTo(cocos2d::Vec2 targetDirection);
	float getBulletMoveTime(cocos2d::Vec2 startPos, cocos2d::Vec2 endPos);
	//������ӵ��ڳ�����Ļ�󷴵�
	void reflect();
	void showNet();

	void setCannon(Cannon* cannon);
	Cannon* getCannon();

	bool isInvalid();
	void setInvalid(bool flag);

	bool canAttack();
	void setCanAttack(bool flag);

	float getExtraRate();

	virtual void draw(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags);
	void onDraw(const Mat4 &transform, uint32_t flags);
	void explosion();
	void setMissionExplor(Armature *pArmature, cocostudio::MovementEventType movementType, const char *movementID);
	
	void animationCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID);
	void laseranimationCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID);//�ӵ����ⷢ��
	void fasheLaserCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID);//���߼��ⷢ��
	void removeSelf();
};
#endif