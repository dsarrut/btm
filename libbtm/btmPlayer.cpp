#include "btmPlayer.h"
#include "btmMatch.h"

// -----------------------------------------------------------------------------
btm::Player::Player()
{
    static int current_id = 0;
    current_id++;
    id = current_id;
    ResetStatus();
    participate = true;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Player::SetName(std::string s)
{
    name = s;
    emit playerNameChanged();
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Player::AddMatch(std::shared_ptr<btm::Match> m)
{
    matches.push_back(m);
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Player::ComputeScores()
{
    nb_of_points = 0;
    nb_of_win_matches = 0;
    nb_of_matches = matches.size();
    nb_of_win_sets = 0;
    for(auto m:matches) {
        int team = m->GetPlayerTeam(shared_from_this());
        nb_of_points += m->GetNumberOfPoints(team);
        if (m->GetWinner() == team) nb_of_win_matches++;
        if (m->GetSet(1)->GetWinner() == team) nb_of_win_sets++;
        if (m->GetSet(2)->GetWinner() == team) nb_of_win_sets++;
        // The third set only counts if needed
        if (m->GetSet(1)->GetWinner() != m->GetSet(1)->GetWinner()
                and m->GetSet(1)->GetWinner() != 0
                and m->GetSet(3)->GetWinner() == team) nb_of_win_sets++;
    }
    emit playerScoreChanged();
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
std::string btm::Player::ToString() const
{
    std::stringstream ss;
    ss << name;
    return ss.str();
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
std::string btm::Player::StatusToString() const
{
    std::stringstream ss;
    ss << "M " << nb_of_matches
       << "  W " << nb_of_win_matches
       << "  L " << nb_of_lost_matches
       << "  t " << nb_of_wait_rounds;
    return ss.str();
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Player::ResetStatus()
{
    nb_of_wait_rounds = 0;
    nb_of_lost_matches = 0;
    nb_of_matches = 0;
    nb_of_win_matches = 0;
    nb_of_points = 0;
    nb_of_win_sets = 0;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Player::Save(std::ostream &os)
{
    os << name << std::endl;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
bool BothAreSpaces(char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
void btm::Player::Load(std::istream &is)
{
    std::getline(is, name);
    // remove double spaces
    std::string::iterator new_end =
            std::unique(name.begin(),
                        name.end(), BothAreSpaces);
    name.erase(new_end, name.end());
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::GenerateRandomPlayers(btm::Player::vector & players, int n)
{
    for(auto i=0; i<n; i++) {
        auto p = btm::Player::New();
        p->name = btm::RandomString(10)+" "+btm::RandomString(10);
        players.push_back(p);
    }
}
// -----------------------------------------------------------------------------
