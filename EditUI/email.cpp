#include"UI.h"

#include "netHelpT.h"

vector<MailT*> mailTs;
bool isMailsBack = false;

Mail* mail = nullptr;
bool isMail = false;



void loadMailsCB(std::string str){
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();

		if (p.HasMember("mails")) {
			mailTs.clear();

			bool b = p["mails"].IsArray();
			if(b){
				const rapidjson::Value &object1 = p["mails"];
				int len2 = object1.Size();
				for (unsigned int i = 0; i<len2 ; ++i) {
					const rapidjson::Value &p1 = object1[i];
					if(p1.IsArray()){
						//log("rank =%s","sss1");
					}else{
						//log("rank =%s","sss2");
						const rapidjson::Value& v_mailId = p1["mailId"];
						const rapidjson::Value& v_isRead = p1["isRead"];
						const rapidjson::Value& v_sendTime = p1["sendTime"];
						const rapidjson::Value& v_title = p1["title"];


						int mailId = v_mailId.GetInt();
						int isRead = v_isRead.GetInt();


						string sendTime = v_sendTime.GetString();
						string title = v_title.GetString();

						MailT* mailT = new MailT();
						mailT->id = mailId;
						mailT->isRead = isRead;
						mailT->time = sendTime;
						mailT->title = title;

						mailTs.push_back(mailT);

						log("rank = %d id =%d",mailId,isRead);
					}
				}
			}

			isMailsBack = true;
			log("rank =%s","sss");
		}



	}
}

void initNetMail(){

	GSocket->openConnect();
	GSocket->ToLoadMails(1,loadMailsCB);
}

void loadMailCB(std::string str){


	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();
		mail = nullptr;


		const rapidjson::Value& v_mailId = p["mailId"];
		const rapidjson::Value& v_isReceivced = p["isReceivced"];
		const rapidjson::Value& v_content = p["content"];
		const rapidjson::Value& v_atmType = p["atmType"];
		const rapidjson::Value& v_atmCount = p["atmCount"];
		const rapidjson::Value& v_isRead = p["isRead"];
		//isRead

		int mailId = v_mailId.GetInt();
		int isReceivced = v_isReceivced.GetInt();
		int atmType = v_atmType.GetInt();
		int atmCount = v_atmCount.GetInt();
		int isRead = v_isRead.GetInt();

		string content = v_content.GetString();

		mail = new Mail();
		for (int i = 0; i < mailTs.size(); i++)
		{
			MailT* temp = mailTs.at(i);
			if (temp->id == mailId)
			{
				temp->isRead = isRead;
				mail->copyData(temp);
				
				isMailsBack = true;
			}
		}

		mail->isReceivced = isReceivced;
		mail->atmCount = atmCount;
		mail->atmType = atmType;
		mail->content = content;
		mail->isRead = isRead;


		isMail = true;
		log("rank =%s","sss");
	}
	



}

void acquireAtmCB(std::string str){
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();


		const rapidjson::Value& v_atmType = p["atmType"];
		const rapidjson::Value& v_atmCount = p["atmCount"];



		int atmType = v_atmType.GetInt();
		int atmCount = v_atmCount.GetInt();

		/*string str_info = "服务器标记已领取 客户端给相应奖励";
		log("str =%s",GBKToUTFStr(str_info).c_str());*/

		GSocket->openConnect();
		GSocket->ToLoadMail(1,mail->id,loadMailCB);
	}

}

void deleteMailCB(std::string str){
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();
		mail = nullptr;
		isMail = true;

		mailTs.clear();
		isMailsBack = true;

		if (result == 1)
		{
			/*string str_info = "单个邮件删除成功";
			log("str =%s",GBKToUTFStr(str_info).c_str());*/

			initNetMail();
		}

	
	}

}


void deleteMailsCB(std::string str){
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();

		mailTs.clear();
		isMailsBack = true;

		if (result == 1)
		{
			/*string str_info = "邮件全部删除成功";
			log("str =%s",GBKToUTFStr(str_info).c_str());*/

			initNetMail();
		}
	}

}




