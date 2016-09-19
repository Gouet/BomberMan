//
// WallOfEnd.hpp for WALL OF END in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Jun  1 23:08:27 2016 Victor Gouet
// Last update Wed Jun  1 23:59:37 2016 Victor Gouet
//

#ifndef WALLOFEND_HPP_
# define WALLOFEND_HPP_

# include "AGameObject.hpp"

class	WallOfEnd : public AGameObject
{
public:
  WallOfEnd(irr::core::vector2df const &pos);
  virtual ~WallOfEnd();

public:
  virtual void		updateTimeOut();
  virtual void          dead();
  virtual bool		isDestructible() const;
  virtual void		serialize(irr::io::IXMLWriter *) const;

private:
  irr::core::vector2df	_pos;
  int			_arrived;
};

#endif 
