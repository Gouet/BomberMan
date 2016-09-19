//
// BonusBombPass.hpp for BOMB PASS in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Thu May 12 12:14:42 2016 Victor Gouet
// Last update Fri Jun  3 18:30:03 2016 Victor Gouet
//

#ifndef BONUSBOMBPASS_HPP_
# define BONUSBOMBPASS_HPP_

# include "ABonus.hpp"

class	        BonusBombPass	: public ABonus
{
public:
  BonusBombPass(irr::core::vector2df const &);
  virtual ~BonusBombPass();

public:
  virtual void		take(ACharacter &);
  virtual void		dead();
};


#endif
