#include"UI.h"
#include "netHelpT.h"


vector<BigRank*> bigranks;
bool isBig = false;
BigRank* bigself = nullptr;
bool isBigSelf = false;
int bigCount = 0;

vector<SuperRank*> superranks;
bool isSuper = false;
SuperRank* superself = nullptr;
bool isSuperSelf = false;
int superCount = 0;

vector<LikedRank*> likedranks;
bool isLiked = false;
LikedRank* likedself = nullptr;
bool isLikedSelf = false;
int likedCount = 0;

vector<TimeRank*> timeranks;
bool isTime = false;
TimeRank* timeself = nullptr;
bool isTimeSelf = false;
int timeCount = 0;

vector<TicketRank*> ticketranks;
bool isTicket = false;
TicketRank* ticketself = nullptr;
bool isTicketSelf = false;
int ticketCount = 0;



void bigRankSelfCB(std::string str){
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();
		
		bigCount = p["count"].GetInt();
		
		if (p.HasMember("bigRankself")) {
			bigself = nullptr;

			bool b = p["bigRankself"].IsObject();
			if(b){
				const rapidjson::Value &object1 = p["bigRankself"];
				if (object1.HasMember("chargeScore"))
				{
					const rapidjson::Value& v_id = object1["id"];
					const rapidjson::Value& v_rank = object1["rank"];
					const rapidjson::Value& v_vip = object1["vip"];
					const rapidjson::Value& v_nickname = object1["nickName"];
					const rapidjson::Value& v_chargeScore = object1["chargeScore"];
					const rapidjson::Value& v_toLike = object1["toLike"];

					int id = v_id.GetInt();
					int rank = v_rank.GetInt();
					int vip = v_vip.GetInt();
					int chargeScore = v_chargeScore.GetInt();

					string nickname = v_nickname.GetString();

					bigself = new BigRank();
					bigself->id = id;
					bigself->rank = rank;
					bigself->vip = vip;
					bigself->chargeScore = chargeScore;
					bigself->nickname = nickname;

				}

			}
		}

		isBigSelf = true;
		log("rank =%s","sss");




	}
} 

void superRankSelfCB(std::string str){
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();
		superCount = p["count"].GetInt();
		if (p.HasMember("superRankself")) {
			superself = nullptr;

			bool b = p["superRankself"].IsObject();
			if(b){
				const rapidjson::Value &object1 = p["superRankself"];
				if (object1.HasMember("fishScore"))
				{
					const rapidjson::Value& v_id = object1["id"];
					const rapidjson::Value& v_rank = object1["rank"];
					const rapidjson::Value& v_vip = object1["vip"];
					const rapidjson::Value& v_nickname = object1["nickName"];
					const rapidjson::Value& v_fishScore = object1["fishScore"];
					const rapidjson::Value& v_toLike = object1["toLike"];

					int id = v_id.GetInt();
					int rank = v_rank.GetInt();
					int vip = v_vip.GetInt();
					int fishScore = v_fishScore.GetInt();

					string nickname = v_nickname.GetString();

					superself = new SuperRank();
					superself->id = id;
					superself->rank = rank;
					superself->vip = vip;
					superself->fishScore = fishScore;
					superself->nickname = nickname;

				}

			}
		}

		isSuperSelf = true;
		log("rank =%s","sss");




	}
} 


void timeRankSelfCB(std::string str){
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();
		timeCount = p["count"].GetInt();
		if (p.HasMember("timeRankself")) {
			timeself = nullptr;

			bool b = p["timeRankself"].IsObject();
			if(b){
				const rapidjson::Value &object1 = p["timeRankself"];
				if (object1.HasMember("onlineTimes"))
				{
					const rapidjson::Value& v_id = object1["id"];
					const rapidjson::Value& v_rank = object1["rank"];
					const rapidjson::Value& v_vip = object1["vip"];
					const rapidjson::Value& v_nickname = object1["nickName"];
					const rapidjson::Value& v_onlineTimes = object1["onlineTimes"];
					const rapidjson::Value& v_toLike = object1["toLike"];

					int id = v_id.GetInt();
					int rank = v_rank.GetInt();
					int vip = v_vip.GetInt();
					int onlineTimes = v_onlineTimes.GetInt();

					string nickname = v_nickname.GetString();

					timeself = new TimeRank();
					timeself->id = id;
					timeself->rank = rank;
					timeself->vip = vip;
					timeself->onlineTimes = onlineTimes;
					timeself->nickname = nickname;

				}

			}
		}

		isTimeSelf = true;
		log("rank =%s","sss");




	}
} 


void likedRankSelfCB(std::string str){
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();
		likedCount = p["count"].GetInt();
		if (p.HasMember("likedRankself")) {
			likedself = nullptr;

			bool b = p["likedRankself"].IsObject();
			if(b){
				const rapidjson::Value &object1 = p["likedRankself"];
				if (object1.HasMember("liked"))
				{
					const rapidjson::Value& v_id = object1["id"];
					const rapidjson::Value& v_rank = object1["rank"];
					const rapidjson::Value& v_vip = object1["vip"];
					const rapidjson::Value& v_nickname = object1["nickName"];
					const rapidjson::Value& v_liked = object1["liked"];
					const rapidjson::Value& v_toLike = object1["toLike"];

					int id = v_id.GetInt();
					int rank = v_rank.GetInt();
					int vip = v_vip.GetInt();
					int liked = v_liked.GetInt();

					string nickname = v_nickname.GetString();

					likedself = new LikedRank();
					likedself->id = id;
					likedself->rank = rank;
					likedself->vip = vip;
					likedself->liked = liked;
					likedself->nickname = nickname;

				}

			}
		}

		isLikedSelf = true;
		log("rank =%s","sss");




	}
} 


void ticketRankSelfCB(std::string str){
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();
		ticketCount = p["count"].GetInt();
		if (p.HasMember("ticketRankself")) {
			ticketself = nullptr;

			bool b = p["ticketRankself"].IsObject();
			if(b){
				const rapidjson::Value &object1 = p["ticketRankself"];
				if (object1.HasMember("ticket"))
				{
					const rapidjson::Value& v_id = object1["id"];
					const rapidjson::Value& v_rank = object1["rank"];
					const rapidjson::Value& v_vip = object1["vip"];
					const rapidjson::Value& v_nickname = object1["nickName"];
					const rapidjson::Value& v_ticket = object1["ticket"];
					const rapidjson::Value& v_toLike = object1["toLike"];

					int id = v_id.GetInt();
					int rank = v_rank.GetInt();
					int vip = v_vip.GetInt();
					int ticket = v_ticket.GetInt();

					string nickname = v_nickname.GetString();

					ticketself = new TicketRank();
					ticketself->id = id;
					ticketself->rank = rank;
					ticketself->vip = vip;
					ticketself->ticket = ticket;
					ticketself->nickname = nickname;

				}

			}
		}

		isTicketSelf = true;
		log("rank =%s","sss");




	}
} 

void bigRankCB(std::string str)
{
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();

		if (p.HasMember("rank")) {
			bigranks.clear();
			//bool a = p.IsArray();
			bool b = p["rank"].IsArray();
			if(b){
				const rapidjson::Value &object1 = p["rank"];
				int len2 = object1.Size();
				for (unsigned int i = 0; i<len2 ; ++i) {
					const rapidjson::Value &p1 = object1[i];
					if(p1.IsArray()){
						//log("rank =%s","sss1");
					}else{
						//log("rank =%s","sss2");
						const rapidjson::Value& v_id = p1["id"];
						const rapidjson::Value& v_rank = p1["rank"];
						const rapidjson::Value& v_vip = p1["vip"];
						const rapidjson::Value& v_nickname = p1["nickName"];
						const rapidjson::Value& v_chargeScore = p1["chargeScore"];
						const rapidjson::Value& v_toLike = p1["toLike"];

						int id = v_id.GetInt();
						int rank = v_rank.GetInt();
						int vip = v_vip.GetInt();
						int chargeScore = v_chargeScore.GetInt();

						string nickname = v_nickname.GetString();

						bool toLike = v_toLike.GetBool();

						BigRank* bigRank = new BigRank();
						bigRank->id = id;
						bigRank->rank = rank;
						bigRank->vip = vip;
						bigRank->chargeScore = chargeScore;
						bigRank->nickname = nickname;
						bigRank->toLike = toLike;
						bigranks.push_back(bigRank);

						log("rank = %d id =%d",rank,id);
					}
				}
			}

			isBig = true;
			log("rank =%s","sss");
		}



	}





}


