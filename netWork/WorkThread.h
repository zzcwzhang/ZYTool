#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include "Thread.h"
#include "Queue.h"

class WorkThread : public Thread {
protected:
	void Run();
public:
	WorkThread();
	~WorkThread();
	void AddTask(Thread* pt);
	void SetStatus(int s);
	int TaskCount();
private:
	Queue<Thread>* q;
};

inline void WorkThread::AddTask(Thread* t) {
	q->Offer(t);
}

inline void WorkThread::SetStatus(int s) {
	status = s;
}
#endif

