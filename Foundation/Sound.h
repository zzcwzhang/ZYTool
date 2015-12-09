//
//  Sound.h
//  paigow-ipad
//
//  Created by ryt on 13-5-14.
//
//

#ifndef __paigow_ipad__Sound__
#define __paigow_ipad__Sound__

//#include "headerLibrary.h"
#include "SimpleAudioEngine.h"
#include <map>
using namespace std;
using namespace CocosDenshion;

class Sound{
public:
    Sound();
    virtual ~Sound();
    static Sound* Instance();
    
private:
    //CCDictionary *dic_sound;
    
public:
    void initSound();

    void playMusic(const char* file);
//    void stopMusic();
    void pauseMusic();
    void resumeMusic();

    int playEffect(const char* file, bool aLoop = false);
    
    
    void stopEffect(int aEffectId);
    
    // 设置是否播放语音
    void switchSound();
	//设置是否播放音效
	void switchSound0();
    
    bool getIsCloseSound()
    {
        return isCloseSound_;
    };
    
private:
    void setCloseSound(bool aIsClose);
    
    
public:
    bool   isCloseSound_;
	bool   isCloseSound0_;
};

#endif /* defined(__paigow_ipad__Sound__) */
