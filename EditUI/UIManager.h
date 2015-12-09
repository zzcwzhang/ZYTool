#ifndef UIManager_H_
#define UIManager_H_
#include "cocos2d.h"
#include <string>
class UISkin;
class UIForm;
class MControl;
class GUILayer;
class UIManager
{
private:
	static UIManager* manager;
	short formCount;
	UIForm** forms;
	UIForm *curForm;
	cocos2d::Layer* guiLayer;
	cocos2d::Layer *uiLayer;
	cocos2d::Layer *uiPaintLayer;
	
	cocos2d::Vector<UISkin*> skinArray;

	//纹理字典
	//cocos2d::CCDictionary *textureDict;

	//系统变量
	short systemVarCount;
	short *systemVarType;
	short *systemVars;
public:
	static UIManager* getInstance();
	UIManager();
	~UIManager();
	UIForm *loadForm(short formId);
	UIForm *reloadForm(short formId);
	void loadFormRes(short formId);
	UIForm *showForm(short formId);
	UIForm *showForm(short formId, bool bInit);
	void closeForm(short formId, bool release);
	void closeForm(UIForm *form, bool release);

	void init();
	void loadSkin();

	UIForm* getForm(short formId);
	UIForm* getCurForm();

	void refreshForm();

	void updateLogic(float dt);
	void drawUI();

	cocos2d::Layer* getLayer(){return guiLayer;}
	cocos2d::Layer* getPaintLayer(){return uiPaintLayer;}
	//纹理
	void addTexture(std::string file,std::string plist);
	cocos2d::Sprite* getSprite(std::string str);
	void removeTexture(std::string file);
	//皮肤
	UISkin* getSkin(int skinId);
	void setSkin(MControl *ctrl,short index,const bool pressState = false);

	//系统变量
	short getSystemVarCount(){return systemVarCount;};
	short getSystemVar(int varIndex);
	void setSystemVar(int varIndex, short value);
	short getSystemVarType(int varIndex);
};
#define  UIM (UIManager::getInstance())
#endif