#include "FishPath.h"
#include "SConfig.h"

Vec2 getMDCurvePoint(Vec2 start, Vec2 end, int distance,bool plus)
{
	float angle = atan2f(start.y - end.y, start.x - end.x);

	if(plus)
		angle += M_PI/2;
	else
		angle -= M_PI/2;

	int x = distance*cosf(angle);
	int y = distance*sinf(angle);

	return (start+end)/2 + Vec2(x,y);
}


Vec2 getMDCurvePointRate(Vec2 start, Vec2 end, float rate,bool plus)
{
	float angle = atan2f(start.y - end.y, start.x - end.x);

	if(plus)
		angle += M_PI/2;
	else
		angle -= M_PI/2;

	int distance = rate * sqrt((start.x-end.x)*(start.x-end.x) + (start.y-end.y)*(start.y-end.y))/2;

	int x = distance*cosf(angle);
	int y = distance*sinf(angle);

	return (start+end)/2 + Vec2(x,y);
}

Vec2 genRandMDPoint(cocos2d::Vec2 & start, cocos2d::Vec2 &end)
{
	int nNum = CCRANDOM_0_1()*3;
	switch (nNum){
	case 0:
		return (end-start)/3+start;
	case 2:
		return (end-start)/3*2+start;
	case 1:
	default:
		return (end-start)/2+start;
	}
}

Vec2 getReflectPoint(Vec2 start, Vec2 origin,float rate = 1)
{
	return origin+(origin-start)*rate;
}

FishBezierTo* generateBezierPath(Vec2 start, Vec2 c1, Vec2 c2, Vec2 end,float t)
{
	ccBezierConfig bezier;
	bezier.controlPoint_1 = c1;
	bezier.controlPoint_2 = c2;
	bezier.endPosition = end;

	FishBezierTo * p = FishBezierTo::create(t,bezier);

	return p;
}

void FishBezierTo::update( float time )
{
	Vec2 last = ((Fish*)this->getTarget())->m_lastPoint;
	Vec2 current = this->getTarget()->getPosition();

	double angle = atan2((current.y-last.y),(current.x-last.x));
	this->getTarget()->setRotation(90 - (angle * 360)/(2*3.1415926));

	((Fish*)this->getTarget())->m_lastPoint = current;
	return BezierTo::update(time);
}

FishBezierTo* FishBezierTo::create( float t, const ccBezierConfig& c )
{
	FishBezierTo * n = new FishBezierTo();
	n->initWithDuration(t, c);
	n->autorelease();

	return n;
}

bool FishBezierTo::initWithDuration( float t, const ccBezierConfig &c )
{
	return BezierTo::initWithDuration(t, c);
}

//CCObject* FishBezierTo::copyWithZone( CCZone* pZone )
//{
//	
//}

BezierTo* FishBezierTo::clone()
{
	BezierTo* pNewZone = NULL;
	FishBezierTo* pRet = NULL;

	//pRet = new FishBezierTo();
	//pRet->initWithDuration(_duration, _toConfig);
	//pRet->autorelease();
	return pRet;
}

void FishCardinalSplineTo::update( float time )
{
	Point last = ((Fish*)this->getTarget())->m_lastPoint;
	Point current = this->getTarget()->getPosition();

	double angle = atan2((current.y-last.y),(current.x-last.x));
	this->getTarget()->setRotation(90 - (angle * 360)/(2*3.1415926));

	((Fish*)this->getTarget())->m_lastPoint = current;
	return CardinalSplineTo::update(time);
}

FishCardinalSplineTo* FishCardinalSplineTo::create( float duration, PointArray* points, float tension )
{
	FishCardinalSplineTo * n = new FishCardinalSplineTo();
	n->initWithDuration(duration, points,tension);
	n->autorelease();

	return n;
}

bool FishCardinalSplineTo::initWithDuration( float duration, PointArray* points, float tension )
{
	return CardinalSplineTo::initWithDuration(duration,points,tension);
}

void FishLineTo::update( float time )
{
	CCPoint last = ((Fish*)this->getTarget())->m_lastPoint;
	CCPoint current = this->getTarget()->getPosition();

	double angle = atan2((current.y-last.y),(current.x-last.x));
	this->getTarget()->setRotation(90 - (angle * 360)/(2*3.1415926));
	float rotata = 90 - (angle * 360)/(2*3.1415926);
	((Fish*)this->getTarget())->m_lastPoint = current;
	return MoveTo::update(time);
}

FishLineTo* FishLineTo::create( float duration, const Point& position )
{
	FishLineTo * n = new FishLineTo();
	n->initWithDuration(duration, position);
	n->autorelease();

	return n;
}

bool FishLineTo::initWithDuration( float duration, const Point& position )
{
	return MoveTo::initWithDuration(duration, position);
}

