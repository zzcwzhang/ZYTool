#include"UI.h"

std::string dialogTxt = "";

std::string propDialogTxt = "";
Node *propCtrl = nullptr;

void initialize(int formId)
{
  UIForm *form = nullptr;
  switch(formId)
  {
  case Form_buyuchang:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(buyuchang_initialize);
          form->setRegisterFunc(buyuchang_register);
      }
      break;
  case Form_duorenbuyuchang:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(duorenbuyuchang_initialize);
          form->setRegisterFunc(duorenbuyuchang_register);
      }
      break;
  case Form_danrenmoshixuanguan:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(danrenmoshixuanguan_initialize);
          form->setRegisterFunc(danrenmoshixuanguan_register);
      }
      break;
  case Form_renwutankuang:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(renwutankuang_initialize);
          form->setRegisterFunc(renwutankuang_register);
      }
      break;
  case Form_genghuanpaotai:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(genghuanpaotai_initialize);
          form->setRegisterFunc(genghuanpaotai_register);
      }
      break;
  case Form_daojushuoming:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(daojushuoming_initialize);
          form->setRegisterFunc(daojushuoming_register);
      }
      break;
  case Form_beilvjieshao:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(beilvjieshao_initialize);
          form->setRegisterFunc(beilvjieshao_register);
      }
      break;
  case Form_zaixianjiangli:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(zaixianjiangli_initialize);
          form->setRegisterFunc(zaixianjiangli_register);
      }
      break;
  case Form_duorenmoshixuanguan:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(duorenmoshixuanguan_initialize);
          form->setRegisterFunc(duorenmoshixuanguan_register);
      }
      break;
  case Form_VIPtishitankuang:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(VIPtishitankuang_initialize);
          form->setRegisterFunc(VIPtishitankuang_register);
      }
      break;
  case Form_fengmian:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(fengmian_initialize);
          form->setRegisterFunc(fengmian_register);
      }
      break;
  case Form_meiriqiandao:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(meiriqiandao_initialize);
          form->setRegisterFunc(meiriqiandao_register);
      }
      break;
  case Form_paihangbang:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(paihangbang_initialize);
          form->setRegisterFunc(paihangbang_register);
      }
      break;
  case Form_gerenxinxi:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(gerenxinxi_initialize);
          form->setRegisterFunc(gerenxinxi_register);
      }
      break;
  case Form_dengluchuangkou:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(dengluchuangkou_initialize);
          form->setRegisterFunc(dengluchuangkou_register);
      }
      break;
  case Form_jingbishangcheng:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(jingbishangcheng_initialize);
          form->setRegisterFunc(jingbishangcheng_register);
      }
      break;
  case Form_gameend:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(gameend_initialize);
          form->setRegisterFunc(gameend_register);
      }
      break;
  case Form_jiesuopaodan:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(jiesuopaodan_initialize);
          form->setRegisterFunc(jiesuopaodan_register);
      }
      break;
  case Form_canrentuichu:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(canrentuichu_initialize);
          form->setRegisterFunc(canrentuichu_register);
      }
      break;
  case Form_huodehuopao:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(huodehuopao_initialize);
          form->setRegisterFunc(huodehuopao_register);
      }
      break;
  case Form_email:
      {
          form = UIManager::getInstance()->getForm(formId);
          form->setInitFunc(email_initialize);
          form->setRegisterFunc(email_register);
      }
      break;
  case Form_daojutishikuang:
	  {
		  form = UIManager::getInstance()->getForm(formId);
		  form->setInitFunc(daojutishikuang_initialize);
		  form->setRegisterFunc(daojutishikuang_register);
	  }
	  break;
  case Form_lipingshangcheng:
	  {
		  form = UIManager::getInstance()->getForm(formId);
		  form->setInitFunc(lipingshangcheng_initialize);
		  form->setRegisterFunc(lipingshangcheng_register);
	  }
	  break;
  case Form_tongyongtishi:
	  {
		  form = UIManager::getInstance()->getForm(formId);
		  form->setInitFunc(tongyongtishi_initialize);
		  form->setRegisterFunc(tongyongtishi_register);
	  }
	  break;
  }
  (form->getRegisterFunc())(form);
}

void showCommonDialog(std::string str)
{
	dialogTxt = str;
	UIM->showForm(Form_tongyongtishi);
}

void showPropDialog(Node* node,std::string str)
{
	propCtrl = node;
	propDialogTxt = str;

	UIM->showForm(Form_daojutishikuang);
}