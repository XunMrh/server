//Author: shane
#include<assert.h>
#include<pthread.h>
namespace shaneServer
{
    class MutexLock
    {
     public:
	MutexLock()
	{
	    int ret = pthread_mutex_init(&mutex_,NULL);
	    assert(ret == 0);
	}
	~MutexLock()
	{
	    int ret = pthread_mutex_destroy(&mutex_);
	    assert(ret == 0);
	}
	void lock()
	{
	    pthread_mutex_lock(&mutex_);
	}
	void unlock()
	{
	    pthread_mutex_unlock(&mutex_);
	}
	pthread_mutex_t* getMutex()
	{
	    return &mutex_;
	}
     private:
	pthread_mutex_t mutex_;
    };

    class MutexLockGuard
    {
     public:
	explicit MutexLockGuard()
	{
	    mutex_.lock();
	}
	~MutexLockGuard()
	{
	    mutex_.unlock();
	}
     private:
	MutexLock mutex_;
    };
}










