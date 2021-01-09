#include<boost/function.hpp>
#include<pthread.h>

namespace shaneServer
{
 class Thread
 {
  public:
    typedef boost::function<void()> ThreadFunc;
    explicit Thread(const ThreadFunc&, const string &name=string());
    ~Thread();
    void start();
    bool started();
    const string& name() const	{return name_;	}
    
  private:
   bool started_;
   pthread_t pthreadId_;
   pid_t tid_;
   ThreadFunc func_;
   string name_;

 };

};
