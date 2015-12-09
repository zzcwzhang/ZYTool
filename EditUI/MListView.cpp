#include "UI.h"
MListView::MListView()
{
	curItem = nullptr;
	preItem = nullptr;
	itemSelectChanged = nullptr;
	itemCount = 0;
	inertiaSpeed = 0.0f;
	acceleration = 0.0f;
	isDragging = false;
	isCorrect = false;
}
MListView::~MListView()
{
	items.clear();
}

void MListView::paint()
{
	for(auto ctrl : items)
	{
		if(ctrl->isVisible())
		{
			ctrl->paint();
		}
	}
}

void MListView::update(float delta)
{
	if(this->m_bClick)
	{
		m_bClick = false;
	}

	if(!isDragging)
	{
		updateInertia(delta);
	}
	correctItems(delta);

	if(this->updateEvent)
	{
		this->updateEvent(this,delta);
	}
	//paint();

	for (auto ctrl : items)
	{
		if(ctrl->isVisible())
		{
			ctrl->update(delta);
		}
	}
}

void MListView::beforeDraw()
{
    //ScrollView don't support drawing in 3D space
    _beforeDrawCommand.init(_globalZOrder);
    _beforeDrawCommand.func = CC_CALLBACK_0(MListView::onBeforeDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_beforeDrawCommand);
}

/**
 * clip this view so that outside of the visible bounds can be hidden.
 */
void MListView::onBeforeDraw()
{
    
	auto glview = Director::getInstance()->getOpenGLView();
	glEnable(GL_SCISSOR_TEST);
	glview->setScissorInPoints(getAbsPosition().x, getAbsPosition().y, getSize().width, getSize().height);
}

void MListView::afterDraw()
{
    _afterDrawCommand.init(_globalZOrder);
    _afterDrawCommand.func = CC_CALLBACK_0(MListView::onAfterDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_afterDrawCommand);
}

/**
 * retract what's done in beforeDraw so that there's no side effect to
 * other nodes.
 */
void MListView::onAfterDraw()
{
    glDisable(GL_SCISSOR_TEST);
}

void MListView::visit(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	this->beforeDraw();

	LayerColor::visit(renderer,transform,flags);

	this->afterDraw();
	//glDisable(GL_STENCIL_TEST);

	//glScissor(getAbsPosition().x,getAbsPosition().y,getSize().width,getSize().height);
}

void MListView::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	MControl::draw(renderer, transform, flags);
	
	//glScissor(getAbsPosition().x,getAbsPosition().y,getSize().width,getSize().height);

 	//glClearStencil(0);
 	//glClear(GL_STENCIL_BUFFER_BIT);
 	//glEnable(GL_STENCIL_TEST);
 	//glStencilFunc(GL_NEVER, 0x0, 0x0);
 	//glStencilOp(GL_INCR, GL_INCR, GL_INCR);// 
 	////glRectf(0,0,getSize().width,getSize().height);
 	//Vec2 filledVertices[] = { Vec2(0, 0), Vec2(getSize().width, 0), Vec2(getSize().width, getSize().height), Vec2(0, getSize().height) };
 	//DrawPrimitives::drawSolidPoly(filledVertices, 4, Color4F(0, 0, 0, 0));
 
 	//glStencilFunc(GL_NOTEQUAL, 0x0, 0x1);
 	//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);// 
	
}

void MListView::loadData(DataStream *dis)
{
	MLabel::loadData(dis);
	itemCtrlId = dis->readShort();
	direction = dis->readByte();
	soundName = dis->readString();
}
void MListView::initMControl()
{
	MControl::initMControl();
}

void MListView::refresh()
{
	MControl::refresh();
	for (auto ctrl : items)
	{
		ctrl->refresh();
	}
}

void MListView::releaseRes()
{
	if (skinNode)
	{
		skinNode->removeAllChildren();
	}
	if (paintNode)
	{
		paintNode->removeAllChildren();
	}
	
	MControl *itemLayout = form->getControl(itemCtrlId);
	itemLayout->releaseRes();
	for (auto ctrl : items)
	{
		ctrl->releaseRes();
	}
	clearItems();
	curItem = NULL;
	preItem = NULL;
}

void MListView::removeItem(int index)
{
	removeItem(getItem(index));
}
void MListView::removeItem(MControl *item)
{
	if(!item)
	{
		return;
	}
	item->m_bNeedRemove = true;
}