void email_register(Node* node)
{
UIForm *form = (UIForm*)node;
  form->getControl(email_control3)->registerClickEvent(email_control3_Click);
  form->getControl(email_control4)->registerClickEvent(email_control4_Click);
  form->getControl(email_control5)->registerClickEvent(email_control5_Click);
  form->getControl(email_control21)->registerClickEvent(email_control21_Click);
  form->getControl(email_control8)->registerClickEvent(email_control8_Click);


   form->getControl(email_control18)->registerClickEvent(email_control18_Click);
   form->getControl(email_control19)->registerClickEvent(email_control19_Click);
}
void email_initialize(Node* node)
{
	UIForm *form = (UIForm*)node;
	form->getControl(email_control7)->registerPaintEvent(email_control7_Paint);
	form->setUpdateEvent(email_update);

	initNetMail();
	//UIForm *form = (UIForm*)node;
	//MListView *listView = (MListView*)form->getControl(email_control6);
	//listView->setItemCount(5);
}
//control1
//control3
void email_control3_Click(Node *node,Touch* ptouch, Event* event){}
//control4
void email_control4_Click(Node *node,Touch* ptouch, Event* event){}
//control5

void email_control5_Click(Node *node,Touch* ptouch, Event* event){
	//领取
	if (mail != nullptr &&mail->isReceivced == 0)
	{
		GSocket->openConnect();
		GSocket->ToAcquireAtm(1,mail->id,acquireAtmCB);
	}
}
//control6
//control18
//control19
//control20
//control21
void email_control21_Click(Node *node,Touch* ptouch, Event* event){

	UIM->closeForm(Form_email,false);
}

void email_update(Node *node,float dt){
	auto form = UIM->getForm(Form_email);

	//context
	MControl *mail_context = form->getControl(email_control10);
	//atmType
	MControl *mail_atmType = form->getControl(email_control12);
	MControl *mail_lingqu = form->getControl(email_control5);

	if (mail == nullptr)
	{
		mail_context->setVisible(false);
		mail_atmType->setVisible(false);
		mail_lingqu->setVisible(false);
	}else{
		mail_lingqu->setVisible(true);
		mail_context->setVisible(true);
		mail_atmType->setVisible(true);
	}


	if(isMailsBack){

		MListView *listview = (MListView*)form->getControl(email_control6);
		listview->clearItems();
		int size = mailTs.size();
		listview->setItemCount(size);

		for (int i = 0; i < size; i++)
		{
			MailT* data = mailTs.at(i);

			MControl *item = listview->getItem(i);
			item->setUserData(data);
		}

		//显示数量
		MControl *mail_count = form->getControl(email_control22);
		Label* label_count = (Label*)mail_count->getPaintNode()->getChildByTag(99);
		if (label_count == nullptr)
		{
			label_count = Label::create(ConvertToString(size), FONT_TEXT, 30);
			label_count->setColor(Color3B::BLACK);
			label_count->setHeight(mail_count->getSize().height);
			label_count->setWidth(mail_count->getSize().width);
			label_count->setPositionX(mail_count->getSize().width/2);
			label_count->setPositionY(mail_count->getSize().height/2);
			mail_count->getPaintNode()->addChild(label_count,1,99);
		}else{
			label_count->setString(ConvertToString(size));
		}
		


		isMailsBack = false;

		/*if (mail != nullptr)
		{
			for (int i = 0; i < mailTs.size(); i++)
			{
				MailT* data = mailTs.at(i);
				MControl *item = listview->getItem(i);
				if (mail->id = data->id)
				{
					UIM->setSkin(item,1);
					UIM->setSkin(item->ctrlList.at(0),1);
				}else{
					UIM->setSkin(item,0);
					UIM->setSkin(item->ctrlList.at(0),0);
				}
			}
		}*/
	}


	if (isMail)
	{
		if (mail != nullptr)
		{
			//context
			//MControl *mail_context = form->getControl(email_control10);
			Label* label_context = (Label*)mail_context->getPaintNode()->getChildByTag(99);
			if (label_context == nullptr)
			{
				label_context = Label::create(mail->content, FONT_TEXT, 30);
				label_context->setColor(Color3B::BLACK);
				label_context->setHeight(mail_context->getSize().height);
				label_context->setWidth(mail_context->getSize().width);
				label_context->setPositionX(mail_context->getSize().width/2);
				label_context->setPositionY(mail_context->getSize().height/2);
				mail_context->getPaintNode()->addChild(label_context,1,99);
			}else
			{
			  label_context->setString(mail->content);
			}

			//atmType
			//MControl *mail_atmType = form->getControl(email_control12);
			Label* label_atmType = (Label*)mail_atmType->getPaintNode()->getChildByTag(99);
			string str = GMI->getString("email","atmType1");
			if (label_atmType == nullptr)
			{
				label_atmType = Label::create(str, FONT_TEXT, 30);
				label_atmType->setColor(Color3B::BLACK);
				label_atmType->setHeight(mail_atmType->getSize().height);
				label_atmType->setWidth(mail_atmType->getSize().width);
				label_atmType->setPositionX(mail_atmType->getSize().width/2);
				label_atmType->setPositionY(mail_atmType->getSize().height/2);
				mail_atmType->getPaintNode()->addChild(label_atmType,1,99);
			}else
			{
				label_atmType->setString(str);
			}

			//atmCount
			Label* label_atmCount = (Label*)mail_atmType->getPaintNode()->getChildByTag(100);
			//string str = "金币";
			if (label_atmCount == nullptr)
			{
				label_atmCount = Label::create(ConvertToString(mail->atmCount), FONT_TEXT, 15);
				label_atmCount->setColor(Color3B::RED);
				label_atmCount->setHeight(mail_atmType->getSize().height);
				label_atmCount->setWidth(mail_atmType->getSize().width);
				label_atmCount->setPositionX(mail_atmType->getSize().width/2+50);
				label_atmCount->setPositionY(20);
				mail_atmType->getPaintNode()->addChild(label_atmCount,1,100);
			}else
			{
				label_atmCount->setString(ConvertToString(mail->atmCount));
			}


			MControl *mail_have = form->getControl(email_control20);
			if (mail->isReceivced == 0)
			{
				mail_have->setVisible(false);
			}else{
				mail_have->setVisible(true);
			}
			
		}

		isMail = false;
	}
}

