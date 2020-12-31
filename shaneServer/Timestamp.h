typedef long long int64_t;
namespace shaneServer
{
 class Timestamp
 {
  public:
    Timestamp():msSinceEpoch_(0)
    {
    }
    explicit Timestamp(int64_t msSinceEpoch)
    :msSinceEpoch_(msSinceEpoch)
    {
    }
    static Timestamp now();
    int64_t msSinceEpoch() const
    {
	return msSinceEpoch_;
    }
    bool operator<(Timestamp &rhs)
    {
	return this->msSinceEpoch_ < rhs.msSinceEpoch();	
    }
    bool operator==(Timestamp &rhs)
    {
	return this->msSinceEpoch_ == rhs.msSinceEpoch();
    }
    Timestamp& addTime(double seconds)
    {
	int64_t delta = static_cast<int64_t>(seconds*1000*1000);
	this->msSinceEpoch_ += delta;
	return *this;
    }
  private:
   int64_t msSinceEpoch_; 
 };
};
