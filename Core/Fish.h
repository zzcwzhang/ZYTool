//
//  Fish.h
//  MyGame
//
//  Created by zhiyxu on 13-11-6.
//
//

#ifndef __MyGame__Fish__
#define __MyGame__Fish__

#include "cocos2d.h"
#include "Bullet.h"
#include <iostream>
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;
USING_NS_CC;
class Room;

enum FishState{
	Live = 0,
	Dead
};
class Fish : public Sprite
{
public:
    enum FishType{
        FISH_XIAOGUANGYU = 0,
        FISH_XIAOCAOYU,
        FISH_REDAIYU,
		FISH_SHANWEIYU,
        FISH_DAYANJINYU,

        FISH_XIAOCHOUYU,
        FISH_HETUN,

        FISH_SHITOUYU,
		FISH_DENGLONGYU,
		FISH_REDAIZIYU,
		FISH_WUGUI,
		FISH_HUDIEYU,
		FISH_MEIRENQUN,
		FISH_JIANYU,
		FISH_MOGUIYU,
		FISH_DAYINSHA,//大银鲨

		FISH_HUANGJINSHA,//黄金鲨
		FISH_XIAOFEIYU,
		FISH_LONGXIA,
		FISH_HAITUN,

		FISH_JINHAITUN,//金海豚
		
		FISH_LVWUGUI,
		FISH_ALILAN,
		FISH_ZIMOGUIYU,
		FISH_QSDAYINSHA,//潜水大银鲨
		FISH_QSDAJINSHA,//潜水黄金鲨
		FISH_MEIRENYU,
		
		FISH_HUANGXIYI,//黄蜥蜴
		FISH_JINXIYI,       //金蜥蜴
		FISH_JINMOGUIYU,
		FISH_LONG,

		FISH_ZHADAN,//范围炸弹
		FISH_PAODAN,
		FISH_ThreeYuan,
		FISH_FourXi,
		FISH_SimilarBomb,
		FISH_ScreenBomb,
		FISH_JiangQuan1,
		FISH_JiangQuan2,
		FISH_JiangQuan3,
		FISH_JiangQuan4,
		FISH_JiangQuan5,
		FISH_JiangQuan6,
		FISH_JiangQuan7,
		FISH_Iphone6s,

        FISH_NORMAL_TYPEMAX,
        /*--new--*/
    };
    
    enum SpecialAttr{
        SPEC_HLYQ = 1,
        SPEC_HYLL,
        SPEC_TLYQ,
        SPEC_DASIXI,
        SPEC_ZDYQ,
        SPEC_YWYQ,
        SPEC_NONE
    };
    static bool _isFishLineGroup;
    //static Fish* create(GameLayer *parent);
	void removeFishShadow();
	void doshadowFishLifeAnimation();
	void doshadowFishDeadAnimation();
	static Fish* createFishshadow(FishType type);
	static Fish* createFish(FishType type);

    static Fish* createSpecificFish(Room *parent,FishType type,bool withPath=true);
    static Fish* createSpecFish(Room *parent);
    static void lockFish(FishType type,bool lck);
    static void lockFishRing(SpecialAttr type, bool lck);
    static FishType getRefreshFishType();
	static FishType getFishTypeforDynameter(int dynamete);//###
    static int getRefreshFishNum(FishType type);
    static bool isFishLocked(FishType type);
    Fish(FishType type);
    virtual ~Fish(void);
	void cleanReference();

	virtual void draw(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags);
	void onDraw(const Mat4 &transform, uint32_t flags);
    void goFish();
    int attackFish(Bullet *pBullet);
	bool outOfView();
	void generateFrameAnimation();

	Armature *getArmtrue();
	void armtureCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID);

    FishType getFishType(){return m_fishType;}
    virtual void setOpacity(GLubyte opacity);
    virtual void setColor(const Color3B& color3);
    void fishDeadCBK();
    void fishStopCBK();
    void unLockAndRelease();
    void updateShine(float dt);
    void setSpec(SpecialAttr spec);
	Animation* getActiveFrameAnimation(){return m_activeFrameAnimation;}
    cocos2d::Vec2 m_lastPoint;
    cocos2d::Color3B m_originColor;
    //Array* m_fishPath; 
	Vector<FiniteTimeAction*> m_fishPath;//###
    FishType m_fishType;
	FishState m_state;
    int m_speedTime;
    //int m_genCornNum;
    //int m_fishCD;
	int m_fishLife;//鱼生命值
	int f_dynameter;//鱼的倍率
	std::string fishName;
    SpecialAttr m_spec;
	Vector<Fish*> fishList;

	void checkFishHurt(bool bDie);
	int hurtCount;
protected:
    static const char * getFishFilePrefix(FishType type);
    
	void createThreeYuanFish(Armature *arm);
	void createFourXiFish(Armature *arm);

    virtual void generateFishPath();
    void generateCoin(int num = 3,Vec2 pos=Vec2(880,30),bool bMachine = false);
    void generateNum(int num);
    void playDeadSound();
    bool willDead(float rate);
    int dealWithTLYQ();
    int dealWithHLYQ();
    int dealWithZDYQ();
    int dealWithYWYQ();
    int dealWithZhadanFish();
	int killFish(Bullet* pBullet);//###
    float m_activeFrameDelay;
    float m_deadFrameDelay;
    cocos2d::Action*  m_fishAction;
	Animation* m_activeFrameAnimation;
	Animation* m_deadFrameAnimation;
    cocos2d::Sprite * m_specSprite;
    
    int m_activeFrameCount;
    int m_deadFrameCount;
    
   CustomCommand _customCommand;
    
    Room * m_parent;
    Armature *_armatrue;
	FishType armType;
    static int _freshRateArray[FISH_NORMAL_TYPEMAX];
    static bool _fishLockArray[FISH_NORMAL_TYPEMAX];
    static bool _fishRingLockArray[Fish::SPEC_NONE];
};

class FishInterface
{
public:
    virtual void removeFish(Fish *pf) = 0;
};

class SeaMonsterInterface
{
public:
    virtual void onGetDamage() = 0;
};

#endif /* defined(__MyGame__Fish__) */
