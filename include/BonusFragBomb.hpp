//
// BonusFragBomb.hpp for BONUS in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sat May 21 12:09:24 2016 Victor Gouet
// Last update Fri Jun  3 18:30:11 2016 Victor Gouet
//

#ifndef BONUSFRAGBOMB_HPP_
# define BONUSFRAGBOMB_HPP_

# include "ABonus.hpp"

class		BonusFragBomb	: public ABonus
{
public:
  BonusFragBomb(irr::core::vector2df const &);
  virtual ~BonusFragBomb();

public:
  virtual void		take(ACharacter &);
  virtual void		dead();
};

#endif
