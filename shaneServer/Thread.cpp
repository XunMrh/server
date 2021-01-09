#include<shaneServer/Thread.h>
using namespace shaneServer;

Thread::Thread(const ThreadFunc& func, const string& n)
    : started_(false),
      pthreadId_(0),
      func_(func),
      name_(n)
{
    errno = pthread_create(&pthreadId_, NULL, &func_, this);
};

Thread::~Thread()
{};

void Thread::start()
{
    started_ = true;
    func_();
};




