//
// BonusPower.cpp for BONUS in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Mon May  9 15:05:25 2016 Victor Gouet
// Last update Sun Jun  5 17:35:08 2016 Victor Gouet
//

#include "BonusPower.hpp"
#include "Texture.hpp"
#include "SoundManager.hpp"

BonusPower::BonusPower(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusPower").mesh,
	   BomberManTexture::getModel("bonusPower").texture, "BonusPower", BONUS)
{

}

BonusPower::~BonusPower()
{
  dead();
}

void		BonusPower::take(ACharacter &player)
{
  player.increasePowerBomb();
  SoundManager::getManager()->play("BonusPower.wav", (*this)->getID(), false, 0.8);
}

void	        BonusPower::dead()
{
  (*this)->setVisible(false);
  this->setPos(irr::core::vector2df(1000, 1000));
}
