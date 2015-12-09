#include "DataStream.h"
DataStream::DataStream(char *p, unsigned long len)
{
	this->pstr = p;
	this->offset = 0;
	this->len = len;
}
DataStream::~DataStream()
{
	
}

char* DataStream::getData()
{
	return this->pstr;
}

char DataStream::readByte()
{
	char ch = *(this->pstr + offset);
	offset++;
	return ch;
}

short DataStream::readShort()
{
	short ch1 =  (short)(readByte()&0xff);
	short ch2 =  (short)(readByte()&0xff);
	return ((ch1<<8)|ch2)&0xffff;
}

//clong DataStream::readLong()
//{
//	short ch1 =  (short)(readByte()&0xff);
//	short ch2 =  (short)(readByte()&0xff);
//	short ch3 =  (short)(readByte()&0xff);
//	short ch4 =  (short)(readByte()&0xff);
//	short ch5 =  (short)(readByte()&0xff);
//	short ch6 =  (short)(readByte()&0xff);
//	short ch7 =  (short)(readByte()&0xff);
//	short ch8 =  (short)(readByte()&0xff);
//	return ((ch1<<56)|(ch1<<48)|(ch2<<40)|(ch3<<32)|(ch1<<24)|(ch2<<16)|(ch3<<8)|ch4)&0xffffffffffffffff;
//}

int DataStream::readInt()
{
	int ch1 =  (int)(readByte()&0xff);
	int ch2 =  (int)(readByte()&0xff);
	int ch3 =  (int)(readByte()&0xff);
	int ch4 =  (int)(readByte()&0xff);
	return ((ch1<<24)|(ch2<<16)|(ch3<<8)|ch4)&0xffffffff;
}

std::string DataStream::readString()
{
	std::string ss;
	int len = readShort();
	char *ch = new char[len+1];

	memset(ch,0,len+1);
	for(int i = 0; i < len ;i++)
	{
		ch[i] = readByte();
	}
	ss = ch;
	delete ch;
	return ss;
}

char* DataStream::readData(int len)
{
	char *data = new char[len];
	memset(data,0,len);
	for(int i = 0; i < len; i++)
	{
		data[i] = readByte();//buffer[tail++];
	}
	return data;
}

void DataStream::skip(unsigned long len)
{
	offset+=len;
}

void DataStream::setSeek(unsigned long offset)
{
	this->offset = offset;
}

unsigned long DataStream::getStreamLength()
{
	return len;
}

void DataStream::close()
{
	if(pstr != NULL)
	{
		delete pstr;
	}
	pstr = NULL;
	delete this;
}
