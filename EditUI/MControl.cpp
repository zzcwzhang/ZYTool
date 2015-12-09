#include "UI.h"
float MControl::ClickInterval = 0.15f;
MControl::MControl()
{
	form = NULL;
	curSkin = NULL;
	curFraemIndex = 0;
	curDelayTime = 0;
	//scripts = NULL;
	//skins = NULL;
	needUpdate = false;
	skinNode = NULL;
	paintNode = NULL;

	touchBegan = NULL;
	touchEnd = NULL;
	touchMove = NULL;
	clickEvent = NULL;
	DoubleClickEvent = NULL;
	updateEvent = NULL;
	paintEvent = NULL;

	userData = NULL;
	lockTime = 1.0f;

	m_bClick = false;
	m_bPressed = false;
	m_bEnabled = true;
	m_bNeedRemove = false;

	this->ignoreAnchorPointForPosition(false);
}
MControl::~MControl()
{
	ctrlList.clear();

	/*if(scripts)
	{
		scripts->removeAllObjects();
		CC_SAFE_RELEASE_NULL(scripts);
	}*/
}

void MControl::loadData(DataStream *dis)
{
	this->id = dis->readShort();

	short x = dis->readShort();
	short y = dis->readShort();
	this->location = Vec2(x,y);

	short w = dis->readShort();
	short h = dis->readShort();
	this->size = Size(w,h);

	short r = dis->readShort();
	short g = dis->readShort();
	short b = dis->readShort();
	short a = dis->readShort();
	this->color = Color4B(r,g,b,a);
	this->opacity = dis->readShort();
	this->rot = dis->readShort();

	float sx = dis->readInt()/100.0f;
	float sy = dis->readInt()/100.0f;
	this->scale = Vec2(sx,sy);

	float ax = dis->readInt()/100.0f;
	float ay = dis->readInt()/100.0f;
	this->anchor = Vec2(ax,ay);

	this->ctrlFlag = dis->readShort();
	this->parentId = dis->readShort();

	int count = dis->readByte();
	if(count > 0)
	{
		for (int i = 0; i < count; i++)
		{
			int scriptId = dis->readByte();
			this->scripts.pushBack(form->getScriptData(scriptId));
		}
	}

	skinNode = Node::create();
	this->addChild(skinNode);
	this->paintNode = Node::create();
	this->addChild(paintNode);

	count = dis->readByte();
	if(count > 0)
	{

		for (int i = 0; i < count; i++)
		{
			short type = dis->readByte();
			MControl *ctrl = NULL;
			switch(type)
			{
			case Type_Label:
				ctrl = MLabel::create();
				break;
			case Type_Button:
				ctrl = MButton::create();
				break;
			case Type_ListView:
				ctrl = MListView::create();
				break;
			}
			ctrl->form = this->form;
			ctrl->type = type;
			ctrl->form->addControl(ctrl);
			this->addChild(ctrl);
			this->addControl(ctrl);
			ctrl->loadData(dis);
		}
	}
}

void MControl::initMControl()
{
	if(this->curSkin)
	{
		curFraemIndex = 0;
		curDelayTime = 0;
	}
	this->initWithColor(this->color);
	skinNode->setContentSize(this->size);
	paintNode->setContentSize(this->size);
	this->setContentSize(this->size);
	this->setPosition(this->location.x,location.y);
	this->setAnchorPoint(this->anchor);
	this->setRotation(-this->rot);
	this->setScaleX(this->scale.x);
	this->setScaleY(this->scale.y);
	
	if(!this->checkFlag(F_Visible))
	{
		this->setVisible(false);
	}

	for(auto ctrl : this->ctrlList)
	{
		ctrl->initMControl();
	}
	
	needUpdate = true;
}

