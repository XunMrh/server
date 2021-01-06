#include<boost/function.hpp>
#include<boost/shared_ptr.hpp>
#include<shaneServer/Timestamp.h>

namespace shaneServer
{
    class Buffer;
    class TcpConnection;
    typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;
    typedef boost::function<void()> TimerCallback;
    typedef boost::function<void (TcpConnectionPtr&)> ConnectionCallback;
    typedef boost::function<void (const TcpConnectionPtr&)> CloseCallback;
    typedef boost::function<void (const TcpConnectionPtr&,Buffer*,Timestamp)> MessageCallback;                          
    void defaultConnectionCallback(const TcpConnectionPtr& conn);	
    void defaultMessageCallback(const TcpConnectionPtr& conn,Buffer* buffer,Timestamp receiveTime);
};
