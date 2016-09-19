//
// BonusPower.hpp for POWER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 15:04:27 2016 Victor Gouet
// Last update Fri Jun  3 18:30:20 2016 Victor Gouet
//

#ifndef BONUSPOWER_HPP_
# define BONUSPOWER_HPP_

# include "ABonus.hpp"

class		BonusPower	: public ABonus
{
public:
  BonusPower(irr::core::vector2df const &);
  virtual ~BonusPower();

public:
  virtual void		take(ACharacter &);
  virtual void		dead();
};

#endif
