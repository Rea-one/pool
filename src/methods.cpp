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
    pool.back().detach();
};


void threads::wait_threads()
{
    for (auto& thread : pool)
    {
        thread.join();
    }
};