void superRankCB(std::string str)
{
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();

		if (p.HasMember("rank")) {
			superranks.clear();
			//bool a = p.IsArray();
			bool b = p["rank"].IsArray();
			if(b){
				const rapidjson::Value &object1 = p["rank"];
				int len2 = object1.Size();
				for (unsigned int i = 0; i<len2 ; ++i) {
					const rapidjson::Value &p1 = object1[i];
					if(p1.IsArray()){
						//log("rank =%s","sss1");
					}else{
						//log("rank =%s","sss2");
						const rapidjson::Value& v_id = p1["id"];
						const rapidjson::Value& v_rank = p1["rank"];
						const rapidjson::Value& v_vip = p1["vip"];
						const rapidjson::Value& v_nickname = p1["nickName"];
						const rapidjson::Value& v_fishScore = p1["fishScore"];
						const rapidjson::Value& v_toLike = p1["toLike"];

						int id = v_id.GetInt();
						int rank = v_rank.GetInt();
						int vip = v_vip.GetInt();
						int fishScore = v_fishScore.GetInt();

						string nickname = v_nickname.GetString();

						bool toLike = v_toLike.GetBool();

						SuperRank* superRank = new SuperRank();
						superRank->id = id;
						superRank->rank = rank;
						superRank->vip = vip;
						superRank->fishScore = fishScore;
						superRank->nickname = nickname;
						superRank->toLike = toLike;
						superranks.push_back(superRank);

						log("rank = %d id =%d",rank,id);
					}
				}
			}

			isSuper = true;
			log("rank =%s","sss");
		}

	}


}

void timeRankCB(std::string str)
{
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();

		if (p.HasMember("rank")) {
			timeranks.clear();
			//bool a = p.IsArray();
			bool b = p["rank"].IsArray();
			if(b){
				const rapidjson::Value &object1 = p["rank"];
				int len2 = object1.Size();
				for (unsigned int i = 0; i<len2 ; ++i) {
					const rapidjson::Value &p1 = object1[i];
					if(p1.IsArray()){
						//log("rank =%s","sss1");
					}else{
						//log("rank =%s","sss2");
						const rapidjson::Value& v_id = p1["id"];
						const rapidjson::Value& v_rank = p1["rank"];
						const rapidjson::Value& v_vip = p1["vip"];
						const rapidjson::Value& v_nickname = p1["nickName"];
						const rapidjson::Value& v_onlineTimes = p1["onlineTimes"];
						const rapidjson::Value& v_toLike = p1["toLike"];

						int id = v_id.GetInt();
						int rank = v_rank.GetInt();
						int vip = v_vip.GetInt();
						int onlineTimes = v_onlineTimes.GetInt();

						string nickname = v_nickname.GetString();

						bool toLike = v_toLike.GetBool();

						TimeRank* timeRank = new TimeRank();
						timeRank->id = id;
						timeRank->rank = rank;
						timeRank->vip = vip;
						timeRank->onlineTimes = onlineTimes;
						timeRank->nickname = nickname;
						timeRank->toLike = toLike;
						timeranks.push_back(timeRank);

						log("rank = %d id =%d",rank,id);
					}
				}
			}

			isTime = true;
			log("rank =%s","sss");
		}

	}


}


void likedRankCB(std::string str)
{
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();

		if (p.HasMember("rank")) {
			likedranks.clear();
			//bool a = p.IsArray();
			bool b = p["rank"].IsArray();
			if(b){
				const rapidjson::Value &object1 = p["rank"];
				int len2 = object1.Size();
				for (unsigned int i = 0; i<len2 ; ++i) {
					const rapidjson::Value &p1 = object1[i];
					if(p1.IsArray()){
						//log("rank =%s","sss1");
					}else{
						//log("rank =%s","sss2");
						const rapidjson::Value& v_id = p1["id"];
						const rapidjson::Value& v_rank = p1["rank"];
						const rapidjson::Value& v_vip = p1["vip"];
						const rapidjson::Value& v_nickname = p1["nickName"];
						const rapidjson::Value& v_liked = p1["liked"];
						const rapidjson::Value& v_toLike = p1["toLike"];

						int id = v_id.GetInt();
						int rank = v_rank.GetInt();
						int vip = v_vip.GetInt();
						int liked = v_liked.GetInt();

						string nickname = v_nickname.GetString();

						bool toLike = v_toLike.GetBool();

						LikedRank* likedRank = new LikedRank();
						likedRank->id = id;
						likedRank->rank = rank;
						likedRank->vip = vip;
						likedRank->liked = liked;
						likedRank->nickname = nickname;
						likedRank->toLike = toLike;
						likedranks.push_back(likedRank);

						log("rank = %d id =%d",rank,id);
					}
				}
			}

			isLiked = true;
			log("rank =%s","sss");
		}

	}


}


void ticketRankCB(std::string str)
{
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();

		if (p.HasMember("rank")) {
			ticketranks.clear();
			//bool a = p.IsArray();
			bool b = p["rank"].IsArray();
			if(b){
				const rapidjson::Value &object1 = p["rank"];
				int len2 = object1.Size();
				for (unsigned int i = 0; i<len2 ; ++i) {
					const rapidjson::Value &p1 = object1[i];
					if(p1.IsArray()){
						//log("rank =%s","sss1");
					}else{
						//log("rank =%s","sss2");
						const rapidjson::Value& v_id = p1["id"];
						const rapidjson::Value& v_rank = p1["rank"];
						const rapidjson::Value& v_vip = p1["vip"];
						const rapidjson::Value& v_nickname = p1["nickName"];
						const rapidjson::Value& v_ticket = p1["ticket"];
						const rapidjson::Value& v_toLike = p1["toLike"];

						int id = v_id.GetInt();
						int rank = v_rank.GetInt();
						int vip = v_vip.GetInt();
						int ticket = v_ticket.GetInt();

						string nickname = v_nickname.GetString();

						bool toLike = v_toLike.GetBool();

						TicketRank* ticketRank = new TicketRank();
						ticketRank->id = id;
						ticketRank->rank = rank;
						ticketRank->vip = vip;
						ticketRank->ticket = ticket;
						ticketRank->nickname = nickname;
						ticketRank->toLike = toLike;
						ticketranks.push_back(ticketRank);

						log("rank = %d id =%d",rank,id);
					}
				}
			}

			isTicket = true;
			log("rank =%s","sss");
		}

	}


}

