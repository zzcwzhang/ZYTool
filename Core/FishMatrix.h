//
//  FishMatrix.h
//  fish
//
//  Created by zhiyxu on 13-12-23.
//
//

#ifndef __fish__FishMatrix__
#define __fish__FishMatrix__

#include <iostream>

#include "cocos2d.h"
#include "Fish.h"

class Room;

class FishMatrix : public cocos2d::Sprite
{
public:
    enum FishMatrix_Type
	{
        FISH_MATRIX_CIRCLE,
        FISH_MATRIX_SCATTER,
        FISH_MATRIX_RANK,
        FISH_MATRIX_ELLIPSE,
        FISH_MATRIX_HELIX,
        FISH_MATRIX_MAX
    };

    static FishMatrix *create(Room *parent,FishMatrix_Type type = FISH_MATRIX_MAX);
    virtual void goFishMatrix(){}
    virtual void removefromParent();
    Vector<Fish*> m_fishes;
    Room * m_parent;
};

class FishMatrixCircle : public FishMatrix
{
public:
    static FishMatrixCircle* create(Room *parent);
    virtual void goFishMatrix();
    void stop(float dt);
};

class FishMatrixScatter : public FishMatrix
{
public:
    static FishMatrixScatter* create(Room *parent);
    virtual void goFishMatrix();
    void stop(float dt);
};

class FishMatrixRank : public FishMatrix
{
public:
    static FishMatrixRank* create(Room *parent);
    virtual void goFishMatrix();
    void stop(float dt);
};

class FishMatrixEllipse : public FishMatrix
{
public:
    static FishMatrixEllipse* create(Room *parent);
    virtual void goFishMatrix();
    void stop(float dt);
};

class FishMatrixHelix : public FishMatrix
{
public:
    static FishMatrixHelix* create(Room *parent);
    virtual void goFishMatrix();
    void stop(float dt);
};

#endif /* defined(__fish__FishMatrix__) */
