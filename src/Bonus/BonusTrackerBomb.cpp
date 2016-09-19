//
// BonusTrackerBomb.cpp for TRACKER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sat May 21 12:31:11 2016 Victor Gouet
// Last update Sun Jun  5 17:34:53 2016 Victor Gouet
//

#include "BonusTrackerBomb.hpp"
#include "TrackerBomb.hpp"
#include "BombFactory.hpp"
#include "Texture.hpp"
#include "SoundManager.hpp"

BonusTrackerBomb::BonusTrackerBomb(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusTrackerBomb").mesh,
	   BomberManTexture::getModel("bonusTrackerBomb").texture, "BonusTrackerBomb", BONUS)
{
}

BonusTrackerBomb::~BonusTrackerBomb()
{
  dead();
}

void	        BonusTrackerBomb::take(ACharacter &player)
{
  BombFactory::AddBomb<TrackerBomb>(*(player.getBombContainer()), player->getID());
  SoundManager::getManager()->play("BonusTrackerBomb.wav", (*this)->getID(), false, 0.8);
}

void	        BonusTrackerBomb::dead()
{
  (*this)->setVisible(false);
  this->setPos(irr::core::vector2df(1000, 1000));
}
