#include "btmMatch.h"
#include "btmRound.h"
#include "btmTournament.h"

btm::Match::Match(std::shared_ptr<btm::Round> r, int n)
{
    round = r;
    for(auto i=0; i<3; i++)
        sets.push_back(btm::Set::New(round->GetNumberOfPointsToWin()));
    match_nb = n;
    QObject::connect(this, SIGNAL(matchStatusHasChanged()),
                     r.get(), SLOT(on_match_status_changed()));
    QObject::connect(this, SIGNAL(matchScoreHasChanged()),
                     r.get(), SLOT(on_match_score_changed()));
}

btm::Match::pointer btm::Match::New(std::shared_ptr<btm::Round> r, int n)
{
    return std::make_shared<Match>(r, n);
}

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
    emit matchScoreHasChanged();
    emit matchStatusHasChanged();
}

void btm::Match::SetScore(int team, int theSet, int points)
{
    DD("set score");
    std::cout << team << " " << theSet << " " << points << std::endl;
    DD(match_nb);

    // current state
    btm::Set::pointer set = GetSet(theSet);
    auto old_points = set->GetTeamPoints(team);
    auto old_set_winner = set->GetWinner();
    auto old_match_winner = GetWinner();
    btm::Player::pointer p1, p2, p3, p4;
    auto other_team = (team == 1 ? 2:1);
    DD(other_team);
    if (team == 1) {
        p1 = players[0];
        p2 = players[1];
        p3 = players[2];
        p4 = players[3];
    }
    else {
        p1 = players[2];
        p2 = players[3];
        p3 = players[0];
        p4 = players[1];
    }

    // points
    DD("points");
    set->SetScore(team, points);
    DD("a");
    p1->UpdateWinPoints(points-old_points);
    DD("b");
    p2->UpdateWinPoints(points-old_points);

    // sets
    DD("sets");
    auto set_winner = set->GetWinner();
    if (old_set_winner == set_winner) {
        emit matchScoreHasChanged();
        return;
    }

    if (set_winner == team) {
        p1->UpdateWinSets(1);
        p2->UpdateWinSets(1);
    }
    if (set_winner == other_team) {
        p3->UpdateWinSets(1);
        p4->UpdateWinSets(1);
    }
    if (old_set_winner == team) {
        p1->UpdateWinSets(-1);
        p2->UpdateWinSets(-1);
    }
    if (old_set_winner == other_team) {
        p3->UpdateWinSets(-1);
        p4->UpdateWinSets(-1);
    }
    emit matchScoreHasChanged();

    // match
    DD("match");
    auto match_winner = GetStatus();
    if (match_winner == old_match_winner) return;

    if (match_winner == team) {
        p1->UpdateWinMatches(1);
        p2->UpdateWinMatches(1);
    }
    if (match_winner == other_team) {
        p3->UpdateWinMatches(1);
        p4->UpdateWinMatches(1);
    }
    if (old_match_winner == team) {
        p1->UpdateWinMatches(-1);
        p2->UpdateWinMatches(-1);
    }
    if (old_match_winner == other_team) {
        p3->UpdateWinMatches(-1);
        p4->UpdateWinMatches(-1);
    }
    emit matchStatusHasChanged();
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
    if (i==0) return;
    if (i>4) return;
    if (players[i-1] != p) {
        players[i-1] = p;
        /*   int team=2;
        if (i == 1 or i == 2) team = 1;
        for(auto s=1; s<=3; s++)
            SetScore(team, s, GetSet(s)->GetTeamPoints(team));*/
    }
}

btm::Player::pointer btm::Match::GetPlayer(int i)
{
    return players[i-1];
}

btm::Set::pointer btm::Match::GetSet(int i)
{
    if (i == 0) {
        DD("error set must be 1-3");
        exit(0);
    }
    return sets[i-1];
}

void btm::Match::SwapPlayer(int player1,
                            btm::Match::pointer m2,
                            int player2)
{
    auto temp = GetPlayer(player1);
    SetPlayer(player1, m2->GetPlayer(player2));
    m2->SetPlayer(player2, temp);
}

void btm::Match::FindPlayer(btm::Player::pointer p, int &ip)
{
    ip = 0;
    if (p == players[0]) ip = 1;
    if (p == players[1]) ip = 2;
    if (p == players[2]) ip = 3;
    if (p == players[3]) ip = 4;
}

void btm::Match::Save(std::ostream &os)
{
    for(auto p:players) os << p->id << " ";
    os << std::endl;
    os << sets.size() << std::endl;
    for(auto s:sets) s->Save(os);
}

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

std::string btm::Match::ToString() const
{
    std::stringstream ss;
    for(auto p:players)
        ss << p << " ";
    for(auto s:sets)
        ss << s << " ";
    return ss.str();
}