void giveLikedCB(std::string str){
	log("str =%s",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int result = p["result"].GetInt();

		if (p.HasMember("type")) {
			const rapidjson::Value& v_type = p["type"];
			int type = v_type.GetInt();
			string infoStr = "";
			switch (type)
			{
			case CmdRank::BIGRANK:
				/*infoStr = "土豪榜点赞成功";
				log("giveLiked =%s",GBKToUTF(infoStr));*/

				GSocket->openConnect();
				GSocket->ToRank(1,CmdRank::BIGRANK,bigRankCB);
				break;
			case CmdRank::SUPERRANK:
				/*infoStr = "捕鱼达人榜点赞成功";
				log("giveLiked =%s",GBKToUTF(infoStr));*/

				GSocket->openConnect();
				GSocket->ToRank(1,CmdRank::SUPERRANK,superRankCB);
				break;
			case CmdRank::TICKETRANK:
				/*infoStr = "奖券榜点赞成功";
				log("giveLiked =%s",GBKToUTF(infoStr));*/

				GSocket->openConnect();
				GSocket->ToRank(1,CmdRank::TICKETRANK,ticketRankCB);
				break;
			case CmdRank::TIMERANK:
				/*infoStr = "在线榜点赞成功";
				log("giveLiked =%s",GBKToUTF(infoStr));*/

				GSocket->openConnect();
				GSocket->ToRank(1,CmdRank::TIMERANK,timeRankCB);
				break;
			case CmdRank::LIKEDRANK:
				/*infoStr = "每日之星点赞成功";
				log("giveLiked =%s",GBKToUTF(infoStr));*/

				GSocket->openConnect();
				GSocket->ToRank(1,CmdRank::LIKEDRANK,likedRankCB);
				break;
			}
		}


		log("rank =%s","sss");




	}
}

void initRank(){
	if (bigranks.size()>0)
	{
		isBig = true;
	}else{

		auto form = UIM->getForm(Form_paihangbang);
		MControl *ctrl3 = form->getControl(paihangbang_control3);//big ui
		MControl *ctrl4 = form->getControl(paihangbang_control4);//ticket ui
		MControl *ctrl5 = form->getControl(paihangbang_control5);//super ui
		MControl *ctrl6 = form->getControl(paihangbang_control6);//time ui
		MControl *ctrl7 = form->getControl(paihangbang_control7);//like ui
		//皮肤
		UIM->setSkin(ctrl3,0);
		UIM->setSkin(ctrl4,0);
		UIM->setSkin(ctrl5,0);
		UIM->setSkin(ctrl6,0);
		UIM->setSkin(ctrl7,0);

		UIM->setSkin(ctrl3,1);

		GSocket->openConnect();
		GSocket->ToRank(1,CmdRank::BIGRANK,bigRankCB);
	}

}

void paihangbang_register(Node* node)
{
UIForm *form = (UIForm*)node;
  form->getControl(paihangbang_control3)->registerClickEvent(paihangbang_control3_Click);
  form->getControl(paihangbang_control4)->registerClickEvent(paihangbang_control4_Click);
  form->getControl(paihangbang_control5)->registerClickEvent(paihangbang_control5_Click);
  form->getControl(paihangbang_control6)->registerClickEvent(paihangbang_control6_Click);
  form->getControl(paihangbang_control7)->registerClickEvent(paihangbang_control7_Click);
  form->getControl(paihangbang_control34)->registerClickEvent(paihangbang_control34_Click);
  
  
  form->getControl(paihangbang_control37)->registerClickEvent(paihangbang_control37_Click);
  
  form->getControl(paihangbang_control39)->registerClickEvent(paihangbang_control39_Click);

  form->getControl(paihangbang_control35)->registerClickEvent(paihangbang_control35_Click);
  form->getControl(paihangbang_control38)->registerClickEvent(paihangbang_control38_Click);
  form->getControl(paihangbang_control26)->registerClickEvent(paihangbang_control26_Click);
  form->getControl(paihangbang_control36)->registerClickEvent(paihangbang_control36_Click);
  form->getControl(paihangbang_control46)->registerClickEvent(paihangbang_control46_Click);

  //初始化排行榜
  initRank();
}




void paihangbang_control11_Paint(Node *node)
{
	//刷新土豪榜bigRank
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	BigRank *data = (BigRank*)ctrl->getUserData();
	if (data != nullptr)
	{
		//排名
		MControl *ctrl_rank = ctrl->ctrlList.at(1);

		if (data->rank == 1)
		{
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_1);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}


		}else if (data->rank == 2){
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_2);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}
		}else if (data->rank == 3){
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_3);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}
		}

		Label* label_rank =(Label*) ctrl_rank->getPaintNode()->getChildByTag(100);
		if (label_rank == nullptr)
		{
			label_rank = Label::create(ConvertToString(data->rank), FONT_TEXT, 20);
			label_rank->setColor(Color3B::BLACK);
			ctrl_rank->getPaintNode()->addChild(label_rank,1,100);
		}else{
			label_rank->setString(ConvertToString(data->rank));
		}

		
		//VIP等级
		MControl *ctrl_vip = ctrl->ctrlList.at(2);
		UIM->setSkin(ctrl_vip,data->vip);
		//auto label_vip = Label::createWithBMFont(VIP_FNT,ConvertToString(data->vip));
		////label_vip->setScale(0.5f);
		//label_vip->setPosition(Vec2(ctrl_vip->getSize().width+5,ctrl_vip->getSize().height/2));
		//ctrl_vip->addChild(label_vip);
		//昵称
		MControl *ctrl_nickname = ctrl->ctrlList.at(3);

		Label* label_nickname =(Label*) ctrl_nickname->getPaintNode()->getChildByTag(99);
		if (label_nickname == nullptr)
		{
			label_nickname = Label::create(ConvertToString(data->nickname), FONT_TEXT, 20);
			label_nickname->setColor(Color3B::BLACK);
			ctrl_nickname->getPaintNode()->addChild(label_nickname,1,99);
		}else
		{
			label_nickname->setString(ConvertToString(data->nickname));
		}

		
		//充值积分
		MControl *ctrl_chargeScore = ctrl->ctrlList.at(4);

		Label* label_chargeScore =(Label*) ctrl_chargeScore->getPaintNode()->getChildByTag(99);
		if (label_chargeScore == nullptr)
		{
			label_chargeScore = Label::create(ConvertToString(data->chargeScore), FONT_TEXT, 20);
			label_chargeScore->setColor(Color3B::BLACK);
			ctrl_chargeScore->getPaintNode()->addChild(label_chargeScore,1,99);
		}else
		{
			label_chargeScore->setString(ConvertToString(data->chargeScore));
		}

		
		//点赞操作
		MControl *ctrl_toliked = ctrl->ctrlList.at(0);

		ctrl_toliked->setVisible(!data->toLike);
		
		
	}
	
	
	
}


void paihangbang_control31_Paint(Node *node) 
{
	//刷新每日之星likedRank
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	LikedRank *data = (LikedRank*)ctrl->getUserData();
	if (data != nullptr)
	{
		//排名
		MControl *ctrl_rank = ctrl->ctrlList.at(1);

		if (data->rank == 1)
		{
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_1);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}


		}else if (data->rank == 2){
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_2);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}
		}else if (data->rank == 3){
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_3);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}
		}

		Label* label_rank =(Label*) ctrl_rank->getPaintNode()->getChildByTag(100);
		if (label_rank == nullptr)
		{
			label_rank = Label::create(ConvertToString(data->rank), FONT_TEXT, 20);
			label_rank->setColor(Color3B::BLACK);
			ctrl_rank->getPaintNode()->addChild(label_rank,1,100);
		}else{
			label_rank->setString(ConvertToString(data->rank));
		}
		//VIP等级
		MControl *ctrl_vip = ctrl->ctrlList.at(4);
		UIM->setSkin(ctrl_vip,data->vip);
		//auto label_vip = Label::createWithBMFont(VIP_FNT,ConvertToString(data->vip));
		////label_vip->setScale(0.5f);
		//label_vip->setPosition(Vec2(ctrl_vip->getSize().width+5,ctrl_vip->getSize().height/2));
		//ctrl_vip->addChild(label_vip);
		//昵称
		MControl *ctrl_nickname = ctrl->ctrlList.at(2);
		Label* label_nickname =(Label*) ctrl_nickname->getPaintNode()->getChildByTag(99);
		if (label_nickname == nullptr)
		{
			label_nickname = Label::create(ConvertToString(data->nickname), FONT_TEXT, 20);
			label_nickname->setColor(Color3B::BLACK);
			ctrl_nickname->getPaintNode()->addChild(label_nickname,1,99);
		}else
		{
			label_nickname->setString(ConvertToString(data->nickname));
		}
		//充值积分
		MControl *ctrl_liked = ctrl->ctrlList.at(3);
		Label* label_liked =(Label*) ctrl_liked->getPaintNode()->getChildByTag(99);
		if (label_liked == nullptr)
		{
			label_liked = Label::create(ConvertToString(data->liked), FONT_TEXT, 20);
			label_liked->setColor(Color3B::BLACK);
			ctrl_liked->getPaintNode()->addChild(label_liked,1,99);
		}else
		{
			label_liked->setString(ConvertToString(data->liked));
		}
		
		//点赞操作
		MControl *ctrl_toliked = ctrl->ctrlList.at(0);
		ctrl_toliked->setVisible(!data->toLike);

	}



}

