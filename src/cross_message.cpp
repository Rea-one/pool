#include "cross_message.h"


void cross_message::set(const std::string& mess)
{
    if (ready != io_status::ready_for_write)
    {
        return;
    }
    ready = io_status::ready_for_read;
    message_ptr.store(std::make_shared<std::string>(mess), std::memory_order_release);
}

std::string cross_message::get()
{
    if (ready != io_status::ready_for_read)
    {
        return "";
    }
    ready = io_status::ready_for_write;
    return *message_ptr.load(std::memory_order_acquire);
}

void ie_message::set(const std::string& tar)
{
    ready = io_status::ready_for_read;
    message_ptr.store(std::make_shared<std::string>(tar), std::memory_order_release);
}

std::string oe_message::get()
{
    ready = io_status::ready_for_write;
    return *message_ptr.load(std::memory_order_acquire);
}

void loose_message::set(const std::string& tar)
{
    ready = io_status::ready_for_read;
    message_ptr.store(std::make_shared<std::string>(tar), std::memory_order_release);
}

std::string loose_message::get()
{
    ready = io_status::ready_for_write;
    return *message_ptr.load(std::memory_order_acquire);
}