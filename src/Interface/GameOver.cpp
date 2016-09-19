//
// Created by consta_n on 25/05/16.
//

#include <utility>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stack>
#include <list>
#include <iostream>
#include "BomberMap.hpp"
#include "ACharacter.hpp"
#include "GameManager.hpp"
#include "GameOver.hpp"
#include "SoundManager.hpp"

GameOver::GameOver(Ranking *ranking) :
        m_ranking(ranking),
        m_status(false),
        m_env(IrrlichtController::getDevice()->getGUIEnvironment()),
        m_skin(m_env->getSkin()),
        m_save_font(m_skin->getFont()),
        m_font(m_env->getFont(BINDIR"media/font/arcade_font.xml")),
        m_st_text(NULL)
{
    if (m_font)
        m_skin->setFont(m_font);
    highScore = new LoadHighScore("bomberman.score");
    rankingList = NULL;
}

GameOver::~GameOver()
{
    if (m_skin)
        m_skin->setFont(m_save_font);
    if (highScore)
      {
	highScore->flush();
	delete highScore;
      }
}

void	GameOver::saveHighScore(std::vector<ACharacter *> const &podium)
{
  std::vector<ACharacter *>::const_iterator	it = podium.begin();
  int					i = 0;

  while (it != podium.end())
    {
      highScore->setHighScore(new t_highScore(this->m_ranking->getPlayerScore((*it)->get_player()), (*it)->getName()));
      ++it;
      ++i;
    }
}

void		GameOver::displayRanking()
{
  std::vector<t_highScore *>    vec = highScore->getAllHighScore();
  size_t				rankingListSizeWidth = 800;
  size_t				rankingListSizeHeight = 700;

  rankingList = IrrlichtController::getSceneManager()->getGUIEnvironment()->addListBox(irr::core::rect<irr::s32>(IrrlichtController::width / 2 - rankingListSizeWidth / 2, IrrlichtController::height / 2 - rankingListSizeHeight / 2, IrrlichtController::width / 2 + rankingListSizeWidth / 2, IrrlichtController::height / 2 + rankingListSizeHeight / 2));

  int	i = 0;
  for (std::vector<t_highScore *>::iterator it = vec.begin(), end = vec.end() ; it != end ; ++it)
    {
      std::wstring wstring = GameManager::ToWstring((*it)->getName() + "    " + std::to_string((*it)->getScore()));
      rankingList->addItem(wstring.c_str());
      rankingList->setItemOverrideColor(i++, irr::video::SColor(255, 255, 255, 255));
    }
}

void GameOver::show()
{
    irr::scene::ICameraSceneNode    *camera;
    std::wstringstream ss;

    camera = GameManager::SharedInstance()->getCam(GameManager::GameCamera::MAIN_MENU_CAM);
    camera->setPosition(irr::core::vector3df(-50, 25, 0));
    camera->setTarget(irr::core::vector3df(0, 25, 0));
    camera->removeAnimators();
    GameManager::SharedInstance()->activeCam(GameManager::GameCamera::MAIN_MENU_CAM);
    SoundManager::getManager()->stopAll();
    ACharacter *winner;
    switch (m_ranking->getState())
    {
        case Ranking::END_GAME:
            winner = m_ranking->getPlayerByID(displayPodium(m_ranking->getFinalPodium()));
            ss << "The winner is " << winner->getName().c_str() << " !";
	    
            saveHighScore(m_ranking->getFinalPodium());
            SoundManager::getManager()->play("winner.wav");
	    displayRanking();
            m_status = true;
            break;
        case Ranking::WIN:
            winner = m_ranking->getPlayerByID(displayPodium(m_ranking->getPodium()));
            ss << winner->getName().c_str() << " win!";
            SoundManager::getManager()->play("gameResults.wav");
            break;
        case Ranking::DRAW:
            ss << "Draw !";
            SoundManager::getManager()->play("drawGame.wav");
            break;
        default:
            break;
    }
    m_st_text = m_env->addStaticText(ss.str().c_str(),
                                     irr::core::rect<irr::s32>(0, 100, (irr::s32) IrrlichtController::width, 200),
                                     false, true);
    m_st_text->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
    m_st_text->setTextAlignment(irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER, irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER);
    m_env->drawAll();
}

int     GameOver::displayPodium(std::vector<ACharacter *> const &podium) const
{
    if (podium[0]) {
        podium[0]->getSceneNode()->setPosition(irr::core::vector3df(0, 0, 0));
        podium[0]->getSceneNode()->setRotation(irr::core::vector3df(0, 90, 0));
        podium[0]->getSceneNode()->setScale(irr::core::vector3df(1, 1, 1));
    }
    if (podium[1]) {
        podium[1]->getSceneNode()->setPosition(irr::core::vector3df(50, 0, 50));
        podium[1]->getSceneNode()->setRotation(irr::core::vector3df(0, 90, 0));
        podium[1]->getSceneNode()->setScale(irr::core::vector3df(1, 1, 1));

    }
    if (podium[2]) {
        podium[2]->getSceneNode()->setPosition(irr::core::vector3df(50, 0, -50));
        podium[2]->getSceneNode()->setRotation(irr::core::vector3df(0, 90, 0));
        podium[2]->getSceneNode()->setScale(irr::core::vector3df(1, 1, 1));
    }
    return (podium[0]->get_player());
}

bool GameOver::getStatus() const
{
    return m_status;
}
