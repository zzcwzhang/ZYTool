#include "Thread.h"
#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include <string>
#include <sstream>
#include <iostream> 
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <string>
#include <sstream>
#include <iostream> 
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#endif

Thread::Thread() : status(UNINITIALIZED)
{
}

Thread::~Thread()
{
	End();
}



/**
* 初始化
* @return 
*/
int Thread::Init()
{
//#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
//	static int semIndex=0;
//	std::stringstream ss;
//	ss<<"cocosocket-";
//	ss<<semIndex++;
//	std::string name;
//	ss>>name;
//	sem = sem_open( name.c_str(),O_CREAT,0644,0);
//	if(sem == SEM_FAILED)
//	{
//		return ERR_AT_CREATE_SEM;
//	}
//#else
//	sem = new sem_t;
//	if (sem_init(sem, 0, 0) < 0)
//	{
//		return ERR_AT_CREATE_SEM;
//	}
//#endif
	std::thread t1(&Thread::DoRun,this);
	t1.detach();
	status = IDLE;
	return status;
}

void Thread::DoRun()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	Sleep(10);
#else
	sleep(20);
#endif

	if (RUNNING == this->status)
	{
		this->Run();
	}
	this->status = QUITED;
}

/**
*  启动线程
* @return 
*/
int Thread::Start()
{
	if (status == UNINITIALIZED)
	{
		this->Init();
		status = RUNNING;
	}
	return status;
}

/**
* 结束
*/
void Thread::End()
{
}


