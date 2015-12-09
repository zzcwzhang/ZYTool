//
//  FishMatrix.cpp
//  fish
//
//  Created by zhiyxu on 13-12-23.
//
//

#include "FishMatrix.h"
#include "Room.h"
#include "FishPath.h"
#include "MyFishPath.h"
#include "SConfig.h"

USING_NS_CC;


FishMatrix *FishMatrix::create(Room *parent,FishMatrix_Type type)
{
    if(type == FISH_MATRIX_MAX) {
		int nNum = CCRANDOM_0_1()*FISH_MATRIX_MAX;
        type = FISH_MATRIX_CIRCLE;//(FishMatrix_Type)(nNum);
    }
    
    switch (type) {
        case FISH_MATRIX_CIRCLE:
            return FishMatrixCircle::create(parent);
        case FISH_MATRIX_SCATTER:
            return FishMatrixScatter::create(parent);
        case FISH_MATRIX_RANK:
            return FishMatrixRank::create(parent);
        case FISH_MATRIX_ELLIPSE:
            return FishMatrixEllipse::create(parent);
        case FISH_MATRIX_HELIX:
            return FishMatrixHelix::create(parent);
        default:
            break;
    }
    
    return NULL;
}

void FishMatrix::removefromParent()
{
    m_parent->startFishGenerator(true);
    m_fishes.clear();
    this->removeAllChildrenWithCleanup(true);
	unschedule(schedule_selector(FishMatrixCircle::stop));
}


FishMatrixCircle * FishMatrixCircle::create(Room *parent)
{
    FishMatrixCircle*p = new FishMatrixCircle();
    p->init();
    p->m_parent = parent;
    
    Fish *pfc = Fish::createSpecificFish(p->m_parent, Fish::FISH_MOGUIYU,false);
    
    pfc->setPosition(Vec2(-500,-500));
    //pfc->m_fishPath = new CCArray();
    pfc->m_fishPath.pushBack(CCRepeat::create(Circle::create(30, Vec2(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2), 1),40));
    p->m_fishes.pushBack(pfc);
    
    //shitouyu
    Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_SHITOUYU,false);
    Size s = pf->getContentSize();
    float duration = 30;
    float radius = 150;
    int num = 2*M_PI*radius/s.height;
    float interval = duration/num;
    for(int i = 0; i < num;i++) {

        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_SHITOUYU,false);
        pf->setPosition(Vec2(-500,-500));

        //pf->m_fishPath = new CCArray();
        pf->m_fishPath.pushBack(CCDelayTime::create(interval*i));
        pf->m_fishPath.pushBack(CCRepeat::create(Circle::create(30, Vec2(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2), radius),40));
        p->m_fishes.pushBack(pf);
    }
    
    //shitouyu
    pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_DAYANJINYU,false);
    s = pf->getContentSize();
    duration = 30;
    radius = 200;
    num = 2*M_PI*radius/s.height;
    interval = duration/num;
    for(int i = 0; i < num;i++) {
        
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_DAYANJINYU,false);
        pf->setPosition(Vec2(-500,-500));
        
        //pf->m_fishPath = new CCArray();
        pf->m_fishPath.pushBack(CCDelayTime::create(interval*i));
        pf->m_fishPath.pushBack(CCRepeat::create(Circle::create(30, Vec2(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2), radius),40));
        p->m_fishes.pushBack(pf);
    }
    
    //redaiyu
    pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_REDAIYU,false);
    s = pf->getContentSize();
    duration = 30;
    radius = 250;
    num = 2*M_PI*radius/s.height;
    interval = duration/num;
    for(int i = 0; i < num;i++) {
        
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_REDAIYU,false);
        pf->setPosition(Vec2(-500,-500));
        
        //pf->m_fishPath = new CCArray();
        pf->m_fishPath.pushBack(CCDelayTime::create(interval*i));
        pf->m_fishPath.pushBack(CCRepeat::create(Circle::create(30, Vec2(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2), radius),40));
        p->m_fishes.pushBack(pf);
    }
    
    //xiaoguangyu
    pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_XIAOGUANGYU,false);
    s = pf->getContentSize();
    duration = 30;
    radius = 300;
    num = 2*M_PI*radius/s.height;
    interval = duration/num;
    for(int i = 0; i < num;i++) {
        
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_XIAOGUANGYU,false);
        pf->setPosition(Vec2(-500,-500));
        
        //pf->m_fishPath = new CCArray();
        pf->m_fishPath.pushBack(CCDelayTime::create(interval*i));
        pf->m_fishPath.pushBack(CCRepeat::create(Circle::create(30, Vec2(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2), radius),40));
        p->m_fishes.pushBack(pf);
    }
    
    return p;
}


