#include "Fish.h"
#include "GameLayer.h"
#include "Coin.h"
#include "Helper.h"
#include "Sound.h"
//#include "GameData.h"
#include "FishPath.h"
#include "GScene.h"
#include "GUILayer.h"
#include "GameDataManager.h"
#include "GameData.h"
#include "Tools.h"
#include "GameManager.h"
#include "SConfig.h"
#include "UICallBack.h"
#include "Player.h"
#include "UI.h"
#include "Room.h"
#include "Tools.h"
//#include "introLayer.h"
//#include "FlipCardBonusLayer.h"
bool Fish::_isFishLineGroup = false;
int Fish::_freshRateArray[Fish::FISH_NORMAL_TYPEMAX] = {
    100,// FISH_XIAOGUANGYU = 0,
    90,// FISH_XIAOCAOYU,
    90,// FISH_REDAIYU,
    80,// FISH_DAYANJINYU,
    80,// FISH_SHUIMU,
    70,// FISH_SHANWEIYU,
    70,// FISH_REDAIZIYU,
    60,// FISH_XIAOCHOUYU,
    60,// FISH_HETUN,
    50,// FISH_WUZEI,
    50,// FISH_SHITOUYU,
    45,// FISH_SHENXIANYU,
    45,// FISH_WUGUI,
    40,// FISH_DENGLONGYU,
    40,// FISH_SHIBANYU,
    35,// FISH_HUDIEYU,
    35,// FISH_LINGDANGYU,
    35,// FISH_JIANYU,
    30,// FISH_MOGUIYU,
    30,// FISH_FEIYU,
    100,//30,// FISH_LONGXIA,
    100,//25,// FISH_HAITUN,modified
    100,//25,//FISH_WHITESHARK
	100,//25,// FISH_DAYINSHA,
    100,//25,// FISH_LANJING,
//    25,// FISH_HUANGJINGJINGYU,
//    40,// FISH_HUANGJINGYU,
//    30,// FISH_BYMOGUIYU,
//    30,// FISH_BYWUGUI,
    30,// FISH_ZHENZHUBEI,
//    40,// FISH_LANSHA,
    30,// FISH_XIAOFEIYU,
    50,// FISH_ALILAN,
//    20,// FISH_HAIMA,
    100,//0,// FISH_ZHADANFISH,
    0,// FISH_NORMAL_TYPEMAX (NO USE)
    80// FISH_XIAOHUANGCI
  // FISH_LANGUANGYU
    // FISH_QICAIYU
};


bool Fish::_fishLockArray[Fish::FISH_NORMAL_TYPEMAX] = {
    false,false,false,false,false,false,false,false,false,false,
    false,false,false,false,false,false,false,false,false,false,
    false,false,false,false,false,false,false,false,false,false,false
};

bool Fish::_fishRingLockArray[Fish::SPEC_NONE] = {
    false,false,false,false,false,false
};


#define SPEED_TIME_A 6
#define SPEED_TIME_B 8
#define SPEED_TIME_C 12
#define SPEED_TIME_D 18
#define SPEED_TIME_E 22
#define SPEED_TIME_F 30


