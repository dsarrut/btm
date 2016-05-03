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
    for(auto p:waiting_players)
        ss << "Waiting players : " << p << std::endl;
    return ss.str();
}

void btm::Round::UpdatePlayersStatus()
{
    for(auto m:matches) {
        m->UpdatePlayersStatus();
    }
    for(auto p:waiting_players) {
        p->nb_of_wait_rounds++;
    }
}
