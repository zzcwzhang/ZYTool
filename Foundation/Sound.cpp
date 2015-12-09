//
//  Sound.cpp
//  paigow-ipad
//
//  Created by ryt on 13-5-14.
//
//

#include "Sound.h"

Sound::Sound()
{
    
}

static Sound* sd = NULL;
Sound::~Sound()
{
    delete sd;
}

Sound* Sound::Instance()
{
    if (sd==NULL) {
        sd = new Sound();
    }
    return sd;
}

void Sound::playMusic(const char* file)
{
//    stopMusic();
    if (file != NULL /*&& !isCloseSound_*/)
    {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(file, true);
    }
}

int Sound::playEffect(const char* file, bool aLoop)
{
    if (file != NULL && !isCloseSound_)
    {
        return SimpleAudioEngine::sharedEngine()->playEffect(file, aLoop);
    }
    return -1;
}

void Sound::stopEffect(int aEffectId)
{
    SimpleAudioEngine::sharedEngine()->stopEffect(aEffectId);
}

//void Sound::stopMusic()
//{
//    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
//}

void Sound::pauseMusic()
{
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void Sound::resumeMusic()
{
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void Sound::setCloseSound(bool aIsClose)
{
    isCloseSound_ = aIsClose;
    if (isCloseSound_)
    {
        /*pauseMusic();*/
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
    }
    else
    {
        /*resumeMusic();*/
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
    }
//    if (isCloseSound_) {
//        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
//        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
//
//    } else {
//        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
//        SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
//
//    }
}

void Sound::switchSound()//背景音乐
{
    this->setCloseSound(!isCloseSound_);
}

void Sound::switchSound0()//音效
{
	isCloseSound0_ = !isCloseSound0_;
	if (isCloseSound0_)
	{
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
	}
	
}


void Sound::initSound()
{
//    bool isCloseAllVoice_ = CCUserDefault::sharedUserDefault()->getBoolForKey("isCloseAllVoice", false);
//    isCloseSound_ = CCUserDefault::sharedUserDefault()->getBoolForKey("isCloseSound", false);
//    int musicVolume_ = CCUserDefault::sharedUserDefault()->getIntegerForKey("musicVolume", 118);
//    int effectVolume_ = CCUserDefault::sharedUserDefault()->getIntegerForKey("effectVolume", 118);
//    musicVolume_ = musicVolume_ >= 118 ? 118 : musicVolume_;
//    musicVolume_ = musicVolume_ <= 9 ? 9 : musicVolume_;
//    effectVolume_ = effectVolume_ >= 118 ? 118 : effectVolume_;
//    effectVolume_ = effectVolume_ <= 9 ? 9 : effectVolume_;
//    if (isCloseAllVoice_)
//    {
//        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
//        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
//    }
//    else
//    {
//        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume((musicVolume_ - 9) / 100.0f);
//        SimpleAudioEngine::sharedEngine()->setEffectsVolume((effectVolume_ - 9) / 100.0f);
//    }
    isCloseSound_ = false;
	isCloseSound0_ = false;
    
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0f);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
}