void MListView::addItem(MControl *ctrl)
{
	items.pushBack(ctrl);
	this->itemCount += 1;
}

void MListView::insertItem(MControl *item, int index)
{
	items.insert(index, item);
	this->itemCount += 1;
}

MControl *MListView::getItem(int index)
{
	if(index >= itemCount || index < 0)
	{
		return 0;
	}
	return (MControl*)items.at(index);
}

short MListView::getItemIndexof(MControl *item)
{
	if(item == NULL)
	{
		return -1;
	}
	return items.getIndex(item);
}

void MListView::clearItems()
{

	for (auto _item : items)
	{
		(*_item).removeFromParent();
	}

	items.clear();
	this->itemCount = 0;
}

void MListView::addItemCount(short num)
{
	int count = getItemCount();
	MControl *itemLayout = form->getControl(itemCtrlId);
	MControl* endItem = (MControl*)items.at(count - 1);
	int x = endItem->getPositionX();
	int y = endItem->getPositionY();
	for(int i = 0; i < num; i++)
	{
		MControl *ctrl = NULL;
		switch(itemLayout->type)
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
		ctrl->copy(itemLayout);
		ctrl->setFlag(F_Visible);
		this->addChild(ctrl);
		this->addItem(ctrl);
		if(direction == 0)
		{
			ctrl->setPosition(x + itemLayout->getSize().width * (i + 1),itemLayout->getPosition().y );
		}
		else
		{
			ctrl->setPosition(itemLayout->getPosition().x,y  - itemLayout->getSize().height * (i+ 1));
		}
		ctrl->initMControl();
	}
}

void MListView::setItemCount(short count)
{
	MControl *itemLayout = form->getControl(itemCtrlId);
	for(int i = 0; i < count; i++)
	{
		MControl *ctrl = NULL;
		switch(itemLayout->type)
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
		ctrl->copy(itemLayout);
		ctrl->setFlag(F_Visible);
		this->addChild(ctrl);
		this->addItem(ctrl);
		if(direction == 0)
		{
			ctrl->setPosition(itemLayout->getPosition().x + itemLayout->getSize().width * i,itemLayout->getPosition().y );
		}
		else
		{
			ctrl->setPosition(itemLayout->getPosition().x,itemLayout->getPosition().y  - itemLayout->getSize().height * i);
		}
		ctrl->initMControl();
	}

	updateItemsPos(0,0);
}

void MListView::updateItemsPos(float dx, float dy)
{
	Size size = getSize();
	int x = this->getPosition().x - this->anchor.x * this->getSize().width;
	int y = this->getPosition().y - this->anchor.y * this->getSize().height;
	Rect rect = Rect( - 10,- 10,this->getSize().width + 20,this->getSize().height + 20);
	if (items.size() > 0)
	{
		int count = items.size();
		MControl *itemLayout = form->getControl(itemCtrlId);
		MControl *firstItem = (MControl*)items.at(0);
		MControl *endItem = (MControl*)items.at(count - 1);
		if(direction == 0)
		{
			int minItemCount = size.width/itemLayout->getSize().width;
			if(count > minItemCount)
			{
				if(firstItem->getPosition().x + dx > size.width/2)
				{
					dx = size.width/2 - firstItem->getPosition().x ;
				}
				else if(endItem->getPosition().x + dx < size.width/2)
				{
					dx = size.width/2 - endItem->getPosition().x ;
				}
			}
			else
			{
				if(firstItem->getPosition().x + dx > size.width/2)
				{
					dx = size.width/2 - firstItem->getPosition().x ;
				}
				else if(firstItem->getPosition().x + dx < -firstItem->getSize().width/2)
				{
					dx = -firstItem->getSize().width/2 - firstItem->getPosition().x ;
				}
			}
		}
		else
		{
			int minItemCount = size.height/itemLayout->getSize().height;
			if(count > minItemCount)
			{
				if(firstItem->getPosition().y + dy < size.height/4)
				{
					dy = size.height/4 - firstItem->getPosition().y ;
				}
				else if(endItem->getPosition().y + dy > size.height/2)
				{
					dy = size.height/2 - endItem->getPosition().y ;
				}
			}
			else
			{
				if(firstItem->getPosition().y + dy < size.height/2)
				{
					dy = size.height/2 - firstItem->getPosition().y ;
				}
				else if(firstItem->getPosition().y + dy > size.height - firstItem->getSize().height/2)
				{
					dy = size.height - firstItem->getSize().height/2 - firstItem->getPosition().y ;
				}
			}
		}

		for(auto item : items)
		{
			if(this->direction == 0)
			{
				item->setPosition(item->getPosition().x + dx,item->getPosition().y);
			}
			else
			{
				item->setPosition(item->getPosition().x,item->getPosition().y +dy);
			}

			int x = item->getPosition().x - item->anchor.x * item->getSize().width;
			int y = item->getPosition().y - item->anchor.y * item->getSize().height;
			Rect itemRect = Rect(x,y,item->getSize().width,item->getSize().height);

			if(rect.intersectsRect(itemRect))
			{
				item->setVisible(true);
			}
			else
			{
				item->setVisible(false);
			}
		}
	}
}

