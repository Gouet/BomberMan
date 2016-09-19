//
// FragBomb.hpp for FRAG in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri May 20 16:23:46 2016 Victor Gouet
// Last update Fri May 20 16:43:14 2016 Victor Gouet
//

#ifndef FRAGBOMB_HPP_
# define FRAGBOMB_HPP_

# include "ABomb.hpp"

class		FragBomb	: public ABomb
{
public:
  FragBomb(int id = -1);
  FragBomb	&operator=(ABomb const *);
  FragBomb(ABomb const *);
  virtual ~FragBomb();

public:
  virtual void	willExplose();

private:
    bool        killObjects(irr::core::vector2df const &pos);

private:
  irr::core::vector2df	*vec;
};

#endif
