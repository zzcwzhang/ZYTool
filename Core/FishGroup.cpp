//
//  FishGroup.cpp
//  fish
//
//  Created by zhiyxu on 13-11-28.
//
//

#include "FishGroup.h"
#include "FishPath.h"
#include "GameLayer.h"
//#include "Fish.h"
#include <vector>

Vector<Fish*> FishGroup::createFishGroup(Room* parent,FishGroupType type,Fish::FishType ft)
{
    //if(ft == Fish::FISH_NORMAL_TYPEMAX /*|| ft == Fish::FISH_All_TYPEMAX*/)
    {
        ft = Fish::getRefreshFishType();
    }
    int num = Fish::getRefreshFishNum(ft);

    if( ft == Fish::FISH_HUDIEYU ) {
        //xiao fei yu only support line group
        //return createFishLineGroup(parent,ft,num);
    }

    switch (type) {
        case FishGroupLine:
            return createFishLineGroup(parent,ft,num);
        case FishGroupRand:
            return createFishRandGroup(parent,ft,num);
        default:
            break;
    }
}

Vector<Fish*> FishGroup::createFishLineGroup(Room* parent,Fish::FishType type,int num)
{
    Vector<Fish*> pa;
    Fish *pf = NULL;
    Fish *p = NULL;
    float interval = 0.5;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    for(int i=0; i < num; i++) {

        if(pf == NULL) {
            pf = Fish::createSpecificFish(parent,type);
            p = pf;
        } else {
            p = Fish::createSpecificFish(parent,type/*,false*/);
            //p->m_fishPath = Array::createWithArray(pf->m_fishPath);
            interval = p->m_speedTime * p->getContentSize().height/visibleSize.width*0.45f;
            p->m_fishPath.insert(0,CCDelayTime::create(interval*i));
            //p->setPosition(pf->getPosition());
            //p->setFlipX(pf->isFlipX());
        }
        pa.pushBack(p);
    }

    return pa;
}

Vector<Fish*> FishGroup::createFishRandGroup(Room* parent,Fish::FishType type,int num)
{
    Vector<Fish*> pa;
    for(int i=0; i < num; i++) {
        Fish *p = Fish::createSpecificFish(parent,type,false);
        pa.pushBack(p);
    }
    
    FishPathFactory::generateFishesPath(pa);
    
    return pa;
}
