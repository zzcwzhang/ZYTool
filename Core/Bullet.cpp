#include "Bullet.h"
#include "GameLayer.h"
#include "GameInit.h"
#include "UICallBack.h"
#include "GUILayer.h"
#include "GameManager.h"
#include "Cannon.h"
#include "Player.h"
USING_NS_CC;

Bullet::Bullet()
{
	pCannon = nullptr;
	bInvalid = false;
	bCanAttack = true;
	atkTime = 1;
}
Bullet::~Bullet()
{
	pCannon = nullptr;
}


Bullet* Bullet::createWithBulletType( CannonType cannontype,int pScore,float hScore,Vec2 sPos,float f_rotation )
{
	Bullet* bt = new Bullet();
	if (bt)
	{
		bt->initWithBulletType(cannontype,pScore,hScore,sPos,f_rotation);
		bt->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(bt);
		return NULL;
	}
	return bt;
}

bool Bullet::initWithBulletType( CannonType cannontype,int pScore,float hScore,Vec2 sPos,float f_rotation )
{
	m_speed = 900.0f;
	m_status = Bullet_Fly;
	bullet_score = pScore;//###
	hit_score = hScore;
	bulletType = cannontype;
	laserStart = sPos;
	
	char* bulletfilename =NULL;

	switch(cannontype){
	case Cannon1:
		bulletfilename = "pao_fire";
		break;
	case Cannon2:
		bulletfilename = "shuip_fire";
		break;
	case Cannon3:
		bulletfilename = "ldp_fire";
		break;
	case Cannon4:
		bulletfilename = "bdp_fire";
		break;
	case Cannon5:
		bulletfilename = "hxj_fire";
		break;
	case Cannon6:
		bulletfilename = "jiguangp_fire";
		break;
	case MissileCannon:
		bulletfilename = "daoju";
		break;
	case LaserCannon:
		bulletfilename = "daoju";
		break;
	default:
		bulletfilename = "pao_fire";
		break;
	}

	auto armature = Armature::create(bulletfilename);

	if (cannontype==Cannon1)
	{
		if (pScore<300)
		{
			armature->getAnimation()->play("GJ_dynamic_2");
		}
		else if (pScore<3000)
		{
			armature->getAnimation()->play("GJ_dynamic_3");	
		}
		else
		{
			armature->getAnimation()->play("GJ_dynamic_4");
		}
	}
	else if (cannontype==MissileCannon)
	{
		armature->getAnimation()->play("dd_feixing");
	}
	else if (cannontype==LaserCannon)
	{
		armature->setRotation(f_rotation);
		//armature->getAnimation()->play("jg_fashe");
		//armature->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Bullet::fasheLaserCallBack));
	}
	else if(cannontype==Cannon6) 
	{
		armature->setAnchorPoint(Vec2(0.5,0));
		armature->getAnimation()->play("GJ_dynamic_1");
		armature->setRotation(f_rotation);
		armature->getAnimation()->setMovementEventCallFunc(this,SEL_MovementEventCallFunc(&Bullet::laseranimationCallBack));
	}
	else
	{
		armature->getAnimation()->play("GJ_dynamic_2");
	}
	this->addChild(armature);
	this->setContentSize(armature->getContentSize());
	this->setPosition(sPos);
	armature->setTag(99);
	pRoom->addChild(this,BULLETLOCALZORDER);
	return true;
}