float downRate = 0.5f;
static int fishesCount = 0;
Fish::Fish(FishType type):m_fishType(type),m_spec(SPEC_NONE),m_specSprite(NULL)
{
	
	fishesCount++;

    m_activeFrameDelay = 0.15f;
    m_deadFrameDelay = 0.15f;
    m_originColor = getColor();
	m_state = Live;
	_armatrue = nullptr;
	armType = FISH_XIAOGUANGYU;
	FishInf* finf = GData->getFishInf((int)type);

	f_dynameter = finf->rate;
	m_fishLife = finf->hp;
	m_speedTime = CCRANDOM_0_1()*1? finf->maxSpeed : finf->minSpeed;
	m_speedTime = 250/m_speedTime;
	fishName = finf->fishname;

    switch(m_fishType){
        case FISH_XIAOGUANGYU:
            m_activeFrameCount = 6;
            m_deadFrameCount = 2;

            break;
        case FISH_XIAOCAOYU:
            m_activeFrameCount = 8;
            m_deadFrameCount = 2;
            break;
        case FISH_REDAIYU:
            m_activeFrameCount = 12;
            m_deadFrameCount = 2;
            break;
        case FISH_DAYANJINYU:
            m_activeFrameCount = 12;
            m_deadFrameCount = 3;
            break;
        case FISH_SHANWEIYU:
            m_activeFrameCount = 12;
            m_deadFrameCount = 3;
            break;
        case FISH_XIAOCHOUYU://
            m_activeFrameCount = 13;
            m_deadFrameCount = 3;
            break;
        case FISH_HETUN:
            m_activeFrameCount = 18;
            m_deadFrameCount = 3;
            break;
        case FISH_SHITOUYU:
            m_activeFrameCount = 10;
            m_deadFrameCount = 3;
            break;
        case FISH_DENGLONGYU:
            m_activeFrameCount = 12;
            m_deadFrameCount = 2;
            break;
        case FISH_REDAIZIYU:
            m_activeFrameCount = 12;
            m_deadFrameCount = 4;
            break;
        case FISH_WUGUI:// 
            m_activeFrameCount = 8;
            m_deadFrameCount = 6;
            break;
        case FISH_HUDIEYU:
            m_activeFrameCount = 6;
            m_deadFrameCount = 3;
            break;
        case FISH_MEIRENQUN:
            m_activeFrameCount = 12;
            m_deadFrameCount = 3;
            break;
        case FISH_JIANYU:
            m_activeFrameCount = 10;
            m_deadFrameCount = 3;
            break;
        case FISH_MOGUIYU:
            m_activeFrameCount = 12;
            m_deadFrameCount = 3;
            break;
        case FISH_DAYINSHA:
            m_activeFrameCount = 12;
            m_deadFrameCount = 3;
            break;
        case FISH_HUANGJINSHA:// 
            m_activeFrameCount = 12;
            m_deadFrameCount = 3;
            break;
        case FISH_XIAOFEIYU:
            m_activeFrameCount = 12;
            m_deadFrameCount = 3;
            break;
		case FISH_LONGXIA:
			m_activeFrameCount = 13;
			m_deadFrameCount = 0;
			break;
        case FISH_HAITUN:
            m_activeFrameCount = 12;
            m_deadFrameCount = 3;
            break;
        case FISH_JINHAITUN:
			m_activeFrameCount = 9;
			m_deadFrameCount = 3;
            break;
        case FISH_LONG:
            m_activeFrameCount = 9;
            m_deadFrameCount = 4;
            break;
        case FISH_LVWUGUI:
            m_activeFrameCount = 11;
            m_deadFrameCount = 6;
            break;
		case FISH_ALILAN:// 
			m_activeFrameCount = 15;
			m_deadFrameCount = 4;
			break;
        case FISH_MEIRENYU:// 
            m_activeFrameCount = 7;
            m_deadFrameCount = 4;
            break;
        case FISH_ZIMOGUIYU:// 
            m_activeFrameCount = 13;
            m_deadFrameCount = 3;
            break;
        case FISH_QSDAYINSHA:
            m_activeFrameCount = 13;
            m_deadFrameCount = 3;

            break;
        case FISH_QSDAJINSHA:
            m_activeFrameCount = 13;
            m_deadFrameCount = 3;
            break;
        case FISH_HUANGXIYI:
            m_activeFrameCount = 9;
            m_deadFrameCount = 2;
            break;
        case FISH_JINXIYI:
            m_activeFrameCount = 10;
            m_deadFrameCount = 2;
            break;
		case FISH_JINMOGUIYU:
			m_activeFrameCount = 12;
			m_deadFrameCount = 3;
			break;
       
    }

//     if(m_fishCD !=0) {
//         if(_fishLockArray[m_fishType] == false){
//             lockFish(m_fishType, true);
//         }
//     }
}


Fish::~Fish()
{
	

	fishesCount--;
	log("fishesCount %d",fishesCount);
}

void Fish::cleanReference()
{
	m_fishPath.clear();
	fishList.clear();
	m_activeFrameAnimation->release();
	m_deadFrameAnimation->release();
}

void Fish::lockFish(FishType type,bool lck)
{
    if(type >= FISH_NORMAL_TYPEMAX)
        return;
    _fishLockArray[type] = lck;
}

void Fish::lockFishRing(SpecialAttr type, bool lck)
{
    if(type >= sizeof(_fishRingLockArray))
        return;
    _fishRingLockArray[type] = lck;
}

#if 0
Fish* Fish::create(GameLayer *parent)
{
    static int freshRateTotal = 0;
    int i;
    if(freshRateTotal == 0) {
        for(i=0; i < FISH_TYPEMAX; i++) {
            if(_fishLockArray[i] == false)
                freshRateTotal += _freshRateArray[i];
        }
    }
    
    int t = arc4random() % freshRateTotal;
    for(i=0; i < FISH_TYPEMAX; i++) {
        if(_fishLockArray[i])
            continue;
        if(t < _freshRateArray[i])
            break;
        t -= _freshRateArray[i];
    }
    
    return createSpecificFish(parent,(FishType)i);
    //return createSpecificFish(parent,Fish::FISH_HUANGJINGJINGYU);
}
#endif

Fish::FishType Fish::getRefreshFishType()
{
    int i = CCRANDOM_0_1()*FISH_HUDIEYU;
	return (FishType)i;
}

Fish::FishType Fish::getFishTypeforDynameter(int dynamete)
{
	int Num = 0;
	switch(dynamete)
	{
	case 2:
		return FISH_XIAOGUANGYU;
	case 3:
		return FISH_XIAOCAOYU;
	case 4:
		return FISH_REDAIYU;
	case 5:
		return FISH_DAYANJINYU;
	case 6:
		return FISH_SHANWEIYU;
	case 7:
		return FISH_XIAOCHOUYU;
	case 8:
		return FISH_HETUN;
	case 9:
		return FISH_SHITOUYU;
	case 10:
		return FISH_DENGLONGYU;
	case 11:
		return FISH_REDAIZIYU;
	case 12:
		Num = CCRANDOM_0_1()*2;
		switch (Num)
		{
		case 0:
			return FISH_WUGUI;
		case 1:
			return FISH_LVWUGUI;
		case 2:
			return FISH_JINHAITUN;
		}
	case 15:
		Num = CCRANDOM_0_1()*1;
		switch (Num)
		{
		case 0:
			return FISH_HUDIEYU;
		case 1:
			return FISH_JIANYU;
		}
	case 18:
		Num = CCRANDOM_0_1()*2;
		switch(Num)
		{
		case 0:
			return FISH_XIAOFEIYU;
		case 1:
			return FISH_LONGXIA;
		case 2:
			return FISH_HAITUN;
		}
	case 20:
		return FISH_MEIRENQUN;
	case 25:
		return FISH_MOGUIYU;
	case 30: 
		return FISH_DAYINSHA;
	case 35:
		Num = CCRANDOM_0_1()*2;
		switch(Num)
		{
		case 0:
			return FISH_HUANGJINSHA;
		case 1:
			return FISH_QSDAYINSHA;
		case 2:
			return FISH_JINMOGUIYU;
		}
	case 40:
		return FISH_ALILAN;
	case 50:
		return FISH_ZIMOGUIYU;
	case 120:
		return FISH_QSDAJINSHA;
	case 130:
		return FISH_HUANGXIYI;
	case 140:
		return FISH_JINXIYI;
	case 150:
		return FISH_MEIRENYU;
	case 160:
		return FISH_LONG;
	}
	return FISH_XIAOGUANGYU;
}

