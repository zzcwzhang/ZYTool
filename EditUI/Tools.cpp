#include "zj.h"
const char * vGraySource = "													\n\
						   attribute vec4 a_position;							\n\
						   attribute vec2 a_texCoord;							\n\
						   attribute vec4 a_color;								\n\
						   #ifdef GL_ES											\n\
						   varying mediump vec2 v_texCoord;						\n\
						   varying lowp vec4 v_fragmentColor;					\n\
						   #else												\n\
						   varying vec2 v_texCoord;								\n\
						   varying vec4 v_fragmentColor;						\n\
						   #endif												\n\
						   void main()											\n\
						   {													\n\
						   gl_Position = CC_MVPMatrix * a_position;			\n\
						   v_texCoord = a_texCoord;							\n\
						   v_fragmentColor = a_color;							\n\
						   }													\n\
						   ";
const char * fGraySource = "													\n\
						   #ifdef GL_ES											\n\
						   precision lowp float;								\n\
						   #endif												\n\
						   \n\
						   varying vec2 v_texCoord;								\n\
						   varying vec4 v_fragmentColor;						\n\
						   uniform sampler2D CC_Texture0;						\n\
						   \n\
						   void main()											\n\
						   {													\n\
						   gl_FragColor = texture2D(CC_Texture0, v_texCoord);\n\
						   gl_FragColor.r = texture2D(CC_Texture0, v_texCoord).r * 0.3 + texture2D(CC_Texture0, v_texCoord).g * 0.59 + texture2D(CC_Texture0, v_texCoord).b * 0.11;\n\
						   gl_FragColor.g = texture2D(CC_Texture0, v_texCoord).r * 0.3 + texture2D(CC_Texture0, v_texCoord).g * 0.59 + texture2D(CC_Texture0, v_texCoord).b * 0.11;\n\
						   gl_FragColor.b = texture2D(CC_Texture0, v_texCoord).r * 0.3 + texture2D(CC_Texture0, v_texCoord).g * 0.59 + texture2D(CC_Texture0, v_texCoord).b * 0.11;\n\
						   }													\n\
						   ";
const char * fLightSource = "													\n\
						   #ifdef GL_ES											\n\
						   precision lowp float;								\n\
						   #endif												\n\
						   \n\
						   varying vec2 v_texCoord;								\n\
						   varying vec4 v_fragmentColor;						\n\
						   uniform sampler2D CC_Texture0;						\n\
						   \n\
						   void main()											\n\
						   {													\n\
						   gl_FragColor = texture2D(CC_Texture0, v_texCoord) * 0.5;\n\
						   }													\n\
						   ";
const char * fStrokeSource = "													\n\
							#ifdef GL_ES											\n\
							precision highp float;								\n\
							#endif												\n\
							\n\
							uniform sampler2D u_texture; 								\n\
							varying vec2 v_texCoord; 						\n\
							varying vec4 v_fragmentColor;  						\n\
							const vec2 step = vec2(0.000, 0.000);		\n\
							\n\
							void main()											\n\
							{													\n\
								vec3 color = texture2D(u_texture, v_texCoord).rgb; \n\
								float weight = 0.0; \n\
								float assess = pow(texture2D(u_texture, v_texCoord).a, 1)*weight; \n\
								float alpha = assess;  \n\
								alpha += texture2D( u_texture, v_texCoord.st + vec2( -3.0*step.x, -3.0*step.y ) ).a;	\n\
								alpha += texture2D( u_texture, v_texCoord.st + vec2( -2.0*step.x, -2.0*step.y ) ).a;\n\
								alpha += texture2D( u_texture, v_texCoord.st + vec2( -1.0*step.x, -1.0*step.y ) ).a;\n\
								alpha += texture2D( u_texture, v_texCoord.st + vec2( 0.0 , 0.0) ).a;\n\
								alpha += texture2D( u_texture, v_texCoord.st + vec2( 1.0*step.x,  1.0*step.y ) ).a;\n\
								alpha += texture2D( u_texture, v_texCoord.st + vec2( 2.0*step.x,  2.0*step.y ) ).a; \n\
								alpha += texture2D( u_texture, v_texCoord.st + vec2( 3.0*step.x, -3.0*step.y ) ).a;  \n\
								alpha /= 7.0+assess;\n\
								color = clamp(color + (alpha - 1.0), 0, 1.0);  \n\
								color = pow(color, vec3(3.0, 3.0, 3.0));  \n\
								gl_FragColor = vec4(color.r, color.g, color.b, alpha); \n\
							}													\n\
							";
