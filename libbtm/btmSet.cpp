#include "btmSet.h"

// -----------------------------------------------------------------------------
btm::Set::Set(int s)
{
    team1_points = 0;
    team2_points = 0;
    nb_points_to_win = s;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
int btm::Set::GetWinner()
{
    if (team1_points < nb_points_to_win-1 and
            team2_points == nb_points_to_win) return 2;
    if (team2_points < nb_points_to_win-1 and
            team1_points == nb_points_to_win) return 1;

    if (team1_points < nb_points_to_win and
            team2_points < nb_points_to_win) return 0;

    int diff = team1_points-team2_points;
    if (diff == 2) return 1;
    if (diff == -2) return 2;
    return 0;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
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
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Set::SetScore(int team, int points)
{
    if (team == 1) team1_points = points;
    else team2_points = points;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
unsigned int btm::Set::GetTeamPoints(unsigned int team) const
{
    if (team == 1) return GetTeam1Points();
    return GetTeam2Points();
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Set::UpdatePlayerStats(int team, btm::Player::pointer m)
{
    if (GetWinner() == 0) return;
    if (team == GetWinner()) ++m->nb_of_win_sets;
    if (team == 1) m->nb_of_points += team1_points;
    if (team == 2) m->nb_of_points += team2_points;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Set::Save(std::ostream &os)
{
    os << team1_points << " " << team2_points << std::endl;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Set::Load(std::istream &is)
{
    is >> team1_points;
    is >> team2_points;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
std::string btm::Set::ToString() const
{
    std::stringstream ss;
    ss << team1_points << "/" << team2_points << " " ;
    return ss.str();
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
btm::Status btm::Set::GetStatus()
{
    if (team1_points == team2_points and team1_points == 0) return Init;
    if (GetWinner() != 0) return Terminated;
    return Playing;
}
// -----------------------------------------------------------------------------
