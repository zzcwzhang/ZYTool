#include "UI.h"
#include "GUILayer.h"
UIManager* UIManager::manager = NULL;

UIManager* UIManager::getInstance()
{
	if(manager == NULL)
	{
		manager = new UIManager();
	}
	return manager;
}

UIManager::UIManager()
{
	guiLayer = Layer::create();
	guiLayer->retain();

	uiLayer = Layer::create();
	guiLayer->addChild(uiLayer,0);

	uiPaintLayer = Layer::create();
	guiLayer->addChild(uiPaintLayer,1);

	//skinArray = NULL;
	//纹理字典
	//textureDict = new CCDictionary();

	forms = NULL;
	curForm = NULL;
	systemVarType = NULL;
	systemVars = NULL;
}

UIManager::~UIManager()
{
	skinArray.clear();
	//CC_SAFE_RELEASE_NULL(textureDict);

	if(systemVars)
	{
		delete systemVars;
	}
	
	if(systemVarType)
	{
		delete systemVarType;
	}

	if(forms)
	{
		for (int i = 0; i < formCount;i++)
		{
			CC_SAFE_RELEASE(forms[i]);
		}
		delete forms;
	}

	guiLayer->removeFromParent();
	CC_SAFE_RELEASE_NULL(guiLayer);
}

void UIManager::init()
{
	DataStream *dis = getInputStream(F_UIData);
	//皮肤
	/*this->skinCount = dis->readShort();
	this->skins = new UISkin *[this->skinCount];
	memset(this->skins,0,sizeof(UISkin*) *this->skinCount);
	this->m_pSkinFlag = new short[this->skinCount];
	memset(this->m_pSkinFlag,0,sizeof(short) * this->skinCount);*/
	//脚本
	/*this->m_scriptDatasCount = dis->readShort();
	this->m_pScriptDatas = new UIScriptData*[m_scriptDatasCount];
	memset(this->m_pScriptDatas,0,sizeof(UIScriptData*) *this->m_scriptDatasCount);
	this->m_pScriptFlag = new short[this->m_scriptDatasCount];
	memset(m_pScriptFlag,0,sizeof(short) * this->m_scriptDatasCount);*/
	//form
	this->formCount = dis->readByte();
	this->forms = new UIForm*[this->formCount];
	memset(this->forms,0,sizeof(UIForm*) * this->formCount);
	//系统变量
	this->systemVarCount = dis->readShort();
	this->systemVars = new short[this->systemVarCount];
	memset(this->systemVars,0,sizeof(short) * this->systemVarCount);
	this->systemVarType = new short[this->systemVarCount];
	for(int i = 0; i < this->systemVarCount; i++)
	{
		this->systemVarType[i] = dis->readByte();
	}
	dis->close();

	//加载皮肤
	loadSkin();
}

void UIManager::loadSkin()
{
	DataStream *dis = getInputStream(F_UISKIN);
	short count  = dis->readShort();
	for (int i = 0; i < count; i++)
	{
		UISkin *skin = UISkin::create();
		skin->m_id = i;
		skin->loadSkin(dis);
		skinArray.pushBack(skin);
	}
	dis->close();
}

void UIManager::loadFormRes(short formId)
{
	UIForm *form = this->forms[formId];
	if(!form)
	{
		form = loadForm(formId);
	}
	for (auto ctrl : form->ctrlList)
	{
		if(ctrl->type == Type_Button)
		{
			MButton *btn = (MButton*)ctrl;
			for (int j = 0; j < btn->skinIds.size();j++)
			{
				UISkin *skin = getSkin(btn->skinIds[j]);
				skin->loadRes();
			}
			for (int j = 0; j < btn->pressSkinIds.size();j++)
			{
				UISkin *skin = getSkin(btn->pressSkinIds[j]);
				skin->loadRes();
			}
		}
		else
		{
			MLabel *label = (MLabel*)ctrl;
			for (int j = 0; j < label->skinIds.size();j++)
			{
				UISkin *skin = getSkin(label->skinIds[j]);
				skin->loadRes();
			}
		}
	}
}