void MControl::copy(MControl *ctrl)
{
	this->id = -ctrl->id;//¸´ÖÆ¿Ø¼þ
	this->location = ctrl->location;
	this->opacity = ctrl->opacity;
	this->size = ctrl->size;
	this->rot = ctrl->rot;
	this->color = ctrl->color;
	this->scale = ctrl->scale;
	this->anchor = ctrl->anchor;
	this->ctrlFlag = ctrl->ctrlFlag;

	this->touchBegan = ctrl->touchBegan;
	this->touchMove = ctrl->touchMove;
	this->touchEnd = ctrl->touchEnd;
	this->clickEvent = ctrl->clickEvent;
	this->DoubleClickEvent = ctrl->DoubleClickEvent;
	this->updateEvent = ctrl->updateEvent;
	this->paintEvent = ctrl->paintEvent;
	this->userData = ctrl->userData;

	this->form = ctrl->form;

	this->skinNode = Node::create();
	this->addChild(skinNode);
	this->paintNode = Node::create();
	this->addChild(paintNode);

	for (auto srcCtrl : ctrl->ctrlList)
	{
		MControl *tempCtrl = srcCtrl->clone();
		this->addChild(tempCtrl);
		this->addControl(tempCtrl);
	}
	
}

MControl* MControl::clone()
{
	return NULL;
}

void MControl::refresh()
{
	needUpdate = true;
	for (auto srcCtrl : ctrlList)
	{
		srcCtrl->refresh();
	}
}

void MControl::runScript()
{
	if(scripts.size() <= 0)
	{
		return;
	}

	for (auto data : scripts)
	{
		if(data->checkRule(this) && data->checkCdts())
		{
			data->runActs(this->form);
		}
	}
}

void MControl::update(float delta)
{
	if(this->m_bClick)
	{
		m_bClick = false;
	}
	if(this->updateEvent)
	{
		this->updateEvent(this,delta);
	}
	
	lockTime+= delta;
	if(lockTime > 2.0f)
	{
		lockTime = 2.0f;
	}
	
	for (auto ctrl : ctrlList)
	{
		if(ctrl->isVisible())
		{
			ctrl->update(delta);
		}
	}
}

void MControl::paint()
{
	_paint();
	for (auto ctrl : ctrlList)
	{
		if(ctrl->isVisible())
		{
			ctrl->paint();
		}
	}
}

void MControl::_paint()
{
	if(!needUpdate)
	{
		return;
	}
	needUpdate = false;
	if(this->curSkin)
	{
		if(curDelayTime > 0)
		{
			curDelayTime--;
			needUpdate = true;
			return;
		}
		skinNode->removeAllChildren();
		SkinFrame *frame = curSkin->frames[curFraemIndex];
		for(int i = 0; i < frame->itemCount; i++)
		{
			SkinItem *item = frame->items[i];
			char name[128];
			memset(name,0,sizeof(name));
			sprintf(name,"ui_%d.png",item->imgId);
			Sprite *sprite = UIM->getSprite(name);
			skinNode->addChild(sprite);
			float x = item->x + this->size.width/2 + this->curSkinOffset.x;
			float y = -item->y + this->size.height/2 + this->curSkinOffset.y;
			Vec2 pp = Vec2(x,y);
			sprite->setPosition(pp);
			sprite->setRotation(-item->rotAngle);
			sprite->setOpacity(item->opacity *this->opacity/255);
			sprite->setColor(item->getColor());
			switch(item->getMirror())
			{
			case Flip_X:
				sprite->setFlippedX(true);
				sprite->setFlippedY(false);
				break;
			case Flip_Y:
				sprite->setFlippedX(false);
				sprite->setFlippedY(true);
				break;
			case Flip_XY:
				sprite->setFlippedX(true);
				sprite->setFlippedY(true);
				break;
			default:
				sprite->setFlippedX(false);
				sprite->setFlippedY(false);
				break;
			}
		}
		curDelayTime = curSkin->frames[curFraemIndex]->m_delay - 1;
		int nextIndex = curFraemIndex + 1;
		if(nextIndex >= curSkin->frameCount)
		{
			if(curSkin->bCyclePlay)
			{
				nextIndex = 0;
			}
			else
			{
				nextIndex = curSkin->frameCount - 1;
			}
			if(nextIndex != curFraemIndex)
			{
				needUpdate = true;
				curFraemIndex = nextIndex;

			}
		}
		else
		{
			curFraemIndex = nextIndex;
			needUpdate = true;
		}
	}
	else
	{
		skinNode->removeAllChildren();
	}

	if(this->paintEvent)
	{
		paintEvent(this);
	}
}

