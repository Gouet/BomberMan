//
// BonusBiggestMan.cpp for BIGGEST in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Thu May 12 12:55:40 2016 Victor Gouet
// Last update Sun Jun  5 17:34:33 2016 Victor Gouet
//

#include "BonusBiggestMan.hpp"
#include "Texture.hpp"
#include "SoundManager.hpp"

BonusBiggestMan::BonusBiggestMan(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusBiggestMan").mesh,
	   BomberManTexture::getModel("bonusBiggestMan").texture, "BonusBiggestMan", BONUS)
{

}

BonusBiggestMan::~BonusBiggestMan()
{
  dead();
}

void	        BonusBiggestMan::take(ACharacter &player)
{
  player.setLifeUp();
  player.setMoveSpeed(ACharacter::BASICSPEED / 1.5);
  player->setScale(irr::core::vector3df(2.5, 2.5, 2.5));
  SoundManager::getManager()->play("BonusBiggestMan.wav", (*this)->getID(), false, 0.8);
}

void	        BonusBiggestMan::dead()
{
  (*this)->setVisible(false);
  this->setPos(irr::core::vector2df(1000, 1000));
}
