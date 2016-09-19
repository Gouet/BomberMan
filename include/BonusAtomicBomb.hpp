//
// BonusAtomicBomb.hpp for ATOMIC in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sat May 21 12:23:56 2016 Victor Gouet
// Last update Fri Jun  3 18:29:55 2016 Victor Gouet
//

#ifndef BONUSATOMICBOMB_HPP_
# define BONUSATOMICBOMB_HPP_

# include "ABonus.hpp"

class		BonusAtomicBomb	: public ABonus
{
public:
  BonusAtomicBomb(irr::core::vector2df const &);
  virtual ~BonusAtomicBomb();

public:
  virtual void		take(ACharacter &);
  virtual void		dead();
};

#endif
