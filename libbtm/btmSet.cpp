#include "btmSet.h"

btm::Set::Set()
{
    team1_points = 0;
    team2_points = 0;
    nb_points_to_win = 11;
}

int btm::Set::GetWinner()
{
    if (team1_points >= nb_points_to_win) {
        int diff = team1_points-team2_points;
        if (diff >= 2) return 1;
        if (diff == -2) return 2;
        return 0;
    }
    if (team2_points >= nb_points_to_win) {
        int diff = team2_points-team1_points;
        if (diff >= 2) return 2;
        if (diff == -2) return 1;
        return 0;
    }
    return 0;
}

void btm::Set::GenerateRandomScore(std::mt19937 & rng)
{
   std::uniform_int_distribution<int> genWinner(1, 2);
   std::uniform_int_distribution<int> genPoints(0, nb_points_to_win);

    int winner = genWinner(rng);
    if (winner == 1) {
        team1_points = nb_points_to_win;
        team2_points = genPoints(rng);
        int diff = team1_points-team2_points;
        if (diff<2) team1_points = team2_points+2;
    }
    if (winner == 2) {
        team2_points = nb_points_to_win;
        team1_points = genPoints(rng);
        int diff = team2_points-team1_points;
        if (diff<2) team2_points = team1_points+2;
    }
}

void btm::Set::SetScore(int team, int points)
{
    if (team == 1) team1_points = points;
    else team2_points = points;
}

unsigned int btm::Set::GetTeamPoints(unsigned int team) const
{
    if (team == 1) return GetTeam1Points();
    if (team == 2) return GetTeam2Points();
    DD("Error team");
    exit(1);
}

btm::Status btm::Set::GetStatus()
{
    if (team1_points == team2_points and team1_points == 0) return Init;
    if (GetWinner() != 0) return Terminated;
    return Playing;
}
