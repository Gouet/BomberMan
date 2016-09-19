//
// BonusFragBomb.cpp for BONUS in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sat May 21 12:04:39 2016 Victor Gouet
// Last update Sun Jun  5 17:34:15 2016 Victor Gouet
//

#include "BonusFragBomb.hpp"
#include "FragBomb.hpp"
#include "BombFactory.hpp"
#include "Texture.hpp"
#include "SoundManager.hpp"

BonusFragBomb::BonusFragBomb(irr::core::vector2df const &pos)
  : ABonus(pos, BomberManTexture::getModel("bonusFragBomb").mesh,
	   BomberManTexture::getModel("bonusFragBomb").texture, "BonusFragBomb", BONUS)
{

}

BonusFragBomb::~BonusFragBomb()
{
  dead();
}

void	        BonusFragBomb::take(ACharacter &player)
{
  BombFactory::AddBomb<FragBomb>(*(player.getBombContainer()), player->getID());
  SoundManager::getManager()->play("BonusFragBomb.wav", (*this)->getID(), false, 0.8);
}

void	        BonusFragBomb::dead()
{
  (*this)->setVisible(false);
  this->setPos(irr::core::vector2df(1000, 1000));
}
