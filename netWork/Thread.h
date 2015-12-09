#ifndef THREAD_H
#define THREAD_H
typedef void * (* func)(void *);

class Thread {
public:
	enum ThreadState {
		ERR_ALREADERY_INITIALIZED = -6,
		ERR_AT_CREATE_THREAD = -5,
		ERR_AT_CREATE_SEM = -4,
		ERR_NO_TASK = -3,
		ERR_NOT_IDLE = -2,
		UNINITIALIZED = -1,
		IDLE = 0,
		RUNNING = 1,
		QUITED = 9
	};
private:
	//int Create(func f, void * context, bool detached = false, bool scope = false);
	void End();
	int Init();
	void DoRun();
protected:
	int status;
public:
	Thread();
	virtual ~Thread();
	virtual void Run() = 0;
	int GetStatus(){return status;}
	int Start();
};
#endif


