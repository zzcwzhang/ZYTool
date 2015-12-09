#ifndef _SMSINFO_H_
#define _SMSINFO_H_
#include "zj.h"
//定义计费点
enum
{
    SMS_BUY_Gold1 = 0,//入门金币礼包
	SMS_BUY_Gold2,
	SMS_BUY_Gold3,
	SMS_BUY_Gold4,
	SMS_BUY_Gold5,//入门钻石礼包
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
	void onSendMessageResult(int payID,int buyResult,std::string params);//短信发送完成后回调
	void onSendMessageSuccess(int payID);//短信发送成功
	void onSendMessageFailed(int payID);//短信发送失败

	void getMoreGame();
	int getSimType();
	int  getOperators();//0为移动，1是联通，2电信
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

	void exitGame();//退出游戏
	int isMusicEnabled();//音乐开关
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