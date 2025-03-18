#include "vesita.h"


vesita::vesita()
{
    // 启动mruby
    mruby_tar = std::make_shared<mruby_runner>();
    mruby_tar -> add_lib("lib/linguist/lib/linguist.rb", "linguist");
    mruby_tar -> add_script("scp/run_linguist.rb");
    mruby_tar -> core_task();
}