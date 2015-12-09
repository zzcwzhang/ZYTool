#include "Room.h"
#include "GameDataManager.h"
#include "SConfig.h"
#include "UI.h"
#include "Fish.h"
#include "Bullet.h"
#include "Cannon.h"
#include "FishGroup.h"
#include "FishMatrix.h"
#include "Player.h"
#include "GameManager.h"
#include "GScene.h"
Room::Room()
{
	FishTag = 0;
	yuchaoTime = 0.0f;
	CheckFishSpeedUp = false;/*–ﬁ∏ƒ*/
	clickDeblock = false;/*–ﬁ∏ƒ*/
}
Room::~Room()
{
	m_pFishes.clear();
	m_pBullets.clear();
	m_pFShadow.clear();
	armatureCJScene.clear();
	drawNodeList.clear();
}
Room* Room::create(int index)
{
	Room *rm = new Room();
	if(rm && rm->initWithRoomIndex(index))
	{
		rm->autorelease();
		return rm;
	}
	else
	{
		delete rm;
		return nullptr;
	}
}

bool Room::initWithRoomIndex(int index)
{
	if(!Layer::init())
	{
		return false;
	}
	RoomInf * inf = GData->getRoomInf(index);
	if(!inf)
	{
		return false;
	}
	setInf(inf);
	initFrame();
	registerEventDispatcher();
	//±≥æ∞“Ù¿÷
	char bgm[128];
	memset(bgm,0,sizeof(bgm));
	sprintf(bgm,"bgm%d.mp3",getRandom(4));
	SMI->playSound(bgm,true);
	return true;
}

void Room::exitLayer()
{
	playerList.clear();
	GMI->clearRunData();
}


void Room::initFrame()
{
	std::string str = getGameScenePrefix(HAICAO);
	auto armatureCJ1 = Armature::create(str);
	armatureCJ1->getAnimation()->play("stand");
	JoinClippingNode(armatureCJ1);

	char str2[65];
	sprintf(str2,"%s.jpg",str.c_str());
	auto bgView = Sprite::create(str2);
	bgView->setPosition(0,0);
	armatureCJ1->addChild(bgView);

	auto armatureWater = Armature::create("shuibo");
	armatureWater->setAnchorPoint(Vec2::ZERO);
	armatureWater->setPosition(Vec2::ZERO);
	armatureWater->getAnimation()->play("stand");
	this->addChild(armatureWater,HALOWATERZORDER);
}

void Room::KillFishToShake()
{
	GScene->stopAllActions();
	MoveTo* moby = MoveTo::create(0.1,Vec2(15,12));
	MoveTo* moby2 = MoveTo::create(0.1,Vec2(-15,-14));
	MoveTo* moby3 = MoveTo::create(0.1,Vec2(19,17));
	MoveTo* moby4 = MoveTo::create(0.1,Vec2(-15,-11));
	MoveTo* moby5 = MoveTo::create(0.1,Vec2(18,16));
	MoveTo* moby6 = MoveTo::create(0.1,Vec2(-13,-13));
	MoveTo* moover= MoveTo::create(0.1,Vec2(0,0));
	Sequence* sq = Sequence::create(moby,moby2,moby3,moby4,moby5,moby6,moover,nullptr);
	GScene->runAction(sq);

	/*–ﬁ∏ƒ*/
	Armature *arm = Armature::create("daoju2");
	arm->getAnimation()->playWithIndex(0);
	arm->setTag(451);
	arm->setPosition(Vec2(S_WIDTH/2,S_HEIGHT/2));
	this->addChild(arm,1010);
	arm->runAction(Sequence::createWithTwoActions(DelayTime::create(0.5f),RemoveSelf::create()));
}

void Room::JoinClippingNode(Armature* BGView)
{
	DrawNode *shape = DrawNode::create();
	Vec2 triangle[4];
	triangle[0] = Vec2(-SCREEN_HALF_WIDTH,-SCREEN_HALF_HEIGHT);
	triangle[1] = Vec2(-SCREEN_HALF_WIDTH, SCREEN_HALF_HEIGHT);
	triangle[2] = Vec2(SCREEN_HALF_WIDTH, SCREEN_HALF_HEIGHT);
	triangle[3] = Vec2(SCREEN_HALF_WIDTH,-SCREEN_HALF_HEIGHT);
	shape->drawPolygon(triangle, 4, Color4F(0,1,0,1), 0, Color4F(0,1,0,1));
	drawNodeList.pushBack(shape);

	ClippingNode *clipper = ClippingNode::create();
	clipper->setPosition(Vec2(SCREEN_HALF_WIDTH, SCREEN_HALF_HEIGHT));
	clipper->setStencil(shape);
	if(armatureCJScene.size()>0)
	{
		ClippingNode* arma = (ClippingNode*)armatureCJScene.at(0);
		this->addChild(clipper,arma->getZOrder()-1);
	}
	else
	{
		this->addChild(clipper,BGLOCALZORDER);
	}
	clipper->addChild(BGView);
	armatureCJScene.pushBack(clipper);
}


