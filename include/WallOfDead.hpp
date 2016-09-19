//
// WallOfDead.hpp for DEAD in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Jun  1 14:14:10 2016 Victor Gouet
// Last update Wed Jun  1 19:49:07 2016 Victor Gouet
//

#ifndef WALLOFDEAD_HPP_
# define WALLOFDEAD_HPP_

# include "Explosion.hpp"

class	WallOfDead
{
public:
  WallOfDead(double timeout);
  virtual ~WallOfDead();

public:
  void		createWallOfDead();
  bool		canDropWall() const;

private:
  void		resetPos();

public:
  static const double	timerSpawn;

private:
  double	_beginTimer;
  mutable double	_timeOut;
  int		_pos;
  int		_y1;
  int		_y2;
  int		_y3;
  int		_y4;
};

#endif
