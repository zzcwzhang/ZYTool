#include "GameDataManager.h"
#include "Tools.h"
USING_NS_CC;
GameDataManager* GameDataManager::instance = nullptr;

GameDataManager::GameDataManager()
{
	gold		=	100000;
	lottery		=	0;
	lvl			=	0;
	iconIndex	=	0;

	score       =   0;
	GameCheck   =   1;
	playGrade   =   1;
	playRank    =   0;
	date		=	"";

	hasLogin	=	false;
	nickName	=	"";
}

GameDataManager::~GameDataManager()
{
	levelInfArray.clear();
}

GameDataManager* GameDataManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameDataManager();
	}
	return instance;
}

void GameDataManager::loadGameInfo()
{
	loadLevelInf();
	loadFishInf();
	loadCannonRateInf();
	loadCannonInf();
	loadGradeinf();
	loadRoomInf();
	loadSignRewardInf();
	loadCastInf();
	loadNameInf();
}

void GameDataManager::loadLevelInf()
{
	DataStream *dis = getInputStream("GameData/level.bin");
	int count = dis->readShort();
	for (int i = 0; i < count; i++)
	{
		LevelInf* data = LevelInf::create();
		data->m_id = i;
		data->load(dis);
		levelInfArray.pushBack(data);
		if(i == 0)
		{
			data->isOpen = true;
		}
	}
	dis->close();
}
LevelInf *GameDataManager::getLevelInf(int index)
{
	if (index < 0 || index >= levelInfArray.size())
	{
		return nullptr;
	}
	return levelInfArray.at(index);
}

void GameDataManager::loadFishInf()
{
	DataStream *dis = getInputStream("GameData/fish.bin");
	int count = dis->readShort();
	for (int i = 0; i < count; i++)
	{
		FishInf* data = FishInf::create();
		data->m_id = i;
		data->load(dis);
		fishInfArray.pushBack(data);
	}
	dis->close();
}
FishInf *GameDataManager::getFishInf(int index)
{
	if (index < 0 || index >= fishInfArray.size())
	{
		return nullptr;
	}
	return fishInfArray.at(index);
}

void GameDataManager::loadCannonRateInf()
{
	DataStream *dis = getInputStream("GameData/CannonRate.bin");
	int count = dis->readShort();
	for (int i = 0; i < count; i++)
	{
		CannonRateInf* data = CannonRateInf::create();
		data->m_id = i;
		data->load(dis);
		cannonRateArray.pushBack(data);
		if(i == 0)
		{
			data->bOpen = true;
		}
	}
	dis->close();
}
CannonRateInf *GameDataManager::getCannonRateInf(int index)
{
	if (index < 0 || index >= cannonRateArray.size())
	{
		return nullptr;
	}
	return cannonRateArray.at(index);
}

void GameDataManager::loadCannonInf()
{
	DataStream *dis = getInputStream("GameData/Cannon.bin");
	int count = dis->readShort();
	for (int i = 0; i < count; i++)
	{
		CannonInf* data = CannonInf::create();
		data->m_id = i;
		data->load(dis);
		cannonArray.pushBack(data);
		if(i == 0)
		{
			data->bOpen = true;
		}
	}
	dis->close();
}
CannonInf *GameDataManager::getCannonInf(int index)
{
	if (index < 0 || index >= cannonArray.size())
	{
		return nullptr;
	}
	return cannonArray.at(index);
}

void GameDataManager::loadRoomInf()
{
	DataStream *dis = getInputStream("GameData/RoomInf.bin");
	int count = dis->readShort();
	for (int i = 0; i < count; i++)
	{
		RoomInf* data = RoomInf::create();
		data->m_id = i;
		data->load(dis);
		roomInfArray.pushBack(data);
	}
	dis->close();
}
RoomInf *GameDataManager::getRoomInf(int index)
{
	if (index < 0 || index >= roomInfArray.size())
	{
		return nullptr;
	}
	return roomInfArray.at(index);
}

void GameDataManager::loadGradeinf()
{
	DataStream *dis = getInputStream("GameData/grade.bin");
	int count = dis->readShort();
	for (int i = 0; i < count; i++)
	{
		GradeInf* data = GradeInf::create();
		data->m_id = i;
		data->load(dis);
		gradeArray.pushBack(data);
	}
	dis->close();
}

GradeInf* GameDataManager::getGradeInf( int index )
{
	if (index < 0 || index >= gradeArray.size())
	{
		return nullptr;
	}
	return gradeArray.at(index);
}

void GameDataManager::loadCastInf()
{
	DataStream *dis = getInputStream("GameData/cast.bin");
	int count = dis->readShort();
	for (int i = 0; i < count; i++)
	{
		CastInf* data = CastInf::create();
		data->m_id = i;
		data->load(dis);
		castArray.pushBack(data);
	}
	dis->close();
}

CastInf* GameDataManager::getCastInf( int index )
{
	if (index < 0 || index >= castArray.size())
	{
		return nullptr;
	}
	return castArray.at(index);
}


void GameDataManager::loadSignRewardInf()
{
	DataStream *dis = getInputStream("GameData/jiangdaojiangli.bin");
	int count = dis->readShort();
	for (int i = 0; i < count; i++)
	{
		SignReward* data = SignReward::create();
		data->m_id = i;
		data->load(dis);
		signRewardArray.pushBack(data);
	}
	dis->close();
}

SignReward* GameDataManager::getSignRewardInf(int index)
{
	if (index < 0 || index >= signRewardArray.size())
	{
		return nullptr;
	}
	return signRewardArray.at(index);
}

void GameDataManager::loadNameInf()
{
	DataStream *dis = getInputStream("GameData/firstName.bin");
	int count = dis->readShort();
	for (int i = 0; i < count; i++)
	{
		FamilyName* data = FamilyName::create();
		data->m_id = i;
		data->load(dis);
		familyNameArray.pushBack(data);
	}
	dis->close();

	dis = getInputStream("GameData/lastNameMale.bin");
	count = dis->readShort();
	for (int i = 0; i < count; i++)
	{
		OtherName* data = OtherName::create();
		data->m_id = i;
		data->load(dis);
		maleNameArray.pushBack(data);
	}
	dis->close();

	dis = getInputStream("GameData/lastNameFemale.bin");
	count = dis->readShort();
	for (int i = 0; i < count; i++)
	{
		OtherName* data = OtherName::create();
		data->m_id = i;
		data->load(dis);
		femaleNameArray.pushBack(data);
	}
	dis->close();
}
std::string GameDataManager::getFamilyName(int index)
{
	if (index < 0 || index >= familyNameArray.size())
	{
		return "";
	}
	return familyNameArray.at(index)->txt;
}
std::string GameDataManager::getMaleName(int index)
{
	if (index < 0 || index >= maleNameArray.size())
	{
		return "";
	}
	return maleNameArray.at(index)->txt;
}
std::string GameDataManager::getFemaleName(int index)
{
	if (index < 0 || index >= femaleNameArray.size())
	{
		return "";
	}
	return femaleNameArray.at(index)->txt;
}






int GameDataManager::getYear()
{
	auto svec = split(this->date,"-");
	if (svec.size() > 0)
	{
		return atoi(svec.at(0).c_str());
	}

	return 0;
}

int GameDataManager::getMonth()
{
	auto svec = split(this->date,"-");
	if (svec.size() > 1)
	{
		return atoi(svec.at(1).c_str());
	}

	return 0;
}

int GameDataManager::getDay()
{
	auto svec = split(this->date,"-");
	if (svec.size() > 2)
	{
		return atoi(svec.at(2).c_str());
	}

	return 0;
}