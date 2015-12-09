#include "OnLineLayer.h"
#include "GameManager.h"
#include "UI.h"
#include "Player.h"
#include "Cannon.h"
#include "Fish.h"
OnLineLayer::OnLineLayer()
{
	memset(seats,0,sizeof(seats));
	
}
OnLineLayer::~OnLineLayer()
{

}
OnLineLayer* OnLineLayer::create(int index)
{
	OnLineLayer *pret = new OnLineLayer();
	if(pret && pret->initWithRoomIndex(index))
	{
		pret->autorelease();
		return pret;
	}
	else
	{
		delete pret;
		return nullptr;
	}
}
bool OnLineLayer::initWithRoomIndex(int index)
{
	if(!Room::initWithRoomIndex(index)) return false;

	GMI->setRoom(this);
	SELF->initCannon();
	addPlayer(SELF);
	SELF->setSeat(getRandom(3));//
	UIM->showForm(Form_duorenbuyuchang);
	sitdown(SELF);
	
	
	addPlayerTime = 5.0f;
	this->schedule(schedule_selector(Room::updateFish),0.5f);
	this->scheduleUpdate();
	return true;
}

void OnLineLayer::update(float dt)
{
	bool flag = false;
	for (auto player : playerList)
	{
		player->upate(dt);
		if(player == SELF)
		{
			continue;
		}
		
		player->addLifeTime(-dt);
		if(player->getLifeTime() <=0)
		{
			if(getRandom(100) < 35 && !flag)
			{
				standUp(player);
				removePlayer(player);
				flag = true;
			}
			else
			{
				player->setLifeTime(getRandom(5.0) + 25.0f);
			}
		}
	}
	checkFish();
	//定时添加玩家
	randomPlayer(dt);

	updateYuchaoTime(dt);
	this->checkBullets();
	this->updateFishShadow(dt);

	int size = playerList.size();
	for (int i = size - 1; i >= 0 ;i--)
	{
		Player *player = playerList.at(i);
		if(player->bNeedRemove)
		{
			playerList.eraseObject(player);
		}
	}
}

void OnLineLayer::checkFish()
{
	Vector<Fish *> tempList;
	for (auto fish : m_pFishes)
	{
		if(fish->m_state == Dead)
		{
			continue;
		}
		FishInf *inf = GData->getFishInf(fish->getFishType());
		if(inf->rate >= 20 && !fish->outOfView())
		{
			tempList.pushBack(fish);
		}
	}
	int size = tempList.size();
	if(size <= 0)
	{
		return;
	}
	for (auto player : playerList)
	{
		if(!player->isMachine())
		{
			continue;
		}
		if(!player->getAiFish())
		{
			player->setAiFish(tempList.at(getRandom(size -1)));
		}
	}

}

void OnLineLayer::randomPlayer(float dt)
{
	addPlayerTime-= dt;
	if(addPlayerTime > 0.0f)
	{
		return;
	}
	float time[3] = {60,2*60.0f,5*60.0f};
	addPlayerTime = time[getRandom(2)];

	std::vector<int> list;
	for (int i =0; i < 4; i++)
	{
		if(seats[i] == 0)
		{
			list.push_back(i);
		}
	}
	if(list.size() == 0)
	{
		return;
	}
	int index = getRandom(list.size());
	Player *player = new Player();
	player->setGameCheck(getRandom(10) + 1);
	player->setMoney(1000);
	player->iconId = getRandom(6) + 1;
	player->setGold(1000000);
	player->changeCannon();
	player->cannonChangeCount = getRandom(2);
	player->cannonChangeTime = 5.0f;
	player->initCannon();
	player->getCannon()->setAutoFire(true);
	player->setSeat(list[index]);
	player->setLifeTime(getRandom(60) + 1*60.0f);
	addPlayer(player);
	sitdown(player);
}

void OnLineLayer::sitdown(Player *player)
{
	seats[player->getSeat()] = 1;
	UIForm *form = UIM->getForm(Form_duorenbuyuchang);
	int aiIds[4] = {duorenbuyuchang_control3,duorenbuyuchang_control36,
		duorenbuyuchang_control5,duorenbuyuchang_control4};
	int playerIds[4] = {duorenbuyuchang_control41,duorenbuyuchang_control2,
		duorenbuyuchang_control49,duorenbuyuchang_control57};
	int sIndex = player->getSeat();
	MControl *ctrl =nullptr;
	if(player == SELF)
	{
		ctrl = form->getControl(playerIds[sIndex]);
	}
	else
	{
		ctrl = form->getControl(aiIds[sIndex]);
	}
	ctrl->setUserData(player);
	ctrl->refresh();
	ctrl->setVisible(true);
}

void OnLineLayer::standUp(Player *player)
{
	seats[player->getSeat()] = 0;
	UIForm *form = UIM->getForm(Form_duorenbuyuchang);
	int aiIds[4] = {duorenbuyuchang_control3,duorenbuyuchang_control36,
		duorenbuyuchang_control5,duorenbuyuchang_control4};

	int aiIds1[4] = {duorenbuyuchang_control19,duorenbuyuchang_control39,
		duorenbuyuchang_control21,duorenbuyuchang_control20};
	int sIndex = player->getSeat();
	MControl *ctrl = form->getControl(aiIds[sIndex]);
	form->getControl(aiIds1[sIndex])->getPaintNode()->removeAllChildren();
	ctrl->setUserData(nullptr);
	ctrl->refresh();
	ctrl->setVisible(false);
}

void OnLineLayer::exitLayer()
{
	Room::exitLayer();
}