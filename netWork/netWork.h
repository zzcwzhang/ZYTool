#ifndef NETWORK_H
#define	NETWORK_H

#include "cocos2d.h"  
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#pragma comment(lib, "wsock32")
#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#endif



#include "AutoLock.h"
#include "Bits.h"
#include "ByteBuf.h"
#include "Frame.h"

#include "Mutext.h"
#include "Socket.h"
#include "SocketListerner.h"
#include "Protocal.h"
#include "Thread.h"
#include "ThreadPool.h"
#include "WorkThread.h"


#endif	/* COCOS2D_H */