void paihangbang_control16_Paint(Node *node) 
{
	//捕鱼达人superRank
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	SuperRank *data = (SuperRank*)ctrl->getUserData();
	if (data != nullptr)
	{
		//排名
		MControl *ctrl_rank = ctrl->ctrlList.at(1);

		if (data->rank == 1)
		{
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_1);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}


		}else if (data->rank == 2){
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_2);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}
		}else if (data->rank == 3){
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_3);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}
		}

		Label* label_rank =(Label*) ctrl_rank->getPaintNode()->getChildByTag(100);
		if (label_rank == nullptr)
		{
			label_rank = Label::create(ConvertToString(data->rank), FONT_TEXT, 20);
			label_rank->setColor(Color3B::BLACK);
			ctrl_rank->getPaintNode()->addChild(label_rank,1,100);
		}else{
			label_rank->setString(ConvertToString(data->rank));
		}
		//VIP等级
		MControl *ctrl_vip = ctrl->ctrlList.at(4);
		UIM->setSkin(ctrl_vip,data->vip);
		//auto label_vip = Label::createWithBMFont(VIP_FNT,ConvertToString(data->vip));
		////label_vip->setScale(0.5f);
		//label_vip->setPosition(Vec2(ctrl_vip->getSize().width+5,ctrl_vip->getSize().height/2));
		//ctrl_vip->addChild(label_vip);
		//昵称
		MControl *ctrl_nickname = ctrl->ctrlList.at(2);
		Label* label_nickname =(Label*) ctrl_nickname->getPaintNode()->getChildByTag(99);
		if (label_nickname == nullptr)
		{
			label_nickname = Label::create(ConvertToString(data->nickname), FONT_TEXT, 20);
			label_nickname->setColor(Color3B::BLACK);
			ctrl_nickname->getPaintNode()->addChild(label_nickname,1,99);
		}else
		{
			label_nickname->setString(ConvertToString(data->nickname));
		}
		//充值积分
		MControl *ctrl_fishScore = ctrl->ctrlList.at(3);
		Label* label_fishScore =(Label*) ctrl_fishScore->getPaintNode()->getChildByTag(99);
		if (label_fishScore == nullptr)
		{
			label_fishScore = Label::create(ConvertToString(data->fishScore), FONT_TEXT, 20);
			label_fishScore->setColor(Color3B::BLACK);
			ctrl_fishScore->getPaintNode()->addChild(label_fishScore,1,99);
		}else
		{
			label_fishScore->setString(ConvertToString(data->fishScore));
		}
		
		
		//点赞操作
		MControl *ctrl_toliked = ctrl->ctrlList.at(0);
		ctrl_toliked->setVisible(!data->toLike);

	}



}

void paihangbang_control45_Paint(Node *node) 
{
	//奖券ticketRank
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	TicketRank *data = (TicketRank*)ctrl->getUserData();
	if (data != nullptr)
	{

		//排名
		MControl *ctrl_rank = ctrl->ctrlList.at(1);

		if (data->rank == 1)
		{
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_1);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}


		}else if (data->rank == 2){
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_2);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}
		}else if (data->rank == 3){
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_3);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}
		}

		Label* label_rank =(Label*) ctrl_rank->getPaintNode()->getChildByTag(100);
		if (label_rank == nullptr)
		{
			label_rank = Label::create(ConvertToString(data->rank), FONT_TEXT, 20);
			label_rank->setColor(Color3B::BLACK);
			ctrl_rank->getPaintNode()->addChild(label_rank,1,100);
		}else{
			label_rank->setString(ConvertToString(data->rank));
		}
		//VIP等级
		MControl *ctrl_vip = ctrl->ctrlList.at(4);
		UIM->setSkin(ctrl_vip,data->vip);
		//auto label_vip = Label::createWithBMFont(VIP_FNT,ConvertToString(data->vip));
		////label_vip->setScale(0.5f);
		//label_vip->setPosition(Vec2(ctrl_vip->getSize().width+5,ctrl_vip->getSize().height/2));
		//ctrl_vip->addChild(label_vip);
		//昵称
		MControl *ctrl_nickname = ctrl->ctrlList.at(2);
		Label* label_nickname =(Label*) ctrl_nickname->getPaintNode()->getChildByTag(99);
		if (label_nickname == nullptr)
		{
			label_nickname = Label::create(ConvertToString(data->nickname), FONT_TEXT, 20);
			label_nickname->setColor(Color3B::BLACK);
			ctrl_nickname->getPaintNode()->addChild(label_nickname,1,99);
		}else
		{
			label_nickname->setString(ConvertToString(data->nickname));
		}
		//充值积分
		MControl *ctrl_ticket = ctrl->ctrlList.at(3);
		Label* label_ticket =(Label*) ctrl_ticket->getPaintNode()->getChildByTag(99);
		if (label_ticket == nullptr)
		{
			label_ticket = Label::create(ConvertToString(data->ticket), FONT_TEXT, 20);
			label_ticket->setColor(Color3B::BLACK);
			ctrl_ticket->getPaintNode()->addChild(label_ticket,1,99);
		}else{
			label_ticket->setString(ConvertToString(data->ticket));
		}

		
		//点赞操作
		MControl *ctrl_toliked = ctrl->ctrlList.at(0);
		ctrl_toliked->setVisible(!data->toLike);

	}



}


