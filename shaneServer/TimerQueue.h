#include<set>
#include<vector>

#include<shaneServer/Mutex.h>
#include<shaneServer/Timestamp.h>
#include<shaneServer/Callback.h>

namespace shaneServer
{
 class EventLoop;
 class Timer;
 class Channel;

 class TimerQueue
 {
  public:
    TimerQueue(EventLoop *loop);
    ~TimerQueue();
    void addTimer(const TimerCallback &cb,
		  Timestamp when);
  private:
    typedef std::pair<Timestamp, Timer*> Entry;
    typedef std::set<Entry> TimerList;
    typedef TimerList ExPiredTimerSet;

    void handleRead();
    void getExpired(Timestamp now);

    EventLoop *loop_;
    const int timerfd_;
    TimerList timers_
    ExPiredTimerSet expiredTimers_;
 };
};