void Bullet::shootTo( Vec2 targetDirection )
{
	Vec2 ptFrom = this->getPosition();
	Vec2 ptTo = targetDirection;
	float angle = atan2f(ptTo.y - ptFrom.y, ptTo.x - ptFrom.x);
	float rotation = angle / M_PI * 180.0f;
	this->setRotation(90.0f - rotation);

	ptLastStart = ptFrom;
	
	Size size = Director::getInstance()->getWinSize(); 
	Vec2 targetPt = ptTo ;
	if(ptTo.x < 0)
	{
		targetPt.x = 0;
		targetPt.y = ptTo.y - (ptTo.y-ptFrom.y)*(ptTo.x - 0)/(ptTo.x-ptFrom.x);
	}
	else if(ptTo.x> size.width)
	{
		targetPt.x = size.width;
		targetPt.y = ptTo.y - (ptTo.y-ptFrom.y)*(ptTo.x - size.width)/(ptTo.x-ptFrom.x);
	}
	if(ptTo.y < 0)
	{
		targetPt.y = 0;
		targetPt.x = ptTo.x - (ptTo.x-ptFrom.x)*(ptTo.y - 0)/(ptTo.y-ptFrom.y);
	}
	else if(ptTo.y> size.height)
	{
		targetPt.y = size.height;
		targetPt.x = ptTo.x - (ptTo.x-ptFrom.x)*(ptTo.y - size.height)/(ptTo.y-ptFrom.y);
	}
	float moveSec = getBulletMoveTime(ptFrom, targetPt);
	FiniteTimeAction *moveto = MoveTo::create(moveSec, targetPt);
	FiniteTimeAction *callFunc=nullptr;
	if(bulletType == MissileCannon)
	{
		moveto = MoveTo::create(moveSec, targetDirection);
		callFunc = CallFunc::create(this, callfunc_selector(Bullet::explosion));
	}
	else
	{
		callFunc = CallFunc::create(this, callfunc_selector(Bullet::reflect));
	}
	FiniteTimeAction *sequence = Sequence::create(moveto, callFunc, NULL);
	this->runAction(sequence);

}

float Bullet::getBulletMoveTime( cocos2d::Vec2 startPos, cocos2d::Vec2 endPos )
{
	float dis = sqrtf((startPos.x - endPos.x) * (startPos.x - endPos.x) + (startPos.y - endPos.y) * (startPos.y - endPos.y));
	float sec = dis / m_speed;
	return sec;
}

float Bullet::getExtraRate()
{
	return pCannon->getPlayer()->getExtraRate();
}

void Bullet::draw(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
	Node::draw(renderer,parentTransform,parentFlags);

	/*_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(Bullet::onDraw, this, parentTransform, parentFlags);
	renderer->addCommand(&_customCommand);*/
}

void Bullet::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	Size size = this->getContentSize();
	DrawPrimitives::setPointSize(10);
	DrawPrimitives::setDrawColor4B(0,0,255,255);
	DrawPrimitives::drawRect(Vec2(-size.width/2,-size.height/2),Vec2(size.width/2,size.height/2));

	//end draw
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void Bullet::explosion()
{
	m_status = Bullet_Net;
	this->stopAllActions();
	setCanAttack(true);
	Armature *arm = (Armature*)this->getChildByTag(99);
	arm->getAnimation()->playWithIndex(3);
	arm->getAnimation()->setMovementEventCallFunc(this,SEL_MovementEventCallFunc(&Bullet::setMissionExplor));

	FiniteTimeAction *callFunc = CallFunc::create(this, callfunc_selector(Bullet::removeSelf));
	FiniteTimeAction *sequence = Sequence::create(DelayTime::create(1.5f), callFunc, NULL);
	this->runAction(sequence);
}
void Bullet::setMissionExplor(cocostudio::Armature *pArmature, cocostudio::MovementEventType movementType, const char *movementID)
{
	if (movementType == COMPLETE)
	{
		pArmature->removeFromParent();
		pCannon->setFireType(Cannon::Common);
	}
}

