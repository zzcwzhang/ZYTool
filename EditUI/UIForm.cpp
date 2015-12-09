#include "UI.h"
UIForm::UIForm()
{
	curTrailer = nullptr;
	updateEvent = nullptr;
	m_bNeedClose = false;
	m_bNeedRelease = false;
	m_eventLock = false;
	m_eventType = Single_Event;
	m_bUpdate = false;
	bTipMessageLock = false;
}
UIForm::~UIForm()
{
	scriptList.clear();

	ctrlList.clear();

	trailerList.clear();
}

void UIForm::loadForm(DataStream * dis)
{
	short count = dis->readByte();
	//脚本
	for (int i = 0; i < count; i++)
	{
		UIScriptData* data = UIScriptData::create();
		data->loadData(dis);
		this->scriptList.pushBack(data);
	}
	//控件
	count = dis->readShort();
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
		ctrl->form = this;
		ctrl->type = type;
		addControl(ctrl);
		this->addChild(ctrl);
		ctrl->loadData(dis);
	}
	//trailer
	count = dis->readByte();
	for (int i = 0; i < count; i++)
	{
		UITrailer *trailer = UITrailer::create();
		trailer->setForm(this);
		trailer->loadData(dis);
		trailerList.pushBack(trailer);
	}
	if(count > 0)
	{
		setTrailer(getTrailer(0));
	}
	_paintNode = Node::create();
	this->addChild(_paintNode,10);
}

void UIForm::initForm()
{
	int count = getChildrenCount();
	for (int i = 0;i<count - 1;i++)
	{
		MControl *ctrl = (MControl*)getChildren().at(i);
		ctrl->initMControl();
	}
// 	for(auto obj : getChildren())
// 	{
// 		MControl *ctrl = (MControl*)obj;
// 		ctrl->initMControl();
// 	}
}

void UIForm::loadRes()
{
	
}

void UIForm::releaseRes()
{
	setUpdateEvent(nullptr);
	getPaintNode()->removeAllChildren();
	int count = this->getChildren().size();
	for (int i = 0; i < count - 1; i++)
	{
		MControl *ctrl = (MControl*)getChildren().at(i);
		ctrl->releaseRes();
	}
}

void UIForm::update(float delta)
{
	if(this->curTrailer)
	{
		curTrailer->updateLogic(delta);
	}

	int count = this->ctrlList.size();
	for (int i = 0; i < count; i++)
	{
		MControl *ctrl = (MControl*)ctrlList.at(i);
		if(ctrl->isVisible() && ctrl->getEnabled())
		{
			ctrl->runScript();
		}
	}

	count = this->getChildren().size();
	for (int i = 0; i < count - 1; i++)
	{
		MControl *ctrl = (MControl*)getChildren().at(i);
		if(ctrl->isVisible())
		{
			ctrl->update(delta);
		}
	}
	
	if(this->updateEvent)
	{
		this->updateEvent(this,delta);
	}

	if(!m_bUpdate)
	{
		m_bUpdate = true;
	}
}

void UIForm::paint()
{
	int count = this->getChildren().size();
	for (int i = 0; i < count - 1; i++)
	{
		MControl *ctrl = (MControl*)getChildren().at(i);
		if(ctrl->isVisible())
		{
			ctrl->paint();
		}
	}
}

void UIForm::setTrailer(UITrailer *trailer)
{
	curTrailer = trailer;
	if(trailer)
	{
		curTrailer->setCurTimeIndex(0);
		curTrailer->play();
	}
}

void UIForm::setTrailer(short trailerId)
{
	UITrailer *trailer = getTrailer(trailerId);
	setTrailer(trailer);
}

UITrailer* UIForm::getTrailer(short trailerId)
{
	if(trailerId < 0 || trailerId >= trailerList.size())
	{
		return NULL;
	}
	return (UITrailer*)trailerList.at(trailerId);
}

MControl *UIForm::getControl(short ctrlId)
{
	int count = ctrlList.size();
	for (int i = 0; i < count; i++)
	{
		MControl *ctrl = (MControl*)ctrlList.at(i);
		if(ctrl->id == ctrlId)
		{
			return ctrl;
		}
	}
	return NULL;
}

void UIForm::addControl(MControl *ctrl)
{
	ctrlList.pushBack(ctrl);
}

Node* UIForm::getPaintNode()
{
	return _paintNode;
}

UIScriptData *UIForm::getScriptData(short scriptId)
{
	if(scriptId >= scriptList.size() || scriptId < 0)
	{
		return NULL;
	}
	return (UIScriptData*)scriptList.at(scriptId);
}

void UIForm::setInitFunc(Initialize initfunc)
{
	this->initFunc = initfunc;
}
Initialize UIForm::getInitFunc()
{
	return this->initFunc;
}
void UIForm::setUpdateEvent(UpdateLogic pevent)
{
	this->updateEvent = pevent;
}
UpdateLogic UIForm::getUpdateEvent()
{
	return this->updateEvent;
}
void UIForm::setEnabled(bool enabled)
{
	int count = this->getChildren().size();
	for (int i = 0; i < count - 1; i++)
	{
		MControl *ctrl = (MControl*)getChildren().at(i);
		ctrl->setEnabled(enabled);
	}

// 	for(auto pnode : getChildren())
// 	{
// 		MControl *control = (MControl*)pnode;
// 		control->setEnabled(enabled);
// 	}
}

bool UIForm::getEnabled()
{
	return this->m_bEnabled;
}

void UIForm::setActive(bool flag)
{
	m_bActive = flag;
}

bool UIForm::isActive()
{
	return m_bActive;
}

