//
// TrackerBomb.hpp for TRACKER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri May 13 11:06:23 2016 Victor Gouet
// Last update Sat May 14 16:58:41 2016 Victor Gouet
//

#ifndef TRACKERBOMB_HPP_
# define TRACKERBOMB_HPP_

# include "ABomb.hpp"

class		TrackerBomb	: public ABomb
{
public:
  TrackerBomb(int id = -1);
  TrackerBomb	&operator=(ABomb const *);
  TrackerBomb(ABomb const *);
  virtual ~TrackerBomb();

public:
  virtual void	willExplose();
  virtual void	updateTimeOut();

private:
  irr::core::vector2df	_last_dir;
 private:
     bool        killObjects(irr::core::vector2df const &pos);
};

#endif
