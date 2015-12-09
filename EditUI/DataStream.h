#ifndef DATASTREAM_H_
#define DATASTREAM_H_
#include "cocos2d.h"
#include <vector>
class DataStream
{
private:
	char *pstr;
	unsigned long offset;
	unsigned long len;
public: 
	DataStream(char *p, unsigned long len);
	~DataStream();
	char readByte();
	short readShort();
	int readInt();
	//clong readLong();
	std::string readString();
	void skip(unsigned long len);
	void setSeek(unsigned long offset);
	char* readData(int len);
	unsigned long getStreamLength();
	void close();
	char* getData();
};
#endif
