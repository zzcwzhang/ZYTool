#include "GameManager.h"
#include "Player.h"
#include "MD5.h"
#include "cocos2d/external/json/stringbuffer.h"
#include "cocos2d/external/json/writer.h"
#include "cocos2d/external/json/document.h"

GameManager* GameManager::manager = nullptr;
GameManager* GameManager::getInstance()
{
	if(!manager)
	{
		manager = new GameManager();
	}
	return manager;
}

GameManager::GameManager()
{
	bSingleMode = true;
	runData = new RunTimeData();
	_self = nullptr;
}
GameManager::~GameManager()
{
	delete runData;
}

void GameManager::clearRunData()
{
	runData->curRoomIndex = -1;
}

void GameManager::encryption()
{
	
}

void GameManager::setMySelf(Player * player)
{
	if(_self)
	{
		return;
	}
	_self = player;
	player->setMachine(false);
	player->retain();
}

Player* GameManager::getMySelf()
{
	return _self;
}

void GameManager::setRoom(Room * room)
{
	_curRoom = room;
}
Room* GameManager::getRoom()
{
	return _curRoom;
}

bool GameManager::isSingleMode()
{
	return bSingleMode;
}
void GameManager::setSingleMode(bool flag)
{
	bSingleMode= flag;
}

void GameManager::loadText()
{
	textDict = FileUtils::getInstance()->getValueMapFromFile("Text/Text.plist");
}
cocos2d::ValueMap GameManager::getTextDict(std::string key)
{
	return textDict.at(key).asValueMap();
}
std::string GameManager::getString(std::string dictKey,std::string key)
{
	ValueMap dict = getTextDict(dictKey); 
	return dict.at(key).asString();
}

void GameManager::saveRecord()
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	//test
	rapidjson::Value rootValue(rapidjson::kObjectType);
	rootValue.AddMember("test",123,allocator);



	document.AddMember("res",rootValue,allocator);
	//MD5
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	log("%s",buffer.GetString());
	std::string str = buffer.GetString();
	long len = str.length();
	unsigned char md5code[16];
	MD5Digest((char*)str.c_str(),len,(char*)md5code);
	std::string outPutPath = CCFileUtils::sharedFileUtils()->getWritablePath();
	std::string fileName("catchfish_temp.rec");
	std::string fullPath = outPutPath+fileName;

	FILE *fp =fopen(fullPath.c_str(),"wb");
	if(fp)
	{
		fwrite(str.c_str(), len, 1 ,fp);
		fwrite(md5code,sizeof(unsigned char),16,fp);
		fclose(fp);
	}

	std::string oldFile = outPutPath.append("catchfish.rec");
	remove(oldFile.c_str());
	rename(fullPath.c_str(),oldFile.c_str());
}

bool GameManager::readRecord()
{
	bool bRet =false;
	unsigned char md5Code[17];
	memset(md5Code,0,sizeof(md5Code));
	char name[64];
	sprintf(name,"catchfish.rec");
	std::string outPutPath = CCFileUtils::sharedFileUtils()->getWritablePath();
	std::string fileName(name);
	std::string fullPath = outPutPath+fileName;
	char* pBuf = NULL;
	long len = 0;
	FILE *fp =fopen(fullPath.c_str(),"rb");
	if(fp)
	{
		//¨¨?¦Ì?¦Ì¡À?¡ã???t¨¢¡Â¦Ì??¨¢¨¨?????
		long cur_pos = ftell( fp );
		//?????t¨¢¡Â¦Ì??¨¢¨¨?????¨¦¨¨?a???t???2
		fseek( fp, 0, SEEK_END );
		//??¨¨????t???2¦Ì??¨¢¨¨?????,?¡ä???t¡ä¨®D?
		len = ftell( fp );//??¨¨£¤1???¨¢?2¡¤?
		//?????t¨¢¡Â¦Ì??¨¢¨¨??????1?-?a?-?¨¨¦Ì??¦Ì
		fseek( fp, cur_pos, SEEK_SET );
		pBuf = new char[len - 16 + 1];
		memset(pBuf,0,len - 16 + 1);
		fread(pBuf,sizeof(char),len - 16,fp);
		fread(md5Code,sizeof(unsigned char),16,fp);
		fclose(fp);
	}
	else
	{
		return false;
	}
	log("%s",pBuf);
	unsigned char md5temp[17];
	memset(md5temp,0,sizeof(md5temp));
	MD5Digest((char*)pBuf,len - 16,(char*)md5temp);
	if(strcmp((char*)md5temp,(char*)md5Code) != 0)
	{
		return false;
	}
	rapidjson::Document _doc;  
	_doc.Parse<0>(pBuf);
	delete pBuf;
	pBuf = NULL;
	const rapidjson::Value &rec = _doc["res"];

	//begin read data

	return bRet;
}