void FishSinTo::update( float time )
{
	CCPoint last = ((Fish*)this->getTarget())->m_lastPoint;
	CCPoint current = this->getTarget()->getPosition();

	double angle = atan2((current.y-last.y),(current.x-last.x));
	this->getTarget()->setRotation(90 - (angle * 360)/(2*3.1415926));
	float rotata = 90 - (angle * 360)/(2*3.1415926);
	((Fish*)this->getTarget())->m_lastPoint = current;
	//return MoveTo::update(time);
	float offsetX = 0,offsetY = 0;

	offsetX = time * (_endPosition.x);

	_angle = time * M_PI * 4;
	offsetY = 150 * sin(_angle);

	_target->setPosition(Vec2(_origin.x + offsetX,_origin.y + offsetY));
}

FishSinTo* FishSinTo::create( float duration, const Point& startPosition,const Point& endPosition)
{
	FishSinTo * n = new FishSinTo();
	n->initWithDuration(duration, startPosition,endPosition);
	n->autorelease();

	return n;
}

bool FishSinTo::initWithDuration( float duration, const Point& startPosition,const Point& endPosition)
{
	if(ActionInterval::initWithDuration(duration))
	{
		_angle = 0;
		_origin = startPosition;
		_endPosition = endPosition - startPosition;
		return true;
	}

	return false;
}

