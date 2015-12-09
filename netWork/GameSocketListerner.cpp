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
			/*info = "服务器繁忙 未知错误";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORUSEREXIST:
			/*info ="用户名已存在";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORHAVESIGN:
			/*info ="已签到";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORSAMENICKNAME:
			/*info ="昵称已存在";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORRANDOMNICKNAME:
			/*info ="随机昵称失败";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORSIGNERR:
			/*info ="签到失败";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORLIKED:
			/*info ="点赞失败";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORRENK:
			/*info ="获取排行榜失败";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORRANKSELF:
			/*info ="获取个人排行榜失败";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORLIKEDFULL:
			/*info ="今日点赞次数已用完";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORLIKEDEXIST:
			/*info ="此用户已点赞过";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORHAVEATM:
			/*info ="附件已领取";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORATMALL:
			/*info ="附件已全部领取";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORLOADMAIL:
			/*info ="加载邮件失败";
			CCLOG("%s\n",GBKToUTF(info));*/
			break;
		case ErrorCode::ERRORDELETEMAIL:
		/*	info ="删除邮件失败";
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
