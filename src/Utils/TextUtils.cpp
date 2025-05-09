#include "TextUtils.h"

#include <sstream>
namespace text_utils
{
    std::vector<std::string> split(const std::string& str, char separator)
    {
        std::vector<std::string> result;
        std::stringstream ss(str);
        std::string token;

        while (std::getline(ss, token, separator))
        {
            result.push_back(token);
        }

        return result;
    }

    std::string join(const std::vector<std::string>& elements, char separator)
    {
        if (elements.empty())
        {
            return "";
        }

        std::ostringstream oss;
        oss << elements[0];

        for (auto i = 1; i < elements.size(); ++i)
        {
            oss << separator << elements[i];
        }

        return oss.str();
    }

    std::string join(const std::vector<std::string_view>& elements, char separator)
    {
        if (elements.empty())
        {
            return "";
        }

        std::ostringstream oss;
        oss << elements[0];

        for (auto i = 1; i < elements.size(); ++i)
        {
            oss << separator << elements[i];
        }

        return oss.str();
    }
}