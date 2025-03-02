#include "methods.h"


void joit_swap(std::vector<std::pair<QString, int>>& words, int i, int j)
{
    std::pair<QString, int> temp = words[i];
    words[i] = words[j];
    words[j] = temp;
}

int fast_index(char c)
{
    return static_cast<int>(c);
}

void thread_pool::add_thread(std::function<void()> func)
{
    pool.emplace_back(func);
}

void thread_pool::join()
{
    for (auto& thread : pool)
    {
        thread.join();
    }
}