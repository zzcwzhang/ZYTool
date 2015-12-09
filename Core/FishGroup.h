//
//  FishGroup.h
//  fish
//
//  Created by zhiyxu on 13-11-28.
//
//

#ifndef __fish__FishGroup__
#define __fish__FishGroup__

#include <iostream>
#include "cocos2d.h"
// #include "GameLayer.h"
#include "Fish.h"
USING_NS_CC;
class Room;

class FishGroup{
public:
    enum FishGroupType{
        FishGroupLine = 0,
        FishGroupRand
    };
    static Vector<Fish*> createFishGroup(Room *parent,FishGroupType type,Fish::FishType ft = Fish::FISH_NORMAL_TYPEMAX);
    
    static Vector<Fish*> createFishLineGroup(Room *parent,Fish::FishType type,int num);
    static Vector<Fish*> createFishRandGroup(Room *parent,Fish::FishType type,int num);
};

#endif /* defined(__fish__FishGroup__) */
