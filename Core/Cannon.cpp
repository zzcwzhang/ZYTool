#include "Cannon.h"
#include "Bullet.h"
#include "GameLayer.h"
#include "GameInit.h"
#include "GameDataManager.h"
#include "GameManager.h"
#include "SConfig.h"
#include "Player.h"
#include "Fish.h"
#include "Room.h"
#include "GScene.h"
USING_NS_CC;

Cannon::Cannon()
{
	for (int i=0;i<6;i++)
	{
		ownCannon[i] = none;
	}
	ownCannon[0] = outfited;

	befRotation = 0;
	prevConsume=0;
	fireType = Common;
	
	autoFire = false;
	banClick = false;
	beginClick = false;

	clickX = 630.0f;
	clickY = 100.0f;
	armature = nullptr;
	specialArm = nullptr;

	lockArm = nullptr;
	targeFish = nullptr;

	isHartLaser = false;
	clickOnce = false;
	bLockFish = false;
	bPress = false;
	bPrepareFire = false;
	LockTime = 0.0f;
	fireInterval = 0.0f;
}

Cannon::~Cannon()
{
	this->removeAllChildren();
	fireArma.clear();
	targeFish = nullptr;
}

Cannon* Cannon::createWithtype(CannonType type)
{
	Cannon* pCannon = new Cannon();
	if (pCannon==NULL)
	{
		CC_SAFE_DELETE(pCannon);
		return NULL;
	}

	if(pCannon->initWithCannonType(type))
	{
		pCannon->autorelease();
	}

	return pCannon;
}

bool Cannon::initWithCannonType( CannonType type )
{
	this->removeAllChildren();
	fireArma.clear();
	targeFish = nullptr;
	switch(type)
	{
	case Cannon1:
		cannonName = "pao";
		break;
	case Cannon2:
		cannonName = "shuip";
		break;
	case Cannon3:
		cannonName = "ldp";
		break;
	case Cannon4:
		cannonName = "bdp_dh";
		break;
	case Cannon5:
		cannonName = "hxj";
		break;
	case Cannon6:
		cannonName = "jiguangp";
		break;
	default:
		cannonName = "pao";
		break;
	}

	armature = Armature::create(cannonName);

	this->addChild(armature);
	return true;
}

void Cannon::cannonFireEffect()//添加火焰特效
{
	Armature* fireArma1 = NULL;//Armature::create("paokou");
	Armature* fireArma2 = NULL;

	if (cannonInf->m_id==Cannon1)
	{
		fireArma1 = Armature::create("paokou");
		fireArma1->setVisible(false);
		fireArma.pushBack(fireArma1);
	}
	else 
	{
		fireArma1 = Armature::create("paokou");
		fireArma2 = Armature::create("paokou");

		fireArma1->setVisible(false);
		fireArma2->setVisible(false);

		fireArma.pushBack(fireArma1);
		fireArma.pushBack(fireArma2);

		this->addChild(fireArma1);
		this->addChild(fireArma2);
	}

	float width = armature->getContentSize().width;
	float height = armature->getContentSize().height;
	Vec2 pos = this->getPosition();

	switch(cannonInf->m_id)
	{
	case Cannon1:
		fireArma1->setPosition(Vec2(0,height+10));
		//fireArma1->setPosition(Vec2(/*pos.x+*/width/5,/*pos.y+*/height*15/16));
		//fireArma2->setPosition(Vec2(/*pos.x-*/-width/5,/*pos.y+*/height*15/16));
		break;
	case Cannon2:
		fireArma1->setPosition(Vec2(/*pos.x+*/width*2/5,/*pos.y+*/height*10/11));
		fireArma2->setPosition(Vec2(/*pos.x-*/-width*2/5,/*pos.y+*/height*10/11));
		break;
	case Cannon3:
		fireArma1->setPosition(Vec2(/*pos.x+*/width/6,/*pos.y+*/height*16/15));
		fireArma2->setPosition(Vec2(/*pos.x-*/-width/6,/*pos.y+*/height*16/15));
		break;
	case Cannon4:
		fireArma1->setPosition(Vec2(/*pos.x+*/width/5,/*pos.y+*/height*2/3));
		fireArma2->setPosition(Vec2(/*pos.x-*/-width/5,/*pos.y+*/height*2/3));
		break;
	case Cannon5:
		fireArma1->setPosition(Vec2(/*pos.x+*/width/5,/*pos.y+*/height*2/3));
		fireArma2->setPosition(Vec2(/*pos.x-*/-width/5,/*pos.y+*/height*2/3));
		break;
	case Cannon6:
		fireArma1->setPosition(Vec2(/*pos.x+*/width/5-2,/*pos.y+*/-height/10));
		fireArma2->setPosition(Vec2(/*pos.x-*/-width/5+5,/*pos.y+*/-height/10));
		break;
	}

// 	fireArma1->setVisible(false);
// 	fireArma2->setVisible(false);
// 
// 	fireArma.pushBack(fireArma1);
// 	fireArma.pushBack(fireArma2);
// 
// 	this->addChild(fireArma1);
// 	this->addChild(fireArma2);
}