void paihangbang_control21_Paint(Node *node) 
{
	//在线时长timeRank
	MControl *ctrl = (MControl*)node;
	Node *paintNode = ctrl->getPaintNode();
	paintNode->removeAllChildren();

	TimeRank *data = (TimeRank*)ctrl->getUserData();
	if (data != nullptr)
	{
		//排名
		MControl *ctrl_rank = ctrl->ctrlList.at(1);

		

		if (data->rank == 1)
		{
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_1);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}


		}else if (data->rank == 2){
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_2);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}
		}else if (data->rank == 3){
			if (ctrl_rank->getPaintNode()->getChildByTag(99) == nullptr)
			{
				Sprite* jb1 = Sprite::create(JB_3);
				ctrl_rank->getPaintNode()->addChild(jb1,1,99);
			}
		}

		Label* label_rank =(Label*) ctrl_rank->getPaintNode()->getChildByTag(100);
		if (label_rank == nullptr)
		{
			label_rank = Label::create(ConvertToString(data->rank), FONT_TEXT, 20);
			label_rank->setColor(Color3B::BLACK);
			ctrl_rank->getPaintNode()->addChild(label_rank,1,100);
		}else{
			label_rank->setString(ConvertToString(data->rank));
		}
		//VIP等级
		MControl *ctrl_vip = ctrl->ctrlList.at(4);
		UIM->setSkin(ctrl_vip,data->vip);
		//auto label_vip = Label::createWithBMFont(VIP_FNT,ConvertToString(data->vip));
		////label_vip->setScale(0.5f);
		//label_vip->setPosition(Vec2(ctrl_vip->getSize().width+5,ctrl_vip->getSize().height/2));
		//ctrl_vip->addChild(label_vip);
		//昵称
		MControl *ctrl_nickname = ctrl->ctrlList.at(2);
		Label* label_nickname =(Label*) ctrl_nickname->getPaintNode()->getChildByTag(99);
		if (label_nickname == nullptr)
		{
			label_nickname = Label::create(ConvertToString(data->nickname), FONT_TEXT, 20);
			label_nickname->setColor(Color3B::BLACK);
			ctrl_nickname->getPaintNode()->addChild(label_nickname,1,99);
		}else
		{
			label_nickname->setString(ConvertToString(data->nickname));
		}
		//充值积分
		MControl *ctrl_onlineTimes = ctrl->ctrlList.at(3);
		Label* label_onlineTimes =(Label*) ctrl_onlineTimes->getPaintNode()->getChildByTag(99);
		if (label_onlineTimes == nullptr)
		{
			label_onlineTimes = Label::create(ConvertToString(data->onlineTimes), FONT_TEXT, 20);
			label_onlineTimes->setColor(Color3B::BLACK);
			ctrl_onlineTimes->getPaintNode()->addChild(label_onlineTimes,1,99);
		}else
		{
			label_onlineTimes->setString(ConvertToString(data->onlineTimes));
		}

		
		//点赞操作
		MControl *ctrl_toliked = ctrl->ctrlList.at(0);
		ctrl_toliked->setVisible(!data->toLike);


	}



}



