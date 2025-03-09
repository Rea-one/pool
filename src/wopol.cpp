#include "wopol.h"



void wopol::read_file(std::string file_path)
{
    if (!file_path.empty())
    {
        state_message="文件不存在！";
    }
    std::ifstream file(file_path);
    std::string line;
    while (std::getline(file, line))
    {
        words.push_back(line);
    }
    file.close();
}

void wopol::write_file(std::string file_path)
{
    if (!file_path.empty())
    {
        state_message="文件不存在！";
    }
    std::ofstream file(file_path);
    for (auto &word : words)
    {
        file << word << std::endl;
    }
    file.close();
}