#pragma once

#include <string>
#include <vector>

namespace text_utils
{
    std::tuple<std::string, std::string, std::string> getFullFileName(std::string_view path);
    std::vector<std::string> split(const std::string& str, char separator);
    std::string join(const std::vector<std::string>& elements, char separator);
    std::string join(const std::vector<std::string_view>& elements, char separator);
};
