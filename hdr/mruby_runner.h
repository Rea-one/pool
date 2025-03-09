#include "mruby.h"

class mruby_runner
{
    mrb_state* mrb{};
    bool run_request = false;
    std::mutex task_lock{};
    std::queue<std::string> tasks{};
    threads task_pool{};
    void start();
    void stop();
    void task();
    void load_libs(std::string lib_path);
    void dark_load_libs();
    void run_task(std::string script_tar_path);
    void add_tasks(std::string script_tar_path);
    void clear_tasks();
}