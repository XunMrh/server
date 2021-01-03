#include<algorithm>
#include<vector>
#include<assert.h>
#include<string>
using namespace std;

namespace shaneServer
{
 class Buffer
 {
  public:
    Buffer()
    :buffer_(1024),
     readerIndex_(0),
     writerIndex_(0)
    {}
    ~Buffer()
    {}
    size_t readableByte()
    {
	return writerIndex_ - readerIndex_;
    }
    size_t writableByte()
    {
	return buffer_.capacity() - writerIndex_;
    }
    void swap(Buffer &rhs)
    {
	buffer_.swap(rhs.buffer_);
	std::swap(readerIndex_,rhs.readerIndex_);
	std::swap(writerIndex_,rhs.writerIndex_);
    }
    const char* peek() const
    {
	return &*buffer_.begin() + readerIndex_;
    }
    string readAsString(int len)
    {
	if(len <= readableByte())
	{
	    string result(peek(),len);
	    readerIndex_ += len;
	    return result;
	}
	else
	{
	    string result(readerIndex_,writerIndex_);
	    readerIndex_ = 0;
	    writerIndex_ = 0;
	    return result;
	}
    }
    void appendString(string &str)
    {
	if(writableByte() < str.length())
	{
	    buffer_.resize(writerIndex_ + str.length());
	}
	copy(str.begin(),str.end(),buffer_.begin()+writerIndex_);
	writerIndex_ += str.length();
    }

  private:
    vector<char> buffer_;
    size_t readerIndex_;
    size_t writerIndex_;
 };
};