void Room::speedUpBeforeFishTide()
{
	CheckFishSpeedUp = true;
	Director::getInstance()->getScheduler()->setTimeScale(10.0f);
}

void Room::prepareFishTideComing(float dt)
{
	this->unschedule(schedule_selector(Room::updateFish));

	auto yuchao = Sprite::create("yuchao.png");
	yuchao->setPosition(SCREEN_WIDTH+100,SCREEN_HALF_HEIGHT);
	this->addChild(yuchao,HALOWATERZORDER);

	CallFunc* callfunc = CallFunc::create(this,callfunc_selector(Room::speedUpBeforeFishTide));

	yuchao->runAction(Sequence::create(MoveTo::create(3.0f,Vec2(-710,SCREEN_HALF_HEIGHT)),callfunc,RemoveSelf::create(true),nullptr));

	//this->scheduleOnce(schedule_selector(Room::switchBGView),4.0f);
}

void Room::updateYuchaoTime(float dt)
{
	yuchaoTime += dt;
	if(yuchaoTime >= 600)
	{
		prepareFishTideComing(dt);
		yuchaoTime = 0;
	}

	if (CheckFishSpeedUp)
	{
		if (m_pFishes.size()==0)
		{
			CheckFishSpeedUp = false;
			Director::getInstance()->getScheduler()->setTimeScale(1.0f);
			switchBGView(0);
		}
	}
}

void Room::removeScene()
{
	DrawNode* dn = (DrawNode*)drawNodeList.at(0);
	drawNodeList.eraseObject(dn);
	ClippingNode* arma = (ClippingNode*)armatureCJScene.at(0);
	armatureCJScene.eraseObject(arma);
	arma->removeFromParent();
	this->schedule(schedule_selector(Room::updateFish),0.5f);
}

void Room::FishTideComing(float dt)
{
	FishMatrix *p = FishMatrix::create(this);
	p->goFishMatrix();
	this->addChild(p);
	for (auto pf : p->m_fishes)
	{
		pf->goFish();
		this->addChild(pf,PHYSICSLZORDER,FishTag);
		m_pFishes.pushBack(pf);

		createFishShadow(pf);
		FishTag++;
	}
}
void Room::startFishGenerator(bool start)
{
	this->schedule(schedule_selector(Room::updateFish),1.0f);
	this->scheduleOnce(schedule_selector(Room::prepareFishTideComing), 60.0f);
}

void Room::switchBGView(float dt)
{
	std::string str = getGameScenePrefix(getRandom(SceneCount - 1));
	auto CJ = Armature::create(str);
	CJ->getAnimation()->play("stand");
	JoinClippingNode(CJ);
	char str2[60];
	sprintf(str2,"%s.jpg",str.c_str());
	auto bgView = Sprite::create(str2);
	bgView->setPosition(Vec2::ZERO);
	CJ->addChild(bgView);

	DrawNode* cn = (DrawNode*)drawNodeList.at(0);
	CallFunc* callfunc = CallFunc::create(this,callfunc_selector(Room::removeScene));
	cn->runAction(Sequence::createWithTwoActions(MoveBy::create(2.0,Vec2(-1280,0)),callfunc));

	auto bubbleArma = Armature::create("paopao");
	bubbleArma->setPosition(Vec2(1280,360));
	this->addChild(bubbleArma,BGLOCALZORDER);

	FiniteTimeAction* m_By = MoveBy::create(4.0f,Vec2(-1280-1280,0));
	bubbleArma->runAction(Sequence::createWithTwoActions(m_By,RemoveSelf::create(true)));

	SMI->playSound("yuchao.mp3",false);

	//this->scheduleOnce(schedule_selector(GameLayer::FishTideComing),5.0f);
	//this->schedule(schedule_selector(GameLayer::updateFish),0.5f);
}

