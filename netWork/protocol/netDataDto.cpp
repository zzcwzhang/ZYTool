#include "netDataDto.h"

BigRank::BigRank()
{

}

BigRank::~BigRank()
{

}

Rank::Rank()
{

}

Rank::~Rank()
{

}

LikedRank::LikedRank()
{

}

LikedRank::~LikedRank()
{

}

TimeRank::TimeRank()
{

}

TimeRank::~TimeRank()
{

}

TicketRank::TicketRank()
{

}

TicketRank::~TicketRank()
{

}

SuperRank::SuperRank()
{

}

SuperRank::~SuperRank()
{

}

MailT::MailT()
{

}

MailT::~MailT()
{

}

Mail::Mail()
{

}

Mail::~Mail()
{

}

void Mail::copyData( MailT* mailT )
{
	this->id = mailT->id;
	this->title = mailT->title;
	this->isRead = mailT->isRead;
	this->time = mailT->time;
}