void MControl::releaseRes()
{
	if (skinNode)
	{
		skinNode->removeAllChildren();
	}
	if (paintNode)
	{
		paintNode->removeAllChildren();
	}
	this->registerPaintEvent(nullptr);
	this->registerUpdateLogicEvent(nullptr);

	for(auto ctrl : ctrlList)
	{
		ctrl->releaseRes();
	}
}

void MControl::visit(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	LayerColor::visit(renderer,transform,flags);
	if(checkFlag(F_Stencil))
	{
		glDisable(GL_STENCIL_TEST);
	}
}

void MControl::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	LayerColor::draw(renderer, transform, flags);
	if(checkFlag(F_Stencil))
	{
		glClearStencil(0);
		glClear(GL_STENCIL_BUFFER_BIT);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_NEVER, 0x0, 0x0);
		glStencilOp(GL_INCR, GL_INCR, GL_INCR);// 
		//glRectf(0,0,size.width,size.height);
		Vec2 filledVertices[] = { Vec2(0, 0), Vec2(size.width, 0), Vec2(size.width, size.height), Vec2(0, size.height) };
		DrawPrimitives::drawSolidPoly(filledVertices, 4, Color4F(0, 0, 0, 0));
		glStencilFunc(GL_NOTEQUAL, 0x0, 0x1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);// 
	}
	
}

void  MControl::setParentCtrl(MControl* parent)
{
	if(this->getParent() == parent || this->getParent() == form)
	{
		return;
	}
	MControl *parentCtrl = (MControl*)getParent();
	this->removeFromParent();
	parent->addChild(this);
	parentCtrl->ctrlList.eraseObject(this);
	parent->addControl(this);
}

void MControl::addControl(MControl * child)
{
	ctrlList.pushBack(child);
}

void MControl::setUserData(void *data)
{
	this->userData = data;
}
void* MControl::getUserData()
{
	return userData;
}

void MControl::setPosition(float x, float y)
{
	Node::setPosition(x,y);
	this->location = Vec2(x,y);
}

void MControl::setPosition(cocos2d::Vec2 p)
{
	Node::setPosition(p);
	this->location = p;
}

Vec2 MControl::getAbsPosition()
{
	if(this->getParent() == this->form)
	{
		return getPosition() - Vec2(anchor.x * size.width,anchor.y * size.height);
	}
	MControl *ctrl = (MControl*)this->getParent();
	return getPosition() - Vec2(anchor.x * size.width,anchor.y * size.height) + ctrl->getAbsPosition();
}

void MControl::setSize(short width, short height)
{
	LayerColor::setContentSize(Size(width,height));
	this->size = Size(width,height);
	skinNode->setContentSize(size);
	paintNode->setContentSize(size);
}

void MControl::setSize(cocos2d::Size size)
{
	LayerColor::setContentSize(size);
	this->size = size;
	skinNode->setContentSize(size);
	paintNode->setContentSize(size);
}

void  MControl::setControlOpacity(short opacity,bool bChild)
{
	if(this->opacity != opacity)
	{
		needUpdate = true;
	}
	this->opacity = opacity;
	if(bChild)
	{
		for (auto ctrl : ctrlList)
		{
			ctrl->setControlOpacity(opacity,bChild);
		}
	}
}
short  MControl::getControlOpacity()
{
	return opacity;
}

void MControl::setControlColor(cocos2d::Color4B color)
{
	if(this->color.r != color.r || this->color.g != color.g
		|| this->color.b != color.b
		|| this->color.a != color.a)
	{
		needUpdate = true;
	}
	this->color = color;
	this->setColor(Color3B(color.r,color.g,color.b));
	this->setOpacity(color.a);
}

