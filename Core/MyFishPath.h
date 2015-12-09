//
//  MyFishPath.h
//  fish
//
//  Created by zhiyxu on 13-12-23.
//
//

#ifndef __fish__MyFishPath__
#define __fish__MyFishPath__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;


class  Circle : public ActionInterval
{
public:
    bool initWithDuration(float t, Vec2 center,float radius,float start = 0);
    virtual void update(float time);//利用update函数来不断的设定坐标
public:
    static Circle *create(float t, Vec2 center,float radius, float start = 0);
    
protected:
    Vec2 m_center;
    float m_radius;
    float m_start;
};


class MoveFromBy : public MoveBy
{
public:
    static MoveFromBy* create(float duration, const Vec2& from,const Vec2& deltaPosition);
    bool initWithDuration(float duration, const Vec2& from, const Vec2& deltaPosition);
    virtual void update(float time);
protected:
    Vec2 m_from;
    bool m_started;
};



typedef struct _ccEllipseConfig {
    //中心点坐标
    Vec2 centerPosition;
    float aLength;
    float bLength;
    float angle;
} ccEllipseConfig;


class EllipseBy : public ActionInterval
{
public:
    //用“动作持续时间”和“椭圆控制参数”初始化动作
    bool initWithDuration(float t, const ccEllipseConfig& c);
    virtual void update(float time);//利用update函数来不断的设定坐标
public:
    //用“动作持续时间”和“椭圆控制参数”创建动作
    static EllipseBy *create(float t, const ccEllipseConfig& c);
    
protected:
    ccEllipseConfig m_sConfig;
    Vec2 m_startPosition;
    Vec2 s_startPosition;
    Vec2 m_from;
};


class  Helix : public ActionInterval
{
public:
    bool initWithDuration(float t, Vec2 center,float minRadius,float maxRadius,float start = 0);
    virtual void update(float time);//利用update函数来不断的设定坐标
public:
    static Helix *create(float t, Vec2 center,float minRadius,float maxRadius, float start = 0);
    
protected:
    Vec2 m_center;
    float m_minRadius;
    float m_maxRadius;
    float m_start;
};

#endif /* defined(__fish__MyFishPath__) */
