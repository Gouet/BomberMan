//
// BonusSmallestMan.cpp for SMALLEST in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Thu May 12 14:33:06 2016 Victor Gouet
// Last update Sun Jun  5 17:34:48 2016 Victor Gouet
//

#include "BonusSmallestMan.hpp"
#include "Texture.hpp"
#include "SoundManager.hpp"

BonusSmallestMan::BonusSmallestMan(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusSmallestMan").mesh,
	   BomberManTexture::getModel("bonusSmallestMan").texture, "BonusSmallestMan", BONUS)
{

}

BonusSmallestMan::~BonusSmallestMan()
{
  dead();
}

void	        BonusSmallestMan::take(ACharacter &player)
{
  player.setMoveSpeed(ACharacter::BASICSPEED * 1.5);
  player.setBasicLife();
  player->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
  SoundManager::getManager()->play("BonusSmallestMan.wav", (*this)->getID(), false, 0.8);
}

void	        BonusSmallestMan::dead()
{
  (*this)->setVisible(false);
  this->setPos(irr::core::vector2df(1000, 1000));
}
