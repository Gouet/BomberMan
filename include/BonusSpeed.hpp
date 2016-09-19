//
// BonusSpeed.hpp for SPEED BONUS in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 13:35:03 2016 Victor Gouet
// Last update Fri Jun  3 18:30:28 2016 Victor Gouet
//

#ifndef BONUSSPEED_HPP_
# define BONUSSPEED_HPP_

# include "ABonus.hpp"

class	BonusSpeed	: public ABonus
{
public:
  BonusSpeed(irr::core::vector2df const &);
  virtual ~BonusSpeed();

public:
  virtual void		take(ACharacter &);
  virtual void		dead();

};

#endif
