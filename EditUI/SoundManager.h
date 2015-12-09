#ifndef SoundManager_H_
#define SoundManager_H_
#include "cocos2d.h"
class SoundMap:public cocos2d::Ref
{
public:
	char m_name[64];
	unsigned int m_playId;
	bool m_bEffect;//�Ƿ���Ч
public:
	SoundMap();
	SoundMap(char *name,bool bEffect);
	~SoundMap();
};
class SoundManager
{
public:
	bool m_bMusicPlayer;
	bool m_bEffectPlayer;
	static SoundManager *manager;
	static SoundManager* getInstance();
	~SoundManager();
	void initSoundRes();
	void loadSound(const char *soundName, bool isEffect);
	void playSound(const char* name,bool bLoop);
	void stopSound(const char* name);
	void setSoundVolum(float volum, bool isEffect);
	void releaseSound(const char *name);//�ͷ������ļ����ͷ�ǰ��ֹͣ���ֲ���
	void clearAllSound();
	bool isSoundIsPlaying(const char *name);
	void disableSound();
	void enableSound();
private:
	SoundManager();
	SoundMap* _search(const char *name);
private:
	cocos2d::Vector<SoundMap*> pSoundList;
};
#define SMI (SoundManager::getInstance())
#endif