void FishPathFactory::generateBezierFishPath( Fish * target )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size spriteSize = target->getContentSize();

	//For big fish, only one path
	CCPoint c1,c2,start,end;
	float t1 = 15;
	int t2 = 10;
	int blank = 100;
	
	int nNum = -1;
	if (Fish::_isFishLineGroup)//###
	{
		if(nNum == -1)
			nNum = 1;
	}
	else
	{
		nNum = CCRANDOM_0_1()*4;
	}
	//int nNum = CCRANDOM_0_1()*4;
	switch(nNum) {
	case 0:
		start = Vec2(-spriteSize.width,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
		end = Vec2(visibleSize.width+spriteSize.width,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
		c1 = Vec2((end.x - start.x)/4,visibleSize.height);
		c2 = Vec2((end.x - start.x)/4*3,visibleSize.height);
		target->setPosition(start);
		target->m_fishPath.pushBack(generateBezierPath(start, c1, c2, end, target->m_speedTime));
		break;
	case 1:
		//target->setFlipX(true);
		target->setScaleX(-1);
		start = Vec2(-spriteSize.width,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
		end = Vec2(visibleSize.width+spriteSize.width,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
		c1 = Vec2((end.x - start.x)/4,visibleSize.height);
		c2 = Vec2((end.x - start.x)/4*3,visibleSize.height);
		target->setPosition(end);
		target->m_fishPath.pushBack(generateBezierPath(end, c2, c1, start, target->m_speedTime));
		break;
	case 2:
		start = Vec2(-spriteSize.width,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
		end = Vec2(visibleSize.width+spriteSize.width,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
		c1 = Vec2((end.x - start.x)/4,MIN(end.y,start.y));
		c2 = Vec2((end.x - start.x)/4*3,MIN(end.y,start.y));
		target->setPosition(start);
		target->m_fishPath.pushBack(generateBezierPath(start, c1, c2, end, target->m_speedTime));
		break;
	case 3:
		//target->setFlipX(true);
		target->setScaleX(-1);
		start = Vec2(-spriteSize.width,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
		end = Vec2(visibleSize.width+spriteSize.width,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
		c1 = Vec2((end.x - start.x)/4,MIN(end.y,start.y));
		c2 = Vec2((end.x - start.x)/4*3,MIN(end.y,start.y));
		target->setPosition(end);
		target->m_fishPath.pushBack(generateBezierPath(end, c2, c1, start, target->m_speedTime));
		break;
	}
}

void FishPathFactory::generateStaticFishPath( Fish * target )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size s = target->getContentSize();

	target->setPosition(Vec2(CCRANDOM_0_1()*(int)visibleSize.width, CCRANDOM_0_1()*(int)visibleSize.height ));
	target->m_fishPath.pushBack(CCMoveBy::create(60, Vec2(0,0)));
}

void FishPathFactory::generateMultiBezierFishPath( Fish *target,Vec2 start,Vec2 end, int num )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size s = target->getContentSize();

	Vec2 c1,c2;
	Vec2 md,c21,c22;

	int blank = 100;

	if(start.x == 0 && start.y == 0) {
// 		start = Vec2(-s.width,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
// 		end = Vec2(visibleSize.width+s.width,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
		start = Vec2(-s.width,blank + CCRANDOM_0_1()*(visibleSize.height-2*blank));
		end = Vec2(visibleSize.width+s.width,blank + CCRANDOM_0_1()*(visibleSize.height-2*blank));
	}

	if (Fish::_isFishLineGroup)//###
	{
		if(num == -1)
			num = 1;
	}
	else
	{
		num = CCRANDOM_0_1()*4;
	}
	/*if(num == -1)
		num = CCRANDOM_0_1()*4;*/
	switch(num) {
	case 0:
		md = genRandMDPoint(start,end);
		c1 = Vec2((md.x-start.x)/4+start.x,md.y + CCRANDOM_0_1()*100-50);
		c2 = Vec2((md.x - start.x)/4*3+start.x,start.y+ CCRANDOM_0_1()*100-50);
		c21 = Vec2((end.x - md.x)/4+md.x,end.y+ CCRANDOM_0_1()*100-50);
		c22 = Vec2((end.x - md.x)/4*3+md.x,md.y+ CCRANDOM_0_1()*100-50);

		target->m_fishPath.pushBack(generateBezierPath(start, c1, c2, md, target->m_speedTime));
		target->m_fishPath.pushBack(generateBezierPath(md, c21, c22, end, target->m_speedTime));
		target->setPosition(start);
		break;
	case 1:
		target->setScaleX(-1.0f);
		md = genRandMDPoint(start,end);
		c1 = Vec2((md.x-start.x)/4+start.x,md.y + CCRANDOM_0_1()*100-50);
		c2 = Vec2((md.x - start.x)/4*3+start.x,start.y + CCRANDOM_0_1()*100-50);
		c21 = Vec2((end.x - md.x)/4+md.x,end.y + CCRANDOM_0_1()*100-50);
		c22 = Vec2((end.x - md.x)/4*3+md.x,md.y + CCRANDOM_0_1()*100-50);

		target->m_fishPath.pushBack(generateBezierPath(end, c22, c21, md, target->m_speedTime));
		target->m_fishPath.pushBack(generateBezierPath(md, c2, c1, start, target->m_speedTime));
		target->setPosition(end);
		break;
	case 2:
		md = genRandMDPoint(start,end);
		c1 = Vec2((md.x-start.x)/4+start.x,start.y + CCRANDOM_0_1()*100-50);
		c2 = Vec2((md.x - start.x)/4*3+start.x,md.y + CCRANDOM_0_1()*100-50);
		c21 = Vec2((end.x - md.x)/4+md.x,md.y + CCRANDOM_0_1()*100-50);
		c22 = Vec2((end.x - md.x)/4*3+md.x,end.y + CCRANDOM_0_1()*100-50);

		target->m_fishPath.pushBack(generateBezierPath(start, c1, c2, md, target->m_speedTime));
		target->m_fishPath.pushBack(generateBezierPath(md, c21, c22, end, target->m_speedTime));
		target->setPosition(start);
		break;
	case 3:
		target->setScaleX(-1.0f);
		md = genRandMDPoint(start,end);
		c1 = Vec2((md.x-start.x)/4+start.x,start.y + CCRANDOM_0_1()*100-50);
		c2 = Vec2((md.x - start.x)/4*3+start.x,md.y + CCRANDOM_0_1()*100-50);
		c21 = Vec2((end.x - md.x)/4+md.x,md.y + CCRANDOM_0_1()*100-50);
		c22 = Vec2((end.x - md.x)/4*3+md.x,end.y + CCRANDOM_0_1()*100-50);

		target->m_fishPath.pushBack(generateBezierPath(end, c22, c21, md, target->m_speedTime));
		target->m_fishPath.pushBack(generateBezierPath(md, c2, c1, start, target->m_speedTime));
		target->setPosition(end);
		break;
	}
}

void FishPathFactory::generateMultiBezierFishPathWithMD( Fish *target,Vec2 start,Vec2 end, int num ,Vec2 md)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size s = target->getContentSize();

	Vec2 c1,c2;
	Vec2 c21,c22;

	int blank = 100;

	if(start.x == 0 && start.y == 0) {
// 		start = Vec2(-s.width,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
// 		end = Vec2(visibleSize.width+s.width,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
		start = Vec2(-s.width,blank + CCRANDOM_0_1()*(visibleSize.height-2*blank));
		end = Vec2(visibleSize.width+s.width,blank + CCRANDOM_0_1()*(visibleSize.height-2*blank));
	}

	if (Fish::_isFishLineGroup)//###
	{
		if(num == -1)
			num = 1;
	}

	switch(num) {
	case 0:
		c1 = Vec2((md.x-start.x)/4+start.x,md.y);
		c2 = Vec2((md.x - start.x)/4*3+start.x,start.y);
		c21 = Vec2((end.x - md.x)/4+md.x,end.y);
		c22 = Vec2((end.x - md.x)/4*3+md.x,md.y);

		target->m_fishPath.pushBack(generateBezierPath(start, c1, c2, md, target->m_speedTime/2));
		target->m_fishPath.pushBack(generateBezierPath(md, c21, c22, end, target->m_speedTime/2));
		target->setPosition(start);
		break;
	case 1:
		target->setScaleX(-1.0f);
		c1 = Vec2((md.x-start.x)/4+start.x,md.y);
		c2 = Vec2((md.x - start.x)/4*3+start.x,start.y);
		c21 = Vec2((end.x - md.x)/4+md.x,end.y);
		c22 = Vec2((end.x - md.x)/4*3+md.x,md.y);

		target->m_fishPath.pushBack(generateBezierPath(end, c22, c21, md, target->m_speedTime/2));
		target->m_fishPath.pushBack(generateBezierPath(md, c2, c1, start, target->m_speedTime/2));
		target->setPosition(end);
		break;
	case 2:
		c1 = Vec2((md.x-start.x)/4+start.x,start.y);
		c2 = Vec2((md.x - start.x)/4*3+start.x,md.y);
		c21 = Vec2((end.x - md.x)/4+md.x,md.y);
		c22 = Vec2((end.x - md.x)/4*3+md.x,end.y);

		target->m_fishPath.pushBack(generateBezierPath(start, c1, c2, md, target->m_speedTime/2));
		target->m_fishPath.pushBack(generateBezierPath(md, c21, c22, end, target->m_speedTime/2));
		target->setPosition(start);
		break;
	case 3:
		md = genRandMDPoint(start,end);
		c1 = Vec2((md.x-start.x)/4+start.x,start.y);
		c2 = Vec2((md.x - start.x)/4*3+start.x,md.y);
		c21 = Vec2((end.x - md.x)/4+md.x,md.y);
		c22 = Vec2((end.x - md.x)/4*3+md.x,end.y);

		target->m_fishPath.pushBack(generateBezierPath(end, c22, c21, md, target->m_speedTime/2));
		target->m_fishPath.pushBack(generateBezierPath(md, c2, c1, start, target->m_speedTime/2));
		target->setPosition(end);
		break;
	}
}

void FishPathFactory::generateFishPathA( Fish *target,Vec2 start/*=Vec2(0,0)*/,Vec2 end/*=Vec2(0,0)*/,bool direction/*=true*/ )
{
	Size s = target->getContentSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if(start.x == 0 && start.y == 0) {
// 		start = Vec2(-s.width,CCRANDOM_0_1()*((int)visibleSize.height));
// 		end = Vec2(visibleSize.width+s.width,CCRANDOM_0_1()*((int)visibleSize.height));
		int blank = 50;
		int ran = CCRANDOM_0_1()*2;
		int dir = CCRANDOM_0_1()*2;
		int outOffset = MAX(s.width,s.height) * 2;
		if(ran == 0)
		{
			//左右
			if(dir == 0)
			{
				start = Vec2(-outOffset,CCRANDOM_0_1()*(visibleSize.height - 2*blank)+blank);
				end = Vec2(visibleSize.width+outOffset,CCRANDOM_0_1()*(visibleSize.height - 2*blank)+blank);
			}
			else
			{
				end = Vec2(-outOffset,CCRANDOM_0_1()*(visibleSize.height - 2*blank)+blank);
				start = Vec2(visibleSize.width+outOffset,CCRANDOM_0_1()*(visibleSize.height - 2*blank)+blank);
			}
		}
		else
		{
			//上下
			if(dir == 0)
			{
				start = Vec2(CCRANDOM_0_1()*(visibleSize.width - 2*blank)+blank,-outOffset);
				end = Vec2(CCRANDOM_0_1()*(visibleSize.height - 2*blank)+blank,visibleSize.height + outOffset);
			}
			else
			{
				end = Vec2(CCRANDOM_0_1()*(visibleSize.width - 2*blank)+blank,-outOffset);
				start = Vec2(CCRANDOM_0_1()*(visibleSize.height - 2*blank)+blank,visibleSize.height + outOffset);
			}
		}
	}

	PointArray *pp = PointArray::create(30);
	PointArray *np = PointArray::create(30);

	pp->addControlPoint(start);
	pp->addControlPoint(end);

	Vec2 a,b,n;
	for(int i=0; i < pp->count()-1;i++)
	{
		a = pp->getControlPointAtIndex(i);
		b = pp->getControlPointAtIndex(i+1);
		n = getMDCurvePointRate(a, b , 0.3f, false);
		np->addControlPoint(a);
		np->addControlPoint(n);
	}

	np->addControlPoint(b);

	Vec2 fc = getMDCurvePointRate(np->getControlPointAtIndex(0), np->getControlPointAtIndex(1), 0.4f, direction);
	fc = fc + Vec2(CCRANDOM_0_1()*100, CCRANDOM_0_1()*100);
	target->m_fishPath.pushBack(generateBezierPath(np->getControlPointAtIndex(0), fc, fc, np->getControlPointAtIndex(1), target->m_speedTime));

	for(int i = 1; i < np->count() - 1; i++) {
		Vec2 s = np->getControlPointAtIndex(i);
		Vec2 c1 = getReflectPoint(fc, s, 0.7f);
		Vec2 e = np->getControlPointAtIndex(i + 1);

		target->m_fishPath.pushBack(generateBezierPath(s, c1, c1, e, target->m_speedTime));
		fc = c1;
	}
	if (start.x > visibleSize.width)
	{
		target->setScaleX(-1.0f);
	}
	target->setPosition(start);
}

void FishPathFactory::generateFishPathB( Fish *target,int type/*=-1*/,Point start/*=Vec2(0,0)*/,Point end/*=Vec2(0,0)*/ )
{
	return generateMultiBezierFishPath(target,start,end,type);
}

void FishPathFactory::generateFishPathB_line( Fish *target,int type/*=-1*/,Point start/*=Vec2(0,0)*/,Point end/*=Vec2(0,0)*/ ,Point md)
{
	return generateMultiBezierFishPathWithMD(target,start,end,type,md);
}

void FishPathFactory::generateFishPathC( Fish *target )
{
	return generateBezierFishPath(target);
}

void FishPathFactory::generateFishPathD( Fish *target )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	Size spriteSize = target->getContentSize();
	Point start,end;

	int nNum = -1;
	if (Fish::_isFishLineGroup)//###
	{
		if(nNum == -1)
			nNum = 1;
	}
	else
	{
		nNum = CCRANDOM_0_1()*4;
	}
	//int nNum = CCRANDOM_0_1()*4;
	switch(nNum)
	{
	case 0:
		start = Vec2(-spriteSize.width,-spriteSize.height);
		end = Vec2(visibleSize.width+spriteSize.width,visibleSize.height+spriteSize.height);
		break;
	case 1:
		target->setScaleX(-1.0f);
		start = Vec2(visibleSize.width+spriteSize.width,visibleSize.height+spriteSize.height);
		end = Vec2(-spriteSize.width,-spriteSize.height);
		break;
	case 2:
		start = Vec2(-spriteSize.width,visibleSize.height+spriteSize.height);
		end = Vec2(visibleSize.width+spriteSize.width,-spriteSize.height);
		break;
	case 3:
		target->setScaleX(-1.0f);
		start = Vec2(visibleSize.width+spriteSize.width,-spriteSize.height);
		end = Vec2(-spriteSize.width,visibleSize.height+spriteSize.height);
		break;
	}

	target->setPosition(start);
	target->m_fishPath.pushBack(FishLineTo::create(target->m_speedTime,end));
}

void FishPathFactory::generateFishPathE( Fish *target )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size spriteSize = target->getContentSize();

	Vec2 start,end;
	float t1 = 15;
	int t2 = 10;

	int nNum = -1;
	if (Fish::_isFishLineGroup)//###
	{
		if(nNum == -1)
			nNum = 1;
	}
	else
	{
		nNum = CCRANDOM_0_1()*4;
	}
	//int nNum = CCRANDOM_0_1()*1;
	if(nNum){
		start = Vec2(-spriteSize.width,CCRANDOM_0_1()*((int)visibleSize.height-400)+300);
		end = Vec2(visibleSize.width+spriteSize.width,start.y);
	} else {
		start = Vec2(visibleSize.width+spriteSize.width, CCRANDOM_0_1()*((int)visibleSize.height-400)+300);
		end = Vec2(-spriteSize.width, start.y);
		target->setScaleX(-1.0f);
	}

	target->setPosition(start);
	target->m_fishPath.pushBack(generateBezierPath(start, (start+end)/2, (start+end)/2, end, target->m_speedTime));
}

void FishPathFactory::generateFishPathF( Fish *target )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size spriteSize = target->getContentSize();

	short dir = CCRANDOM_MINUS1_1() * 1;
	int offsetX = spriteSize.width + 100;
	Point start,end;
	if(dir == 1)
	{
		start = Point(-offsetX,visibleSize.height/2 + CCRANDOM_MINUS1_1() * visibleSize.height/2);
		end = start + Point(visibleSize.width + 2 * offsetX,0);
	}
	else
	{
		start = Point(visibleSize.width + offsetX,visibleSize.height/2 + CCRANDOM_MINUS1_1() * visibleSize.height/2);
		end = start - Point(visibleSize.width+2 * offsetX,0);
	}

	target->setPosition(start);
	target->m_fishPath.pushBack(FishSinTo::create(target->m_speedTime,start,end));
}

void FishPathFactory::generateFishPathG( Fish *target )
{
	//单个circle out 没用
}

void FishPathFactory::generateFishesPathF(Vector<Fish*>pfishes)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size spriteSize = ((Fish *)pfishes.at(0))->getContentSize();
	short dir = CCRANDOM_0_1() > 0.5f?1:-1;

	Point start,end;
	int offsetX = spriteSize.width + 100;
	if(dir == 1)
	{
		start = Point(-offsetX,visibleSize.height/2 + CCRANDOM_MINUS1_1() * visibleSize.height/2);
		end = start + Point(visibleSize.width+2*offsetX,0);
	}
	else
	{
		start = Point(visibleSize.width + offsetX,visibleSize.height/2 + CCRANDOM_MINUS1_1() * visibleSize.height/2);
		end = start - Point(visibleSize.width+2*offsetX,0);
	}

	for(int i=0; i < pfishes.size(); i++) {
		Fish *p = (Fish *)pfishes.at(i);
		
		p->setPosition(start);
		p->m_fishPath.pushBack(CCDelayTime::create(i * 0.5f));
		p->m_fishPath.pushBack(FishSinTo::create(p->m_speedTime,start,end));
	}
}

