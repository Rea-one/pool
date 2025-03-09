#include "methods.h"


class bist
{
    std::string dark{};
    std::string light{};

    bist(std::string dark, std::string light);
};


class cross_message
{
    public:
    std::string state_message{};
    std::vector<bool> states{};
    std::vector<std::string> messgaes{};

    std::mutex cm_lock{};
    void set(std::string state_message, std::vector<std::string> messgaes);
    void get(std::string& state_message, std::vector<std::string>& messgaes);
};