void email_control7_Paint(Node *node) {

	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	MailT *data = (MailT*)ctrl->getUserData();
	if (data != nullptr)
	{
		//图标
		MControl *ctrl_icon = ctrl->ctrlList.at(0);
		
		if (data->isRead == 0)
		{
			UIM->setSkin(ctrl_icon,0);
		}else{
			UIM->setSkin(ctrl_icon,1);
		}

		//title
		MControl *ctrl_title = ctrl->ctrlList.at(2);

		Label* label_title = (Label*)ctrl_title->getPaintNode()->getChildByTag(99);
		if(label_title == nullptr){
			label_title = Label::create(data->title, FONT_TEXT, 20);
			label_title->setColor(Color3B::BLACK);
			label_title->setHeight(ctrl_title->getSize().height);
			label_title->setWidth(ctrl_title->getSize().width);
			label_title->setPositionX(ctrl_title->getSize().width/2);
			label_title->setPositionY(ctrl_title->getSize().height/2-10);
			ctrl_title->getPaintNode()->addChild(label_title,1,99);
		}else{
			label_title->setString(data->title);
		}
		
		//time
		MControl *ctrl_time = ctrl->ctrlList.at(3);
		Label* label_time = (Label*)ctrl_time->getPaintNode()->getChildByTag(99);
		if (label_time == nullptr)
		{
			label_time = Label::create(data->time, FONT_TEXT, 10);
			label_time->setColor(Color3B::BLACK);
			label_time->setHeight(ctrl_time->getSize().height);
			label_time->setWidth(ctrl_time->getSize().width);
			label_time->setPositionX(ctrl_time->getSize().width/2);
			label_time->setPositionY(0);
			ctrl_time->getPaintNode()->addChild(label_time,1,99);

		}else
		{
			label_time->setString(data->time);
		}
		
	}
}

void email_control8_Click(Node *node,Touch* ptouch, Event* event){

	MControl *parent =(MControl*) node->getParent();
	MailT *data = (MailT*)parent->getUserData();
	if (data != nullptr){
		int id = data->id;
		GSocket->openConnect();
		GSocket->ToLoadMail(1,id,loadMailCB);

	}
	//auto form = UIM->getForm(Form_email);
	////context
	//MControl *item_bg = form->getControl(email_control7);
	//UIM->setSkin((MControl*)node,1);
	//UIM->setSkin(item_bg,1);
}

void email_control18_Click(Node *node,Touch* ptouch, Event* event){
	//邮件全删
	if (mailTs.size()>0)
	{
		GSocket->openConnect();
		GSocket->ToDeleteMails(1,deleteMailsCB);
	}
}
void email_control19_Click(Node *node,Touch* ptouch, Event* event){
	//删一个
	if (mail != nullptr)
	{
		GSocket->openConnect();
		GSocket->ToDeleteMail(1,mail->id,deleteMailCB);
	}
}