int Fish::getRefreshFishNum(FishType type)
{
    switch(type){
        case FISH_XIAOGUANGYU:
            return CCRANDOM_0_1()*4+4;
            break;
        case FISH_XIAOCAOYU:
            return CCRANDOM_0_1()*3+4;
        case FISH_REDAIYU:
            return CCRANDOM_0_1()*3+2;
        case FISH_DAYANJINYU:
		case FISH_SHANWEIYU:
        case FISH_XIAOCHOUYU:
            return CCRANDOM_0_1()*2+2;
        case FISH_HETUN:
        case FISH_SHITOUYU:
        case FISH_DENGLONGYU:
        case FISH_REDAIZIYU:
       
            return CCRANDOM_0_1()*2;
        case FISH_WUGUI:
            return CCRANDOM_0_1()*3;
        case FISH_HUDIEYU:
            return 4;
        case FISH_MEIRENQUN:
        case FISH_JIANYU:
        case FISH_MOGUIYU:
			return CCRANDOM_0_1()*2+1;
		case FISH_DAYINSHA:
		case FISH_HUANGJINSHA:
		case FISH_XIAOFEIYU:
        case FISH_HAITUN:
			return CCRANDOM_0_1()*2;
		case FISH_JINHAITUN:
			return 1;
		case FISH_LONG:
			return CCRANDOM_0_1()*2;
		case FISH_LVWUGUI:
			return CCRANDOM_0_1()*4;
		case FISH_ALILAN:
			return CCRANDOM_0_1()*2+2;
		case FISH_MEIRENYU:
			return CCRANDOM_0_1()*2;
		case FISH_ZIMOGUIYU:
			return CCRANDOM_0_1()*2;
		case FISH_QSDAYINSHA:
		case FISH_QSDAJINSHA:
		case FISH_HUANGXIYI:
		case FISH_JINXIYI:
            return CCRANDOM_0_1()*2;
		case FISH_JINMOGUIYU:
			return CCRANDOM_0_1()*3;
        default:
            return 1;
    }
}

Fish* Fish::createFish(FishType type)
{
	Fish * n = new Fish(type);
	n->init();
	n->generateFrameAnimation();
	n->autorelease();
	return n;
}

Fish* Fish::createSpecFish(Room *parent)
{
    FishType specArray[] = {
//         FISH_REDAIZIYU,
//         FISH_XIAOCHOUYU,
//         FISH_HETUN,
//         FISH_SHITOUYU,
//         FISH_DENGLONGYU,	
//         FISH_WUGUI,
//         FISH_HUDIEYU
		FISH_MEIRENQUN,
		FISH_JIANYU,
		FISH_MOGUIYU,
		FISH_DAYINSHA,//大银鲨
		FISH_HUANGJINSHA,//黄金鲨
		FISH_XIAOFEIYU,
		FISH_HAITUN,
		FISH_JINHAITUN,
		FISH_LONG,
		FISH_LVWUGUI,
		FISH_ALILAN,
		FISH_MEIRENYU,
		FISH_ZIMOGUIYU,
		FISH_QSDAYINSHA,//潜水大银鲨
		FISH_QSDAJINSHA,//潜水黄金鲨
		FISH_HUANGXIYI,//黄蜥蜴
		FISH_JINXIYI,       //金蜥蜴
		FISH_JINMOGUIYU,
		FISH_ThreeYuan,
		FISH_FourXi,
		FISH_JiangQuan1,
		FISH_JiangQuan2,
		FISH_JiangQuan3,
		FISH_JiangQuan4,
		FISH_JiangQuan5,
		FISH_JiangQuan6,
		FISH_JiangQuan7,
		FISH_Iphone6s,
    };
    int count = sizeof(specArray)/sizeof(specArray[0]);
	if(GMI->isSingleMode())
	{
		count  = count - 10;
	}
    int i = CCRANDOM_0_1()*count;
    Fish *p = createSpecificFish(parent,specArray[i]);
    p->m_speedTime = 18;
    return p;
}


Fish* Fish::createSpecificFish(Room *parent,FishType type,bool withPath)
{
    Fish * n = new Fish(type);
    n->init();
    n->generateFrameAnimation();
    if(withPath)
        n->generateFishPath();
    n->autorelease();
    n->m_parent = parent;
    return n;
}

void Fish::generateFishPath()
{
    FishPathFactory::createFishPath(this);
}

bool Fish::outOfView()
{
	float fx = this->getPositionX();
	float fy = this->getPositionY();

	if (fx<0||fx>SCREEN_WIDTH)
	{
		return true;
	}

	if (fy<0||fy>SCREEN_HEIGHT)
	{
		return true;
	}
	return false;
}

