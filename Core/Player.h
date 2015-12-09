#ifndef Player_H_
#define Player_H_
#include "cocos2d.h"
USING_NS_CC;
enum VarName
{
	Money =0,
	Diamond,
	LvL,//关卡
	Score,
	GameCheck,
	PlayerGrade,//玩家等级
	PlayerRank,//玩家称号
	Lottery,

	FixedItem,
	LockFishItem,
	RageItem,
	MissileItem,
	LaserItem,

	VIP,
	TotalCharge,
	VarCount,
};

class Cannon;
class CannonInf;
class Fish;
class Player : public Ref
{
public:
	explicit Player();
	~Player();

	void initCannon();
	void encryption();

	//钻石和金币
	void setMoney(int money);
	void setGold(int gold);
	int getMoney();
	int getGold();
	void addMoney(int money);
	void addGold(int gold);
	void setLottery(int num);
	void addLottery(int num);
	int  getLottery();
	void  setScore(int sco);
	void  addScore(int sco);
	int   getScore();

	void setLvl(int num);
	void addLvl(int num);
	int  getLvl();

	void setVIP(int vip);
	void addVIP(int vip);
	int getVip();

	void setTotalCharge(int num);
	void addTotalCharge(int num);
	int getTotalCharge();

	void  setGameCheck(int check);
	void  addGameCheck(int check);
	int   getGameCheck();

	void  setPlayGrade(int grade);
	void  addPlayGrade(int grade);
	int   getPlayGrade();

	void setPlayRank(int rank);
	void addPlayRank(int rank);
	int  getPlayRank();

	void setSeat(int index);
	int getSeat();

	void setLifeTime(float time);
	void addLifeTime(float time);
	float getLifeTime();
	//变量的操作
	void setVariable(int index,int num);
	int getVariable(int index);
	void addVariable(int index,int num);

	Cannon* getCannon();
	void setCannonRate(int rateIndex);
	void setCannonInf(int index);

	bool isMachine(){return bMachine;}
	void setMachine(bool flag){bMachine = flag;}

	void setAiFish(Fish *fish);
	Fish* getAiFish();

	void setSex(int sex);
	int getSex();

	bool checkFirstCharge();
	void setFirstCharge(bool flag);

	void changeCannon();
	float getExtraRate();
	virtual void upate(float dt);
	
public:
	std::string userName;
	std::string psw;
	std::string nickName;
	int curRateInfIndex;
	int curCannonIndex;//当前炮台索引
	bool bNeedRemove;
	bool bFirstCharge;
	short iconId;
	//炮台
	short cannonChangeCount;//炮台更换次数
	float cannonChangeTime;
protected:
	float lifeTime;
	bool bMachine;
	float cannonRateTime;
	float aiFishTime;
	float clickTime;
	//游戏变量
	int seatIndex;
	int sex;//0是男，1为女
	int gameVariables[VarCount];
	int gameVariablesBackUp[VarCount];
	int m_keyCode;
	bool bModifyMemory;
	Cannon *pCannon;
	Fish *aiFish;
};
#endif