//const char*  fStrokeSource = "												\n\
//						void main(void)  												\n\
//						{   												\n\
//							//获得当前点的颜色  \n\
//							vec3 color = texture2D(u_texture, v_texCoord).rgb;  \n\
//							//该权值用于自身对结果的影响  \n\
//							float weight = 30.0;  \n\
//							//加入alpha权重，alpha越大，权值assess越小  \n\
//							float assess = pow(texture2D(u_texture, v_texCoord).a, 3)*weight;\n\  
//							//开始计算平均alpha值  
//							float alpha = assess;  \n\
//							//以下为高斯模糊（仅对alpha）  
//							alpha += texture2D( u_texture, v_texCoord.st + vec2( -3.0*step.x, -3.0*step.y ) ).a;\n\  
//							alpha += texture2D( u_texture, v_texCoord.st + vec2( -2.0*step.x, -2.0*step.y ) ).a;\n\ 
//							alpha += texture2D( u_texture, v_texCoord.st + vec2( -1.0*step.x, -1.0*step.y ) ).a;\n\   
//							alpha += texture2D( u_texture, v_texCoord.st + vec2( 0.0 , 0.0) ).a;\n\   
//							alpha += texture2D( u_texture, v_texCoord.st + vec2( 1.0*step.x,  1.0*step.y ) ).a;\n\   
//							alpha += texture2D( u_texture, v_texCoord.st + vec2( 2.0*step.x,  2.0*step.y ) ).a; \n\  
//							alpha += texture2D( u_texture, v_texCoord.st + vec2( 3.0*step.x, -3.0*step.y ) ).a;  \n\ 
//							alpha /= 7.0+assess;  
//							//alpha越大，对颜色影响越小  
//							color = clamp(color + (alpha - 1.0), 0, 1.0);  
//							//进一步加强颜色的区分  
//							color = pow(color, vec3(3.0, 3.0, 3.0));   
//							//输出  
//							gl_FragColor = vec4(color.r, color.g, color.b, alpha);  
//						}   
//						";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID ) //判断当前是否为Android平台 
jstring stoJstring(JNIEnv* env, const char* pat)   
{   
	jclass strClass = env->FindClass("java/lang/String");   
	jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");   
	jbyteArray bytes = env->NewByteArray(strlen(pat));   
	env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);   
	jstring encoding = env->NewStringUTF("utf-8");   
	jstring rstStr =(jstring) env->NewObject(strClass, ctorID, bytes, encoding);  
	return rstStr;  
}  
#endif
DataStream* getInputStream(string str)
{
	DataStream *dis = NULL;
	//获得文件在体系的绝对路径
	std::string ff = FileUtils::getInstance()->fullPathForFilename(str.c_str());
	const char *filepath = ff.c_str();
	//读取的字节数，读取失败则为0
	//CCLog(filepath);
	ssize_t len = 0;
	//读取的内容
	unsigned char* data = FileUtils::getInstance()->getFileData(filepath, "rb", &len);
	dis = new DataStream((char*)data, len);
	return dis;
}
unsigned int srandNum = 0;
int getRandom(int time)
{
	if(srandNum == 0)
	{
		struct  timeval  psv;
		gettimeofday(&psv, nullptr);
		//CCTime::gettimeofdayCocos2d( &psv, nullptr );    // 计算时间种子   
		srandNum = psv.tv_sec * 1000 + psv.tv_usec / 1000;    // 初始化随机数   
		srand(srandNum);
	}
	int result = CCRANDOM_0_1()*time;
	return result;
}

int getSecond()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct timeval now;
	gettimeofday(&now, nullptr);
	struct tm *tm;
	time_t tp = now.tv_sec;
	tm = localtime(&tp);
	return tm->tm_min;
