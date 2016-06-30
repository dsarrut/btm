#include "btmMatch.h"
#include "btmRound.h"
#include "btmTournament.h"

// -----------------------------------------------------------------------------
btm::Match::Match(std::shared_ptr<btm::Round> r, int n,
                  btm::Player::pointer p1,
                  btm::Player::pointer p2,
                  btm::Player::pointer p3,
                  btm::Player::pointer p4)
{
    round = r;
    for(auto i=0; i<3; i++)
        sets.push_back(btm::Set::New(round->GetNumberOfPointsToWin()));
    match_nb = n;

    players[0] = p1;
    players[1] = p2;
    players[2] = p3;
    players[3] = p4;
    for(auto p:players) p->AddMatch(pointer(this));

    // TO CHECK ?
    QObject::connect(this, SIGNAL(matchStatusHasChanged()),
                     r.get(), SLOT(on_match_status_changed()));
    QObject::connect(this, SIGNAL(matchScoreHasChanged()),
                     r.get(), SLOT(on_match_score_changed()));
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
btm::Match::pointer btm::Match::New(std::shared_ptr<btm::Round> r, int n,
                                    btm::Player::pointer p1,
                                    btm::Player::pointer p2,
                                    btm::Player::pointer p3,
                                    btm::Player::pointer p4)
{
    return std::make_shared<Match>(r, n, p1, p2, p3, p4);
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
int btm::Match::GetNumberOfPoints(int team)
{
    int points = 0;
    for(auto s:sets)
        points += s->GetTeamPoints(team);
    return points;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
std::string btm::Match::ToString()
{
    std::stringstream ss;
    ss << players[0]->ToString() << "+" << players[1]->ToString()
                                 << "    vs    "
                                 << players[2]->ToString() << "+"
                                 << players[3]->ToString()
                                 << " --> " << GetWinner();
    return ss.str();
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Match::ComputePlayersStatus()
{
    int score = GetWinner();
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
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
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
    // Update players stats
    for(auto p:players) p->ComputeScores();
    emit matchScoreHasChanged();
    emit matchStatusHasChanged();
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Match::SetScore(int team, int theSet, unsigned int points)
{
    // Check the score changes, do nothing if it is the same
    if (GetSet(theSet)->GetTeamPoints(team) == points)
        return;

    // Change the score of the set
    GetSet(theSet)->SetScore(team, points);

    // Update player score
    for(auto p:players)
        p->ComputeScores();

    // Say world it has changed
    emit matchScoreHasChanged();
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
int btm::Match::GetWinner()
{
    if (sets[0]->GetWinner() == 0) return 0;
    if (sets[0]->GetWinner() == sets[1]->GetWinner())
        return sets[0]->GetWinner();
    if (sets[1]->GetWinner() == 0) return 0;
    return sets[2]->GetWinner();
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
btm::Status btm::Match::GetStatus()
{
    if (GetWinner() != 0) return Terminated;
    if (sets[0]->GetStatus() == Init and
            sets[1]->GetStatus() == Init and
            sets[2]->GetStatus() == Init) return Init;
    return Playing;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Match::SetPlayer(unsigned int i, btm::Player::pointer p)
{
    if (i<1 or i>4) {
        DD("ERROR set Player");
        DD(i);
        exit(0);
    }
    if (players[i-1] != p) {
        players[i-1] = p;
        DD("emit");
        emit matchPlayersHaveChanged();
        emit matchScoreHasChanged();
        DD("fin emit");
    }
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
btm::Player::pointer btm::Match::GetPlayer(int i)
{
    return players[i-1];
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
int btm::Match::GetPlayerTeam(btm::Player::pointer p)
{
    int team = 1;
    if (p == players[2] or p == players[3]) team = 2;
    return team;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
btm::Set::pointer btm::Match::GetSet(int i)
{
    if (i == 0) {
        DD("error set must be 1-3");
        exit(0);
    }
    return sets[i-1];
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Match::SwapPlayer(btm::Player::pointer p1,
                            int ip1,
                            btm::Match::pointer m2,
                            btm::Player::pointer p2,
                            int ip2)
{
    DD("swap player");
    DD(p1->GetName());
    DD(p2->GetName());
    DD(p1->GetMatches()[0]->GetMatchNb());
    DD(p2->GetMatches()[0]->GetMatchNb());
    //return; //FIXME
    auto m1 = shared_from_this();
    if (m1 != m2) {
        //p1->ChangeMatch(m1, m2);
        //p2->ChangeMatch(m2, m1);
        DD(p1->GetMatches()[0]->GetMatchNb());
        DD(p2->GetMatches()[0]->GetMatchNb());
    }
    SetPlayer(ip1,p2);
    m2->SetPlayer(ip2,p1);
    //DD("emit");
    //std::cout.flush();
    // Both match change !
    //emit matchPlayersHaveChanged();
    //std::cout.flush();
    //DD("after emit");
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Match::ChangePlayer(btm::Player::pointer p1,
                              btm::Player::pointer p2)
{
    DDF();
    int i;
    FindPlayer(p1, i);
    DD(i);
    players[i] = p2;
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Match::FindPlayer(btm::Player::pointer p, int &ip)
{
    ip = 0;
    if (p->GetId() == players[0]->GetId()) { ip = 1; return; }
    if (p->GetId() == players[1]->GetId()) { ip = 2; return; }
    if (p->GetId() == players[2]->GetId()) { ip = 3; return; }
    if (p->GetId() == players[3]->GetId()) { ip = 4; return; }
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Match::Save(std::ostream &os)
{
    for(auto p:players) os << p->id << " ";
    os << std::endl;
    os << sets.size() << std::endl;
    for(auto s:sets) s->Save(os);
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
void btm::Match::Load(std::istream &is)
{
    for(unsigned int i=0; i<players.size(); i++) {
        int id;
        is >> id;
        auto p = round->tournament->FindPlayerById(id);
        //SetPlayer(i,p);
        players[i] = p;
    }
    int nb_sets;
    is >> nb_sets;
    for(auto s:sets) s->Load(is);
}
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
std::string btm::Match::ToString() const
{
    std::stringstream ss;
    for(auto p:players)
        ss << p << " ";
    for(auto s:sets)
        ss << s << " ";
    return ss.str();
}
// -----------------------------------------------------------------------------
