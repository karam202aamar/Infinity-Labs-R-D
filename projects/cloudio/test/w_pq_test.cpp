/******************************************************************************/
#include <iostream> /*cout*/
#include <thread>   /*thread*/
/******************************************************************************/
#include "w_pq.hpp"
/******************************************************************************/
using namespace ilrd::hrd26;
/******************************************************************************/
static void Producer(WPriorityQueue<int> *queue_);
static void Consumer(WPriorityQueue<int> *queue_);
static void TestFunc(void);
/******************************************************************************/
int main()
{
    TestFunc();
    
    return 0;
}
/******************************************************************************/
static void Producer(WPriorityQueue<int> *queue_)
{
    for (size_t i = 0; i < 3; ++i)
    {
        queue_->Push(i);
        std::cout << "Produced: " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
/******************************************************************************/
static void Consumer(WPriorityQueue<int> *queue_)
{
    for (size_t i = 0; i < 3; ++i)
    {
        int value = queue_->Pop();
        std::cout << "Consumed: " << value << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
/******************************************************************************/
static void TestFunc()
{
    WPriorityQueue<int> queue;

    std::thread producer(Producer, &queue);
    std::thread consumer(Consumer, &queue);

    producer.join();
    consumer.join();

    queue.Push(1); 
    queue.Push(2); 
    queue.Push(3); 

    if(queue.IsEmpty())
    {
        std::cout << "failed" << std::endl;
    }

    if(3 != queue.Size())
    {
        std::cout << "Calculating Size failed" << std::endl;
    }

}
/******************************************************************************/
