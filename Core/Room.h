#ifndef Room_H_
#define Room_H_
#include "GameBase.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;
USING_NS_CC;
#define MAX_FISH_COUNT 50
#define FISHTAGPOOR 20000

#define BGLOCALZORDER 1000   //�������
#define HALOWATERZORDER 1001 //���β��
#define SCENECLEARZORDER 1002//�������
#define FISHSHADOWZORDER 1006 //��Ӱ���
#define PHYSICSLZORDER 1008   //������
#define GUILOCALZORDER 1009  //GUI���
#define BULLETLOCALZORDER 1010//�ӵ����

enum SceneType{
	HAICAO = 0,
	CJ2,
	CJ4,
	CJ5,
	SceneCount
};
class RoomInf;
class Player;
class Bullet;
class Fish;
class Room : public BaseLayer
{
public:
	Room();
	~Room();

	static Room* create(int index);
	bool initWithRoomIndex(int index);
	virtual void exitLayer();
	void setInf(RoomInf *inf);
	RoomInf* getInf();

	Player* getPlayer(int index);
	void addPlayer(Player* player);
	void removePlayer(Player *player);

	int  getBulletCount();
	void addBullet(Bullet *bullet);
	void checkBullets();
	void checkDeblock(); /*�޸�*/
	bool checkFishWithBulletCollision(Fish* pFish,Bullet* pBullet);
	virtual bool catchFish(Fish *pFish, Bullet *pBullet);
	void removeFish(Fish *pf);
	void removeBullet(Bullet *bullet);
	void removeFishShadow(Fish *pf);

	Vector<Fish*> getFishes();
	
	//��������߼�
	void updateFish(float dt);
	void addFish();

	//�����¼�
	void registerEventDispatcher();
	bool onTouchBegan(Touch* touch,Event* evt);
	void onTouchMoved(Touch* touch,Event* evt);
	void onTouchEnded(Touch* touch,Event* evt);

	void createFishShadow(Fish* fish);
	void checkFishShadow(Fish* fish);
	void updateFishShadow(float dt);

	void updateYuchaoTime(float dt);
	void prepareFishTideComing(float dt);

	void speedUpBeforeFishTide();
	void FishTideComing(float dt);
	void startFishGenerator(bool start);

	std::string getGameScenePrefix(int type);
	void removeScene();
	void switchBGView(float dt);
	void JoinClippingNode(Armature* BGView);
	void initFrame();

	void KillFishToShake();

	bool getClickDeblock(){return clickDeblock;}  /*�޸�*/
	void setClickDeblock(bool click){clickDeblock = click;}  /*�޸�*/

protected:
	RoomInf *_inf;
	int onlineCount;//�������
	float yuchaoTime;
	bool CheckFishSpeedUp; /*�޸�*/
	bool clickDeblock;   /*�޸�*/
	Vector<Fish*> m_pFishes;
	Vector<Bullet*> m_pBullets;
	Vector<Fish*> m_pFShadow;
	int FishTag;

	Vector<Player*> playerList;
	Vector<Node*> armatureCJScene;
	Vector<Node*> drawNodeList;
};
Rect shrinkRect(Rect rc, float xr, float yr);
bool isLineThroghRect( Vec2 beginPot,Vec2 endPot,Rect aimRect );
bool checkTwoPXLine( Vec2 A,Vec2 B,Rect mRect, float len);
bool checkJGHurt( Vec2 A,Vec2 B,Rect mRect );
#endif