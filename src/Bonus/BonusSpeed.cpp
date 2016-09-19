//
// BonusSpeed.cpp for BONUS SPEED in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Mon May  9 13:37:03 2016 Victor Gouet
// Last update Sun Jun  5 17:34:03 2016 Victor Gouet
//

#include "BonusSpeed.hpp"
#include "Texture.hpp"
#include "SoundManager.hpp"

BonusSpeed::BonusSpeed(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusSpeed").mesh,
	   BomberManTexture::getModel("bonusSpeed").texture, "BonusSpeed", BONUS)
{

}

BonusSpeed::~BonusSpeed()
{
  dead();
}

void		BonusSpeed::take(ACharacter &player)
{
  player.setMoveSpeed(player.getMoveSpeed() + 0.5);
  SoundManager::getManager()->play("BonusSpeed.wav", (*this)->getID(), false, 0.8);
}

void		BonusSpeed::dead()
{
  (*this)->setVisible(false);
  this->setPos(irr::core::vector2df(1000, 1000));
}
