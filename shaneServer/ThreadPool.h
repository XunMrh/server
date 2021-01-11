#include<shaneServer/Condition.h>
#include<shaneServer/Mutex.h>
#include<shaneServer/Thread.h>

#include<boost/function.hpp>
#include<boost/ptr_container/ptr_vector.hpp>

namespace shaneServer
{
 class ThreadPool
 {
  public:
    typedef boost::function<void()> Task;
    explicit ThreadPool(const string& name = string());
    ~ThreadPool();

    void start(int numThreads);
    void stop();
    void run(const Task& f);
  private:
    void runInThread();
    Task take();
    MutexLock mutex_;
    Condition cond_;
    string name_;
    boost::ptr_vector<shaneServer::Thread> threads_;
    std::deque<Task> queue_;
    bool runing_;
 };
};
