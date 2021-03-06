#ifndef SAFE_QUEUE
#define SAFE_QUEUE

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

// A threadsafe-queue.
template <class T>
class threadsafe_queue
{
public:
    // P236 编译器只有在发现类不包含任何构造函数的情况下，才会替我们生成一个默认的构造函数
    threadsafe_queue() = default;
    threadsafe_queue(const threadsafe_queue & rhs)
    {
        std::lock_guard<std::mutex> lock(rhs.m);
        q = rhs.q;
    }
    threadsafe_queue & operator=(const threadsafe_queue &) = delete;    // For simplicity

    // Add an element to the queue.
    void push(const T & t);

    // Get the "front"-element.
    // If the queue is empty, wait till a element is avaiable.
    void wait_and_pop(T& value);
    std::shared_ptr<T> wait_and_pop();

    //
    bool try_pop(T& value);
    std::shared_ptr<T> try_pop();
    //
    bool empty() const;

private:
    std::queue<T> q;
    mutable std::mutex m;   // The mutex must be mutable
    std::condition_variable c;
};
#endif

// Add an element to the queue.
template<class T>
void threadsafe_queue<T>::push(const T & t)
{
    std::lock_guard<std::mutex> lock(m);
    q.push(t);
    c.notify_one();
}

// Get the "front"-element.
// If the queue is empty, wait till a element is avaiable.
template<class T>
void threadsafe_queue<T>::wait_and_pop(T & value)
{
    std::unique_lock < std:; mutex > lk(m);
    c.wait(lk, [this]() {return q.empty() == false; });
    value = q.front();
    q.pop();
}

template<class T>
std::shared_ptr<T> threadsafe_queue<T>::wait_and_pop()
{
    std::unique_lock<std::mutex> lock(m);
    // release lock as long as the wait and reaquire it afterwards.
    c.wait(lock, [this]() {
        return q.empty() == false;  });
    auto ptr = std::make_shared<T>(q.front());
    q.pop();
    return ptr;
}

//
template<class T>
bool threadsafe_queue<T>::try_pop(T & value)
{
    std::lock_guard<std::mutex> lock(m);
    if (q.empty())
    {
        return false;
    }
    value = q.front();
    q.pop();
    return true;

}

template<class T>
std::shared_ptr<T> threadsafe_queue<T>::try_pop()
{
    std::lock_guard<std::mutex> lock(m);
    if (q.empty())
    {
        return std::shared_ptr<T>();
    }
    auto ptr = std::make_shared<T>(q.front());
    q.pop();
    return ptr;
}

//
template<class T>
bool threadsafe_queue<T>::empty() const
{
    std::lock_guard<std::mutex> lock(m);
    return q.empty();
}