void FishMatrixCircle::goFishMatrix()
{
    this->schedule(schedule_selector(FishMatrixCircle::stop), 10.0f, 5, 30);
}

void FishMatrixCircle::stop(float dt)
{
    Fish *pt = nullptr;
    for(auto pf : m_fishes)
    {
        if(pt == nullptr) {
            pt = pf;
        }
        
        if(pt->m_fishType == pf->m_fishType) {
            pf->stopAllActions();
            Vec2 last = pf->m_lastPoint;
            Vec2 current = pf->getPosition();
            double angle = atan2((current.y-last.y),(current.x-last.x));
            Vec2 end = Vec2(700*cos(angle),700*sin(angle));
            pf->m_fishPath.clear();
            pf->m_fishPath.pushBack(MoveBy::create(10, end));
            
        }
    }
    
	int count = m_fishes.size();
    for(int i = count - 1; i >= 0; i--)
    {
		Fish* pf = m_fishes.at(i);
        if(pt->m_fishType == pf->m_fishType) {
            pf->goFish();
            m_fishes.eraseObject(pf);
        }
    }
    
    if(m_fishes.size() == 0) {
        removefromParent();
    }
}


///---------------Implementation of FishMatrixScatter---------------------

FishMatrixScatter* FishMatrixScatter::create(Room *parent)
{
    FishMatrixScatter *p = new FishMatrixScatter();
    p->init();
    p->m_parent = parent;
    
    float interval = 0.1f;
    for(int i = 0; i < 300; i++)
	{
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_XIAOCAOYU,false);
        
        pf->setPosition(Vec2(-500,-500));
        //pf->m_fishPath = new CCArray();
        pf->m_fishPath.pushBack(DelayTime::create(interval*i));
        
        int ag = CCRANDOM_0_1()*360;
        float angle = 2*M_PI*ag/360;
        Vec2 to = Vec2(700*cos(angle),700*sin(angle));
        pf->setRotation(90-ag);
        pf->m_fishPath.pushBack(MoveFromBy::create(5,Vec2(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2), to));
        p->m_fishes.pushBack(pf);
    }
    
    return p;
}

void FishMatrixScatter::goFishMatrix()
{
    scheduleOnce(schedule_selector(FishMatrixScatter::stop), 30);
}

void FishMatrixScatter::stop(float dt)
{
    removefromParent();
}

///---------------Implementation of FishMatrixRank---------------------

