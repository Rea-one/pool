

// mruby_runner.h
#pragma once
#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/value.h"
#include "mruby/array.h"
#include "mruby/string.h"
#include "mruby/object.h"
#include "mruby/class.h"
#include <atomic>
#include <future>
#include <mutex>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <condition_variable>

class mruby_runner {
public:
    explicit mruby_runner();
    ~mruby_runner();

    // 异步执行脚本接口
    [[nodiscard]] std::future<std::string> async_run_script(const std::string& input);

    // 资源管理
    void add_library(std::string lib_path, std::string lib_name);
    void add_script(std::string script_path);

    // 禁止拷贝和移动
    mruby_runner(const mruby_runner&) = delete;
    mruby_runner& operator=(const mruby_runner&) = delete;

private:
    struct execution_context {
        std::string input;
        std::promise<std::string> promise;
    };

    // 线程控制
    std::jthread worker_;
    std::stop_source stop_source_;

    // MRuby环境
    std::unique_ptr(mrb_state) mrb_{nullptr};

    // 资源存储
    std::vector<std::pair<std::string, std::string>> libraries_;
    std::vector<std::string> scripts_;

    // 任务队列
    std::mutex queue_mutex_;
    std::queue<execution_context> request_queue_;
    std::condition_variable_any queue_cv_;

    // 核心执行逻辑
    void core_loop(std::stop_token st);
    void initialize_mruby_env();
    void load_resources();
    void safe_execute_script(const std::string& input, std::promise<std::string>& result_promise);
};