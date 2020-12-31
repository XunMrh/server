#include<Timestamp.h>
#include<iostream>
using namespace std;
using namespace shaneServer;
int main()
{
    Timestamp t1;
    Timestamp t2(20);
    cout<< (t1<t2) <<endl;
    cout<< (t1==t2) <<endl;
    cout<< (Timestamp::now().msSinceEpoch()) <<endl;
    t1.addTime(30);
    cout<< (t1<t2) <<endl;
    return 0;
}
