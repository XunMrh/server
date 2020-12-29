#include<iostream>
#include<Mutex.h>
using namespace std;
using namespace shaneServer;
int main()
{
    MutexLockGuard mutex_;
    cout<<"hello world"<<endl;
    return 0;
}
