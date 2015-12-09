#include "GameSocket.h"
#include "GameSocketListerner.h"
#include "GameProtocal.h"
#include "GameManager.h"
#include "cocostudio/WidgetReader/SpriteReader/SpriteReader.h"
#include "json/writer.h"
#include "json/document.h"
#include "FProtocol.h"
GameSocket* GameSocket::_instance = NULL;
GameSocket* GameSocket::getInstance()
{
	if(_instance == NULL)
	{
		_instance = new GameSocket();
	}
	return _instance;
}

GameSocket::GameSocket()
{
	pSocket = NULL;
	isConnect = false;
}
GameSocket::~GameSocket()
{
	
	if(pSocket)
	{
		
		pSocket->Close();
		delete pSocket;
	}
	
}

template <class T> 
void convertFromString(T &value, const std::string &s) {
  std::stringstream ss(s);
   ss >> value;
}
void GameSocket::initScoket(const char* ipAdr,int port)
{

	this->ipAdr = GMI->getString("serverConfig","ip").c_str();
	convertFromString(port,GMI->getString("serverConfig","port"));
	this->port =  port;
	/*this->ipAdr = ipAdr;
	this->port = port;*/
	if(pSocket)
	{
		pSocket->Close();
		delete pSocket;
		pSocket = NULL;
	}
	if(pSocket == NULL){
		pSocket = new Socket();
		SocketListerner* sl = new GameSocketListerner();
		pSocket->SetListerner(sl); //需要定制一个listerner
		pSocket->SetProtocal(new GameProtocal());
		pSocket->Connect(ipAdr, port);
	}
}

void GameSocket::closeScoket()
{
	isConnect = false;
	pSocket->Close();
	pSocket = NULL;
}

void GameSocket::openScoket()
{
	isConnect = true;
}

void GameSocket::openConnect()
{
	if (!isConnect)
	{
		initScoket(FIP,FPORT);
	}
}

//////////////////////////////////////////////////////////////////////////
void GameSocket::registerGame(SocketCallBackFunc callBack)
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("userName", "abctest", allocator);
	document.AddMember("password", "123456", allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::USER);
	f->PutShort(CmdUser::FISH_REGISTER);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}
void GameSocket::loginGame(SocketCallBackFunc callBack)
{
	
}

void GameSocket::signInGame(SocketCallBackFunc callBack)
{
	/*rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	document.AddMember("userId", GMI->userId, allocator);

	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	CCLOG("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(123);
	f->PutShort(123);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;*/
}

void GameSocket::ToRegister( std::string username,std::string password,SocketCallBackFunc callBack )
{
	
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	rapidjson::Value us(username.c_str(),allocator);
	document.AddMember("userName",us , allocator);

	rapidjson::Value ps(password.c_str(),allocator);
	document.AddMember("password",ps , allocator);

	//document.AddMember("userName",sss, allocator);
	//document.AddMember("password",password, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());


	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::USER);
	f->PutShort(CmdUser::FISH_REGISTER);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::ToLogin( std::string username,std::string password,SocketCallBackFunc callBack )
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	
	rapidjson::Value us(username.c_str(),allocator);
	document.AddMember("userName",us , allocator);

	rapidjson::Value ps(password.c_str(),allocator);
	document.AddMember("password",ps , allocator);

	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::USER);
	f->PutShort(CmdUser::FISH_LOGIN);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::ToNickname(int id, std::string nickname,SocketCallBackFunc callBack )
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("id", id, allocator);

	rapidjson::Value nn(nickname.c_str(),allocator);
	document.AddMember("nickname",nn , allocator);

	
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::USER);
	f->PutShort(CmdUser::FISH_NICKNAME);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::ToRandom( int id,SocketCallBackFunc callBack )
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("id", id, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::USER);
	f->PutShort(CmdUser::FISH_RANDOM);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::ToSign( int id,SocketCallBackFunc callBack )
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("id", id, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::USER);
	f->PutShort(CmdUser::FISH_SIGN);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::ToRank( int id,int cmd,SocketCallBackFunc callBack )
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("id", id, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::RANK);
	f->PutShort(cmd);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::ToRankSelf( int id,int cmd,SocketCallBackFunc callBack )
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("id", id, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::RANK);
	f->PutShort(cmd);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::ToGiveLiked( int id,int cmd,int likedId,int type,SocketCallBackFunc callBack )
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("id", id, allocator);
	document.AddMember("likedId", likedId, allocator);
	document.AddMember("type", type, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::RANK);
	f->PutShort(cmd);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::ToLoadMails( int id,SocketCallBackFunc callBack )
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("id", id, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::MAIL);
	f->PutShort(CmdMail::LOADMAILS);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::ToLoadMail( int id,int mailId,SocketCallBackFunc callBack )
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("id", id, allocator);
	document.AddMember("mailId", mailId, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::MAIL);
	f->PutShort(CmdMail::LOADMAIL);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::ToAcquireAtm( int id,int mailId,SocketCallBackFunc callBack )
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("id", id, allocator);
	document.AddMember("mailId", mailId, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::MAIL);
	f->PutShort(CmdMail::ACQUIREATM);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::ToDeleteMail( int id,int mailId,SocketCallBackFunc callBack )
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("id", id, allocator);
	document.AddMember("mailId", mailId, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::MAIL);
	f->PutShort(CmdMail::DELETEMAIL);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::ToDeleteMails( int id,SocketCallBackFunc callBack )
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("id", id, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::MAIL);
	f->PutShort(CmdMail::DELETEMAILS);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::ToHeart( std::string str )
{
	Frame* f=new Frame(1024);
	f->PutShort(Module::HEART);
	f->PutShort(CmdHeart::HEART_HEART);
	f->PutString((char*)str.c_str());
	f->End();
	pSocket->Send(f);
	delete f;
}

void GameSocket::SaveData(int userID,int level,int vipLevel,int coin,int chargeScore,int fishScore,int onlineTime,int prop0,int prop1,SocketCallBackFunc callBack)
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("id", userID, allocator);

	if (level > -1)
	{
		document.AddMember(F_level, level, allocator);
	}

	if (vipLevel > -1)
	{
		document.AddMember(F_vip, vipLevel, allocator);
	}

	if (coin > -1)
	{
		document.AddMember(F_coin, coin, allocator);
	}

	if (chargeScore > -1)
	{
		document.AddMember(F_chargeScore, chargeScore, allocator);
	}

	if (fishScore > -1)
	{
		document.AddMember(F_fishScore, fishScore, allocator);
	}

	if (onlineTime > -1)
	{
		document.AddMember(F_onlineTimes, onlineTime, allocator);
	}

	if (prop0 > -1)
	{
		document.AddMember(F_propTopspeed, prop0, allocator);
	}

	if (prop1 > -1)
	{
		document.AddMember(F_propThousand, prop1, allocator);
	}

	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	pCallBack = callBack;
	Frame* f=new Frame(1024);
	f->PutShort(Module::USER);
	f->PutShort(CmdUser::FISH_SAVE);
	f->PutString((char*)buffer.GetString());
	f->End();
	pSocket->Send(f);
	delete f;
}