std::string Room::getGameScenePrefix(int type)
{
	//presceneType = cursceneType = type;
	switch(type)
	{
	case HAICAO:
		return "haicao";
	case CJ2:
		return "CJ2";
	case CJ4:
		return "CJ4";
	case CJ5:
		return "CJ_5";
	}
}

void Room::createFishShadow( Fish* fish )
{
	if(fish->getFishType() >= Fish::FISH_ZHADAN)
	{
		return;
	}
	Vec2 shadowPos;
	int ptag = fish->getTag();
	Fish* shadow = Fish::createFishshadow(fish->m_fishType);
	shadow->setPosition(fish->getPosition());
	if(fish->getScaleX() < 0) shadow->setFlipX(true);
	//shadow->setFlipX(fish->getScaleX());
	shadow->setScale(0.7f);
	this->addChild(shadow,FISHSHADOWZORDER,ptag+FISHTAGPOOR);

	m_pFShadow.pushBack(shadow);
}

void Room::checkFishShadow( Fish* fish )
{
	Vec2 f_shadowOffset;
	Object* f_shadowObj = NULL;
	int fishTag = fish->getTag();

	switch(fish->m_fishType){
	case Fish::FISH_XIAOGUANGYU:
		f_shadowOffset = Vec2(-25,-25);
		break;
	case Fish::FISH_XIAOCAOYU:
		f_shadowOffset = Vec2(-25,-25);
		break;
	case Fish::FISH_REDAIYU:
		f_shadowOffset = Vec2(-25,-25);
		break;
	case Fish::FISH_DAYANJINYU:
		f_shadowOffset = Vec2(-25,-25);
		break;
	case Fish::FISH_SHANWEIYU:
		f_shadowOffset = Vec2(-30,-30);
		break;
	case Fish::FISH_XIAOCHOUYU:
		f_shadowOffset = Vec2(-40,-40);
		break;
	case Fish::FISH_HETUN:
		f_shadowOffset = Vec2(-30,-30);
		break;
	case Fish::FISH_SHITOUYU:
		f_shadowOffset = Vec2(-40,-40);
		break;
	case Fish::FISH_DENGLONGYU:
		f_shadowOffset = Vec2(-40,-40);
		break;
	case Fish::FISH_REDAIZIYU:
		f_shadowOffset = Vec2(-40,-40);
		break;
	case Fish::FISH_WUGUI:
		f_shadowOffset = Vec2(-50,-50);
		break;
	case Fish::FISH_HUDIEYU:
		f_shadowOffset = Vec2(-60,-55);
		break;
	case Fish::FISH_MEIRENQUN:
		f_shadowOffset = Vec2(-50,-45);
		break;
	case Fish::FISH_JIANYU:
		f_shadowOffset = Vec2(-50,-55);
		break;
	case Fish::FISH_MOGUIYU://
		f_shadowOffset = Vec2(-80,-80);
		break;
	case Fish::FISH_DAYINSHA:
		f_shadowOffset = Vec2(-50,-55);
		break;
	case Fish::FISH_HUANGJINSHA:
		f_shadowOffset = Vec2(-50,-55);
		break;
	case Fish::FISH_XIAOFEIYU:
		f_shadowOffset = Vec2(-60,-55);
		break;
	case Fish::FISH_LONGXIA:
		f_shadowOffset = Vec2(-50,-50);
		break;
	case Fish::FISH_HAITUN:
		f_shadowOffset = Vec2(-70,-65);
		break;
	case Fish::FISH_JINHAITUN:
		f_shadowOffset = Vec2(-40,-35);
		break;
	case Fish::FISH_LONG:
		f_shadowOffset = Vec2(-70,-65);
		break;
	case Fish::FISH_LVWUGUI:
		f_shadowOffset = Vec2(-50,-45);
		break;
	case Fish::FISH_ALILAN:
		f_shadowOffset = Vec2(-50,-50);
		break;
	case Fish::FISH_MEIRENYU:
		f_shadowOffset = Vec2(-50,-50);
		break;
	case Fish::FISH_ZIMOGUIYU:
		f_shadowOffset = Vec2(-80,-80);
		break;
	case Fish::FISH_QSDAYINSHA:
		f_shadowOffset = Vec2(-70,-55);
		break;
	case Fish::FISH_QSDAJINSHA:
		f_shadowOffset = Vec2(-70,-55);
		break;
	case Fish::FISH_HUANGXIYI:
		f_shadowOffset = Vec2(-70,-55);
		break;
	case Fish::FISH_JINXIYI:
		f_shadowOffset = Vec2(-70,-55);
		break;
	case Fish::FISH_JINMOGUIYU:
		f_shadowOffset = Vec2(-80,-80);
		break;
	}

	for(auto shadowFish : m_pFShadow)
	{
		if(shadowFish == nullptr) continue;

		if (shadowFish->getTag()==(fishTag+FISHTAGPOOR))
		{
			shadowFish->setRotation(fish->getRotation());
			shadowFish->setPosition(Vec2(fish->getPositionX()+f_shadowOffset.x,fish->getPositionY()+f_shadowOffset.y));
		}
	}
}