void Fish::goFish()
{
	Action*  fishaction = NULL;
	FiniteTimeAction *callFunc = CallFunc::create(this,callfunc_selector(Fish::fishStopCBK));
	if(m_fishType < FISH_ZHADAN)
	{
		Animate*animate = Animate::create(m_activeFrameAnimation);
		this->runAction(RepeatForever::create(animate));
	}
	if (m_fishPath.size()>0)
	{
		m_fishPath.pushBack(callFunc);
		fishaction = Sequence::create(m_fishPath);//Spawn::createWithTwoActions(,);
	}
	if(GMI->isSingleMode())
	{
		GameLayer *layer = (GameLayer*)GMI->getRoom();
		layer->getObjActionManager()->addAction(fishaction,this,false);
		//this->setPosition(Vec2(SCREEN_WIDTH/2,SCREEN_HEIGHT/2));
	}
	else
	{
		this->runAction(fishaction);
	}
}

int Fish::dealWithTLYQ()
{
    return 0;
}


void Fish::setColor( const Color3B& color3 )
{
	Vector<Node*>child = getChildren();
	for(vector<Node*>::const_iterator citer=child.begin();citer!=child.end();citer++)
	{
		Sprite* sp = (Sprite*)*citer;
		sp->setColor(color3);
	}
	
	Sprite::setColor(color3);
}

void Fish::setOpacity( GLubyte opacity )
{
	Vector<Node*>child = getChildren();
	for(vector<Node*>::const_iterator citer=child.begin();citer!=child.end();citer++)
	{
		Sprite* sp = (Sprite*)*citer;
		sp->setOpacity(opacity);
	}

	Sprite::setOpacity(opacity);
}

int Fish::dealWithZhadanFish()
{
    return 0;
}

int Fish::dealWithHLYQ()
{
    float rate = 0.0f;
    int score = 0;
    switch(m_fishType ) {
        case FISH_REDAIZIYU:
        case FISH_XIAOCHOUYU:
            rate = 0.05f;
            break;
        case FISH_HETUN:
        case FISH_SHITOUYU:
            rate = 0.06f;
            break;
       
        case FISH_WUGUI:
            rate = 0.08f;
            break;
        case FISH_DENGLONGYU:
            rate = 0.09f;
            break;
        case FISH_HUDIEYU:
            rate = 0.1f;
            break;
        default:
            break;
    }
   
    if(score < 1000)
        score = 1000;
    if(score > 1000000)
        score = 1000000;
    return score;
}


extern Rect shrinkRect(Rect rc, float xr, float yr);


int Fish::dealWithZDYQ()
{
    return 0;
}

int Fish::dealWithYWYQ()
{
    return 0;
}

void Fish::updateShine(float dt)
{
    Color3B c1 = getColor();
    if(c1.r != 125){
        setColor(Color3B(125,0,0));
    }else{
        setColor(m_originColor);
    }
}

void Fish::unLockAndRelease()
{
    lockFish(m_fishType,false);
    removeFromParentAndCleanup(true);
}

void Fish::fishDeadCBK()
{
	if(GMI->isSingleMode())
	{
		GameLayer *layer = (GameLayer*)GMI->getRoom();
		layer->getObjActionManager()->removeAllActionsFromTarget(this);
	}
	cleanReference();
	pRoom->removeFish(this);
	this->removeFromParentAndCleanup(true); 
	log("my releases %d",_referenceCount);
	//this->release();
}

void Fish::fishStopCBK()
{
	Fish* fish = (Fish*)m_parent->getChildByTag(this->getTag()+FISHTAGPOOR);
	if(fish)
	{
		m_parent->removeFishShadow(fish);
		fish->cleanReference();
		fish->removeFromParentAndCleanup(true);
		
		delete fish;
	}
	cleanReference();
    m_parent->removeFish(this);
    this->removeFromParentAndCleanup(true);
}


const char * Fish::getFishFilePrefix(FishType type)
{
    switch (type) {
        case FISH_XIAOGUANGYU:
            return "xiaoguangyu";
        case FISH_XIAOCAOYU:
            return "xiaocaoyu";
        case FISH_REDAIYU:
            return "redaiyu";
        case FISH_DAYANJINYU:
            return "dayanjinyu";
        case FISH_SHANWEIYU:
            return "shanweiyu";
		case FISH_XIAOCHOUYU:
			return "xiaochouyu";
		case FISH_HETUN:
			return "hetun";
		case FISH_SHITOUYU:
			return "shitouyu";
		case FISH_DENGLONGYU:
			return "denglongyu";
        case FISH_REDAIZIYU:
            return "redaiziyu";
        case FISH_WUGUI:
            return "wugui";
        case FISH_HUDIEYU:
            return "hudieyu";
        case FISH_MEIRENQUN:
            return "meirenqun";
        case FISH_JIANYU:
            return "jianyu";
        case FISH_MOGUIYU:
            return "moguiyu";
        case FISH_DAYINSHA:
            return "dayinsha";
        case FISH_HUANGJINSHA:
            return "huangjinsha";
        case FISH_XIAOFEIYU:
            return "xiaofeiyu";
		case FISH_LONGXIA:
			return "longxia";
        case FISH_HAITUN:
            return "haitun";
        case FISH_JINHAITUN:
            return "jinhaitun";
        case FISH_LONG:
            return "long";
        case FISH_LVWUGUI:
            return "lvwugui";
        case FISH_ALILAN:
            return "alilan";
		case FISH_MEIRENYU:
			return "meirenyu";
        case FISH_ZIMOGUIYU:
            return "zimoguiyu";
        case FISH_QSDAYINSHA:
            return "qsdayinsha";
        case FISH_QSDAJINSHA:
            return "qsdajinsha";
        case FISH_HUANGXIYI:
            return "huangxiyi";
        case FISH_JINXIYI:
            return "jinxiyi";
		case FISH_JINMOGUIYU:
			return "jinmoguiyu";
        default:
            return "";
    }
}


