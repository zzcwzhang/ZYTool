//
//  MyFishPath.cpp
//  fish
//
//  Created by zhiyxu on 13-12-23.
//
//

#include "MyFishPath.h"
#include "Fish.h"
bool Circle::initWithDuration(float t, Vec2 center,float radius,float start)
{
    if (ActionInterval::initWithDuration(t))
    {
        m_center = center;
        m_radius = radius;
        m_start = start;
        return true;
    }
    
    return false;
}


Circle* Circle::create(float t, Vec2 center, float radius, float start)
{
    Circle *pc = new Circle();
    pc->initWithDuration(t, center,radius,start);
    pc->autorelease();
    
    return pc;
}


void Circle::update(float time)
{
    if (_target)
    {
        Vec2 last = ((Fish*)this->getTarget())->m_lastPoint;
        Vec2 current = this->getTarget()->getPosition();
        
        if(last.x != -500 || last.y != -500) {
            double angle = atan2((current.y-last.y),(current.x-last.x));
            this->getTarget()->setRotation(90 - (angle * 360)/(2*3.1415926));
        }
        ((Fish*)this->getTarget())->m_lastPoint = current;
        _target->setPosition(m_center + Vec2(m_radius*cos(m_start + (2*M_PI)*time),m_radius*sin(m_start + (2*M_PI)*time)));
    }
}


MoveFromBy * MoveFromBy::create(float duration, const Vec2 &from, const Vec2 &deltaPosition)
{
    MoveFromBy * pn = new MoveFromBy;
    pn->initWithDuration(duration, from, deltaPosition);
    
    return pn;
}

bool MoveFromBy::initWithDuration(float duration, const Vec2& from, const Vec2& deltaPosition)
{
    m_from = from;
    m_started = false;
    return MoveBy::initWithDuration(duration, deltaPosition);
}

void MoveFromBy::update(float time)
{
    if(!m_started && getTarget()) {
        getTarget()->setPosition(m_from);
        m_started = true;
    }
    
    return MoveBy::update(time);
}






//++++++++++++++++++++++++++++++


//static inline float tuoyuanXat( float a, float bx, float c, float t )//返回X坐标
//{
//    //参数方程
//    //return -a*cos(2*M_PI*t)+a;
//    //float x = -a*cos(2*M_PI*t)+a;
//    return a*cos(2*M_PI*t);
//}
//static inline float tuoyuanYat( float a, float by, float c, float t )//返回Y坐标
//{
//    float b = sqrt(powf(a, 2) - powf(c, 2));//因为之前定义的参数是焦距c而不是短半轴b，所以需要计算出b
//    //参数方程
//    return b*sin(2*M_PI*t);
//}

Point getEllipsePos(float a, float b,float angle,float t)
{
    float x = a*cos(2*M_PI*t);
    float y = b*sin(2*M_PI*t);
    
    float u = x*cos(angle)+y*sin(angle);
    float v = x*sin(angle)-y*cos(angle);
    
    return Vec2(u,v);
}


EllipseBy* EllipseBy::create(float t, const ccEllipseConfig& c)//利用之前定义的椭圆的三个参数初始化椭圆
{
    EllipseBy *pTuoyuanBy = new EllipseBy();
    pTuoyuanBy->initWithDuration(t, c);
    pTuoyuanBy->autorelease();
    
    return pTuoyuanBy;
}

bool EllipseBy::initWithDuration(float t, const ccEllipseConfig& c)
{
    if (ActionInterval::initWithDuration(t))
    {
        m_sConfig = c;
        return true;
    }
    
    return false;
}
void EllipseBy::update(float time)
{
    if (_target)
    {
        //rotate
        Point last = ((Fish*)this->getTarget())->m_lastPoint;
        Point current = this->getTarget()->getPosition();
        
        if(last.x != -500 || last.y != -500) {
            double angle = atan2((current.y-last.y),(current.x-last.x));
            this->getTarget()->setRotation(90 - (angle * 360)/(2*3.1415926));
        }
        ((Fish*)this->getTarget())->m_lastPoint = current;
        
        //
        Point s_startPosition =m_sConfig.centerPosition;//中心点坐标
        float a = m_sConfig.aLength;
        float b = m_sConfig.bLength;
        float angle = m_sConfig.angle;
        _target->setPosition(ccpAdd(s_startPosition, getEllipsePos(a,b,angle,time)));//由于我们画计算出的椭圆你做值是以原点为中心的，所以需要加上我们设定的中心点坐标
    }
}




bool Helix::initWithDuration(float t, Point center,float minRadius,float maxRadius,float start)
{
    if (ActionInterval::initWithDuration(t))
    {
        m_center = center;
        m_minRadius = minRadius;
        m_maxRadius = maxRadius;
        m_start = start;
        return true;
    }
    
    return false;
}


Helix* Helix::create(float t, Point center,float minRadius,float maxRadius,float start)
{
    Helix *pc = new Helix();
    pc->initWithDuration(t, center,minRadius,maxRadius,start);
    pc->autorelease();
    
    return pc;
}


void Helix::update(float time)
{
    if (_target)
    {
        Point last = ((Fish*)this->getTarget())->m_lastPoint;
        Point current = this->getTarget()->getPosition();
        
        if(last.x != -500 || last.y != -500) {
            double angle = atan2((current.y-last.y),(current.x-last.x));
            this->getTarget()->setRotation(90 - (angle * 360)/(2*3.1415926));
        }
        ((Fish*)this->getTarget())->m_lastPoint = current;
        _target->setPosition(m_center + Vec2(((m_maxRadius-m_minRadius)*time+m_minRadius)*cos(m_start + (6*M_PI)*time),((m_maxRadius-m_minRadius)*time+m_minRadius)*sin(m_start + (6*M_PI)*time)));
    }
}