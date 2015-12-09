#include"UI.h"
void VIPtishitankuang_register(Node* node)
{
UIForm *form = (UIForm*)node;
  form->getControl(VIPtishitankuang_control3)->registerClickEvent(VIPtishitankuang_control3_Click);
  form->getControl(VIPtishitankuang_control4)->registerClickEvent(VIPtishitankuang_control4_Click);
  form->getControl(VIPtishitankuang_control6)->registerClickEvent(VIPtishitankuang_control6_Click);
}
void VIPtishitankuang_initialize(Node* node)
{
}
//control3
void VIPtishitankuang_control3_Click(Node *node,Touch* ptouch, Event* event){}
//control4
void VIPtishitankuang_control4_Click(Node *node,Touch* ptouch, Event* event){}
//control6
void VIPtishitankuang_control6_Click(Node *node,Touch* ptouch, Event* event){}