#endif
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	struct tm *tm;  
	time_t timep;  
	time(&timep);  
	tm = localtime(&timep);  
	return tm->tm_sec;
#endif
}

int getMinute()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct timeval now;
	gettimeofday(&now, nullptr);
	struct tm *tm;
	time_t tp = now.tv_sec;
	tm = localtime(&tp);
	return tm->tm_min;
#endif
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	struct tm *tm;  
	time_t timep;  
	time(&timep);  
	tm = localtime(&timep);  
	return tm->tm_min;
#endif
}

int getHour()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct timeval now;
	gettimeofday(&now, nullptr);
	struct tm *tm;
	time_t tp = now.tv_sec;
	tm = localtime(&tp);
	return tm->tm_hour;
#endif
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	struct tm *tm;  
	time_t timep;  
	time(&timep);  
	tm = localtime(&timep);  
	return tm->tm_hour;
#endif
}

int getDay()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct timeval now;
	gettimeofday(&now, nullptr);
	struct tm *tm;
	time_t tp = now.tv_sec;
	tm = localtime(&tp);
	return tm->tm_mday;
#endif
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	struct tm *tm;  
	time_t timep;  
	time(&timep);  
	tm = localtime(&timep);  
	return tm->tm_mday;
#endif
}
int getMonth()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct timeval now;
	gettimeofday(&now, nullptr);
	struct tm *tm;
	time_t tp = now.tv_sec;
	tm = localtime(&tp);
	return tm->tm_mon+1;
#endif
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	struct tm *tm;  
	time_t timep;  
	time(&timep);  
	tm = localtime(&timep);  
	return tm->tm_mon + 1;
#endif
}
int getYear()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	struct timeval now;
	gettimeofday(&now, nullptr);
	struct tm *tm;
	time_t tp = now.tv_sec;
	tm = localtime(&tp);
	return tm->tm_year + 1900;
#endif
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	struct tm *tm;  
	time_t timep;  
	time(&timep);  
	tm = localtime(&timep);  
	return tm->tm_year + 1900;
#endif
}

