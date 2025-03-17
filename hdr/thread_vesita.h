// #include <vector>
// #include <queue>
// #include <thread>
// #include <mutex>
// #include <condition_variable>
// #include <functional>
// #include <future>
// #include <atomic>
// #include <type_traits>  // 用于std::invoke_result_t

// class vth
// {
// public:
//     // 构造函数：初始化指定数量的工作线程
//     explicit vth(size_t worker_size = std::thread::hardware_concurrency()): stop(false)
//     {
//         workers.reserve(worker_size);
//         for (size_t i = 0; i < worker_size; ++i)
//         {
//             workers.emplace_back(&vth::worker_loop, this);
//         }
//     }

//     // 析构函数：安全停止所有线程
//     ~vth() noexcept
//     {
//         {
//             std::unique_lock<std::mutex> lock(queue_mutex);
//             stop = true;
//         }
//         condition.notify_all();
//         for (std::thread& worker : workers)
//         {
//             if (worker.joinable())
//             {
//                 worker.join();
//             }
//         }
//     }

//     // // 任务提交方法
//     // template <class auto, class... auto>
//     auto enqueue(auto&& f, auto&&... args)
//         -> std::future<typename std::invoke_result_t<decltype(f), decltype(args)...>>
//     {
//         using return_type = typename std::invoke_result_t<decltype(f), decltype(args)...>;

//         // 使用shared_ptr保证任务生命周期
//         auto task = std::make_shared<std::packaged_task<return_type()>>(
//             [f = std::forward<decltype(f)>(f),
//                 ...args = std::forward<decltype(args)>(args)...]() mutable
//             {
//                 return std::invoke(f, std::forward<decltype(args)>(args)...);
//             }
//         );

//         std::future<return_type> res = task->get_future();
//         {
//             std::lock_guard<std::mutex> lock(queue_mutex);
//             if (stop) {
//                 throw std::runtime_error("enqueue on stopped thread pool");
//             }
//             tasks.emplace([task]() { (*task)(); });
//         }
//         condition.notify_one();
//         return res;
//     }

//     // 禁用拷贝构造和赋值
//     vth(const vth&) = delete;
//     vth& operator=(const vth&) = delete;

// private:
//     // 工作线程主循环
//     void worker_loop()
//     {
//         while (true)
//         {
//             std::function<void()> task;
//             {
//                 std::unique_lock<std::mutex> lock(queue_mutex);
//                 condition.wait(lock, [this]
//                 {
//                     return stop || !tasks.empty();
//                 });

//                 if (stop && tasks.empty())
//                 {
//                     return;
//                 }

//                 task = std::move(tasks.front());
//                 tasks.pop();
//             }

//             try
//             {
//                 if (task)
//                 {
//                     task();
//                 }
//             }
//             catch (...)
//             {
//                 // 可在此处添加异常处理逻辑
//             }
//         }
//     }

//     std::vector<std::thread> workers;       // 工作线程集合
//     std::queue<std::function<void()>> tasks;// 任务队列
//     std::mutex queue_mutex;                 // 队列互斥锁
//     std::condition_variable condition;      // 条件变量
//     std::atomic<bool> stop;                 // 停止标志
// };


#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <stop_token>    // C++20停止令牌
#include <concepts>      // C++20概念

class vth
{
public:
    // 构造函数：初始化线程池，默认使用硬件并发数
    explicit vth(size_t cores = std::thread::hardware_concurrency())
        : stop_source{}  // 初始化停止令牌源
    {
        workers.reserve(cores);  // 预分配线程容器空间
        for (size_t i = 0; i < cores; ++i)
        {
            // 使用jthread并传递停止令牌（C++20特性）
            workers.emplace_back([this](std::stop_token stoken)
            {
                worker_loop(stoken);
            });
        }
    }

    // 析构函数：自动请求停止并等待线程结束（RAII）
    ~vth() noexcept
    {
        stop_source.request_stop();    // 请求停止
        condition.notify_all();        // 唤醒所有等待线程
    }

    // 任务入队方法（支持完美转发和任意可调用对象）
    auto enqueue(auto&& f, auto&&... args)
        -> std::future<std::invoke_result_t<decltype(f), decltype(args)...>>
    {
        using return_type = std::invoke_result_t<auto, auto...>;
        
        // 使用packaged_task封装任务（C++11特性）
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            [func = std::forward<auto>(f), ...args = std::forward<auto>(args)]() mutable
            {
                return std::invoke(func, std::forward<auto>(args)...);
            }
        );

        auto res = task->get_future();
        {
            std::scoped_lock lock(queue_mutex);  // C++17自动推导模板参数
            
            if (stop_source.stop_requested())
            {
                throw std::runtime_error("Enqueue on stopped thread pool");
            }

            // 使用lambda捕获移动的task（替代move_only_function）
            tasks.emplace([task = std::move(task)] { (*task)(); });
        }
        condition.notify_one();  // 通知一个等待线程
        return res;
    }

    // 禁用拷贝构造和赋值操作
    vth(const vth&) = delete;
    vth& operator=(const vth&) = delete;

private:
    // 工作线程主循环
    void worker_loop(std::stop_token stoken)
    {
        while (!stoken.stop_requested())
        {  // 使用停止令牌作为退出条件
            std::function<void()> task;     // 使用常规function
            
            {
                std::unique_lock lock(queue_mutex);
                
                // 使用条件变量+停止令牌实现等待（C++20特性）
                condition.wait(lock, stoken, [this]
                {
                    return !tasks.empty();
                });

                if (tasks.empty()) break;  // 收到停止信号且任务队列为空时退出

                task = std::move(tasks.front());
                tasks.pop();
            }

            if (task)
            {
                try
                {
                    task();  // 执行实际任务
                }
                catch (...)
                {
                    // 可扩展异常处理逻辑
                }
            }
        }
    }

    std::vector<std::jthread> workers;       // C++20 jthread
    std::queue<std::function<void()>> tasks; // 使用常规function队列
    mutable std::mutex queue_mutex;          // 任务队列互斥锁
    std::condition_variable_any condition;   // 通用条件变量（C++11）
    std::stop_source stop_source;            // C++20停止信号源
};