//circle out
void FishPathFactory::generateFishesPathG(Vector<Fish*>pfishes)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size spriteSize = ((Fish *)pfishes.at(0))->getContentSize();

	int ranWidth  = visibleSize.width * 3/4;
	int ranHeight = visibleSize.height * 3/4;
	Vec2 ranVec = Vec2(visibleSize.width/2 + (CCRANDOM_0_1() * ranWidth - ranWidth/2),visibleSize.height/2 + (CCRANDOM_0_1() * ranHeight - ranHeight/2));

	float interval = 0.3f;
	int count = pfishes.size();
	float preAngle = 360.0f/count;
	for (int i = 0; i < count; ++i)
	{
		//setRotation(90 - (angle * 360)/(2*3.1415926));
		float ag = preAngle * i;
		float delay = interval * i;
		Fish *f = (Fish *)pfishes.at(i);
		f->setPosition(ranVec);

		float ang = ag * M_PI / 180;
		f->setRotation(90 - ag);
		
		Vec2 vecTo = ranVec + Vec2(visibleSize.width * (cos(ang)) , visibleSize.width * (sin(ang)));

		DelayTime *action0 = DelayTime::create(delay);
		MoveTo    *action1 = MoveTo::create(f->m_speedTime,vecTo);

		f->m_fishPath.pushBack(action0);
		f->m_fishPath.pushBack(action1);
	}
}

