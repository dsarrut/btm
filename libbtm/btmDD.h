#ifndef btmDD_H
#define btmDD_H

#include <iostream>
#include <sstream>
#ifdef _WIN32
# include <windows.h>
#endif

// DD = David's Debug

#define DD_COLOR "\x1b[36m"
#define DD_RESET "\x1b[0m"

#ifdef _WIN32
# define DD(a) { \
    std::ostringstream ossDD__; \
    ossDD__ << #a " = [ " << a << " ]" << std::endl; \
    std::string s__ = ossDD__.str(); \
    std::wstring widestr__ = std::wstring(s__.begin(), s__.end()); \
    OutputDebugString(widestr__.c_str()); \
    }
#else
# define DD(a) std::cout << DD_COLOR << #a " = [ " << a << " ]" << DD_RESET << std::endl;std::cout.flush();
#endif

#define DDV(a,n) { std::cout << DD_COLOR << #a " = [ "; \
    for(unsigned int _i_=0; _i_<n; _i_++) { \
    std::cout << a[_i_] << " "; }; std::cout << " ]" \
    << DD_RESET << std::endl;std::cout.flush();}

template<class T>
void _print_container(T const& a)
{
    for(typename T::const_iterator i=a.begin();i!=a.end();++i) {
        std::cout << *i << " ";
    };
}

#define DDS(a) { std::cout << DD_COLOR << #a " = [ "; \
    _print_container(a) ; std::cout << "]" \
    << DD_RESET << std::endl;std::cout.flush();}

#define DDF() { std::cout << DD_COLOR \
    << "--> Function " << __func__ << std::endl; }

#endif