void Cannon::addLockToFish( Fish* fish )
{
	lockArm = Armature::create("daoju2");

	Size size = fish->getContentSize();
	float x = size.width/2;
	float y = size.height/2;


	lockArm->setPosition(Vec2(x,y));
	lockArm->setScale(0.7f);
	fish->addChild(lockArm);
	lockArm->getAnimation()->playWithIndex(2);
	
	targeFish = fish;
	autoFire = true;
}

void Cannon::setClick(Vec2 v2)
{
	clickX = v2.x;
	clickY = v2.y;
}

void Cannon::onTouchBegan( float fx,float fy )
{
	clickX = fx;
	clickY = fy;
	bPress = true;
	if (banClick) return ;

	autoFire = true;
	//beginClick = true;
	//this->schedule(schedule_selector(Cannon::updateFire),0.1f);
}

void Cannon::onTouchMoved( float fx,float fy )
{
	clickX = fx;
	clickY = fy;
	if (banClick) return ;
}

void Cannon::onTouchEnded( float fx,float fy )
{
	bPress = false;
	if (banClick) return ;
	
	if (bLockFish)
	{
		Vector<Fish*> tfishes = pRoom->getFishes();
		for (Fish* fish : tfishes)
		{
			//9号鱼以下阻止选择;
			if (fish->getFishType()<Fish::FISH_REDAIZIYU)
			{
				continue;
			}

			if (fish->getBoundingBox().containsPoint(Vec2(fx,fy)))
			{
				if (!lockArm)
				{
					addLockToFish(fish);
				}
				else
				{
					lockArm->removeAllChildrenWithCleanup(true);
					addLockToFish(fish);
				}
			}
		}
	}
	else
	{
		autoFire = false;
	}
}

void Cannon::doRageFire()
{
	int angle = 15;
	for (int i = -2; i <= 2; i++)
	{
		for(Vector<Armature*>::const_iterator citer=fireArma.begin();citer!=fireArma.end();citer++)
		{
			Armature* arma = (Armature*)*citer;
			if(cannonInf->m_id!=Cannon6) 
			{
				arma->setVisible(true);
				arma->getAnimation()->play("tx_1");
			}
			float rot =befRotation +  i*angle;
			Vec2 firePos = convertToWorldSpace(arma->getPosition());
			Bullet* pBullet;
			Vec2 temPos = bulletFlyendPos(firePos);
			float rad;
			rad = M_PI * ((i*angle + 360)%360)/180;
			Vec2 endPos = Vec2(temPos.x * cosf(rad)  - sinf(rad) *temPos.y,
				temPos.y * cosf(rad) + sinf(rad) *temPos.x);
			pBullet = Bullet::createWithBulletType((CannonType)cannonInf->m_id,rateInf->consume,cannonInf->power,firePos,rot);
			pBullet->laserEnd = endPos;//激光终点
			pBullet->setCannon(this);
			if(cannonInf->m_id!=Cannon6) 
			{
				pBullet->shootTo(endPos);
			}
			pRoom->addBullet(pBullet);
		}
	}
}