FishPathFactory::FishPathType FishPathFactory::getFishPathType( Fish::FishType type )
{
	int nNum = 0;
	switch (type) {
	case Fish::FISH_XIAOGUANGYU:
	case Fish::FISH_XIAOCAOYU:
	case Fish::FISH_REDAIYU:
	case Fish::FISH_DAYANJINYU:
		{
			nNum = CCRANDOM_0_1()*4;
			switch (nNum)
			{
			case 0:
				return FISH_PATHTYPE_A;
			case 1:
				return FISH_PATHTYPE_B;
			case 2:
				return FISH_PATHTYPE_B_LINE;
			case 3:
				return FISH_PATHTYPE_F;
			}
		}
	case Fish::FISH_SHANWEIYU:
	case Fish::FISH_XIAOCHOUYU:
	case Fish::FISH_HETUN:
	case Fish::FISH_SHITOUYU:
	case Fish::FISH_DENGLONGYU:
	case Fish::FISH_REDAIZIYU:
	case Fish::FISH_WUGUI:
	case Fish::FISH_HUDIEYU:
	case Fish::FISH_MEIRENQUN:
	case Fish::FISH_JIANYU:
	case Fish::FISH_MOGUIYU:
	case Fish::FISH_DAYINSHA:
	case Fish::FISH_HUANGJINSHA:
	case Fish::FISH_XIAOFEIYU:
	case Fish::FISH_HAITUN:
	case Fish::FISH_JINHAITUN:
	case Fish::FISH_LONG:
	case Fish::FISH_LVWUGUI:
		nNum = CCRANDOM_0_1()*2;
		switch(nNum){
		case 0:
			return FISH_PATHTYPE_A;
		case 1:
			return FISH_PATHTYPE_B;
		}
	case Fish::FISH_ALILAN:
	case Fish::FISH_MEIRENYU:
	case Fish::FISH_ZIMOGUIYU:
	case Fish::FISH_QSDAYINSHA:
	case Fish::FISH_QSDAJINSHA:
	case Fish::FISH_HUANGXIYI:
	case Fish::FISH_JINXIYI:
		return FISH_PATHTYPE_A;

	case Fish::FISH_LONGXIA://以下暂时不用

		return FISH_PATHTYPE_A;
	default:
		return FISH_PATHTYPE_A;
	}
}

