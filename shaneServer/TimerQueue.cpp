#include<shaneServer/TimerQueue.h>
#include<shaneServer/EventLoop.h>
#include<shaneServer/Timer.h>

#include<boost/bind.hpp>
#include<sys/timerfd.h>

namespace shaneServer
{
 int createTimerfd()
 {
    int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    return timerfd;
 }
};

using namespace shaneServer;

TimerQueue::TimerQueue(EventLoop *loop)
    :loop_(loop),
     timerfd_(createTimerfd())
{
    //将handlread()和timerfd_加入到eventloop的map中
}
TimerQueue::~TimerQueue()
{
    ::close(timerfd_);
    for (TimerList::iterator it = timers_.begin();
	it != timers_.end(); ++it)
    {
	delete it->second;
    }
}
void TimerQueue::addTimer(const TimerCallback &cb,
		Timestamp when)
{
    Timer *timer = new Timer(cb, when);
    bool earliestChanged = insert(timer);
    if (earliestChanged)
    {
	resetTimerfd(timerfd_, timer->expiration());
    }
}

void TimerQueue::handleRead()
{
    Timestamp now(Timestamp::now());
    readTimerfd(timerfd_, now);
    
    getExpired(now);
    for (std::vector<Entry>::iterator it = expiredTimers_.begin();
	it != expiredTimers_.end(); ++it)
    {
	it->second->run();
    }
    expiredTimers_.erase();
}

void getExpired(Timestamp now)
{
   expiredTimers_;
   Entry sentry(now, reinterpret_cast<Timer*>(UINTPTR_MAX));
   TimerList::iterator end = timers_.lower_bound(sentry);
   std::copy(timers_.begin(), end, back_inserter(expiredTimers_));
   timers_.erase(timers_.begin(), end);
}


bool TimerQueue::insert(Timer *timer)
{
    bool earliestChanged = false;
    Timestamp when = timer->expiration();
    TimerList::iterator it = timers_.begin();
    if (it == timers_.end() || when < it->first)
    {
	earliestChanged = true;
    }
    timers_.insert(Entry(when, timer));
    return earliestChanged;
}


