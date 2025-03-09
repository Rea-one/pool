#include "pool_tool.h"

std::string state_read(std::string state, std::string id)
{
    return state + "消息来自： " + id + "\n";
}