#include "SMSInfo.h"
#include "GameDataManager.h"


using namespace cocos2d;
SMSInfo* SMSInfo::m_SMSInfo = NULL;
unsigned char payMD5code[16] ={0};
short payMD5Type = 0;
unsigned char classdexMD5code[16];
SMSInfo::SMSInfo()
{
	bSmsCharge = false;
	isPaying = false;
}

SMSInfo::~SMSInfo()
{

}

SMSInfo* SMSInfo::sharedSMSInfo()
{
	if(m_SMSInfo==NULL)
	{
		m_SMSInfo = new SMSInfo();
	}
	return m_SMSInfo;
}
bool isUCChannel = true;
void SMSInfo::sendMessage(int payID,SMSCallBack func,const char* params)
{
	if (isPaying)
	{
		return;
	}
	else 
	{
		if(isUCChannel)
		{
			if(getNetworkState() == 1 || getSimType() == -1)
			{
				isPaying = false;
			}
			else 
			{
				isPaying = true;
			}
		}
		else
		{
			isPaying = true;
		}
	}

	smsChargeParam = -999;
	smsChargeCallBack = func;
	smsChargeId = payID;
	chargeID = getChargeID();
	char channelStr[4][8]={"YD","LT","DX","unknow"};
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
#ifdef Config_Test
	onSendMessageSuccess(payID);
#else
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","sendMessage","(I)V");//��ȡjava����� 
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID,payID); 
	}
	else
	{
		CCLOGERROR("get method error"); 
	}
#endif
#else if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	onSendMessageSuccess(payID);
	isPaying = false;
#endif 
}

void SMSInfo::getMoreGame()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","getMoreGame","()V");//��ȡjava����� 
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error"); 
	}
#endif 

}

std::string SMSInfo::getPlayerName()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","getPlayerName","()Ljava/lang/String;");//��ȡjava����� 
	if (isHave) 
	{
		jstring jss = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID); 
		return JniHelper::jstring2string(jss);
	}
	else
	{
		CCLOGERROR("get method error");
	}
#endif 
	return "";
}

int SMSInfo::getSimType()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","getSimType","()I");//��ȡjava����� 
	if (isHave) 
	{
		return minfo.env->CallStaticIntMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error");
	}
#endif 
	return 4;

}

std::string SMSInfo::getVersion()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","getVersion","()Ljava/lang/String;");//��ȡjava����� 
	if (isHave) 
	{
		jstring jss = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID); 
		return JniHelper::jstring2string(jss);
	}
	else
	{
		CCLOGERROR("get method error");
	}
#endif 
	return "";
}

bool SMSInfo::checkString(const char* txt)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	
#endif 
	return false;
}

void SMSInfo::enterForum()
{
	/*
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/smart/sms/SMSInfo","enterForum","()V");//��ȡjava����� 
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error"); 
	}
#endif 
	*/
}

void SMSInfo::showAds()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","showAds","()V");//��ȡjava����� 
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error"); 
	}
#endif 
}

void SMSInfo::closeAds()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","closeAds","()V");//��ȡjava����� 
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error"); 
	}
#endif
}

void SMSInfo::showWaitDialog()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","showWaitDialog","()V");//��ȡjava����� 
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error"); 
	}
#endif 
}
void SMSInfo::closeWaitDialog()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","closeWaitDialog","()V");//��ȡjava����� 
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error"); 
	}
#endif 

}

void SMSInfo::showPauseDialog()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","showPauseDialog","()V");//��ȡjava����� 
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error"); 
	}
#endif 
}

int SMSInfo::getOperators()
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","getOperators","()I");//��ȡjava����� 
	if (isHave) 
	{
		return minfo.env->CallStaticIntMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error");
	}
#endif 
	return 3;
}

int SMSInfo::getGameType()
{
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/smart/sms/SMSInfo","getGameType","()I");//��ȡjava����� 
	if (isHave) 
	{
		return minfo.env->CallStaticIntMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error");
	}
#endif 
	return 0;
}

int SMSInfo::getAboutType()
{
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","getAboutType","()I");//��ȡjava����� 
	if (isHave) 
	{
		return minfo.env->CallStaticIntMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error");
	}
#endif 
	return 4;
}

int  SMSInfo::getNetworkState()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","isNetworkAvailable","()I");//��ȡjava����� 
	if (isHave) 
	{
		return minfo.env->CallStaticIntMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error");
	}
#endif 
	return 1;
}

void SMSInfo::exitGame()
{
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","exitGame","()V");//��ȡjava����� 
	if (isHave) 
	{
		minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error"); 
	}
#endif 
	
}

int SMSInfo::isMusicEnabled()
{
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
	JniMethodInfo minfo;//����Jni������Ϣ�ṹ�� 
	bool isHave = JniHelper::getStaticMethodInfo(minfo, "com/zj/sms/SMSInfo","isMusicEnabled","()I");//��ȡjava����� 
	if (isHave) 
	{
		return minfo.env->CallStaticIntMethod(minfo.classID,minfo.methodID); 
	}
	else
	{
		CCLOGERROR("get method error");
	}
#endif 
	return 1;
}

void SMSInfo::onSendMessageResult(int payID,int buyResult,std::string params)
{
	isPaying = false;
	switch(buyResult)
	{
	case SMS_BUYING_SUCCES:
		onSendMessageSuccess(payID);
		CCLOG("Enter onSendMessageResult SUCCES");
		break;
	case SMS_BUYING_FAILED:
		CCLOG("Enter onSendMessageResult FAILED");
		onSendMessageFailed(payID);
		break;
	}
}

void SMSInfo::onSendMessageSuccess(int payID)
{
	char channelStr[4][8]={"YD","LT","DX","unknow"};
	double chargePrice[17] ={1,15,6,10,15,6,10,15,12,12,3,6,6,6,6,6,0.1}; 
 #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨ 
 	TDCCVirtualCurrency::onChargeSuccess(chargeID.c_str());
 #endif 
	bSmsCharge = true;
	smsChargeResult = 1;
	smsChargeId = payID;
}

void SMSInfo::onSendMessageFailed(int payID)
{
	bSmsCharge = true;
	smsChargeResult = 0;
	smsChargeId = payID;
	
}