#include<shaneServer/ThreadPool.h>

#include<boost/bind.hpp>

using namespace shaneServer;

ThreadPool::ThreadPool(const string& name)
    :mutex_(),
    cond_(mutex_),
    name_(name),
    running_(false)
{}

ThreadPool::~ThreadPool()
{
    if(runing_)
	stop();
}

void ThreadPool::start(int numThreads)
{
    running_ = true;
    threads_.reserve(numThreads);
    for (int i = 0; i < numThreads; ++i)
    {
	threads_.push_back(new muduo::Thread(boost::bind(&ThreadPool::runInThread, this), name_));
	threads_[i].start();
    }
}

void ThreadPool::stop()
{
    {
	MutexLockGuard lock(mutex_);
	running_ = false;
        cond_.notifyAll();
    }
    for_each(threads_.begin(),threads_.end(), boost::bind(&muduo::Thread::join, _1));
}

void ThreadPool::run(const Task& task)
{
    if (threads_.empty())
    {
        task();
    }
    else
    {

	MutexLockGuard lock(mutex_);
	queue_.push_back(task);
	cond_.notify();
    }
}

ThreadPool::Task ThreadPool::take()
{
    MutexLockGuard lock(mutex_);
    while (queue_.empty() && running_)
    {
        cond_.wait();
    }
    Task task;
    if(!queue_.empty())
    {
        task = queue_.front();
	queue_.pop_front();
    }
    return task;
}

void ThreadPool::runInThread()
{
    try
    {
        while (running_)
	{
	    Task task(take());
	    if (task)
	    {
		task();
	    }
	}
    }
    catch (const Exception& ex)
    {
    }
}