void Room::updateFishShadow( float dt )
{
	for(auto fish : m_pFishes)
	{
		if(fish==NULL) continue;
		checkFishShadow(fish);
	}
}

void Room::setInf(RoomInf *inf)
{
	this->_inf = inf;
}

RoomInf* Room::getInf()
{
	return _inf;
}

void Room::addPlayer(Player* player)
{
	playerList.pushBack(player);
}
void Room::removePlayer(Player *player)
{
	for(auto bullet : m_pBullets)
	{
		if(bullet->getCannon() == player->getCannon())
		{
			bullet->setInvalid(true);
		}
	}
	player->bNeedRemove = true;
	//playerList.eraseObject(player);
}

Player* Room::getPlayer(int index)
{
	if(index <0 || index >= playerList.size())
	{
		return nullptr;
	}
	return playerList.at(index);
}

void Room::updateFish(float dt)
{
	if(m_pFishes.size()< MAX_FISH_COUNT)//
	{
		addFish();
	}
}
void Room::addFish()
{
	Vector<Fish*> p = FishGroup::createFishGroup(this, (CCRANDOM_0_1()*1)?FishGroup::FishGroupRand:FishGroup::FishGroupLine);
	for(int x=0; x < p.size();x++)
	{
		Fish *pf = (Fish*)(p.at(x));
		this->addChild(pf,PHYSICSLZORDER,FishTag);
		pf->goFish();
		m_pFishes.pushBack(pf);
		createFishShadow(pf);
		FishTag++;
	}

	int rad = CCRANDOM_0_1()*100;
	if (rad%30==0)
	{
		Fish*pf = Fish::createSpecFish(this);
		this->addChild(pf,PHYSICSLZORDER,FishTag);
		pf->goFish();
		m_pFishes.pushBack(pf);

		createFishShadow(pf);
		FishTag++;
	}
}

void Room::removeFish( Fish *pf )
{
	m_pFishes.eraseObject(pf);
}

void Room::removeBullet(Bullet *bullet)
{
	m_pBullets.eraseObject(bullet);
}
void Room::removeFishShadow(Fish *pf)
{
	m_pFShadow.eraseObject(pf);
}

int  Room::getBulletCount()
{
	return m_pBullets.size();
}

void Room::addBullet(Bullet *bullet)
{
	m_pBullets.pushBack(bullet);
}

Vector<Fish*> Room::getFishes()
{
	return m_pFishes;
}

bool Room::checkFishWithBulletCollision(Fish* pFish,Bullet* pBullet)
{
	Vec2 bPos = pBullet->getPosition();
	Rect bulletRect;
	if (pBullet->bulletType==CannonType::MissileCannon)
	{
		bulletRect.setRect(bPos.x-150,bPos.y-150,300,300);
	}
	else
	{
		bulletRect.setRect(bPos.x-15,bPos.y-35,30,70);
	}
	if(pFish->fishList.size() == 0)
	{
		Rect hittestRect = shrinkRect(pFish->getBoundingBox(), 0.5f, 0.5f);
		if (pBullet->bulletType==Cannon6
			|| pBullet->bulletType==LaserCannon)
		{
			return  checkJGHurt(pBullet->laserStart,pBullet->laserEnd,hittestRect);
		}
		else
		{
			return hittestRect.intersectsRect(bulletRect);
		}	
	}
	else
	{
		for(auto fish : pFish->fishList)
		{
			Rect rect = fish->getBoundingBox();
			Vec2 pp = pFish->convertToWorldSpace(rect.origin);
			rect.origin = pp;
			Rect hittestRect = shrinkRect(rect, 0.5f, 0.5f);
			if (pBullet->bulletType==Cannon6
				|| pBullet->bulletType==LaserCannon)
			{
				if(checkJGHurt(pBullet->laserStart,pBullet->laserEnd,hittestRect))
				{
					return true;
				}
			}
			else
			{
				if(hittestRect.intersectsRect(bulletRect))
				{
					return true;
				}
			}	
		}

		Rect hittestRect = shrinkRect(pFish->getBoundingBox(), 0.5f, 0.5f);
		if (pBullet->bulletType==Cannon6
			|| pBullet->bulletType==LaserCannon)
		{
			return  checkJGHurt(pBullet->laserStart,pBullet->laserEnd,hittestRect);
		}
		else
		{
			return hittestRect.intersectsRect(bulletRect);
		}	
	}
}

