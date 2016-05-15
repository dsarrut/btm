#include "btmMatch.h"

btm::Match::Match(int n)
{
    score = 0;
    for(auto i=0; i<3; i++) sets.push_back(btm::Set::New());
    match_nb = n;
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
    for(auto i=0; i<3; i++) {
        sets[i]->UpdatePlayerStats(1,players[0]);
        sets[i]->UpdatePlayerStats(1,players[1]);
        sets[i]->UpdatePlayerStats(2,players[2]);
        sets[i]->UpdatePlayerStats(2,players[3]);
    }
}

void btm::Match::GenerateRandomScore(std::mt19937 & rng)
{
    sets[0]->GenerateRandomScore(rng);
    sets[1]->GenerateRandomScore(rng);
    if (sets[0]->GetWinner() != sets[1]->GetWinner())
        sets[2]->GenerateRandomScore(rng);
    else {
        sets[2]->SetScore(1,0);
        sets[2]->SetScore(2,0);
    }
    score = GetWinner();
    emit matchScoreHasChanged();
    emit matchStatusHasChanged();
}

void btm::Match::SetScore(int team, int set, int points)
{
    int s = GetStatus();
    DD(s);
    sets[set-1]->SetScore(team,points);
    emit matchScoreHasChanged();
    if (GetWinner() != 0) {
        if (sets[0]->GetWinner() == sets[1]->GetWinner()) {
            sets[2]->SetScore(1,0);
            sets[2]->SetScore(2,0);
        }
    }
    DD(GetStatus());
    if (s != GetStatus()) emit matchStatusHasChanged();
}

int btm::Match::GetWinner()
{
    if (sets[0]->GetWinner() == 0) return 0;
    if (sets[0]->GetWinner() == sets[1]->GetWinner())
        return sets[0]->GetWinner();
    if (sets[1]->GetWinner() == 0) return 0;
    return sets[2]->GetWinner();
}

btm::Status btm::Match::GetStatus()
{
    if (GetWinner() != 0) return Terminated;
    if (sets[0]->GetStatus() == Init and
            sets[1]->GetStatus() == Init and
            sets[2]->GetStatus() == Init) return Init;
    return Playing;
}

void btm::Match::SetPlayer(unsigned int i, btm::Player::pointer p)
{
    if (i>=4) return;
    if (players[i] != p) {
        players[i] = p;
        emit matchPlayersHaveChanged();
    }
    DD("Set player is the same");
}

void btm::Match::SwitchPlayer(int player1,
                              btm::Match::pointer m2,
                              int player2)
{
    auto temp = GetPlayer(player1);
    SetPlayer(player1, m2->GetPlayer(player2));
    m2->SetPlayer(player2, temp);
}