long long getCurrentTime()  
{ 
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//	struct cc_timeval now;
//	CCTime::gettimeofdayCocos2d(&now, NULL);
//	struct tm *tm;
//	time_t tp = now.tv_sec;
//	tm = localtime(&tp);
//	long tt = tm->tm_sec * 1000L + tm->tm_min * 60 * 1000L + tm->tm_hour * 60 * 60 * 1000L;
//	return tt;
//#endif
//#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
//	struct tm *tm;  
//	time_t timep;  
//	time(&timep);  
//	tm = localtime(&timep);  
//	long tt = tm->tm_sec * 1000L + tm->tm_min * 60 * 1000L + tm->tm_hour * 60 * 60 * 1000L;
//	return tt;
//#endif
	struct timeval now;
	gettimeofday(&now, nullptr);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

short getMonthDay(short month)
{
	switch(month)
	{
	case 1:
		return 31;
	case 2:
		return 28;
	case 3:
		return 31;
	case 4:
		return 30;
	case 5:
		return 31;
	case 6:
		return 30;
	case 7:
		return 31;
	case 8:
		return 31;
	case 9:
		return 30;
	case 10:
		return 31;
	case 11:
		return 30;
	case 12:
		return 31;
	}
	return 0;
}

short getYearDay(short year)
{
	if(year%4==0 && year%100!=0 || year%400==0)
	{
		return 366;
	}
	return 365;
}

int getDayCount(int year1,int month1,int day1,int year2,int month2,int day2)
{
	return (year2 - year1)*getYearDay(year1) + (month2 - month1)*getMonthDay(month1) + day2 - day1;
}

std::string getChargeID()
{
	std::string ss = "zj";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && USE_TALKINGDATA == 1)
	//ss = TDCCTalkingDataGA::getDeviceId();
#endif
	char name[256];
	memset(name,0,sizeof(name));
	sprintf(name,"%s%d%d%d%d%d%d%d%d%d",ss.c_str(),getYear(),getMonth(),getDay(),getHour(),getMinute(),getSecond(),getRandom(10),getRandom(10),getRandom(10));
	return name;
}
//0不弹，1弹，2重置，3作弊
short checkLoginTime(short year, short month, short day)
{
	short dyear = getYear()- year;
	short dMonth = getMonth()- month;
	short dDay = getDay()- day;
	if(dyear == 0)
	{
		if(dMonth == 0)
		{
			if (dDay == 0)
			{
				return 0;
			}
			else if(dDay == 1)
			{
				return 1;
			}
			else if(dDay > 1)
			{
				return 2;//重置
			}
			else
			{
				return 3;//作弊
			}
		}
		else if(dMonth == 1)
		{
			if(getMonthDay(month) == day && getDay() == 1)
			{
				return 1;
			}
			else
			{
				return 2;//重置
			}
		}
		else if(dMonth > 1)
		{
			return 2;//重置
		}
		else
		{
			return 3;//作弊
		}
	}
	else if(dyear == 1)
	{
		if(getMonthDay(month) == day && getDay() == 1 && getMonth() == 1)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else if(dyear > 1)
	{
		return 2;
	}
	else
	{
		return 3;//作弊
	}
}

//字符串分割函数
std::vector<std::string> split(std::string str,std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str+=pattern;//扩展字符串以方便操作
	int size=str.size();

	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(pos<size)
		{
			std::string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}

bool startWith(std::string str,std::string head)
{
	return str.compare(0, head.size(), head) == 0;
	
}
bool endWith(std::string str,std::string tail)
{
	return str.compare(str.size() - tail.size(), tail.size(), tail) == 0;
}

//替换纹理
void changeTextureWithFile(Texture2D *texture,std::string str)
{
	/*Image *img = new Image();
	img->initWithImageFile(str.c_str());
	texture->deleteTexture();
	texture->initWithImage(img);
	CC_SAFE_DELETE(img);*/
}

int getMsecNum(int mSecond,int type)
{
	int msecArray[4] = {0};
	int temp = 0;
	msecArray[MSEC_HOUR] = mSecond/3600000;
	temp = mSecond%3600000;
	msecArray[MSEC_MINUTE] = temp/60000;
	temp = temp%60000;
	msecArray[MSEC_SECOND] = temp/1000;
	msecArray[MSEC_MSEC] = (temp%1000)/10;//舍掉毫秒个位

	return msecArray[type];
}

Node* ColorMask(Node* stencil, Node* content, int x, int y, bool bInverse)
{
	//默认使用stencil中心点对齐
	ClippingNode *clipper = ClippingNode::create();
	//stencil->setAnchorPoint(Vec2(0,1.0f));
	//stencil->setPosition( Vec2(x,y) );

	clipper->setAnchorPoint(Vec2(0,0));
	clipper->setPosition(Vec2(0, 0));
	clipper->setContentSize(Size(S_WIDTH + 100, S_HEIGHT + 100));
	clipper->setStencil(stencil);
	clipper->setInverted(bInverse);

	content->setPosition(Vec2(0, 0));
	content->setAnchorPoint(Vec2(0, 0));
	clipper->addChild(content);
	return clipper;
}

Vec2 getRanPointInScreen()
{
	Vec2 _result = Vec2::ZERO;
// 	int cameraLeft = CAMERA->cameraLeft;
// 	int cameraTop = CAMERA->cameraTop;
// 	Size sceneSize = GMI->curSize;
// 	int ranX = getRandom(S_WIDTH) + cameraLeft - 100;
// 	int ranY = getRandom(S_HEIGHT) +sceneSize.height - (cameraTop + S_HEIGHT);
// 
// 	_result = Vec2(ranX,ranY);

	return _result;
}
int getRollSpeed(int height)
{
	//最小是5
	int i = 5;
	while (true)
	{
		if (height%i == 0)
		{
			break;
		}
		i++;
	}

	return i;
}

int getIndexInVector(std::string value,std::vector<std::string> sVec)
{
	int _result = -1;
	for (int i = 0;i<sVec.size();i++)
	{
		if (value == sVec[i])
		{
			_result = i;
			break;
		}
	}

	return _result;
}

std::string getCoinChargePointStr(int num)
{
	/*std::string tempStr = GMI->getString(std::string("UIText"),std::string("GoldNotEnough"));*/
	std::string tempStr ;
	char name[128];
	memset(name,0,sizeof(name));
	int price = 0;
	int coin = 0;
	if(num <= 5000)
	{
		coin = 5000;
		price = 5;
	}
	else if(num <= 11000)
	{
		coin = 11000;
		price = 10;
	}
	else if(num <= 16500)
	{
		coin = 16500;
		price = 15;
	}
	else
	{
		coin = 23000;
		price = 20;
	}
	sprintf(name,tempStr.c_str(),price,coin);
	return name;
}
std::string getDiamondChargePointStr(int num)
{
/*	std::string tempStr = GMI->getString(std::string("UIText"),std::string("DiamondNotEnough"));*/
	std::string tempStr;
	char name[128];
	memset(name,0,sizeof(name));
	int price = 0;
	int coin = 0;
	if(num <= 60)
	{
		coin = 60;
		price = 5;
	}
	else if(num <= 110)
	{
		coin = 110;
		price = 10;
	}
	else if(num <= 165)
	{
		coin = 165;
		price = 15;
	}
	else
	{
		coin = 230;
		price = 20;
	}
	sprintf(name,tempStr.c_str(),price,coin);
	return name;
}

std::string translateStr(std::string ss,int index)
{
	std::string list= "abcedefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	std::string hashMap1 =  "8gaclmD3EbFnopqftuwx5yvzA1BCGedehkHIJKLMiWjNP24QRSTUXVZ06O7rYs9";
	std::string hashMap2 =  "P4QbRT3UnVYo5Zac8edSefgWX7hip0qrstu6vwAB9CxDE2FGmKLjklIyJMHzNO1";
	std::string hashMap3 =  "m6zDpcByCF8o7Yqr4VWhX9abeEndef0giPklsLMOvwxAGHI1JKQjN5uT2RSt3UZ";
	int len = strlen(ss.c_str());
	std::string encodeStr = "";
	std::string map = "";
	switch (index)
	{
	case 0:
		map = hashMap1;
		break;
	case 1:
		map = hashMap2;
		break;
	default:
		map = hashMap3;
		break;
	} 
	for(int i = 0; i < len;i++)
	{
		char ch = ss.c_str()[i];
		char chs[2] = {0};
		int index = list.find(ch);
		chs[0] = map[index];
		encodeStr.append(chs);
	}
	return ConvertToString(index)+encodeStr;
}

std::string getWeaponTypeIconStr(short wIndex)
{
	std::string str;

	switch (wIndex)
	{
	case 0:
		str = "UI/ACT/weapon_melee.png";
		break;
	case 1:
		str = "UI/ACT/weapon_pistol.png";
		break;
	case 2:
		str = "UI/ACT/weapon_machinegun.png";
		break;
	case 3:
		str = "UI/ACT/weapon_shotgun.png";
		break;
	case 4:
		str = "UI/ACT/weapon_special.png";
		break;
	}

	return str;
}

int getTotalFightingPower()
{
	//战斗力=角色战力*（角色等级/2+0.5)+(武器战力+hero系数）*武器等级+（宠物战力+hero系数）*（宠物等级/2+0.5)
	int fightingPower = 0;
	//人物
	//HeroInf* heroInfo= GData->getHeroInf(HERO->heroIndex);
	//fightingPower += heroInfo->fightingPower * (HERO->getLevel(HERO->heroIndex)/2 + 0.5f);

	////武器
	//for (int i = 0;i < 3;++i)
	//{
	//	Weapon* weapon = HERO->weaponArray[i];
	//	if (weapon)
	//	{
	//		fightingPower += (weapon->fightingPower + HERO->heroIndex+1) * weapon->getLevel();
	//	}
	//}

	////宠物
	//HeroPet* pet = GData->getHeroPet(HERO->petIndex);
	//if (pet)
	//{
	//	fightingPower += (pet->fightingPower + HERO->heroIndex + 1) * (pet->getLevel()/2 + 0.5f);
	//}

	return fightingPower;
}
