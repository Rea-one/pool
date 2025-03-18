// mruby_runner.cpp
#include "mruby_runner.h"

mruby_runner::mruby_runner() : 
    worker_([this](std::stop_token st) { core_loop(st); }) {
    initialize_mruby_env();
}

mruby_runner::~mruby_runner() {
    stop_source_.request_stop();
    if (mrb_) mrb_close(mrb_);
}

std::future<std::string> mruby_runner::async_run_script(const std::string& input) {
    execution_context ctx{input, {}};
    auto future = ctx.promise.get_future();
    
    {
        std::lock_guard lock(queue_mutex_);
        request_queue_.push(std::move(ctx));
    }
    
    queue_cv_.notify_one();
    return future;
}

void mruby_runner::core_loop(std::stop_token st) {
    while (!st.stop_requested()) {
        std::unique_lock lock(queue_mutex_);
        queue_cv_.wait(lock, st, [&] { return !request_queue_.empty(); });

        if (!request_queue_.empty()) {
            auto ctx = std::move(request_queue_.front());
            request_queue_.pop();
            lock.unlock();

            try {
                safe_execute_script(ctx.input, ctx.promise);
            } catch (...) {
                ctx.promise.set_exception(std::current_exception());
            }
        }
    }
}

void mruby_runner::initialize_mruby_env() {
    mrb_ = mrb_open();
    if (!mrb_) throw std::runtime_error("Failed to initialize MRuby");
    load_resources();
}

void mruby_runner::load_resources() {
    // 加载库
    for (const auto& [path, name] : libraries_) {
        std::string load_code = 
            "$LOAD_PATH << '" + path + "'\n"
            "require '" + name + "'";
        mrb_load_string(mrb_, load_code.c_str());
    }

    // 加载脚本
    for (const auto& script : scripts_) {
        if (std::ifstream file{script}; file) {
            mrb_load_file(mrb_, file);
        } else {
            throw std::runtime_error("Cannot open script: " + script);
        }
    }
}

void mruby_runner::safe_execute_script(const std::string& input,
                                      std::promise<std::string>& result_promise) {
    // 将输入参数转换为mrb数组
    auto* args = mrb_ary_new_capa(mrb_, 1);
    mrb_ary_push(mrb_, args, mrb_str_new_cstr(mrb_, input.c_str()));

    // 执行脚本
    mrb_value result = mrb_funcall(mrb_, mrb_top_self(mrb_), "run", 1, args);

    // 处理结果
    if (mrb_->exc) {
        mrb_value exc = mrb_obj_value(mrb_->exc);
        result_promise.set_exception(std::make_exception_ptr(
            std::runtime_error(mrb_str_to_cstr(mrb_, mrb_inspect(mrb_, exc)))
        ));
        mrb_->exc = nullptr;
    } else {
        result_promise.set_value(mrb_str_to_cstr(mrb_, result));
    }
}

void mruby_runner::add_library(std::string lib_path, std::string lib_name) {
    libraries_.emplace_back(std::move(lib_path), std::move(lib_name));
}

void mruby_runner::add_script(std::string script_path) {
    scripts_.push_back(std::move(script_path));
}