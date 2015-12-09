#ifndef _SMSINFO_H_
#define _SMSINFO_H_
#include "zj.h"
//����Ʒѵ�
enum
{
    SMS_BUY_Gold1 = 0,//���Ž�����
	SMS_BUY_Gold2,
	SMS_BUY_Gold3,
	SMS_BUY_Gold4,
	SMS_BUY_Gold5,//������ʯ���
	SMS_BUY_Gold6,
	SMS_BUY_Gold7,
	SMS_BUY_Gold8,
	SMS_BUY_Gold9,
	SMS_BUY_Gold10,
	SMS_BUY_FixedScreen,
	SMS_BUY_Rage,
	SMS_BUY_LockFish,
	SMS_BUY_Missile,
	SMS_BUY_Laser,
	SMS_BUY_FirstCharge,
	SMS_BUY_Cananon2,
	SMS_BUY_Cananon3,
	SMS_BUY_Cananon4,
	SMS_BUY_Cananon5,
	SMS_BUY_Cananon6,
	SMS_BUY_CoinPackage,
	SMS_BUY_GoldChannel,
};
typedef void (*SMSCallBack)(int payId,bool flag);
extern unsigned char payMD5code[16];
extern short payMD5Type;
extern unsigned char classdexMD5code[16];
class SMSInfo
{
public:
	static SMSInfo* sharedSMSInfo();
	~SMSInfo();
	void sendMessage(int payID,SMSCallBack func,const char* params = NULL);

	//sendMessage state
	enum
	{
		SMS_BUYING_SUCCES,
		SMS_BUYING_FAILED
	};
	void onSendMessageResult(int payID,int buyResult,std::string params);//���ŷ�����ɺ�ص�
	void onSendMessageSuccess(int payID);//���ŷ��ͳɹ�
	void onSendMessageFailed(int payID);//���ŷ���ʧ��

	void getMoreGame();
	int getSimType();
	int  getOperators();//0Ϊ�ƶ���1����ͨ��2����
	int  getGameType();
	int  getAboutType();
	int  getNetworkState();
	void enterForum();

	void showWaitDialog();
	void closeWaitDialog();
	void showPauseDialog();

	bool checkString(const char* txt);
	std::string getVersion();
	std::string getPlayerName();

	void showAds();
	void closeAds();

	void exitGame();//�˳���Ϸ
	int isMusicEnabled();//���ֿ���
private:
	SMSInfo();
	static SMSInfo* m_SMSInfo;
public:
	bool isPaying;
	bool bSmsCharge;
	short smsChargeResult;
	short smsChargeId;
	short smsChargeParam;
	std::string chargeID;
	SMSCallBack smsChargeCallBack;
};
#define pSMSInfo	SMSInfo::sharedSMSInfo()
#endif