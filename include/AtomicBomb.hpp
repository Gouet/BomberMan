//
// AtomicBomb.hpp for ATOMIC in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri May 20 10:58:00 2016 Victor Gouet
// Last update Fri May 20 10:58:31 2016 Victor Gouet
//

#ifndef ATOMICBOMB_HPP_
# define ATOMICBOMB_HPP_

# include "ABomb.hpp"

class	        AtomicBomb	: public ABomb
{
public:
  AtomicBomb(int id = -1);
  AtomicBomb	&operator=(ABomb const *);
  AtomicBomb(ABomb const *);
  virtual ~AtomicBomb();

public:
  virtual void	willExplose();

private:
    bool        killObjects(irr::core::vector2df const &pos);
};

#endif