Armature *Fish::getArmtrue()
{
	return _armatrue;
}

void Fish::createThreeYuanFish(Armature *arm)
{
	int count = 11;
	FishType type = (FishType)getRandom(count);
	armType = type;
	Fish *fish = Fish::createFish(type);
	Animate*animate = Animate::create(fish->m_activeFrameAnimation);
	fish->runAction(RepeatForever::create(animate));
	arm->addChild(fish);
	fish->setTag(3331);
	fishList.pushBack(fish);

	fish = Fish::createFish(type);
	animate = Animate::create(fish->m_activeFrameAnimation);
	fish->runAction(RepeatForever::create(animate));
	arm->addChild(fish);
	fish->setPosition(Vec2(-160,0));
	fish->setTag(3332);
	fishList.pushBack(fish);

	fish = Fish::createFish(type);
	animate = Animate::create(fish->m_activeFrameAnimation);
	fish->runAction(RepeatForever::create(animate));
	arm->addChild(fish);
	fish->setPosition(Vec2(160,0));
	fish->setTag(3333);
	fishList.pushBack(fish);
}

void Fish::createFourXiFish(Armature *arm)
{
	int count = 11;
	FishType type = (FishType)getRandom(count);
	armType = type;
	Fish *fish = Fish::createFish(type);
	Animate*animate = Animate::create(fish->m_activeFrameAnimation);
	fish->runAction(RepeatForever::create(animate));
	arm->addChild(fish);
	fish->setTag(44441);
	fish->setPosition(Vec2(-74,60));
	fishList.pushBack(fish);

	fish = Fish::createFish(type);
	animate = Animate::create(fish->m_activeFrameAnimation);
	fish->runAction(RepeatForever::create(animate));
	arm->addChild(fish);
	fish->setPosition(Vec2(-74,-110));
	fish->setTag(44442);
	fishList.pushBack(fish);

	fish = Fish::createFish(type);
	animate = Animate::create(fish->m_activeFrameAnimation);
	fish->runAction(RepeatForever::create(animate));
	arm->addChild(fish);
	fish->setPosition(Vec2(80,-40));
	fish->setTag(44443);
	fishList.pushBack(fish);

	fish = Fish::createFish(type);
	animate = Animate::create(fish->m_activeFrameAnimation);
	fish->runAction(RepeatForever::create(animate));
	arm->addChild(fish);
	fish->setPosition(Vec2(80,130));
	fish->setTag(44444);
	fishList.pushBack(fish);
}

void Fish::generateFrameAnimation()
{
	if(m_fishType >= FISH_ZHADAN)
	{
		FishInf* finf = GData->getFishInf((int)m_fishType);
		setTexture("specialFish.png");
		_armatrue = Armature::create(finf->fishname);
		switch (m_fishType)
		{
		case Fish::FISH_ZHADAN:
			_armatrue->getAnimation()->play("tsy_2_01");
			break;
		case Fish::FISH_PAODAN:
			_armatrue->getAnimation()->play("tsy_1_01");
			break;
		case Fish::FISH_ThreeYuan:
			_armatrue->getAnimation()->play("tsy_5_01");
			createThreeYuanFish(_armatrue);
			break;
		case Fish::FISH_FourXi:
			_armatrue->getAnimation()->play("tsy_4_01");
			createFourXiFish(_armatrue);
			break;
		case Fish::FISH_SimilarBomb:
			break;
		case Fish::FISH_ScreenBomb:
			_armatrue->getAnimation()->play("tsy_3_01");
			break;
		case Fish::FISH_JiangQuan1:
			_armatrue->getAnimation()->playWithIndex(2);
			break;
		case Fish::FISH_JiangQuan2:
			_armatrue->getAnimation()->playWithIndex(2);
			break;
		case Fish::FISH_JiangQuan3:
			_armatrue->getAnimation()->playWithIndex(2);
			break;
		case Fish::FISH_JiangQuan4:
			_armatrue->getAnimation()->playWithIndex(1);
			break;
		case Fish::FISH_JiangQuan5:
			_armatrue->getAnimation()->playWithIndex(1);
			break;
		case Fish::FISH_JiangQuan6:
			_armatrue->getAnimation()->playWithIndex(1);
			break;
		case Fish::FISH_JiangQuan7:
			_armatrue->getAnimation()->playWithIndex(0);
			break;
		case Fish::FISH_Iphone6s:
			_armatrue->getAnimation()->playWithIndex(0);
			break;
		default:
			break;
		}
		this->setContentSize(_armatrue->getContentSize());
		_armatrue->setAnchorPoint(Vec2(0,0));
		this->addChild(_armatrue);
	}
	else
	{
		char str[32];
		memset(str, '0', sizeof(str));
		Vector<SpriteFrame*> animFrames;
		for(int i=0;i <m_activeFrameCount;i++)
		{

			sprintf(str,"%s_%d.png",/*getFishFilePrefix(m_fishType)*/fishName.c_str(),i);  //通过下标动态创建精灵

			auto *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
			animFrames.pushBack(frame);

			if(i==0){//默认添加第一帧图到界面上
				initWithSpriteFrame(frame);
				//setPosition(Vec2(480,320));
			}  
		}

		m_activeFrameAnimation = Animation::createWithSpriteFrames(animFrames,m_activeFrameDelay);//通过集合创建动画
		m_activeFrameAnimation->retain();

		memset(str, '0', sizeof(str));

		Vector<SpriteFrame*> animFrames2;
		for(int i=0;i <m_deadFrameCount;i++)
		{
			if (m_fishType==FISH_LONGXIA)
			{
				m_deadFrameDelay = 0.05f;
				sprintf(str,"%s_%d.png",fishName.c_str(),i);
			}
			else
			{
				sprintf(str,"%s_d%d.png",fishName.c_str(),i);
			}

			SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
			animFrames2.pushBack(frame);
		}

		if (m_fishType==FISH_WUGUI ||
			m_fishType==FISH_LVWUGUI)
		{
			m_deadFrameDelay = 0.05f;
		}

		m_deadFrameAnimation = Animation::createWithSpriteFrames(animFrames2,m_deadFrameDelay);//通过集合创建动画
		m_deadFrameAnimation->retain();
	}
}