UIForm* UIManager::loadForm(short formId)
{
	if(!this->forms[formId])
	{
		UIForm *form = new UIForm;
		form->formId = formId;
		char name[64];
		memset(name,0,sizeof(name));
		sprintf(name,"UI/%d.f",formId);
		DataStream *dis = getInputStream(name);
		form->loadForm(dis);
		form->initForm();
		dis->close();

		form->setActive(false);
		this->forms[formId] = form;
		initialize(formId);
		form->setTag(formId);

		Size size = Director::getInstance()->getWinSize();
		form->setContentSize(size);
		form->setAnchorPoint(Vec2(0.5f,0.5f));
		form->setPosition(Vec2(size.width/2,size.height/2));
	}
	return this->forms[formId];
}

UIForm *UIManager::reloadForm(short formId)
{
	if(this->forms[formId])
	{
		this->uiLayer->removeChild(this->forms[formId]);
		CC_SAFE_RELEASE_NULL(this->forms[formId]);
		this->forms[formId] = nullptr;
	}
	return loadForm(formId);
}

UIForm* UIManager::showForm(short formId)
{
	return showForm(formId,true);
}

UIForm *UIManager::showForm(short formId, bool bInit)
{
	Size size = Director::getInstance()->getWinSize();
	if(!this->forms[formId])
	{
		UIForm *form = loadForm(formId);
		this->uiLayer->addChild(form);
		bInit = true;
	}
	else
	{
		this->uiLayer->removeChild(this->forms[formId]);
		this->forms[formId]->m_bNeedClose = false;
		this->uiLayer->addChild(this->forms[formId]);
	}

	if(bInit)
	{
		(this->forms[formId]->getInitFunc())(this->forms[formId]);
	}

	if(this->forms[formId]->getTouchEventType() != NO_Event)
	{
		if(this->curForm)
		{
			this->curForm->setEnabled(false);
		}

		this->curForm = this->forms[formId];
		this->curForm->setEnabled(true);
		this->curForm->setActive(true);
		this->curForm->refresh();
		this->curForm->m_bUpdate = false;
		//this->curForm->setEventLock(false);
		this->curForm->m_bNeedClose = false;
		this->curForm->m_bNeedRelease = false;

		return this->curForm;
	}
	else
	{
		return this->forms[formId];
	}
}

void UIManager::closeForm(short formId, bool release)
{
	if(formId >= this->formCount || formId < 0)
	{
		return;
	}

	closeForm(this->forms[formId],release);
	/*if(release)
	{
	this->forms[formId] = NULL;
	}*/
}
void UIManager::closeForm(UIForm *form, bool release)
{
	if(form == nullptr)
	{
		return;
	}

	form->m_bNeedClose = true;
	form->m_bNeedRelease = release;
	if(release)
	{
		form->releaseRes();
	}
	//form->setEventLock(false);
	form->setEnabled(false);
}

UIForm *UIManager::getForm(short formId)
{
	if(formId >= this->formCount || formId < 0)
	{
		return nullptr;
	}
	return this->forms[formId];
}

UIForm *UIManager::getCurForm()
{
	if (this->curForm != nullptr)
	{
		return this->curForm;
	}
	return nullptr;
}

void UIManager::refreshForm()
{
	/*UIForm *form = getForm(Form_choujiang);
	if(form)
	{
		form->getControl(choujiang_control30)->refresh();
		form->getControl(choujiang_control31)->refresh();
	}


	form = getForm(Form_renwuzhuangbei);
	if(form)
	{
		form->refresh();
	}


	form = getForm(Form_zhuangbeichankan);
	if(form)
	{
		form->refresh();
	}


	form = getForm(Form_Trophy);
	if(form)
	{
		form->getControl(Trophy_control16)->refresh();
		form->getControl(Trophy_control17)->refresh();
	}


	form = getForm(Form_Evolution);
	if(form)
	{
		form->getControl(Evolution_control9)->refresh();
		form->getControl(Evolution_control10)->refresh();
	}

	form = getForm(Form_shangcheng);
	if(form)
	{
		form->refresh();
	}


	form = getForm(Form_NEWZHUUI);
	if(form)
	{
		form->refresh();
	}


	form = getForm(Form_BUFF);
	if (form)
	{
		form->getControl(BUFF_control13)->refresh();
		form->getControl(BUFF_control14)->refresh();
	}


	form = getForm(Form_newmap);
	if (form)
	{
		form->refresh();
	}*/
}