FishMatrixRank* FishMatrixRank::create(Room *parent)
{
    FishMatrixRank *p = new FishMatrixRank();
    p->init();
    p->m_parent = parent;
    Size screen = Director::getInstance()->getVisibleSize();
    int blank = 100;
        
    Point last = Vec2(CCRANDOM_0_1()*10,-blank);
    float interval = 0.3f;
    while(1) {
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_XIAOCAOYU,false);
        int aaa = (CCRANDOM_0_1()*10 - 10);
        float lasty = (-blank+aaa);
        last = Vec2((last.x+CCRANDOM_0_1()*10+10),lasty);
        pf->setPosition(last);
        //pf->m_fishPath = new CCArray();
        pf->m_fishPath.pushBack(DelayTime::create(interval*(CCRANDOM_0_1()*5)));
        
        pf->m_fishPath.pushBack(MoveBy::create(3, Vec2(0,250)));
        
        pf->m_fishPath.pushBack(DelayTime::create(55));
        pf->m_fishPath.pushBack(MoveBy::create(6, Vec2(0,screen.height+2*blank - 250)));
        p->m_fishes.pushBack(pf);
        
        if(last.x > SCREEN_WIDTH)
            break;
    }
    
    
    last = Vec2(CCRANDOM_0_1()*10,screen.height+blank);
    interval = 0.3f;
    while(1) {
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_XIAOCAOYU,false);
        int aaa = (CCRANDOM_0_1()*10 - 10);
        float lasty=screen.height+blank+aaa;
        last = Vec2(last.x+CCRANDOM_0_1()*10+10,lasty);
        pf->setPosition(last);
        pf->setRotation(180);
        //pf->m_fishPath = new CCArray();
        pf->m_fishPath.pushBack(DelayTime::create(interval*(CCRANDOM_0_1()*5)));
        
        pf->m_fishPath.pushBack(MoveBy::create(3, Vec2(0,-250)));
        pf->m_fishPath.pushBack(DelayTime::create(55));
        pf->m_fishPath.pushBack(MoveBy::create(6, Vec2(0,-(screen.height+2*blank - 250))));
        p->m_fishes.pushBack(pf);
        
        if(last.x > SCREEN_WIDTH) {
            break;
        }
    }
    
    
    
    
    Fish *tp = Fish::createSpecificFish(p->m_parent, Fish::FISH_DENGLONGYU,false);
    Size s = tp->getContentSize();
    //tp->release();
    
    for(int i=0; i < 20;i++) {
        Fish *pf;
        if(i < 5) {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_MOGUIYU,false);
        } else if(i < 10) {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_WUGUI,false);
        } else if(i < 15) {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_SHANWEIYU,false);
        } else {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_REDAIZIYU,false);
        }
        pf->setPosition(Vec2(-200,300));
        pf->cocos2d::Node::setRotation(90);
        
        //pf->m_fishPath = new CCArray();
        pf->m_fishPath.pushBack(DelayTime::create(5+2*i));
        pf->m_fishPath.pushBack(MoveBy::create(15, Vec2(SCREEN_WIDTH+2*200,0)));
        p->m_fishes.pushBack(pf);
    }
    
    
    
    for(int i=0; i < 20;i++) {
        Fish *pf;
        if(i < 5) {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_MOGUIYU,false);
        } else if(i < 10) {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_WUGUI,false);
        } else if(i < 15) {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_SHANWEIYU,false);
        } else {
            pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_REDAIZIYU,false);
        }
        
        pf->setPosition(Vec2(SCREEN_WIDTH+200,screen.height-300));
        pf->cocos2d::Node::setRotation(-90);
        
        //pf->m_fishPath = new CCArray();
        pf->m_fishPath.pushBack(DelayTime::create(5+2*i));
        pf->m_fishPath.pushBack(MoveBy::create(15, Vec2(-SCREEN_WIDTH-2*200,0)));
        p->m_fishes.pushBack(pf);
    }
    
    return p;
}


void FishMatrixRank::goFishMatrix()
{
    scheduleOnce(schedule_selector(FishMatrixRank::stop), 66);
}

void FishMatrixRank::stop(float dt)
{
    removefromParent();
}


