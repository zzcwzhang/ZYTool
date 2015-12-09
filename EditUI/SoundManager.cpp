#include "SoundManager.h"
#include "SimpleAudioEngine.h"
#include <map>
USING_NS_CC;
using namespace CocosDenshion;
SoundMap::SoundMap()
{
	memset(m_name,0,sizeof(m_name));
	m_playId= -1;
	m_bEffect = false;
	this->autorelease();
}
SoundMap::SoundMap(char *name,bool bEffect)
{
	memset(m_name,0,sizeof(m_name));
	int len = strlen(name);
	memcpy(m_name,name,sizeof(char)*len);
	m_bEffect = bEffect;
	this->autorelease();
}
SoundMap::~SoundMap()
{

}
//////////////////////////////////////////////////////////////////////////
SoundManager* SoundManager::manager = NULL;
SoundManager::SoundManager()
{
	m_bMusicPlayer = true;
	m_bEffectPlayer = true;
}

SoundManager::~SoundManager()
{
	pSoundList.clear();
}

SoundManager* SoundManager::getInstance()
{
	if(!manager)
	{
		manager = new SoundManager;
	}
	return manager;
}

void SoundManager::initSoundRes()
{
	loadSound("bgm0.mp3",false);
	loadSound("bgm1.mp3",false);
	loadSound("bgm2.mp3",false);
	loadSound("bgm3.mp3",false);
	loadSound("fengmian_bgm.mp3",false);

	loadSound("anniu.mp3",true);
	loadSound("cannon_fire0.mp3",true);
	loadSound("cannon_fire1.mp3",true);
	loadSound("cannon_fire2.mp3",true);
	loadSound("cannon_fire3.mp3",true);
	loadSound("cannon_fire4.mp3",true);
	loadSound("cannon_fire5.mp3",true);

	loadSound("fengmian_paopao.mp3",true);

	loadSound("guoguan.mp3",true);
	loadSound("qiandaojinbi.mp3",true);
	loadSound("shenji.mp3",true);
	loadSound("yuchao.mp3",true);
}

void SoundManager::loadSound(const char *soundName, bool isEffect)
{
	SoundMap *map = _search((char*)soundName);
	if(map)
	{
		log("already exsist Sound %s",soundName);
		return;
	}
	map = new SoundMap((char*)soundName,isEffect);
	pSoundList.pushBack(map);
	std::string fileName = "Music/";
	fileName.append(soundName);
	std::string ff = FileUtils::getInstance()->fullPathForFilename(fileName.c_str());
	if(isEffect)
	{
		SimpleAudioEngine::getInstance()->preloadEffect(ff.c_str());
	}
	else
	{
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(ff.c_str());
	}
}

void SoundManager::playSound(const char* name,bool bLoop)
{
	SoundMap *map = _search((char*)name);
	if(!map)
	{
		log("no found file %s",name);
		return;
	}
	std::string fileName = "Music/";
	fileName.append(map->m_name);
	std::string ff = FileUtils::getInstance()->fullPathForFilename(fileName.c_str());
	if(map->m_bEffect)
	{
		if(!m_bEffectPlayer)
		{
			return;
		}
		unsigned int rt = SimpleAudioEngine::getInstance()->playEffect(ff.c_str(), bLoop);
		map->m_playId = rt;
	}
	else
	{
		if(!m_bMusicPlayer)
		{
			return;
		}
		SimpleAudioEngine::getInstance()->playBackgroundMusic(ff.c_str(), bLoop);
	}
}

bool SoundManager::isSoundIsPlaying(const char *name)
{
	SoundMap *map = _search((char*)name);
	if(!map)
	{
		log("no such file: %s",name);
		return false;
	}
	if(map->m_bEffect)
	{
		return false;
		//return SimpleAudioEngine::sharedEngine()->getEffectIsPlaying(map->m_playId);
	}
	else
	{
		return SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
	}
}

void SoundManager::stopSound(const char* name)
{
	SoundMap *map = _search((char*)name);
	if(!map)
	{
		log("no such file: %s",name);
		return;
	}
	if(map->m_bEffect)
	{
		if(map->m_playId >= 0)
		{
			SimpleAudioEngine::getInstance()->stopEffect(map->m_playId);
		}
		else
		{
			log("Music %s is not playing",name);
		}

	}
	else
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
}

void SoundManager::setSoundVolum(float volum, bool isEffect)
{
	if(isEffect)
	{
		SimpleAudioEngine::getInstance()->setEffectsVolume(volum);
	}
	else
	{
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volum);
	}
}

void SoundManager::clearAllSound()
{
	pSoundList.clear();
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
}

void SoundManager::releaseSound(const char *name)
{
	SoundMap *map = _search((char*)name);
	if(!map)
	{
		log("no such file: %s",name);
		return;
	}
	
	if(map->m_bEffect)
	{
		std::string ff = FileUtils::getInstance()->fullPathForFilename(map->m_name);
		SimpleAudioEngine::getInstance()->unloadEffect(ff.c_str());
	}
	else
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	}
	pSoundList.eraseObject(map);
}

SoundMap* SoundManager::_search(const char *name)
{
	int count = pSoundList.size();
	for (int i = 0; i < count; i++)
	{
		SoundMap *map = (SoundMap*)pSoundList.at(i);
		if(strcmp(map->m_name,name) == 0)
		{
			return map;
		}
	}
	return NULL;
}

void SoundManager::disableSound()
{
	setSoundVolum(0.0f,true);
	setSoundVolum(0.0f,false);
}

void SoundManager::enableSound()
{
	setSoundVolum(1.0f,true);
	setSoundVolum(1.0f,false);
}