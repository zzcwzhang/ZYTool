#ifndef GameSocketListerner_H_
#define GameSocketListerner_H_
#include "netWork.h"


class GameSocketListerner : public SocketListerner
{
public:
	GameSocketListerner();
	virtual ~GameSocketListerner();
	void OnClose(Socket* so, bool fromRemote);
	void OnError(Socket* so, const char* e);
	void OnIdle(Socket* so);
	void OnMessage(Socket* so, ByteBuf* frame);
	void OnOpen(Socket* so);
	//error
	void doError(std::string str);
public:
	//»Øµ÷
	void doResult(std::string str);
	//user
	void doRegister(std::string str);
	void doLogin(std::string str);
	void doNickname(std::string str);
	void doRandom(std::string str);
	void doSign(std::string str);
	//rank
	void doBigRank(std::string str);
	void doSuperRank(std::string str);
	void doTimeRank(std::string str);
	void doLikedRank(std::string str);
	void doTicketRank(std::string str);

	void doBigRankSelf(std::string str);
	void doSuperRankSelf(std::string str);
	void doTimeRankSelf(std::string str);
	void doLikedRankSelf(std::string str);
	void doTicketRankSelf(std::string str);

	void doLike(std::string str);
	//mail
	void doLoadMails(std::string str);
	void doLoadMail(std::string str);
	void doDeleteMail(std::string str);
	void doDeleteMails(std::string str);
	void doAcquireAtm(std::string str);
	void doAcquireAtms(std::string str);


};
#endif