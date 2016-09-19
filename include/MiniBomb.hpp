//
// MiniBomb.hpp for MINI in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri May 20 16:29:00 2016 Victor Gouet
// Last update Sun Jun  5 12:57:59 2016 Matthieu Tavernier
//

#ifndef MINIBOMB_HPP_
# define MINIBOMB_HPP_

# include "ABomb.hpp"

class		MiniBomb	: public ABomb
{
public:
  MiniBomb(int id = 1);
  MiniBomb	&operator=(ABomb const *);
  MiniBomb(ABomb const *);
  virtual ~MiniBomb();

public:
  virtual void	willExplose();
  virtual bool		isDestructible() const;

private:
    bool        killObjects(irr::core::vector2df const &pos);
};

#endif
