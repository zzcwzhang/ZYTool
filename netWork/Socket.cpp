#include "Socket.h"
#include "ByteBuf.h"
#include "Protocal.h"
#include "Frame.h"
#include "SocketListerner.h"
#include "cocos2d.h"
USING_NS_CC;

Socket::Socket():listerner(nullptr),protocal(nullptr)
{
}

Socket::~Socket()
{
    delete this->protocal;
	delete this->listerner;
}

/**
 * 返回sockeid
 * @return 
 */
int Socket::GetSocketId()
{
    return this->sockid;
}

/**
 * 监听器
 * @return 
 */
SocketListerner* Socket::GetListerner()
{
    return this->listerner;
}

Protocal* Socket::GetProtocal()
{
    return this->protocal;
}

void Socket::SetProtocal(Protocal* p)
{
    this->protocal = p;
}

/**
 * 连接服务器
 * @return 
 */
void Socket::Connect(const char* ip, unsigned short port)
{
    this->ip = ip;
    this->port = port;

	#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	WSAStartup(version, &wsaData);
	#endif
	
	this->sockid = socket(AF_INET, SOCK_STREAM, 0);
	log("sockid = %d",this->sockid);
    if (this->sockid != INVALID_SOCKET)
    {
		struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(this->port);
        addr.sin_addr.s_addr = inet_addr(ip);
        if (connect(sockid, (struct sockaddr *) &addr, sizeof (addr)) != SOCKET_ERROR)
		{
			this->listerner->OnOpen(this);
            this->listerner->Start();
        }else
		{
			 this->listerner->OnClose(this, false);
		}
    }
	else
    {
       this->listerner->OnClose(this, false);
    }
}

/**
 * 关闭
 */
int Socket::Close()
{
	if (sockid == -1)
	{
		return -1;
	}
	int t=sockid;
	sockid=-1;
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	shutdown(t, SD_SEND);
	sockid = INVALID_SOCKET;
	WSACleanup();
	return (closesocket(t));
#else
	shutdown(t, SHUT_RDWR);
	return (close(t));
#endif
}

/**
 * 发送内容
 * @param frame
 * @return 
 */
int Socket::Send(ByteBuf* frame)
{
    char* content = frame->GetRaw();
    int bytes;
    int count = 0;
    int len = frame->ReadableBytes();
    while (count < len)
    {
        bytes = send(this->sockid, content + count, len - count, 0);
        if (bytes == -1 || bytes == 0)
            return -1;
        count += bytes;
        frame->ReaderIndex(frame->ReaderIndex() + bytes);
    }
    return count;
}

/**
 * 发送一帧
 * @param frame
 * @return 
 */
int Socket::Send(Frame* frame)
{
    if (frame->IsEnd())
    {
        return this->Send(frame->GetData());
    }
    return 0;
}

/**
 * 设置一个socket状态监听
 * @param listerner
 */
void Socket::SetListerner(SocketListerner* listerner)
{
    this->listerner = listerner;
    this->listerner->SetContext(this);
}