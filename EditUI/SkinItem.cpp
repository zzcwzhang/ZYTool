#include "SkinItem.h"
#include "DataStream.h"
USING_NS_CC;
SkinItem::SkinItem()
{
	//needFunc = false;
}
SkinItem::~SkinItem()
{

}
void SkinItem::loadItem(DataStream *dis)
{
	this->x = dis->readShort();
	this->y = dis->readShort();
	this->mirror = dis->readByte();
	this->rotAngle = dis->readShort();
	this->opacity = dis->readShort();
	short r = dis->readShort();
	short g = dis->readShort();
	short b = dis->readShort();
	this->color = Color3B(r,g,b);
	this->imgId = dis->readShort();
	this->sx = dis->readShort();
	this->sy = dis->readShort();
	this->sw = dis->readShort();
	this->sh = dis->readShort();
}

//CCRect SkinItem::getSpriteRect(UIForm *form)
//{
//	CCRect rect = form->getRect(imgId);
//	int x = rect.origin.x + sx;
//	int y = rect.origin.y + sy;
//	int w = sw;
//	int h = sh;
//	return rect;
//}

short SkinItem::getOpacity()
{
	return this->opacity;
}

Color3B SkinItem::getColor()
{
	return this->color;
}

Vec2 SkinItem::getLocation()
{
	return Vec2(x, y);
}

short SkinItem::getMirror()
{
	return this->mirror;
}
short SkinItem::getRotAngle()
{
	return this->rotAngle;
}
