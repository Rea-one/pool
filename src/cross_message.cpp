#include "cross_message.h"

void cross_message::get(std::string& state_message, std::vector<std::string>& messgaes)
{
    std::unique_lock<std::mutex> lock(cm_lock);
    
}
