#ifndef GameSocket_H_
#define GameSocket_H_
#include "netWork.h"
#include <string>
typedef void (*SocketCallBackFunc)(std::string str);
class GameSocket 
{
public:
	static GameSocket* getInstance();
	~GameSocket();

	void initScoket(const char* ipAdr,int port);
	void closeScoket();
	void openScoket();
private:
	GameSocket();
	static GameSocket*  _instance;
	bool isConnect;
public:
	SocketCallBackFunc pCallBack;
	Socket * pSocket;
	std::string ipAdr;
	int port;
public:
	void openConnect();
public:
	void registerGame(SocketCallBackFunc callBack);
	void loginGame(SocketCallBackFunc callBack);
	void signInGame(SocketCallBackFunc callBack);

public:
	//user
	//注册 用户名，密码
	void ToRegister(std::string username,std::string password,SocketCallBackFunc callBack);
	//登录 ：用户名，密码
	void ToLogin(std::string username,std::string password,SocketCallBackFunc callBack);
	//昵称是否存在：昵称
	void ToNickname(int id,std::string nickname,SocketCallBackFunc callBack);
	//随机昵称：用户名
	void ToRandom(int id,SocketCallBackFunc callBack);
	//签到 ：用户ID
	void ToSign(int id,SocketCallBackFunc callBack);

public:
	//rank
	//榜 ：用户ID 榜ID
	void ToRank(int id,int cmd,SocketCallBackFunc callBack);
	//榜个人排名 ：用户ID 榜ID
	void ToRankSelf(int id,int cmd,SocketCallBackFunc callBack);
	//榜点赞 ：用户ID,点赞用户ID 榜ID
	void ToGiveLiked(int id,int cmd,int likedId,int type,SocketCallBackFunc callBack);

public:
	//mail
	void ToLoadMails(int id,SocketCallBackFunc callBack);
	void ToLoadMail(int id,int mailId,SocketCallBackFunc callBack);
	void ToAcquireAtm(int id,int mailId,SocketCallBackFunc callBack);
	void ToDeleteMail(int id,int mailId,SocketCallBackFunc callBack);
	void ToDeleteMails(int id,SocketCallBackFunc callBack);

public:
	//heart
	void ToHeart(std::string str);
	//保存数据
	/*
	userID
	level		角色等级
	viplevel	vip等级
	coin		金币数量
	chargeScore	充值积分
	fishScore	经验
	onlineTime	在线时长
	prop0		导弹数量
	prop1		能量炮数量
	*/
	void SaveData(int userID,int level,int vipLevel,int coin,int chargeScore,int fishScore,int onlineTime,int prop0,int prop1,SocketCallBackFunc callBack);
};
#define  GSocket (GameSocket::getInstance())
#endif