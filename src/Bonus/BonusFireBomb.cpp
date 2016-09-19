//
// BonusBombUp.cpp for BONUS UP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Mon May  9 15:54:55 2016 Victor Gouet
// Last update Sun Jun  5 17:34:39 2016 Victor Gouet
//

#include "BonusFireBomb.hpp"
#include "FragBomb.hpp"
#include "BombFactory.hpp"
#include "Texture.hpp"
#include "SoundManager.hpp"

BonusFireBomb::BonusFireBomb(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusFireBomb").mesh,
	   BomberManTexture::getModel("bonusFireBomb").texture, "BonusFireBomb", BONUS)
{
}

BonusFireBomb::~BonusFireBomb()
{
  dead();
}

void	        BonusFireBomb::take(ACharacter &player)
{
  BombFactory::AddBomb<FireBomb>(*(player.getBombContainer()), player->getID());
  SoundManager::getManager()->play("BonusFireBomb.wav", (*this)->getID(), false, 0.8);
}

void	        BonusFireBomb::dead()
{
  (*this)->setVisible(false);
  this->setPos(irr::core::vector2df(1000, 1000));
}
