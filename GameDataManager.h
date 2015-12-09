#ifndef _GAME_DATA_MANAGER_H_
#define _GAME_DATA_MANAGER_H_
#include "GameData.h"

enum Gender
{
	Male = 0,
	Female
};

class GameDataManager
{
public:
	GameDataManager();
	~GameDataManager();

	static GameDataManager* getInstance();
	void loadGameInfo();

	void loadLevelInf();
	LevelInf *getLevelInf(int index);

	void loadFishInf();
	FishInf *getFishInf(int index);

	void loadCannonRateInf();
	CannonRateInf *getCannonRateInf(int index);

	void loadCannonInf();
	CannonInf *getCannonInf(int index);

	void loadRoomInf();
	RoomInf *getRoomInf(int index);
	
	void loadGradeinf();
	GradeInf* getGradeInf(int index);

	void loadSignRewardInf();
	SignReward *getSignRewardInf(int index);

	void loadCastInf();
	CastInf* getCastInf(int index);

	void loadNameInf();
	std::string getFamilyName(int index);
	std::string getMaleName(int index);
	std::string getFemaleName(int index);

	inline void setDate(std::string str){date = str;}
	inline std::string getDate(){return date;}

	inline void setUserID(int id){userID = id;}
	inline int getUserID(){return userID;}

	inline void setSignData(int data){signData = data;}
	inline int getSignData(){return signData;}
	inline bool isSigned(int day){return signData & (1<<day);}

	inline void setLogin(bool bFlag){hasLogin = bFlag;}
	inline bool isLogin(){return hasLogin;}

	inline void setNickName(std::string name){nickName = name;}
	inline std::string getNickName(){return nickName;}

	inline void setGender(Gender gender){this->gender = gender;}
	inline Gender getGender(){return this->gender;}

	int getYear();
	int getMonth();
	int getDay();

private:
	static GameDataManager *instance;

	int gold;			//金币
	int lottery;		//奖券
	int lvl;			//等级
	int score;			//分数
	int GameCheck;		//关卡
	int playGrade;		//玩家等级
	int playRank;		//玩家职衔
	std::string date;	//服务器时间
	int userID;			//用户ID
	int signData;		//签到数据 用31位&
	bool hasLogin;		//是否登陆
	std::string nickName;//昵称
	Gender gender;			//性别
public:
	int iconIndex;	//头像索引
	Vector<LevelInf*> levelInfArray;
	Vector<FishInf*> fishInfArray;
	Vector<CannonInf*> cannonArray;  
	Vector<CannonRateInf*> cannonRateArray;  //炮台倍率信息
	Vector<RoomInf*> roomInfArray;  
	Vector<GradeInf*> gradeArray;
	Vector<SignReward*> signRewardArray;
	Vector<CastInf*> castArray;
	Vector<FamilyName*> familyNameArray;//姓
	Vector<OtherName*> maleNameArray;//名（男）
	Vector<OtherName*> femaleNameArray;//名（女）
};

#define GData (GameDataManager::getInstance())

#endif