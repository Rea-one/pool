#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <queue>
#include <type_traits>
#include <utility>
#include <chrono>
#include <algorithm>
#include <ctime>
#include <condition_variable>



void joit_swap(std::vector<std::pair<std::string, int>>& words, int i, int j);

int fast_index(char c);


class threads
{
    public:
    threads();
    ~threads();
    std::vector<std::thread> pool;

    void add_thread(std::function<void()> act);
    void depart_run(std::function<void()> act);
    void wait_threads();
};

template<typename data_type>
class cross_data
{
private:
    std::mutex self_lock; // 互斥锁
    data_type data;       // 数据

public:
    // 获取数据的副本（线程安全）
    data_type get() const
    {
        std::lock_guard<std::mutex> lock(self_lock);
        return data;
    }

    // 设置数据（线程安全）
    void set(const data_type &new_data)
    {
        std::lock_guard<std::mutex> lock(self_lock);
        data = new_data;
    }

    // 修改数据（线程安全）
    template<typename Func>
    auto access(Func &&func) -> decltype(func(data))
    {
        std::lock_guard<std::mutex> lock(self_lock);
        return func(data); // 在锁保护下执行用户提供的函数
    }
};


std::vector<std::string> split_string(std::string tar, std::string departer);