void paihangbang_update(Node *node,float dt)
{
	auto form = UIM->getForm(Form_paihangbang);
	

	MControl *ctrl28 = form->getControl(paihangbang_control28);//liked kuang
	MControl *ctrl8 = form->getControl(paihangbang_control8);//big kuang
	MControl *ctrl18 = form->getControl(paihangbang_control18);//super kuang
	MControl *ctrl13 = form->getControl(paihangbang_control13);//ticket kuang
	MControl *ctrl23 = form->getControl(paihangbang_control23);//time kuang

	
	

	MControl *ctrl33 = (MControl*)form->getControl(paihangbang_control33)->getPaintNode();//like ui




	//个人排名信息
	if (isBigSelf)
	{
		MControl *big_rank = (MControl*)form->getControl(paihangbang_control62)->getPaintNode();
		MControl *big_vip = (MControl*)form->getControl(paihangbang_control63)->getPaintNode();
		MControl *big_nickname = (MControl*)form->getControl(paihangbang_control64)->getPaintNode();
		MControl *big_chargeScore = (MControl*)form->getControl(paihangbang_control65)->getPaintNode();
		

		if (bigself != nullptr)
		{
			//rank
			Label* label_big_rank = (Label*)big_rank->getChildByTag(99);
			if(label_big_rank == nullptr){
				label_big_rank = Label::create(ConvertToString(bigself->rank), FONT_TEXT, 20);
				label_big_rank->setColor(Color3B::BLACK);
				big_rank->addChild(label_big_rank,1,99);
			}
			//vip
			UIM->setSkin((MControl*)big_vip->getParent(),bigself->vip);
			//nickname
			Label* label_big_nickname = (Label*)big_nickname->getChildByTag(99);
			if(label_big_nickname == nullptr){
				label_big_nickname = Label::create(ConvertToString(bigself->nickname), FONT_TEXT, 20);
				label_big_nickname->setColor(Color3B::BLACK);
				big_nickname->addChild(label_big_nickname,1,99);
			}
			//chargeScore
			Label* label_big_chargeScore = (Label*)big_chargeScore->getChildByTag(99);
			if(label_big_chargeScore == nullptr){
				label_big_chargeScore = Label::create(ConvertToString(bigself->chargeScore), FONT_TEXT, 20);
				label_big_chargeScore->setColor(Color3B::BLACK);
				big_chargeScore->addChild(label_big_chargeScore,1,99);
			}

			MControl *count = (MControl*)form->getControl(paihangbang_control61)->getPaintNode();
			//count 
			Label* label_count = (Label*)count->getChildByTag(99);
			if(label_count == nullptr){
				label_count = Label::create(ConvertToString(bigCount), FONT_TEXT, 20);
				label_count->setColor(Color3B::BLACK);
				count->addChild(label_count,1,99);
			}
			label_count->setString(ConvertToString(bigCount));
			

		}

		isBigSelf = false;
	}

	//捕鱼达人 个人
	if (isSuperSelf)
	{
		MControl *super_rank = (MControl*)form->getControl(paihangbang_control82)->getPaintNode();
		MControl *super_vip = (MControl*)form->getControl(paihangbang_control83)->getPaintNode();
		MControl *super_nickname = (MControl*)form->getControl(paihangbang_control84)->getPaintNode();
		MControl *super_fishScore = (MControl*)form->getControl(paihangbang_control85)->getPaintNode();

		if (superself != nullptr)
		{
			//rank
			Label* label_super_rank = (Label*)super_rank->getChildByTag(99);
			if(label_super_rank == nullptr){
				label_super_rank = Label::create(ConvertToString(superself->rank), FONT_TEXT, 20);
				label_super_rank->setColor(Color3B::BLACK);
				super_rank->addChild(label_super_rank,1,99);
			}
			//vip
			UIM->setSkin((MControl*)super_vip->getParent(),superself->vip);
			//nickname
			Label* label_super_nickname = (Label*)super_nickname->getChildByTag(99);
			if(label_super_nickname == nullptr){
				label_super_nickname = Label::create(ConvertToString(superself->nickname), FONT_TEXT, 20);
				label_super_nickname->setColor(Color3B::BLACK);
				super_nickname->addChild(label_super_nickname,1,99);
			}
			//fishScore
			Label* label_super_fishScore = (Label*)super_fishScore->getChildByTag(99);
			if(label_super_fishScore == nullptr){
				label_super_fishScore = Label::create(ConvertToString(superself->fishScore), FONT_TEXT, 20);
				label_super_fishScore->setColor(Color3B::BLACK);
				super_fishScore->addChild(label_super_fishScore,1,99);
			}

			MControl *count = (MControl*)form->getControl(paihangbang_control86)->getPaintNode();
			//count 
			Label* label_count = (Label*)count->getChildByTag(99);
			if(label_count == nullptr){
				label_count = Label::create(ConvertToString(superCount), FONT_TEXT, 20);
				label_count->setColor(Color3B::BLACK);
				count->addChild(label_count,1,99);
			}
			label_count->setString(ConvertToString(superCount));
			
		}
		isSuperSelf = false;
	}
	//奖券 个人
	if (isTicketSelf)
	{
		MControl *ticket_rank = (MControl*)form->getControl(paihangbang_control32)->getPaintNode();
		MControl *ticket_vip = (MControl*)form->getControl(paihangbang_control77)->getPaintNode();
		MControl *ticket_nickname =(MControl*) form->getControl(paihangbang_control78)->getPaintNode();
		MControl *ticket_ticket = (MControl*)form->getControl(paihangbang_control79)->getPaintNode();

		if (ticketself != nullptr)
		{
			//rank
			Label* label_ticket_rank = (Label*)ticket_rank->getChildByTag(99);
			if(label_ticket_rank == nullptr){
				label_ticket_rank = Label::create(ConvertToString(ticketself->rank), FONT_TEXT, 20);
				label_ticket_rank->setColor(Color3B::BLACK);
				ticket_rank->addChild(label_ticket_rank,1,99);
			}
			//vip
			UIM->setSkin((MControl*)ticket_vip->getParent(),ticketself->vip);
			
			//nickname
			Label* label_ticket_nickname = (Label*)ticket_nickname->getChildByTag(99);
			if(label_ticket_nickname == nullptr){
				label_ticket_nickname = Label::create(ConvertToString(ticketself->nickname), FONT_TEXT, 20);
				label_ticket_nickname->setColor(Color3B::BLACK);
				ticket_nickname->addChild(label_ticket_nickname,1,99);
			}
			//ticket
			Label* label_ticket_ticket = (Label*)ticket_ticket->getChildByTag(99);
			if(label_ticket_ticket == nullptr){
				label_ticket_ticket = Label::create(ConvertToString(ticketself->ticket), FONT_TEXT, 20);
				label_ticket_ticket->setColor(Color3B::BLACK);
				ticket_ticket->addChild(label_ticket_ticket,1,99);
			}

			MControl *count = (MControl*)form->getControl(paihangbang_control80)->getPaintNode();
			//count 
			Label* label_count = (Label*)count->getChildByTag(99);
			if(label_count == nullptr){
				label_count = Label::create(ConvertToString(ticketCount), FONT_TEXT, 20);
				label_count->setColor(Color3B::BLACK);
				count->addChild(label_count,1,99);
			}
			label_count->setString(ConvertToString(ticketCount));
			

		}
		isTicketSelf = false;
	}
	//在线时间 个人
	if (isTimeSelf)
	{
		MControl *time_rank = (MControl*)form->getControl(paihangbang_control66)->getPaintNode();
		MControl *time_vip = (MControl*)form->getControl(paihangbang_control67)->getPaintNode();
		MControl *time_nickname = (MControl*)form->getControl(paihangbang_control68)->getPaintNode();
		MControl *time_onlineTimes = (MControl*)form->getControl(paihangbang_control69)->getPaintNode();

		if (timeself != nullptr)
		{
			//rank
			Label* label_time_rank = (Label*)time_rank->getChildByTag(99);
			if(label_time_rank == nullptr){
				label_time_rank = Label::create(ConvertToString(timeself->rank), FONT_TEXT, 20);
				label_time_rank->setColor(Color3B::BLACK);
				time_rank->addChild(label_time_rank,1,99);
			}
			//vip
			UIM->setSkin((MControl*)time_vip->getParent(),timeself->vip);
			//nickname
			Label* label_time_nickname = (Label*)time_nickname->getChildByTag(99);
			if(label_time_nickname == nullptr){
				label_time_nickname = Label::create(ConvertToString(timeself->nickname), FONT_TEXT, 20);
				label_time_nickname->setColor(Color3B::BLACK);
				time_nickname->addChild(label_time_nickname,1,99);
			}
			//onlineTimes
			Label* label_time_onlineTimes = (Label*)time_onlineTimes->getChildByTag(99);
			if(label_time_onlineTimes == nullptr){
				label_time_onlineTimes = Label::create(ConvertToString(timeself->onlineTimes), FONT_TEXT, 20);
				label_time_onlineTimes->setColor(Color3B::BLACK);
				time_onlineTimes->addChild(label_time_onlineTimes,1,99);
			}

			MControl *count = (MControl*)form->getControl(paihangbang_control70)->getPaintNode();
			//count 
			Label* label_count = (Label*)count->getChildByTag(99);
			if(label_count == nullptr){
				label_count = Label::create(ConvertToString(timeCount), FONT_TEXT, 20);
				label_count->setColor(Color3B::BLACK);
				count->addChild(label_count,1,99);
			}
			label_count->setString(ConvertToString(timeCount));
			

		}
		isTimeSelf = false;
	}
	//点赞 个人
	if (isLikedSelf)
	{
		MControl *liked_rank = (MControl*)form->getControl(paihangbang_control72)->getPaintNode();
		MControl *liked_vip = (MControl*)form->getControl(paihangbang_control73)->getPaintNode();
		MControl *liked_nickname = (MControl*)form->getControl(paihangbang_control74)->getPaintNode();
		MControl *liked_liked = (MControl*)form->getControl(paihangbang_control75)->getPaintNode();

		if (likedself != nullptr)
		{
			//rank
			Label* label_liked_rank = (Label*)liked_rank->getChildByTag(99);
			if(label_liked_rank == nullptr){
				label_liked_rank = Label::create(ConvertToString(likedself->rank), FONT_TEXT, 20);
				label_liked_rank->setColor(Color3B::BLACK);
				liked_rank->addChild(label_liked_rank,1,99);
			}
			//vip
			UIM->setSkin((MControl*)liked_vip->getParent(),likedself->vip);
			//nickname
			Label* label_liked_nickname = (Label*)liked_nickname->getChildByTag(99);
			if(label_liked_nickname == nullptr){
				label_liked_nickname = Label::create(ConvertToString(likedself->nickname), FONT_TEXT, 20);
				label_liked_nickname->setColor(Color3B::BLACK);
				liked_nickname->addChild(label_liked_nickname,1,99);
			}
			//liked
			Label* label_liked_liked = (Label*)liked_liked->getChildByTag(99);
			if(label_liked_liked == nullptr){
				label_liked_liked = Label::create(ConvertToString(likedself->liked), FONT_TEXT, 20);
				label_liked_liked->setColor(Color3B::BLACK);
				liked_liked->addChild(label_liked_liked,1,99);
			}

			MControl *count = (MControl*)form->getControl(paihangbang_control76)->getPaintNode();
			//count 
			Label* label_count = (Label*)count->getChildByTag(99);
			if(label_count == nullptr){
				label_count = Label::create(ConvertToString(likedCount), FONT_TEXT, 20);
				label_count->setColor(Color3B::BLACK);
				count->addChild(label_count,1,99);
			}
			label_count->setString(ConvertToString(likedCount));
			

		}
		isLikedSelf = false;
	}

	Label* label_IfoText = (Label*)ctrl33->getChildByTag(99);
	if(label_IfoText == nullptr){
		label_IfoText = Label::create(ConvertToString(222), FONT_TEXT, 15);
		label_IfoText->setColor(Color3B::BLACK);
		label_IfoText->setAlignment(TextHAlignment::LEFT);
		label_IfoText->setHeight(((MControl*)ctrl33->getParent())->getSize().height);
		label_IfoText->setWidth(((MControl*)ctrl33->getParent())->getSize().width);
		label_IfoText->setPositionX(((MControl*)ctrl33->getParent())->getSize().width/2);
		label_IfoText->setPositionY(((MControl*)ctrl33->getParent())->getSize().height/2-10);
		ctrl33->addChild(label_IfoText,1,99);
	}

	if (isBig)
	{
		
		MListView *listview = (MListView*)form->getControl(paihangbang_control10);
		listview->clearItems();
		int size = bigranks.size();
		listview->setItemCount(size);

		for (int i = 0; i < size; i++)
		{
			BigRank* data = bigranks.at(i);

			MControl *item = listview->getItem(i);
			item->setUserData(data);
		}
		//位置
		ctrl8->setPosition(Vec2(1239,171));
		ctrl18->setPosition(Vec2(1239,171));
		ctrl28->setPosition(Vec2(1239,171));
		ctrl13->setPosition(Vec2(1239,171));
		ctrl23->setPosition(Vec2(1239,171));

		ctrl8->setPosition(Vec2(239,171));
		

		//介绍
		/*string info_bigRank = "*<土豪榜>每天8点更新，并结算发放排行奖励，直接发送到玩家邮箱\n*<土豪榜>排行榜为玩家每日充值积分总和，充值一元获得一积分\n*<土豪榜>排行榜中，每位玩家可对5名玩家“点赞”，每次可获得200金币奖励\n*<土豪榜>排行榜奖励：第一名：88万金币；第二名：50万金币；第三名：20万金币；第4-10名：5万金币；第11-20名：2万金币";
		label_IfoText->setString(GBKToUTFStr(info_bigRank));*/
		string info_bigRank = GMI->getString("paihangbang","info_bigRank");
		char name[2048];
		memset(name,0,sizeof(name));
		sprintf(name,info_bigRank.c_str(),"<",">","<",">","<",">","<",">");

		label_IfoText->setString(name);

		//获得自己 土豪榜排名
		GSocket->openConnect();
		GSocket->ToRankSelf(1,CmdRank::BIGRANKSELF,bigRankSelfCB);

		isBig = false;

		
	}

	if (isLiked)
	{
		auto form = UIM->getForm(Form_paihangbang);
		MListView *listview = (MListView*)form->getControl(paihangbang_control30);
		listview->clearItems();
		int size = likedranks.size();
		listview->setItemCount(size);

		for (int i = 0; i < size; i++)
		{
			LikedRank* data = likedranks.at(i);

			MControl *item = listview->getItem(i);
			item->setUserData(data);
		}
		ctrl8->setPosition(Vec2(1239,171));
		ctrl18->setPosition(Vec2(1239,171));
		ctrl28->setPosition(Vec2(1239,171));
		ctrl13->setPosition(Vec2(1239,171));
		ctrl23->setPosition(Vec2(1239,171));
		
		ctrl28->setPosition(Vec2(239,171));

		

		//介绍
		/*string info_likedRank = "*<每日之星>每天8点更新，并结算发放排行奖励，直接发送到玩家邮箱\n*<每日之星>排行榜为玩家每日累计获得“赞”的总和\n*<每日之星>排行榜奖励：第一名：10万金币；第二：8万金币；第三名：6万金币；第4-10名：4万金币；第11-20名：2万金币";
		label_IfoText->setString(GBKToUTFStr(info_likedRank));*/
		string info_likedRank = GMI->getString("paihangbang","info_likedRank");
		char name[2048];
		memset(name,0,sizeof(name));
		sprintf(name,info_likedRank.c_str(),"<",">","<",">","<",">");

		label_IfoText->setString(name);

		//获得自己 每日之星排名
		GSocket->openConnect();
		GSocket->ToRankSelf(1,CmdRank::LIKEDRANKSELF,likedRankSelfCB);

		isLiked = false;

		
		
	}

	if (isSuper)
	{
		auto form = UIM->getForm(Form_paihangbang);
		MListView *listview = (MListView*)form->getControl(paihangbang_control20);
		listview->clearItems();
		int size = superranks.size();
		listview->setItemCount(size);

		for (int i = 0; i < size; i++)
		{
			SuperRank* data = superranks.at(i);

			MControl *item = listview->getItem(i);
			item->setUserData(data);
		}
		ctrl8->setPosition(Vec2(1239,171));
		ctrl18->setPosition(Vec2(1239,171));
		ctrl28->setPosition(Vec2(1239,171));
		ctrl13->setPosition(Vec2(1239,171));
		ctrl23->setPosition(Vec2(1239,171));

		ctrl18->setPosition(Vec2(239,171));

		
		

		//介绍
		/*string info_superRank = "*<捕鱼达人>每天8点更新，并结算发放排行奖励，直接发送到玩家邮箱\n*<捕鱼达人>排行榜为玩家每日击杀鱼所获得鱼分总和（只计算获得，不计算消耗）\n*<捕鱼达人>排行榜中，每位玩家可对5名玩家“点赞”，每次可获得200金币奖励\n*<捕鱼达人>排行榜奖励：第一名：15万金币；第二名：10万金币；第三名：8万金币；第4-10名：4万金币；第11-20名：2万金币";
		label_IfoText->setString(GBKToUTFStr(info_superRank));*/
		string info_superRank = GMI->getString("paihangbang","info_superRank");
		char name[2048];
		memset(name,0,sizeof(name));
		sprintf(name,info_superRank.c_str(),"<",">","<",">","<",">","<",">");

		label_IfoText->setString(name);

		//获得自己捕鱼达人排名
		GSocket->openConnect();
		GSocket->ToRankSelf(1,CmdRank::SUPERRANKSELF,superRankSelfCB);

		isSuper = false;


		
	}

	if (isTicket)
	{
		auto form = UIM->getForm(Form_paihangbang);
		MListView *listview = (MListView*)form->getControl(paihangbang_control15);
		listview->clearItems();
		int size = ticketranks.size();
		listview->setItemCount(size);

		for (int i = 0; i < size; i++)
		{
			TicketRank* data = ticketranks.at(i);

			MControl *item = listview->getItem(i);
			item->setUserData(data);
		}
		ctrl8->setPosition(Vec2(1239,171));
		ctrl18->setPosition(Vec2(1239,171));
		ctrl28->setPosition(Vec2(1239,171));
		ctrl13->setPosition(Vec2(1239,171));
		ctrl23->setPosition(Vec2(1239,171));

		ctrl13->setPosition(Vec2(239,171));

		

		//介绍
		/*string info_ticketRank = "*<奖券达人>每天8点更新，并结算发放排行奖励，直接发送到玩家邮箱\n*<奖券达人>排行榜为玩家每日击杀鱼获得奖券总和（只计算获得，不计算消耗\n*<奖券达人>排行榜中，每位玩家可对5名玩家“点赞”，每次可获得200金币奖励\n*<奖券达人>排行榜奖励：第一名：20万金币；第二名：15万金币；第三名：10万金币；第4-10名：4万金币；第11-20名：2万金币";
		label_IfoText->setString(GBKToUTFStr(info_ticketRank));*/
		string info_ticketRank = GMI->getString("paihangbang","info_ticketRank");
		char name[2048];
		memset(name,0,sizeof(name));
		sprintf(name,info_ticketRank.c_str(),"<",">","<",">","<",">","<",">");
		label_IfoText->setString(name);

		//获得自己  奖券榜排名
		GSocket->openConnect();
		GSocket->ToRankSelf(1,CmdRank::TICKETRANKSELF,ticketRankSelfCB);

		isTicket = false;

		
	}

	if (isTime)
	{
		auto form = UIM->getForm(Form_paihangbang);
		MListView *listview = (MListView*)form->getControl(paihangbang_control25);
		listview->clearItems();
		int size = timeranks.size();
		listview->setItemCount(size);

		for (int i = 0; i < size; i++)
		{
			TimeRank* data = timeranks.at(i);

			MControl *item = listview->getItem(i);
			item->setUserData(data);
		}

		ctrl8->setPosition(Vec2(1239,171));
		ctrl18->setPosition(Vec2(1239,171));
		ctrl28->setPosition(Vec2(1239,171));
		ctrl13->setPosition(Vec2(1239,171));
		ctrl23->setPosition(Vec2(1239,171));

		ctrl23->setPosition(Vec2(239,171));

		

		//介绍
		
		string info_timeRank = GMI->getString("paihangbang","info_timeRank");
		char name[2048];
		memset(name,0,sizeof(name));
		sprintf(name,info_timeRank.c_str(),"<",">","<",">","<",">","<",">");

		label_IfoText->setString(name);

		//获得自己  在线榜排名
		GSocket->openConnect();
		GSocket->ToRankSelf(1,CmdRank::TIMERANKSELF,timeRankSelfCB);

		isTime = false;

		
	}
	//form->setUpdateEvent(nullptr);
}
void paihangbang_initialize(Node* node)
{
	UIForm *form = (UIForm*)node;
	form->getControl(paihangbang_control11)->registerPaintEvent(paihangbang_control11_Paint);
	form->getControl(paihangbang_control31)->registerPaintEvent(paihangbang_control31_Paint);
	form->getControl(paihangbang_control16)->registerPaintEvent(paihangbang_control16_Paint);
	form->getControl(paihangbang_control45)->registerPaintEvent(paihangbang_control45_Paint);
	form->getControl(paihangbang_control21)->registerPaintEvent(paihangbang_control21_Paint);
	form->setUpdateEvent(paihangbang_update);

	
	
}




