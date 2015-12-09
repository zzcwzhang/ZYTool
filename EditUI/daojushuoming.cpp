#include"UI.h"
void daojushuoming_register(Node* node)
{
UIForm *form = (UIForm*)node;
  form->getControl(daojushuoming_control3)->registerClickEvent(daojushuoming_control3_Click);
  form->getControl(daojushuoming_control4)->registerClickEvent(daojushuoming_control4_Click);
  form->getControl(daojushuoming_control5)->registerClickEvent(daojushuoming_control5_Click);
  form->getControl(daojushuoming_control12)->registerClickEvent(daojushuoming_control12_Click);
}
void daojushuoming_initialize(Node* node)
{
}
//control3
void daojushuoming_control3_Click(Node *node,Touch* ptouch, Event* event){}
//control4
void daojushuoming_control4_Click(Node *node,Touch* ptouch, Event* event){}
//control5
void daojushuoming_control5_Click(Node *node,Touch* ptouch, Event* event){}
//control12
void daojushuoming_control12_Click(Node *node,Touch* ptouch, Event* event){}