void Fish::generateCoin(int onum,Vec2 pos,bool bMachine)
{ 

	Vec2 pt = this->getPosition();

	int num = 0;
	int type = 0;

	if (onum<=3000)
	{
		num = 1;
	}
	else 
	{
		num = 2;
	}

	for(int i=0; i < num ;i++)
	{
		float angle = CCRANDOM_0_1()*360;
		angle = angle*M_PI/180;
		Coin::CoinType _type = Coin::COIN_TYPE_GOLDBIG;
		if(bMachine)
		{
			_type =  Coin::COIN_TYPE_GOLDSMALL;
		}
		
		Coin*pc = Coin::create(_type);
		pc->setPosition(pt);
		pc->addLineCoinPath(0.2f, Vec2(pt.x+100*cos(angle),pt.y+100*sin(angle)));
		pc->m_coinPath.pushBack(DelayTime::create(0.5f));
		pc->addLineCoinPath(0.2f,pt);
		pc->m_coinPath.pushBack(DelayTime::create(0.2f * i));

		pc->addLineCoinPath(1, pos);
		pc->goCoin();
		GScene->addChild(pc,GUILOCALZORDER);
	}
    //Sound::Instance()->playEffect("Coin.mp3");
}

void Fish::generateNum(int num)
{
	Label *np = Label::createWithBMFont("fonts/num_tcsz.fnt",ConvertToString(num));
	np->setPosition(this->getPosition());
	//np->setScale(0.4f);
	pRoom->addChild(np,PHYSICSLZORDER);

	Spawn* sp2 = Spawn::createWithTwoActions(FadeOut::create(2), MoveBy::create(2, Vec2(0,100)));

	FiniteTimeAction *callFunc = CallFunc::create(np,callfunc_selector(Label::removeFromParent));
	np->runAction(Sequence::create(MoveBy::create(0.15f, Vec2(0,20)), sp2, callFunc, NULL));
}

void Fish::playDeadSound()
{
    const char *p = NULL;
    switch(m_fishType)
	{
        case FISH_HUDIEYU:
            p = "fish04.mp3";
            break;
       
        case FISH_MOGUIYU:
//        case FISH_BYMOGUIYU:
            p = "fish06.mp3";
            break;
        case FISH_LONGXIA:
            p = "fish07.mp3";
            break;
        case FISH_HAITUN:
            p = "fish08.mp3";
            break;
		
        case FISH_DAYINSHA:
            p = "fish09.mp3";
            break;
        
        case FISH_JIANYU:
        case FISH_MEIRENYU:
//        case FISH_HUANGJINGYU:
            p = "fish00.mp3";
            break;
        default:
            p = NULL;
            break;
    }
    
    if( p!= NULL)
	{
        Sound::Instance()->playEffect(p);
    }
}

bool Fish::willDead(float rate)
{
	float probaNum = 0;
	float proba = 0;
	probaNum = rate*10000;
	proba = getRandom(10000);
	if (proba<probaNum)
	{
		return true;
	}
	return false;	
}

void Fish::armtureCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType==COMPLETE)
	{
		if(movementID.compare("tsy_5_02") == 0)
		{
			_armatrue->getAnimation()->play("tsy_5_01");
			//_armatrue->getAnimation()->setMovementEventCallFunc(this,nullptr);
		}
		else if(movementID.compare("tsy_4_02") == 0)
		{
			_armatrue->getAnimation()->play("tsy_4_01");
			//_armatrue->getAnimation()->setMovementEventCallFunc(this,nullptr);
		}
		else if(movementID.compare("tsy_3_02") == 0)
		{
			_armatrue->getAnimation()->play("tsy_3_01");
			//_armatrue->getAnimation()->setMovementEventCallFunc(this,nullptr);
		}
		else if(movementID.compare("tsy_2_02") == 0)
		{
			_armatrue->getAnimation()->play("tsy_2_01");
			//_armatrue->getAnimation()->setMovementEventCallFunc(this,nullptr);
		}
		else if(movementID.compare("tsy_1_02") == 0)
		{
			_armatrue->getAnimation()->play("tsy_1_01");
			//_armatrue->getAnimation()->setMovementEventCallFunc(this,nullptr);
		}
		else if(movementID.compare("tsy_1_03") == 0
		||movementID.compare("tsy_2_03") == 0
		||movementID.compare("tsy_3_03") == 0
		||movementID.compare("tsy_4_03") == 0
		||movementID.compare("tsy_5_03") == 0)
		{
			this->fishDeadCBK();
		}
	}
}

