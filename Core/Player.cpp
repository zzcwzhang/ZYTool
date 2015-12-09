#include "Player.h"
#include "Cannon.h"
#include "GameDataManager.h"
#include "GameManager.h"
#include "Tools.h"
#include "Fish.h"
#include "UI.h"
int BackUPKEY = 31;
Player::Player()
{
	userName = "";
	psw = "";
	nickName ="";
	m_keyCode = 0;
	bModifyMemory = false;
	curRateInfIndex = 0;
	curCannonIndex = 0;
	seatIndex = 0;
	lifeTime = 0.0f;
	clickTime = 0.0f;
	cannonRateTime = 0.0f;
	bMachine = true;
	bNeedRemove = false;
	bFirstCharge = false;
	aiFish = nullptr;
	aiFishTime = 0.0f;
	iconId = 1;
	sex = 0;
	memset(gameVariables,0,sizeof(int) * VarCount);
	for (int i = 0; i < VarCount; i++)
	{
		gameVariablesBackUp[i] = BackUPKEY;
	}

	setPlayGrade(1);
	setPlayRank(0);
	setGameCheck(1);
	setGold(1000);
	setVariable(FixedItem,1);
	pCannon = nullptr;
	autorelease();
}
Player::~Player()
{
	pCannon->release();
}

void Player::initCannon()
{
	if(!pCannon)
	{
		pCannon = Cannon::createWithtype((CannonType)curCannonIndex);
		pCannon->retain();
		pCannon->setPlayer(this);
	}
	else
	{
		pCannon->initWithCannonType((CannonType)curCannonIndex);
	}
	
	CannonRateInf *ratInf = GData->getCannonRateInf(curRateInfIndex);
	CannonInf *inf = GData->getCannonInf(curCannonIndex);
	pCannon->setCannonRateInf(ratInf);
	pCannon->setCannonInf(inf);
	pCannon->setLevelEffect();
	pCannon->cannonFireEffect();
}

Cannon* Player::getCannon()
{
	return pCannon;
}

void Player::setCannonRate(int rateIndex)
{
	curRateInfIndex = rateIndex;
	CannonRateInf *ratInf = GData->getCannonRateInf(rateIndex);
	pCannon->setCannonRateInf(ratInf);
}

void Player::setCannonInf(int index)
{
	curCannonIndex = index;
	CannonInf *inf = GData->getCannonInf(index);
	pCannon->setCannonInf(inf);
}

void Player::setAiFish(Fish *fish)
{
	this->aiFish = fish;
}
Fish* Player::getAiFish()
{
	return aiFish;
}

void Player::setSex(int sex)
{
	this->sex = sex;
}
int Player::getSex()
{
	return this->sex;
}

bool Player::checkFirstCharge()
{
	return bFirstCharge;
}
void Player::setFirstCharge(bool flag)
{
	bFirstCharge = flag;
}

void Player::encryption()
{
	int preKeyValue = this->m_keyCode;
	for (int i = 0; i <VarCount;i++)
	{
		gameVariables[i] = gameVariables[i] - preKeyValue + m_keyCode;
		if(gameVariablesBackUp[i] - BackUPKEY != gameVariables[i] - m_keyCode)
		{
			bModifyMemory = true;
			break;
		}
	}
}

void Player::setVariable(int index,int num)
{
	if(index >= VarCount || index < 0)
	{
		return;
	}
	gameVariables[index] = num + m_keyCode;
	gameVariablesBackUp[index] = num + BackUPKEY;
}
int Player::getVariable(int index)
{
	return gameVariables[index] - m_keyCode;
}
void Player::addVariable(int index,int num)
{
	gameVariables[index] += num;
	gameVariablesBackUp[index] += num;
}

void Player::setMoney(int money)
{
	setVariable(Money,money);
}
void Player::setGold(int gold)
{
	setVariable(Diamond,gold);
}
int Player::getMoney()
{
	return getVariable(Money);
}
int Player::getGold()
{
	return getVariable(Diamond);
}

void Player::addMoney(int money)
{
	addVariable(Money,money);
}
void Player::addGold(int gold)
{
	addVariable(Diamond,gold);
}
void Player::setLottery(int num)
{
	setVariable(Lottery,num);
}
void Player::addLottery(int num)
{
	addVariable(Lottery,num);
}
int  Player::getLottery()
{
	return getVariable(Lottery);
}
void  Player::setScore(int sco)
{
	setVariable(Score,sco);
}
void  Player::addScore(int sco)
{
	addVariable(Score,sco);
	int score = getScore();
	int level = getPlayGrade();
	GradeInf* inf = GData->getGradeInf(level - 1);
	while(inf->upScore < score)
	{
		score = score - inf->upScore;
		level++;
		inf = GData->getGradeInf(level - 1);
		//播放升级音效
		SMI->playSound("shenji.mp3",false);
	}
	int rankLv = 0;
	if(level >= 5 && level <10 )
	{
		rankLv = 1;
	}
	else if(level >= 10 && level <15 )
	{
		rankLv = 2;
	}
	else if(level >= 15 && level <20 )
	{
		rankLv = 3;
	}
	else if(level >= 20 && level <30 )
	{
		rankLv = 4;
	}
	else if(level >= 30 && level <35 )
	{
		rankLv = 5;
	}
	else if(level >= 35 && level <40 )
	{
		rankLv = 6;
	}
	else if(level >= 40 && level <45 )
	{
		rankLv = 7;
	}
	else if(level >= 45 && level <50 )
	{
		rankLv = 8;
	}
	else if(level >= 50)
	{
		rankLv = 9;
	}
	setScore(score);
	setPlayGrade(level);
	setPlayRank(rankLv);
}
int   Player::getScore()
{
	return getVariable(Score);
}
void  Player::setGameCheck(int check)
{
	setVariable(GameCheck,check);
}
void  Player::addGameCheck(int check)
{
	addVariable(GameCheck,check);
}
int   Player::getGameCheck()
{
	return getVariable(GameCheck);
}