void FishPathFactory::createFishPath( Fish* target )
{
	FishPathType t = getFishPathType(target->m_fishType);
	switch(t){
	case FISH_PATHTYPE_A:
		return generateFishPathA(target);
	case FISH_PATHTYPE_B:
		return generateFishPathB(target);
	case FISH_PATHTYPE_C:
		return generateFishPathC(target);
	case FISH_PATHTYPE_D:
		return generateFishPathD(target);
	case FISH_PATHTYPE_E:
		return generateFishPathE(target);
	case FISH_PATHTYPE_STATIC:
		return generateStaticFishPath(target);
	default:
		return generateFishPathA(target);
	}
}

void FishPathFactory::generateFishesPath( Vector<Fish*>pfishes )
{
	if(pfishes.size() == 0)
		return;
	Fish::FishType ft = ((Fish*)pfishes.at(0))->m_fishType;
	FishPathType t = getFishPathType(ft);

	//for test
	//t = FISH_PATHTYPE_E;

	switch(t){
	case FISH_PATHTYPE_A:
		return generateFishesPathA(pfishes);
	case FISH_PATHTYPE_B:
		return generateFishesPathB(pfishes);
	case FISH_PATHTYPE_B_LINE:
		return generateFishesPathB_line(pfishes);
	case FISH_PATHTYPE_C:
		return generateFishesPathC(pfishes);
	case FISH_PATHTYPE_D:
		return generateFishesPathD(pfishes);
	case FISH_PATHTYPE_E:
		return generateFishesPathE(pfishes);
	case FISH_PATHTYPE_F:
		return generateFishesPathF(pfishes);
	case FISH_PATHTYPE_G:
		return generateFishesPathG(pfishes);
	case FISH_PATHTYPE_STATIC:
		return generateFishesPathStatic(pfishes);
	default:
		return generateFishesPathA(pfishes);
	}
}

