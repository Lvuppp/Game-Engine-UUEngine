#pragma once

#include <chrono>

namespace time_facade
{
    template<typename T>
    inline T getCurrentTime()
    {
        auto currentTime = std::time(nullptr);

        auto localTime = std::localtime(&currentTime);

        auto currentTimeSeconds = std::chrono::duration_cast<std::chrono::duration<T>>(
            std::chrono::system_clock::now().time_since_epoch()
            ).count();

        return currentTimeSeconds;
    }

}
