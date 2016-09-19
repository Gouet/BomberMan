//
// Created by gaspar_q on 6/1/16.
//

#include <algorithm>
#include "GameManager.hpp"
#include "Ranking.hpp"

const int	Ranking::winScore[4] = {8, 4, 2, 1};

Ranking::Ranking(size_t nbPlayers) : nbAlives(nbPlayers), nbPlayedGames(0),
                                     m_gameover(NULL), m_state(DEFAULT), endGame(false)
{

}

Ranking::Ranking(const Ranking &ranking)
{
    *this = ranking;
}

Ranking::~Ranking()
{
    clear();
}

Ranking &Ranking::operator=(const Ranking &ranking)
{
    m_gameover      = ranking.m_gameover;
    m_state         = ranking.m_state;
    playersScores   = ranking.playersScores;
    nbAlives        = ranking.nbAlives;
    nbPlayedGames   = ranking.nbPlayedGames;
    return *this;
}

bool Ranking::isTheEndOfTheGame(ACharacter *winner)
{
    if (endGame)
        return (true);
    if (nbAlives > 1)
        return (false);
    if (nbAlives == 0) {
        clear();
        m_state = DRAW;
    } else if (winner) {
        addPlayerToRank(winner);
        m_state = (++nbPlayedGames >= 3) ? END_GAME : WIN;
    }
    endGame = true;
    return (true);
}

void Ranking::addPlayerToRank(ACharacter *character)
{
    --nbAlives;
    playersScores[character->get_player()] += Ranking::winScore[nbAlives];
    podium.push_back(character);
}

void    Ranking::setPlayers(std::vector<ACharacter *> &characters)
{
    this->players = characters;
    this->nbAlives = characters.size();
}

void Ranking::clear(void)
{
    endGame = false;
    players.clear();
    podium.clear();
    nbAlives = 0;
    destroyGameOver();
}

void Ranking::displayRankingScreen()
{
    if (!m_gameover)
        m_gameover = new GameOver(this);
    m_gameover->show();
}

GameOver *Ranking::getGameOver(void) const
{
    return m_gameover;
}

void Ranking::destroyGameOver(void)
{
    if (m_gameover)
    {
        delete (m_gameover);
        m_gameover = NULL;
    }
}

Ranking::State Ranking::getState(void) const
{
    return m_state;
}

std::vector<ACharacter *> Ranking::getPodium()
{
    std::reverse(podium.begin(), podium.end());
    return (podium);
}

std::vector<ACharacter *> Ranking::getFinalPodium()
{
    std::vector<ACharacter *>   finalPodium;
    std::vector<std::pair<int, size_t >> rank;

    for (std::map<int, size_t>::const_iterator it = playersScores.begin(), end = playersScores.end(); it != end; ++it) {
        rank.push_back(std::make_pair(it->first, it->second));
    }
    std::sort(rank.begin(), rank.end(), [](std::pair<int, int> p1, std::pair<int, int> p2) { return p1.second > p2.second; });
    for (size_t i = 0; i < rank.size(); ++i) {
        finalPodium.push_back(getPlayerByID(rank[i].first));
    }
    return (finalPodium);
}

ACharacter         *Ranking::getPlayerByID(int id) const
{
    for (std::vector<ACharacter *>::const_iterator it = players.begin(), end = players.end(); it != end; ++it) {
        if ((*it)->get_player() == id)
            return *it;
    }
    return nullptr;
}

size_t     Ranking::getPlayerScore(int id) const
{
    return (this->playersScores.find(id)->second);
}

void Ranking::reset(void)
{
    clear();
    nbPlayedGames = 0;
    playersScores.clear();
}
