#include "log.h"

void Debug(std::string message)
{
    if (LOG_LEVEL != LogLevel::DEBUG)
    {
        return;
    }
    else
    {
        std::cout << "Debug: " << message << std::endl;
    }
};