void FishPathFactory::generateFishesPathA(Vector<Fish*>pfishes )
{
	Vec2 start,end;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if(pfishes.size() == 0)
		return;
	Size s = ((Fish*)pfishes.at(0))->getContentSize();

// 	start = Vec2(-s.height*3,CCRANDOM_0_1()*((int)visibleSize.height));
// 	end = Vec2(visibleSize.width+s.height*3,CCRANDOM_0_1()*((int)visibleSize.height));
	int blank = 50;
	int ran = CCRANDOM_0_1()*2;
	int dir = CCRANDOM_0_1()*2;
	int outOffset = MAX(s.width,s.height) * 2;
	if(ran == 0)
	{
		//左右
		if(dir == 0)
		{
			start = Vec2(-outOffset,CCRANDOM_0_1()*(visibleSize.height - 2*blank)+blank);
			end = Vec2(visibleSize.width+outOffset,CCRANDOM_0_1()*(visibleSize.height - 2*blank)+blank);
		}
		else
		{
			end = Vec2(-outOffset,CCRANDOM_0_1()*(visibleSize.height - 2*blank)+blank);
			start = Vec2(visibleSize.width+outOffset,CCRANDOM_0_1()*(visibleSize.height - 2*blank)+blank);
		}
	}
	else
	{
		//上下
		if(dir == 0)
		{
			start = Vec2(CCRANDOM_0_1()*(visibleSize.width - 2*blank)+blank,-outOffset);
			end = Vec2(CCRANDOM_0_1()*(visibleSize.height - 2*blank)+blank,visibleSize.height + outOffset);
		}
		else
		{
			end = Vec2(CCRANDOM_0_1()*(visibleSize.width - 2*blank)+blank,-outOffset);
			start = Vec2(CCRANDOM_0_1()*(visibleSize.height - 2*blank)+blank,visibleSize.height + outOffset);
		}
	}

	int r = sqrt(s.width*s.width+s.height*s.height);
	float angle = (CCRANDOM_0_1()*(int)((2*M_PI)*1000))/1000;
	bool direction = CCRANDOM_0_1()*2;

	for(int i=0; i < pfishes.size(); i++)
	{
		Fish *p = (Fish *)pfishes.at(i);
		float rs = CCRANDOM_0_1()*r;
		float re = CCRANDOM_0_1()*r;
		angle += (CCRANDOM_0_1()*(int)((M_PI/12)*1000))/1000;
		generateFishPathA(p,start+Vec2(rs*cos(angle),rs*sin(angle)),end+Vec2(re*cos(angle),re*sin(angle)),direction);
		angle += M_PI/6;
	}
}

