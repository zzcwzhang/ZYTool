#ifndef Tools_H_
#define Tools_H_
#include "zj.h"
class GameData;

enum
{
	MSEC_HOUR = 0,
	MSEC_MINUTE,
	MSEC_SECOND,
	MSEC_MSEC
};
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //判断当前是否为Android平台 
jstring stoJstring(JNIEnv* env, const char* pat);
#endif
DataStream* getInputStream(std::string str);
int getRandom(int time);
int getYear();
int getMonth();
int getDay();
int getHour();
int getMinute();
int getSecond();
long long getCurrentTime();
std::string getChargeID();

short getMonthDay(short month);
short getYearDay(short year);
int getDayCount(int year1,int month1,int day1,int year2,int month2,int day2);
short checkLoginTime(short year, short month, short day);

//字符串分割函数
std::vector<std::string> split(std::string str,std::string pattern);

bool startWith(std::string str,std::string head);
bool endWith(std::string str,std::string tail);

std::string getCoinChargePointStr(int num);
std::string getDiamondChargePointStr(int num);

//替换纹理
void changeTextureWithFile(Texture2D *texture,std::string str);

template <class T> 
std::string ConvertToString(T value) {
	  std::stringstream ss;
	  std::string str;
	  ss << value;
	  ss>>str;
	  return str;
}

int getMsecNum(int mSecond,int type);

Vec2 getRanPointInScreen();

Node* ColorMask(Node* stencil,Node* content,int x,int y,bool bInverse);

int getRollSpeed(int height);

std::string translateStr(std::string ss,int index);

int getIndexInVector(std::string value,std::vector<std::string> sVec);

std::string getWeaponTypeIconStr(short wIndex);

int getTotalFightingPower();

extern const char * vGraySource;
extern const char * fGraySource;
extern const char * fLightSource;
extern const char*  fStrokeSource;
#endif
