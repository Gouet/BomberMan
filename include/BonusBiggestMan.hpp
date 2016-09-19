//
// BonusBiggestMan.hpp for BIGGEST MAN in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu May 12 12:55:09 2016 Victor Gouet
// Last update Fri Jun  3 18:30:00 2016 Victor Gouet
//

#ifndef BONUSBIGGESTMAN_HPP_
# define BONUSBIGGESTMAN_HPP_

# include "ABonus.hpp"

class	        BonusBiggestMan	: public ABonus
{
public:
  BonusBiggestMan(irr::core::vector2df const &);
  virtual ~BonusBiggestMan();

public:
  virtual void		take(ACharacter &);
  virtual void		dead();
};


#endif