int Fish::attackFish( Bullet *pBullet )
{
	Player *player = pBullet->getCannon()->getPlayer();
	int originScore = 0;
	int extraScore = 0;
	float rate;
	if(pBullet)
	{
		rate = pBullet->hit_score/m_fishLife + pBullet->getExtraRate() +pRoom->getInf()->rp;
	}
	if(m_fishType == FISH_Iphone6s)
	{
		rate = -500.0f;
	}
	if(pBullet->atkTime <= 0)
	{
		rate = 0;
	}
	if (!(pBullet->bulletType==MissileCannon||pBullet->bulletType==LaserCannon))	
	{
		if (!willDead(rate))
		{
			switch (m_fishType)
			{
			case Fish::FISH_ZHADAN:
				_armatrue->getAnimation()->play("tsy_2_01");
				_armatrue->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Fish::armtureCallBack));
				break;
			case Fish::FISH_PAODAN:
				_armatrue->getAnimation()->play("tsy_1_01");
				_armatrue->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Fish::armtureCallBack));
				break;
			case Fish::FISH_ThreeYuan:
				_armatrue->getAnimation()->play("tsy_5_02");
				_armatrue->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Fish::armtureCallBack));
				break;
			case Fish::FISH_FourXi:
				_armatrue->getAnimation()->play("tsy_4_02");
				_armatrue->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Fish::armtureCallBack));
				break;
			case Fish::FISH_SimilarBomb:
				break;
			case Fish::FISH_ScreenBomb:
				_armatrue->getAnimation()->play("tsy_3_01");
				_armatrue->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Fish::armtureCallBack));
				break;
			case Fish::FISH_JiangQuan1:
			case Fish::FISH_JiangQuan2:
			case Fish::FISH_JiangQuan3:
			case Fish::FISH_JiangQuan4:
			case Fish::FISH_JiangQuan5:
			case Fish::FISH_JiangQuan6:
			case Fish::FISH_JiangQuan7:
			case Fish::FISH_Iphone6s:
				if(!_armatrue->getActionByTag(-10))
				{
					TintTo *to = TintTo::create(0.1,Color3B(255,0,0));
					TintTo* back = TintTo::create(0.1,Color3B(255,255,255));
					Sequence *seq = Sequence::create(to,back,nullptr);
					seq->setTag(-10);
					_armatrue->runAction(seq);
				}
				break;
			default:
				if(!this->getActionByTag(-10))
				{
					TintTo *to = TintTo::create(0.1,Color3B(255,0,0));
					TintTo* back = TintTo::create(0.1,Color3B(255,255,255));
					Repeat *rept = Repeat::create(Sequence::create(to,back,nullptr),2);
					rept->setTag(-10);
					this->runAction(rept);
				}
				//schedule(schedule_selector(Fish::updateShine), 0.1f, 5, 0);
				break;
			}

			//打中，没死
			checkFishHurt(false);
			return 0;
		}
	}

	//鱼死了
	checkFishHurt(true);
	
	m_state = Dead;

	if ((m_fishType==FISH_DAYINSHA ||
		m_fishType==FISH_HUANGJINSHA ||
		(m_fishType>=FISH_QSDAYINSHA && m_fishType<FISH_ZHADAN))&&!player->isMachine())
	{		
		auto levelUp = Armature::create("upgrade");
		levelUp->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);
		levelUp->getAnimation()->play("taibang");
		levelUp->getAnimation()->setMovementEventCallFunc(levelUp,movementEvent_selector(UICallBack::playGradeArmature));
		UIM->getPaintLayer()->addChild(levelUp,GUILOCALZORDER);
		pRunData->catchFishType = m_fishType;
		pRoom->KillFishToShake();
	}

	int ttag = this->getTag()+FISHTAGPOOR;
	Fish* fish = (Fish*)pRoom->getChildByTag(this->getTag()+FISHTAGPOOR);
	if(fish)
	{
		fish->doshadowFishDeadAnimation();
	}
	originScore = killFish(pBullet);
	if(m_fishType < FISH_ZHADAN)
	{
		if ((originScore+extraScore)>0)
		{
			if(!player->isMachine())
			{
				generateNum(originScore+extraScore);
			}

			if (GMI->isSingleMode())
			{
				generateCoin(originScore);
			}
			else
			{
				int playerIds[4] = {duorenbuyuchang_control45,duorenbuyuchang_control11,
					duorenbuyuchang_control54,duorenbuyuchang_control63};
				int aiIds[4] = {duorenbuyuchang_control13,duorenbuyuchang_control37,duorenbuyuchang_control14,
					duorenbuyuchang_control15};

				int seatId = player->getSeat();
				MControl *ctrl;
				bool _flag =false;
				if(player->isMachine())
				{
					_flag = true;
					ctrl = UIM->getForm(Form_duorenbuyuchang)->getControl(playerIds[seatId]);
				}
				else
				{
					ctrl = UIM->getForm(Form_duorenbuyuchang)->getControl(playerIds[seatId]);
				}
				Size size = ctrl->getSize();
				Vec2 pos = ctrl->convertToWorldSpace(Vec2::ZERO) + Vec2(size.width/2,size.height/2);
				generateCoin(originScore,pos,_flag);
			}
		}
	}
	return originScore+extraScore;
}