void MListView::setInertiaSpeed(float speed,float acc)
{
	inertiaSpeed = speed;
	acceleration = acc;
}

void MListView::setSelectIndex(int index,bool bsmooth)
{
	int curIndex = 0;
	MControl *item = getItem(index);
	bool flag = false;
	if(this->direction == 0)
	{
		if(item->getPositionX() < -20.0f)
		{
			flag = true;
		}
		else if(item->getPositionX() + item->getSize().width > getSize().width)
		{
			flag = true;
		}
	}
	else
	{
		if(item->getPositionY() < -20.0f)
		{
			flag = true;
		}
		else if(item->getPositionX() + item->getSize().height > getSize().height)
		{
			flag = true;
		}
	}
	if(!flag)
	{
		return;
	}
	int firstIndex = -1,endIndex = -1;
	for(auto _ctrl : items)
	{
		if(this->direction == 0)
		{
			if(_ctrl->getPositionX() > 0 && firstIndex == -1)
			{
				firstIndex = items.getIndex(_ctrl);
			}

			if(_ctrl->getPositionX() > getSize().width && endIndex == -1)
			{
				endIndex = items.getIndex(_ctrl) - 1;
			}
		}
		else
		{
			if(_ctrl->getPositionY()  + _ctrl->getSize().height < getSize().height && firstIndex == -1)
			{
				firstIndex = items.getIndex(_ctrl);
			}

			if(_ctrl->getPositionY() < 0 && endIndex == -1)
			{
				endIndex = items.getIndex(_ctrl) - 1;
			}
		}
	}
	if(endIndex == -1)
	{
		endIndex = items.size() - 1;
	}
	MControl *itemLayout = form->getControl(itemCtrlId);
	Size size = itemLayout->getSize();
	int offsetIndex = (endIndex + firstIndex)/2 - index;
	float offset = 0;
	if(this->direction == 0)
	{
		offset = offsetIndex * size.width;
		if(item->getPositionX() + offset > index *size.width)
		{
			offset =  index *size.width - item->getPositionX();
		}
		if(!bsmooth)
		{
			updateItemsPos(offset,0);
		}
	}
	else
	{
		offset = offsetIndex * size.height;
		//
		if(!bsmooth)
		{
			updateItemsPos(0,-offset);
		}
	}
	if(bsmooth)
	{
		inertiaSpeed = -offset/20;
		acceleration = offset/800;
	}
	
}

void MListView::correctItems(float dt)
{
	int count = items.size();
	for (int i = count - 1; i >= 0; i--)
	{
		auto item = items.at(i);
		if(item->m_bNeedRemove)
		{
			this->itemCount -= 1;
			items.eraseObject(item);
			item->removeFromParent();
			isCorrect = true;
		}
	}
	if(!isCorrect)
	{
		return;
	}
	MControl *itemLayout = form->getControl(itemCtrlId);
	Size itemSize =itemLayout->getSize();
	MControl *pre = nullptr,*cur = nullptr;
	bool flag = false;
	for(auto item : items)
	{
		if(pre == nullptr)
		{
			pre = item;
			continue;
		}
		cur = item;
		Vec2 v2= cur->getPosition() - pre->getPosition();
		if(direction == 0)
		{//水平
			float dx = abs(v2.x) - itemSize.width;
			if(dx > 0.0f)
			{
				flag = true;
				if(dx > 15)
				{
					cur->setPositionX(cur->getPositionX() - 15);
				}
				else
				{
					cur->setPositionX(cur->getPositionX() - dx);
				}
			}
		}
		else
		{
			float dy = abs(v2.y) - itemSize.height;
			if(dy > 0.0f)
			{
				flag = true;
				if(dy > 15)
				{
					cur->setPositionY(cur->getPositionY() + 15);
				}
				else
				{
					cur->setPositionY(cur->getPositionY() + dy);
				}
			}
		}
		pre = cur;
	}

	if(!flag)
	{
		isCorrect = false;
	}
}

