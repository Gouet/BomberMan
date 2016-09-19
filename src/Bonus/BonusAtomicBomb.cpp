//
// BonusAtomicBomb.cpp for BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Sat May 21 12:19:25 2016 Victor Gouet
// Last update Sun Jun  5 17:34:23 2016 Victor Gouet
//

#include "BonusAtomicBomb.hpp"
#include "BombFactory.hpp"
#include "Texture.hpp"
#include "AtomicBomb.hpp"
#include "SoundManager.hpp"

BonusAtomicBomb::BonusAtomicBomb(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusAtomicBomb").mesh,
	   BomberManTexture::getModel("bonusAtomicBomb").texture, "BonusAtomicBomb", BONUS)
{

}

BonusAtomicBomb::~BonusAtomicBomb()
{
  dead();
}

void	        BonusAtomicBomb::take(ACharacter &player)
{
  BombFactory::AddBomb<AtomicBomb>(*(player.getBombContainer()), player->getID());
  SoundManager::getManager()->play("BonusAtomicBomb.wav", (*this)->getID(), false, 0.8);
}

void	        BonusAtomicBomb::dead()
{
  (*this)->setVisible(false);
  this->setPos(irr::core::vector2df(1000, 1000));
}