void  Player::setPlayGrade(int grade)
{
	setVariable(PlayerGrade,grade);
}
void  Player::addPlayGrade(int grade)
{
	addVariable(PlayerGrade,grade);
}
int   Player::getPlayGrade()
{
	return getVariable(PlayerGrade);
}

void Player::setPlayRank(int rank)
{
	setVariable(PlayerRank,rank);
}
void Player::addPlayRank(int rank)
{
	addVariable(PlayerRank,rank);
}
int  Player::getPlayRank()
{
	return getVariable(PlayerRank);
}

void Player::setLvl(int num)
{
	setVariable(LvL,num);
}
void Player::addLvl(int num)
{
	addVariable(LvL,num);
}
int  Player::getLvl()
{
	return getVariable(LvL);
}

void Player::setVIP(int vip)
{
	setVariable(VIP,vip);
}

void Player::addVIP(int vip)
{
	addVariable(VIP,vip);
}

int Player::getVip()
{
	return getVariable(VIP);
}

void Player::setTotalCharge(int num)
{
	setVariable(TotalCharge,num);
}
void Player::addTotalCharge(int num)
{
	addVariable(TotalCharge,num);
}
int Player::getTotalCharge()
{
	return getVariable(TotalCharge);
}

void Player::setSeat(int index)
{
	seatIndex = index;
	if(seatIndex > 1)
	{
		pCannon->setRotation(180);
	}
	else
	{
		pCannon->setRotation(0);
	}
}
int Player::getSeat()
{
	return seatIndex;
}

void Player::setLifeTime(float time)
{
	lifeTime = time;
}

void Player::addLifeTime(float time)
{
	lifeTime += time;
}

float Player::getLifeTime()
{
	return lifeTime;
}

float Player::getExtraRate()
{
	if(bMachine)
	{
		return 0.05f;
	}
	return 0.0f;
}

void Player::changeCannon()
{
	int rate = getRandom(100);
	if (rate <= 8)
	{
		curCannonIndex = 0;
	}
	else if(rate <= 20)
	{
		curCannonIndex = 1;
	}
	else if(rate <= 36)
	{
		curCannonIndex = 2;
	}
	else if(rate <= 54)
	{
		curCannonIndex = 3;
	}
	else if(rate <= 76)
	{
		curCannonIndex = 4;
	}
	else
	{
		curCannonIndex = 5;
	}
}

void Player::upate(float dt)
{
	Size size= Director::getInstance()->getWinSize();
	pCannon->update(dt);
	if(!bMachine)
	{
		return;
	}
	//炮台变化
	if(cannonChangeCount > 0)
	{
		float time[3] = {5*60.0f,8*60.0f,10*60.0f};
		cannonChangeTime -= dt;
		if(cannonChangeTime <= 0.0f)
		{
			cannonChangeCount--;
			cannonChangeTime = time[getRandom(2)];
			changeCannon();
			initCannon();
		}
	}
	//炮台射击
	if (aiFish)
	{
		pCannon->setClick(aiFish->getPosition());
	}
	else
	{
		clickTime -= dt;
		if(clickTime <= 0.0f)
		{
			clickTime = getRandom(200)/100.0f + 5.0f;
			Vec2 v2;
			v2.x = getRandom(size.width);
			v2.y = size.height/2;
			pCannon->setClick(v2);
		}
	}

	//aifish变化
	aiFishTime += dt;
	if(aiFishTime >= 15.0f)
	{
		aiFishTime = 0.0f;
		if(aiFish && (getRandom(100) < 40 || aiFish->m_state == Dead || aiFish->outOfView()))
		{
			aiFish = nullptr;
		}
	}

	//炮台倍率变化
	cannonRateTime -=dt;
	if(cannonRateTime <= 0)
	{
		float time[3] = {2*60.0f,4*60.0f,6*60.0f};
		cannonRateTime = time[getRandom(2)];
		if (aiFish)
		{
			switch (pRunData->curRoomIndex)
			{
			case 1:
				curRateInfIndex = 10+getRandom(3);
				break;
			case 2:
				curRateInfIndex =  18 + getRandom(3);
				break;
			case 3:
				curRateInfIndex = 23;
				break;
			case 4:
				curRateInfIndex = 9 + getRandom(14);
				break;
			default:
				break;
			}
		}
		else
		{
			switch (pRunData->curRoomIndex)
			{
			case 1:
				curRateInfIndex = 5+getRandom(3);
				break;
			case 2:
				curRateInfIndex =  14 + getRandom(3);
				break;
			case 3:
				curRateInfIndex = 23;
				break;
			case 4:
				curRateInfIndex = 9 + getRandom(14);
				break;
			default:
				break;
			}
		}
		CannonRateInf *ratInf = GData->getCannonRateInf(curRateInfIndex);
		pCannon->setCannonRateInf(ratInf);

		UIForm *form = UIM->getForm(Form_duorenbuyuchang);
		form->getControl(duorenbuyuchang_control23)->refresh();
		form->getControl(duorenbuyuchang_control38)->refresh();
		form->getControl(duorenbuyuchang_control25)->refresh();
		form->getControl(duorenbuyuchang_control24)->refresh();
	}
	
}