int Fish::killFish( Bullet* pBullet )
{
	this->stopAllActions();
	switch (m_fishType)
	{
	case Fish::FISH_ZHADAN:
		_armatrue->getAnimation()->play("tsy_2_03");
		_armatrue->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Fish::armtureCallBack));
		break;
	case Fish::FISH_PAODAN:
		_armatrue->getAnimation()->play("tsy_1_03");
		_armatrue->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Fish::armtureCallBack));
		break;
	case Fish::FISH_ThreeYuan:
		_armatrue->getAnimation()->play("tsy_5_03");
		_armatrue->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Fish::armtureCallBack));
		break;
	case Fish::FISH_FourXi:
		_armatrue->getAnimation()->play("tsy_4_03");
		_armatrue->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Fish::armtureCallBack));
		break;
	case Fish::FISH_SimilarBomb:
		break;
	case Fish::FISH_ScreenBomb:
		_armatrue->getAnimation()->play("tsy_3_03");
		_armatrue->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Fish::armtureCallBack));
		break;
	case Fish::FISH_JiangQuan1:
	case Fish::FISH_JiangQuan2:
	case Fish::FISH_JiangQuan3:
	case Fish::FISH_JiangQuan4:
	case Fish::FISH_JiangQuan5:
	case Fish::FISH_JiangQuan6:
	case Fish::FISH_JiangQuan7:
		{
			ScaleTo *scaleTo = ScaleTo::create(1.0f,0.1f);
			CallFunc* callfunc = CallFunc::create(this,callfunc_selector(Fish::fishDeadCBK));
			this->runAction(Sequence::createWithTwoActions(scaleTo,callfunc));
		}
		break;
	default:
		{
			Animate *animate = Animate::create(m_deadFrameAnimation);
			CallFunc* callfunc = CallFunc::create(this,callfunc_selector(Fish::fishDeadCBK));
			this->runAction(Sequence::createWithTwoActions(animate,callfunc));
		}
		break;
	}
	if (pBullet->bulletType==LaserCannon)
	{
		return pBullet->getCannon()->laserCosume*f_dynameter;
	}
	return pBullet->bullet_score*f_dynameter;
}

void Fish::setSpec(SpecialAttr spec)
{
    const char* pstr = NULL;
    switch(spec)
	{
        case SPEC_DASIXI:
            pstr = "dasixi.png";
            break;
        case SPEC_HLYQ:
            pstr = "hlyq.png";
            break;
        case SPEC_TLYQ:
            pstr = "tlyq.png";
            break;
        case SPEC_HYLL:
            pstr = "hyll.png";
            break;
        case SPEC_ZDYQ:
            pstr = "zdyq.png";
            break;
        case SPEC_YWYQ:
            pstr = "bjyq.png";
        default:
            break;
    }
    
    if(pstr)
	{
        m_spec = spec;
        if(m_specSprite)
		{
            m_specSprite->release();
            m_specSprite = NULL;
        }

        SpriteFrame *frame = SpriteFrameCache::getInstance()->spriteFrameByName(pstr);
        m_specSprite = Sprite::createWithSpriteFrame(frame);
        m_specSprite->retain();
        addChild(m_specSprite,-1);
        Size a = getContentSize();
        Size b = m_specSprite->getContentSize();
//        m_specSprite->setAnchorPoint(CCPointZero);
        m_specSprite->setPosition(Vec2(a.width/2,a.height/2));
        m_specSprite->runAction(RepeatForever::create(RotateBy::create(1.0f, 150)));
    }
}

bool Fish::isFishLocked(FishType type)
{
    return _fishLockArray[type];
}

void Fish::draw(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
	Sprite::draw(renderer,parentTransform,parentFlags);

	/*_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(Fish::onDraw, this, parentTransform, parentFlags);
	renderer->addCommand(&_customCommand);*/
}

void Fish::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	Size size = this->getContentSize();
	DrawPrimitives::setPointSize(10);
	DrawPrimitives::setDrawColor4B(0,0,255,255);
	DrawPrimitives::drawRect(Vec2(0,0),Vec2(size.width,size.height));

	//end draw
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

Fish* Fish::createFishshadow( FishType type )
{
	Fish * n = new Fish(type);
	n->init();
	n->generateFrameAnimation();
	n->setColor(Color3B(0,0,0));
	n->setOpacity(55);
	n->doshadowFishLifeAnimation();
	return n;
}

void Fish::doshadowFishLifeAnimation()
{
	Animate*animate = Animate::create(m_activeFrameAnimation);
	this->runAction(RepeatForever::create(animate));
}

void Fish::doshadowFishDeadAnimation()
{
	this->stopAllActions();

	Animate* animate = Animate::create(m_deadFrameAnimation);
	CallFunc* callfunc = CallFunc::create(this,callfunc_selector(Fish::removeFishShadow));
	this->runAction(Sequence::createWithTwoActions(animate,callfunc));
}


void Fish::removeFishShadow()
{
	this->cleanReference();
	pRoom->removeFishShadow(this);
	this->removeFromParentAndCleanup(true);
	this->release();

}

void Fish::checkFishHurt(bool bDie)
{
	if (bDie)
	{
		//播放音效

	}
	else
	{
		hurtCount++;
		if (hurtCount > 10)
		{
			hurtCount = 0;
			//播放特殊音效

		}
		
	}
	
}


