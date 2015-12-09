#include <iostream>
#include "ThreadPool.h"
#include "Thread.h"
//#include <semaphore.h>

using namespace std;

ThreadPool::ThreadPool(int poolsize)
: poolSize(poolsize),  pool(NULL)
{
    pool = new WorkThread* [poolsize];
    for (int i = 0; i < poolsize; ++i)
    {
        pool[i] = new WorkThread();
    }
}

ThreadPool::~ThreadPool()
{
    if (NULL == pool)
    {
        return;
    }
    for (int i = 0; i < poolSize; ++i)
    {
        if (NULL == pool[i])
        {
            continue;
        }
        delete pool[i];
    }
    delete [] pool;
}

void ThreadPool::Offer(Thread * task)
{
    bool result = false;
    WorkThread* g = NULL;
    for (int i = 0; i < poolSize; ++i)
    {
        if (pool[i]->GetStatus() == Thread::IDLE)
        {
            pool[i]->AddTask(task);
            return;
        } else if (g == NULL)
        {
            g = pool[i];
        } else if (g->TaskCount() > pool[i]->TaskCount())
        {
            g = pool[i];
        }
    }
	g->AddTask(task);
}

/**
 * ֹͣ�̳߳أ�����֮���������̳߳����task������
 */
void ThreadPool::Shutdown()
{
    if (NULL == pool)
    {
        return;
    }
    for (int i = 0; i < poolSize; ++i)
    {
        if (NULL == pool[i])
        {
            continue;
        }
        pool[i]->SetStatus(Thread::QUITED);
		//sem_post(pool[i]->GetSem());
        //pool[i]->Join();
        delete pool[i];
        pool[i] = NULL;
    }
    delete [] pool;
}