//control3
void paihangbang_control3_Click(Node *node,Touch* ptouch, Event* event){
	//土豪榜

	auto form = UIM->getForm(Form_paihangbang);
	MControl *ctrl3 = form->getControl(paihangbang_control3);//big ui
	MControl *ctrl4 = form->getControl(paihangbang_control4);//ticket ui
	MControl *ctrl5 = form->getControl(paihangbang_control5);//super ui
	MControl *ctrl6 = form->getControl(paihangbang_control6);//time ui
	MControl *ctrl7 = form->getControl(paihangbang_control7);//like ui
	//皮肤
	UIM->setSkin(ctrl3,0);
	UIM->setSkin(ctrl4,0);
	UIM->setSkin(ctrl5,0);
	UIM->setSkin(ctrl6,0);
	UIM->setSkin(ctrl7,0);

	UIM->setSkin(ctrl3,1);

	GSocket->openConnect();
	GSocket->ToRank(1,CmdRank::BIGRANK,bigRankCB);


}
//control4
void paihangbang_control4_Click(Node *node,Touch* ptouch, Event* event){
	//奖券榜
	auto form = UIM->getForm(Form_paihangbang);
	MControl *ctrl3 = form->getControl(paihangbang_control3);//big ui
	MControl *ctrl4 = form->getControl(paihangbang_control4);//ticket ui
	MControl *ctrl5 = form->getControl(paihangbang_control5);//super ui
	MControl *ctrl6 = form->getControl(paihangbang_control6);//time ui
	MControl *ctrl7 = form->getControl(paihangbang_control7);//like ui
	//皮肤
	UIM->setSkin(ctrl3,0);
	UIM->setSkin(ctrl4,0);
	UIM->setSkin(ctrl5,0);
	UIM->setSkin(ctrl6,0);
	UIM->setSkin(ctrl7,0);

	UIM->setSkin(ctrl4,1);

	GSocket->openConnect();
	GSocket->ToRank(1,CmdRank::TICKETRANK,ticketRankCB);
}
//control5
void paihangbang_control5_Click(Node *node,Touch* ptouch, Event* event){
	//捕鱼达人榜
	auto form = UIM->getForm(Form_paihangbang);
	MControl *ctrl3 = form->getControl(paihangbang_control3);//big ui
	MControl *ctrl4 = form->getControl(paihangbang_control4);//ticket ui
	MControl *ctrl5 = form->getControl(paihangbang_control5);//super ui
	MControl *ctrl6 = form->getControl(paihangbang_control6);//time ui
	MControl *ctrl7 = form->getControl(paihangbang_control7);//like ui
	//皮肤
	UIM->setSkin(ctrl3,0);
	UIM->setSkin(ctrl4,0);
	UIM->setSkin(ctrl5,0);
	UIM->setSkin(ctrl6,0);
	UIM->setSkin(ctrl7,0);

	UIM->setSkin(ctrl5,1);
	GSocket->openConnect();
	GSocket->ToRank(1,CmdRank::SUPERRANK,superRankCB);
}
//control6
void paihangbang_control6_Click(Node *node,Touch* ptouch, Event* event){
	//在线时长榜
	auto form = UIM->getForm(Form_paihangbang);
	MControl *ctrl3 = form->getControl(paihangbang_control3);//big ui
	MControl *ctrl4 = form->getControl(paihangbang_control4);//ticket ui
	MControl *ctrl5 = form->getControl(paihangbang_control5);//super ui
	MControl *ctrl6 = form->getControl(paihangbang_control6);//time ui
	MControl *ctrl7 = form->getControl(paihangbang_control7);//like ui
	//皮肤
	UIM->setSkin(ctrl3,0);
	UIM->setSkin(ctrl4,0);
	UIM->setSkin(ctrl5,0);
	UIM->setSkin(ctrl6,0);
	UIM->setSkin(ctrl7,0);

	UIM->setSkin(ctrl6,1);

	GSocket->openConnect();
	GSocket->ToRank(1,CmdRank::TIMERANK,timeRankCB);
}
//control7
void paihangbang_control7_Click(Node *node,Touch* ptouch, Event* event){
	//每日之星
	auto form = UIM->getForm(Form_paihangbang);
	MControl *ctrl3 = form->getControl(paihangbang_control3);//big ui
	MControl *ctrl4 = form->getControl(paihangbang_control4);//ticket ui
	MControl *ctrl5 = form->getControl(paihangbang_control5);//super ui
	MControl *ctrl6 = form->getControl(paihangbang_control6);//time ui
	MControl *ctrl7 = form->getControl(paihangbang_control7);//like ui
	//皮肤
	UIM->setSkin(ctrl3,0);
	UIM->setSkin(ctrl4,0);
	UIM->setSkin(ctrl5,0);
	UIM->setSkin(ctrl6,0);
	UIM->setSkin(ctrl7,0);

	UIM->setSkin(ctrl7,1);

	GSocket->openConnect();
	GSocket->ToRank(1,CmdRank::LIKEDRANK,likedRankCB);
}
//control34
void paihangbang_control34_Click(Node *node,Touch* ptouch, Event* event)
{
	UIM->closeForm(Form_paihangbang,false);
}
//control35
void paihangbang_control35_Click(Node *node,Touch* ptouch, Event* event){
	//big 点赞
	
	MControl *parent =(MControl*) node->getParent();
	BigRank *data = (BigRank*)parent->getUserData();
	if (data != nullptr){
		int id = data->id;
		GSocket->openConnect();
		GSocket->ToGiveLiked(1,CmdRank::LIKE,id,CmdRank::BIGRANK,giveLikedCB);

	}
}
//control26
void paihangbang_control26_Click(Node *node,Touch* ptouch, Event* event){
	//time 点赞
	MControl *parent =(MControl*) node->getParent();
	BigRank *data = (BigRank*)parent->getUserData();
	if (data != nullptr){
		int id = data->id;
		GSocket->openConnect();
		GSocket->ToGiveLiked(1,CmdRank::LIKE,id,CmdRank::TIMERANK,giveLikedCB);

	}
}