void UIForm::showTipMessage(short ctrlId)
{
	return;
	/*
	if(formId == Form_ATK)
	{
		if(ctrlId == 50)
		{
			return;
		}
	}
	if(bTipMessageLock)
	{
		return;
	}
	bTipMessageLock = true;
	Node *paintNode = getPaintNode();
	CCLayerColor *layerColor = CCLayerColor::create(ccc4(0,0,0,128),S_WIDTH/4 + 40,30);
	layerColor->ignoreAnchorPointForPosition(false);
	layerColor->setAnchorPoint(Vec2(0.5f,0));
	layerColor->setPosition(Vec2(S_WIDTH/2,S_HEIGHT/2 + 20));
	paintNode->addChild(layerColor,1);

	char buf[22] = {-24,-81,-91,-27,-118,-97,-24,-125,-67,-26,-102,-126,-28,-72,-115,-27,-113,-81,-25,-108,-88,0};
	CCLabelBMFont *tff = CCLabelBMFont::create("","fonts/word.fnt",24.0f);
	tff->enableStroke(Vec2(1,1),ccBLUE);
	tff->setAnchorPoint(Vec2(0.5f,0));
	tff->setPosition(Vec2(S_WIDTH/2,S_HEIGHT/2 + 20));
	tff->setString(buf);
	paintNode->addChild(tff,2);


	CCSequence *seq = CCSequence::create(CCDelayTime::create(1.0f),CCFadeOut::create(0.5f),
		CCCallFuncN::create(this, callfuncN_selector(UIForm::tipMessageEnd)),NULL);

	CCSequence *seq1 = CCSequence::create(CCFadeIn::create(0.5f),CCDelayTime::create(0.5f),CCFadeOut::create(0.5f),
		CCCallFuncN::create(this, callfuncN_selector(UIForm::tipMessageEnd)),NULL);
	layerColor->runAction(seq);
	tff->runAction(seq1);
	*/
}

void UIForm::tipMessageEnd(Node *node)
{
	if(node)
	{
		node->removeFromParent();
	}
	bTipMessageLock = false;
}

void UIForm::refresh()
{
	for (auto ctrl : ctrlList)
	{
		ctrl->refresh();
	}
}

void UIForm::setTouchEventType(short eventType)
{
	this->m_eventType = eventType;
}
short UIForm::getTouchEventType()
{
	return m_eventType;
}
void UIForm::setEventLock(bool flag)
{
	/*if(m_eventType == Single_Event)
	{
		m_eventLock = flag;
	}
	else
	{
		m_eventLock = false;
	}*/
	m_eventLock = flag;
}
bool UIForm::isEventLock()
{
	return m_eventLock;
}

void UIForm::onEnter()
{
	Node::onEnter();
	registerTouchListenner();
}
void UIForm::onExit()
{
	Node::onExit();
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);  
}

void UIForm::visit(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	Node::visit(renderer,transform,flags);
	glDisable(GL_STENCIL_TEST);
}

void UIForm::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	Node::draw(renderer,transform,flags);

	Size size = Director::getInstance()->getWinSize();
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

void UIForm::registerTouchListenner()
{
	// 创建一个事件监听器类型为 OneByOne 的单点触摸
	auto listener1 = EventListenerTouchOneByOne::create();
	// 设置是否吞没事件，在 onTouchBegan 方法返回 true 时吞没
	listener1->setSwallowTouches(true);

	// 使用 lambda 实现 onTouchBegan 事件回调函数
	listener1->onTouchBegan = CC_CALLBACK_2(UIForm::touchBegan, this);
	listener1->onTouchMoved = CC_CALLBACK_2(UIForm::touchMoved, this);
	listener1->onTouchEnded = CC_CALLBACK_2(UIForm::touchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), this);
}

void UIForm::addChild(Node* child, int zOrder, int tag)
{

	Node::addChild(child,zOrder,tag);
}
void UIForm::addChild(Node *child)
{

	Node::addChild(child);
}
void UIForm::addChild(Node *child,int zOrder)
{

	Node::addChild(child,zOrder);
}

bool UIForm::touchBegan(Touch* ptouch, Event* event)
{
	if (this->m_eventType == NO_Event)
	{
		return false;
	}
	if (!this->m_bActive || !m_bUpdate)//!this->getEnabled() || 
	{
		return false;
	}
	if (this->isEventLock())
	{
		return false;
	}
	Vec2 p = ptouch->getLocationInView();
	int count = this->getChildren().size();
	for (int i = count - 2; i >= 0; i--)
	{
		MControl *ctrl = (MControl*)this->getChildren().at(i);
		if (ctrl->pressDownEvent(ptouch))
		{
			if (m_eventType == Single_Event)
			{
				this->setEventLock(true);
			}
			return true;
		}
	}
	return false;
}
void UIForm::touchMoved(Touch *pTouch, Event *pEvent)
{
	int count = ctrlList.size();
	for (int i = count - 1; i >= 0; i--)
	{
		MControl *ctrl = (MControl*)ctrlList.at(i);
		if (ctrl->m_bPressed)
		{
			ctrl->moveEvent(pTouch);
		}
	}
}
void UIForm::touchEnded(Touch *pTouch, Event *pEvent)
{
	int count = ctrlList.size();
	for (int i = count - 1; i >= 0; i--)
	{
		MControl *ctrl = (MControl*)ctrlList.at(i);
		if (ctrl->m_bPressed)
		{
			ctrl->pressUpEvent(pTouch);
		}
	}
	this->setEventLock(false);
}

void UIForm::setRegisterFunc(Register initfunc)
{
	this->registerFunc = initfunc;
}
Register UIForm::getRegisterFunc()
{
	return this->registerFunc;
}