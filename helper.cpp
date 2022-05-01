#include "helper.h"
#include <string>

Helper::Helper()
{

}

bool Helper::isNumber(char *number)
{
    std::string s = number;
    std::string::const_iterator it = s.begin();

    while (it != s.end() && std::isdigit(*it)){
        ++it;
    }
    return !s.empty() && it == s.end();

}
