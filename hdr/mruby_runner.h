#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/value.h"
#include "mruby/array.h"
#include "mruby/string.h"
#include "mruby/object.h"
#include "mruby/class.h"

#include "methods.h"

class mruby_runner
{
    std::condition_variable cv{};
    std::mutex io_lock{};
    bool run_request = false;
    std::thread task{};
    std::vector<std::string> libs{};
    std::vector<std::string> scripts{};
    std::queue<std::pair<std::string, bool>> ins{};
    std::queue<std::pair<std::string, bool>> outs{};
    
    void start();
    void stop();
    void core_task();

    void auto_load(mrb_state* mrb);
    void add_script(std::string script_path);
    void add_lib(std::string lib_path);

    void set_input(std::string input);
    std::string get_output();
};


mrb_value convert_to_mrb_array(mrb_state* mrb, const std::vector<std::string>& vec);