void Bullet::reflect()
{
	//this->removeFromParent();
	//return ;
	Vec2 ptFrom = this->getPosition();
	Size size = Director::getInstance()->getWinSize();

	float k = -(ptFrom.y - ptLastStart.y)/(ptFrom.x-ptLastStart.x);
	float b = ptFrom.y-k*ptFrom.x;
	Vec2 target[4];
	Vec2 realTarget;
	Rect rc;
	rc.setRect(0, 0, size.width, size.height);

	//cross with left
	target[0].x = 0;
	target[0].y = b;

	//cross with right
	target[1].x=size.width;
	target[1].y=size.width*k+b;

	//cross with down
	target[2].y = 0;
	target[2].x = -b/k;

	//cross with up
	target[3].y = size.height;
	target[3].x = (size.height-b)/k;

	for (int i=0; i< 4;i++) {
		if( ((int)target[i].x !=(int)ptFrom.x || (int)target[i].y !=(int)ptFrom.y) && rc.containsPoint(target[i])){
			realTarget = target[i];
			break;
		}
	}

	float angle = atan2f(realTarget.y - ptFrom.y, realTarget.x - ptFrom.x);
	float rotation = angle / M_PI * 180.0f;
	this->setRotation(90.0f - rotation);


	//    CCLog("(%f,%f)(%f,%f)(%f,%f)(%f,%f)",target[0].x,target[0].y,target[1].x,target[1].y,target[2].x,target[2].y,target[3].x,target[3].y);
	//    CCLog("readTarget (%f,%f)",realTarget.x,realTarget.y);

	float moveSec = getBulletMoveTime(ptFrom,realTarget);
	FiniteTimeAction *moveto = MoveTo::create(moveSec, realTarget);
	FiniteTimeAction *callFunc = CallFunc::create(this, callfunc_selector(Bullet::reflect));
	FiniteTimeAction *sequence = Sequence::create(moveto, callFunc, NULL);
	this->runAction(sequence);
	ptLastStart = ptFrom;
}

void Bullet::setCannon(Cannon* cannon)
{
	pCannon = cannon;
}
Cannon* Bullet::getCannon()
{
	return pCannon;
}

bool Bullet::isInvalid()
{
	return bInvalid;
}
void Bullet::setInvalid(bool flag)
{
	bInvalid = flag;
}

bool Bullet::canAttack()
{
	return bCanAttack;
}
void Bullet::setCanAttack(bool flag)
{
	bCanAttack = flag;
}

void Bullet::showNet()
{
	m_status = Bullet_Net;
	this->stopAllActions();
	this->setVisible(false);

	char* nameNet;

	switch(bulletType)
	{
	case Cannon1:
		nameNet = "pao_fire";
		break;
	case Cannon2:
		nameNet = "shuip_fire";
		break;
	case Cannon3:
		nameNet = "ldp_fire";
		break;
	case Cannon4:
		nameNet = "bdp_fire";
		break;
	case Cannon5:
		nameNet = "hxj_fire";
		break;
	case Cannon6:
		return ;
		break;
	default:
		nameNet = "pao_fire";
		break;
	}
	
	auto armature = Armature::create(nameNet);

	armature->setPosition(this->getPosition());

	armature->getAnimation()->play("GJ_dynamic_1");

	armature->getAnimation()->setMovementEventCallFunc(this,SEL_MovementEventCallFunc(&Bullet::animationCallBack));
	pRoom->addChild(armature,PHYSICSLZORDER);

	FiniteTimeAction *callFunc = CallFunc::create(this, callfunc_selector(Bullet::removeSelf));
	FiniteTimeAction *sequence = Sequence::create(DelayTime::create(0.5f), callFunc, NULL);
	this->runAction(sequence);
}

void Bullet::animationCallBack( Armature *armature, MovementEventType movementType, const std::string& movementID )
{
	if(movementType==COMPLETE)
	{
		pRoom->removeChild(armature);
	}
}
void Bullet::laseranimationCallBack( Armature *armature, MovementEventType movementType, const std::string& movementID )
{
	if(movementType==COMPLETE)
	{
		removeSelf();
	}
}

void Bullet::fasheLaserCallBack(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType==COMPLETE)
	{
		if(movementID.compare("jg_fashe") == 0)
		{
			armature->getAnimation()->play("jg_xiaoshi");
			armature->getAnimation()->setMovementEventCallFunc(this,movementEvent_selector(Bullet::fasheLaserCallBack));
		}
		else if (movementID.compare("jg_xiaoshi") == 0)
		{
			pCannon->setFireType(Cannon::Common);
			removeSelf();
			auto rota = RotateTo::create(0.2f,0);
			auto m_by1 = MoveBy::create(0.3f,Vec2(0,220));
			auto m_by2 = MoveBy::create(0.2f,Vec2(0,-40));
			pCannon->runAction(Sequence::create(rota,m_by1,m_by2,nullptr)); 
		}
	}
}

void Bullet::removeSelf()
{
	pRoom->removeBullet(this);
	this->removeFromParent();
}
