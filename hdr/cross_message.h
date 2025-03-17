#include "methods.h"


class cross_message
{
public:
    enum class io_status { ready_for_read, ready_for_write };
    std::atomic<io_status> ready{io_status::ready_for_write};
    std::atomic<std::shared_ptr<std::string>> message_ptr; // 原子智能指针方案

    void set(const std::string& mess);
    std::string get();
};

/*
in easy
输入宽松通信机
*/
class ie_message: public cross_message
{
public:
    void set(const std::string& mess);
};


/*
out easy
输出宽松通信机
*/
class oe_message: public cross_message
{
public:
    std::string get();
};


/*
loose
宽松通信机
*/
class loose_message: public cross_message
{
public:
    void set(const std::string& mess);
    std::string get();
};

