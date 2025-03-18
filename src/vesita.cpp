#include "vesita.h"


vesita::vesita()
{
    // 启动mruby
    mruby_tar = std::make_shared<mruby_runner>();
    mruby_tar -> add_lib("lib/linguist/lib/linguist.rb", "linguist");
    mruby_tar -> add_script("scp/run_linguist.rb");
    mruby_tar -> core_task();
    ftree_tar = std::make_shared<ftree>(this);
}


void vesita::clicked_file()
{
    auto file_path = ftree_tar -> get_path();
    if (file_path.empty())
    {
        return;
    }
    if (!wopol_tar.try_emplace(file_path))
    {
        wopol_tar[file_path] = std::make_shared<wopol>(this);
    }
    wopol_tar[file_path] -> read_file(file_path);
}