void Room::checkBullets()
{
	//∆’Õ®◊”µØ
	for(auto bullet : m_pBullets)
	{
		if(!bullet->canAttack())
		{
			continue;
		}
		
		for(auto pFish :m_pFishes)
		{
			if (!pFish)continue;
			if(GMI->isSingleMode())
			{
				Cannon *pCannon = bullet->getCannon();
				Fish * tgfish = pCannon->targeFish;
				if ( tgfish)
				{
					if (pFish!=tgfish)
					{
						continue;
					}
				}
			}
			if (pFish->m_state == Dead)
			{
				continue;
			}
			if(checkFishWithBulletCollision(pFish,bullet))
			{
				if(!bullet->isInvalid())
				{
					this->catchFish(pFish,bullet);
				}

				bullet->atkTime --;

				if (bullet->bulletType!=Cannon6 &&
					bullet->bulletType!=LaserCannon&&
					bullet->bulletType!=MissileCannon)
				{
					bullet->showNet();
					bullet->setCanAttack(false);
				}
			}
		}
	}
}

void Room::checkDeblock()
{
	auto form = UIM->getForm(Form_buyuchang);
	auto ctrl43 = form->getControl(buyuchang_control43);
	
	if (!ctrl43->isVisible() && !clickDeblock)
	{
		CannonRateInf* caI;
		for (auto CRInf : GData->cannonRateArray)
		{
			if(CRInf) caI = CRInf;
			if (!caI->bOpen)
			{
				break;
			}
		}

		int bulletWorth = caI->openCoin;
		int ownGold = SELF->getGold();

		if (ownGold >= bulletWorth)
		{
			ctrl43->setVisible(true);
			ctrl43->refresh();
		}
	}
}


bool Room::catchFish( Fish *pFish, Bullet *pBullet )
{
	Player* player = pBullet->getCannon()->getPlayer();
	int gold = pFish->attackFish(pBullet);
	if(gold == 0)
	{
		return false;
	}
	if (gold>=10000)//∏ƒ∂Ø
	{
		auto goodGold = Armature::create("icon_3");
		goodGold->setPosition(850,150);
		goodGold->getAnimation()->play("jinbi");
		goodGold->setScale(0.65f);
		auto pStr = String::createWithFormat("%d",gold);
		pStr->retain();
		goodGold->setUserData(pStr);
		goodGold->getAnimation()->setMovementEventCallFunc(goodGold,movementEvent_selector(UICallBack::SetbigGoldArmaCallBack));
		this->addChild(goodGold,BULLETLOCALZORDER);
	}
	if(pFish->getFishType() >= Fish::FISH_JiangQuan1
		&& pFish->getFishType() <= Fish::FISH_JiangQuan7)
	{
		player->addLottery(gold);
		if(!player->isMachine())
		{
			UIM->getForm(Form_duorenbuyuchang)->getControl(buyuchang_control31)->refresh();
		}
	}
	else
	{
		player->addGold(gold);
	}
	int playerLevel = player->getPlayGrade();
	int playerRank = player->getPlayRank();
	player->addScore(pFish->f_dynameter);
	if(player->getPlayGrade() != playerLevel)
	{
		if(GMI->isSingleMode())
		{
			UIM->getForm(Form_buyuchang)->getControl(buyuchang_control24)->refresh();
		}
		else if(!player->isMachine())
		{
			UIM->getForm(Form_duorenbuyuchang)->getControl(buyuchang_control29)->refresh();
		}
	}
	if(player->getPlayRank() != playerRank)
	{

		if(GMI->isSingleMode())
		{
			UIM->getForm(Form_buyuchang)->getControl(buyuchang_control6)->refresh();
		}
		else if(!player->isMachine())
		{
			UIM->getForm(Form_duorenbuyuchang)->getControl(buyuchang_control29)->refresh();
		}
		if(player == SELF)
		{
			pRunData->bUpLevel = true;
			GradeInf* Inf = GData->getGradeInf(SELF->getPlayGrade());
			player->addGold(Inf->upReward);

			auto levelUp = Armature::create("upgrade");
			levelUp->setPosition(SCREEN_HALF_WIDTH,SCREEN_HALF_HEIGHT);
			levelUp->getAnimation()->play("dengji");
			String *pString = String::create("dengji_2");
			pString->retain();
			levelUp->setUserData(pString);
			levelUp->getAnimation()->setMovementEventCallFunc(levelUp,movementEvent_selector(UICallBack::playGradeArmature));
			UIM->getPaintLayer()->addChild(levelUp,GUILOCALZORDER);
		}
	}

	if(GMI->isSingleMode())
	{
		UIM->getForm(Form_buyuchang)->getControl(buyuchang_control23)->refresh();
	}
	else if(!player->isMachine())
	{
		UIM->getForm(Form_duorenbuyuchang)->getControl(buyuchang_control30)->refresh();
	}
	return true;
}