void MListView::updateInertia(float dt)
{
	if (checkItemPostion(dt))
	{
		inertiaSpeed = 0.0f;
	}
	if(inertiaSpeed == 0.0f)
	{
		return;
	}
	if(this->direction == 0)
	{
		float sx = inertiaSpeed + (acceleration)/2;
		updateItemsPos(sx,0);
		inertiaSpeed += acceleration;
	}
	else
	{
		float sy = inertiaSpeed + (acceleration)/2;
		updateItemsPos(0,sy);
		inertiaSpeed += acceleration ;
	}
	if(inertiaSpeed * acceleration >= 0)
	{//惯性与加速度反向
		inertiaSpeed = 0.0f;
	}
}
bool MListView::checkItemPostion(float dt)
{
	Size size = getSize();
	if (items.size() > 0)
	{
		MControl *itemLayout = form->getControl(itemCtrlId);
		int count = items.size();
		MControl *firstItem = (MControl*)items.at(0);
		MControl *endItem = (MControl*)items.at(count - 1);
		if(direction == 0)
		{
			int minItemCount = size.width/itemLayout->getSize().width;
			if(count > minItemCount)
			{
				if(firstItem->getPosition().x > itemLayout->getPosition().x)
				{
					float ssx = itemLayout->getPosition().x - firstItem->getPosition().x;
					float dy = 0;
					float dx;
					if(abs(ssx) > 15)
					{
						dx = ssx/2 > 0 ? 15 : -15;
					}
					else
					{
						dx = ssx;
					}
					updateItemsPos(dx,dy);
					return true;
				}
				else if(endItem->getPosition().x + endItem->getSize().width < size.width)
				{
					float dy = 0;
					float ssx = size.width - (endItem->getPosition().x + endItem->getSize().width);
					float dx;
					if(abs(ssx) > 15)
					{
						dx = ssx/2 > 0 ? 15 : -15;
					}
					else
					{
						dx = ssx;
					}
					updateItemsPos(dx,dy);
					return true;
				}
			}
			else
			{
				if(firstItem->getPosition().x > itemLayout->getPosition().x)
				{
					float ssx = itemLayout->getPosition().x - firstItem->getPosition().x;
					float dy = 0;
					float dx;
					if(abs(ssx) > 15)
					{
						dx = ssx/2 > 0 ? 15 : -15;
					}
					else
					{
						dx = ssx;
					}
					updateItemsPos(dx,dy);
					return true;
				}
				else if(firstItem->getPosition().x < 0)
				{
					float dy = 0;
					float ssx = -firstItem->getPosition().x;
					float dx;
					if(abs(ssx) > 15)
					{
						dx = ssx/2 > 0 ? 15 : -15;
					}
					else
					{
						dx = ssx;
					}
					updateItemsPos(dx,dy);
					return true;
				}
			}
		}
		else
		{
			int minItemCount = size.height/itemLayout->getSize().height;
			if(count > minItemCount)
			{
				if(firstItem->getPositionY() < itemLayout->getPosition().y)
				{
					float dx = 0;
					float ssy = itemLayout->getPosition().y - firstItem->getPosition().y;
					float dy;
					if(abs(ssy) > 15)
					{
						dy = ssy/2 > 0 ? 15 : -15;
					}
					else
					{
						dy = ssy;
					}
					updateItemsPos(dx,dy);
					return true;
				}
				else if(endItem->getPosition().y > 0)
				{
					float dx = 0;
					float dy = - endItem->getPosition().y;
					if(endItem->getPosition().y > 15)
					{
						dy = -endItem->getPosition().y/2;
					}
					else
					{
						dy = - endItem->getPosition().y;
					}
					updateItemsPos(dx,dy);
					return true;
				}
			}
			else
			{
				if(firstItem->getPosition().y < itemLayout->getPosition().y)
				{
					float dx = 0;
					float ssy = itemLayout->getPosition().y - firstItem->getPosition().y;
					float dy;
					if(abs(ssy) > 15)
					{
						dy = ssy/2 > 0 ? 15 : -15;
					}
					else
					{
						dy = ssy;
					}
					updateItemsPos(dx,dy);
					return true;
				}
				else if(firstItem->getPosition().y > itemLayout->getPosition().y)
				{
					float dx = 0;
					float ssy = itemLayout->getPosition().y - firstItem->getPosition().y;
					float dy;
					if(abs(ssy) > 15)
					{
						dy = -(ssy/2 > 0 ? 15 : -15);
					}
					else
					{
						dy = -ssy;
					}
					updateItemsPos(dx,dy);
					return true;
				}
			}
		}
	}
	return false;
}