//control46
void paihangbang_control46_Click(Node *node,Touch* ptouch, Event* event){
	//ticket 点赞
	MControl *parent =(MControl*) node->getParent();
	BigRank *data = (BigRank*)parent->getUserData();
	if (data != nullptr){
		int id = data->id;
		GSocket->openConnect();
		GSocket->ToGiveLiked(1,CmdRank::LIKE,id,CmdRank::TICKETRANK,giveLikedCB);

	}
}
//control36
void paihangbang_control36_Click(Node *node,Touch* ptouch, Event* event){
	//super 点赞
	MControl *parent =(MControl*) node->getParent();
	BigRank *data = (BigRank*)parent->getUserData();
	if (data != nullptr){
		int id = data->id;
		GSocket->openConnect();
		GSocket->ToGiveLiked(1,CmdRank::LIKE,id,CmdRank::SUPERRANK,giveLikedCB);

	}
}
//control37
void paihangbang_control37_Click(Node *node,Touch* ptouch, Event* event){}
//control38
void paihangbang_control38_Click(Node *node,Touch* ptouch, Event* event){
	//liked 点赞
	//super 点赞
	MControl *parent =(MControl*) node->getParent();
	BigRank *data = (BigRank*)parent->getUserData();
	if (data != nullptr){
		int id = data->id;
		GSocket->openConnect();
		GSocket->ToGiveLiked(1,CmdRank::LIKE,id,CmdRank::LIKEDRANK,giveLikedCB);

	}
}
//control39
void paihangbang_control39_Click(Node *node,Touch* ptouch, Event* event){}
