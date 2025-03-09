#include "mruby.h"

class mruby_runner
{
    mrb_state* mrb{};

    void run_ruby(std::string code)
    {
        mrb_load_string(mrb, code.c_str());
    }
}