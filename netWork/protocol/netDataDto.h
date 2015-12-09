#ifndef NETDATADTO_H
#define	NETDATADTO_H
#include "string"
#include "cocos2d.h"
USING_NS_CC;

using namespace std;
/************************************************************************/
/* 排行榜 模型数据                                                                     */
/************************************************************************/
class Rank : public Ref
{
public:
	Rank();
	~Rank();

public:
	int id;
	int rank;
	int vip;
	string nickname;
	bool toLike;
	int count;
};



class BigRank : public Rank
{
public:
	BigRank();
	~BigRank();

public:
	int chargeScore;

};

class SuperRank : public Rank
{
public:
	SuperRank();
	~SuperRank();

public:
	int fishScore;
};

class LikedRank : public Rank
{
public:
	LikedRank();
	~LikedRank();

public:
	int liked;
};

class TimeRank : public Rank
{
public:
	TimeRank();
	~TimeRank();

public:
	int onlineTimes;
};

class TicketRank : public Rank
{
public:
	TicketRank();
	~TicketRank();

public:
	int ticket;
};



/************************************************************************/
/* 邮件 模型数据                                                                     */
/************************************************************************/
class MailT : public Ref
{
public:
	MailT();
	~MailT();

public:
	int id;
	string title;
	string time;
	bool isRead;
};

class Mail : public MailT
{
public:
	Mail();
	~Mail();

public:
	string content;
	bool isReceivced;
	int atmType;
	int atmCount;
public:
	void copyData(MailT* mailT);
};

#endif