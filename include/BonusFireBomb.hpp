//
// BonusBombUp.hpp for BOMB UP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 15:53:10 2016 Victor Gouet
// Last update Fri Jun  3 18:30:07 2016 Victor Gouet
//

#ifndef BONUSFIREBOMB_HPP_
# define BONUSFIREBOMB_HPP_

# include "ABonus.hpp"

class		BonusFireBomb	: public ABonus
{
public:
  BonusFireBomb(irr::core::vector2df const &);
  virtual ~BonusFireBomb();

public:
  virtual void		take(ACharacter &);
  virtual void		dead();
};

#endif