void MControl::setControlScale(float fScaleX,float fScaleY)
{
	LayerColor::setScale(fScaleX,fScaleY);
	this->scale = Vec2(fScaleX,fScaleY);
}

void MControl::setControlScale(Vec2 scale)
{
	LayerColor::setScale(scale.x,scale.y);
	this->scale = scale;
}

Vec2 MControl::getControlScale()
{
	return this->scale;
}

void MControl::setRotation(float fRotation)
{
	LayerColor::setRotation(fRotation);
	this->rot = fRotation;
}

float MControl::getRotation()
{
	return this->rot;
}

void MControl::setFlag(short flag)
{
	ctrlFlag |= (short)flag;
}

bool MControl::checkFlag(short flag)
{
	return (ctrlFlag & (short)flag) != 0;
}

void MControl::clearFlag(short flag)
{
	ctrlFlag &= (short)(~flag);
}

void MControl::setSkin(UISkin* skin, cocos2d::Vec2 offset)
{
	if(skin || curSkin )
	{
		needUpdate = true;
	}
	curSkin = skin;
	curSkinOffset = offset;
	if(curSkin && curSkin->frameCount > 0)
	{
		curFraemIndex = 0;
		curDelayTime = 0;
	}
}

void MControl::setEnabled(bool enabled)
{
	for (auto control : ctrlList)
	{
		control->setEnabled(enabled);
	}
	this->m_bEnabled = enabled;
}

bool MControl::getEnabled()
{
	return this->m_bEnabled;
}

bool MControl::pressDownEvent(Touch *ptouch)
{
	if(!this->isVisible())
	{
		return false;
	}
	for (auto control : ctrlList)
	{
		if (control->isVisible() && control->pressDownEvent(ptouch))
		{
			return true;
		}
	}
	if(!this->getEnabled() || !this->checkFlag(F_AcceptEvent))
	{
		return false;
	}
	
	/*if(lockTime < ClickInterval && form->getTouchEventType() != Multi_Event)
	{
		return true;
	}*/
	lockTime = 0.0f;
	Vec2 pp = this->getParent()->convertToWorldSpace(this->getPosition());
	Vec2 p = ptouch->getLocation();
	Rect rect = Rect(pp.x - anchor.x * size.width,pp.y - anchor.y * size.height,this->size.width,size.height);
	if(rect.containsPoint(p))
	{
		if(!this->getEnabled())
		{
			form->showTipMessage(this->id);
			return false;
		}
		long long time = getCurrentTime();
		if(time - m_time <= 650)
		{
			if(this->DoubleClickEvent)
			{
				this->DoubleClickEvent(this,ptouch,nullptr);
			}
		}
		m_time = time;
		this->m_bPressed = true;
		this->touchId = ptouch->getID();
		if(this->touchBegan)
		{
			return this->touchBegan(this,ptouch,nullptr);
		}
		return true;
	}
	return false;
}

void MControl::moveEvent(Touch *ptouch)
{
	if(!m_bPressed)
	{
		return ;
	}
	if(ptouch->getID() != touchId)
	{
		return;
	}
	if(this->touchMove)
	{
		touchMove(this,ptouch,nullptr);
	}
}

void MControl::pressUpEvent(Touch *ptouch)
{
	if(!m_bPressed)
	{
		return ;
	}
	if(ptouch->getID() != touchId)
	{
		return;
	}
	Vec2 pp = this->getParent()->convertToWorldSpace(this->getPosition());
	Vec2 p = ptouch->getLocation();
	Rect rect = Rect(pp.x - anchor.x * size.width,pp.y - anchor.y * size.height,this->size.width,size.height);
	if(rect.containsPoint(p))
	{
		m_bClick = true;
		if(this->clickEvent)
		{
			clickEvent(this,ptouch,nullptr);
		}
	}
	if(this->touchEnd)
	{
		touchEnd(this,ptouch,nullptr);
	}
	m_bPressed = false;
}