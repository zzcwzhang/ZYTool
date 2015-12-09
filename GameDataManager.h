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

	int gold;			//���
	int lottery;		//��ȯ
	int lvl;			//�ȼ�
	int score;			//����
	int GameCheck;		//�ؿ�
	int playGrade;		//��ҵȼ�
	int playRank;		//���ְ��
	std::string date;	//������ʱ��
	int userID;			//�û�ID
	int signData;		//ǩ������ ��31λ&
	bool hasLogin;		//�Ƿ��½
	std::string nickName;//�ǳ�
	Gender gender;			//�Ա�
public:
	int iconIndex;	//ͷ������
	Vector<LevelInf*> levelInfArray;
	Vector<FishInf*> fishInfArray;
	Vector<CannonInf*> cannonArray;  
	Vector<CannonRateInf*> cannonRateArray;  //��̨������Ϣ
	Vector<RoomInf*> roomInfArray;  
	Vector<GradeInf*> gradeArray;
	Vector<SignReward*> signRewardArray;
	Vector<CastInf*> castArray;
	Vector<FamilyName*> familyNameArray;//��
	Vector<OtherName*> maleNameArray;//�����У�
	Vector<OtherName*> femaleNameArray;//����Ů��
};

#define GData (GameDataManager::getInstance())

#endif