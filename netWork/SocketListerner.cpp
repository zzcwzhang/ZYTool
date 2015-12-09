#include "SocketListerner.h"
#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#pragma comment(lib, "wsock32")
#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#endif
#include "Socket.h"
#include "ByteBuf.h"
#include "Protocal.h"

SocketListerner::SocketListerner():context(NULL)
{
}

SocketListerner::~SocketListerner()
{
}

void SocketListerner::SetContext(Socket* context)
{
    this->context = context;
}

void SocketListerner::Run()
{
    ByteBuf* buf = new ByteBuf(1024);
	ByteBuf* recv_buf = new ByteBuf(1024);
    int size = 0;
    int sockid = context->GetSocketId();
	bool first = true;
	int readLen = 0;
	int len = 0;
    while (true)
    {
		
        size = recv(sockid, buf->GetRaw(), 1024, 0);
        if (size > 0){
        
			buf->WriterIndex(size);
			ByteBuf* temp = (ByteBuf*)buf->Copy();
			
			readLen += size;
			if(first){
				first = false;
				buf->ReaderIndex(0);
				temp->ReaderIndex(0);
				len = temp->ReadShort();
				recv_buf->resetLen(len);
				
			}
			recv_buf->WriteBytes(temp);
			delete temp;
          

			if(len == readLen && len!=0){

				readLen = 0;
				first = true;
				len = 0;
				recv_buf->ReaderIndex(0);
				ByteBuf* frame = (ByteBuf*)recv_buf->Copy();
				this->OnMessage(context, frame);
				recv_buf->Clear();
			}

        } else
        {
            break;
        }
    }
    delete buf;
    this->OnClose(context, true);
}