void FishPathFactory::generateFishesPathB(Vector<Fish*>pfishes )
{
	Vec2 start,end;
	int blank = 20;
	int type = CCRANDOM_0_1()*4;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	if(pfishes.size() == 0)
		return;

	Size s = ((Fish*)pfishes.at(0))->getContentSize();

// 	start = Vec2(-s.height*3,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
// 	end = Vec2(visibleSize.width+s.height*3,CCRANDOM_0_1()*((int)visibleSize.height-blank)+blank);
	int centerOffset = 150;
	int ranOffset = centerOffset + CCRANDOM_0_1()*(visibleSize.height/2-centerOffset);
	int ranY = 0;
	int ran = CCRANDOM_0_1() * 2;
	if(ran == 0)
	{
		ranY = visibleSize.height/2 + ranOffset;
	}
	else 
	{
		ranY = visibleSize.height/2 - ranOffset;
	}
	start = Vec2(-s.height*3,ranY);
	int endY = 0;

	if (start.y < visibleSize.height/2)
	{
		endY = start.y + visibleSize.height/2;
	}
	else
	{
		endY = visibleSize.height - start.y;
	}
	end = Vec2(visibleSize.width+s.height*3,endY);

	int r = sqrt(s.width*s.width+s.height*s.height);
	float angle = M_PI/6;
	int offset = MAX(s.width,s.height);//40;
	for(int i=0; i < pfishes.size(); i++)
	{
		Fish *p = (Fish *)pfishes.at(i);
		generateFishPathB(p,type,start+Vec2(CCRANDOM_0_1()*offset*2 - offset,CCRANDOM_0_1()*offset*3 - offset),end+Vec2(CCRANDOM_0_1()*offset*3 - offset,CCRANDOM_0_1()*offset*3 - offset));
	}
}

void FishPathFactory::generateFishesPathB_line(Vector<Fish*>pfishes)
{
	Vec2 start,end;
	int blank = 20;
	int type = CCRANDOM_0_1()*4;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	if(pfishes.size() == 0)
		return;

	Size s = ((Fish*)pfishes.at(0))->getContentSize();

	int centerOffset = 150;
	int ranOffset = centerOffset + CCRANDOM_0_1()*(visibleSize.height/2-centerOffset);
	int ranY = 0;
	int ran = CCRANDOM_0_1() * 2;
	if(ran == 0)
	{
		ranY = visibleSize.height/2 + ranOffset;
	}
	else 
	{
		ranY = visibleSize.height/2 - ranOffset;
	}
	start = Vec2(-s.height*3,ranY);
	int endY = 0;

	if (start.y < visibleSize.height/2)
	{
		endY = start.y + visibleSize.height/2;
	}
	else
	{
		endY = visibleSize.height - start.y;
	}


	end = Vec2(visibleSize.width+s.height*3,endY);

	int r = sqrt(s.width*s.width+s.height*s.height);
	float angle = M_PI/6;
	int offset = 40;
	Point md = genRandMDPoint(start,end);
	for(int i=0; i < pfishes.size(); i++)
	{
		Fish *p = (Fish *)pfishes.at(i);
		float interval = p->m_speedTime * p->getContentSize().height/visibleSize.width*0.45f;
		p->m_fishPath.pushBack(DelayTime::create(i * interval));
		generateFishPathB_line(p,type,start,end,md);
	}
}

void FishPathFactory::generateFishesPathC(Vector<Fish*>pfishes )
{
	for(int i=0; i < pfishes.size(); i++) {
		Fish *p = (Fish *)pfishes.at(i);
		float interval = p->m_speedTime * p->getContentSize().height/Director::getInstance()->getVisibleSize().width*0.45f;/*修改*/
		p->m_fishPath.pushBack(DelayTime::create(i * interval));/*修改*/
		generateFishPathC(p);
	}
}

void FishPathFactory::generateFishesPathD(Vector<Fish*>pfishes )
{
	for(int i=0; i < pfishes.size(); i++) {
		Fish *p = (Fish *)pfishes.at(i);
		generateFishPathD(p);
	}
}

void FishPathFactory::generateFishesPathE(Vector<Fish*>pfishes )
{
	int nNum = CCRANDOM_0_1()*1;

	for(int i=0; i < pfishes.size(); i++) {
		Fish *p = (Fish *)pfishes.at(i);
		//generateFishPathE(p);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Size spriteSize = p->getContentSize();
		Point start,end;

		float py = ((visibleSize.height-400)+300)*i/pfishes.size()+100;
		py += (CCRANDOM_0_1()*spriteSize.height)/2-spriteSize.height/4;
		if(nNum){
			start = Vec2(-spriteSize.width,py);
			end = Vec2(visibleSize.width+spriteSize.width,start.y);
		} else {
			start = Vec2(visibleSize.width+spriteSize.width,py);
			end = Vec2(-spriteSize.width, start.y);
			p->setScaleX(-1.0f);
		}

		p->setPosition(start);
		p->m_fishPath.pushBack(generateBezierPath(start, (start+end)/2, (start+end)/2, end, p->m_speedTime));
	}
}

void FishPathFactory::generateFishesPathStatic(Vector<Fish*>pfishes )
{
	for(int i=0; i < pfishes.size(); i++)
	{
		Fish *p = (Fish *)pfishes.at(i);
		createFishPath(p);
	}
}
