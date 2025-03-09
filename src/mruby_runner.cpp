#include "mruby_runner.h"

void ruby_runner::start()
{
    run_request = true;
    task_pool.add_thread([this]() { this->task(); });  
}

void ruby_runner::stop()
{
    run_request = false;
    clear_tasks();
    task_pool.clear_threads();
    task_pool.wait_threads();
}

void task()
{
    mrb = mrb_open();
    dark_load_libs();  
    while (run_request)
    {
        std::unique_lock<std::mutex> lock(task_lock);
        if(!tasks.empty())
        {
            std::string script_tar_path = tasks.front();
            tasks.pop();
            run_tasks(script_tar_path);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

void ruby_runner::load_libs(std::string lib_path)
{
    mrb.load_file(lib_path.c_str());
}

void ruby_runner::dark_load_libs()
{
    mrb.load_file("github-linguist");
}

void ruby_runner::run_task(std::string script_tar_path)
{
    mrb.load_file(script_tar_path.c_str());
}

void ruby_runner::add_tasks(std::string script_tar_path)
{
    std::unique_lock<std::mutex> lock(task_lock);
    tasks.push(script_tar_path);
}

void ruby_runner::clear_tasks()
{
    std::unique_lock<std::mutex> lock(task_lock);
    while(!tasks.empty())
    {
        tasks.pop();
    }
}