#include "GameSocketListerner.h"
#include "GameSocket.h"
#include "GameManager.h"
#include "netHelpT.h"

GameSocketListerner::GameSocketListerner()
{

}
GameSocketListerner::~GameSocketListerner()
{

}

void GameSocketListerner::OnClose(Socket* so, bool fromRemote)
{
	CCLOG("%s\n","closed");
	GameSocket::getInstance()->closeScoket();
}
void GameSocketListerner::OnError(Socket* so, const char* e)
{
	CCLOG("%s:%s","error connection",e);
}
void GameSocketListerner::OnIdle(Socket* so)
{
	CCLOG("%s\n","connection idle");
}
void GameSocketListerner::OnMessage(Socket* so, ByteBuf* frame)
{
	frame->ReaderIndex(0);
	//short len = frame->ReadShort();
	short mudelid = frame->ReadShort();
	short cmd = frame->ReadShort();

	std::string str = frame->ReadUTF8();
	str = "["+str+"]";
	if(mudelid == Module::USER){
		switch (cmd)
		{
		case CmdUser::FISH_REGISTER://
			doRegister(str);
			break;
		case CmdUser::FISH_LOGIN://
			doLogin(str);
			break;
		case CmdUser::FISH_NICKNAME:
			doNickname(str);
			break;
		case CmdUser::FISH_RANDOM:
			doRandom(str);
			break;
		case CmdUser::FISH_SIGN:
			doSign(str);
			break;
		}

	}else if (mudelid == Module::RANK)
	{
		switch (cmd)
		{
		case CmdRank::BIGRANK://
			doBigRank(str);
			break;
		case CmdRank::SUPERRANK://
			doSuperRank(str);
			break;
		case CmdRank::TIMERANK:
			doTimeRank(str);
			break;
		case CmdRank::LIKEDRANK:
			doLikedRank(str);
			break;
		case CmdRank::TICKETRANK:
			doTicketRank(str);
			break;


		case CmdRank::BIGRANKSELF:
			doBigRankSelf(str);
			break;
		case CmdRank::SUPERRANKSELF:
			doSuperRankSelf(str);
			break;
		case CmdRank::TIMERANKSELF:
			doTimeRankSelf(str);
			break;
		case CmdRank::LIKEDRANKSELF:
			doLikedRankSelf(str);
			break;
		case CmdRank::TICKETRANKSELF:
			doTicketRankSelf(str);
			break;



		case CmdRank::LIKE:
			doLike(str);
			break;
		}

	}else if (mudelid == Module::MAIL)
	{
		switch (cmd)
		{
		case CmdMail::LOADMAILS:
			doLoadMails(str);
			break;
		case CmdMail::LOADMAIL:
			doLoadMail(str);
			break;
		case CmdMail::DELETEMAIL:
			doDeleteMail(str);
			break;
		case CmdMail::DELETEMAILS:
			doDeleteMails(str);
			break;
		case CmdMail::ACQUIREATM:
			doAcquireAtm(str);
			break;
		case CmdMail::ACQUIREATMS:
			doAcquireAtms(str);
			break;
		}
	}
	
	
	delete frame;
}
void GameSocketListerner::OnOpen(Socket* so)
{
	log("%s","connecting");
	GameSocket::getInstance()->openScoket();
}

void GameSocketListerner::doError( std::string str )
{
	
	log("%s\n",str.c_str());

	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
	{
		const rapidjson::Value &p = _doc[i];  
		int errorCode = p["errorCode"].GetInt();
		std::string info = "";
		switch (errorCode)
		{
		case ErrorCode::ERRORUNKNOWN:
			/*info = "��������æ δ֪����";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORUSEREXIST:
			/*info ="�û����Ѵ���";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORHAVESIGN:
			/*info ="��ǩ��";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORSAMENICKNAME:
			/*info ="�ǳ��Ѵ���";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORRANDOMNICKNAME:
			/*info ="����ǳ�ʧ��";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORSIGNERR:
			/*info ="ǩ��ʧ��";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORLIKED:
			/*info ="����ʧ��";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORRENK:
			/*info ="��ȡ���а�ʧ��";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORRANKSELF:
			/*info ="��ȡ�������а�ʧ��";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORLIKEDFULL:
			/*info ="���յ��޴���������";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORLIKEDEXIST:
			/*info ="���û��ѵ��޹�";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORHAVEATM:
			/*info ="��������ȡ";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORATMALL:
			/*info ="������ȫ����ȡ";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORLOADMAIL:
			/*info ="�����ʼ�ʧ��";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORDELETEMAIL:
		/*	info ="ɾ���ʼ�ʧ��";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		}
		
	}
}

void GameSocketListerner::doResult( std::string str )
{
	log("%s\n",str.c_str());
	rapidjson::Document _doc;  
	_doc.Parse<0>(str.c_str());
	if (_doc.IsArray())
	{
		for (rapidjson::SizeType i = 0; i < _doc.Size(); i++)  
		{
			const rapidjson::Value &p = _doc[i];  
			int result = p["result"].GetInt();
			if(result ==  0){
				doError(str);
				return;
			}
		}

		if(GSocket->pCallBack)
		{
			GSocket->pCallBack(str);
		}
	}
	
}

//////////////////////////////////////////////////////////////////////////
void GameSocketListerner::doRegister(std::string str)
{
	
	doResult(str);
}

void GameSocketListerner::doLogin( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doNickname( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doRandom( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doSign( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doBigRank( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doSuperRank( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doTimeRank( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doLikedRank( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doTicketRank( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doBigRankSelf( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doSuperRankSelf( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doTimeRankSelf( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doLikedRankSelf( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doTicketRankSelf( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doLike( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doLoadMails( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doLoadMail( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doDeleteMail( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doDeleteMails( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doAcquireAtm( std::string str )
{
	doResult(str);
}

void GameSocketListerner::doAcquireAtms( std::string str )
{
	doResult(str);
}
