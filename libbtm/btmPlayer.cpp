#include "btmPlayer.h"
#include "btmMatch.h"
#include "btmRound.h"
#include <regex>
#include <sstream>

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
    DD("Computescores");
    nb_of_points = 0;
    nb_of_win_matches = 0;
    nb_of_matches = matches.size();
    nb_of_win_sets = 0;
    for(auto & m:matches) {
        int team = m->GetPlayerTeam(shared_from_this());
        nb_of_points += m->GetNumberOfPoints(team);
        if (m->GetWinner() == team) nb_of_win_matches++;
        if (m->GetSet(1)->GetWinner() == team) nb_of_win_sets++;
        if (matches[0]->GetRound()->GetNumberOfSetsToWin() > 1) {
            if (m->GetSet(2)->GetWinner() == team) nb_of_win_sets++;
            // The third set only counts if needed
            if ((m->GetSet(1)->GetWinner() != m->GetSet(2)->GetWinner())
                    and m->GetSet(1)->GetWinner() != 0
                    and (m->GetSet(3)->GetWinner() == team)) {
                nb_of_win_sets++;
            }
        }
    }
    DD("end compute scores");
    emit playerScoreChanged();
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
std::vector<std::shared_ptr<btm::Match> > & btm::Player::GetMatches()
{
    return matches;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Player::SetParticipateFlag(bool b)
{
    participate = b;
    emit playerParticipateFlagChanged(shared_from_this());
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Player::ChangeMatch(std::shared_ptr<btm::Match> m1,
                              std::shared_ptr<btm::Match> m2)
{
    if (m1->GetMatchNb() == m2->GetMatchNb()) return;
    for(unsigned int i=0; i<matches.size(); i++) { //& m:matches) {
        /*if (matches[i]->GetMatchNb() == m1->GetMatchNb()) {
            DD(i);
            DD(matches[i]->GetMatchNb());
            matches[i] = m2;
            DD(m2->GetMatchNb());
            DD(matches[i]->GetMatchNb());
            return;
        }*/
    }
    //exit(0);
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
    os << "Player " << id << " [ " << name << " ]" << std::endl;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Player::Load(std::istream &is)
{
    std::string line;
    std::getline(is, line);
    std::istringstream iss(line);
    std::string s;
    iss >> s; // Player
    iss >> s; // id
    id = atoi(s.c_str());
    iss >> s; // [
    iss >> s;
    name = "";
    while (iss && s != "]") {
        name += s+" ";
        iss >> s;
    }
    DD(id);
    DD(name);
    // remove spaces
    //name = std::regex_replace(name, std::regex("^ +| +$|( ) +"), "$1");
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
