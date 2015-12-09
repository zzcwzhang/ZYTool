#ifndef MUTEX_H
#define MUTEX_H
#include <mutex>
class Mutext 
{
private:
	std::mutex mutext;
public:
	Mutext();
	~Mutext();
private:

	Mutext(const Mutext & cMutex) {
	}

	Mutext & operator =(const Mutext & cMutex) {
		return *this;
	}

public:
	inline void Lock(){mutext.lock();}
	inline void Unlock(){mutext.unlock();}
	inline bool Trylock(){mutext.try_lock();}
};

#endif
