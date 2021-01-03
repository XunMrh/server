#include<Buffer.h>
#include<iostream>
#include<string>
using namespace std;
using namespace shaneServer;
int main()
{
    Buffer mbuff;
    cout<<mbuff.readableByte()<<endl;
    cout<<mbuff.writableByte()<<endl;
    string str="hello";
    mbuff.appendString(str);
    cout<<mbuff.readableByte()<<endl;
    string res=mbuff.readAsString(2);
    cout<<res<<endl;
}
