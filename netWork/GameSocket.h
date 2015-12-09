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
	//ע�� �û���������
	void ToRegister(std::string username,std::string password,SocketCallBackFunc callBack);
	//��¼ ���û���������
	void ToLogin(std::string username,std::string password,SocketCallBackFunc callBack);
	//�ǳ��Ƿ���ڣ��ǳ�
	void ToNickname(int id,std::string nickname,SocketCallBackFunc callBack);
	//����ǳƣ��û���
	void ToRandom(int id,SocketCallBackFunc callBack);
	//ǩ�� ���û�ID
	void ToSign(int id,SocketCallBackFunc callBack);

public:
	//rank
	//�� ���û�ID ��ID
	void ToRank(int id,int cmd,SocketCallBackFunc callBack);
	//��������� ���û�ID ��ID
	void ToRankSelf(int id,int cmd,SocketCallBackFunc callBack);
	//����� ���û�ID,�����û�ID ��ID
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
	//��������
	/*
	userID
	level		��ɫ�ȼ�
	viplevel	vip�ȼ�
	coin		�������
	chargeScore	��ֵ����
	fishScore	����
	onlineTime	����ʱ��
	prop0		��������
	prop1		����������
	*/
	void SaveData(int userID,int level,int vipLevel,int coin,int chargeScore,int fishScore,int onlineTime,int prop0,int prop1,SocketCallBackFunc callBack);
};
#define  GSocket (GameSocket::getInstance())
#endif