void Room::registerEventDispatcher()
{
	auto touchEvt                =   EventListenerTouchOneByOne::create();  
	touchEvt->onTouchBegan   =   CC_CALLBACK_2(Room::onTouchBegan,this);  
	touchEvt->onTouchMoved   =   CC_CALLBACK_2(Room::onTouchMoved,this);  
	touchEvt->onTouchEnded    =   CC_CALLBACK_2(Room::onTouchEnded,this);  

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvt,this);
}

bool Room::onTouchBegan( Touch* touch,Event* evt )
{
	//if(banckick) return false;
	Vec2 p_touch = touch->getLocation();
	SELF->getCannon()->onTouchBegan(p_touch.x,p_touch.y);

	return true;
}

void Room::onTouchMoved( Touch* touch,Event* evt )
{
	//if(banckick) return ;
	Vec2 p_touch = touch->getLocation();
	SELF->getCannon()->onTouchMoved(p_touch.x,p_touch.y);
}

void Room::onTouchEnded( Touch* touch,Event* evt )
{
	//if(banckick) return ;
	Vec2 p_touch = touch->getLocation();
	SELF->getCannon()->onTouchEnded(p_touch.x,p_touch.y);
}

Rect shrinkRect(Rect rc, float xr, float yr)
{
	float w = rc.size.width * xr;
	float h = rc.size.height * yr;
	Vec2 pt = Vec2(rc.origin.x + rc.size.width * (1.0f - xr) / 2,
		rc.origin.y + rc.size.height * (1.0f - yr) / 2);
	return Rect(pt.x, pt.y, w, h);
}



bool isLineThroghRect( Vec2 beginPot,Vec2 endPot,Rect aimRect )//º§π‚”Î”„≈ˆ◊≤ºÏ≤‚
{
	Vec2 vertex[4] ; 
	float x = aimRect.getMinX();
	float X = aimRect.getMaxX();
	float y = aimRect.getMinY();
	float Y = aimRect.getMaxY();
	vertex[0] = Vec2(x,y);
	vertex[1] = Vec2(x,Y);
	vertex[2] = Vec2(X,Y);
	vertex[3] = Vec2(X,y);

	for (int i = 0 ;i<3;i++)
	{
		if (ccpSegmentIntersect(endPot,beginPot,vertex[i],vertex[i+1]))
		{
			return true;
		}
	}
	if (ccpSegmentIntersect(endPot,beginPot,vertex[3],vertex[0]))
	{
		return true;
	}

	return false;
}
bool checkTwoPXLine( Vec2 A,Vec2 B,Rect mRect, float len)
{
	float mk = (B.y - A.y)/(B.x - A.x);
	float hudu = atan2f((B.y - A.y) , (B.x - A.x));
	float offx = len*sinf(hudu);
	float offy = len*cosf(hudu);
	Vec2 up_A = Vec2(A.x-offx,A.y+offx);
	Vec2 up_B = Vec2(B.x-offx,B.y+offx);
	Vec2 down_A = Vec2(A.x+offx,A.y-offx);
	Vec2 down_B = Vec2(B.x+offx,B.y-offx);
	//up
	if(isLineThroghRect(up_A,up_B,mRect)){
		return true;
	}
	//down
	if(isLineThroghRect(down_A,down_B,mRect)){
		return true;
	}
	return false;
}

bool checkJGHurt( Vec2 A,Vec2 B,Rect mRect )
{
	//center check
	if(isLineThroghRect(A,B,mRect)){
		return true;
	}
	//mult line check
	if(checkTwoPXLine(A,B,mRect,100)){
		return true;
	}
	return false;
}