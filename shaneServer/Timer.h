#include<shaneServer/Timestamp.h>
#include<shaneServer/Callback.h>

namespace shaneServer
{
 class Timer
 {
  public:
    Timer(TimerCallback &callback,Timestamp &expiration)
    :callback_(callback),expiration_(expiration)
    {}
    ~Timer()
    {}
    void run() const
    {
	callback_();
    }
    Timestamp expiration() const
    {
	return expiration_;
    }
  private:
    const TimerCallback callback_;
    Timestamp expiration_;
 }
}
