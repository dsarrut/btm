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
        if (diff <= 2) return 2;
        return 0;
    }
    if (team2_points >= nb_points_to_win) {
        int diff = team2_points-team1_points;
        if (diff >= 2) return 2;
        if (diff <= 2) return 1;
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
