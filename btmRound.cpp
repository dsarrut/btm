#include "btmRound.h"

btm::Round::Round()
{

}

void btm::Round::Bidon()
{
    std::cout << "hello" << std::endl;
}

std::string btm::Round::ToString()
{
    std::stringstream ss;
    int n=1;
    for(auto m:matches) {
        ss << "Match " << n << " " << m->ToString() << std::endl;
        ++n;
    }
    return ss.str();
}
