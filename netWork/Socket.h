#ifndef SOCKET_H
#define	SOCKET_H
#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#pragma comment(lib, "wsock32")
#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <WS2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif
#include <string>
class ByteBuf;
class Frame;
class Protocal;
class SocketListerner;

class Socket {
public:
    Socket();
    virtual ~Socket();
    void Connect(const char* ip, unsigned short port);
    int Close();
    int Send(ByteBuf* frame);
    int Send(Frame* frame);
    void SetListerner(SocketListerner* listerner);
    void SetProtocal(Protocal* p);
    Protocal* GetProtocal();
    int GetSocketId();
    SocketListerner* GetListerner();
private:
    std::string ip;
    unsigned short port;
    unsigned sockid;
    SocketListerner* listerner;
    Protocal* protocal;
	
};

#endif	/* SOCKET_H */

