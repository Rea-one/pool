#include "methods.h"


void joit_swap(std::vector<std::pair<std::string, int>>& words, int i, int j)
{
    std::pair<std::string, int> temp = words[i];
    words[i] = words[j];
    words[j] = temp;
};

int fast_index(char c)
{
    return static_cast<int>(c);
};


threads::threads()
{
    
};

threads::~threads()
{
    wait_threads();
    pool.clear();
};

void threads::add_thread(std::function<void()> func)
{
    pool.emplace_back(func);
};

void threads::depart_run(std::function<void()> act)
{
    pool.emplace_back(act);
    pool.back().detach();
};

void threads::wait_threads()
{
    for (auto& thread : pool)
    {
        thread.join();
    }
};


std::vector<std::string> split_string(const std::string& tar, const std::string& departer)
{
    std::vector<std::string> result;
    std::string temp;
    for (char elem : tar)
    {
        if (departer.find(elem) == std::string::npos)
        {
            temp += elem;
        }
        else
        {
            if (!temp.empty())
                result.push_back(temp);
            temp.clear();
        }
    }
    if (!temp.empty())
        result.push_back(temp);
    return result;
}