void Cannon::doMissileFire()
{
	if(!specialArm)
	{
		return;
	}
	specialArm->getAnimation()->playWithIndex(1);
	specialArm->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Cannon::fasheMissileCallBack));
}

void Cannon::doLaserFire()
{
	if(!specialArm)
	{
		return;
	}

	Vec2 firePos = convertToWorldSpace(Vec2::ZERO);
	Vec2 endPos = Vec2(m_pDirection.x,m_pDirection.y);
	
	Bullet* pBullet = Bullet::createWithBulletType(LaserCannon,100,10000,firePos,befRotation);
	pBullet->setCannon(this);
	pBullet->removeFromParent();//隐藏子弹
	pRoom->addBullet(pBullet);
	pBullet->laserStart = firePos;
	pBullet->laserEnd = endPos;
	laserCosume = 100;

	isHartLaser = true;
	specialArm->setRotation(befRotation);
	specialArm->getAnimation()->play("jg_fashe");
	specialArm->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Cannon::fasheLaserCallBack));
	laserS = endPos;
	laserE = firePos;
	laserCosume = 100;
	specialArm->setUserData(pBullet);
}
void Cannon::fasheMissileCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	std::string id = movementID;
	if(movementType == LOOP_COMPLETE ||
		movementType == COMPLETE)
	{
		if(id.compare("dd_fashe") == 0)
		{
			armature->removeFromParent();
			specialArm=nullptr;
			//setFireType(Cannon::Common);
			Vec2 firePos = Vec2(640,70);//convertToWorldSpace(arma->getPosition());
			Vec2 endPos = Vec2(clickX,clickY);

			Bullet* pBullet = Bullet::createWithBulletType(MissileCannon,100,10000,firePos,befRotation);
			pBullet->setCannon(this);

			pRoom->addBullet(pBullet);
			Vec2 absP = pBullet->convertToWorldSpace(Vec2(0,0));
			pBullet->removeFromParent();
			pBullet->setPosition(absP);
			GScene->addChild(pBullet,10);
			pBullet->shootTo(endPos);
			pBullet->setCanAttack(false);
			auto rota = RotateTo::create(0.2f,0);
			auto m_by1 = MoveBy::create(0.3f,Vec2(0,220));
			auto m_by2 = MoveBy::create(0.2f,Vec2(0,-40));
			//CallFunc* callfunc = CallFunc::create(this,callfunc_selector(Cannon::setCilckOnceWithMissionAndLaser));
			this->runAction(Sequence::create(rota,DelayTime::create(0.15f),m_by1,m_by2,nullptr)); 
		}
	}
	else if(movementType == START)
	{

	}
	
}

void Cannon::fasheLaserCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType==COMPLETE)
	{
		if(movementID.compare("jg_fashe") == 0)
		{
			armature->getAnimation()->play("jg_xiaoshi");
			armature->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Cannon::fasheLaserCallBack));

		
			isHartLaser = false;
		}
		else if (movementID.compare("jg_xiaoshi") == 0)
		{
			laserS = Vec2::ZERO;
			laserE = Vec2::ZERO;
			laserCosume = 0;

			Bullet *bullet = (Bullet*)armature->getUserData();
			pRoom->removeBullet(bullet);
			setFireType(Cannon::Common);
			armature->removeFromParent();
			specialArm = nullptr;

			auto rota = RotateTo::create(0.2f,0);
			auto m_by1 = MoveBy::create(0.3f,Vec2(0,220));
			auto m_by2 = MoveBy::create(0.2f,Vec2(0,-40));
			CallFunc* callfunc = CallFunc::create(this,callfunc_selector(Cannon::setCilckOnceWithMissionAndLaser));
			this->runAction(Sequence::create(rota,m_by1,m_by2,callfunc,nullptr)); 
		}
	}
}
//void Cannon::clearLaserCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID)
//{
//	if (movementType==COMPLETE)
//	{
//		fireType = Common;
//		armature->removeFromParent();
//		specialArm = nullptr;
//	}
//}
void Cannon::updateFire( float dt )
{
	int curGold = _owner->getGold();
	if(targeFish && !bPress)
	{
		clickX = targeFish->getPositionX();
		clickY = targeFish->getPositionY();
	}
	switch (fireType)
	{
	case Cannon::Common:
		if (curGold>=rateInf->consume)
		{
			_owner->addGold(-rateInf->consume);
			rotationAndFire(Vec2(clickX,clickY));
		}
		break;
	case Cannon::Rage://狂暴
		rotationAndFire(Vec2(clickX,clickY));
		break;
	case Cannon::Missile://导弹
	case Cannon::Laser://激光
		if(clickOnce)
		{
			rotationAndFire(Vec2(clickX,clickY));
			clickOnce = false;
		}
		break;
	default:
		break;
	}
}

