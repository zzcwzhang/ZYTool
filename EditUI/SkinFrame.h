#ifndef SkinFrame_H_
#define SkinFrame_H_
#include "SkinItem.h"
class SkinFrame
{
public:
	SkinFrame();
	~SkinFrame();
	short m_delay;
	void loadFrame(DataStream *dis);
	void loadRes();
	short itemCount;
	SkinItem **items;
};
#endif