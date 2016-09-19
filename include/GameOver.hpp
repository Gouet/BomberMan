//
// Created by consta_n on 25/05/16.
//

#ifndef CPP_INDIE_STUDIO_GAMEOVER_HPP
#define CPP_INDIE_STUDIO_GAMEOVER_HPP

#include <vector>
#include <stack>
#include "ACharacter.hpp"
#include "LoadHighScore.hpp"

class Ranking;

class GameOver
{
private:
    Ranking                   *m_ranking;
    bool                      m_status;
    irr::gui::IGUIEnvironment *m_env;
    irr::gui::IGUISkin        *m_skin;
    irr::gui::IGUIFont        *m_save_font;
    irr::gui::IGUIFont        *m_font;
    irr::gui::IGUIStaticText  *m_st_text;
    LoadHighScore			*highScore;
    irr::gui::IGUIListBox		*rankingList;

public:
    GameOver(Ranking *ranking);
    ~GameOver();

public:
    void show();
    bool getStatus() const;

private:
    int     displayPodium(std::vector<ACharacter *> const &podium) const;
    void	saveHighScore(std::vector<ACharacter *> const &podium);
    void    displayRanking();
};


#endif //CPP_INDIE_STUDIO_GAMEOVER_HPP
