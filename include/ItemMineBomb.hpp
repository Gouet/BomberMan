//
// ItemMineBomb.hpp for MINE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sun May 22 13:02:16 2016 Victor Gouet
// Last update Sun May 22 13:26:57 2016 Victor Gouet
//

#ifndef ITEMMINEBOMB_HPP_
# define ITEMMINEBOMB_HPP_

# include "MineBomb.hpp"
# include "AItem.hpp"

class	ItemMineBomb	: public AItem
{
public:
  ItemMineBomb(irr::core::vector2df const &);
  virtual ~ItemMineBomb();

public:
  virtual void		use(irr::core::vector2df const &, irr::core::vector2df const &);
  
};

#endif
