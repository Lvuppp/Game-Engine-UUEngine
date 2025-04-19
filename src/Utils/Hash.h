#pragma once

#include <string_view>
#include <cstdint>

class Hash
{
public:
    static constexpr uint32_t hash(std::string_view str)
    {
        uint32_t hash = 2166136261u;
        for (char c : str)
        {
            hash ^= static_cast<uint8_t>(c);
            hash *= 16777619u;
        }
        return hash;
    }
};

constexpr uint32_t operator"" _hash(const char* str, size_t len)
{
    return Hash::hash(std::string_view(str, len));
}
