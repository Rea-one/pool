#include "methods.h"


// class cross_message
// {
// public:
//     enum class io_status { ready_for_read, ready_for_write };
//     std::atomic<io_status> ready{io_status::ready_for_write};
//     std::atomic<std::shared_ptr<std::string>> message_ptr; // 原子智能指针方案

//     void set(const std::string& mess);
//     std::string get();
// };

// /*
// in easy
// 输入宽松通信机
// */
// class ie_message: public cross_message
// {
// public:
//     void set(const std::string& mess);
// };


// /*
// out easy
// 输出宽松通信机
// */
// class oe_message: public cross_message
// {
// public:
//     std::string get();
// };


// /*
// loose
// 宽松通信机
// */
// class loose_message: public cross_message
// {
// public:
//     void set(const std::string& mess);
//     std::string get();
// };


class crsm
{
private:
    enum class State { Idle, Processing };
    
    std::condition_variable state_cv_;
    std::atomic<State> current_state_{State::Idle};
    std::vector<std::jthread> workers_; // C++20 自动join线程

    void process_data()
    {
        // 示例处理逻辑
        static thread_local int counter = 0;
        std::cout << "Processing data: " << ++counter << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
public:
    // C++20 停止令牌 + 原子状态组合
    void start_workers(int thread_count)
    {
        std::latch sync_point{thread_count}; // C++20 同步点

        for(int i = 0; i < thread_count; ++i)
        {
            workers_.emplace_back([this, &sync_point](std::stop_token st)
            {
                sync_point.arrive_and_wait(); // 等待所有线程就绪
                
                while(!st.stop_requested())
                { // C++20 停止令牌检查
                    // 状态驱动的执行逻辑
                    if(auto state = current_state_.load(); state == State::Processing)
                    {
                        process_data();
                    } 
                    else if(state == State::Idle)
                    {
                        std::this_thread::yield();
                    }
                }
            });
        }
    }

    // 状态切换接口
    void set_state(State new_state) noexcept
    {
        if(current_state_.exchange(new_state) != new_state)
        { // 状态变化时才通知
            state_cv_.notify_all(); // 需配合条件变量使用
        }
    }

    // 安全停止（C++20 jthread自动管理停止请求）
    void stop()
    {
        for(auto& t : workers_)
        {
            t.request_stop();
        }
    }
};