UISkin* UIManager::getSkin(int skinId)
{
	if(skinId < 0 || skinId >= skinArray.size())
	{
		return nullptr;
	}
	return (UISkin*)skinArray.at(skinId);
}

void UIManager::setSkin(MControl *ctrl,short index,bool pressState)
{
	if(pressState)
	{
		MButton *btn = (MButton*)ctrl;
		UISkin *skin = nullptr;
		if(index >= 0)
		{
			skin = getSkin(btn->pressSkinIds[index]);
		}
		btn->pressSkin = skin;
	}
	else
	{
		MLabel *label = (MLabel*)ctrl;
		UISkin *skin = nullptr;
		if(index >= 0)
		{
			skin = getSkin(label->skinIds[index]);
			label->setSkin(skin,label->getSkinOffset(skin));
			label->skin = skin;
		}
		else
		{
			label->skin = NULL;
			label->curSkin = NULL;
			label->refresh();
		}
	}
	
}

short UIManager::getSystemVar(int varIndex)
{
	if(varIndex < 0 || varIndex >= systemVarCount)
	{
		return -1;
	}
	return systemVars[varIndex];
}
void UIManager::setSystemVar(int varIndex, short value)
{
	if(varIndex < 0 || varIndex >= systemVarCount)
	{
		return;
	}
	systemVars[varIndex] = value;
}
short UIManager::getSystemVarType(int varIndex)
{
	if(varIndex < 0 || varIndex >= systemVarCount)
	{
		return -1;
	}
	return systemVarType[varIndex];
}

//纹理
void UIManager::addTexture(std::string file,std::string plist)
{
	/*CCTexture2D *texture = dynamic_cast<CCTexture2D*>(textureDict->objectForKey(file));
	if(!texture)
	{
		CCImage *img = new CCImage();
		img->initWithImageFile(file.c_str(),CCImage::kFmtPng);
		texture = new CCTexture2D;
		texture->initWithImage(img);
		CC_SAFE_RELEASE_NULL(img);
		textureDict->setObject(texture,file);
		texture->autorelease();
	}
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist.c_str(),texture);*/
}
Sprite* UIManager::getSprite(std::string str)
{
	//CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.c_str());
	//CCSprite *sprite = CCSprite::createWithSpriteFrame(frame);
	__String *txt = __String::createWithFormat("UI/Img/%s", str.c_str());
	return Sprite::create(txt->getCString());
}

void UIManager::removeTexture(std::string file)
{
	//textureDict->removeObjectForKey(file);
}

void UIManager::drawUI()
{
	if(!this->uiLayer)
	{
		return;
	}
	Vector<Node*> children = this->uiLayer->getChildren();
	for(auto node : children)
	{
		UIForm *form = (UIForm*)node;
		form->paint();
	}
}

void UIManager::updateLogic(float dt)
{
	if(!this->uiLayer)
	{
		return;
	}
	Vector<Node*> children = this->uiLayer->getChildren();
	int count = children.size();
	for (auto node : children)
	{
		UIForm *form = (UIForm*)node;
		form->update(dt);
	}
	bool flag = false;
	for(int i = count - 1; i >= 0; i--)
	{
		UIForm *form = (UIForm*)children.at(i);
		if(form->m_bNeedClose)
		{
			form->m_bNeedClose = false;
			form->setActive(false);
			form->setEventLock(false);
			this->uiLayer->removeChild(form);
			if(form->getTouchEventType() != NO_Event)
			{
				flag = true;
			}
		}
	}
	if(flag)
	{
		count = this->uiLayer->getChildrenCount();
		if(count > 0)
		{
			int index = count - 1;
			while(true && index >= 0)
			{
				UIForm *nextForm = (UIForm*)this->uiLayer->getChildren().at(index);
				if(nextForm->m_eventType != NO_Event)
				{
					nextForm->setEnabled(true);
					nextForm->m_bUpdate = false;
					this->curForm = nextForm;
					return;
				}
				else
				{
					index--;
				}
			}

			if(index < 0)
			{
				this->curForm = (UIForm*)this->uiLayer->getChildren().at(count - 1);
			}
		}
		else
		{
			this->curForm = NULL;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
