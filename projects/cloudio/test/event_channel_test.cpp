/******************************************************************************

* ****************************************************************************/
#include <iostream>
#include "event_channel.hpp"

using namespace ilrd::hrd26;

/**********************************CLASSES************************************/
/********/
class Publisher
{ 
    public:
        Publisher(std::string msg_);
        ~Publisher() = default;
        Dispatcher<std::string> m_dp;
        void SendMessage() 
        { 
            m_dp.NotifyAll(m_msg); 
        }
        

    private:
        std::string m_msg;
};

Publisher::Publisher(std::string msg_):
    m_msg(msg_)
{
    //empty
}
/********/
class Subscriber
{
    public:
        Subscriber(std::string msg_, Dispatcher<std::string> *dp_);
        ~Subscriber() = default;

        void DoSomething(const std::string &str_);
        void StopDoing();

    private:
        Callback<std::string, Subscriber> m_cb;
        std::string m_msg;
};

Subscriber::Subscriber(std::string msg_, Dispatcher<std::string> *dp_):
    m_msg(msg_),
    m_cb(dp_, *this, &Subscriber::DoSomething, &Subscriber::StopDoing)
{

}

void Subscriber::DoSomething(const std::string &str_)
{
    std::cout << "Do something: " << m_msg << std::endl;
}

void Subscriber::StopDoing()
{
    std::cout << "Do nothing " << m_msg << std::endl;
}

/**********************************MAIN***************************************/
int main(void)
{
    Publisher *pb = new Publisher("this is my message");
    Subscriber sb1("sb1 message", &pb->m_dp);
    Subscriber sb2("sb2 message", &pb->m_dp);
    Subscriber sb3("sb3 message", &pb->m_dp);

    pb->SendMessage();
    std::cout<< "UNSUBSCRIBE:"<<std::endl;
    delete pb;

    return 0;
}