void Cannon::dostudioAniamtion()
{
	if (rateInf->consume<300)
	{
		armature->getAnimation()->play("DJ_dynamic");
	}
	else if (rateInf->consume<3000)
	{
		armature->getAnimation()->play("ZJ_dynamic");	
	}
	else
	{
		armature->getAnimation()->play("GJ_dynamic");
	}

	armature->getAnimation()->setMovementEventCallFunc(this,SEL_MovementEventCallFunc(&Cannon::animationCallBack_1));
}

cocos2d::Vec2 Cannon::getCannonHolePos()
{
 	float width = armature->getContentSize().width;
 	float height = armature->getContentSize().height;
 	Vec2 pos = this->getPosition();
	
	Vec2 res;

	res = Vec2(pos.x+width/5,pos.y+height/3);
	return Vec2(res);
}

Vec2 Cannon::bulletFlyendPos( Vec2 bulletStart )
{
	Vec2 bulletEnd;
	Vec2 cannonPos = this->convertToWorldSpace(Vec2::ZERO);
	bulletEnd.y = m_pDirection.y;
	bulletEnd.x=(bulletEnd.y-bulletStart.y)*(m_pDirection.x-cannonPos.x)/(m_pDirection.y-cannonPos.y)+bulletStart.x;

	return bulletEnd;
}

void Cannon::doFire()
{
	for(Vector<Armature*>::const_iterator citer=fireArma.begin();citer!=fireArma.end();citer++)
	{
		Armature* arma = (Armature*)*citer;
		
		if(cannonInf->m_id!=Cannon6) 
		{
			arma->setVisible(true);
			arma->getAnimation()->play("tx_1");

			//炮台声音
			char soundFile[64];
			memset(soundFile,0,sizeof(soundFile));
			sprintf(soundFile,"cannon_fire%d.mp3",cannonInf->m_id);
			SMI->playSound(soundFile,false);
		}
		else
		{
			if (!SMI->isSoundIsPlaying("cannon_fire5.mp3"))
			{
				SMI->playSound("cannon_fire5.mp3",false);
			}
		}

		Vec2 firePos = convertToWorldSpace(arma->getPosition());

		Bullet* pBullet;
		pBullet = Bullet::createWithBulletType((CannonType)cannonInf->m_id,rateInf->consume,cannonInf->power,firePos,befRotation);
		pBullet->laserEnd = bulletFlyendPos(firePos);//激光终点
		pBullet->setCannon(this);
		if(cannonInf->m_id!=Cannon6) 
		{ 
			pBullet->shootTo(bulletFlyendPos(firePos));
		}
		else
		{
			pBullet->atkTime = cannonInf->atkTime;
		}
		pRoom->addBullet(pBullet);
	}

}

