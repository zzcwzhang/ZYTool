#include "GameData.h"
#include "Tools.h"
LevelInf::LevelInf()
{
	isOpen = false;
	missionCount = 0;
}

LevelInf::~LevelInf()
{

}

void LevelInf::load(DataStream *dis)
{
	GameData::load(dis);
	this->reward = dis->readInt()/100;
	std::string str = dis->readString();
	if(str.compare("") != 0)
	{
		std::vector<std::string> list = split(str,",");

		for (int i = 0; i < list.size(); i += 3)
		{
			std::string s = list[i];
			int index = atoi(s.c_str());
			s = list[i + 1];
			int id = atoi(s.c_str());
			s = list[i + 2];
			int count = atoi(s.c_str());
			//targets.push_back(index);
			targets.push_back(id);
			//targets.push_back(count);
		}
	}
	str.clear();
	missionCount = dis->readInt()/100;
}
//////////////////////////////////////////////////////////////////////////
FishInf::FishInf()
{
	
}

FishInf::~FishInf()
{

}

void FishInf::load(DataStream *dis)
{
	GameData::load(dis);
	this->rate = dis->readInt()/100;
	this->hp = dis->readInt()/100;
	this->minSpeed = dis->readInt()/100.0f;
	this->maxSpeed = dis->readInt()/100.0f;
	fishname = dis->readString();
	jiangquan = dis->readInt()/100;
}
//////////////////////////////////////////////////////////////////////////
CannonRateInf::CannonRateInf()
{
	bOpen = false;
}

CannonRateInf::~CannonRateInf()
{

}

void CannonRateInf::load(DataStream *dis)
{
	GameData::load(dis);
	this->rate = dis->readInt()/100;
	this->openCoin = dis->readInt()/100;
	this->consume = dis->readInt()/100;
}
//////////////////////////////////////////////////////////////////////////
void CannonInf::load(DataStream *dis)
{
	GameData::load(dis);
	this->power = dis->readInt()/100.0f;
	this->price = dis->readInt()/100;
	cannonName = dis->readString();
	atkSpeed = dis->readInt()/100.0f;
	atkTime = dis->readInt()/100;
}

///////////////////////////////////////////////////////////////////////////

void GradeInf::load( DataStream *dis )
{
	GameData::load(dis);
	this->upReward = dis->readInt()/100;
	upScore = dis->readInt()/100;
}

//////////////////////////////////////////////////////////////////////////
void RoomInf::load(DataStream *dis)
{
	GameData::load(dis);
	this->minCoin = dis->readInt()/100;
	this->cannonRateIndex = dis->readInt();
	this->vip = dis->readInt()/100;
	rp = dis->readInt()/100.0f;
}
///////////////////////////////////////////////////////////////////////////
void SignReward::load(DataStream *dis)
{
	GameData::load(dis);
	this->goldCount = dis->readInt()/100;
}
//////////////////////////////////////////////////////////////////////////
void FamilyName::load(DataStream *dis)
{
	GameData::load(dis);
	txt = dis->readString();
}
//////////////////////////////////////////////////////////////////////////
void OtherName::load(DataStream *dis)
{
	GameData::load(dis);
	txt = dis->readString();
}
//////////////////////////////////////////////////////////////////////////
void CastInf::load( DataStream *dis )
{
	GameData::load(dis);
	this->buygold = dis->readInt()/100;
	this->buyworth = dis->readInt()/100;
	this->count = dis->readInt()/100;
}
