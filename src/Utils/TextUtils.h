#pragma once

#include <string>
#include <vector>

namespace text_utils
{
    std::vector<std::string> split(const std::string& str, char separator);
    std::string join(const std::vector<std::string>& elements, char separator);
};
