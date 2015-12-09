#ifndef GameProtocal_H_
#define GameProtocal_H_
#include "netWork.h"
class GameProtocal :public Protocal 
{
public:
	GameProtocal();
	virtual ~GameProtocal();
	ByteBuf* TranslateFrame(ByteBuf* in);
private:
	int status;
	int h;
	int l;
	short len;
	ByteBuf* frame; 
};
#endif