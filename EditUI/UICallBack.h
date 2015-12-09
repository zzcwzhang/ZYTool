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
	/****�����ڵ�������ը***/
	void setBulletLockBlast(cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const char *movementID);
	/*****��������****/
	void setMisssionAppear();
	/*****�������****/
	void setLaserAppear();
	/****���⵼������׼��****/
	void MissileOrLaserReadyCallBack(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const char *movementID);


	/****�����****/
	void SetbigGoldArmaCallBack(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID);

	/********�ȼ�������������**********/
	void playGradeArmature(cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const std::string& movementID);
	void playGradeNextArmature(cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const char *movementID);

	/**********���߽��������ص�*************/
	void onlineRewardCallback();
	//��ʾ��½����
	void showLogin();

	//�رյ�����ʾ��
	void closePropDialog();
};
#endif