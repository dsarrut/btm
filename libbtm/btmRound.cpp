#include "btmRound.h"

btm::Round::Round()
{
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

btm::Status btm::Round::GetStatus()
{
    btm::Status status = Init;
    unsigned int playing=0;
    unsigned int term=0;
    for(auto m:matches) {
     if (m->GetStatus() == Init) status = Init;
     if (m->GetStatus() == Playing) ++playing;
     if (m->GetStatus() == Terminated) ++term;
    }
    if (playing == matches.size()) status = Playing;
    if (term == matches.size()) status = Terminated;
    return status;
}
