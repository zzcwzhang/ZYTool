#ifndef SOCKETLISTERNER_H
#define	SOCKETLISTERNER_H
#include "Thread.h"
class Socket;
class ByteBuf;
class SocketListerner : public Thread
{
public:
	SocketListerner();
	virtual ~SocketListerner();
	virtual void OnMessage(Socket* so, ByteBuf* frame) = 0;
	virtual void OnClose(Socket* so, bool fromRemote) = 0;
	virtual void OnIdle(Socket* so) = 0;
	virtual void OnOpen(Socket* so) = 0;
	virtual void OnError(Socket* so, const char* e) = 0;
	void SetContext(Socket* context);
	virtual void Run();

private:
	Socket* context;
};
#endif	/* SOCKETLISTERNER_H */

