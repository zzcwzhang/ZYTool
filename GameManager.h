#ifndef GameManager_H_
#define GameManager_H_
#include "GameData.h"
class Player;
class Room;
class GameLayer;
//��Ϸ��������
typedef struct _RunTimeData
{
	short curRoomIndex;
	short duorenPlayeIndex;
	short  catchFishType;
	bool bUpLevel;
}RunTimeData;

class GameManager
{
public:
	static GameManager* getInstance();
	GameManager();
	~GameManager();

	void clearRunData();
	void encryption();

	void setMySelf(Player * player);
	Player* getMySelf();

	void setRoom(Room * room);
	Room* getRoom();

	bool isSingleMode();
	void setSingleMode(bool flag);
	//�����ı�
	void loadText();
	cocos2d::ValueMap getTextDict(std::string str);
	std::string getString(std::string dictKey,std::string key);

	void saveRecord();
	bool readRecord();

public:
	//��Ϸ��������
	RunTimeData * runData;
private:
	static GameManager* manager;
	//�ı��ֵ�
	cocos2d::ValueMap textDict;
	Player* _self;
	Room* _curRoom;
	bool bSingleMode;
};
#define  GMI (GameManager::getInstance())
#define  SELF (GameManager::getInstance()->getMySelf())
#define  pRunData (GameManager::getInstance()->runData)
#define  pRoom (GameManager::getInstance()->getRoom())
#define  gamelayer ((GameLayer*)pRoom)
#endif