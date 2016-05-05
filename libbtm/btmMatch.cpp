#include "btmMatch.h"

btm::Match::Match()
{
    score = 0;
    for(auto i=0; i<3; i++) sets.push_back(btm::Set::New());
}

std::string btm::Match::ToString()
{
    std::stringstream ss;
    ss << players[0]->ToString() << "+" << players[1]->ToString()
       << "    vs    "
       << players[2]->ToString() << "+" << players[3]->ToString()
       << " --> " << score;
    return ss.str();
}

void btm::Match::UpdatePlayersStatus()
{
    if (score == 0) return;
    for(auto p:players) p->nb_of_matches++;
    if (score == 1) {
        players[0]->nb_of_win_matches++;
        players[1]->nb_of_win_matches++;
        players[2]->nb_of_lost_matches++;
        players[3]->nb_of_lost_matches++;
    }
    if (score == 2) {
        players[2]->nb_of_win_matches++;
        players[3]->nb_of_win_matches++;
        players[0]->nb_of_lost_matches++;
        players[1]->nb_of_lost_matches++;
    }
}

void btm::Match::GenerateRandomScore(std::mt19937 & rng)
{
    sets[0]->GenerateRandomScore(rng);
    sets[1]->GenerateRandomScore(rng);
    if (sets[0]->GetWinner() != sets[1]->GetWinner())
        sets[2]->GenerateRandomScore(rng);
    int w0 = sets[0]->GetWinner();
    int w1 = sets[1]->GetWinner();
    if (w0 == w1) score = w0;
    else score = sets[2]->GetWinner();
}
