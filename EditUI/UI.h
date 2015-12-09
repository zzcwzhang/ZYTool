#ifndef UI_H_
#define UI_H_
#include "cocos2d.h"
USING_NS_CC;

#define F_UIData	"UI/uidata.bin"
#define F_UISKIN	"UI/skin.bin"

enum ControlType
{
	Type_Button = 1,
	Type_Label,
	Type_TextBox,
	Type_Screen,
	Type_ListView,
	Type_ScrollView,
	Type_Shade,
	Type_Silder
};
#include "Tools.h"
#include "DataStream.h"
#include "UIConfig.h"
#include "UIEvent.h"

#include "UIScriptCDTh.h"
#include "UIScriptACT.h"
#include "UIScriptData.h"

#include "UITrailer.h"

//Æ¤·ô
#include "SkinItem.h"
#include "SkinFrame.h"
#include "UISkin.h"

#include "MControl.h"
#include "MLabel.h"
#include "MButton.h"
#include "MListView.h"
#include "UIForm.h"
#include "UIManager.h"
#include "UICallBack.h"
#include "SConfig.h"
#endif