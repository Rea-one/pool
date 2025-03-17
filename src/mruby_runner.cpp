#include "mruby_runner.h"


void mruby_runner::core_task()
{
    while (run_request)
    {
        std::unique_lock<std::mutex> lock(io_lock);

        cv.wait_for(lock, std::chrono::milliseconds(300), [this]
        {
            return !ins.empty() || !run_request;
        });

        if (!ins.empty())
        {
            auto [param, state] = ins.front();
            if (state)
            {
                for (auto& script : scripts)
                {
                    mrb_load_string(mrb, script.c_str());
                }
                std::vector<std::string> tars = split_string(param, " ");
                mrb_value mrb_args = convert_to_mrb_array(mrb, tars);
                mrb_value result = mrb_funcall(mrb, mrb_top_self(mrb), "run", 1, mrb_args);
                outs.push({mrb_str_to_cstr(mrb, result), state});
                if (mrb->exc)
                {
                    mrb_print_error(mrb);
                    mrb->exc = 0;
                }
            }
            ins.pop();
        }
    }

    mrb_close(mrb);
}

void mruby_runner::auto_load(mrb_state* mrb)
{
    for (auto& lib : libs)
    {
        lib = "$LOAD_PATH << '" + lib + "'";
        mrb_load_string(mrb, lib.c_str());
    }

    for (auto& script : scripts)
    {
        FILE* script_tar = fopen(script.c_str(), "r");
        if (script_tar)
        {
            mrb_load_file(mrb, script_tar);
            fclose(script_tar);
        }
    }
}

void mruby_runner::add_script(std::string script_path)
{
    scripts.push_back(script_path);
}

void mruby_runner::add_lib(std::string lib_path)
{
    libs.push_back(lib_path);
}


void mruby_runner::set_input(std::string input)
{
    std::unique_lock<std::mutex> lock(io_lock);
    ins.emplace(input, true);
}

std::string mruby_runner::get_output()
{
    std::unique_lock<std::mutex> lock(io_lock);
    if (!outs.empty())
    {
        auto [param, state] = outs.front();
        outs.pop();
       return param;
    }
}

mrb_value convert_to_mrb_array(mrb_state* mrb, const std::vector<std::string>& vec)
{
    mrb_value arr = mrb_ary_new_capa(mrb, vec.size());
    for (const auto& s : vec)
    {
      mrb_ary_push(mrb, arr, mrb_str_new_cstr(mrb, s.c_str()));
    }
    return arr;
}