FishMatrixEllipse* FishMatrixEllipse::create(Room *parent)
{
    FishMatrixEllipse *p = new FishMatrixEllipse();
    p->init();
   
    p->m_parent = parent;
    
    float interval = 1;
    
    Fish *pfc = Fish::createSpecificFish(p->m_parent, Fish::FISH_MOGUIYU,false);
    pfc->setPosition(Vec2(-500,-500));
    
    //pfc->m_fishPath = new CCArray();
    pfc->m_fishPath.pushBack(Repeat::create(Circle::create(20, Vec2(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2), 1),40));
	p->m_fishes.pushBack(pfc);
    
    for(int i = 0; i < 20; i++) {
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_REDAIZIYU,false);
        
        pf->setPosition(Vec2(-500,-500));
        //pf->m_fishPath = new CCArray();
        pf->m_fishPath.pushBack(DelayTime::create(interval*i));

        ccEllipseConfig c;
        c.centerPosition = Vec2(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2);
        c.aLength = 100;
        c.bLength = 300;
        c.angle = 0;
        pf->m_fishPath.pushBack(Repeat::create(EllipseBy::create(20,c),40));
        p->m_fishes.pushBack(pf);
    }

    for(int i = 0; i < 20; i++) {
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_REDAIZIYU,false);
        
        pf->setPosition(Vec2(-500,-500));
        //pf->m_fishPath = new CCArray();
        pf->m_fishPath.pushBack(DelayTime::create(interval*i));
        
        ccEllipseConfig c;
        c.centerPosition = Vec2(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2);
        c.aLength = 100;
        c.bLength = 300;
        c.angle = 2*M_PI/3;
        pf->m_fishPath.pushBack(Repeat::create(EllipseBy::create(20, c), 40));
        p->m_fishes.pushBack(pf);
    }
    
    for(int i = 0; i < 20; i++) {
        Fish *pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_REDAIZIYU, false);
        
        pf->setPosition(Vec2(-500,-500));
        //pf->m_fishPath = new CCArray();
        pf->m_fishPath.pushBack(DelayTime::create(interval*i));
        
        ccEllipseConfig c;
        c.centerPosition = Vec2(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2);
        c.aLength = 100;
        c.bLength = 300;
        c.angle = 4*M_PI/3;
        pf->m_fishPath.pushBack(Repeat::create(EllipseBy::create(20, c), 40));
        p->m_fishes.pushBack(pf);
    }
    
    return p;
}



void FishMatrixEllipse::goFishMatrix()
{
    schedule(schedule_selector(FishMatrixEllipse::stop), 10.0f, 2, 40);
}


void FishMatrixEllipse::stop(float dt)
{
    Fish *pt = NULL;
    for(auto pf : m_fishes)
    {
        if(pt == NULL) {
            pt = pf;
        }
        
        if(pt->m_fishType == pf->m_fishType) {
            pf->stopAllActions();
            Vec2 last = pf->m_lastPoint;
            Vec2 current = pf->getPosition();
            double angle = atan2((current.y-last.y),(current.x-last.x));
            Vec2 end = Vec2(700*cos(angle),700*sin(angle));
            //pf->m_fishPath->removeAllObjects();
            //pf->m_fishPath->addObject(CCMoveBy::create(10, end));
            
        }
    }
    
	int count = m_fishes.size();
    for(int i = count - 1;i >= 0; i--)
    {
        Fish* pf=m_fishes.at(i);
        if(pt->m_fishType == pf->m_fishType) {
            pf->goFish();
            m_fishes.eraseObject(pf);
        }
    }
    
    if(m_fishes.size() == 0) {
        removefromParent();
    }
}


FishMatrixHelix* FishMatrixHelix::create(Room *parent)
{
    FishMatrixHelix *p = new FishMatrixHelix();
    p->init();
    p->m_parent = parent;
    
    float interval = 1;
    Fish *pf = NULL;
    
    for(int i = 0; i < 30; i++) {
        pf = Fish::createSpecificFish(p->m_parent, Fish::FISH_DENGLONGYU,false);
        
        pf->setPosition(Vec2(-500,-500));
        //pf->m_fishPath = new CCArray();
        pf->m_fishPath.pushBack(DelayTime::create(interval*i));
        
        pf->m_fishPath.pushBack(Repeat::create(Helix::create(30,Vec2(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2),100,SCREEN_WIDTH / 2+50),1));
        p->m_fishes.pushBack(pf);
    }

    return p;
}



void FishMatrixHelix::goFishMatrix()
{
    scheduleOnce(schedule_selector(FishMatrixHelix::stop), 60);
}


void FishMatrixHelix::stop(float dt)
{
    removefromParent();
}

