//
// BonusSmallestMan.hpp for SMALLEST in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu May 12 14:34:49 2016 Victor Gouet
// Last update Fri Jun  3 18:30:24 2016 Victor Gouet
//

#ifndef BONUSSMALLESTMAN_HPP_
# define BONUSSMALLESTMAN_HPP_

# include "ABonus.hpp"

class	        BonusSmallestMan	: public ABonus
{
public:
  BonusSmallestMan(irr::core::vector2df const &);
  virtual ~BonusSmallestMan();

public:
  virtual void		take(ACharacter &);
  virtual void		dead();
};


#endif
