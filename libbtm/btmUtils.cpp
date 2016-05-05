
#include "btmUtils.h"
#include <cstdlib>


std::string btm::RandomString(const int len) {
    static const char alphanum[] =
        "abcdefghijklmnopqrstuvwxyz";
    static const char alphanum_maj[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string s;
    s.resize(len);
    s[0] = alphanum_maj[rand() % (sizeof(alphanum_maj) - 1)];
    for (int i = 1; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
    return s;
}
