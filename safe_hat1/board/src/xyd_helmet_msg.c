#include "main.h"

uint32_t sum_value(HELMET_MSG msg)
{
    return msg.command + msg.data_length +(uint32_t)msg.data_ptr;
}


bool sum_test(HELMET_MSG msg)
{
    if(msg.sum==msg.command + msg.data_length +(uint32_t)msg.data_ptr)
    {
        return true;
    }
    return false;
}