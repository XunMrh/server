#include<Condition.h>
#include<errno.h>
bool shaneServer::Condition::waitForSeconds(int seconds)
{
   struct timespec curTime;
   clock_gettime(CLOCK_REALTIME, &curTime);
   abstime.tv_sec += second;
   return ETIMEDOUT == pthread_cond_timedwait(&pcond_, mutex_.getMutex(), &curTime);
}
