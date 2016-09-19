//
// BonusInvincible.hpp for INVINCIBLE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu May 12 18:26:37 2016 Victor Gouet
// Last update Fri Jun  3 18:30:16 2016 Victor Gouet
//
//

#ifndef BONUSINVINCIBLE_HPP_
# define BONUSINVINCIBLE_HPP_

# include "ABonus.hpp"

class	        BonusInvincible	: public ABonus
{
public:
  BonusInvincible(irr::core::vector2df const &);
  virtual ~BonusInvincible();

public:
  virtual void		take(ACharacter &);
  virtual void		dead();
};


#endif