void Cannon::rotationAndFire( Vec2 pTo )
{
	if(pTo.y<70) pTo.y = 71.0f;
	//取得炮台的位置，再与ptTo连线构造三角形，便于下一步从炮台出发的角度计算
	Vec2 ptFrom = this->convertToWorldSpace(Vec2(0,0));//Vec2(cannonPosX,cannonPosY);
	//计算预备要转到的角度值 atan2f函数 返回 弧度值
	float angle=atan2f(pTo.y-ptFrom.y,pTo.x-ptFrom.x)/M_PI * 180.0f;
	/*if (angle<10) angle = 10.0f;
	else if(angle>170) angle = 170.0f;*/

	//存储炮台准备转向的角度值（方向）
	float m_fRotation=90 - angle;
	befRotation = m_fRotation;//###
	//float rrr = armature->getRotation();
	//计算从当前炮台的角度转向指定的方向经过的绝对角度值
	float absf_rotation=fabsf(m_fRotation-this->getRotation());
	
	//计算转向需要的时间预设0.2ms转1弧度
	float duration=absf_rotation/360.0f*0.02f;
	//构造旋转动作对象 参考:[C4]
	FiniteTimeAction *callFunc = CallFunc::create(this, callfunc_selector(Cannon::dostudioAniamtion));
	FiniteTimeAction *callFunc1 =nullptr;
	switch (fireType)
	{
	case Cannon::Common:
		callFunc1 = CallFunc::create(this, callfunc_selector(Cannon::doFire));
		break;
	case Cannon::Rage://狂暴
		callFunc1 = CallFunc::create(this, callfunc_selector(Cannon::doRageFire));
		break;
	case Cannon::Missile://导弹
		callFunc1 = CallFunc::create(this, callfunc_selector(Cannon::doMissileFire));
		break;
	case Cannon::Laser://激光
		callFunc1 = CallFunc::create(this, callfunc_selector(Cannon::doLaserFire));
		break;
	default:
		break;
	}
	
	FiniteTimeAction *pAction = RotateTo::create(duration, m_fRotation);
	Action*  fishaction = Sequence::create(pAction,callFunc,callFunc1,NULL);
	if ((fireType == Cannon::Missile || fireType == Cannon::Laser) && specialArm)
	{
		this->runAction(Sequence::create(pAction,callFunc,NULL));
		specialArm->runAction(fishaction);
	}
	else
	{
		this->runAction(fishaction);
	}

	Vec2 cannonPos = this->convertToWorldSpace(Vec2::ZERO);
	if(ptFrom.y > SCREEN_HALF_HEIGHT)
	{
		m_pDirection.y = 0;
	}
	else
	{
		m_pDirection.y = 720;
	}
	m_pDirection.x=(m_pDirection.y-cannonPos.y)*(pTo.x-cannonPos.x)/(pTo.y-cannonPos.y)+cannonPos.x;
	//doFire();
}

void Cannon::update( float dt )
{
	if (fireType!=Common)
	{
		if (fireType==Rage)
		{
			RageTime -=dt;
			if (RageTime<=0)
			{
				fireType = Common;
				pRoom->removeChildByTag(-22);
			}
		}
	}

	//锁定
	if (bLockFish)
	{
		LockTime -= dt;
		if (LockTime<=0)
		{
			bLockFish = false;
			autoFire = false;
			if (lockArm)
			{
				//updateFire( dt );
				lockArm->removeFromParentAndCleanup(true);
				lockArm  = nullptr;
			}	
			targeFish = nullptr;
		}
		else
		{
			if (targeFish && ((targeFish->m_state == Dead)||targeFish->outOfView()))
			{
				lockArm->removeFromParentAndCleanup(true);
				autoFire = false;
				lockArm  = nullptr;
				targeFish = nullptr;
			}
		}
	}
	

	if (autoFire && !bPrepareFire)
	{
		fireInterval += dt;
		if (fireInterval >= cannonInf->atkSpeed)
		{
			updateFire( dt );
			fireInterval = 0.0f;
		}
	}
}

void Cannon::animationCallBack_1( Armature *armature, MovementEventType movementType, const std::string& movementID )
{
	if(movementType==COMPLETE)
	{
		setLevelEffect();
	}
}

void Cannon::setLevelEffect()
{
	if (rateInf->consume<300)
	{
		armature->getAnimation()->play("DJ_static");
	}
	else if (rateInf->consume<3000)
	{
		armature->getAnimation()->play("ZJ_static");
	}
	else
	{
		armature->getAnimation()->play("GJ_static");
	}
}

void Cannon::setPlayer(Player *player)
{
	_owner = player;
}
Player* Cannon::getPlayer()
{
	return _owner;
}