bool MListView::pressDownEvent(cocos2d::Touch *ptouch)
{
	Size size = getSize();
	if(!this->getEnabled() || !this->isVisible())
	{
		return false;
	}
	int count = ctrlList.size();
	for (int i = count - 1; i >= 0; i--)
	{
		MControl *ctrl = (MControl*)ctrlList.at(i);
		if (ctrl->isVisible() && ctrl->pressDownEvent(ptouch))
		{
			return true;
		}
	}
	if(!this->checkFlag(F_AcceptEvent))
	{
		return false;
	}
	Vec2 pp = this->getParent()->convertToWorldSpace(this->getPosition());
	Vec2 p = ptouch->getLocation();
	Rect rect = Rect(pp.x - anchor.x * size.width,pp.y - anchor.y * size.height,size.width,size.height);
	if(rect.containsPoint(p))
	{
		if(!this->getEnabled())
		{
			return false;
		}
		startPoint = ptouch->getLocation();
		long long time = getCurrentTime();
		if(time - m_time <= 0)
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
			this->touchBegan(this,ptouch,nullptr);
		}
		//子项
		if(items.size()>0)
		{
			int count = items.size();
			for (int i = count - 1; i >= 0; i--)
			{
				MControl *ctrl = (MControl*)items.at(i);
				if(ctrl->pressDownEvent(ptouch))
				{
					this->preItem = curItem;
					this->curItem = ctrl;
					ctrl->m_bPressed = true;
					this->touchId = ptouch->getID();
					if(this->itemSelectChanged)
					{
						this->itemSelectChanged(ctrl,preItem,ptouch);
					}
					return true;
				}
			}
		}
		return true;
	}
	return false;
}
void MListView::moveEvent(cocos2d::Touch *ptouch)
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
	float dx = ptouch->getLocation().x - startPoint.x;
	float dy = ptouch->getLocation().y - startPoint.y;
	startPoint = ptouch->getLocation();
	if(this->direction == 0)
	{
		inertiaSpeed = dx;
		acceleration = inertiaSpeed > 0 ? -0.1f : 0.1f;
	}
	else
	{
		inertiaSpeed = dy;
		acceleration = inertiaSpeed > 0 ? -0.1f : 0.1f;
	}
	isDragging = true;
	updateItemsPos(dx,dy);
}
void MListView::pressUpEvent(cocos2d::Touch *ptouch)
{
	if(!m_bPressed)
	{
		return ;
	}
	if(ptouch->getID() != touchId)
	{
		return;
	}
	isDragging = false;
	m_bPressed = false;
	m_bClick = true;

	float dd = inertiaSpeed > 0 ? inertiaSpeed : -inertiaSpeed;
	bool flag = false;
	if(dd >= 2.0f)
	{
		flag = true;
	}

	//子项
	if(items.size()>0)
	{
		int count = items.size();
		for (int i = count - 1; i >= 0; i--)
		{
			MControl *item = (MControl*)items.at(i);
			if(item->m_bPressed)
			{
				Vec2 pp = item->getParent()->convertToWorldSpace(item->getPosition());
				Vec2 p = ptouch->getLocation();
				Rect rect = Rect(pp.x - item->anchor.x * item->getSize().width,pp.y - item->anchor.y * item->getSize().height,
					item->getSize().width,item->getSize().height);
				if(rect.containsPoint(p))
				{
					int ctrlCount = item->ctrlList.size();
					for (int j = 0; j < ctrlCount; j++)
					{
						MControl *ctrl = (MControl*)item->ctrlList.at(j);
						if(ctrl->m_bPressed)
						{
							ctrl->pressUpEvent(ptouch);
						}
					}
				}
				else
				{
					this->curItem = this->preItem;
				}
				if(!flag)
				{
					item->pressUpEvent(ptouch);
				}
				else
				{
					this->curItem = this->preItem;
				}
			}
			item->m_bPressed = false;
		}
	}
}