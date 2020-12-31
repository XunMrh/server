#include<Timestamp.h>
#include<sys/time.h>
#include<stdio.h>
using namespace shaneServer;

Timestamp Timestamp::now()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    int64_t seconds = tv.tv_sec;
    return Timestamp(seconds * 1000 * 1000 + tv.tv_usec);
}
