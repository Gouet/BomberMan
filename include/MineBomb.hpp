//
// MineBomb.hpp for MINE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sat May 21 21:27:19 2016 Victor Gouet
// Last update Sat May 21 21:56:45 2016 Victor Gouet
//

#ifndef MINEBOMB_HPP_
# define MINEBOMB_HPP_

# include "ABomb.hpp"

class		MineBomb	: public ABomb
{
public:
  MineBomb(int id = 1);
  MineBomb	&operator=(ABomb const *);
  MineBomb(ABomb const *);
  virtual ~MineBomb();

public:
  virtual void	willExplose();
  virtual bool		isDestructible() const;
  virtual void		disable();
  virtual void	updateTimeOut();

private:
    bool        killObjects(irr::core::vector2df const &pos);

private:
  double		secRef;
};

#endif
