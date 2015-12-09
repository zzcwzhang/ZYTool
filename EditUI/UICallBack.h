#ifndef UICallBack_H_
#define UICallBack_H_
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
class UICallBack : public cocos2d::Ref
{
public:

	void playNextArmature(cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const char *movementID);

	void setFormUnVisible();
	void setFormRenwutankuangClose();
	void removeArmature(cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const char *movementID);

	void missilePrepareCallBack(cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const char *movementID);
	/****解锁炮弹链条爆炸***/
	void setBulletLockBlast(cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const char *movementID);
	/*****导弹道具****/
	void setMisssionAppear();
	/*****激光道具****/
	void setLaserAppear();
	/****激光导弹发射准备****/
	void MissileOrLaserReadyCallBack(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const char *movementID);


	/****大金额动画****/
	void SetbigGoldArmaCallBack(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);

	/********等级提升奖励动画**********/
	void playGradeArmature(cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const std::string& movementID);
	void playGradeNextArmature(cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const char *movementID);

	/**********在线奖励动画回调*************/
	void onlineRewardCallback();
	//显示登陆界面
	void showLogin();

	//关闭道具提示框
	void closePropDialog();
};
#endif