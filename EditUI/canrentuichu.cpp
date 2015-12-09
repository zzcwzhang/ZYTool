#include"UI.h"
#include "GScene.h"
#include "GUILayer.h"
#include "GameManager.h"
void canrentuichu_register(Node* node)
{
UIForm *form = (UIForm*)node;
  form->getControl(canrentuichu_control2)->registerClickEvent(canrentuichu_control2_Click);
  form->getControl(canrentuichu_control3)->registerClickEvent(canrentuichu_control3_Click);
  form->getControl(canrentuichu_control4)->registerClickEvent(canrentuichu_control4_Click);
}
void canrentuichu_initialize(Node* node)
{
}
//control1
//control2
void canrentuichu_control2_Click(Node *node,Touch* ptouch, Event* event){}
//control3
void canrentuichu_control3_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->closeForm((short)Form_canrentuichu,true);
}
//control4
void canrentuichu_control4_Click(Node *node,Touch* ptouch, Event* event)
{
	if(GMI->isSingleMode())
	{
		auto form = UIM->getForm(Form_renwutankuang);
		auto ctrl = form->getControl(renwutankuang_control1);
		ctrl->setOpacity(125);
		UIM->closeForm((short)Form_buyuchang,true);
	}
	else
	{
		UIM->closeForm((short)Form_duorenbuyuchang,true);
	}
	UIM->closeForm((short)Form_canrentuichu,true);
	GScene->setState(GST_MENU);
}
